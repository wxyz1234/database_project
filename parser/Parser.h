
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
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



/* Line 1676 of yacc.c  */
#line 159 "Parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


