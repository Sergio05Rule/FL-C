#include "C2Python.h"

typedef void (*ast_translator)(ast_node *n);

static ast_translator g_ast_translators[AST_TYPE_LIMIT];
static const char* g_ast_names[AST_TYPE_LIMIT];

/* Flag & Aux var */
int tabn = 0; // keep track of the tab level/number

int trans_last_ArrayDimension = 0;
int trans_isArray = 0;
int trans_arraydim = 0;  //count array dimension
int trans_last_function_ret_type = 0;

int trans_is_first_subvar = 0; // keep track if we are trans the first subvar

int trans_is_func_def = 0; //keep track if we are in a func definition

/* Scope level tracker */
int trans_scope_level = 0;
int aux_last_trans_scope_level = 0;
int trans_sub_scope_level = 0;
int stack_sub_scope[1024];
int trans_stack_sub_scope_index = 0;

char var_name[1024]; // keep track of the last var name
int trans_array_dim_number = 0; // keep track of array dimension number
int trans_init_array_dimensions[1024]; // keep track of array dimension value i.e. int v[10][11] --> 10,11
int dec_init = 0;// keep track if we are in an int i.e. int var = ---
int trans_is_binop_eq = 0; //keep track if the binop op. is '='
int trans_is_stmt = 0; // keeps track if we are on a stmt instruction (change ++ in + 1 and -- in -1)

char *split = "\n";


void emit(const char *fmt, ...)
{
    va_list args;
    char buffer[1024], format[1024];

    va_start(args, fmt);
    vsnprintf(buffer, sizeof buffer, fmt, args);
    va_end(args);

    sprintf(format, "%s", buffer);

    fprintf(stdout, "%s", format);
}


// emit tab for a tabn number
void emit_tab()
{
	for (int i = 0; i < tabn; ++i) {
		emit("\t");
	}
}


// emit of new line
void emit_newline()
{
	for (int i = 0; i < 1; ++i) {
		emit("\n");
	}
}


// replace substring
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}


// retrieve type_id
char * retrieve_type_str(int type)
{
  switch(type)
  {
    case 1:
      return "int";
      break;
    case -2:
      return "str"; //char is str (string) in python
      break;
    case 2:
      return "None"; //void is None in python
      break;
    case 3:
      return "float";
      break;
    case 4:
      return "float"; //python does not have double
      break;
    case -3:
      return "str"; //String is str (string) in python
      break;
  }
}


int closed_list = 0;
void check_closed()
{
  if(closed_list > 1)
  {
    closed_list = 0;
    emit_newline();
    emit_tab();
  }
}

static void trans_list(ast_node *n)
{
    closed_list = 0;
    for (; n; n = n->list.tail)
    {
        trans_ast(n->list.head);
        if (n->list.tail)
        {
          emit("%s", split);
          if (strcmp(split,"\n") == 0)
          emit_tab();
        }
        else{
            closed_list++;
            check_closed();
           }
    }
}


static void trans_funcdef(ast_node *n)
{
  emit_newline(); //PEP8 two blank lines
  trans_last_function_ret_type = n->funcdef.ret_type;

  trans_scope_level = aux_last_trans_scope_level + 1;
  aux_last_trans_scope_level = trans_scope_level;

  trans_sub_scope_level = 0;
  trans_stack_sub_scope_index = 0;
  stack_sub_scope[trans_stack_sub_scope_index] = 0;

  emit("\n%s ","def");
  emit("%s",  n->funcdef.funchead->funchead.sym_name);
  emit("%s","(");

  trans_is_func_def = 1;
  trans_ast(n->funcdef.funchead);
  trans_is_func_def = 0;

  emit(") -> %s:",retrieve_type_str(trans_last_function_ret_type));
  tabn++;
  emit_newline();
  emit_tab();
  trans_ast(n->funcdef.funcbody);
  tabn--;
  emit_newline(); //PEP8
  emit_newline(); //PEP8
  trans_scope_level = 0;
}


static void trans_funchead(ast_node *n)
{
  struct funcdef_node * f_def = find_record_scope_funcdef_node_ST( n->funchead.sym_name,trans_scope_level);
  split=", ";
  trans_ast(n->funchead.paras);
  split="\n";
}

static void trans_para(ast_node *n)
{
  trans_ast(n->para.var);
}


