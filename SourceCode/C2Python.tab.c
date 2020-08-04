/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "C2Python.y" /* yacc.c:339  */

#include "C2Python.h"
#include <stdio.h>
#include <stdlib.h>

#define YYERROR_VERBOSE

extern int yylineno;
extern FILE *yyin;


#line 78 "C2Python.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "C2Python.tab.h".  */
#ifndef YY_YY_C2PYTHON_TAB_H_INCLUDED
# define YY_YY_C2PYTHON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OR_OP = 258,
    AND_OP = 259,
    EQ_OP = 260,
    NE_OP = 261,
    LE_OP = 262,
    GE_OP = 263,
    INC_OP = 264,
    DEC_OP = 265,
    CONSTANT = 266,
    SPECIAL_CHAR = 267,
    IDENTIFIER = 268,
    CONSTANT_F = 269,
    CHAR_VALUE = 270,
    STRING = 271,
    INT = 272,
    FLOAT = 273,
    DOUBLE = 274,
    CHAR = 275,
    VOID = 276,
    IF = 277,
    FOR = 278,
    CONTINUE = 279,
    BREAK = 280,
    RETURN = 281,
    SCANF = 282,
    PRINTF = 283,
    ELSE = 284,
    EXTDEFS = 285,
    PARAS = 286,
    STMTS = 287,
    DEFS = 288,
    DECS = 289,
    ARGS = 290,
    INIT_ARGS = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 13 "C2Python.y" /* yacc.c:355  */

    int i;
    char *sval;
    struct ast_node *n;

#line 161 "C2Python.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_C2PYTHON_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 192 "C2Python.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   518

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  228

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    18,    35,     2,     2,    17,    21,     2,
      22,    23,    15,    13,     3,    14,     2,    16,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
      11,     4,    12,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    25,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,    27,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     5,     6,
       7,     8,     9,    10,    19,    20,    28,    29,    30,    31,
      32,    33,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    53,    53,    54,    58,    59,    63,    64,    65,    66,
      67,    68,    72,    73,    77,    78,    82,    83,    84,    85,
      89,    90,    94,    95,    99,   100,   101,   102,   103,   104,
     105,   109,   110,   111,   112,   116,   120,   121,   125,   126,
     127,   128,   129,   130,   131,   132,   136,   137,   138,   142,
     146,   147,   148,   149,   153,   154,   158,   159,   160,   161,
     165,   166,   170,   171,   175,   176,   177,   181,   185,   186,
     190,   191,   195,   196,   201,   202,   206,   207,   208,   212,
     213,   214,   215,   216,   220,   221,   222,   226,   227,   228,
     229,   233,   234,   235,   236,   237,   238,   239,   243,   244,
     245,   246,   250,   251,   252,   253,   254,   255,   259,   260,
     264,   265,   269
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "','", "'='", "OR_OP", "AND_OP", "EQ_OP",
  "NE_OP", "LE_OP", "GE_OP", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'!'", "INC_OP", "DEC_OP", "'&'", "'('", "')'", "'['", "']'",
  "'{'", "'}'", "CONSTANT", "SPECIAL_CHAR", "IDENTIFIER", "CONSTANT_F",
  "CHAR_VALUE", "STRING", "';'", "'\"'", "INT", "FLOAT", "DOUBLE", "CHAR",
  "VOID", "IF", "FOR", "CONTINUE", "BREAK", "RETURN", "SCANF", "PRINTF",
  "ELSE", "EXTDEFS", "PARAS", "STMTS", "DEFS", "DECS", "ARGS", "INIT_ARGS",
  "$accept", "program", "extdefs", "extdef", "func", "paras", "para",
  "var", "stmts", "stmt", "compound_stmt", "expr_stmt", "selection_stmt",
  "iteration_stmt", "printf_stmt", "scanf_stmt", "jump_stmt", "defs",
  "def", "decs", "dec", "init", "expr", "assignment", "logical_or",
  "logical_and", "bit_and", "equality", "relational", "additive", "multi",
  "unary", "postfix", "primary", "args", "init_args", "init_arg", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    44,    61,   258,   259,   260,   261,   262,
     263,    60,    62,    43,    45,    42,    47,    37,    33,   264,
     265,    38,    40,    41,    91,    93,   123,   125,   266,   267,
     268,   269,   270,   271,    59,    34,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291
};
# endif

