
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
#include "../RecordManageSystem/utils/Myhash.h"

void yyerror(const char *);
int yylex(void); 
int parseFile();

std::string CurrentDatabase = "";
RecordManager* rm = new RecordManager();
PrimaryData pd;
ForeignData fd;
int sumRID;


/* Line 189 of yacc.c  */
#line 94 "Parser.c"

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
     CONSTRAINT = 291,
     INTEGER = 292,
     SMALLINT = 293,
     CHARTYPE = 294,
     DOUBLETYPE = 295,
     FLOATTYPE = 296,
     DATETYPE = 297,
     NUMERICTYPE = 298,
     EQ = 299,
     GT = 300,
     LT = 301,
     GE = 302,
     LE = 303,
     NE = 304,
     NAME = 305,
     TEXT = 306,
     INUM = 307,
     FNUM = 308,
     DATENUM = 309
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 23 "Parser.y"

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
	
	AddPrimaryTree *AddPrimaryTree;
	AddForeignTree *AddForeignTree;
	DropPrimaryTree *DropPrimarytree;	
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
#line 239 "Parser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 251 "Parser.c"

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
#define YYFINAL  35
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   230

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNRULES -- Number of states.  */
#define YYNSTATES  206

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    52,     2,     2,
      44,    45,    50,    48,    47,    49,    53,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,    10,    14,    18,    21,    25,    28,
      32,    35,    42,    46,    50,    54,    57,    66,    70,    76,
      88,   105,   112,   120,   128,   134,   141,   147,   152,   158,
     164,   170,   173,   174,   176,   180,   184,   188,   193,   195,
     199,   201,   205,   209,   211,   213,   215,   219,   223,   227,
     231,   235,   237,   239,   241,   243,   245,   247,   249,   253,
     257,   259,   263,   266,   271,   276,   283,   289,   300,   305,
     307,   312,   314,   316,   318,   325,   329,   335,   337,   341,
     343,   345,   348,   350,   352
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      66,     0,    -1,    67,    46,    -1,    66,    67,    46,    -1,
       3,     9,    60,    -1,     4,     9,    60,    -1,     5,    60,
      -1,     6,     9,    60,    -1,     6,    10,    -1,     7,     9,
      60,    -1,     7,    60,    -1,     3,    11,    60,    44,    78,
      45,    -1,     4,    11,    60,    -1,     6,    11,    60,    -1,
       7,    11,    60,    -1,     6,    12,    -1,     3,    13,    60,
      33,    60,    44,    60,    45,    -1,     4,    13,    60,    -1,
      14,    11,    60,     8,    79,    -1,    14,    11,    60,     8,
      36,    60,    27,    29,    44,    72,    45,    -1,    14,    11,
      60,     8,    36,    60,    28,    29,    44,    72,    45,    30,
      60,    44,    72,    45,    -1,    14,    11,    60,     4,    27,
      29,    -1,    14,    11,    60,     4,    27,    29,    60,    -1,
      14,    11,    60,     4,    28,    29,    60,    -1,    14,    11,
      60,     4,    60,    -1,    14,    11,    60,    31,    32,    60,
      -1,    15,    16,    60,    17,    81,    -1,    18,    19,    60,
      68,    -1,    20,    60,    35,    76,    68,    -1,    21,    72,
      19,    71,    68,    -1,    21,    50,    19,    71,    68,    -1,
      22,    69,    -1,    -1,    70,    -1,    69,    34,    70,    -1,
      73,    75,    74,    -1,    73,    23,    25,    -1,    73,    23,
      24,    25,    -1,    60,    -1,    71,    47,    60,    -1,    73,
      -1,    72,    47,    73,    -1,    60,    53,    60,    -1,    60,
      -1,    83,    -1,    73,    -1,    74,    48,    74,    -1,    74,
      49,    74,    -1,    74,    50,    74,    -1,    74,    51,    74,
      -1,    74,    52,    74,    -1,    54,    -1,    55,    -1,    56,
      -1,    57,    -1,    58,    -1,    59,    -1,    77,    -1,    76,
      47,    77,    -1,    73,    54,    74,    -1,    79,    -1,    78,
      47,    79,    -1,    60,    80,    -1,    60,    80,    24,    25,
      -1,    60,    80,    26,    83,    -1,    60,    80,    24,    25,
      26,    83,    -1,    27,    29,    44,    60,    45,    -1,    28,
      29,    44,    60,    45,    30,    60,    44,    60,    45,    -1,
      37,    44,    62,    45,    -1,    38,    -1,    39,    44,    62,
      45,    -1,    40,    -1,    41,    -1,    42,    -1,    43,    44,
      62,    47,    62,    45,    -1,    44,    82,    45,    -1,    81,
      47,    44,    82,    45,    -1,    83,    -1,    82,    47,    83,
      -1,    61,    -1,    62,    -1,    49,    62,    -1,    63,    -1,
      64,    -1,    25,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   108,   108,   111,   116,   122,   128,   134,   140,   145,
     151,   158,   164,   170,   176,   182,   188,   194,   200,   206,
     212,   218,   224,   230,   236,   242,   249,   255,   261,   267,
     272,   279,   282,   286,   290,   294,   297,   300,   304,   309,
     314,   318,   322,   326,   331,   334,   337,   340,   343,   346,
     349,   353,   356,   359,   362,   365,   368,   372,   376,   380,
     385,   389,   393,   397,   401,   405,   409,   413,   419,   422,
     425,   428,   431,   434,   437,   442,   446,   451,   455,   459,
     463,   467,   471,   475,   479
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
  "REFERENCES", "RENAME", "TO", "ON", "AND", "SET", "CONSTRAINT",
  "INTEGER", "SMALLINT", "CHARTYPE", "DOUBLETYPE", "FLOATTYPE", "DATETYPE",
  "NUMERICTYPE", "'('", "')'", "';'", "','", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'.'", "EQ", "GT", "LT", "GE", "LE", "NE", "NAME", "TEXT", "INUM",
  "FNUM", "DATENUM", "$accept", "sql", "command", "whereClauses",
  "conditions", "comparison", "tablelist", "columnlist", "column", "expr",
  "op", "setClauselist", "setClause", "attributelist", "attribute", "type",
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
     295,   296,   297,   298,    40,    41,    59,    44,    43,    45,
      42,    47,    37,    46,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    68,    68,    69,    69,    70,    70,    70,    71,    71,
      72,    72,    73,    73,    74,    74,    74,    74,    74,    74,
      74,    75,    75,    75,    75,    75,    75,    76,    76,    77,
      78,    78,    79,    79,    79,    79,    79,    79,    80,    80,
      80,    80,    80,    80,    80,    81,    81,    82,    82,    83,
      83,    83,    83,    83,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     3,     3,     2,     3,     2,     3,
       2,     6,     3,     3,     3,     2,     8,     3,     5,    11,
      16,     6,     7,     7,     5,     6,     5,     4,     5,     5,
       5,     2,     0,     1,     3,     3,     3,     4,     1,     3,
       1,     3,     3,     1,     1,     1,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     3,     2,     4,     4,     6,     5,    10,     4,     1,
       4,     1,     1,     1,     6,     3,     5,     1,     3,     1,
       1,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
       0,     8,     0,    15,     0,     0,    10,     0,     0,     0,
       0,     0,    43,     0,    40,     1,     0,     2,     4,     0,
       0,     5,    12,    17,     7,    13,     9,    14,     0,     0,
      32,     0,     0,     0,     0,     0,     3,     0,     0,     0,
       0,     0,     0,     0,    27,     0,    32,    57,    38,    32,
      42,    32,    41,     0,     0,     0,     0,    60,     0,     0,
       0,    24,     0,    18,     0,     0,    26,    31,    33,     0,
       0,     0,    28,     0,    30,    29,     0,     0,     0,    69,
       0,    71,    72,    73,     0,    62,    11,     0,     0,    21,
       0,     0,    25,    84,     0,    79,    80,    82,    83,     0,
      77,     0,     0,     0,    51,    52,    53,    54,    55,    56,
       0,    45,    59,    44,    58,    39,     0,     0,     0,     0,
       0,     0,     0,    61,     0,    22,    23,     0,     0,    81,
      75,     0,     0,    34,     0,    36,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    63,    64,    16,
       0,     0,    78,     0,    37,    46,    47,    48,    49,    50,
      66,     0,    68,    70,     0,     0,     0,     0,    76,     0,
       0,    65,     0,     0,     0,    74,    19,     0,     0,     0,
       0,     0,    67,     0,     0,    20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    64,    87,    88,    69,    33,   131,   132,
     130,    66,    67,    76,    77,   105,    86,   119,   133
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -97
static const yytype_int16 yypact[] =
{
      99,   124,   125,   -52,   130,    -6,     4,     6,    46,    13,
     -33,    79,    34,    28,    32,    35,    55,    83,    85,   -97,
      86,   -97,    87,   -97,    88,    89,   -97,    90,    91,    92,
     109,   134,   101,   -13,   -97,   -97,   110,   -97,   -97,   111,
     126,   -97,   -97,   -97,   -97,   -97,   -97,   -97,    12,   140,
     136,   100,   102,   103,   102,   100,   -97,   -16,   104,   -14,
     -18,   129,   121,   100,   -97,   112,   -15,   -97,   -97,     3,
     -97,     3,   -97,   138,   139,    84,   -26,   -97,   127,   141,
     143,   -97,   113,   -97,   114,     8,   122,   144,   -97,   -19,
      -1,   100,   -97,   115,   -97,   -97,   135,   137,   142,   -97,
     145,   -97,   -97,   -97,   146,    40,   -97,   -16,   120,   123,
     128,    24,   -97,   -97,   132,   -97,   -97,   -97,   -97,    42,
     -97,   147,   100,    31,   -97,   -97,   -97,   -97,   -97,   -97,
      -1,   -97,    80,   -97,   -97,   -97,   148,   149,   133,   150,
     151,   157,     8,   -97,   152,   -97,   -97,   155,   156,   -97,
     -97,     8,     8,   -97,   162,   -97,    80,    -1,    -1,    -1,
      -1,    -1,   153,   154,   158,   159,   160,   166,   -97,   -97,
     161,   167,   -97,    51,   -97,   -21,   -21,   -97,   -97,   -97,
     -97,   170,   -97,   -97,   163,     8,   100,   100,   -97,   164,
     165,   -97,    63,    64,   171,   -97,   -97,   172,   168,   169,
     173,   175,   -97,   100,    71,   -97
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -97,   -97,   185,   -43,   -97,    94,   176,   -96,   -10,   -83,
     -97,   -97,   131,   -97,   -58,   -97,   -97,    49,   -84
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      34,   120,    83,    24,   123,    25,    54,    63,    19,    73,
      74,    73,    74,    79,    80,    27,    59,    31,    82,   106,
      60,   107,    28,    92,   113,    63,    94,    32,    95,   159,
     160,   161,    91,   113,    55,   124,   125,   126,   127,   128,
     129,    65,    75,    61,    75,    72,    81,   156,   114,   143,
      93,   147,   148,    89,    26,   154,   155,   114,   168,    32,
     115,   116,   117,   118,   141,    29,   142,   172,   120,   115,
     116,   117,   118,    30,   175,   176,   177,   178,   179,    35,
      37,    65,     1,     2,     3,     4,     5,   150,    38,   151,
     192,   193,    39,     6,     7,    40,   188,     8,   151,     9,
      10,   191,     1,     2,     3,     4,     5,   204,   196,   197,
      55,    55,    89,     6,     7,    41,   205,     8,    55,     9,
      10,    98,    99,   100,   101,   102,   103,   104,   157,   158,
     159,   160,   161,    13,    16,    14,    17,    15,    18,    20,
      21,    22,    23,    42,    51,    43,    44,    45,    46,    47,
      48,    49,    50,    52,    53,    57,    56,    62,    63,    58,
      32,    84,    68,    70,    78,    85,    90,    96,    97,   121,
     109,   108,   110,   111,   112,   135,    34,    34,   122,   136,
     144,   137,   167,   145,   170,   171,   138,   174,   146,   139,
     140,   152,   185,    34,   149,   164,    36,   169,   180,   181,
     189,   173,   199,   182,   183,   186,     0,   184,   162,   163,
     195,   187,   165,   166,     0,   198,   153,     0,   202,   203,
       0,     0,   134,     0,   194,   190,     0,     0,   200,   201,
      71
};