static void trans_def(ast_node *n)
{
  trans_ast(n->def.decs);
}


static void trans_dec(ast_node *n)
{
  trans_is_first_subvar = 0;
  trans_array_dim_number = 0;

	if (n->dec.init)
     dec_init = 1;
	else
    dec_init = 0;

  trans_ast(n->dec.var);

  if (n->dec.init)
    {
        //init a non array var
        if(trans_isArray == 0)
        {
          emit(" = ");
          trans_ast(n->dec.init);
        }
    }

  // special case i.e char v[10] = "ciao" (NB vector char 1-d)
  if (trans_isArray == 1 )
  {
    if (n->dec.init)
    {

      if(n->dec.init->type_id == str_type())
      {
        emit(" 0"); // closing np.full
        emit("%s",", dtype=object)");

        char c[1024];
        int str_len = strlen(n->dec.init->constant_str.string) - 1; //include " " (2 chars)

        strcpy(c, n->dec.init->constant_str.string);

        for(int i_str = 1; i_str<str_len; i_str++)
        {
          emit_newline();
          emit_tab();
          //stampa nove var con la hiusta dimensions_number
          emit("%s",var_name);
          emit(" = np.insert(%s,",var_name);
          emit("%d ",i_str-1);
          emit(", ");
          emit(" '%c'",c[i_str]);
          emit(")");
        }

        // resize
        emit_newline();
        emit_tab();
        emit("%s = np.resize(%s , (",var_name,var_name);

        int is_first = 0;
        for (int i = 0; i<trans_array_dim_number;i++)
        {
          if (is_first!=0)
          emit(" , ");

          emit("%d",trans_init_array_dimensions[i]);
          is_first++;
        }
        emit("))");
      }
    }
    else{
      emit("%s","0");
      emit("%s",", dtype=object)");
    }
  }

  if(trans_isArray == 1 && dec_init == 1) //init with array {...}
  {
    ast_node *p = n->dec.init;

    if (p->type == AST_LIST) // case init with {}
    {
      emit(" 0"); // closing np.full
      emit("%s",", dtype=object)");
      emit_newline();
      emit_tab();
      emit("# the following lines are needed to preserve c initialization");

      int i=0;
      int dim_count=0;
      for (; p; p = p->list.tail, i++)
      {

        if(p->list.head->type_id == str_type())
        {
          char c[1024];
          int str_len = strlen(p->list.head->constant_str.string) - 1; //include " " (2 chars)

          strcpy(c, p->list.head->constant_str.string);

          for(int i_str = 1 /* skip first "*/ ; i_str<trans_last_ArrayDimension+1; i_str++)
          {
            emit_newline();
            emit_tab();
            emit("%s",var_name);
            emit(" = np.insert(%s,",var_name);
            emit("%d ",dim_count);
            emit(", ");

            if(c[i_str] != '"'  && c[i_str] != '\0'  && i_str<str_len)
            emit(" '%c'",c[i_str]);
            else
            emit("0");

            emit(")");
            dim_count++;
          }

        }
        else
        {
          emit_newline();
          emit_tab();
          emit("%s",var_name);
          emit(" = np.insert(%s,",var_name);
          emit("%d ",dim_count);
          emit(", ");
          trans_ast(p->list.head);
          emit(")");
          dim_count++;
        }

      }

      //resize to original dimension with the inizialized element in the correct position
      emit_newline();
      emit_tab();
      emit("%s = np.resize(%s , (",var_name,var_name);

      int is_first = 0;
      for (int i = 0; i<trans_array_dim_number;i++)
      {
        if (is_first!=0)
        emit(" , ");
        emit("%d",trans_init_array_dimensions[i]);
        is_first++;
      }
      emit("))");

    }

  }

  if (dec_init == 0 && trans_isArray == 0)
  emit(" = 0");
}


static void trans_var(ast_node *n)
{
  struct var_node* vn = find_record_scope_varST(n->var.sym_name, trans_scope_level, trans_stack_sub_scope_index, n->line_number);

  strcpy(var_name,vn->identifier);
  trans_last_ArrayDimension = retrieve_last_dimension_array_parST(vn->id);

  if(strcmp(vn->typeName,"array") == 0)
    trans_isArray = 1;
  else
    trans_isArray = 0;

  trans_arraydim = count_dimension_array_parST(vn->id);
  emit("%s: %s", n->var.sym_name,retrieve_type_str(vn->typeid) );
}


