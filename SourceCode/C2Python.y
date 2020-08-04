%{
#include "C2Python.h"
#include <stdio.h>
#include <stdlib.h>

#define YYERROR_VERBOSE

extern int yylineno;
extern FILE *yyin;

%}

%union{
    int i;
    char *sval;
    struct ast_node *n;
}

//Terminal Token
%left <i> ','
%right <i> '='
%left  <i> OR_OP
%left  <i> AND_OP
%left  <i> EQ_OP NE_OP
%left  <i> LE_OP GE_OP '<' '>'
%left  <i> '+' '-'
%left  <i> '*' '/' '%'
%right <i> '!'
%right <i> INC_OP DEC_OP '&'
%left  <i> '(' ')' '[' ']' '{' '}'

%token <i> CONSTANT SPECIAL_CHAR
%token <sval> IDENTIFIER CONSTANT_F CHAR_VALUE STRING


%token  ';' '"'
%token INT FLOAT DOUBLE CHAR VOID
%token IF FOR CONTINUE BREAK RETURN SCANF PRINTF
%precedence ELSE
%token EXTDEFS PARAS STMTS DEFS DECS ARGS INIT_ARGS

//NON-Terminal Token
%type <n> extdef func para var def dec init init_arg
%type <n> expr assignment logical_or logical_and bit_and equality relational additive multi unary postfix primary
%type <n> program extdefs paras stmts defs decs args init_args
%type <n> stmt compound_stmt expr_stmt selection_stmt iteration_stmt jump_stmt printf_stmt scanf_stmt


%start program

%%
program
  : /* empty */   { set_parse_tree($$ = NULL); }
  | extdefs       { set_parse_tree($$ = $1); }
  ;

extdefs
  : extdef          { $$ = list_new(EXTDEFS, $1, NULL); }
  | extdefs extdef  { list_append($$ = $1, list_new(EXTDEFS, $2, NULL)); }
  ;

extdef
  : def                         { $$ = $1; }
  | INT    func compound_stmt   { $$ = funcdef_new(int_type(), $2, $3); }
  | VOID   func compound_stmt   { $$ = funcdef_new(void_type(), $2, $3); }
  | FLOAT  func compound_stmt   { $$ = funcdef_new(float_type(), $2, $3); }
  | DOUBLE func compound_stmt   { $$ = funcdef_new(double_type(), $2, $3); }
  | CHAR   func compound_stmt   { $$ = funcdef_new(char_type(), $2, $3); }
  ;

func
  : IDENTIFIER '(' paras ')'  { $$ = funchead_new($1, $3, yylineno); }
  | IDENTIFIER '('       ')'  { $$ = funchead_new($1, NULL, yylineno); }
  ;

paras
  : para            { $$ = list_new(PARAS, $1, NULL); }
  | paras ',' para  { list_append($$ = $1, list_new(PARAS, $3, NULL)); }
  ;

para
  : INT     var  { $$ = para_new(int_type(), $2, yylineno); }
  | FLOAT   var  { $$ = para_new(float_type(), $2, yylineno); }
  | DOUBLE  var  { $$ = para_new(double_type(), $2, yylineno); }
  | CHAR    var  { $$ = para_new(char_type(), $2, yylineno); }
  ;

var
  : IDENTIFIER              { $$ = var_new($1, yylineno); }
  | var '[' expr ']'        { $$ = subvar_new_id($1, $3, yylineno); }
  ;

stmts
  : stmt        { $$ = list_new(STMTS, $1, NULL); }
  | stmts stmt  { list_append($$ = $1, list_new(STMTS, $2, NULL)); }
  ;

stmt
  : compound_stmt   { $$ = $1; }
  | expr_stmt       { $$ = $1; }
  | selection_stmt  { $$ = $1; }
  | iteration_stmt  { $$ = $1; }
  | printf_stmt     { $$ = $1; }
  | scanf_stmt      { $$ = $1; }
  | jump_stmt       { $$ = $1; }
  ;

compound_stmt
  : '{' defs stmts '}'  { $$ = compound_stmt_new($2, $3); }
  | '{' defs       '}'  { $$ = compound_stmt_new($2, NULL); }
  | '{'      stmts '}'  { $$ = compound_stmt_new(NULL, $2); }
  | '{'            '}'  { $$ = compound_stmt_new(NULL, NULL); }
  ;

