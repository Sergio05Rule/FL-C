#include "C2Python.h"

// unique id for all ST
int varST_id;
int funcdefST_id;
int funcparST_id;
int arrayparST_id;

int scope_lv = 0; //global var has scope level 0
int aux_last_scope_lv = 0;
int sub_scope_lv = 0; //keep track of sub_scope_lv in a function

int last_definition_type = 0; // keeps track of the definition type
int aux_is_array = 0; // keeps track if the var is an array or not
int aux_par_number = 0; // keeps track of the array dimension number
int aux_funcdef_ST_id = 0; // keeps track of the last funcdefST_id value
int aux_is_parameter = 0; // keeps track if the var is a parameter function or not
int aux_func_par_number = 0; // keeps track of the parameter number of a function
int is_brackets = 0; // keeps track of brakets expr

ast_expr *aux_binop = NULL; //used to propagate flag_brackets to the last ast_binop leaf


/* ST functions */
// Print Symbol Tables
void print_all_st_node()
{
  report_warning("\n--------------------------------------- SYMBOL TABLE PRINT  ---------------------------------------");
  report_warning("------ FUNCDEF TABLE PRINT  ------");
  for (struct funcdef_node *p = funcdef_table; p; p = p->next)
  {
    report_warning("ID:%d\tIdentifier:%s\t ret_typeid:%d\tparameter_num:%d\tScopeLV:%d\tLine_Number:%d", p->id, p->identifier, p->ret_typeid, p->parameter_num, p->scopeId, p->line_number);
  }

  report_warning("\n--- FUNC_PAR TABLE ---");
  for (struct func_par_node *p = func_par_table; p; p = p->next)
  {
    report_warning("ID:%d\t var_id: %d\t identifier: %s\t typeid: %d\tpar_number: %d\t func_id:%d\t",p->id, p->var_id, p->identifier, p->typeid,p->par_number, p->funcId);
  }

  report_warning("\n--- VAR TABLE ---");
  for (struct var_node *p = var_table; p; p = p->next)
  {
    report_warning("ID:%d\tIdentifier:%s\tType:%d\tTypeName:%s\tScopeLV:%d\tsub_scope_lv: %d\tdec_line_number:%d",p->id, p->identifier,p->typeid,p->typeName,p->scopeId,p->sub_scopeId,p->declaration_line_number);
  }

  report_warning("\n--- ARRAY_PAR TABLE ---");
  for (struct array_par_node *p = array_par_table; p; p = p->next)
  {
    report_warning("ID:%d\tvar_id:%d\t par_number:%d\t par_value:%d\t",p->id, p->var_id,p->par_number, p->par_value);
  }
  report_warning("-------------------------------------------------------------------------------------------------\n");
}


/* var symbol Table */
//insert new var in Symbol Table Var
struct var_node* insert_record_varST(int id, char *identifier, int type, int isarray, int scope ,int sub_scope, int line_number, struct var_node *next)
{
  struct var_node *new_record = malloc (sizeof * new_record);

  //check if the var has already been declared in the same scope
  for (struct var_node *p = next; p; p = p->next)
  {
    if(strcmp(identifier,p->identifier) == 0 && (scope_lv == p->scopeId) && sub_scope == p->sub_scopeId)
    {
      report_error("Error at line number: %d - redeclaration of ‘%s’ with no linkage",line_number ,identifier);
    }
  }
  new_record -> id = id;
  strcpy(new_record -> identifier, identifier);
  new_record ->typeid = type;
  if (isarray == 0)
  {
      strcpy(new_record ->typeName, "variable");
  }
  else
  {
    strcpy(new_record ->typeName,"array");
  }
  new_record ->scopeId = scope;
  new_record ->sub_scopeId = sub_scope;
  new_record ->declaration_line_number = line_number;
  new_record -> next = next;
}


/* array_par symbol Table */
//insert a new record in the array_par Symbol Table
struct array_par_node* insert_record_array_parST(int id, int var_id, int par_number, int par_value, struct array_par_node *next)
{
  struct array_par_node *new_record = malloc (sizeof * new_record);
  new_record -> id = id;
  new_record -> var_id = var_id;
  new_record -> par_number = par_number;
  new_record -> par_value = par_value;
  new_record -> next = next;
}

struct array_par_node* update_par_value_record_array_parST(int id, int par_value, struct array_par_node *next)
{
  for (struct array_par_node *p = next; p; p = p->next)
  {
    if(id == p->id)
    {
      p->par_value = par_value;
    }
  }
  return NULL;
}


/* func_def symbol Table */
//insert new function in the funcdef Symbol Table
struct funcdef_node* insert_record_funcdef_node_ST(int id, char *identifier, int ret_typeid, int parameter_num, int scope ,int line_number, struct funcdef_node *next)
{

