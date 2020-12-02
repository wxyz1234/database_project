
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
#include "../parser/tree.h"
#include "../parser/Lexer.cpp"
#include <string>
#include "../RecordManageSystem/RecordManager.h"

void yyerror(const char *);
int yylex(void); 
int parseFile();
std::string CurrentDatabase = "";
RecordManager* rm = new RecordManager();


/* Line 189 of yacc.c  */
#line 89 "Parser.c"

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
#line 18 "Parser.y"

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
#line 232 "Parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 244 "Parser.c"

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
#define YYLAST   200

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  184

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
      32,    39,    43,    47,    50,    59,    63,    69,    76,    86,
      92,    99,   105,   110,   116,   122,   128,   131,   132,   134,
     138,   142,   146,   151,   153,   157,   159,   163,   167,   169,
     171,   173,   177,   181,   185,   189,   193,   195,   197,   199,
     201,   203,   205,   207,   211,   215,   217,   221,   224,   229,
     234,   241,   247,   258,   263,   265,   270,   272,   274,   276,
     283,   287,   293,   295,   299,   301,   303,   305
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
      13,    58,    -1,    14,    11,    58,     8,    79,    -1,    14,
      11,    58,     4,    27,    29,    -1,    14,    11,    58,     4,
      28,    29,    43,    58,    44,    -1,    14,    11,    58,     4,
      58,    -1,    14,    11,    58,    31,    32,    58,    -1,    15,
      16,    58,    17,    81,    -1,    18,    19,    58,    68,    -1,
      20,    58,    35,    76,    68,    -1,    21,    72,    19,    71,
      68,    -1,    21,    49,    19,    71,    68,    -1,    22,    69,
      -1,    -1,    70,    -1,    69,    34,    70,    -1,    73,    75,
      74,    -1,    73,    23,    25,    -1,    73,    23,    24,    25,
      -1,    58,    -1,    71,    46,    58,    -1,    73,    -1,    72,
      46,    73,    -1,    58,    63,    58,    -1,    58,    -1,    83,
      -1,    73,    -1,    74,    47,    74,    -1,    74,    48,    74,
      -1,    74,    49,    74,    -1,    74,    50,    74,    -1,    74,
      51,    74,    -1,    52,    -1,    53,    -1,    54,    -1,    55,
      -1,    56,    -1,    57,    -1,    77,    -1,    76,    46,    77,
      -1,    73,    64,    74,    -1,    79,    -1,    78,    46,    79,
      -1,    58,    80,    -1,    58,    80,    24,    25,    -1,    58,
      80,    26,    83,    -1,    58,    80,    24,    25,    26,    83,
      -1,    27,    29,    43,    58,    44,    -1,    28,    29,    43,
      58,    44,    30,    58,    43,    58,    44,    -1,    36,    43,
      60,    44,    -1,    37,    -1,    38,    43,    60,    44,    -1,
      39,    -1,    40,    -1,    41,    -1,    42,    43,    60,    46,
      60,    44,    -1,    43,    82,    44,    -1,    81,    46,    43,
      82,    44,    -1,    83,    -1,    82,    46,    83,    -1,    59,
      -1,    60,    -1,    61,    -1,    62,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   102,   102,   105,   110,   116,   122,   128,   134,   139,
     146,   152,   158,   164,   170,   176,   182,   188,   194,   200,
     206,   213,   219,   225,   231,   236,   243,   246,   250,   254,
     258,   261,   264,   268,   273,   278,   282,   286,   290,   295,
     298,   301,   304,   307,   310,   313,   317,   320,   323,   326,
     329,   332,   336,   340,   344,   349,   353,   357,   361,   365,
     369,   373,   377,   383,   386,   389,   392,   395,   398,   401,
     406,   410,   415,   419,   423,   427,   431,   435
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
      67,    67,    67,    67,    67,    67,    68,    68,    69,    69,
      70,    70,    70,    71,    71,    72,    72,    73,    73,    74,
      74,    74,    74,    74,    74,    74,    75,    75,    75,    75,
      75,    75,    76,    76,    77,    78,    78,    79,    79,    79,
      79,    79,    79,    80,    80,    80,    80,    80,    80,    80,
      81,    81,    82,    82,    83,    83,    83,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     3,     3,     3,     3,     2,     2,
       6,     3,     3,     2,     8,     3,     5,     6,     9,     5,
       6,     5,     4,     5,     5,     5,     2,     0,     1,     3,
       3,     3,     4,     1,     3,     1,     3,     3,     1,     1,
       1,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     3,     2,     4,     4,
       6,     5,    10,     4,     1,     4,     1,     1,     1,     6,
       3,     5,     1,     3,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     8,     0,    13,     9,     0,     0,     0,     0,     0,
      38,     0,    35,     1,     0,     2,     4,     0,     0,     5,
      11,    15,     6,     7,    12,     0,     0,    27,     0,     0,
       0,     0,     0,     3,     0,     0,     0,     0,     0,     0,
       0,    22,     0,    27,    52,    33,    27,    37,    27,    36,
       0,     0,     0,     0,    55,     0,     0,     0,    19,    16,
       0,     0,    21,    26,    28,     0,     0,     0,    23,     0,
      25,    24,     0,     0,     0,    64,     0,    66,    67,    68,
       0,    57,    10,     0,     0,    17,     0,    20,    74,    75,
      76,    77,     0,    72,     0,     0,     0,    46,    47,    48,
      49,    50,    51,     0,    40,    54,    39,    53,    34,     0,
       0,     0,     0,     0,     0,     0,    56,     0,     0,    70,
       0,     0,    29,     0,    31,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,    59,    14,     0,
      73,     0,    32,    41,    42,    43,    44,    45,    61,     0,
      63,    65,     0,     0,    18,    71,     0,     0,    60,     0,
      69,     0,     0,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    11,    12,    61,    83,    84,    66,    31,   124,   125,
     123,    63,    64,    73,    74,   101,    82,   112,   126
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -120
static const yytype_int16 yypact[] =
{
      83,   104,   105,     3,    47,   -43,     8,     2,    27,   -11,
     -44,    64,    17,    22,    33,    34,    41,    65,    66,    67,
      68,  -120,    69,  -120,  -120,    71,    72,    73,    31,   109,
      74,    -3,  -120,  -120,    87,  -120,  -120,    90,   101,  -120,
    -120,  -120,  -120,  -120,  -120,     9,   118,   114,    80,    81,
      82,    81,    80,  -120,   -19,    84,   -17,   -19,   111,    98,
      80,  -120,    85,    -2,  -120,  -120,    -1,  -120,    -1,  -120,
     115,   116,    70,     7,  -120,   103,   119,   121,  -120,  -120,
      89,    60,   106,   117,  -120,   -20,   -36,    80,  -120,    95,
    -120,  -120,   112,   113,   120,  -120,   122,  -120,  -120,  -120,
     123,    39,  -120,   -19,    96,  -120,   124,  -120,  -120,  -120,
    -120,  -120,    37,  -120,   125,    80,   -18,  -120,  -120,  -120,
    -120,  -120,  -120,   -36,  -120,    25,  -120,  -120,  -120,    99,
     100,   102,   110,   126,   134,    60,  -120,   127,   129,  -120,
      60,    60,  -120,   135,  -120,    25,   -36,   -36,   -36,   -36,
     -36,   128,   130,   131,   132,   133,   138,  -120,  -120,   136,
    -120,    56,  -120,    45,    45,  -120,  -120,  -120,  -120,   139,
    -120,  -120,   137,    60,  -120,  -120,   140,   141,  -120,   145,
    -120,   142,   146,  -120
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -120,  -120,   150,   -14,  -120,    58,   143,  -120,   -10,  -119,
    -120,  -120,    91,  -120,   -55,  -120,  -120,    36,   -80
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      32,   113,    79,   116,   145,    29,   143,   144,    70,    71,
      76,    77,    19,    56,    30,    24,    51,    57,    26,    25,
      60,    60,    30,   108,   109,   110,   111,   163,   164,   165,
     166,   167,   117,   118,   119,   120,   121,   122,    62,    72,
      58,    78,    69,    52,    87,    89,    27,    28,   136,    88,
      85,   102,    90,   103,    91,   157,    20,    21,    22,    23,
     160,   113,    35,   134,    33,   135,    48,     1,     2,     3,
       4,     5,   146,   147,   148,   149,   150,    62,     6,     7,
      36,   139,     8,   140,     9,    10,     1,     2,     3,     4,
       5,    37,    38,   178,   148,   149,   150,     6,     7,    39,
     175,     8,   140,     9,    10,    85,    94,    95,    96,    97,
      98,    99,   100,    13,    16,    14,    17,    15,    18,   108,
     109,   110,   111,    40,    41,    42,    43,    44,    49,    45,
      46,    47,    53,    54,    55,    59,    60,    50,    30,    65,
      67,    81,    75,    80,    92,    93,   104,   107,   105,    86,
     106,   115,   114,   128,   137,   129,   130,   151,   152,   156,
     162,    34,   153,   131,   173,   132,   133,   138,   141,   176,
     154,   158,   168,   142,   169,   170,   171,   161,   127,   172,
     174,     0,     0,     0,     0,   180,   155,   159,   181,     0,
     183,     0,     0,     0,    68,     0,     0,   177,   179,     0,
     182
};