#define YYPACT_NINF -46

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-46)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     262,     7,     7,     7,     7,    22,    54,   262,   -46,   -46,
      48,    37,     9,     4,   -46,    37,    12,    37,    16,    37,
      19,    48,    37,   -46,   -46,    28,   162,   -46,   326,   473,
      42,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,
      42,    42,    42,    42,    11,   -46,   473,   473,   237,   237,
     473,   -46,   -46,   -46,   -46,   -46,   -46,    42,    42,    42,
      42,    79,    83,   100,   111,    84,    91,   104,    -2,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   196,   -46,   113,
     -46,   143,   144,   131,    41,    66,    43,    80,   154,    49,
     -46,   346,   -46,   -46,   135,   -46,   -46,   137,   137,   137,
     137,    92,   -46,   -46,   -46,   -13,   -13,   141,   473,   105,
     -46,   -46,   -46,   133,   136,   145,   -46,   -46,   -46,   230,
     -46,   -46,   473,   473,   473,   473,   473,   473,   473,   473,
     473,   473,   473,   473,   473,   473,   473,   -46,   -46,   366,
     473,   -46,   -46,     5,   -46,   -46,   -46,   -46,   160,   298,
     151,   -46,   183,    24,   -46,   144,   -46,   131,    41,    66,
      66,    43,    43,    43,    43,    80,    80,   -46,   -46,   -46,
     -46,   -46,   -46,    32,   166,   473,   -46,   264,   386,   153,
     305,   175,   406,   163,   473,   -46,   -46,   -46,   164,   264,
     179,   426,   446,   177,   473,   473,   190,   -46,   -46,   264,
     -46,   264,   264,   194,   264,   197,   466,   198,   202,   185,
     -46,   -46,   -46,   264,   -46,   264,   264,   207,   211,   212,
     -46,   -46,   -46,   -46,   264,   -46,   -46,   -46
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,     0,     0,     0,     3,     4,     6,
      20,     0,    62,     0,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     5,     0,     0,     7,     0,     0,
       0,    56,     9,    57,    10,    58,    11,    59,     8,    13,
       0,     0,     0,     0,     0,    14,     0,     0,     0,     0,
       0,    34,   103,   102,   104,   105,   106,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    22,
      24,    25,    26,    27,    28,    29,    30,     0,    54,     0,
      67,    68,    70,    72,    74,    76,    79,    84,    87,    91,
      98,     0,    63,    64,     0,    20,    61,    16,    17,    18,
      19,     0,    12,    96,    97,    92,    93,     0,     0,     0,
      52,    53,    51,     0,     0,     0,    33,    23,    32,     0,
      55,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    95,     0,
       0,    66,   112,     0,   110,    21,    15,   107,     0,     0,
       0,    50,     0,     0,    31,    71,    87,    73,    75,    77,
      78,    83,    81,    82,    80,    85,    86,    88,    89,    90,
      69,   101,   108,     0,     0,     0,    65,     0,     0,     0,
       0,     0,     0,     0,     0,   100,    99,   111,    36,     0,
       0,     0,     0,     0,     0,     0,     0,    46,   109,     0,
      45,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,    44,    43,     0,    41,     0,     0,     0,     0,     0,
      47,    42,    40,    39,     0,    49,    48,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -46,   -46,   -46,   224,   138,   -46,   146,   132,   159,   -45,
     496,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -16,     0,
     221,   -46,   -29,   -27,   -46,   142,   130,   155,   -26,   242,
     -24,   -41,    73,   -46,   -46,   -46,   106
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,    11,    44,    45,    12,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,     9,    13,
      14,    92,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,   173,   143,   144
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      94,    93,    16,    18,    20,   103,   104,    30,   175,   139,
      78,   140,    46,    28,   101,    30,    47,    48,    49,    30,
      50,   107,    30,   117,    26,   116,    52,   182,    53,    54,
      55,    56,   176,    29,   102,   184,   113,    10,    31,    61,
      62,    63,    64,    65,    66,    67,    33,   183,   125,   126,
      35,    39,    21,    37,    23,   185,   131,   132,    16,    18,
      20,   120,   142,    26,    40,    41,    42,    43,   137,   138,
      25,   139,    95,   140,   117,   127,   128,   129,   130,   148,
     150,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   167,   168,   169,   133,   134,   135,    46,   159,
     160,   108,    47,    48,    49,   109,    50,   165,   166,   170,
     172,   174,    52,   114,    53,    54,    55,    56,   112,    46,
     179,   105,   106,    47,    48,    49,   115,    50,    40,    41,
      42,    43,   188,    52,   110,    53,    54,    55,    56,   149,
      15,    17,    19,    22,   200,   111,   142,   121,   122,   190,
     123,   193,   124,   196,   210,   198,   211,   212,   136,   214,
     145,    29,   203,   205,   147,   207,   208,   151,   221,   152,
     222,   223,    97,    98,    99,   100,    46,   217,   153,   227,
      47,    48,    49,   177,    50,   180,   181,   191,    26,    51,
      52,   186,    53,    54,    55,    56,   194,   197,    57,    58,
      59,    60,   201,    61,    62,    63,    64,    65,    66,    67,
      46,   206,   199,   209,    47,    48,    49,   213,    50,   220,
     215,   218,    26,   118,    52,   219,    53,    54,    55,    56,
     224,    24,    57,    58,    59,    60,   119,    61,    62,    63,
      64,    65,    66,    67,    46,   225,   226,   146,    47,    48,
      49,    96,    50,   157,     0,     0,    26,   154,    52,    50,
      53,    54,    55,    56,   155,    52,     0,    53,    54,    55,
      56,    61,    62,    63,    64,    65,    66,    67,    46,   158,
       0,   187,    47,    48,    49,     0,    50,     0,     0,     0,
      26,     0,    52,     0,    53,    54,    55,    56,     1,     2,
       3,     4,     5,     0,     0,    61,    62,    63,    64,    65,
      66,    67,    46,     0,     0,     0,    47,    48,    49,    46,
      50,     0,     0,    47,    48,    49,    52,    50,    53,    54,
      55,    56,   178,    52,     0,    53,    54,    55,    56,   192,
      46,     0,     0,     0,    47,    48,    49,     0,    50,     0,
       0,     0,    91,     0,    52,     0,    53,    54,    55,    56,
      46,     0,     0,     0,    47,    48,    49,     0,    50,   161,
     162,   163,   164,   141,    52,     0,    53,    54,    55,    56,
      46,     0,     0,     0,    47,    48,    49,     0,    50,   171,
       0,     0,     0,     0,    52,     0,    53,    54,    55,    56,
      46,     0,     0,     0,    47,    48,    49,     0,    50,   189,
       0,     0,     0,     0,    52,     0,    53,    54,    55,    56,
      46,     0,     0,     0,    47,    48,    49,   195,    50,     0,
       0,     0,     0,     0,    52,     0,    53,    54,    55,    56,
      46,     0,     0,     0,    47,    48,    49,     0,    50,   202,
       0,     0,     0,     0,    52,     0,    53,    54,    55,    56,
      46,     0,     0,     0,    47,    48,    49,     0,    50,   204,
       0,     0,     0,     0,    52,     0,    53,    54,    55,    56,
      46,     0,     0,     0,    47,    48,    49,    46,    50,   216,
       0,    47,    48,    49,    52,    50,    53,    54,    55,    56,
       0,    52,     0,    53,    54,    55,    56,    27,     0,     0,
       0,    32,     0,    34,     0,    36,     0,     0,    38
};