expr_stmt
  : expr ';'  { $$ = expr_stmt_new($1); }
  ;

selection_stmt
  : IF '(' expr ')' stmt              { $$ = if_stmt_new($3, $5, NULL, @1.first_line); }
  | IF '(' expr ')' stmt ELSE stmt    { $$ = if_stmt_new($3, $5, $7, @1.first_line); }
  ;

iteration_stmt
  : FOR '(' expr ';' expr ';' expr ')' stmt   { $$ = for_stmt_new($3,   $5,   $7,   $9, @1.first_line); }
  | FOR '(' expr ';' expr ';'      ')' stmt   { $$ = for_stmt_new($3,   $5,   NULL, $8, @1.first_line); }
  | FOR '(' expr ';'      ';' expr ')' stmt   { $$ = for_stmt_new($3,   NULL, $6,   $8, @1.first_line); }
  | FOR '(' expr ';'      ';'      ')' stmt   { $$ = for_stmt_new($3,   NULL, NULL, $7, @1.first_line); }
  | FOR '('      ';' expr ';' expr ')' stmt   { $$ = for_stmt_new(NULL, $4,   $6,   $8, @1.first_line); }
  | FOR '('      ';' expr ';'      ')' stmt   { $$ = for_stmt_new(NULL, $4,   NULL, $7, @1.first_line); }
  | FOR '('      ';'      ';' expr ')' stmt   { $$ = for_stmt_new(NULL, NULL, $5,   $7, @1.first_line); }
  | FOR '('      ';'      ';'      ')' stmt   { $$ = for_stmt_new(NULL, NULL, NULL, $6, @1.first_line); }
  ;

printf_stmt
  :  PRINTF '(' STRING ')' ';'                  { $$ = printf_stmt_new($3, NULL,0, yylineno); }
  |  PRINTF '(' STRING ',' expr ')' ';'         { $$ = printf_stmt_new($3, $5, 0, yylineno); }
  |  PRINTF '(' STRING ',' '&' expr ')' ';'     { $$ = printf_stmt_new($3, $6, 1, yylineno); }
  ;

scanf_stmt
  : SCANF '(' STRING ',' '&' expr ')' ';'   { $$ = scanf_stmt_new($3 , $6, yylineno); }
  ;

jump_stmt
  : RETURN expr ';'   { $$ = return_stmt_new($2,1, yylineno); }
  | RETURN  ';'       { $$ = return_stmt_new(NULL ,0, yylineno); }
  | CONTINUE ';'      { $$ = continue_stmt_new(yylineno); }
  | BREAK ';'         { $$ = break_stmt_new(yylineno); }
  ;

defs
  : def       { $$ = list_new(DEFS, $1, NULL); }
  | defs def  { list_append($$ = $1, list_new(DEFS, $2, NULL)); }
  ;

def
  : INT      decs ';'   { $$ = def_new(int_type(), $2); }
  | FLOAT    decs ';'   { $$ = def_new(float_type(), $2); }
  | DOUBLE   decs ';'   { $$ = def_new(double_type(), $2); }
  | CHAR     decs ';'   { $$ = def_new(char_type(), $2); }
  ;

decs
  : dec           { $$ = list_new(DECS, $1, NULL); }
  | decs ',' dec  { list_append($$ = $1, list_new(DECS, $3, NULL)); }
  ;

dec
  : var           { $$ = dec_new($1, NULL, yylineno); }
  | var '=' init  { $$ = dec_new($1, $3, yylineno); }
  ;

init
  : assignment                { $$ = $1; }
  | '{' init_args '}'         { $$ = $2; }
  | '{'  '}'                  { $$ = NULL; }
  ;

expr
  : assignment  { $$ = $1; }
  ;

assignment
  : logical_or             { $$ = $1; }
  | unary '=' assignment   { $$ = binop_new('=', $1, $3, 0, yylineno); }
  ;

logical_or
  : logical_and                   { $$ = $1; }
  | logical_or OR_OP logical_and  { $$ = binop_new(OR_OP, $1, $3, 0, yylineno); }
  ;

logical_and
  : bit_and                      { $$ = $1; }
  | logical_and AND_OP bit_and   { $$ = binop_new(AND_OP, $1, $3, 0, yylineno); }
  ;