static const yytype_int16 yycheck[] =
{
      10,    81,    57,    23,   123,    49,    24,    25,    27,    28,
      27,    28,     9,     4,    58,    58,    19,     8,    16,    11,
      22,    22,    58,    59,    60,    61,    62,   146,   147,   148,
     149,   150,    52,    53,    54,    55,    56,    57,    48,    58,
      31,    58,    52,    46,    46,    46,    19,    58,   103,    63,
      60,    44,    66,    46,    68,   135,     9,    10,    11,    12,
     140,   141,    45,    24,     0,    26,    35,     3,     4,     5,
       6,     7,    47,    48,    49,    50,    51,    87,    14,    15,
      58,    44,    18,    46,    20,    21,     3,     4,     5,     6,
       7,    58,    58,   173,    49,    50,    51,    14,    15,    58,
      44,    18,    46,    20,    21,   115,    36,    37,    38,    39,
      40,    41,    42,     9,     9,    11,    11,    13,    13,    59,
      60,    61,    62,    58,    58,    58,    58,    58,    19,    58,
      58,    58,    45,    43,    33,    17,    22,    63,    58,    58,
      58,    43,    58,    32,    29,    29,    43,    58,    29,    64,
      29,    34,    46,    58,    58,    43,    43,    58,    58,    25,
      25,    11,    60,    43,    26,    43,    43,    43,    43,    30,
      60,    44,    44,   115,    44,    44,    44,   141,    87,    46,
      44,    -1,    -1,    -1,    -1,    44,    60,    58,    43,    -1,
      44,    -1,    -1,    -1,    51,    -1,    -1,    60,    58,    -1,
      58
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
      27,    28,    58,    78,    79,    58,    27,    28,    58,    79,
      32,    43,    81,    69,    70,    73,    64,    46,    68,    46,
      68,    68,    29,    29,    36,    37,    38,    39,    40,    41,
      42,    80,    44,    46,    43,    29,    29,    58,    59,    60,
      61,    62,    82,    83,    46,    34,    23,    52,    53,    54,
      55,    56,    57,    75,    73,    74,    83,    77,    58,    43,
      43,    43,    43,    43,    24,    26,    79,    58,    43,    44,
      46,    43,    70,    24,    25,    74,    47,    48,    49,    50,
      51,    58,    58,    60,    60,    60,    25,    83,    44,    58,
      83,    82,    25,    74,    74,    74,    74,    74,    44,    44,
      44,    44,    46,    26,    44,    44,    30,    60,    83,    58,
      44,    43,    58,    44
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
#line 103 "Parser.y"
    {				
            ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 106 "Parser.y"
    {				
            ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 110 "Parser.y"
    {
			(yyval.tree)=new CreateDatabaseTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 116 "Parser.y"
    {
			(yyval.tree)=new DropDatabaseTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 122 "Parser.y"
    {
			(yyval.tree)=new UseDatabaseTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 128 "Parser.y"
    {
			(yyval.tree)=new ShowDatabaseTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 134 "Parser.y"
    {
			(yyval.tree)=new ShowDatabaseSTree();
			Tree::setInstance((yyval.tree));			
			Tree::run();
		;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 139 "Parser.y"
    {
			(yyval.tree)=new ShowDatabaseDescTree((yyvsp[(2) - (2)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(2) - (2)].string);
			Tree::run();
		;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 146 "Parser.y"
    {
			(yyval.tree)=new CreateTableTree((yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].attributelisttree));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (6)].string);
			Tree::run;			
		;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 152 "Parser.y"
    {
			(yyval.tree)=new DropTableTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 158 "Parser.y"
    {
			(yyval.tree)=new ShowTableTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 164 "Parser.y"
    {
			(yyval.tree)=new ShowTableSTree();
			Tree::setInstance((yyval.tree));			
			Tree::run();
		;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 170 "Parser.y"
    {
			(yyval.tree)=new CreateIndexTree((yyvsp[(3) - (8)].string),(yyvsp[(5) - (8)].string),(yyvsp[(7) - (8)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (8)].string),(yyvsp[(5) - (8)].string),(yyvsp[(7) - (8)].string);
			Tree::run();
		;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 176 "Parser.y"
    {
			(yyval.tree)=new DropIndexTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 182 "Parser.y"
    {
			(yyval.tree)=new AddAttributeTree((yyvsp[(3) - (5)].string),(yyvsp[(5) - (5)].attributetree));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (5)].string);
			Tree::run();
		;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 188 "Parser.y"
    {
			(yyval.tree)=new DropPrimaryTree((yyvsp[(3) - (6)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (6)].string);
			Tree::run();
		;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 194 "Parser.y"
    {
			(yyval.tree)=new DropForeignTree((yyvsp[(3) - (9)].string),(yyvsp[(8) - (9)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (9)].string),(yyvsp[(8) - (9)].string);
			Tree::run();
		;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 200 "Parser.y"
    {
			(yyval.tree)=new DropAttributeTree((yyvsp[(3) - (5)].string),(yyvsp[(5) - (5)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (5)].string),(yyvsp[(5) - (5)].string);
			Tree::run();
		;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 206 "Parser.y"
    {
			(yyval.tree)=new TableRenameTree((yyvsp[(3) - (6)].string),(yyvsp[(6) - (6)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (6)].string),(yyvsp[(6) - (6)].string);
			Tree::run();
		;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 213 "Parser.y"
    {
			(yyval.tree)=new InsertTree((yyvsp[(3) - (5)].string),(yyvsp[(5) - (5)].valueliststree));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (5)].string);
			Tree::run();
		;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 219 "Parser.y"
    {
			(yyval.tree)=new DeleteTree((yyvsp[(3) - (4)].string),(yyvsp[(4) - (4)].WhereClausestree));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (4)].string);
			Tree::run();
		;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 225 "Parser.y"
    {
			(yyval.tree)=new UpdateTree((yyvsp[(2) - (5)].string),(yyvsp[(4) - (5)].setClauselisttree),(yyvsp[(5) - (5)].WhereClausestree));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(2) - (5)].string);
			Tree::run();
		;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 231 "Parser.y"
    {
			(yyval.tree)=new SelectTree((yyvsp[(2) - (5)].columnlisttree),(yyvsp[(4) - (5)].tablelisttree),(yyvsp[(5) - (5)].WhereClausestree));
			Tree::setInstance((yyval.tree));			
			Tree::run();
		;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 236 "Parser.y"
    {
			(yyval.tree)=new SelectTree(nullptr,(yyvsp[(4) - (5)].tablelisttree),(yyvsp[(5) - (5)].WhereClausestree));
			Tree::setInstance((yyval.tree));			
			Tree::run();
		;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 243 "Parser.y"
    {
			(yyval.WhereClausestree)=new WhereClausesTree((yyvsp[(2) - (2)].conditionstree));
		;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 246 "Parser.y"
    {
			(yyval.WhereClausestree)=nullptr;
		;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 250 "Parser.y"
    {
			(yyval.conditionstree)=new conditionsTree();
			(yyval.conditionstree)->append((yyvsp[(1) - (1)].comparisontree));
		;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 254 "Parser.y"
    {
			(yyval.conditionstree)->append((yyvsp[(3) - (3)].comparisontree));
		;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 258 "Parser.y"
    {
			 (yyval.comparisontree)=new comparisonTree((yyvsp[(1) - (3)].columntree),(yyvsp[(2) - (3)].opname),(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 261 "Parser.y"
    {
			(yyval.comparisontree)=new comparisonTree((yyvsp[(1) - (3)].columntree),opName::INULL,nullptr);
		;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 264 "Parser.y"
    {
			(yyval.comparisontree)=new comparisonTree((yyvsp[(1) - (4)].columntree),opName::NNULL,nullptr);
		;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 268 "Parser.y"
    {		
			(yyval.tablelisttree)=new tablelistTree();
			(yyval.tablelisttree)->append((yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 273 "Parser.y"
    {			
			(yyval.tablelisttree)->append((yyvsp[(3) - (3)].string));
			delete (yyvsp[(3) - (3)].string);
		;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 278 "Parser.y"
    {		
			(yyval.columnlisttree)=new columnlistTree();
			(yyval.columnlisttree)->append((yyvsp[(1) - (1)].columntree));
		;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 282 "Parser.y"
    {			
			(yyval.columnlisttree)->append((yyvsp[(3) - (3)].columntree));
		;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 286 "Parser.y"
    {
			(yyval.columntree)=new columnTree((yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string));
			delete (yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string);
		;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 290 "Parser.y"
    {
			(yyval.columntree)=new columnTree((yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 295 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (1)].valuetree));
		;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 298 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (1)].columntree));
		;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 301 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::ADD,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 304 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::MINUS,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 307 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::MULTI,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 310 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::DIV,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 313 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::MODC,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 317 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 320 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 323 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 326 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 329 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 332 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 336 "Parser.y"
    {
			(yyval.setClauselisttree)=new setClauselistTree();
			(yyval.setClauselisttree)->append((yyvsp[(1) - (1)].setClausetree));
		;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 340 "Parser.y"
    {
			(yyval.setClauselisttree)->append((yyvsp[(3) - (3)].setClausetree));
		;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 344 "Parser.y"
    {
			(yyval.setClausetree)=new setClauseTree((yyvsp[(1) - (3)].columntree),(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 349 "Parser.y"
    {		
			(yyval.attributelisttree)=new attributelistTree();
			(yyval.attributelisttree)->append((yyvsp[(1) - (1)].attributetree));
		;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 353 "Parser.y"
    {			
			(yyval.attributelisttree)->append((yyvsp[(3) - (3)].attributetree));
		;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 357 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree((yyvsp[(1) - (2)].string),(yyvsp[(2) - (2)].typetree),false,false);
			delete (yyvsp[(1) - (2)].string);
		;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 361 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree((yyvsp[(1) - (4)].string),(yyvsp[(2) - (4)].typetree),true,false);
			delete (yyvsp[(1) - (4)].string);
		;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 365 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree((yyvsp[(1) - (4)].string),(yyvsp[(2) - (4)].typetree),false,true,(yyvsp[(4) - (4)].valuetree));
			delete (yyvsp[(1) - (4)].string),(yyvsp[(4) - (4)].valuetree);
		;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 369 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree((yyvsp[(1) - (6)].string),(yyvsp[(2) - (6)].typetree),true,true,(yyvsp[(6) - (6)].valuetree));
			delete (yyvsp[(1) - (6)].string),(yyvsp[(6) - (6)].valuetree);
		;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 373 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree(KeyName::Primary,(yyvsp[(4) - (5)].string));
			delete (yyvsp[(4) - (5)].string);
		;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 377 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree(KeyName::Foreign,(yyvsp[(4) - (10)].string),(yyvsp[(7) - (10)].string),(yyvsp[(9) - (10)].string));
			delete (yyvsp[(4) - (10)].string),(yyvsp[(7) - (10)].string),(yyvsp[(9) - (10)].string);
		;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 383 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Int,(yyvsp[(3) - (4)].string));
		;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 386 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::SmallInt);
		;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 389 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Char,(yyvsp[(3) - (4)].string));			
		;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 392 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Double);
		;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 395 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Float);
		;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 398 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Date);
		;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 401 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Numeric,(yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].string));
		;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 406 "Parser.y"
    {
			(yyval.valueliststree)=new valuelistsTree();
			(yyval.valueliststree)->append((yyvsp[(2) - (3)].valuelisttree));
		;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 410 "Parser.y"
    {
			(yyval.valueliststree)->append((yyvsp[(4) - (5)].valuelisttree));
		;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 415 "Parser.y"
    {
			(yyval.valuelisttree)=new valuelistTree();
			(yyval.valuelisttree)->append((yyvsp[(1) - (1)].valuetree));
		;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 419 "Parser.y"
    {
			(yyval.valuelisttree)->append((yyvsp[(3) - (3)].valuetree));
		;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 423 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::TEXT,(yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 427 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::INUM,(yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 431 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::FNUM,(yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 435 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::DATENUM,(yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;



/* Line 1455 of yacc.c  */
#line 2361 "Parser.c"
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
#line 441 "Parser.y"


/*支撑函数节  规则节用到的局部 C 函数定义,可选*/
void yyerror(const char *msg) {
    printf("YACC error: %s\n", msg);
}
int parseFile(){//程序主函数，读取命令，执行输出
	bool instd=true;	
	//char* inputname = "./parser/input.txt";
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
	//system("pause");
	return 0;
}