static void trans_subvar_id(ast_node*n)
{
  trans_is_first_subvar++;

  trans_ast(n->subvar_id.var);

  if (trans_is_func_def == 0)
  {
    if (trans_is_first_subvar == trans_arraydim)
    emit(" = np.full((");

    if (trans_is_first_subvar != trans_arraydim)
    emit(" ,");

    trans_ast(n->subvar_id.index);

    trans_is_first_subvar--;

    if(trans_is_first_subvar == 0)
    emit("%s","), ");
  }

  // retrieve array dimension pars
  if (dec_init == 1 && trans_isArray==1)
  {
    trans_init_array_dimensions[trans_array_dim_number] = n->subvar_id.index->constant.number;
    trans_array_dim_number++;
  }
}


static void trans_compound_stmt(ast_node *n)
{
  trans_sub_scope_level++;
  trans_stack_sub_scope_index++;
  stack_sub_scope[trans_stack_sub_scope_index] = trans_sub_scope_level;

  // emit pass to let empty compound stmt
  if(n->compound_stmt.stmts==NULL && n->compound_stmt.defs==NULL)
  {
    emit("pass");
    //emit_newline();
    //emit_tab();
  }

	split = "\n";
	trans_ast(n->compound_stmt.defs);
  trans_ast(n->compound_stmt.stmts);

  trans_stack_sub_scope_index--;
}


static void trans_expr_stmt(ast_node *n)
{
  trans_ast(n->expr_stmt.expr);
}


// operator conversion between c and python
static const char * binop_instr(int op)
{
    switch (op)
    {
    case GE_OP:
        return ">=";
    case LE_OP:
        return "<=";
    case EQ_OP:
        return "==";
    case NE_OP:
        return "!=";
    case AND_OP:
		  return "and";
	  case OR_OP:
		  return "or";
	  case '+':
        return "+";
    case '-':
        return "-";
    case '*':
        return "*";
    case '/':
        return "/";
    case '%':
        return "%";
    case '&':
        return "&";
    case '>':
        return ">";
    case '<':
        return "<";
	case '=':
    trans_is_binop_eq = 1;
		return "=";
    }
    return "Unkonwn operator!";
}


static void trans_if_stmt(ast_node *n)
{
  trans_is_binop_eq = 0;
  emit("if ");
  trans_ast(n->if_stmt.cond);
  emit(":");

  // case: translating an equal binop -> i.e if ( i=0 ) { works in C }
  if(trans_is_binop_eq == 1)
  emit("  # Error: python cannot accept assignment in if statement");
  tabn++;
  emit_newline();
  emit_tab();
  trans_ast(n->if_stmt.then);
  tabn--;
  if(n->if_stmt.els != NULL)
  {
    emit_newline();
    emit_tab();
    emit("else:");
    tabn++;
    emit_newline();
    emit_tab();
    trans_ast(n->if_stmt.els);
    tabn--;
  }
}


