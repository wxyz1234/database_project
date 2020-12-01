
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "Parser.y"

/*声明节  将被原样拷贝,可选*/
#include <stdio.h>
#include "../parser/global.h"
#include "../parser/tree.h"
#include "../parser/Lexer.c"
//#include "../RecordManageSystem/utils/Myhash.h"

void yyerror(const char *);
int yylex(void); 
int parseFile();
Tree* Tree::tree = nullptr;


/* Line 189 of yacc.c  */
#line 87 "Parser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CREATE = 258,
     DROP = 259,
     USE = 260,
     SHOW = 261,
     DESC = 262,
     ADD = 263,
     DATABASE = 264,
     DATABASES = 265,
     TABLE = 266,
     TABLES = 267,
     INDEX = 268,
     ALTER = 269,
     INSERT = 270,
     INTO = 271,
     VALUES = 272,
     DELETEC = 273,
     FROM = 274,
     UPDATE = 275,
     SELECT = 276,
     WHERE = 277,
     IS = 278,
     NOT = 279,
     NULLC = 280,
     DEFAULT = 281,
     PRIMARY = 282,
     FOREIGN = 283,
     KEY = 284,
     REFERENCES = 285,
     RENAME = 286,
     TO = 287,
     ON = 288,
     AND = 289,
     SET = 290,
     INTEGER = 291,
     SMALLINT = 292,
     CHARTYPE = 293,
     DOUBLETYPE = 294,
     FLOATTYPE = 295,
     DATETYPE = 296,
     NUMERICTYPE = 297,
     EQ = 298,
     GT = 299,
     LT = 300,
     GE = 301,
     LE = 302,
     NE = 303,
     NAME = 304,
     TEXT = 305,
     INUM = 306,
     FNUM = 307,
     DATENUM = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 16 "Parser.y"

	Tree* tree;
	char* string;

	CreateDatabaseTree *CreateDatabasetree;
	DropDatabaseTree *DropDatabasetree;
	UseDatabaseTree *UseDatabasetree;
	ShowDatabaseTree *ShowDatabasetree;
	ShowDatabaseSTree *ShowDatabaseStree;
	ShowDatabaseDescTree *ShowDatabaseDesctree;	

	CreateTableTree *CreateTabletree;
	DropTableTree *DropTabletree;
	ShowTableTree *ShowTabletree;
	ShowTableSTree *ShowTableStree;

	CreateIndexTree *CreateIndextree;
	DropIndexTree *DropIndextree;

	AddPrimaryTree *AddPrimarytree;
	DropPrimaryTree *DropPrimarytree;
	AddForeignTree *AddForeigntree;
	DropForeignTree *DropForeigntree;
	AddAttributeTree *AddAttributetree;
	DropAttributeTree *DropAttributetree;
	TableRenameTree *TableRenametree;

	InsertTree *Inserttree;
	DeleteTree *Deletetree;
	UpdateTree *Updatetree;
	SelectTree *Selecttree;

	WhereClausesTree *WhereClausestree;
	conditionsTree *conditionstree;
	comparisonTree *comparisontree;		
	exprTree *exprtree;
	columnTree *columntree;
	columnlistTree *columnlisttree;
	tablelistTree *tablelisttree;	
	setClauselistTree *setClauselisttree;
	setClauseTree *setClausetree;

	attributelistTree *attributelisttree;
	attributeTree *attributetree;
	typeTree *typetree;
	valuelistsTree *valueliststree;
	valuelistTree *valuelisttree;
	valueTree *valuetree;	

	opName opname;



