%option noyywrap nodefault yylineno
%{

#include "C2Python.tab.h"

int line_number = 1;

YYSTYPE yylval;   // token value

#define YY_USER_ACTION do{     \
  yylloc.first_line = yylloc.last_line = yylineno; \
} while(0); \

%}

%x C_COMMENT

%%

"break"     { return BREAK; }
"continue"  { return CONTINUE; }
"else"      { return ELSE; }
"for"        { return FOR; }
"if"        { return IF; }
"int"       { return INT; }
"char"      { return CHAR; }
"float"     { return FLOAT;}
"double"     { return DOUBLE;}
"void"      { return VOID;}
"printf"    { return PRINTF; }
"scanf"     { return SCANF; }
"return"    { return RETURN; }

[a-zA-Z_][0-9a-zA-Z_]*   { yylval.sval = strdup(yytext); return IDENTIFIER; }
'((''|[^'])*)'           { yylval.sval = strdup(yytext); return CHAR_VALUE; }
[0-9]+                   { yylval.i = atoi(yytext); return CONSTANT; }
([0-9]*\.?[0-9]*)([eE]([0-9]+))*  { yylval.sval = strdup(yytext); return CONSTANT_F; }

";"     { return ';'; }
","     { return ','; }
"\""    { return '"'; }
"["     { return '['; }
"]"     { return ']'; }
"{"     { return '{'; }
"}"     { return '}'; }
"!"     { return '!'; }
"++"    { return INC_OP; }
"--"    { return DEC_OP; }
"*"     { return '*'; }
"/"     { return '/'; }
"%"     { return '%'; }
"+"     { return '+'; }
"-"     { return '-'; }
">"     { return '>'; }
">="    { return GE_OP; }
"<"     { return '<'; }
"<="    { return LE_OP; }
"=="    { return EQ_OP; }
"!="    { return NE_OP; }
"&"     { return '&'; }
"&&"    { return AND_OP; }
"||"    { return OR_OP; }
"="     { return '='; }
"("     { return '('; }
")"     { return ')'; }
[$:@#£|'^?]  {return SPECIAL_CHAR;}

\"(\\.|[^\\"])*\"         { yylval.sval = strdup(yytext); return STRING; }

[ \t\v\r\f]   { /* ignore  */ }
\n            {line_number++ ;}

.       { /* ignore */ }

"//".*            { BEGIN(INITIAL) ;}
"/*"              { BEGIN(C_COMMENT);}
<C_COMMENT>"*/"   { BEGIN(INITIAL) ; }
<C_COMMENT>\n     { }
<C_COMMENT>.      { }

%%
