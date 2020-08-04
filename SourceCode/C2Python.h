#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "C2Python.tab.h"


/** Parsing functions **/
extern int yylex(void);
extern void yyerror(char const *s);
extern int yyparse(void);


/** AST nodes **/
typedef struct ast_node {
    enum {
        AST_LIST/*0*/,
        AST_FUNCDEF, AST_FUNCHEAD, AST_PARA,
        AST_VAR,AST_SUBVAR_ID/*5*/,
        AST_COMPOUND_STMT, AST_EXPR_STMT, AST_IF_STMT, AST_FOR_STMT, AST_PRINTF_STMT/*10*/, AST_SCANF_STMT,
        AST_RETURN_STMT, AST_CONTINUE_STMT, AST_BREAK_STMT,
        AST_DEF/*15*/, AST_DEC,
        AST_BINOP, AST_PREFIX, AST_POSTFIX,
        AST_INDEXING/*20*/, AST_FUNC_CALL,
        AST_ID, AST_CONST,AST_CONST_F, AST_CONST_C/*25*/, AST_CONST_STR,
        AST_TYPE_LIMIT
    } type;

    union {
        struct {
            int type;
            struct ast_node *head;
            struct ast_node *tail;
        } list;

        struct {
            int ret_type;
            struct ast_node *funchead;
            struct ast_node *funcbody;
        } funcdef;

        struct {
            char *sym_name;
            struct ast_node *paras;
        } funchead;

        struct {
            int para_type;
            struct ast_node *var;
        } para;

        struct {
            char *sym_name;
        } var;

        struct {
            struct ast_node *index;
            struct ast_node *var;
        } subvar_id;

        struct {
            struct ast_node *defs;
            struct ast_node *stmts;
        } compound_stmt;

        struct {
            struct ast_node *expr;
        } expr_stmt;

        struct {
            struct ast_node *cond;
            struct ast_node *then;
            struct ast_node *els;
        } if_stmt;

        struct {
            struct ast_node *init;
            struct ast_node *cond;
            struct ast_node *incr;
            struct ast_node *body;
        } for_stmt;

        struct {
            char *init;
            struct ast_node *var;
            int address;
        } printf_stmt;

        struct {
            char *init;
            struct ast_node *var;
        } scanf_stmt;

        struct {
            int isReturn_var;
            struct ast_node *retval;
        } return_stmt;

        struct {
            int def_type;
            struct ast_node *decs;
        } def;

        struct {
            struct ast_node *var;
            struct ast_node *init;
        } dec;

        struct {
            int op;
            struct ast_node *lhs;
            struct ast_node *rhs;
            int flag_brackets;
        } binop;

        struct {
            int op;
            struct ast_node *unary;
        } prefix;

        struct {
            int op;
            struct ast_node *unary;
        } postfix;

        struct {
            struct ast_node *postfix;
            struct ast_node *expr;
        } indexing;

        struct {
            struct ast_node *postfix;
            struct ast_node *args;
        } func_call;

        struct {
            char *sym_name;
        } id;

        struct {
            int number;
        } constant;

        struct {
            char *number;
        } constant_f;

        struct {
            char *char_value;
        } constant_c;

        struct {
            char *string;
        } constant_str;

    };

    int type_id;
    int lvalue; // l value error handler
    int line_number; // line number
    int is_brackets;

} ast_node;

typedef ast_node ast_expr;
typedef ast_node ast_list;
typedef ast_node ast_stmt;

/* Symbol Table */
/* ST Legend */
// typeid (1->int)(2->void)(3->float)(4->double)(-2->char type)(-3->string type)
// typeName ("array", "var")
// ret_typeid (0->void)(1->int)(2->void)(3->float)(4->double)(-2->char type)

struct var_node
{
  int id;
  char identifier[1024];
  int typeid;
  char typeName[1024];
  int scopeId;
  int sub_scopeId;
  int declaration_line_number;
  struct var_node *next;
};

struct funcdef_node
{
  int id;
  char identifier[1024];
  int ret_typeid;
  int parameter_num;
  int scopeId;
  struct funcdef_node *next;
  int line_number;
};

