#include "C2Python.h"

/* Flag & Aux var */
char var_name[512]; // keeps track of the last var name
int is_printf_address = 0; //keeps track if we are printing an address

int last_function_ret_type = 0; //keeps track of a function return type

int isZero = 0; // keeps track if the last constant is a zero or not
int isNegative = 0; // keeps track of a '-' prefix

int isBinop = 0; // Keeps track if we are checking a binop

int isFunc_call = 0; // keeps track if we are checking a function call leaf
int isFunc_call_par = 0; // keeps track if we are checking a function paramater
int isFunc_call_lvalue = 0; // keeps track of func call for l value errors

/* keeps track of the dimension of the var (parameter) used in the funcion call */
int given_declareted_dimension = 0; //dimension number of the declaration
int given_called_dimension = 0; //dimension number used in the function call

int e_present_flag = 0; //Keeps track of the presence of a power^10 floating number for overflow warning (simulating this warning)

int str_len = 0; // allows to count char of a string

int first_indexing = 0; //checks if postfix op are incorrect
int is_dec = 0; // keeps track if we are in a declaration leaf

/* record array dim and parameter for the parse tree */
int tree_ArrayDim = 0;
int tree_ArrayDim_subvar = 0;
int is_subvar_id = 0; //keeps track if we are using a variable dimension

int isArray = 0; //keeps track of array's vars

int isId_init = 0; //keeps track if the init of a declaration is a var

int error_flag_Id = 0; //keeps track of an occurence of warning in the AST_ID leaf. Used for return errors

int multi_array_dim; // keeps track of the product of the n-dimensions of an array
int last_ArrayDimension; // keeps track of the last dimension of an array
int ArrayDim; // keeps track of array's number of dimensions

/* Scope level tracker */
int scope_level = 0;
int aux_last_scope_level = 0;
int sub_scope_level = 0;
int stack_sub_scope[1024];
int stack_sub_scope_index = 0;

int loop_level = 0; // keeps track of loop level

int warning_count = 0; // counts the warning number

/* Declarations ST */
struct var_node *var_table;
struct funcdef_node *funcdef_table;
struct func_par_node *func_par_table;
struct array_par_node *array_par_table;

/* ST functions */
// finds a var record in the var ST with respect to the scope
struct var_node* find_record_scope_varST(char *identifier, int scope_lv, int stack_sub_scope_index, int line_number)
{
  while(stack_sub_scope_index >= 0) //check for every sub_scopeId
  {
    for (struct var_node *p = var_table; p; p = p->next)
    {
      if(strcmp(identifier,p->identifier) == 0 && (scope_lv == p->scopeId && p->sub_scopeId == stack_sub_scope[stack_sub_scope_index] ) /*&& line_number>= p->declaration_line_number*/)
      {
        return p;
      }
    }
    stack_sub_scope_index--;
  }


  for (struct var_node *p = var_table; p; p = p->next)
  {
    if(strcmp(identifier,p->identifier) == 0 && (p->scopeId == 0) && line_number>= p->declaration_line_number)
    {
      return p;
    }
  }
  return NULL;
}


// given the var id, counts the number of var/array dimensions
int count_dimension_array_parST(int var_id)
{
  int dimensions_number = 0;
  for (struct array_par_node *p = array_par_table; p; p = p->next)
  {
    if(p->var_id == var_id)
    {
      dimensions_number = dimensions_number + 1;
    }
  }
  return dimensions_number;
}


// given the var id, retrieves the multiplied dimension value
int retrieve_multiply_dimension_array_parST(int var_id)
{
  int dimensions_multiply = 1;
  for (struct array_par_node *p = array_par_table; p; p = p->next)
  {
    if(p->var_id == var_id)
    {
      dimensions_multiply = dimensions_multiply * p->par_value;
    }
  }
  return dimensions_multiply;
}


// given the var id, retrieves the last array dimension value
int retrieve_last_dimension_array_parST(int var_id)
{
  int i = 0;
  int a = 0;
  for (struct array_par_node *p = array_par_table; p; p = p->next)
  {
    if(p->var_id == var_id)
    {
      a = p->par_value;
    }
    i++;
  }
  return a;
}


// finds a function record in the funcdef_node ST in all the scopes
struct funcdef_node* find_record_funcdef_node_ST(char *identifier)
{
  for (struct funcdef_node *p = funcdef_table; p; p = p->next)
  {
    if(strcmp(identifier,p->identifier) == 0)
    {
      return p;
    }
  }
  return NULL;
}


// finds a function record in the funcdef_node ST with respect to the scope
struct funcdef_node* find_record_scope_funcdef_node_ST(char *identifier, int scope_lv)
{
  for (struct funcdef_node *p = funcdef_table; p; p = p->next)
  {
    if((strcmp(identifier,p->identifier) == 0 && scope_lv >= p->scopeId) ||(strcmp(identifier,p->identifier) == 0 && scope_lv == 0) )
    {
      return p;
    }
  }
  return NULL;
}


// given the func_id and the par_number, retrieves record of the specified parameter
struct func_par_node* find_record_par_node_ST(int func_id, int par_number)
{
  for (struct func_par_node *p = func_par_table; p; p = p->next)
  {
    if(p->funcId == func_id && par_number == p->par_number)
    {
      return p;
    }
  }
  return NULL;
}

typedef void (*ast_checker)(ast_node *n);

static ast_checker g_ast_checkers[AST_TYPE_LIMIT];
static const char* g_ast_names[AST_TYPE_LIMIT];


void report_error(const char *fmt, ...)
{
    va_list args;
    char buffer[1024];

    va_start(args, fmt);
    vsnprintf(buffer, sizeof buffer, fmt, args);
    va_end(args);

    fprintf(stderr, "%s\n", buffer);
    exit(1);
}


void report_warning(const char *fmt, ...)
{
    va_list args;
    char buffer[1024];

    va_start(args, fmt);
    vsnprintf(buffer, sizeof buffer, fmt, args);
    va_end(args);
    warning_count++;
    fprintf(stderr, "%s\n", buffer);
}


int binary_operator_case(int op)
{

  switch (op)
    {
    case '=':
    case '&':
    case '%':
    case '*':
    case '/':
        return 1;

    case GE_OP:
    case LE_OP:
    case EQ_OP:
    case NE_OP:
    case '<':
    case '>':
      return 2;

    case '+':
    case '-':
      return 3;

    case AND_OP:
    case OR_OP:
      return 4;
    }

    return 0;
}


/* AST Functions */
static void check_list(ast_node *n)
{
    ast_node *p = n;
    for (; p; p = p->list.tail)
    {
         p->list.head->is_brackets = p->is_brackets ;
        check_ast(p->list.head);
    }
}


static void check_def(ast_node *n)
{
  n->type_id =  n->def.def_type;
  check_ast(n->def.decs);
}