  struct funcdef_node *new_record = malloc (sizeof * new_record);

  //check if the func has already been declared
  for (struct funcdef_node *p = next; p; p = p->next)
  {
    if(strcmp(identifier,p->identifier) == 0)
    {
      if(p->ret_typeid == ret_typeid)
      report_error("Error at line number: %d - redefinition of ‘%s’.\nPrevious definition of ‘%s’ was at line: %d",line_number ,identifier,identifier,p->line_number);
      else
      report_error("Error at line number: %d - conflicting types for ‘%s’.\nPrevious definition of ‘%s’ was at line: %d",line_number ,identifier,identifier,p->line_number);

    }
  }
  new_record -> id = id;
  strcpy(new_record -> identifier, identifier);
  new_record ->ret_typeid = ret_typeid;
  new_record ->parameter_num = 0;
  new_record ->scopeId = scope;
  new_record ->line_number = line_number;
  new_record -> next = next;
}


//update parameter number in the funcdef Symbol Table
struct funcdef_node* update_par_number_funcdef_node_ST (int id, int line_number)
{
  for (struct funcdef_node *p = funcdef_table; p; p = p->next)
  {
    if(p->id == id)
    {
      p->parameter_num++;
      p->line_number = line_number;
    }
  }
  return NULL;
}


/* func_par Symbol Table */
//insert new function parameter in function parameter Symbol Table
struct func_par_node* insert_record_func_par_ST(int id, int var_id, int typeid,int par_number , int funcId,  struct func_par_node *next)
{
  struct func_par_node *new_record = malloc (sizeof * new_record);
  new_record -> id = id;
  new_record -> var_id = var_id;
  new_record ->typeid = typeid;
  new_record ->par_number = par_number;
  new_record -> funcId = funcId;
  new_record -> next = next;
}

//update the variable identifier
struct func_par_node* update_identifier_funcdef_node_ST (int id, char *identifier)
{
  for (struct func_par_node *p = func_par_table; p; p = p->next)
  {
    if(p->id == id)
    {
      strcpy(p->identifier, identifier);
    }
  }
  return NULL;
}


/* Populate Symbol Table */
void st_populate(ast_node *node)
{
  if(node)
  {
    switch(node->type)
  		{

        case AST_LIST:
        for (; node; node = node->list.tail)
        {
            st_populate(node->list.head);
        }
        break;

        case AST_FUNCDEF:
        scope_lv = aux_last_scope_lv + 1;
        aux_last_scope_lv = scope_lv;
        sub_scope_lv = 0;
        aux_func_par_number = 0;
        funcdef_table = insert_record_funcdef_node_ST(funcdefST_id, node->funcdef.funchead->funchead.sym_name, node->funcdef.ret_type, aux_is_array, scope_lv, node->funcdef.funchead->line_number, funcdef_table);
        funcdefST_id++;
        st_populate(node->funcdef.funchead);
        st_populate(node->funcdef.funcbody);
        scope_lv = 0;
        break;

        case AST_FUNCHEAD:
        st_populate(node->funchead.paras);
        break;

        case AST_PARA:
        aux_is_parameter = 1;
        aux_funcdef_ST_id = funcdefST_id - 1;
        update_par_number_funcdef_node_ST (aux_funcdef_ST_id, node->line_number);
        func_par_table = insert_record_func_par_ST(funcparST_id, varST_id, node->para.para_type,aux_func_par_number, aux_funcdef_ST_id, func_par_table);
        aux_func_par_number++;
        funcparST_id++;
        last_definition_type =  node->para.para_type;
        st_populate(node->para.var);
        break;

        case AST_VAR:
        var_table = insert_record_varST(varST_id, node->var.sym_name , last_definition_type ,aux_is_array, scope_lv, sub_scope_lv, node->line_number,var_table);
        varST_id++;
        if(aux_is_parameter == 1)
        {
          update_identifier_funcdef_node_ST(funcparST_id - 1, node->var.sym_name);
        }
        aux_par_number = 0;
        aux_is_array = 0;
        aux_is_parameter = 0;
        break;

        case AST_SUBVAR_ID:
        aux_par_number++;
        aux_is_array = 1;
        array_par_table = insert_record_array_parST(arrayparST_id, varST_id ,aux_par_number, 1 /*node->subvar.index*/, array_par_table);
        arrayparST_id++;

        if(node->subvar_id.index->type==AST_CONST)
        st_populate(node->subvar_id.index);

        st_populate(node->subvar_id.var);
        break;

        case AST_CONST:
        if(aux_par_number!=0)
        {
          arrayparST_id--;
          update_par_value_record_array_parST(arrayparST_id, node->constant.number ,array_par_table);
          arrayparST_id++;
        }
        break;

        case AST_COMPOUND_STMT:
        sub_scope_lv++;
        st_populate(node->compound_stmt.defs);
        st_populate(node->compound_stmt.stmts);
        break;

        case AST_EXPR_STMT:
        st_populate(node->expr_stmt.expr);
        break;

        case AST_IF_STMT:
        st_populate(node->if_stmt.cond);
        st_populate(node->if_stmt.then);
        st_populate(node->if_stmt.els);
        break;

        case AST_FOR_STMT:
        st_populate(node->for_stmt.init);
        if (node->for_stmt.cond)
          {
            st_populate(node->for_stmt.cond);
          }
        st_populate(node->for_stmt.incr);
        st_populate(node->for_stmt.body);
        break;

        case AST_RETURN_STMT:
        st_populate(node->return_stmt.retval);
        break;

        case AST_DEF:
        last_definition_type = node->def.def_type;
        st_populate(node->def.decs);
        break;

        case AST_DEC:
        st_populate(node->dec.var);
        if (node->dec.init)
        {
            st_populate(node->dec.init);
        }
        break;

        case AST_BINOP:
        st_populate(node->binop.lhs);
        st_populate(node->binop.rhs);
        break;

        case AST_PREFIX:
        st_populate(node->prefix.unary);
        break;

        case AST_POSTFIX:
        st_populate(node->postfix.unary);
        break;

        case AST_INDEXING:
        st_populate(node->indexing.postfix);
        st_populate(node->indexing.expr);
        break;
        }
  }
}