static void trans_for_stmt(ast_node *n)
{
  trans_is_binop_eq = 0;
  int for_init = 0;
  int for_cond = 0;
  int for_incr = 0;

  if (n->for_stmt.init != NULL)
  for_init = 1;

  if (n->for_stmt.cond != NULL)
  for_cond = 1;

  if (n->for_stmt.incr != NULL)
  for_incr = 1;

  if(for_init == 1 && for_cond == 1 && for_incr == 1)
  {
    trans_ast(n->for_stmt.init);
    emit_newline();
    emit_tab();
    emit("while ");
    trans_ast(n->for_stmt.cond);
    emit(":");
    if(trans_is_binop_eq == 1)
    emit("  # Error: python cannot accept assignment in for statement");
    tabn++;
    emit_newline();
    emit_tab();
    trans_ast(n->for_stmt.body);
    emit_newline();
    emit_tab();
    trans_ast(n->for_stmt.incr);
  }

  if(for_init == 1 && for_cond == 1 && for_incr == 0)
  {
    trans_ast(n->for_stmt.init);
    emit_newline();
    emit_tab();
    emit("while ");
    trans_ast(n->for_stmt.cond);
    emit(":");
    if(trans_is_binop_eq == 1)
    emit("  # Error: python cannot accept assignment in for statement");
    tabn++;
    emit_newline();
    emit_tab();
    trans_ast(n->for_stmt.body);

  }
  if(for_init == 1 && for_cond == 0 && for_incr == 1)
  {
    trans_ast(n->for_stmt.init);
    emit_newline();
    emit_tab();
    emit("while 1:  # warning: infinite loop");
    tabn++;
    emit_newline();
    emit_tab();
    trans_ast(n->for_stmt.body);
    emit_newline();
    emit_tab();
    trans_ast(n->for_stmt.incr);
  }
  if(for_init == 1 && for_cond == 0 && for_incr == 0)
  {
    trans_ast(n->for_stmt.init);
    emit_newline();
    emit_tab();
    emit("while 1:  # warning: infinite loop");
    tabn++;
    emit_newline();
    emit_tab();
    trans_ast(n->for_stmt.body);
  }
  if(for_init == 0 && for_cond == 1 && for_incr == 1)
  {
    emit("while ");
    trans_ast(n->for_stmt.cond);
    emit(":");
    if(trans_is_binop_eq == 1)
    emit("  # Error: python cannot accept assignment in for statement");
    tabn++;
    emit_newline();
    emit_tab();
    trans_ast(n->for_stmt.body);
    emit_newline();
    emit_tab();
    trans_ast(n->for_stmt.incr);
  }
  if(for_init == 0 && for_cond == 1 && for_incr == 0)
  {
    emit("while ");
    trans_ast(n->for_stmt.cond);
    emit(":");
    if(trans_is_binop_eq == 1)
    emit("  # Error: python cannot accept assignment in for statement");
    tabn++;
    emit_newline();
    emit_tab();
    trans_ast(n->for_stmt.body);
  }

  if(for_init == 0 && for_cond == 0 && for_incr == 1)
  {
    emit("while 1:  # warning: infinite loop");
    tabn++;
    emit_newline();
    emit_tab();
    trans_ast(n->for_stmt.body);
    emit_newline();
    emit_tab();
    trans_ast(n->for_stmt.incr);
  }

  if(for_init == 0 && for_cond == 0 && for_incr == 0)
  {
    emit("while 1:  # warning: infinite loop");
    tabn++;
    emit_newline();
    emit_tab();
    trans_ast(n->for_stmt.body);
  }
  tabn--;
}


static void trans_printf_stmt(ast_node *n)
{
  int format_specifier_typeid = 0;
  trans_is_stmt = 1;

  // retrieve format specifier
  if (strstr(n->scanf_stmt.init,"%d")!=NULL)
      format_specifier_typeid = int_type();

  if (strstr(n->scanf_stmt.init,"%f")!=NULL)
      format_specifier_typeid = float_type();

  if (strstr(n->scanf_stmt.init,"%c")!=NULL)
      format_specifier_typeid = char_type();

  if (strstr(n->scanf_stmt.init,"%p")!=NULL)
      format_specifier_typeid = -4;

  if (strstr(n->scanf_stmt.init,"%lf")!=NULL)
      format_specifier_typeid = double_type();

  //replace_char(n->printf_stmt.init,'%','{');
  n->printf_stmt.init = str_replace(n->printf_stmt.init,"%d","{}");
  n->printf_stmt.init = str_replace(n->printf_stmt.init,"%c","{}");
  n->printf_stmt.init = str_replace(n->printf_stmt.init,"%f","{}");
  n->printf_stmt.init = str_replace(n->printf_stmt.init,"%lf","{}");
  n->printf_stmt.init = str_replace(n->printf_stmt.init,"%p","{}");

  if(n->printf_stmt.address == 0) // without '&'
  {
    emit("print(");
    emit("%s",n->printf_stmt.init);

    if(n->printf_stmt.var != NULL)
    {
      emit(".format(");

      if (format_specifier_typeid == int_type())
        emit("char2ascii(");

      if (format_specifier_typeid == char_type())
      emit("ascii2char(");

      trans_ast(n->printf_stmt.var);

      if (format_specifier_typeid== int_type() || format_specifier_typeid== char_type())
      emit(")), end='')");
      else
      emit("), end='')");
    }
    else
    {
      emit(", end='')");
    }
  }
  else // with '&'
  {
    emit("print(");
    emit("%s",n->printf_stmt.init);

    if(n->printf_stmt.var!=NULL)
    {
      emit(".format(hex(id(");
      trans_ast(n->printf_stmt.var);
      emit("))), end='')");
    }
    else
    {
      emit(", end='')");
    }
  }
  trans_is_stmt = 0;
}