static void check_dec(ast_node *n)
{
    is_dec = 1;
    is_subvar_id = 0;
    isNegative = 0;
    isArray = 0;
    str_len = 0;
    isId_init = 0;

    check_ast(n->dec.var);
    n->type_id = n->dec.var->type_id;

    if (n->dec.init)
    {
        isId_init = 0;
        check_ast(n->dec.init);
        ast_node *p = n->dec.init;

        // it's not possibile to inizialize element with another var/func in the global scopes
        if( (scope_level==0 && isId_init==1) || scope_level==0 && isFunc_call==1)
        report_error("Error at line number: %d - initializer element is not constant",n->line_number);

        //if the var is a non-array type, the var is like a monodimensional "array[1]"
        if(isArray == 0)
        last_ArrayDimension = 1;

        if(is_subvar_id == 1)
        report_error("Error at line number: %d - variable-sized object may not be initialized",n->line_number);

        if (p->type == AST_LIST) //init with { }
        {
          int string_count=0;
          int i = 0;

          int first_element = 0;
          for (; p; p = p->list.tail, ++i)
          {
              //var is char and element of the list type = String is permitted only once
              if (p->list.head->type_id == str_type() && n->type_id == char_type())
              {
                str_len = strlen(p->list.head->constant_str.string);
                str_len = str_len -2 ; //" " -> NOT to include in the count of chars

                string_count++;
                if(string_count>1 && ArrayDim==1 )
                report_error("Error at line number: %d - excess elements in char initializer",n->line_number);

                if(isArray==0)
                report_warning("Warning at line number: %d - makes integer from pointer without a cast",n->line_number);

                if(isArray==1 && last_ArrayDimension<str_len)
                report_warning("Warning at line number: %d - initializer-string for array of chars is too long",n->line_number);

                i = i + last_ArrayDimension -1; //each string corresponds to a block relative to the last array dimension  i.e char v3[5][10] 5 words with 10 characters
              }

              //i.e. int v[10]={"ciao"};
              if (p->list.head->type_id== str_type() && n->type_id == int_type() && isArray==1 && first_element==0)
              report_error("Error at line number: %d - wide character array initialized from non-wide string",n->line_number);

              //i.e. int v={"ciao"};
              if (p->list.head->type_id == str_type() && n->type_id == int_type() && isArray==0)
              report_warning("Warning at line number: %d - initialization makes integer from pointer without a cast",n->line_number);

              //i.e. float v={"ciao"}; float v[10]={"ciao"};
              if (p->list.head->type_id == str_type() && n->type_id == float_type() )
              report_error("Error at line number: %d - incompatible types when initializing type ‘float’ using type ‘char *’",n->line_number);

              //i.e. double v={"ciao"}; double v[10]={"ciao"};
              if (p->list.head->type_id == str_type() && n->type_id == double_type() )
              report_error("Error at line number: %d - incompatible types when initializing type 'double' using type ‘char *’",n->line_number);

              if (p->list.head->type_id == str_type() && n->type_id != char_type() && scope_level==0)
              report_error("Error at line number: %d - initializer element is not computable at load time",n->line_number);

              //i.e.   char vec[10][10]={0,1,2,"c",3.5,'c'};
              if (p->list.head->type_id == str_type() && (n->type_id == char_type() || n->type_id == int_type()) && scope_level==0 && first_element>0)
              report_error("Error at line number: %d - initializer element is not computable at load time",n->line_number);

              //i.e char c[10]={"ciao",1}
              if(ArrayDim == 1 && string_count>0 && first_element!=0)
              report_error("Error at line number: %d - excess elements in char initializer",n->line_number);

              first_element++;
          }
          //control for number of element in the list with respect to the array/var dimension (for var last_ArrayDimension = 1)
          //i.e. char v={'a', 'a'};
          if (i > multi_array_dim && isArray==0)
          report_error("Error at line number: %d - excess elements in scalar initializer",n->line_number); //Warning in GCC! (Report as error to preserve correct translation !)

          if (i > multi_array_dim && isArray==1)
          report_warning("Warning at line number: %d - excess elements in array initializer",n->line_number);
        }

        else // init with assignment
        {
            if(n->type_id == int_type()) //int case
            {
              //i.e. int ciao = "ciao";
              if(n->dec.init->type_id == str_type() && isArray == 0)
              report_warning("Warning at line number: %d - initialization makes integer from pointer without a cast",n->line_number);

              //i.e. int ciao[4]="hi";
              if(n->dec.init->type_id == str_type() && isArray == 1)
              report_error("Error at line number: %d - wide character array initialized from non-wide string",n->line_number);

              if (n->dec.init->type_id== str_type() && scope_level==0)
              report_error("Error at line number: %d - initializer element is not computable at load time",n->line_number);

              //i.e. void ciao(){}; int main(){int a = ciao();}
              if(n->dec.init->type_id == void_type() && isArray == 0)
              report_error("Error at line number: %d - void value not ignored as it ought to be",n->line_number);

              //i.e. void ciao(){}; int main(){int a[10] = ciao();}
              if(n->dec.init->type_id == void_type() && isArray == 1)
              report_error("Error at line number: %d - invalid initializer",n->line_number);

            }
            else if(n->type_id == float_type() ) //float case
            {
              //i.e. float ciao = "ciao";
              if (n->dec.init->type_id== str_type() && isArray == 0)
              report_error("Error at line number: %d - incompatible types when initializing type ‘float’ using type ‘char *’",n->line_number);

              //i.e. void ciao(){}; int main(){float a = ciao();}
              if(n->dec.init->type_id== void_type() && isArray == 0)
              report_error("Error at line number: %d - void value not ignored as it ought to be",n->line_number);

              //i.e. void ciao(){}; int main(){float a[10] = ciao();}
              if(n->dec.init->type_id==void_type() && isArray == 1)
              report_error("Error at line number: %d - invalid initializer",n->line_number);
            }

            else if(n->type_id == double_type() ) // double case
            {
              //i.e. double ciao = "ciao";
              if (n->dec.init->type_id== str_type() && isArray ==0)
              report_error("Error at line number: %d - incompatible types when initializing type 'double' using type ‘char *’",n->line_number);

              //i.e. void ciao(){}; int main(){double a = ciao();}
              if(n->dec.init->type_id==void_type() && isArray == 0)
              report_error("Error at line number: %d - void value not ignored as it ought to be",n->line_number);

              //i.e. void ciao(){}; int main(){double a[10] = ciao();}
              if(n->dec.init->type_id==void_type() && isArray == 1)
              report_error("Error at line number: %d - invalid initializer",n->line_number);
            }

            else if(n->type_id == char_type()) // char case
            {
              //i.e. char c = 0.15858e5858;
              if( (n->dec.init->type_id == float_type() || n->dec.init->type_id == double_type()) && e_present_flag==1 )
              report_warning("Warning at line number: %d - overflow in implicit constant conversion",n->line_number);

              //i.e. char c = "stringa";
              if(n->dec.init->type_id == str_type() && ArrayDim==0 )
              report_warning("Warning at line number: %d - initialization makes integer from pointer without a cast",n->line_number);

              //i.e. char c[5] = "stringa"; check string length
              if(n->dec.init->type_id == str_type() && ArrayDim==1 && str_len>last_ArrayDimension)
              report_warning("Warning at line number: %d - initializer-string for array of chars is too long",n->line_number,str_len,last_ArrayDimension);

              //i.e.  char s= "ciao"; in scope level 0
              if (n->dec.init->type_id==str_type() && isArray==0 && scope_level==0)
              report_error("Error at line number: %d - initializer element is not computable at load time",n->line_number);

              // void check
              //i.e. void ciao(){}; int main(){char a = ciao();}
              if(n->dec.init->type_id==void_type() && isArray == 0)
              report_error("Error at line number: %d - void value not ignored as it ought to be",n->line_number);

              //i.e. void ciao(){}; int main(){char a[10] = ciao();}
              if(n->dec.init->type_id==void_type() && isArray == 1)
              report_error("Error at line number: %d - invalid initializer",n->line_number);
            }

            //if the Array is type (non char) it can be initialized like this: int v[1][1]= 0;
            //if the Array is  char vector with number of dimension > 1 it can't be initialized
            if( (n->type_id != char_type() && isArray == 1) || (n->type_id == char_type() && ArrayDim > 1) || (n->dec.init->type_id!=str_type() && n->type_id == char_type()  && isArray==1) )
            report_error("Error at line number: %d - invalid initializer",n->line_number);
        }
    }
    is_dec = 0;
    ArrayDim=0;
    str_len = 0;
    isId_init = 0;
    isArray = 0;
}