/* Parse Tree Functions */
int int_type(void)
{
  return 1;
}


int void_type(void)
{
  return 2;
}


int float_type(void)
{
  return 3;

}


int double_type(void)
{
  return 4;
}


int char_type(void)
{
  return -2;
}


int str_type(void)
{
  return -3;
}

static ast_node *newast(int type)
{
    ast_node *node = malloc(sizeof(ast_node));
    node->type = type;
    node->type_id = -1;
    node->lvalue = -1;
    node->line_number = -1;
    node->is_brackets = -1;
    return node;
}


ast_list *list_new(int type, ast_node *head, ast_list *tail)
{
    ast_list *l = newast(AST_LIST);
    l->list.type = type;
    l->list.head = head;
    l->list.tail = tail;

    if(is_brackets == 1)
    l->is_brackets = 1;

    is_brackets = 0;

    return l;
}


void brackets_expr_new()
{
    if(aux_binop != NULL && aux_binop->binop.op != '=')
    aux_binop->binop.flag_brackets = 1;

    is_brackets=1;
}


// Allows append of two list element
void list_append(ast_list *first, ast_list *second)
{
    while (first && first->list.tail)
    {
        first = first->list.tail;
    }
    if (first)
    {
        first->list.tail = second;
    }
}

ast_node *funcdef_new(int ret_type, ast_node *funchead, ast_stmt *funcbody)
{
    ast_node *n = newast(AST_FUNCDEF);
    n->funcdef.ret_type = ret_type;
    n->funcdef.funchead = funchead;
    n->funcdef.funcbody = funcbody;
    return n;
}


ast_node *funchead_new(char *sym_name, ast_list *paras, int line_number)
{
    ast_node *n = newast(AST_FUNCHEAD);
    n->funchead.sym_name = sym_name;
    n->funchead.paras = paras;
    n->line_number = line_number;
    return n;
}


ast_node *para_new(int para_type, ast_node *var, int line_number)
{
    ast_node *n = newast(AST_PARA);
    n->para.para_type = para_type;
    n->para.var = var;
    n->line_number = line_number;
    return n;
}


ast_node *var_new(char *sym_name, int line_number)
{
    ast_node *n = newast(AST_VAR);
    n->var.sym_name = sym_name;
    n->line_number = line_number;
    return n;
}


ast_node *subvar_new_id(ast_node *var, ast_node * index, int line_number)
{
    ast_node *n = newast(AST_SUBVAR_ID);
    n->subvar_id.var = var;
    n->subvar_id.index = index;
    n->line_number = line_number;
    return n;
}


ast_stmt *compound_stmt_new(ast_list *defs, ast_list *stmts)
{
    ast_stmt *s = newast(AST_COMPOUND_STMT);
    s->compound_stmt.defs = defs;
    s->compound_stmt.stmts = stmts;
    return s;
}


ast_stmt *expr_stmt_new(ast_expr *expr)
{
    ast_stmt *s = newast(AST_EXPR_STMT);
    s->expr_stmt.expr = expr;
    return s;
}


ast_stmt *if_stmt_new(ast_expr *cond, ast_stmt *then, ast_stmt *els, int line_number)
{
    ast_stmt *s = newast(AST_IF_STMT);
    s->if_stmt.cond = cond;
    s->if_stmt.then = then;
    s->if_stmt.els = els;
    s->line_number = line_number;
    return s;
}