static void trans_scanf_stmt(ast_node *n)
{
  trans_is_stmt = 1;

  trans_ast(n->scanf_stmt.var);

  // retrieve format specifier
  if (strstr(n->scanf_stmt.init,"%d")!=NULL)
        {
          emit(" = int(input())");
        }
  if (strstr(n->scanf_stmt.init,"%f")!=NULL)
        {
          emit(" = float(input())");
        }
  if (strstr(n->scanf_stmt.init,"%c")!=NULL)
        {
          emit(" = input()");
        }
  if (strstr(n->scanf_stmt.init,"%p")!=NULL)
        {
          emit(" = id(input())"); // we don't have pointers in our compiler, therefore %p is used for printf memory address
        }
  if (strstr(n->scanf_stmt.init,"%lf")!=NULL)
        {
          emit(" = float(input())");
        }

  trans_is_stmt = 0;

}


static void trans_return_stmt(ast_node *n)
{
  if(trans_last_function_ret_type == void_type() )
  emit("return None ");
  else
  emit("return ");
  trans_ast(n->return_stmt.retval);
}


static void trans_continue_stmt(ast_node *n)
{
  emit("continue");
}


static void trans_break_stmt(ast_node *n)
{
  emit("break");
}


static void trans_binop(ast_node *n)
{
  trans_is_stmt = 1;

  if(n->binop.flag_brackets == 1)
  emit("(");

  if((n->binop.lhs->type_id==int_type() || n->binop.lhs->type_id==char_type()) && (n->binop.lhs->type == AST_CONST_C || n->binop.lhs->type == AST_INDEXING || n->binop.lhs->type == AST_ID ) && n->binop.op !='='  /*&& n->binop.op !=NE_OP*/)
  emit("char2ascii(");

  trans_ast(n->binop.lhs);

  if((n->binop.lhs->type_id==int_type() || n->binop.lhs->type_id==char_type()) && (n->binop.lhs->type == AST_CONST_C || n->binop.lhs->type == AST_INDEXING || n->binop.lhs->type == AST_ID ) && n->binop.op !='=' /* && n->binop.op !=NE_OP*/)
  emit(")");

  emit(" %s ", binop_instr(n->binop.op));

  if((n->binop.rhs->type_id==int_type() || n->binop.rhs->type_id==char_type()) && (n->binop.rhs->type == AST_CONST_C || n->binop.rhs->type == AST_INDEXING || n->binop.rhs->type == AST_ID ) )
  emit("char2ascii(");

  trans_ast(n->binop.rhs);

  if((n->binop.rhs->type_id==int_type() || n->binop.rhs->type_id==char_type()) && (n->binop.rhs->type == AST_CONST_C || n->binop.rhs->type == AST_INDEXING || n->binop.rhs->type == AST_ID ) )
  emit(")");

  if(n->binop.flag_brackets == 1)
  emit(")");

  trans_is_stmt = 0;
}


static void trans_prefix(ast_node *n)
{
  if(trans_is_stmt == 0)
  {
    if (n->prefix.op == INC_OP)
    {
      trans_ast(n->prefix.unary);
      emit(" = char2ascii(");
      trans_ast(n->prefix.unary);
      emit(") + 1");
      trans_is_binop_eq = 1;
    }
    else if (n->prefix.op == DEC_OP)
    {
      trans_ast(n->prefix.unary);
      emit(" = char2ascii(");
      trans_ast(n->prefix.unary);
      emit(") - 1");
      trans_is_binop_eq = 1;
    }
  	else if (n->prefix.op == '!'){
    emit("not(");
    trans_ast(n->prefix.unary);
    emit(")");
    }
    else if (n->prefix.op == '-'){
    emit(" - ");
    trans_ast(n->prefix.unary);
    }
  }

  if(trans_is_stmt == 1)
  {
    if (n->prefix.op == INC_OP)
    {
      emit("(char2ascii(");
      trans_ast(n->prefix.unary);
      emit(") + 1)");
      trans_is_binop_eq = 1;
    }
    else if (n->prefix.op == DEC_OP)
    {
      emit("(char2ascii(");
      trans_ast(n->prefix.unary);
      emit(") - 1)");
      trans_is_binop_eq = 1;
    }
  	else if (n->prefix.op == '!'){
    emit("not(");
    trans_ast(n->prefix.unary);
    emit(")");
    }
    else if (n->prefix.op == '-'){
    emit(" - ");
    trans_ast(n->prefix.unary);
    }
  }

}