static void check_subvar_id(ast_node *n)
{
  if(n->subvar_id.index->type != AST_CONST)
  is_subvar_id = 1;

  isArray = 1;
  tree_ArrayDim_subvar++;
  check_ast(n->subvar_id.index);
  check_ast(n->subvar_id.var);
  n->type_id = n->subvar_id.var->type_id; // propagates real type up for declaration
  int index_type_id = n->subvar_id.index->type_id;

  if(scope_level == 0 && is_subvar_id == 1)
  {
    report_error("Error at line number: %d - variable modified ‘%s’ at file scope",n->line_number, var_name);
  }

  if( index_type_id != int_type() && index_type_id != char_type() )
  {
    report_error("Error at line number: %d - size of array '%s' has non-integer type",n->line_number, var_name);
  }

  if( isNegative == 1 )
  {
    report_error("Error at line number: %d - size of array ‘%s’ is negative",n->line_number,var_name);
  }

}


static void check_var(ast_node *n)
{
  // checks if var has been initiialized
  struct var_node* vn = find_record_scope_varST(n->var.sym_name, scope_level, stack_sub_scope_index, n->line_number);
  if(vn==NULL)
  report_error("Error at line number: %d - '%s' undeclared (first use in this function)",n->line_number ,n->var.sym_name);

  ArrayDim = count_dimension_array_parST(vn->id);
  n->type_id = vn->typeid;
  strcpy(var_name,vn->identifier);
  ArrayDim = count_dimension_array_parST(vn->id);
  last_ArrayDimension = retrieve_last_dimension_array_parST(vn->id);
  multi_array_dim = retrieve_multiply_dimension_array_parST(vn->id);

  // dimensionality check
  if(tree_ArrayDim_subvar > ArrayDim)
  {
    report_error("Error at line number: %d - subscripted value is neither array nor pointer nor vector",n->line_number);
  }
  if(tree_ArrayDim_subvar < ArrayDim && isBinop == 0  && is_printf_address == 0)
  {
    report_warning("Warning at line number: %d - initialization makes integer from pointer without a cast",n->line_number);
    error_flag_Id++;
  }
  tree_ArrayDim_subvar = 0;
}


static void check_funcdef(ast_node *n)
{
  last_function_ret_type = n->funcdef.ret_type;

  scope_level = aux_last_scope_level + 1;
  aux_last_scope_level = scope_level;

  sub_scope_level = 0;
  stack_sub_scope_index = 0;
  stack_sub_scope[stack_sub_scope_index] = 0;

  check_ast(n->funcdef.funchead);
  check_ast(n->funcdef.funcbody);

  scope_level = 0;
}


static void check_funchead(ast_node *n)
{
  check_ast(n->funchead.paras);
}


static void check_para(ast_node *n)
{
  check_ast(n->para.var);
}


static void check_compound_stmt(ast_node *n)
{
    sub_scope_level++;
    stack_sub_scope_index++;
    stack_sub_scope[stack_sub_scope_index] = sub_scope_level;

    check_ast(n->compound_stmt.defs);
    check_ast(n->compound_stmt.stmts);

    stack_sub_scope_index--;
}


static void check_expr_stmt(ast_node *n)
{
    check_ast(n->expr_stmt.expr);

    n->type_id = n->expr_stmt.expr->type_id;
    n->lvalue = n->expr_stmt.expr->lvalue;
}


static void check_if_stmt(ast_node *n)
{
    check_ast(n->if_stmt.cond);

    // condition type can't be void
    if (n->if_stmt.cond->type_id == void_type())
    report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);

    check_ast(n->if_stmt.then);
    check_ast(n->if_stmt.els);
}



static void check_for_stmt(ast_node *n)
{
  check_ast(n->for_stmt.init);

  if (n->for_stmt.cond)
  {
      check_ast(n->for_stmt.cond);

      // contition of FOR can't be void
      if (n->for_stmt.cond->type_id == void_type())
      report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
  }

  check_ast(n->for_stmt.incr);

  loop_level++;
  check_ast(n->for_stmt.body);
  loop_level--;
}