/* Line 214 of yacc.c  */
#line 230 "Parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 242 "Parser.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  33
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   212

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNRULES -- Number of states.  */
#define YYNSTATES  192

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    51,     2,     2,
      43,    44,    49,    47,    46,    48,    63,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    45,
       2,    64,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,    10,    14,    18,    22,    26,    29,
      32,    39,    43,    47,    50,    59,    63,    73,    80,    95,
     105,   111,   117,   124,   130,   135,   141,   147,   153,   156,
     157,   159,   163,   167,   171,   176,   178,   182,   184,   188,
     192,   194,   196,   198,   202,   206,   210,   214,   218,   220,
     222,   224,   226,   228,   230,   232,   236,   240,   242,   246,
     249,   254,   259,   266,   270,   279,   281,   283,   288,   290,
     292,   294,   301,   305,   311,   313,   317,   319,   321,   323
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      66,     0,    -1,    67,    45,    -1,    66,    67,    45,    -1,
       3,     9,    58,    -1,     4,     9,    58,    -1,     5,     9,
      58,    -1,     6,     9,    58,    -1,     6,    10,    -1,     7,
      58,    -1,     3,    11,    58,    43,    78,    44,    -1,     4,
      11,    58,    -1,     6,    11,    58,    -1,     6,    12,    -1,
       3,    13,    58,    33,    58,    43,    58,    44,    -1,     4,
      13,    58,    -1,    14,    11,    58,     8,    27,    29,    43,
      58,    44,    -1,    14,    11,    58,     4,    27,    29,    -1,
      14,    11,    58,     8,    28,    29,    43,    58,    44,    30,
      58,    43,    58,    44,    -1,    14,    11,    58,     4,    28,
      29,    43,    58,    44,    -1,    14,    11,    58,     8,    79,
      -1,    14,    11,    58,     4,    58,    -1,    14,    11,    58,
      31,    32,    58,    -1,    15,    16,    58,    17,    81,    -1,
      18,    19,    58,    68,    -1,    20,    58,    35,    76,    68,
      -1,    21,    72,    19,    71,    68,    -1,    21,    49,    19,
      71,    68,    -1,    22,    69,    -1,    -1,    70,    -1,    69,
      34,    70,    -1,    73,    75,    74,    -1,    73,    23,    25,
      -1,    73,    23,    24,    25,    -1,    58,    -1,    71,    46,
      58,    -1,    73,    -1,    72,    46,    73,    -1,    58,    63,
      58,    -1,    58,    -1,    83,    -1,    73,    -1,    74,    47,
      74,    -1,    74,    48,    74,    -1,    74,    49,    74,    -1,
      74,    50,    74,    -1,    74,    51,    74,    -1,    52,    -1,
      53,    -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,
      77,    -1,    76,    46,    77,    -1,    73,    64,    74,    -1,
      79,    -1,    78,    46,    79,    -1,    58,    80,    -1,    58,
      80,    24,    25,    -1,    58,    80,    26,    83,    -1,    58,
      80,    24,    25,    26,    83,    -1,    27,    29,    58,    -1,
      28,    29,    58,    30,    58,    43,    58,    44,    -1,    36,
      -1,    37,    -1,    38,    43,    60,    44,    -1,    39,    -1,
      40,    -1,    41,    -1,    42,    43,    60,    46,    60,    44,
      -1,    43,    82,    44,    -1,    81,    46,    43,    82,    44,
      -1,    83,    -1,    82,    46,    83,    -1,    59,    -1,    60,
      -1,    61,    -1,    62,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   100,   100,   103,   108,   114,   120,   126,   132,   137,
     144,   150,   156,   162,   168,   174,   181,   187,   193,   199,
     205,   211,   217,   224,   230,   236,   242,   247,   254,   257,
     261,   265,   269,   272,   275,   279,   284,   289,   293,   297,
     301,   306,   309,   312,   315,   318,   321,   324,   328,   331,
     334,   337,   340,   343,   347,   351,   355,   360,   364,   368,
     372,   376,   380,   384,   388,   394,   397,   400,   403,   406,
     409,   412,   417,   421,   426,   430,   434,   438,   442,   446
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CREATE", "DROP", "USE", "SHOW", "DESC",
  "ADD", "DATABASE", "DATABASES", "TABLE", "TABLES", "INDEX", "ALTER",
  "INSERT", "INTO", "VALUES", "DELETEC", "FROM", "UPDATE", "SELECT",
  "WHERE", "IS", "NOT", "NULLC", "DEFAULT", "PRIMARY", "FOREIGN", "KEY",
  "REFERENCES", "RENAME", "TO", "ON", "AND", "SET", "INTEGER", "SMALLINT",
  "CHARTYPE", "DOUBLETYPE", "FLOATTYPE", "DATETYPE", "NUMERICTYPE", "'('",
  "')'", "';'", "','", "'+'", "'-'", "'*'", "'/'", "'%'", "EQ", "GT", "LT",
  "GE", "LE", "NE", "NAME", "TEXT", "INUM", "FNUM", "DATENUM", "'.'",
  "'='", "$accept", "sql", "command", "whereClauses", "conditions",
  "comparison", "tablelist", "columnlist", "column", "expr", "op",
  "setClauselist", "setClause", "attributelist", "attribute", "type",
  "valuelists", "valuelist", "value", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    40,    41,    59,    44,    43,    45,    42,
      47,    37,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,    46,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    68,    68,
      69,    69,    70,    70,    70,    71,    71,    72,    72,    73,
      73,    74,    74,    74,    74,    74,    74,    74,    75,    75,
      75,    75,    75,    75,    76,    76,    77,    78,    78,    79,
      79,    79,    79,    79,    79,    80,    80,    80,    80,    80,
      80,    80,    81,    81,    82,    82,    83,    83,    83,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     3,     3,     3,     3,     2,     2,
       6,     3,     3,     2,     8,     3,     9,     6,    14,     9,
       5,     5,     6,     5,     4,     5,     5,     5,     2,     0,
       1,     3,     3,     3,     4,     1,     3,     1,     3,     3,
       1,     1,     1,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     1,     3,     2,
       4,     4,     6,     3,     8,     1,     1,     4,     1,     1,
       1,     6,     3,     5,     1,     3,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     8,     0,    13,     9,     0,     0,     0,     0,     0,
      40,     0,    37,     1,     0,     2,     4,     0,     0,     5,
      11,    15,     6,     7,    12,     0,     0,    29,     0,     0,
       0,     0,     0,     3,     0,     0,     0,     0,     0,     0,
       0,    24,     0,    29,    54,    35,    29,    39,    29,    38,
       0,     0,     0,     0,    57,     0,     0,     0,    21,     0,
       0,    20,     0,     0,    23,    28,    30,     0,     0,     0,
      25,     0,    27,    26,     0,     0,    65,    66,     0,    68,
      69,    70,     0,    59,    10,     0,     0,    17,     0,     0,
       0,    22,    76,    77,    78,    79,     0,    74,     0,     0,
       0,    48,    49,    50,    51,    52,    53,     0,    42,    56,
      41,    55,    36,    63,     0,     0,     0,     0,     0,    58,
       0,     0,     0,     0,    72,     0,     0,    31,     0,    33,
      32,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      61,    14,     0,     0,     0,    75,     0,    34,    43,    44,
      45,    46,    47,     0,    67,     0,     0,    19,    16,     0,
      73,     0,     0,    62,     0,     0,    71,     0,    64,     0,
       0,    18
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    61,    85,    86,    66,    31,   128,   129,
     127,    63,    64,    73,    74,   103,    84,   116,   130
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -108
static const yytype_int16 yypact[] =
{
      77,    97,   107,    -4,   112,   -43,    13,    11,    34,     4,
     -42,    54,    -8,    12,    19,    35,    38,    49,    74,    75,
      76,  -108,    78,  -108,  -108,    79,    80,    81,    55,   116,
      68,     6,  -108,  -108,    95,  -108,  -108,    98,   109,  -108,
    -108,  -108,  -108,  -108,  -108,    18,   126,   122,    87,    88,
      89,    88,    87,  -108,   -19,    90,   -17,   -15,   117,   108,
      87,  -108,    86,   -18,  -108,  -108,   -16,  -108,   -16,  -108,
     123,   124,    63,   -27,  -108,   111,   127,   128,  -108,   129,
     130,  -108,   102,    66,   115,   121,  -108,   -21,    27,    87,
    -108,   104,  -108,  -108,   106,   110,  -108,  -108,   120,  -108,
    -108,  -108,   131,    47,  -108,   -19,   113,  -108,   132,   -29,
      -3,  -108,  -108,  -108,  -108,  -108,    32,  -108,   133,    87,
     105,  -108,  -108,  -108,  -108,  -108,  -108,    27,  -108,    64,
    -108,  -108,  -108,  -108,   135,   118,   119,   141,    66,  -108,
     125,   114,   134,   136,  -108,    66,    66,  -108,   142,  -108,
      64,    27,    27,    27,    27,    27,   137,   138,   139,   144,
    -108,  -108,   140,   143,   145,  -108,    73,  -108,    16,    16,
    -108,  -108,  -108,   147,  -108,   146,    66,  -108,  -108,   150,
    -108,   149,   152,  -108,   151,   153,  -108,   148,  -108,   154,
     155,  -108
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -108,  -108,   162,   -45,  -108,    58,   157,  -108,   -10,  -107,
    -108,  -108,    92,  -108,   -54,  -108,  -108,    37,   -82
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      32,   117,   120,    81,    60,    19,    60,    29,    70,    71,
      76,    77,    79,    80,   142,    24,    30,   104,    90,   105,
     150,    92,    56,    93,    25,    51,    57,    26,    89,   133,
      91,   121,   122,   123,   124,   125,   126,    35,    62,    72,
     143,    78,    69,    72,   168,   169,   170,   171,   172,    58,
      87,   139,    52,    27,    33,   134,   160,     1,     2,     3,
       4,     5,    28,   165,   117,   153,   154,   155,     6,     7,
      36,   137,     8,   138,     9,    10,   144,    37,   145,    62,
       1,     2,     3,     4,     5,    30,   112,   113,   114,   115,
      48,     6,     7,    38,   183,     8,    39,     9,    10,    96,
      97,    98,    99,   100,   101,   102,    13,    40,    14,    87,
      15,   151,   152,   153,   154,   155,    16,   180,    17,   145,
      18,    20,    21,    22,    23,   112,   113,   114,   115,   148,
     149,    50,    41,    42,    43,    49,    44,    45,    46,    47,
      53,    54,    55,    59,    60,    30,    65,    67,    75,    82,
      88,    83,    94,    95,   106,   119,   107,   108,   109,   110,
     111,   118,   132,   135,   133,   156,   159,   167,   134,   161,
     176,   140,   162,    34,   136,   141,   146,   147,   157,   158,
     184,   131,   174,   166,   177,   175,     0,   178,     0,   179,
     181,   189,   163,     0,   164,   173,   186,   188,     0,   191,
       0,     0,     0,     0,     0,     0,   182,   185,    68,   187,
       0,     0,   190
};