static void trans_postfix(ast_node *n)
{

  if(trans_is_stmt == 0 )
  {
    if (n->postfix.op == INC_OP)
    {
      trans_ast(n->postfix.unary);
      emit(" = char2ascii(");
      trans_ast(n->postfix.unary);
      emit(") + 1");
      trans_is_binop_eq = 1;
    }
    else if (n->postfix.op == DEC_OP)
    {
      trans_ast(n->postfix.unary);
      emit(" = char2ascii(");
      trans_ast(n->postfix.unary);
      emit(") - 1");
      trans_is_binop_eq = 1;
    }
  }

  if(trans_is_stmt == 1 )
  {
    if (n->postfix.op == INC_OP)
    {
      emit("(char2ascii(");
      trans_ast(n->postfix.unary);
      emit(") + 1)");
      trans_is_binop_eq = 1;
    }
    else if (n->postfix.op == DEC_OP)
    {
      emit("(char2ascii(");
      trans_ast(n->postfix.unary);
      emit(") - 1)");
      trans_is_binop_eq = 1;
    }
  }
}


static void trans_indexing(ast_node *n)
{

    trans_ast(n->indexing.postfix);

    emit("[");
    trans_ast(n->indexing.expr);
    emit("]");

}


static void trans_func_call(ast_node *n)
{
  trans_is_stmt = 1;
  trans_ast(n->func_call.postfix);
  emit("(");
  if (n->func_call.args) {
  	split = ", ";
  	trans_ast(n->func_call.args);
  	split = "";
  }
  emit(")");
  split="\n";
  trans_is_stmt = 0;
}


static void trans_id(ast_node *n)
{
  emit("%s",n->id.sym_name);
}


static void trans_const(ast_node *n)
{
  emit("%d", n->constant.number);
}


static void trans_const_f(ast_node *n)
{
  emit("%s", n->constant_f.number);
}


static void trans_const_c(ast_node *n)
{
  emit("%s", n->constant_c.char_value);
}


static void trans_const_str(ast_node *n)
{
  emit("%s", n->constant_str.string);
}