static void check_printf_stmt(ast_node *n)
{
  is_printf_address = 0;

  if (n->printf_stmt.address == 1 || (strstr(n->printf_stmt.init,"%p")!=NULL))
  is_printf_address = 1;

  if (n->printf_stmt.var) // case pritnf with var
  {
    check_ast(n->printf_stmt.var);
    n->type_id = n->printf_stmt.var -> type_id;

    //Checking the format specifier
    int flag = 0;
    char * f ="%f";
    char * d ="%d";
    char * c ="%c";
    char * p ="%p";
    char * lf = "%lf";

    if (n->printf_stmt.address == 0 ) // without '&'
    {

      //typing checks
      if (n->type_id==void_type())
      {
        report_error("Error at line number: %d - invalid use of void expression",n->line_number);
      }

      if (  n->type_id == int_type()) //var is int type
      {

        if (strstr(n->printf_stmt.init,"%d")!=NULL)
              {
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%f")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘double’, but argument 2 has type ‘int’",n->line_number, f);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%c")!=NULL)
              {
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%p")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘void *’, but argument 2 has type ‘int’",n->line_number,p);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%lf")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘double’, but argument 2 has type ‘int’",n->line_number, lf);
                flag++;
              }

        if (flag == 0) report_warning("Warning at line number: %d - format specifier absent",n->line_number);

      }

      if (  n->type_id == char_type()) //var is char type
      {

        if (strstr(n->printf_stmt.init,"%d")!=NULL)
              {
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%f")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘double’, but argument 2 has type ‘int’",n->line_number, f);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%c")!=NULL)
              {
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%p")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘void *’, but argument 2 has type ‘int’",n->line_number,p);
                flag++;
              }

        if (strstr(n->printf_stmt.init,"%lf")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘double’, but argument 2 has type ‘int’",n->line_number, lf);
                flag++;
              }

        if (flag == 0) report_warning("Warning at line number: %d - format specifier absent",n->line_number);

      }

      if (  n->type_id == float_type() || n->type_id == double_type() ) //var is float or double type
      {

        if (strstr(n->printf_stmt.init,"%d")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int’, but argument 2 has type ‘double’",n->line_number,d);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%f")!=NULL)
              {
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%c")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int’, but argument 2 has type ‘double’",n->line_number,c);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%p")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘void *’, but argument 2 has type ‘double’",n->line_number,p);
                flag++;
              }

        if (strstr(n->printf_stmt.init,"%lf")!=NULL)
              {
                flag++;
              }

        if (flag == 0) report_warning("Warning at line number: %d - format specifier absent",n->line_number);

      }
    }
    else //printf is printing an address with '&'
    {
      if(n->printf_stmt.var->type==AST_FUNC_CALL)
      isFunc_call_lvalue = 1;

      if( isFunc_call_lvalue == 1)
      {
        if(n->type_id == void_type() )
        {
        report_warning("Warning at line number: %d - taking address of expression of type ‘void’",n->line_number);
        }
        report_error("Error at line number: %d - lvalue required as unary ‘&’ operand",n->line_number);
      }

      if (n->printf_stmt.var->type!=AST_BINOP) //if is not a binop, brackets it's OK i.e scanf("%d", &(i) );
      n->is_brackets=0;

      if(n->is_brackets == 1 )
      report_error("Error at line number: %d - lvalue required as unary ‘&’ operand",n->line_number);

      n->lvalue = n->printf_stmt.var -> lvalue;
      if(n->lvalue==2 || n->lvalue==3)
      report_warning("Warning at line number: %d - comparison between pointer and another type",n->line_number);

      if(n->lvalue==1)
      report_error("Error at line number: %d - lvalue required as unary ‘&’ operand %d",n->line_number,n->lvalue);

      // typing checks
      if (  n->type_id == int_type()) //var is int type
      {

        if (strstr(n->printf_stmt.init,"%d")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int’, but argument 2 has type ‘int *’",n->line_number,d);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%f")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘double’, but argument 2 has type ‘int *’",n->line_number, f);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%c")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int’, but argument 2 has type ‘int *’",n->line_number,c);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%p")!=NULL)
              {
                flag++;
              }

        if (strstr(n->printf_stmt.init,"%lf")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘double’, but argument 2 has type ‘int *’",n->line_number, lf);
                flag++;
              }

         if (flag == 0) report_warning("Warning at line number: %d - format specifier absent",n->line_number);
      }

      if (  n->type_id == char_type()) //var is char type
      {

        if (strstr(n->printf_stmt.init,"%d")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int’, but argument 2 has type ‘char *’",n->line_number,d);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%f")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘double’, but argument 2 has type ‘char *’",n->line_number, f);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%c")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int’, but argument 2 has type ‘char *’",n->line_number,c);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%p")!=NULL)
              {
                flag++;
              }

        if (strstr(n->printf_stmt.init,"%lf")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘double’, but argument 2 has type ‘char *’",n->line_number, lf);
                flag++;
              }

         if (flag == 0) report_warning("Warning at line number: %d - format specifier absent",n->line_number);
      }

      if (  n->type_id == float_type() ) //var is float type
      {

        if (strstr(n->printf_stmt.init,"%d")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int’, but argument 2 has type ‘float *’",n->line_number,d);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%f")!=NULL)
              {
                report_warning("Warning at line number: %d -  format ‘%s’ expects argument of type ‘double’, but argument 2 has type ‘float *’",n->line_number, f);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%c")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int’, but argument 2 has type ‘float *’",n->line_number,c);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%p")!=NULL)
              {
                flag++;
              }

        if (strstr(n->printf_stmt.init,"%lf")!=NULL)
              {
                report_warning("Warning at line number: %d -  format ‘%s’ expects argument of type ‘double’, but argument 2 has type ‘float *’",n->line_number, lf);
                flag++;
              }

         if (flag == 0) report_warning("Warning at line number: %d - format specifier absent",n->line_number);
      }

      if (  n->type_id == double_type() ) //var is double type
      {

        if (strstr(n->printf_stmt.init,"%d")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int’, but argument 2 has type ‘double *’",n->line_number,d);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%f")!=NULL)
              {
                report_warning("Warning at line number: %d -  format ‘%s’ expects argument of type ‘double’, but argument 2 has type ‘double *’",n->line_number, f);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%c")!=NULL)
              {
                report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int’, but argument 2 has type ‘double *’",n->line_number,c);
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%p")!=NULL)
              {
                flag++;
              }
        if (strstr(n->printf_stmt.init,"%lf")!=NULL)
              {
                report_warning("Warning at line number: %d -  format ‘%s’ expects argument of type ‘double’, but argument 2 has type ‘double *’",n->line_number, f);
                flag++;
              }

         if (flag == 0) report_warning("Warning at line number: %d - format specifier absent",n->line_number);
      }

    }

  }

  isFunc_call_lvalue = 0;
}


static void check_scanf_stmt(ast_node *n)
{
  check_ast(n->scanf_stmt.var);
  n->type_id = n->scanf_stmt.var -> type_id;

  if (n->scanf_stmt.var->type==AST_FUNC_CALL) //if is not a binop, brackets OK i.e scanf("%d", &(i) );
  isFunc_call_lvalue = 1;

  // function scanf stmt generates error l value
  if( isFunc_call_lvalue == 1)
  {
    if(n->type_id == void_type() )
    {
    report_warning("Warning at line number: %d - taking address of expression of type ‘void’",n->line_number);
    }

    report_error("Error at line number: %d - lvalue required as unary ‘&’ operand",n->line_number);
  }

  if (n->scanf_stmt.var->type != AST_BINOP) //if is not a binop, brackets OK i.e scanf("%d", &(i) );
  n->is_brackets=0;

  if(n->is_brackets == 1 )
  report_error("Error at line number: %d - lvalue required as unary ‘&’ operand",n->line_number);

  n->lvalue = n->scanf_stmt.var -> lvalue;
  if(n->lvalue==2 || n->lvalue==4)
  report_warning("Warning at line number: %d - comparison between pointer and another type",n->line_number);

  if(n->lvalue==1 )
  report_error("Error at line number: %d - lvalue required as unary ‘&’ operand",n->line_number);

  //Checking the format specifier ("%d")
  int flag = 0;
  char * f ="%f";
  char * d ="%d";
  char * c ="%c";
  char * p ="%p";
  char * lf ="%lf";

  if (  n->type_id == int_type()) //var is int type
  {

    if (strstr(n->scanf_stmt.init,"%d")!=NULL)
          {
            flag++;
          }
    if (strstr(n->scanf_stmt.init,"%f")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘float *’, but argument 2 has type ‘int *’",n->line_number, f);
            flag++;
          }
    if (strstr(n->scanf_stmt.init,"%c")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘int *’",n->line_number,c);
            flag++;
          }
    if (strstr(n->scanf_stmt.init,"%p")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘void **’, but argument 2 has type ‘int’",n->line_number,p);
            flag++;
          }

    if (strstr(n->scanf_stmt.init,"%lf")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘float *’, but argument 2 has type ‘int *’",n->line_number, lf);
            flag++;
          }

     if (flag == 0) report_warning("Warning at line number: %d - format specifier absent",n->line_number);

  }

  if (  n->type_id == char_type()) //var is char type
  {

    if (strstr(n->scanf_stmt.init,"%d")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int *’, but argument 2 has type ‘char *’",n->line_number,d);
            flag++;
          }
    if (strstr(n->scanf_stmt.init,"%f")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘float *’, but argument 2 has type ‘char *’",n->line_number, f);
            flag++;
          }
    if (strstr(n->scanf_stmt.init,"%c")!=NULL)
          {
            flag++;
          }
    if (strstr(n->scanf_stmt.init,"%p")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘void **’, but argument 2 has type ‘int’",n->line_number,p);
            flag++;
          }

    if (strstr(n->scanf_stmt.init,"%lf")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘float *’, but argument 2 has type ‘char *’",n->line_number, lf);
            flag++;
          }

     if (flag == 0) report_warning("Warning at line number: %d - format specifier absent",n->line_number);

  }

  if (  n->type_id == float_type() ) //var is float type
  {

    if (strstr(n->scanf_stmt.init,"%d")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int *’, but argument 2 has type ‘double *’",n->line_number,d);
            flag++;
          }
    if (strstr(n->scanf_stmt.init,"%f")!=NULL)
          {
            flag++;
          }
    if (strstr(n->scanf_stmt.init,"%c")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘double *’",n->line_number,c);
            flag++;
          }
    if (strstr(n->scanf_stmt.init,"%p")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘void **’, but argument 2 has type ‘int’",n->line_number,p);
            flag++;
          }

    if (strstr(n->scanf_stmt.init,"%lf")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘double *’, but argument 2 has type ‘float *’",n->line_number, lf);
            flag++;
          }

     if (flag == 0) report_warning("Warning at line number: %d - format specifier absent",n->line_number);
  }


  if (  n->type_id == double_type() ) //var is double type
  {

    if (strstr(n->scanf_stmt.init,"%d")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘int *’, but argument 2 has type ‘double *’",n->line_number,d);
            flag++;
          }
    if (strstr(n->scanf_stmt.init,"%f")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘float *’, but argument 2 has type ‘double *’",n->line_number, f);
            flag++;
          }
    if (strstr(n->scanf_stmt.init,"%c")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘double *’",n->line_number,c);
            flag++;
          }
    if (strstr(n->scanf_stmt.init,"%p")!=NULL)
          {
            report_warning("Warning at line number: %d - format ‘%s’ expects argument of type ‘void **’, but argument 2 has type ‘int’",n->line_number,p);
            flag++;
          }

    if (strstr(n->scanf_stmt.init,"%lf")!=NULL)
          {
            flag++;
          }

     if (flag == 0) report_warning("Warning at line number: %d - format specifier absent",n->line_number);
  }

  isFunc_call_lvalue = 0;

}