static const yytype_int16 yycheck[] =
{
      29,    28,     2,     3,     4,    46,    47,     3,     3,    22,
      26,    24,    14,     4,     3,     3,    18,    19,    20,     3,
      22,    50,     3,    68,    26,    27,    28,     3,    30,    31,
      32,    33,    27,    24,    23,     3,    65,    30,    34,    41,
      42,    43,    44,    45,    46,    47,    34,    23,     7,     8,
      34,    23,    30,    34,     0,    23,    13,    14,    58,    59,
      60,    77,    91,    26,    36,    37,    38,    39,    19,    20,
      22,    22,    30,    24,   119,     9,    10,    11,    12,   108,
     109,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,    15,    16,    17,    14,   125,
     126,    22,    18,    19,    20,    22,    22,   131,   132,   136,
     139,   140,    28,    22,    30,    31,    32,    33,    34,    14,
     149,    48,    49,    18,    19,    20,    22,    22,    36,    37,
      38,    39,   177,    28,    34,    30,    31,    32,    33,    34,
       2,     3,     4,     5,   189,    34,   175,    34,     5,   178,
       6,   180,    21,   182,   199,   184,   201,   202,     4,   204,
      25,    24,   191,   192,    23,   194,   195,    34,   213,    33,
     215,   216,    40,    41,    42,    43,    14,   206,    33,   224,
      18,    19,    20,    23,    22,    34,     3,    34,    26,    27,
      28,    25,    30,    31,    32,    33,    21,    34,    36,    37,
      38,    39,    23,    41,    42,    43,    44,    45,    46,    47,
      14,    34,    48,    23,    18,    19,    20,    23,    22,    34,
      23,    23,    26,    27,    28,    23,    30,    31,    32,    33,
      23,     7,    36,    37,    38,    39,    77,    41,    42,    43,
      44,    45,    46,    47,    14,    34,    34,   101,    18,    19,
      20,    30,    22,   123,    -1,    -1,    26,    27,    28,    22,
      30,    31,    32,    33,   122,    28,    -1,    30,    31,    32,
      33,    41,    42,    43,    44,    45,    46,    47,    14,   124,
      -1,   175,    18,    19,    20,    -1,    22,    -1,    -1,    -1,
      26,    -1,    28,    -1,    30,    31,    32,    33,    36,    37,
      38,    39,    40,    -1,    -1,    41,    42,    43,    44,    45,
      46,    47,    14,    -1,    -1,    -1,    18,    19,    20,    14,
      22,    -1,    -1,    18,    19,    20,    28,    22,    30,    31,
      32,    33,    34,    28,    -1,    30,    31,    32,    33,    34,
      14,    -1,    -1,    -1,    18,    19,    20,    -1,    22,    -1,
      -1,    -1,    26,    -1,    28,    -1,    30,    31,    32,    33,
      14,    -1,    -1,    -1,    18,    19,    20,    -1,    22,   127,
     128,   129,   130,    27,    28,    -1,    30,    31,    32,    33,
      14,    -1,    -1,    -1,    18,    19,    20,    -1,    22,    23,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      14,    -1,    -1,    -1,    18,    19,    20,    -1,    22,    23,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      14,    -1,    -1,    -1,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      14,    -1,    -1,    -1,    18,    19,    20,    -1,    22,    23,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      14,    -1,    -1,    -1,    18,    19,    20,    -1,    22,    23,
      -1,    -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,
      14,    -1,    -1,    -1,    18,    19,    20,    14,    22,    23,
      -1,    18,    19,    20,    28,    22,    30,    31,    32,    33,
      -1,    28,    -1,    30,    31,    32,    33,    11,    -1,    -1,
      -1,    15,    -1,    17,    -1,    19,    -1,    -1,    22
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    37,    38,    39,    40,    57,    58,    59,    74,
      30,    60,    63,    75,    76,    60,    75,    60,    75,    60,
      75,    30,    60,     0,    59,    22,    26,    66,     4,    24,
       3,    34,    66,    34,    66,    34,    66,    34,    66,    23,
      36,    37,    38,    39,    61,    62,    14,    18,    19,    20,
      22,    27,    28,    30,    31,    32,    33,    36,    37,    38,
      39,    41,    42,    43,    44,    45,    46,    47,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    26,    77,    79,    78,    30,    76,    63,    63,    63,
      63,     3,    23,    87,    87,    88,    88,    78,    22,    22,
      34,    34,    34,    78,    22,    22,    27,    65,    27,    64,
      74,    34,     5,     6,    21,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     4,    19,    20,    22,
      24,    27,    78,    91,    92,    25,    62,    23,    78,    34,
      78,    34,    33,    33,    27,    81,    87,    82,    83,    84,
      84,    85,    85,    85,    85,    86,    86,    87,    87,    87,
      79,    23,    78,    90,    78,     3,    27,    23,    34,    78,
      34,     3,     3,    23,     3,    23,    25,    92,    65,    23,
      78,    34,    34,    78,    21,    21,    78,    34,    78,    48,
      65,    23,    23,    78,    23,    78,    34,    78,    78,    23,
      65,    65,    65,    23,    65,    23,    23,    78,    23,    23,
      34,    65,    65,    65,    23,    34,    34,    65
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    57,    58,    58,    59,    59,    59,    59,
      59,    59,    60,    60,    61,    61,    62,    62,    62,    62,
      63,    63,    64,    64,    65,    65,    65,    65,    65,    65,
      65,    66,    66,    66,    66,    67,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    70,    71,
      72,    72,    72,    72,    73,    73,    74,    74,    74,    74,
      75,    75,    76,    76,    77,    77,    77,    78,    79,    79,
      80,    80,    81,    81,    82,    82,    83,    83,    83,    84,
      84,    84,    84,    84,    85,    85,    85,    86,    86,    86,
      86,    87,    87,    87,    87,    87,    87,    87,    88,    88,
      88,    88,    89,    89,    89,    89,    89,    89,    90,    90,
      91,    91,    92
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     1,     3,     3,     3,
       3,     3,     4,     3,     1,     3,     2,     2,     2,     2,
       1,     4,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     4,     3,     3,     2,     2,     5,     7,     9,     8,
       8,     7,     8,     7,     7,     6,     5,     7,     8,     8,
       3,     2,     2,     2,     1,     2,     3,     3,     3,     3,
       1,     3,     1,     3,     1,     3,     2,     1,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     2,     2,     2,     2,     2,     2,     1,     4,
       4,     3,     1,     1,     1,     1,     1,     3,     1,     3,
       1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 53 "C2Python.y" /* yacc.c:1646  */
    { set_parse_tree((yyval.n) = NULL); }
#line 1579 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 54 "C2Python.y" /* yacc.c:1646  */
    { set_parse_tree((yyval.n) = (yyvsp[0].n)); }
#line 1585 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 58 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = list_new(EXTDEFS, (yyvsp[0].n), NULL); }
#line 1591 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 59 "C2Python.y" /* yacc.c:1646  */
    { list_append((yyval.n) = (yyvsp[-1].n), list_new(EXTDEFS, (yyvsp[0].n), NULL)); }
#line 1597 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 63 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1603 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 64 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = funcdef_new(int_type(), (yyvsp[-1].n), (yyvsp[0].n)); }
#line 1609 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 65 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = funcdef_new(void_type(), (yyvsp[-1].n), (yyvsp[0].n)); }
#line 1615 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 66 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = funcdef_new(float_type(), (yyvsp[-1].n), (yyvsp[0].n)); }
#line 1621 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 67 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = funcdef_new(double_type(), (yyvsp[-1].n), (yyvsp[0].n)); }
#line 1627 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 68 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = funcdef_new(char_type(), (yyvsp[-1].n), (yyvsp[0].n)); }
#line 1633 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 72 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = funchead_new((yyvsp[-3].sval), (yyvsp[-1].n), yylineno); }
#line 1639 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 73 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = funchead_new((yyvsp[-2].sval), NULL, yylineno); }
#line 1645 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 77 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = list_new(PARAS, (yyvsp[0].n), NULL); }
#line 1651 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 78 "C2Python.y" /* yacc.c:1646  */
    { list_append((yyval.n) = (yyvsp[-2].n), list_new(PARAS, (yyvsp[0].n), NULL)); }
#line 1657 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 82 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = para_new(int_type(), (yyvsp[0].n), yylineno); }
#line 1663 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 83 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = para_new(float_type(), (yyvsp[0].n), yylineno); }
#line 1669 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 84 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = para_new(double_type(), (yyvsp[0].n), yylineno); }
#line 1675 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 85 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = para_new(char_type(), (yyvsp[0].n), yylineno); }
#line 1681 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 89 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = var_new((yyvsp[0].sval), yylineno); }
#line 1687 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 90 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = subvar_new_id((yyvsp[-3].n), (yyvsp[-1].n), yylineno); }
#line 1693 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 94 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = list_new(STMTS, (yyvsp[0].n), NULL); }
#line 1699 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 95 "C2Python.y" /* yacc.c:1646  */
    { list_append((yyval.n) = (yyvsp[-1].n), list_new(STMTS, (yyvsp[0].n), NULL)); }
#line 1705 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 99 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1711 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 100 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1717 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 101 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1723 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 102 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1729 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 103 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1735 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 104 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1741 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 105 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1747 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 109 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = compound_stmt_new((yyvsp[-2].n), (yyvsp[-1].n)); }
#line 1753 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 110 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = compound_stmt_new((yyvsp[-1].n), NULL); }
#line 1759 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 111 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = compound_stmt_new(NULL, (yyvsp[-1].n)); }
#line 1765 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 112 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = compound_stmt_new(NULL, NULL); }
#line 1771 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 116 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = expr_stmt_new((yyvsp[-1].n)); }
#line 1777 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 120 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = if_stmt_new((yyvsp[-2].n), (yyvsp[0].n), NULL, (yylsp[-4]).first_line); }
#line 1783 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 121 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = if_stmt_new((yyvsp[-4].n), (yyvsp[-2].n), (yyvsp[0].n), (yylsp[-6]).first_line); }
#line 1789 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 125 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = for_stmt_new((yyvsp[-6].n),   (yyvsp[-4].n),   (yyvsp[-2].n),   (yyvsp[0].n), (yylsp[-8]).first_line); }
#line 1795 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 126 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = for_stmt_new((yyvsp[-5].n),   (yyvsp[-3].n),   NULL, (yyvsp[0].n), (yylsp[-7]).first_line); }
#line 1801 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 127 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = for_stmt_new((yyvsp[-5].n),   NULL, (yyvsp[-2].n),   (yyvsp[0].n), (yylsp[-7]).first_line); }
#line 1807 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 128 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = for_stmt_new((yyvsp[-4].n),   NULL, NULL, (yyvsp[0].n), (yylsp[-6]).first_line); }
#line 1813 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 129 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = for_stmt_new(NULL, (yyvsp[-4].n),   (yyvsp[-2].n),   (yyvsp[0].n), (yylsp[-7]).first_line); }
#line 1819 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 130 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = for_stmt_new(NULL, (yyvsp[-3].n),   NULL, (yyvsp[0].n), (yylsp[-6]).first_line); }
#line 1825 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 131 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = for_stmt_new(NULL, NULL, (yyvsp[-2].n),   (yyvsp[0].n), (yylsp[-6]).first_line); }
#line 1831 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 132 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = for_stmt_new(NULL, NULL, NULL, (yyvsp[0].n), (yylsp[-5]).first_line); }
#line 1837 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 136 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = printf_stmt_new((yyvsp[-2].sval), NULL,0, yylineno); }
#line 1843 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 137 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = printf_stmt_new((yyvsp[-4].sval), (yyvsp[-2].n), 0, yylineno); }
#line 1849 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 138 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = printf_stmt_new((yyvsp[-5].sval), (yyvsp[-2].n), 1, yylineno); }
#line 1855 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 142 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = scanf_stmt_new((yyvsp[-5].sval) , (yyvsp[-2].n), yylineno); }
#line 1861 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 146 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = return_stmt_new((yyvsp[-1].n),1, yylineno); }
#line 1867 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 147 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = return_stmt_new(NULL ,0, yylineno); }
#line 1873 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 148 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = continue_stmt_new(yylineno); }
#line 1879 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 149 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = break_stmt_new(yylineno); }
#line 1885 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 153 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = list_new(DEFS, (yyvsp[0].n), NULL); }
#line 1891 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 154 "C2Python.y" /* yacc.c:1646  */
    { list_append((yyval.n) = (yyvsp[-1].n), list_new(DEFS, (yyvsp[0].n), NULL)); }
#line 1897 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 158 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = def_new(int_type(), (yyvsp[-1].n)); }
#line 1903 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 159 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = def_new(float_type(), (yyvsp[-1].n)); }
#line 1909 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 160 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = def_new(double_type(), (yyvsp[-1].n)); }
#line 1915 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 161 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = def_new(char_type(), (yyvsp[-1].n)); }
#line 1921 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 165 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = list_new(DECS, (yyvsp[0].n), NULL); }
#line 1927 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 166 "C2Python.y" /* yacc.c:1646  */
    { list_append((yyval.n) = (yyvsp[-2].n), list_new(DECS, (yyvsp[0].n), NULL)); }
#line 1933 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 170 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = dec_new((yyvsp[0].n), NULL, yylineno); }
#line 1939 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 171 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = dec_new((yyvsp[-2].n), (yyvsp[0].n), yylineno); }
#line 1945 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 175 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1951 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 176 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[-1].n); }
#line 1957 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 177 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = NULL; }
#line 1963 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 181 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1969 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 185 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1975 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 186 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new('=', (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 1981 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 190 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1987 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 191 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new(OR_OP, (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 1993 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 195 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 1999 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 196 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new(AND_OP, (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2005 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 201 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 2011 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 202 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new('&', (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2017 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 206 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 2023 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 207 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new(EQ_OP, (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2029 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 208 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new(NE_OP, (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2035 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 212 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 2041 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 213 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new('>', (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2047 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 214 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new(GE_OP, (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2053 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 215 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new('<', (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2059 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 216 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new(LE_OP, (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2065 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 220 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 2071 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 221 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new('+', (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2077 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 222 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new('-', (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2083 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 226 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 2089 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 227 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new('*', (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2095 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 228 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new('/', (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2101 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 229 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = binop_new('%', (yyvsp[-2].n), (yyvsp[0].n), 0, yylineno); }
#line 2107 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 233 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 2113 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 234 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = prefix_new(INC_OP, (yyvsp[0].n), yylineno); }
#line 2119 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 235 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = prefix_new(DEC_OP, (yyvsp[0].n), yylineno); }
#line 2125 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 236 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = postfix_new(INC_OP, (yyvsp[-1].n), yylineno); }
#line 2131 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 237 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = postfix_new(DEC_OP, (yyvsp[-1].n), yylineno); }
#line 2137 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 238 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = prefix_new('-', (yyvsp[0].n), yylineno); }
#line 2143 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 239 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = prefix_new('!', (yyvsp[0].n), yylineno); }
#line 2149 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 243 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 2155 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 244 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = indexing_new((yyvsp[-3].n), (yyvsp[-1].n), yylineno); }
#line 2161 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 245 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = func_call_new((yyvsp[-3].n), (yyvsp[-1].n), yylineno); }
#line 2167 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 246 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = func_call_new((yyvsp[-2].n), NULL, yylineno); }
#line 2173 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 250 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = id_new((yyvsp[0].sval), yylineno); }
#line 2179 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 251 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = const_new((yyvsp[0].i), yylineno); }
#line 2185 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 252 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = const_f_new((yyvsp[0].sval), yylineno); }
#line 2191 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 253 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = const_c_new((yyvsp[0].sval), yylineno); }
#line 2197 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 254 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = const_str_new((yyvsp[0].sval), yylineno); }
#line 2203 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 255 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[-1].n); brackets_expr_new();}
#line 2209 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 259 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = list_new(ARGS, (yyvsp[0].n), NULL); }
#line 2215 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 260 "C2Python.y" /* yacc.c:1646  */
    { list_append((yyval.n) = (yyvsp[-2].n), list_new(ARGS, (yyvsp[0].n), NULL)); }
#line 2221 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 264 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = list_new(INIT_ARGS, (yyvsp[0].n), NULL); }
#line 2227 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 265 "C2Python.y" /* yacc.c:1646  */
    { list_append((yyval.n) = (yyvsp[-2].n), list_new(INIT_ARGS, (yyvsp[0].n), NULL)); }
#line 2233 "C2Python.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 269 "C2Python.y" /* yacc.c:1646  */
    { (yyval.n) = (yyvsp[0].n); }
#line 2239 "C2Python.tab.c" /* yacc.c:1646  */
    break;


#line 2243 "C2Python.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 272 "C2Python.y" /* yacc.c:1906  */



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