struct func_par_node
{
  int id;
  int var_id;
  char identifier[1024];
  int typeid;
  int par_number;
  int funcId;   //id of funcdef_node
  struct func_par_node *next;
};

struct array_par_node
{
  int id;
  int var_id; //id of var_node
  int par_number; //i.e. pluto[10][20] -> par_number = 2
  int par_value; //i.e. pluto[10][20] -> par_value = 10 or 20
  struct array_par_node *next;
};

extern int warning_count; // count the warning number

// Symbol Table function prototypes
extern void print_all_st_node();
extern void st_populate(ast_node *node);

extern int stack_sub_scope[1024];
extern struct var_node* find_record_scope_varST(char *identifier, int scope_lv, int stack_sub_scope_index, int line_number);
extern int count_dimension_array_parST(int var_id);
extern int retrieve_last_dimension_array_parST(int var_id);
extern struct funcdef_node* find_record_funcdef_node_ST(char *identifier);
extern struct funcdef_node* find_record_scope_funcdef_node_ST(char *identifier, int scope_lv);
extern struct func_par_node* find_record_par_node_ST(int func_id, int par_number);

extern struct var_node *var_table;
extern struct funcdef_node *funcdef_table;
extern struct func_par_node *func_par_table;
extern struct array_par_node *array_par_table;

extern int int_type(void);
extern int void_type(void);
extern int float_type(void);
extern int double_type(void);
extern int char_type(void);
extern int str_type(void);


// AST function prototypes
extern ast_list *list_new(int type, ast_node *head, ast_list *tail);
extern void list_append(ast_list *first, ast_list *second);

extern void brackets_expr_new();

extern ast_node *funcdef_new(int ret_type, ast_node *funchead, ast_stmt *funcbody);
extern ast_node *funchead_new(char *sym_name, ast_list *paras, int line_number);
extern ast_node *para_new(int para_type, ast_node *var, int line_number);

extern ast_node *var_new(char *sym_name, int line_number);
extern ast_node *subvar_new_id(ast_node *var, ast_node * index, int line_number);

extern ast_stmt *compound_stmt_new(ast_list *defs, ast_list *stmts);
extern ast_stmt *expr_stmt_new(ast_expr *expr);
extern ast_stmt *if_stmt_new(ast_expr *cond, ast_stmt *then, ast_stmt *els, int line_number);
extern ast_stmt *for_stmt_new(ast_expr *init, ast_expr *cond, ast_expr *incr, ast_stmt *body, int line_number);
extern ast_stmt *printf_stmt_new(char *init, ast_node *var, int address, int line_number);
extern ast_stmt *scanf_stmt_new(char *init, ast_node *var, int line_number);
extern ast_stmt *return_stmt_new(ast_expr *retval,int isReturn_var, int line_number);
extern ast_stmt *continue_stmt_new(int line_number);
extern ast_stmt *break_stmt_new(int line_number);

extern ast_node *def_new(int def_type, ast_list *decs);
extern ast_node *dec_new(ast_node *var, ast_node *init, int line_number);

extern ast_expr *binop_new(int op, ast_expr *lhs, ast_expr *rhs, int flag_brackets, int line_number);
extern ast_expr *prefix_new(int op, ast_expr *unary, int line_number);
extern ast_expr *postfix_new(int op, ast_expr *unary, int line_number);
extern ast_expr *indexing_new(ast_expr *postfix, ast_expr *expr, int line_number);
extern ast_expr *func_call_new(ast_expr *postfix, ast_list *args, int line_number);
extern ast_expr *id_new(char *sym_name, int line_number);
extern ast_expr *const_new(int number, int line_number);
extern ast_expr *const_f_new(char *number, int line_number);
extern ast_expr *const_c_new(char *char_value, int line_number);
extern ast_expr *const_str_new(char *string, int line_number);

extern void set_parse_tree(ast_node *tree);
extern void report_error(const char *fmt, ...);
extern void report_warning(const char *fmt, ...);
extern int binary_operator_case(int op);

extern void check_ast(ast_node *n);
extern void check_semantics(ast_node *ast);
extern void trans_ast(ast_node *ast);
extern void transtext_ast(ast_node *ast);