static void check_continue_stmt(ast_node *n)
{
    if (loop_level > 0)
    {
    }
    else report_error("Error at line number: %d - continue statement not within a loop", n->line_number);
}

static void check_break_stmt(ast_node *n)
{
    if (loop_level > 0)
    {
    }
    else report_error("Error at line number: %d - break statement not within loop or switch", n->line_number);
}


static void check_return_stmt(ast_node *n)
{
  error_flag_Id = 0;

  if (n->return_stmt.isReturn_var == 1)
  {
    check_ast(n->return_stmt.retval);
    n->type_id = n->return_stmt.retval->type_id;
  }
  else n->type_id = -1; // return with no value

  if (last_function_ret_type == void_type() && n->type_id != -1)
  {
    report_warning("Warning at line number: %d - ‘return’ with a value, in function returning void",n->line_number);
  }
  else if(last_function_ret_type != void_type() && n->type_id == -1)
  {
    report_warning("Warning at line number: %d - ‘return’ with no value, in function returning non-void",n->line_number);
  }
  else if(error_flag_Id != 0)
  {
    report_error("Error at line number: %d - incompatible types with returning type",n->line_number); //GCC more detailed on return type error
  }

  error_flag_Id = 0;
}


int binop_lv = 0;
static void check_binop(ast_node *n)
{
  binop_lv++;
  isBinop = 1;
  int op_error = 0; //If an error with the operator occours, ignore typing checks on Binop
  check_ast(n->binop.lhs);
  check_ast(n->binop.rhs);

  switch (n->binop.op)
  {
  case GE_OP:
      if( (n->binop.lhs->type_id == int_type() || n->binop.lhs->type_id == char_type() )  && n->binop.rhs->type_id == str_type())
      {
        report_warning("Warning at line number: %d -  comparison between pointer and integer", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == float_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary >= (have ‘float’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == double_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary >= (have ‘double’ and ‘char *’)", n->line_number);
        op_error++;
      }

      //reverse
      if( (n->binop.rhs->type_id == int_type() || n->binop.rhs->type_id == char_type() )  && n->binop.lhs->type_id == str_type())
      {
        report_warning("Warning at line number: %d -  comparison between pointer and integer", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == float_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary >= (have ‘char *’ and ‘float’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == double_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary >= (have ‘char *’ and ‘double’)", n->line_number);
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case LE_OP:
      if( (n->binop.lhs->type_id == int_type() || n->binop.lhs->type_id == char_type() )  && n->binop.rhs->type_id == str_type())
      {
        report_warning("Warning at line number: %d -  comparison between pointer and integer", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == float_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary <= (have ‘float’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == double_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary <= (have ‘double’ and ‘char *’)", n->line_number);
        op_error++;
      }

      //reverse
      if( (n->binop.rhs->type_id == int_type() || n->binop.rhs->type_id == char_type() )  && n->binop.lhs->type_id == str_type())
      {
        report_warning("Warning at line number: %d -  comparison between pointer and integer", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == float_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary <= (have ‘char *’ and ‘float’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == double_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary <= (have ‘char *’ and ‘double’)", n->line_number);
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case EQ_OP:
      if( (n->binop.lhs->type_id == int_type() || n->binop.lhs->type_id == char_type() )  && n->binop.rhs->type_id == str_type())
      {
        report_warning("Warning at line number: %d -  comparison between pointer and integer", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == float_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary == (have ‘float’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == double_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary == (have ‘double’ and ‘char *’)", n->line_number);
        op_error++;
      }

      //reverse
      if( (n->binop.rhs->type_id == int_type() || n->binop.rhs->type_id == char_type() )  && n->binop.lhs->type_id == str_type())
      {
        report_warning("Warning at line number: %d -  comparison between pointer and integer", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == float_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary == (have ‘char *’ and ‘float’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == double_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary == (have ‘char *’ and ‘double’)", n->line_number);
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case NE_OP:
      if( (n->binop.lhs->type_id == int_type() || n->binop.lhs->type_id == char_type() )  && n->binop.rhs->type_id == str_type())
      {
        report_warning("Warning at line number: %d -  comparison between pointer and integer", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == float_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary != (have ‘float’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == double_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary != (have ‘double’ and ‘char *’)", n->line_number);
        op_error++;
      }

      //reverse
      if( (n->binop.rhs->type_id == int_type() || n->binop.rhs->type_id == char_type() )  && n->binop.lhs->type_id == str_type())
      {
        report_warning("Warning at line number: %d -  comparison between pointer and integer", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == float_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary != (have ‘char *’ and ‘float’)", n->line_number);
        op_error++;
      }
      if(n->binop.rhs->type_id == double_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary != (have ‘char *’ and ‘double’)", n->line_number);
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case AND_OP:
      {
        op_error++;
      }

      //check void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case OR_OP:
      {
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case '+':
      if(n->binop.lhs->type_id == float_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary + (have ‘float’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == double_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary + (have ‘double’ and ‘char *’)", n->line_number);
        op_error++;
      }

      //reverse
      if(n->binop.rhs->type_id == float_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary + (have ‘char *’ and ‘float’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == double_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary + (have ‘char *’ and ‘double’)", n->line_number);
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case '-':
      if(n->binop.lhs->type_id == float_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary - (have ‘float’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == double_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary - (have ‘double’ and ‘char *’)", n->line_number);
        op_error++;
      }

      //reverse
      if(n->binop.rhs->type_id == float_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary - (have ‘char *’ and ‘float’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == double_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary - (have ‘char *’ and ‘double’)", n->line_number);
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case '*':
      if( (n->binop.lhs->type_id == int_type() || n->binop.lhs->type_id == char_type() )  && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d -  invalid operands to binary * (have ‘int’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == float_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary * (have ‘float’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == double_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary * (have ‘double’ and ‘char *’)", n->line_number);
        op_error++;
      }

      //reverse
      if( (n->binop.rhs->type_id == int_type() || n->binop.rhs->type_id == char_type() )  && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d -  invalid operands to binary * (have ‘char *’ and ‘int’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == float_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary * (have ‘char*’ and ‘float’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == double_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary * (have ‘char *’ and ‘double’)", n->line_number);
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case '/':
      if (isZero != 0)
      {
        report_warning("Warning at line number: %d - division by zero", n->line_number);
        op_error++;
      }

      if( (n->binop.lhs->type_id == int_type() || n->binop.lhs->type_id == char_type() )  && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d -  invalid operands to binary / (have ‘int’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == float_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary / (have ‘float’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == double_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary / (have ‘double’ and ‘char *’)", n->line_number);
        op_error++;
      }

      //reverse
      if( (n->binop.rhs->type_id == int_type() || n->binop.rhs->type_id == char_type() )  && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary / (have ‘char *’ and ‘int’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == float_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary / (have ‘char*’ and ‘float’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == double_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary / (have ‘char *’ and ‘double’)", n->line_number);
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case '%':
      // % works only with int types
      if( (n->binop.lhs->type_id == int_type() || n->binop.lhs->type_id == char_type() )  && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d -  invalid operands to binary % (have ‘int’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if( (n->binop.lhs->type_id == int_type() || n->binop.lhs->type_id == char_type()) && n->binop.rhs->type_id == float_type() )
      {
        report_error("Error at line number: %d - invalid operands to binary % (have ‘int’ and 'float')", n->line_number);
        op_error++;
      }

      if( (n->binop.lhs->type_id == int_type() || n->binop.lhs->type_id == char_type())  && n->binop.rhs->type_id == double_type() )
      {
        report_error("Error at line number: %d - invalid operands to binary % (have ‘int’ and 'double')", n->line_number);
        op_error++;
      }

      //reverse
      if( (n->binop.rhs->type_id == int_type() || n->binop.rhs->type_id == char_type() )  && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary % (have ‘char *’ and ‘int’)", n->line_number);
        op_error++;
      }

      if( (n->binop.rhs->type_id == int_type() || n->binop.rhs->type_id == char_type()) && n->binop.lhs->type_id == float_type() )
      {
        report_error("Error at line number: %d - invalid operands to binary % (have ‘float’ and 'int')", n->line_number);
        op_error++;
      }

      if( (n->binop.rhs->type_id == int_type() || n->binop.rhs->type_id == char_type())  && n->binop.lhs->type_id == double_type() )
      {
        report_error("Error at line number: %d - invalid operands to binary % (have ‘double’ and 'int')", n->line_number);
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case '&':
      if( (n->binop.lhs->type_id == int_type() || n->binop.lhs->type_id == char_type() )  && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d -  invalid operands to binary & (have ‘int’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == float_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary & (have ‘float’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == double_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary & (have ‘double’ and ‘char *’)", n->line_number);
        op_error++;
      }

      //reverse
      if( (n->binop.rhs->type_id == int_type() || n->binop.rhs->type_id == char_type() )  && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d -  invalid operands to binary & (have ‘char *’ and ‘int’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == float_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary & (have ‘char*’ and ‘float’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == double_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary & (have ‘char *’ and ‘double’)", n->line_number);
        op_error++;
      }

      //Bit AND specific error
      if(n->binop.rhs->type_id == double_type() && n->binop.lhs->type_id == double_type())
      {
        report_error("Error at line number: %d - invalid operands to binary & (have ‘double’ and ‘double’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == float_type() && n->binop.lhs->type_id == float_type())
      {
        report_error("Error at line number: %d - invalid operands to binary & (have ‘float’ and ‘float’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == str_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary & (have ‘char *’ and ‘char *’)", n->line_number);
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case '>':
      if( (n->binop.lhs->type_id == int_type() || n->binop.lhs->type_id == char_type() )  && n->binop.rhs->type_id == str_type())
      {
        report_warning("Warning at line number: %d -  comparison between pointer and integer", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == float_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary > (have ‘float’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == double_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary > (have ‘double’ and ‘char *’)", n->line_number);
        op_error++;
      }

      //reverse
      if( (n->binop.rhs->type_id == int_type() || n->binop.rhs->type_id == char_type() )  && n->binop.lhs->type_id == str_type())
      {
        report_warning("Warning at line number: %d -  comparison between pointer and integer", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == float_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary > (have ‘char*’ and ‘float’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == double_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary > (have ‘char *’ and ‘double’)", n->line_number);
        op_error++;
      }
      break;

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case '<':
      if( (n->binop.lhs->type_id == int_type() || n->binop.lhs->type_id == char_type() )  && n->binop.rhs->type_id == str_type())
      {
        report_warning("Warning at line number: %d -  comparison between pointer and integer", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == float_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary < (have ‘float’ and ‘char *’)", n->line_number);
        op_error++;
      }

      if(n->binop.lhs->type_id == double_type() && n->binop.rhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary < (have ‘double’ and ‘char *’)", n->line_number);
        op_error++;
      }

      //reverse
      if( (n->binop.rhs->type_id == int_type() || n->binop.rhs->type_id == char_type() )  && n->binop.lhs->type_id == str_type())
      {
        report_warning("Warning at line number: %d -  comparison between pointer and integer", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == float_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary < (have ‘char*’ and ‘float’)", n->line_number);
        op_error++;
      }

      if(n->binop.rhs->type_id == double_type() && n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - invalid operands to binary < (have ‘char *’ and ‘double’)", n->line_number);
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type() ||n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      break;

  case '=':
      if(n->binop.rhs->type_id == str_type() || n->binop.lhs->type_id == str_type())
      {
        report_error("Error at line number: %d - assignment to expression with array type", n->line_number);
        op_error++;
      }

      //checks void func
      if(n->binop.rhs->type_id == void_type())
      {
        report_error("Error at line number: %d - void value not ignored as it ought to be", n->line_number);
        op_error++;
      }
      if(n->binop.lhs->type_id == void_type())
      {
        report_error("Error at line number: %d - invalid use of void expression", n->line_number);
        op_error++;
      }

      // left operator can't be a function
      if(n->binop.lhs->lvalue == 0 ||  n->binop.lhs->type == AST_FUNC_CALL)
      report_error("Error at line number: %d - lvalue required as left operand of assignment", n->line_number);
      break;

  default:
      {
        report_error("Unkonwn operator!");
      }
      break;
  }

  if(op_error == 0)
    {
        //if left side is an int (with reverse)
        if (n->binop.lhs->type_id == int_type() || n->binop.rhs->type_id == int_type() )
        {
          if(n->binop.rhs->type_id == str_type() || n->binop.lhs->type_id == str_type())
          report_warning("Warning at line number: %d - assignment makes integer from pointer without a cast", n->line_number);

          if( (n->binop.rhs->type_id == float_type() || n->binop.rhs->type_id == double_type()) && e_present_flag!=0)
          report_warning("Warning at line number: %d - overflow in implicit constant conversion", n->line_number);

          if( (n->binop.lhs->type_id == float_type() || n->binop.lhs->type_id == double_type()) && e_present_flag!=0)
          report_warning("Warning at line number: %d - overflow in implicit constant conversion", n->line_number);
        }

        //if left side is a float
        if (n->binop.lhs->type_id == float_type() )
        {
          if(n->binop.rhs->type_id == str_type())
          report_error("Error at line number: %d - incompatible types when assigning to type ‘float’ from type ‘char *’", n->line_number);
        }

        //reverse
        if (n->binop.rhs->type_id == float_type() )
        {
          if(n->binop.lhs->type_id == str_type())
          report_error("Error at line number: %d - incompatible types when assigning to type ‘char *’ from type ‘float’", n->line_number);
        }

        //if left side is a double
        if (n->binop.lhs->type_id == double_type())
        {
          if(n->binop.rhs->type_id == str_type())
          report_error("Error at line number: %d - incompatible types when assigning to type ‘double’ from type ‘char *’", n->line_number);
        }

        //reverse
        if (n->binop.rhs->type_id == double_type())
        {
          if(n->binop.lhs->type_id == str_type())
          report_error("Error at line number: %d - incompatible types when assigning to type ‘char *’ from type ‘double’", n->line_number);
        }

        //if left side is a char (with reverse)
        if (n->binop.lhs->type_id == char_type() || n->binop.rhs->type_id == char_type())
        {
          if( (n->binop.rhs->type_id == float_type() || n->binop.rhs->type_id == double_type() || n->binop.lhs->type_id == float_type() || n->binop.lhs->type_id == double_type() ) && e_present_flag!=0)
          report_warning("Warning at line number: %d - overflow in implicit constant conversion", n->line_number);

          if(n->binop.rhs->type_id == str_type() || n->binop.lhs->type_id == str_type())
          report_warning("Warning at line number: %d - assignment makes integer from pointer without a cast", n->line_number);
        }
    }

  n->type_id = n->binop.rhs->type_id;
  n->lvalue = binary_operator_case(n->binop.op);

  binop_lv--;
  e_present_flag = 0;
  isZero = 0;
  op_error = 0;

  if (binop_lv == 0)
  isBinop = 0;
}

static void check_prefix(ast_node *n)
{
  if(n->prefix.op == '-')
  {
    isNegative = 1 ;
  }

  if((n->prefix.unary->type == AST_CONST || n->prefix.unary->type == AST_CONST_C || n->prefix.unary->type == AST_CONST_F || n->prefix.unary->type == AST_CONST_STR  || n->prefix.unary->type == AST_FUNC_CALL ) && n->prefix.op == INC_OP)
  report_error("Error at line number: %d - lvalue required as increment operand", n->line_number);

  if((n->prefix.unary->type == AST_CONST || n->prefix.unary->type == AST_CONST_C || n->prefix.unary->type == AST_CONST_F || n->prefix.unary->type == AST_CONST_STR || n->prefix.unary->type == AST_FUNC_CALL ) && n->prefix.op == DEC_OP)
  report_error("Error at line number: %d - lvalue required as decrement operand", n->line_number);

  check_ast(n->prefix.unary);

  n->type_id = n->prefix.unary->type_id;
  n->lvalue = 1;
}

static void check_postfix(ast_node *n)
{
  if((n->postfix.unary->type == AST_CONST || n->postfix.unary->type == AST_CONST_C || n->postfix.unary->type == AST_CONST_F || n->postfix.unary->type == AST_CONST_STR  || n->postfix.unary->type == AST_FUNC_CALL ) && n->postfix.op == INC_OP)
  report_error("Error at line number: %d - lvalue required as increment operand", n->line_number);

  if((n->postfix.unary->type == AST_CONST || n->postfix.unary->type == AST_CONST_C || n->postfix.unary->type == AST_CONST_F || n->postfix.unary->type == AST_CONST_STR || n->postfix.unary->type == AST_FUNC_CALL ) && n->postfix.op == DEC_OP)
  report_error("Error at line number: %d - lvalue required as decrement operand", n->line_number);

  check_ast(n->postfix.unary);
  n->type_id = n->postfix.unary->type_id;
  n->lvalue = 1;
}


static void check_indexing(ast_node *n)
{
    first_indexing = first_indexing + 1;

    tree_ArrayDim++;
    given_called_dimension++;

    check_ast(n->indexing.postfix);

    if(n->indexing.expr->type == AST_CONST_C || n->indexing.expr->type == AST_CONST_F || n->indexing.expr->type == AST_CONST_STR)
    report_error("Error at line number: %d - size of array has non-integer type", n->line_number);

    check_ast(n->indexing.expr);

    n->type_id=n->indexing.postfix->type_id;
    n->lvalue=n->indexing.postfix->lvalue;

    first_indexing = first_indexing -1;
}

static void check_func_call(ast_node *n)
{
  int error_flag_func_call = 0;
  isFunc_call = 1;
  isFunc_call_par = 1;
  given_called_dimension = 0;

  //Checks if the func has been declared in previous scopes
  struct funcdef_node * f_def = find_record_scope_funcdef_node_ST( n->func_call.postfix->id.sym_name,scope_level);
  if(f_def == NULL)
  report_error("Error at line number: %d - implicit declaration of function ‘%s’", n->line_number, n->func_call.postfix->id.sym_name);

  check_ast(n->func_call.postfix);
  n->type_id = n->func_call.postfix->type_id;
  n->lvalue = 1;
  n->func_call.postfix->lvalue = 0;
  isFunc_call = 0;

  // checks the argument number and types
  ast_node *p = n->func_call.args;
  for (int i = 0; i < f_def->parameter_num; ++i)
  {
      if (!p)
      {
          report_error("Error at line number: %d - too few arguments to function ‘%s’", n->line_number, n->func_call.postfix->id.sym_name);
      }

      //retrieves call parameter
      check_ast(p->list.head);
      int given_type = p->list.head->type_id;

      //retrieves declaration parameter
      struct func_par_node* par_node = find_record_par_node_ST(f_def->id, i);
      int expected_type = par_node->typeid;
      int expected_dimension = count_dimension_array_parST(par_node->var_id);

      //checks the coerence of the parameter with the declaration
      if( given_declareted_dimension != expected_dimension || given_called_dimension > 0)
      {
        report_warning("Warning at line number: %d -  passing argument %d of ‘%s’ from incompatible pointer type", n->line_number,i+1, n->func_call.postfix->id.sym_name);
        error_flag_func_call = 1;
      }

      //type's check
      if( expected_type == double_type() && given_type == float_type() && given_declareted_dimension == 0 && isArray == 0)
      {
        //cast from float to double is possible only for non array
      }
      else if( expected_type == char_type() && given_type == str_type() && expected_dimension == 1)
      {
        //passing a string to a char array is allowed
      }
      //if we use as calling par a cost string, it's like as it is an 1 dim array (of char)
      else if (given_type == str_type())
      {
        report_error("Error at line number: %d -  passing argument %d of ‘%s’ is string const", n->line_number,i+1, n->func_call.postfix->id.sym_name);
      }
      else if ( given_type != expected_type && isArray == 1 )
      {
        report_warning("Warning at line number: %d - passing argument %d of ‘%s’ from incompatible pointer type ", n->line_number,i+1, n->func_call.postfix->id.sym_name); //GCC more detailed
      }

      given_called_dimension = 0; // redundant (?)
      given_declareted_dimension = 0;
      isFunc_call_par = 0;
      isArray = 0;
      p = p->list.tail;
  }
  //more parameters than necessary
  if (p)
  {
    report_error("Error at line number: %d - too many arguments to function ‘%s’", n->line_number, n->func_call.postfix->id.sym_name);
  }
}

static void check_id(ast_node *n)
{
    int propagate_type_id;
    isId_init = 1;

    if (isFunc_call == 0) //check used to avoid if we are in a function call leaf
    {
      // check variables have been declared before usage
      struct var_node* vn = find_record_scope_varST(n->var.sym_name, scope_level, stack_sub_scope_index, n->line_number);
      if(vn == NULL)
      report_error("Error at line number: %d - variable '%s' undeclared",n->line_number ,n->var.sym_name);

      ArrayDim = count_dimension_array_parST(vn->id);
      given_declareted_dimension = ArrayDim;
      last_ArrayDimension = retrieve_last_dimension_array_parST(vn->id);

      if(strcmp(vn->typeName,"array") == 0)
      {
        isArray = 1;
      }

      if(tree_ArrayDim > ArrayDim)
      {
        report_error("Error at line number: %d - subscripted value is neither array nor pointer nor vector",n->line_number);
      }

      // init case i.e var[10]={v1} // int v1[10];
      if(tree_ArrayDim < ArrayDim && isBinop == 0 && isFunc_call_par == 0 && is_printf_address == 0 && is_dec==1)
      {
        report_error("Error at line number: %d - incompatible types when initializing type",n->line_number);
        error_flag_Id++;
      }

      if(tree_ArrayDim < ArrayDim && isBinop == 0 && isFunc_call_par == 0 && is_printf_address == 0)
      {
        report_warning("Warning at line number: %d - initialization makes integer from pointer without a cast",n->line_number);
        error_flag_Id++;
      }
      if(tree_ArrayDim < ArrayDim && isBinop == 1  && isFunc_call_par == 0)
      {
        report_error("Error at line number: %d - assignment to expression with array type",n->line_number);
      }

      propagate_type_id = vn->typeid;

    }
    else if (isFunc_call == 1)
    {
      struct funcdef_node* func_call_n = find_record_scope_funcdef_node_ST(n->var.sym_name, scope_level);
      if(func_call_n != NULL)
      {
        propagate_type_id = func_call_n->ret_typeid;
      }
    }
    n->type_id = propagate_type_id;
    ArrayDim = 0;
    tree_ArrayDim = 0;
}

static void check_const(ast_node *n)
{
    if(n->constant.number == 0 )
    {
      isZero = 1 ;
    }
    n->type_id = int_type();
    n->lvalue = 0;
}

static void check_const_f(ast_node *n)
{
    //Checks if the float/double number is present and there is a power of 10's (i.e float f= 55e1;)
    char *e_present = strchr(n->constant_f.number, 'e');
    if (e_present!=NULL)
    e_present_flag = 1;

    n->type_id = float_type(); //assuming float
    n->lvalue = 0;
}

static void check_const_c(ast_node *n)
{
    // counts char character: -2 for ' ' & != from special chars CAP ("\0")
    if(strlen(n->constant_c.char_value)-2 > 1  && strcmp(n->constant_c.char_value,"'\\0'")!= 0)
    report_warning("Warning at line number: %d - multi-character character constant", n->line_number);

    if(strlen(n->constant_c.char_value)-2 == 0 )
    report_error("Error at line number: %d - empty character constant", n->line_number);

    n->type_id = char_type();
    n->lvalue = 0;
}

static void check_const_str(ast_node *n)
{
    str_len = strlen(n->constant_str.string);
    str_len = str_len -2 ; //" " -> NOT to include in the count of chars
    n->type_id = str_type();
    n->lvalue = 0;
}


static void init_ast_checkers()
{
    if (g_ast_checkers[0]) return;
    g_ast_checkers[AST_LIST] = check_list;
    g_ast_checkers[AST_FUNCDEF] = check_funcdef;
    g_ast_checkers[AST_FUNCHEAD] = check_funchead;
    g_ast_checkers[AST_PARA] = check_para;
    g_ast_checkers[AST_VAR] = check_var;
    g_ast_checkers[AST_SUBVAR_ID] = check_subvar_id;
    g_ast_checkers[AST_COMPOUND_STMT] = check_compound_stmt;
    g_ast_checkers[AST_EXPR_STMT] = check_expr_stmt;
    g_ast_checkers[AST_IF_STMT] = check_if_stmt;
    g_ast_checkers[AST_FOR_STMT] = check_for_stmt;
    g_ast_checkers[AST_PRINTF_STMT] = check_printf_stmt;
    g_ast_checkers[AST_SCANF_STMT] = check_scanf_stmt;
    g_ast_checkers[AST_RETURN_STMT] = check_return_stmt;
    g_ast_checkers[AST_CONTINUE_STMT] = check_continue_stmt;
    g_ast_checkers[AST_BREAK_STMT] = check_break_stmt;
    g_ast_checkers[AST_DEF] = check_def;
    g_ast_checkers[AST_DEC] = check_dec;
    g_ast_checkers[AST_BINOP] = check_binop;
    g_ast_checkers[AST_PREFIX] = check_prefix;
    g_ast_checkers[AST_POSTFIX] = check_postfix;
    g_ast_checkers[AST_INDEXING] = check_indexing;
    g_ast_checkers[AST_FUNC_CALL] = check_func_call;
    g_ast_checkers[AST_ID] = check_id;
    g_ast_checkers[AST_CONST] = check_const;
    g_ast_checkers[AST_CONST_F] = check_const_f;
    g_ast_checkers[AST_CONST_C] = check_const_c;
    g_ast_checkers[AST_CONST_STR] = check_const_str;

    g_ast_names[AST_LIST] = "check_list";
    g_ast_names[AST_FUNCDEF] = "check_funcdef";
    g_ast_names[AST_FUNCHEAD] = "check_funchead";
    g_ast_names[AST_PARA] = "check_para";
    g_ast_names[AST_VAR] = "check_var";
    g_ast_names[AST_SUBVAR_ID] = "check_subvar_id";
    g_ast_names[AST_COMPOUND_STMT] = "check_compound_stmt";
    g_ast_names[AST_EXPR_STMT] = "check_expr_stmt";
    g_ast_names[AST_IF_STMT] = "check_if_stmt";
    g_ast_names[AST_FOR_STMT] = "check_for_stmt";
    g_ast_names[AST_PRINTF_STMT] = "check_printf_stmt";
    g_ast_names[AST_SCANF_STMT] = "check_scanf_stmt";
    g_ast_names[AST_RETURN_STMT] = "check_return_stmt";
    g_ast_names[AST_CONTINUE_STMT] = "check_continue_stmt";
    g_ast_names[AST_BREAK_STMT] = "check_break_stmt";
    g_ast_names[AST_DEF] = "check_def";
    g_ast_names[AST_DEC] = "check_dec";
    g_ast_names[AST_BINOP] = "check_binop";
    g_ast_names[AST_PREFIX] = "check_prefix";
    g_ast_names[AST_POSTFIX] = "check_postfix";
    g_ast_names[AST_INDEXING] = "check_indexing";
    g_ast_names[AST_FUNC_CALL] = "check_func_call";
    g_ast_names[AST_ID] = "check_id";
    g_ast_names[AST_CONST] = "check_const";
    g_ast_names[AST_CONST_F] = "check_const_f";
    g_ast_names[AST_CONST_C] = "check_const_c";
    g_ast_names[AST_CONST_STR] = "check_const_str";

}

void check_ast(ast_node *n)
{
    init_ast_checkers();
    if (n)
    {
        g_ast_checkers[n->type](n);
    }
}

void check_semantics(ast_node *ast)
{
    //the "main" function MUST be in the program.c
    if(find_record_funcdef_node_ST("main") == NULL)
    report_error("Error - riferimento non definito a \"main\"");

    check_ast(ast);
}