bit_and
  : equality              { $$ = $1; }
  | bit_and '&' equality  { $$ = binop_new('&', $1, $3, 0, yylineno); }
  ;

equality
  : relational                  { $$ = $1; }
  | equality EQ_OP relational   { $$ = binop_new(EQ_OP, $1, $3, 0, yylineno); }
  | equality NE_OP relational   { $$ = binop_new(NE_OP, $1, $3, 0, yylineno); }
  ;

relational
  : additive                   { $$ = $1; }
  | relational '>'   additive  { $$ = binop_new('>', $1, $3, 0, yylineno); }
  | relational GE_OP additive  { $$ = binop_new(GE_OP, $1, $3, 0, yylineno); }
  | relational '<'   additive  { $$ = binop_new('<', $1, $3, 0, yylineno); }
  | relational LE_OP additive  { $$ = binop_new(LE_OP, $1, $3, 0, yylineno); }
  ;

additive
  : multi               { $$ = $1; }
  | additive '+' multi  { $$ = binop_new('+', $1, $3, 0, yylineno); }
  | additive '-' multi  { $$ = binop_new('-', $1, $3, 0, yylineno); }
  ;

multi
  : unary             { $$ = $1; }
  | multi '*' unary   { $$ = binop_new('*', $1, $3, 0, yylineno); }
  | multi '/' unary   { $$ = binop_new('/', $1, $3, 0, yylineno); }
  | multi '%' unary   { $$ = binop_new('%', $1, $3, 0, yylineno); }
  ;

unary
  : postfix         { $$ = $1; }
  | INC_OP postfix  { $$ = prefix_new(INC_OP, $2, yylineno); }
  | DEC_OP postfix  { $$ = prefix_new(DEC_OP, $2, yylineno); }
  | postfix INC_OP  { $$ = postfix_new(INC_OP, $1, yylineno); }
  | postfix DEC_OP  { $$ = postfix_new(DEC_OP, $1, yylineno); }
  | '-' unary       { $$ = prefix_new('-', $2, yylineno); }
  | '!' unary       { $$ = prefix_new('!', $2, yylineno); }
  ;

postfix
  : primary                 { $$ = $1; }
  | postfix '[' expr ']'    { $$ = indexing_new($1, $3, yylineno); }
  | postfix '(' args ')'    { $$ = func_call_new($1, $3, yylineno); }
  | postfix '('      ')'    { $$ = func_call_new($1, NULL, yylineno); }
  ;

primary
  : IDENTIFIER    { $$ = id_new($1, yylineno); }
  | CONSTANT      { $$ = const_new($1, yylineno); }
  | CONSTANT_F    { $$ = const_f_new($1, yylineno); }
  | CHAR_VALUE    { $$ = const_c_new($1, yylineno); }
  | STRING        { $$ = const_str_new($1, yylineno); }
  | '(' expr ')'  { $$ = $2; brackets_expr_new();}
  ;

args
  : expr            { $$ = list_new(ARGS, $1, NULL); }
  | args ',' expr   { list_append($$ = $1, list_new(ARGS, $3, NULL)); }
  ;

init_args
  : init_arg                { $$ = list_new(INIT_ARGS, $1, NULL); }
  | init_args ',' init_arg  { list_append($$ = $1, list_new(INIT_ARGS, $3, NULL)); }
  ;

init_arg
  : expr   { $$ = $1; }
  ;

%%


/*EPILOGUE */
static ast_node *g_parse_tree;
int yy_error_flag = 0;

void yyerror(char const *s)
{
    fprintf(stderr, "Error at line number: %d - %s \n", yylineno ,s);
    yy_error_flag++;
}

void set_parse_tree(ast_node *tree)
{
    g_parse_tree = tree;
}


int main(int argc, char *argv[])
{

    yyin = fopen(argv[1],"r");

    if (argc > 1)
    freopen(argv[1], "r", stdin);

    if (argc > 2)
    freopen(argv[2], "w", stdout);

    yyparse();
    fclose(yyin);

    if (g_parse_tree && yy_error_flag == 0)
    {
        st_populate(g_parse_tree);
        // print_all_st_node();
        check_semantics(g_parse_tree);

        if( warning_count > 0)
        report_warning("\nATTENTION!\nWarnings have been found in your source program.\nErrors may occour in the target translated code.\n");

        transtext_ast(g_parse_tree);
    }
    return 0;
}