static const yytype_int16 yycheck[] =
{
      10,    85,    60,     9,    23,    11,    19,    22,    60,    27,
      28,    27,    28,    27,    28,    11,     4,    50,    36,    45,
       8,    47,    16,    66,    25,    22,    69,    60,    71,    50,
      51,    52,    47,    25,    47,    54,    55,    56,    57,    58,
      59,    51,    60,    31,    60,    55,    60,   130,    49,   107,
      47,    27,    28,    63,    60,    24,    25,    49,   142,    60,
      61,    62,    63,    64,    24,    19,    26,   151,   152,    61,
      62,    63,    64,    60,   157,   158,   159,   160,   161,     0,
      46,    91,     3,     4,     5,     6,     7,    45,    60,    47,
     186,   187,    60,    14,    15,    60,    45,    18,    47,    20,
      21,   185,     3,     4,     5,     6,     7,   203,    45,    45,
      47,    47,   122,    14,    15,    60,    45,    18,    47,    20,
      21,    37,    38,    39,    40,    41,    42,    43,    48,    49,
      50,    51,    52,     9,     9,    11,    11,    13,    13,     9,
      10,    11,    12,    60,    35,    60,    60,    60,    60,    60,
      60,    60,    60,    19,    53,    44,    46,    17,    22,    33,
      60,    32,    60,    60,    60,    44,    54,    29,    29,    47,
      29,    44,    29,    60,    60,    60,   186,   187,    34,    44,
      60,    44,    25,    60,    29,    29,    44,    25,    60,    44,
      44,    44,    26,   203,    62,    62,    11,    45,    45,    45,
      30,   152,    30,    45,    45,    44,    -1,    47,    60,    60,
      45,    44,    62,    62,    -1,    44,   122,    -1,    45,    44,
      -1,    -1,    91,    -1,    60,    62,    -1,    -1,    60,    60,
      54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    14,    15,    18,    20,
      21,    66,    67,     9,    11,    13,     9,    11,    13,    60,
       9,    10,    11,    12,     9,    11,    60,    11,    16,    19,
      60,    50,    60,    72,    73,     0,    67,    46,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    35,    19,    53,    19,    47,    46,    44,    33,     4,
       8,    31,    17,    22,    68,    73,    76,    77,    60,    71,
      60,    71,    73,    27,    28,    60,    78,    79,    60,    27,
      28,    60,    36,    79,    32,    44,    81,    69,    70,    73,
      54,    47,    68,    47,    68,    68,    29,    29,    37,    38,
      39,    40,    41,    42,    43,    80,    45,    47,    44,    29,
      29,    60,    60,    25,    49,    61,    62,    63,    64,    82,
      83,    47,    34,    23,    54,    55,    56,    57,    58,    59,
      75,    73,    74,    83,    77,    60,    44,    44,    44,    44,
      44,    24,    26,    79,    60,    60,    60,    27,    28,    62,
      45,    47,    44,    70,    24,    25,    74,    48,    49,    50,
      51,    52,    60,    60,    62,    62,    62,    25,    83,    45,
      29,    29,    83,    82,    25,    74,    74,    74,    74,    74,
      45,    45,    45,    45,    47,    26,    44,    44,    45,    30,
      62,    83,    72,    72,    60,    45,    45,    45,    44,    30,
      60,    60,    45,    44,    72,    45
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
#line 109 "Parser.y"
    {				
            ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 112 "Parser.y"
    {				
            ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 116 "Parser.y"
    {
			(yyval.tree)=new CreateDatabaseTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 122 "Parser.y"
    {
			(yyval.tree)=new DropDatabaseTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 128 "Parser.y"
    {
			(yyval.tree)=new UseDatabaseTree((yyvsp[(2) - (2)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(2) - (2)].string);
			Tree::run();
		;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 134 "Parser.y"
    {
			(yyval.tree)=new ShowDatabaseTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 140 "Parser.y"
    {
			(yyval.tree)=new ShowDatabaseSTree();
			Tree::setInstance((yyval.tree));			
			Tree::run();
		;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 145 "Parser.y"
    {
			(yyval.tree)=new ShowDatabaseDescTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 151 "Parser.y"
    {
			(yyval.tree)=new ShowTableDescTree((yyvsp[(2) - (2)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(2) - (2)].string);
			Tree::run();
		;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 158 "Parser.y"
    {
			(yyval.tree)=new CreateTableTree((yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].attributelisttree));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (6)].string);
			Tree::run();						
		;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 164 "Parser.y"
    {
			(yyval.tree)=new DropTableTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 170 "Parser.y"
    {
			(yyval.tree)=new ShowTableTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 176 "Parser.y"
    {
			(yyval.tree)=new ShowTableDescTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 182 "Parser.y"
    {
			(yyval.tree)=new ShowTableSTree();
			Tree::setInstance((yyval.tree));			
			Tree::run();
		;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 188 "Parser.y"
    {
			(yyval.tree)=new CreateIndexTree((yyvsp[(3) - (8)].string),(yyvsp[(5) - (8)].string),(yyvsp[(7) - (8)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (8)].string),(yyvsp[(5) - (8)].string),(yyvsp[(7) - (8)].string);
			Tree::run();
		;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 194 "Parser.y"
    {
			(yyval.tree)=new DropIndexTree((yyvsp[(3) - (3)].string));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (3)].string);
			Tree::run();
		;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 200 "Parser.y"
    {
			(yyval.tree)=new AddAttributeTree((yyvsp[(3) - (5)].string),(yyvsp[(5) - (5)].attributetree));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (5)].string);
			Tree::run();
		;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 206 "Parser.y"
    {
			(yyval.tree)=new AddPrimaryTree((yyvsp[(3) - (11)].string),(yyvsp[(10) - (11)].columnlisttree),(yyvsp[(6) - (11)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (11)].string),(yyvsp[(6) - (11)].string);
			Tree::run();
		;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 212 "Parser.y"
    {
			(yyval.tree)=new AddForeignTree((yyvsp[(3) - (16)].string),(yyvsp[(10) - (16)].columnlisttree),(yyvsp[(13) - (16)].string),(yyvsp[(15) - (16)].columnlisttree),(yyvsp[(6) - (16)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (16)].string),(yyvsp[(6) - (16)].string),(yyvsp[(13) - (16)].string);
			Tree::run();
		;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 218 "Parser.y"
    {
			(yyval.tree)=new DropPrimaryTree((yyvsp[(3) - (6)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (6)].string);
			Tree::run();
		;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 224 "Parser.y"
    {
			(yyval.tree)=new DropPrimaryTree((yyvsp[(3) - (7)].string),(yyvsp[(7) - (7)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (7)].string),(yyvsp[(7) - (7)].string);
			Tree::run();
		;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 230 "Parser.y"
    {
			(yyval.tree)=new DropForeignTree((yyvsp[(3) - (7)].string),(yyvsp[(7) - (7)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (7)].string),(yyvsp[(7) - (7)].string);
			Tree::run();
		;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 236 "Parser.y"
    {
			(yyval.tree)=new DropAttributeTree((yyvsp[(3) - (5)].string),(yyvsp[(5) - (5)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (5)].string),(yyvsp[(5) - (5)].string);
			Tree::run();
		;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 242 "Parser.y"
    {
			(yyval.tree)=new TableRenameTree((yyvsp[(3) - (6)].string),(yyvsp[(6) - (6)].string));
			Tree::setInstance((yyval.tree));			
			delete (yyvsp[(3) - (6)].string),(yyvsp[(6) - (6)].string);
			Tree::run();
		;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 249 "Parser.y"
    {
			(yyval.tree)=new InsertTree((yyvsp[(3) - (5)].string),(yyvsp[(5) - (5)].valueliststree));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (5)].string);
			Tree::run();
		;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 255 "Parser.y"
    {
			(yyval.tree)=new DeleteTree((yyvsp[(3) - (4)].string),(yyvsp[(4) - (4)].WhereClausestree));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(3) - (4)].string);
			Tree::run();
		;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 261 "Parser.y"
    {
			(yyval.tree)=new UpdateTree((yyvsp[(2) - (5)].string),(yyvsp[(4) - (5)].setClauselisttree),(yyvsp[(5) - (5)].WhereClausestree));
			Tree::setInstance((yyval.tree));
			delete (yyvsp[(2) - (5)].string);
			Tree::run();
		;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 267 "Parser.y"
    {
			(yyval.tree)=new SelectTree((yyvsp[(2) - (5)].columnlisttree),(yyvsp[(4) - (5)].tablelisttree),(yyvsp[(5) - (5)].WhereClausestree));
			Tree::setInstance((yyval.tree));			
			Tree::run();
		;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 272 "Parser.y"
    {
			(yyval.tree)=new SelectTree(nullptr,(yyvsp[(4) - (5)].tablelisttree),(yyvsp[(5) - (5)].WhereClausestree));
			Tree::setInstance((yyval.tree));			
			Tree::run();
		;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 279 "Parser.y"
    {
			(yyval.WhereClausestree)=new WhereClausesTree((yyvsp[(2) - (2)].conditionstree));
		;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 282 "Parser.y"
    {
			(yyval.WhereClausestree)=new WhereClausesTree();
		;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 286 "Parser.y"
    {
			(yyval.conditionstree)=new conditionsTree();
			(yyval.conditionstree)->append((yyvsp[(1) - (1)].comparisontree));
		;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 290 "Parser.y"
    {
			(yyval.conditionstree)->append((yyvsp[(3) - (3)].comparisontree));
		;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 294 "Parser.y"
    {
			 (yyval.comparisontree)=new comparisonTree((yyvsp[(1) - (3)].columntree),(yyvsp[(2) - (3)].opname),(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 297 "Parser.y"
    {
			(yyval.comparisontree)=new comparisonTree((yyvsp[(1) - (3)].columntree),opName::INULL,nullptr);
		;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 300 "Parser.y"
    {
			(yyval.comparisontree)=new comparisonTree((yyvsp[(1) - (4)].columntree),opName::NNULL,nullptr);
		;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 304 "Parser.y"
    {		
			(yyval.tablelisttree)=new tablelistTree();
			(yyval.tablelisttree)->append((yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 309 "Parser.y"
    {			
			(yyval.tablelisttree)->append((yyvsp[(3) - (3)].string));
			delete (yyvsp[(3) - (3)].string);
		;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 314 "Parser.y"
    {		
			(yyval.columnlisttree)=new columnlistTree();
			(yyval.columnlisttree)->append((yyvsp[(1) - (1)].columntree));
		;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 318 "Parser.y"
    {			
			(yyval.columnlisttree)->append((yyvsp[(3) - (3)].columntree));
		;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 322 "Parser.y"
    {
			(yyval.columntree)=new columnTree((yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string));
			delete (yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string);
		;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 326 "Parser.y"
    {
			(yyval.columntree)=new columnTree((yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 331 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (1)].valuetree));
		;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 334 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (1)].columntree));
		;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 337 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::ADD,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 340 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::MINUS,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 343 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::MULTI,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 346 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::DIV,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 349 "Parser.y"
    {
			(yyval.exprtree)=new exprTree((yyvsp[(1) - (3)].exprtree),clacopName::MODC,(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 353 "Parser.y"
    {
			(yyval.opname)=opName::EQ;
		;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 356 "Parser.y"
    {
			(yyval.opname)=opName::GT;
		;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 359 "Parser.y"
    {
			(yyval.opname)=opName::LT;
		;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 362 "Parser.y"
    {
			(yyval.opname)=opName::GE;
		;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 365 "Parser.y"
    {
			(yyval.opname)=opName::LE;
		;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 368 "Parser.y"
    {
			(yyval.opname)=opName::NE;
		;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 372 "Parser.y"
    {
			(yyval.setClauselisttree)=new setClauselistTree();
			(yyval.setClauselisttree)->append((yyvsp[(1) - (1)].setClausetree));
		;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 376 "Parser.y"
    {
			(yyval.setClauselisttree)->append((yyvsp[(3) - (3)].setClausetree));
		;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 380 "Parser.y"
    {
			(yyval.setClausetree)=new setClauseTree((yyvsp[(1) - (3)].columntree),(yyvsp[(3) - (3)].exprtree));
		;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 385 "Parser.y"
    {		
			(yyval.attributelisttree)=new attributelistTree();
			(yyval.attributelisttree)->append((yyvsp[(1) - (1)].attributetree));
		;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 389 "Parser.y"
    {			
			(yyval.attributelisttree)->append((yyvsp[(3) - (3)].attributetree));
		;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 393 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree(false,false,(yyvsp[(1) - (2)].string),(yyvsp[(2) - (2)].typetree),true,false);
			delete (yyvsp[(1) - (2)].string);
		;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 397 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree(false,false,(yyvsp[(1) - (4)].string),(yyvsp[(2) - (4)].typetree),false,false);
			delete (yyvsp[(1) - (4)].string);
		;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 401 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree(false,false,(yyvsp[(1) - (4)].string),(yyvsp[(2) - (4)].typetree),true,true,(yyvsp[(4) - (4)].valuetree));
			delete (yyvsp[(1) - (4)].string),(yyvsp[(4) - (4)].valuetree);
		;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 405 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree(false,false,(yyvsp[(1) - (6)].string),(yyvsp[(2) - (6)].typetree),false,true,(yyvsp[(6) - (6)].valuetree));
			delete (yyvsp[(1) - (6)].string),(yyvsp[(6) - (6)].valuetree);
		;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 409 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree(true,false,(yyvsp[(4) - (5)].string));
			delete (yyvsp[(4) - (5)].string);
		;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 413 "Parser.y"
    {
			(yyval.attributetree)=new attributeTree(false,true,(yyvsp[(4) - (10)].string),(yyvsp[(7) - (10)].string),(yyvsp[(9) - (10)].string));
			delete (yyvsp[(4) - (10)].string),(yyvsp[(7) - (10)].string),(yyvsp[(9) - (10)].string);
		;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 419 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Int,(yyvsp[(3) - (4)].string));
		;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 422 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::SmallInt);
		;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 425 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Char,(yyvsp[(3) - (4)].string));			
		;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 428 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Double);
		;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 431 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Float);
		;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 434 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Date);
		;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 437 "Parser.y"
    {
			(yyval.typetree)=new typeTree(TypeName::Numeric,(yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].string));
		;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 442 "Parser.y"
    {
			(yyval.valueliststree)=new valuelistsTree();
			(yyval.valueliststree)->append((yyvsp[(2) - (3)].valuelisttree));
		;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 446 "Parser.y"
    {
			(yyval.valueliststree)->append((yyvsp[(4) - (5)].valuelisttree));
		;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 451 "Parser.y"
    {
			(yyval.valuelisttree)=new valuelistTree();
			(yyval.valuelisttree)->append((yyvsp[(1) - (1)].valuetree));
		;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 455 "Parser.y"
    {
			(yyval.valuelisttree)->append((yyvsp[(3) - (3)].valuetree));
		;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 459 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::TEXT,(yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 463 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::INUM,(yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 467 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::INUM,std::string("-"+std::string((yyvsp[(2) - (2)].string))).c_str());
			delete (yyvsp[(2) - (2)].string);
		;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 471 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::FNUM,(yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 475 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::DATENUM,(yyvsp[(1) - (1)].string));
			delete (yyvsp[(1) - (1)].string);
		;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 479 "Parser.y"
    {
			(yyval.valuetree)=new valueTree(CharTypeName::NULLC);			
		;}
    break;



/* Line 1455 of yacc.c  */
#line 2468 "Parser.c"
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
#line 484 "Parser.y"


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