static const yytype_int16 yycheck[] =
{
      10,    83,    23,    57,    22,     9,    22,    49,    27,    28,
      27,    28,    27,    28,    43,    58,    58,    44,    63,    46,
     127,    66,     4,    68,    11,    19,     8,    16,    46,    58,
      46,    52,    53,    54,    55,    56,    57,    45,    48,    58,
      43,    58,    52,    58,   151,   152,   153,   154,   155,    31,
      60,   105,    46,    19,     0,    58,   138,     3,     4,     5,
       6,     7,    58,   145,   146,    49,    50,    51,    14,    15,
      58,    24,    18,    26,    20,    21,    44,    58,    46,    89,
       3,     4,     5,     6,     7,    58,    59,    60,    61,    62,
      35,    14,    15,    58,   176,    18,    58,    20,    21,    36,
      37,    38,    39,    40,    41,    42,     9,    58,    11,   119,
      13,    47,    48,    49,    50,    51,     9,    44,    11,    46,
      13,     9,    10,    11,    12,    59,    60,    61,    62,    24,
      25,    63,    58,    58,    58,    19,    58,    58,    58,    58,
      45,    43,    33,    17,    22,    58,    58,    58,    58,    32,
      64,    43,    29,    29,    43,    34,    29,    29,    29,    29,
      58,    46,    58,    43,    58,    30,    25,    25,    58,    44,
      26,    58,    58,    11,    43,    43,    43,   119,    60,    60,
      30,    89,    44,   146,    44,    46,    -1,    44,    -1,    44,
      43,    43,    58,    -1,    58,    58,    44,    44,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    58,    51,    58,
      -1,    -1,    58
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    14,    15,    18,    20,
      21,    66,    67,     9,    11,    13,     9,    11,    13,     9,
       9,    10,    11,    12,    58,    11,    16,    19,    58,    49,
      58,    72,    73,     0,    67,    45,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    35,    19,
      63,    19,    46,    45,    43,    33,     4,     8,    31,    17,
      22,    68,    73,    76,    77,    58,    71,    58,    71,    73,
      27,    28,    58,    78,    79,    58,    27,    28,    58,    27,
      28,    79,    32,    43,    81,    69,    70,    73,    64,    46,
      68,    46,    68,    68,    29,    29,    36,    37,    38,    39,
      40,    41,    42,    80,    44,    46,    43,    29,    29,    29,
      29,    58,    59,    60,    61,    62,    82,    83,    46,    34,
      23,    52,    53,    54,    55,    56,    57,    75,    73,    74,
      83,    77,    58,    58,    58,    43,    43,    24,    26,    79,
      58,    43,    43,    43,    44,    46,    43,    70,    24,    25,
      74,    47,    48,    49,    50,    51,    30,    60,    60,    25,
      83,    44,    58,    58,    58,    83,    82,    25,    74,    74,
      74,    74,    74,    58,    44,    46,    26,    44,    44,    44,
      44,    43,    60,    83,    30,    58,    44,    58,    44,    43,
      58,    44
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 101 "Parser.y"
    {				
            ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 104 "Parser.y"
    {				
            ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 108 "Parser.y"
    {
			(yyval.tree)=new CreateDatabaseTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 114 "Parser.y"
    {
			(yyval.tree)=new DropDatabaseTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 120 "Parser.y"
    {
			(yyval.tree)=new UseDatabaseTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 126 "Parser.y"
    {
			(yyval.tree)=new ShowDatabaseTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 132 "Parser.y"
    {
			(yyval.tree)=new ShowDatabaseSTree();
			Tree::setInstance((yyval.tree));			
			Tree::run();
		;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 137 "Parser.y"
    {
			(yyval.tree)=new ShowDatabaseDescTree((yyvsp[(2) - (2)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(2) - (2)].string);
			Tree::run();
		;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 144 "Parser.y"
    {
			(yyval.tree)=new CreateTableTree((yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].attributelisttree));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (6)].string);
			Tree::run;			
		;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 150 "Parser.y"
    {
			(yyval.tree)=new DropTableTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 156 "Parser.y"
    {
			(yyval.tree)=new ShowTableTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 162 "Parser.y"
    {
			(yyval.tree)=new ShowTableSTree();
			Tree::setInstance((yyval.tree));			
			Tree::run();
		;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 168 "Parser.y"
    {
			(yyval.tree)=new CreateIndexTree((yyvsp[(3) - (8)].string),(yyvsp[(5) - (8)].string),(yyvsp[(7) - (8)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (8)].string),(yyvsp[(5) - (8)].string),(yyvsp[(7) - (8)].string);
			Tree::run();
		;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 174 "Parser.y"
    {
			(yyval.tree)=new DropIndexTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 181 "Parser.y"
    {
			(yyval.tree)=new AddPrimaryTree((yyvsp[(3) - (9)].string),(yyvsp[(8) - (9)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (9)].string),(yyvsp[(8) - (9)].string);
			Tree::run();
		;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 187 "Parser.y"
    {
			(yyval.tree)=new DropPrimaryTree((yyvsp[(3) - (6)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (6)].string);
			Tree::run();
		;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 193 "Parser.y"
    {
			(yyval.tree)=new AddForeignTree((yyvsp[(3) - (14)].string),(yyvsp[(8) - (14)].string),(yyvsp[(11) - (14)].string),(yyvsp[(13) - (14)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (14)].string),(yyvsp[(8) - (14)].string),(yyvsp[(11) - (14)].string),(yyvsp[(13) - (14)].string);
			Tree::run();
		;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 199 "Parser.y"
    {
			(yyval.tree)=new DropForeignTree((yyvsp[(3) - (9)].string),(yyvsp[(8) - (9)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (9)].string),(yyvsp[(8) - (9)].string);
			Tree::run();
		;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 205 "Parser.y"
    {
			(yyval.tree)=new AddAttributeTree((yyvsp[(3) - (5)].string),(yyvsp[(5) - (5)].attributetree));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (5)].string);
			Tree::run();
		;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 211 "Parser.y"
    {
			(yyval.tree)=new DropAttributeTree((yyvsp[(3) - (5)].string),(yyvsp[(5) - (5)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (5)].string),(yyvsp[(5) - (5)].string);
			Tree::run();
		;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 217 "Parser.y"
    {
			(yyval.tree)=new TableRenameTree((yyvsp[(3) - (6)].string),(yyvsp[(6) - (6)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (6)].string),(yyvsp[(6) - (6)].string);
			Tree::run();
		;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 224 "Parser.y"
    {
			(yyval.tree)=new InsertTree((yyvsp[(3) - (5)].string),(yyvsp[(5) - (5)].valueliststree));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (5)].string);
			Tree::run();
		;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 230 "Parser.y"
    {
			(yyval.tree)=new DeleteTree((yyvsp[(3) - (4)].string),(yyvsp[(4) - (4)].WhereClausestree));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (4)].string);
			Tree::run();
		;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 236 "Parser.y"
    {
			(yyval.tree)=new UpdateTree((yyvsp[(2) - (5)].string),(yyvsp[(4) - (5)].setClauselisttree),(yyvsp[(5) - (5)].WhereClausestree));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(2) - (5)].string);
			Tree::run();
		;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 242 "Parser.y"
    {
			(yyval.tree)=new SelectTree((yyvsp[(2) - (5)].columnlisttree),(yyvsp[(4) - (5)].tablelisttree),(yyvsp[(5) - (5)].WhereClausestree));
			Tree::setInstance((yyval.tree));			
			Tree::run();
		;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 247 "Parser.y"
    {
			(yyval.tree)=new SelectTree(nullptr,(yyvsp[(4) - (5)].tablelisttree),(yyvsp[(5) - (5)].WhereClausestree));
			Tree::setInstance((yyval.tree));			
			Tree::run();
		;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 254 "Parser.y"
    {
			(yyval.WhereClausestree)=new WhereClausesTree((yyvsp[(2) - (2)].conditionstree));
		;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 257 "Parser.y"
    {
			(yyval.WhereClausestree)=nullptr;
		;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 261 "Parser.y"
    {
			(yyval.conditionstree)=new conditionsTree();
			(yyval.conditionstree)->append((yyvsp[(1) - (1)].comparisontree));
		;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 265 "Parser.y"
    {
			(yyval.conditionstree)->append((yyvsp[(3) - (3)].comparisontree));
		;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 269 "Parser.y"
    {
			 (yyval.comparisontree)=new comparisonTree((yyvsp[(1) - (3)].columntree),(yyvsp[(2) - (3)].opname),(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 272 "Parser.y"
    {
			(yyval.comparisontree)=new comparisonTree((yyvsp[(1) - (3)].columntree),opName::INULL,nullptr);
		;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 275 "Parser.y"
    {
			(yyval.comparisontree)=new comparisonTree((yyvsp[(1) - (4)].columntree),opName::NNULL,nullptr);
		;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 279 "Parser.y"
    {		
			(yyval.tablelisttree)=new tablelistTree();
			(yyval.tablelisttree)->append((yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 284 "Parser.y"
    {			
			(yyval.tablelisttree)->append((yyvsp[(3) - (3)].string));
			delete (yyvsp[(3) - (3)].string);
		;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 289 "Parser.y"
    {		
			(yyval.columnlisttree)=new columnlistTree();
			(yyval.columnlisttree)->append((yyvsp[(1) - (1)].columntree));
		;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 293 "Parser.y"
    {			
			(yyval.columnlisttree)->append((yyvsp[(3) - (3)].columntree));
		;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 297 "Parser.y"
    {
			(yyval.columntree)=new columnTree((yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string));
			delete (yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string);
		;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 301 "Parser.y"
    {
			(yyval.columntree)=new columnTree((yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 306 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (1)].valuetree));
		;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 309 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (1)].columntree));
		;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 312 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::ADD,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 315 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::MINUS,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 318 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::MULTI,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 321 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::DIV,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 324 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::MODC,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 328 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 331 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 334 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 337 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 340 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 343 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 347 "Parser.y"
    {
			(yyval.setClauselisttree)=new setClauselistTree();
			(yyval.setClauselisttree)->append((yyvsp[(1) - (1)].setClausetree));
		;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 351 "Parser.y"
    {
			(yyval.setClauselisttree)->append((yyvsp[(3) - (3)].setClausetree));
		;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 355 "Parser.y"
    {
			(yyval.setClausetree)=new setClauseTree((yyvsp[(1) - (3)].columntree),(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 360 "Parser.y"
    {		
			(yyval.attributelisttree)=new attributelistTree();
			(yyval.attributelisttree)->append((yyvsp[(1) - (1)].attributetree));
		;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 364 "Parser.y"
    {			
			(yyval.attributelisttree)->append((yyvsp[(3) - (3)].attributetree));
		;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 368 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree((yyvsp[(1) - (2)].string),(yyvsp[(2) - (2)].typetree),false,false);
			delete (yyvsp[(1) - (2)].string);
		;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 372 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree((yyvsp[(1) - (4)].string),(yyvsp[(2) - (4)].typetree),true,false);
			delete (yyvsp[(1) - (4)].string);
		;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 376 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree((yyvsp[(1) - (4)].string),(yyvsp[(2) - (4)].typetree),false,true,(yyvsp[(4) - (4)].valuetree));
			delete (yyvsp[(1) - (4)].string),(yyvsp[(4) - (4)].valuetree);
		;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 380 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree((yyvsp[(1) - (6)].string),(yyvsp[(2) - (6)].typetree),true,true,(yyvsp[(6) - (6)].valuetree));
			delete (yyvsp[(1) - (6)].string),(yyvsp[(6) - (6)].valuetree);
		;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 384 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree(KeyName::Primary,(yyvsp[(3) - (3)].string));
			delete (yyvsp[(3) - (3)].string);
		;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 388 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree(KeyName::Foreign,(yyvsp[(3) - (8)].string),(yyvsp[(5) - (8)].string),(yyvsp[(7) - (8)].string));
			delete (yyvsp[(3) - (8)].string),(yyvsp[(5) - (8)].string),(yyvsp[(7) - (8)].string);
		;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 394 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Int);
		;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 397 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::SmallInt);
		;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 400 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Char,(yyvsp[(3) - (4)].string));			
		;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 403 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Double);
		;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 406 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Float);
		;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 409 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Date);
		;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 412 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Numeric,(yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].string));
		;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 417 "Parser.y"
    {
			(yyval.valueliststree)=new valuelistsTree();
			(yyval.valueliststree)->append((yyvsp[(2) - (3)].valuelisttree));
		;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 421 "Parser.y"
    {
			(yyval.valueliststree)->append((yyvsp[(4) - (5)].valuelisttree));
		;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 426 "Parser.y"
    {
			(yyval.valuelisttree)=new valuelistTree();
			(yyval.valuelisttree)->append((yyvsp[(1) - (1)].valuetree));
		;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 430 "Parser.y"
    {
			(yyval.valuelisttree)->append((yyvsp[(3) - (3)].valuetree));
		;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 434 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::TEXT,(yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 438 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::INUM,(yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 442 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::FNUM,(yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 446 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::DATENUM,(yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;



/* Line 1455 of yacc.c  */
#line 2390 "Parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



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
		      yytoken, &yylval);
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 452 "Parser.y"


/*支撑函数节  规则节用到的局部 C 函数定义,可选*/
void yyerror(const char *msg) {
    printf("YACC error: %s\n", msg);
}
int parseFile(){//程序主函数，读取命令，执行输出
	bool instd=true;	
	char* inputname="input.txt";	
	FILE  *fin;	
	extern FILE *yyin;	
	if (instd){
		fin = fopen(inputname, "r"); 
		yyin=fin;
		printf("input name is %s\n",inputname);
	}else
		printf("input is stdin\n");	
	printf("parse Begin!\n");	
	yyparse();	
	printf("\n");
	printf("parse End!\n");
	if (instd)fclose(fin);    
	return 0;
}

int main() {	
	parseFile();
	system("pause");
	return 0;
}