static void init_ast_translators()
{
    if (g_ast_translators[0]) return;

    g_ast_translators[AST_LIST] = trans_list;
    g_ast_translators[AST_FUNCDEF] = trans_funcdef;
    g_ast_translators[AST_FUNCHEAD] = trans_funchead;
    g_ast_translators[AST_PARA] = trans_para;
    g_ast_translators[AST_VAR] = trans_var;
    g_ast_translators[AST_SUBVAR_ID] = trans_subvar_id;
    g_ast_translators[AST_COMPOUND_STMT] = trans_compound_stmt;
    g_ast_translators[AST_EXPR_STMT] = trans_expr_stmt;
    g_ast_translators[AST_IF_STMT] = trans_if_stmt;
    g_ast_translators[AST_FOR_STMT] = trans_for_stmt;
    g_ast_translators[AST_PRINTF_STMT] = trans_printf_stmt;
    g_ast_translators[AST_SCANF_STMT] = trans_scanf_stmt;
    g_ast_translators[AST_RETURN_STMT] = trans_return_stmt;
    g_ast_translators[AST_CONTINUE_STMT] = trans_continue_stmt;
    g_ast_translators[AST_BREAK_STMT] = trans_break_stmt;
    g_ast_translators[AST_DEF] = trans_def;
    g_ast_translators[AST_DEC] = trans_dec;
    g_ast_translators[AST_BINOP] = trans_binop;
    g_ast_translators[AST_PREFIX] = trans_prefix;
    g_ast_translators[AST_POSTFIX] = trans_postfix;
    g_ast_translators[AST_INDEXING] = trans_indexing;
    g_ast_translators[AST_FUNC_CALL] = trans_func_call;
    g_ast_translators[AST_ID] = trans_id;
    g_ast_translators[AST_CONST] = trans_const;
    g_ast_translators[AST_CONST_F] = trans_const_f;
    g_ast_translators[AST_CONST_C] = trans_const_c;
    g_ast_translators[AST_CONST_STR] = trans_const_str;

    g_ast_names[AST_LIST] = "trans_list";
    g_ast_names[AST_FUNCDEF] = "trans_funcdef";
    g_ast_names[AST_FUNCHEAD] = "trans_funchead";
    g_ast_names[AST_PARA] = "trans_para";
    g_ast_names[AST_VAR] = "trans_var";
    g_ast_names[AST_SUBVAR_ID] = "trans_subvar_id";
    g_ast_names[AST_COMPOUND_STMT] = "trans_compound_stmt";
    g_ast_names[AST_EXPR_STMT] = "trans_expr_stmt";
    g_ast_names[AST_IF_STMT] = "trans_if_stmt";
    g_ast_names[AST_FOR_STMT] = "trans_for_stmt";
    g_ast_names[AST_PRINTF_STMT] = "trans_printf_stmt";
    g_ast_names[AST_SCANF_STMT] = "trans_scanf_stmt";
    g_ast_names[AST_RETURN_STMT] = "trans_return_stmt";
    g_ast_names[AST_CONTINUE_STMT] = "trans_continue_stmt";
    g_ast_names[AST_BREAK_STMT] = "trans_break_stmt";
    g_ast_names[AST_DEF] = "trans_def";
    g_ast_names[AST_DEC] = "warning_count";
    g_ast_names[AST_BINOP] = "trans_binop";
    g_ast_names[AST_PREFIX] = "trans_prefix";
    g_ast_names[AST_POSTFIX] = "trans_postfix";
    g_ast_names[AST_INDEXING] = "trans_indexing";
    g_ast_names[AST_FUNC_CALL] = "trans_func_call";
    g_ast_names[AST_ID] = "trans_id";
    g_ast_names[AST_CONST] = "trans_const";
    g_ast_names[AST_CONST_F] = "trans_const_f";
    g_ast_names[AST_CONST_C] = "trans_const_c";
    g_ast_names[AST_CONST_STR] = "trans_const_str";
}


void trans_ast(ast_node *n)
{
    init_ast_translators();
    if (n)
    {
        g_ast_translators[n->type](n);
    }
}


void trans_char2ascii()
{
  emit("# Return ASCII value from char, otherwise return the value itself");
  emit_newline();
  emit_tab();
  emit("def char2ascii(var):");
  tabn++;
  emit_newline();
  emit_tab();
  emit("if type(var) != str:");
  tabn++;
  emit_newline();
  emit_tab();
  emit("return int(var) ");
  tabn--;
  emit_newline();
  emit_tab();
  emit("else:");
  tabn++;
  emit_newline();
  emit_tab();
  emit("return ord(var[0])");
  tabn--;
  tabn--;
  emit_newline();
  emit_newline();
  emit_newline();
}


void trans_ascii2char()
{
  emit("# Return char from ASCII value, otherwise return the char itself");
  emit_newline();
  emit_tab();
  emit("def ascii2char(var):");
  tabn++;
  emit_newline();
  emit_tab();
  emit("if type(var) == str:");
  tabn++;
  emit_newline();
  emit_tab();
  emit("return var[0]");
  tabn--;
  emit_newline();
  emit_tab();
  emit("else:");
  tabn++;
  emit_newline();
  emit_tab();
  emit("return chr(int(var))");
  tabn--;
  tabn--;
  emit_newline();
}


void transtext_ast(ast_node *n)
{
  emit("# Please, check the installation of the following libraries");
  emit_newline();
	emit("import typing");
  emit_newline();
  emit("import numpy as np");
  emit_newline();
  emit_newline();
  emit_newline();

  /* Auxiliar function definition */
  trans_char2ascii();
  trans_ascii2char();
  /*  */

  trans_ast(n);

  //emit_newline();
  //emit_newline();
  emit("if __name__ == \"__main__\":");
  tabn++;
  emit_newline();
  emit_tab();
  emit("main()  # please, insert parameters if needed");
  emit_newline();
}