ast_stmt *for_stmt_new(ast_expr *init, ast_expr *cond, ast_expr *incr, ast_stmt *body, int line_number)
{
    ast_stmt *s = newast(AST_FOR_STMT);
    s->for_stmt.init = init;
    s->for_stmt.cond = cond;
    s->for_stmt.incr = incr;
    s->for_stmt.body = body;
    s->line_number = line_number;
    return s;
}


ast_stmt *printf_stmt_new(char *init, ast_node *var, int address, int line_number)
{
    ast_stmt *s = newast(AST_PRINTF_STMT);
    s->printf_stmt.init = init;
    s->printf_stmt.var = var;
    s->printf_stmt.address = address;
    s->line_number = line_number;
    return s;
}


ast_stmt *scanf_stmt_new(char *init, ast_node *var, int line_number)
{
    ast_stmt *s = newast(AST_SCANF_STMT);
    s->scanf_stmt.init = init;
    s->scanf_stmt.var = var;
    s->line_number = line_number;
    return s;
}


ast_stmt *return_stmt_new(ast_expr *retval,int isReturn_var, int line_number)
{
    ast_stmt *s = newast(AST_RETURN_STMT);
    s->return_stmt.retval = retval;
    s->return_stmt.isReturn_var = isReturn_var;
    s->line_number = line_number;
    return s;
}


ast_stmt *continue_stmt_new(int line_number)
{
    ast_stmt *s = newast(AST_CONTINUE_STMT);
    s->line_number = line_number;
    return s;
}

ast_stmt *break_stmt_new(int line_number)
{
    ast_stmt *s = newast(AST_BREAK_STMT);
    s->line_number = line_number;
    return s;
}


ast_node *def_new(int def_type, ast_list *decs)
{
    ast_node *n = newast(AST_DEF);
    n->def.def_type = def_type;
    n->def.decs = decs;
    return n;
}


ast_node *dec_new(ast_node *var, ast_node *init, int line_number)
{
    ast_node *n = newast(AST_DEC);
    n->dec.var = var;
    n->dec.init = init;
    n->line_number = line_number;
    return n;
}


ast_expr *binop_new(int op, ast_expr *lhs, ast_expr *rhs, int flag_brackets, int line_number)
{
    ast_expr *e = newast(AST_BINOP);

    memcpy(&aux_binop,&e,sizeof(struct ast_node));

    e->binop.op = op;
    e->binop.lhs = lhs;
    e->binop.rhs = rhs;
    e->binop.flag_brackets = flag_brackets;
    e->line_number = line_number;
    return e;
}


ast_expr *prefix_new(int op, ast_expr *unary, int line_number)
{
    ast_expr *e = newast(AST_PREFIX);
    e->prefix.op = op;
    e->prefix.unary = unary;
    e->line_number = line_number;
    return e;
}


ast_expr *postfix_new(int op, ast_expr *unary, int line_number)
{
    ast_expr *e = newast(AST_POSTFIX);
    e->postfix.op = op;
    e->postfix.unary = unary;
    e->line_number = line_number;
    return e;
}


ast_expr *indexing_new(ast_expr *postfix, ast_expr *expr, int line_number)
{
    ast_expr *e = newast(AST_INDEXING);
    e->indexing.postfix = postfix;
    e->indexing.expr = expr;
    e->line_number = line_number;
    return e;
}


ast_expr *func_call_new(ast_expr *postfix, ast_list *args, int line_number)
{
    ast_expr *e = newast(AST_FUNC_CALL);
    e->func_call.postfix = postfix;
    e->func_call.args = args;
    e->line_number = line_number;
    return e;
}


ast_expr *id_new(char *sym_name, int line_number)
{
    ast_expr *e = newast(AST_ID);
    e->id.sym_name = sym_name;
    e->line_number = line_number;
    return e;
}


ast_expr *const_new(int number, int line_number)
{
    ast_expr *e = newast(AST_CONST);
    e->constant.number = number;
    return e;
}

ast_expr *const_f_new(char *number, int line_number)
{
    ast_expr *e = newast(AST_CONST_F);
    e->constant_f.number = number;
    e->line_number = line_number;

    return e;
}


ast_expr *const_c_new(char *char_value, int line_number)
{
    ast_expr *e = newast(AST_CONST_C);
    e->constant_c.char_value = char_value;
    e->line_number = line_number;

    return e;
}


ast_expr *const_str_new(char *string, int line_number)
{
    ast_expr *e = newast(AST_CONST_STR);
    e->constant_str.string = string;
    e->line_number = line_number;

    return e;
}
