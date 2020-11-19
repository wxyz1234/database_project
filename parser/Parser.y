%{
/*声明节  将被原样拷贝,可选*/
#include <tree.h>
#include <stdio.h>
#include "../parser/Lexer.c"
#include "../RecordManageSystem/DType/DKey.h"
#include "../RecordManageSystem/DType/TypeName.h"
%}

/*辅助定义节  定义文法相关的名称和属性,可选*/

%union{
	Tree* tree
	char* string;

	CreateDatabaseTree *CreateDatabaseTree;
	DropDatabaseTree *DropDatabaseTree;
	UseDatabaseTree *UseDatabaseTree;
	ShowDatabaseTree *ShowDatabaseTree;
	ShowDatabaseSTree *ShowDatabaseSTree;
	ShowDatabaseDescTree *ShowDatabaseDescTree;
	CreateTableTree *CreateTableTree;

	CreateTableTree *CreateTableTree;
	DropTableTree *DropTableTree;
	ShowTableTree *ShowTableTree;
	ShowTableSTree *ShowTableSTree;

	CreateIndexTree *CreateIndexTree;
	DropIndexTree *DropIndexTree;

	AddPrimaryTree *AddPrimaryTree;
	DropPrimaryTree *DropPrimaryTree;
	AddForeignTree *AddForeignTree;
	DropForeignTree *DropForeignTree;
	AddAttributeTree *AddAttributeTree;
	DropAttributeTree *DropAttributeTree;
	TableRenameTree *TableRenameTree;

	InsertTree *InsertTree;
	DeleteTree *DeleteTree;
	UpdateTree *UpdateTree;
	SelectTree *SelectTree;

	WhereClausesTree *WhereClausesTree;
	conditionsTree *conditionsTree;
	comparisonTree *comparisonTree;		
	exprTree *exprTree;
	columnTree *columnTree;
	columnlistTree *columnlistTree;
	tablelistTree *tablelistTree;	
	setClauselistTree *setClauselistTree;
	setClauseTree *setClauseTree;

	attributelistTree *attributelistTree;
	attributeTree *attributeTree;
	typeTree *typeTree;
	valuelistsTree *valuelistsTree;
	valuelistTree *valuelistTree;
	valueTree *valueTree;	

	opName opName;
}
%token CREATE DROP USE SHOW DESC ADD
%token DATABASE DATABASES TABLE TABLES INDEX
%token ALTER INSERT INTO VALUES DELETE FROM UPDATE SELECT WHERE
%token IS NOT NULL DEFAULT PRIMARY FOREIGN KEY REFERENCES RENAME TO
%token INT  SMALLINT  CHAR  DOUBLE  FLOAT  DATE  NUMERIC 
%token '(' ')' ';' ',' '+' '-' '*' '/' '%'
%token EQ GT LT GE LE NE
%token <string> NAME TEXT INUM FNUM DATE
%type <tree> command
%type <WhereClausesTree> whereClauses
%type <conditionsTree> conditions
%type <comparisonTree> comparison
%type <opName> op
%type <columnTree> column
%type <columnlistTree> columnlist
%type <tablelistTree> tablelist
%type <exprTree> expr
%type <setClauselistTree> setClauselist
%type <setClauseTree> setClause;
%type <attributelistTree> attributelist
%type <attributeTree> attribute
%type <typeTree> type
%type <valuelistsTree>valuelists
%type <valuelistTree>valuelist
%type <valueTree> value

%%
/*语法规则节  定义语法规则及语义动作. Yacc中的产生式格式为非终结符: 右端 {C语句表示的语义动作}*/

sql:
    command ';'
            {				
            }
    | sql command ';'
            {				
            }
    ;

command: CREATE DATABASE NAME{
			$$=new CreateDatabaseTree($3);
			Tree::setInstance($$);
			delete $3;
			Tree::run();
		}
	|	DROP DATABASE NAME{
			$$=new DropDatabaseTree($3);
			Tree::setInstance($$);
			delete $3;
			Tree::run();
		}
	|	USE DATABASE NAME{
			$$=new UseDatabaseTree($3);
			Tree::setInstance($$);
			delete $3;
			Tree::run();
		}
	|	SHOW DATABASE NAME{
			$$=new ShowDatabaseTree($3);
			Tree::setInstance($$);
			delete $3;
			Tree::run();
		}
	|	SHOW DATABASES{
			$$=new ShowDatabaseSTree();
			Tree::setInstance($$);			
			Tree::run();
		}
	|	DESC NAME{
			$$=new ShowDatabaseDescTree($2);
			Tree::setInstance($$);
			delete $3;
			Tree::run();
		}

	|	CREATE TABLE NAME '(' attributelist ')'{
			$$=new CreateTableTree($3,$5);
			Tree::setInstance($$);
			delete $3;
			Tree::run;			
		}
	|	DROP TABLE NAME{
			$$=new DropTableTree($3);
			Tree::setInstance($$);
			delete $3;
			Tree::run();
		}
	|	SHOW TABLE NAME{
			$$=new ShowTableTree($3);
			Tree::setInstance($$);
			delete $3;
			Tree::run();
		}
	|	SHOW TABLES{
			$$=new ShowTableSTree();
			Tree::setInstance($$);			
			Tree::run();
		}

	|	CREATE INDEX NAME ON NAME '(' NAME ')' {
			$$=new CreateIndexTree($3,$5,$7);
			Tree::setInstance($$);			
			delete $3,$5,$7;
			Tree::run();
		}
	|	DROP INDEX NAME{
			$$=new DropIndexTree($3);
			Tree::setInstance($$);
			delete $3;
			Tree::run();
		}

	|	ALTER TABLE NAME ADD PRIMARY KEY '(' NAME ')'{
			$$=new AddPrimaryTree($3,$8);
			Tree::setInstance($$);			
			delete $3,$8;
			Tree::run();
		}
	|	ALTER TABLE NAME DROP PRIMARY KEY {
			$$=new DropPrimaryTree($3);
			Tree::setInstance($$);			
			delete $3;
			Tree::run();
		}
	|	ALTER TABLE NAME ADD FOREIGN KEY '(' NAME ')' REFERENCES NAME '(' NAME ')'{
			$$=new AddForeignTree($3,$8,$11,$13);
			Tree::setInstance($$);			
			delete $3,$8,$11,$13;
			Tree::run();
		}
	|	ALTER TABLE NAME DROP FOREIGN KEY '(' NAME ')'{
			$$=new DropForeignTree($3,$8);
			Tree::setInstance($$);			
			delete $3,$8;
			Tree::run();
		}
	|	ALTER TABLE NAME ADD attribute{
			$$=new AddAttributeTree($3,$5);
			Tree::setInstance($$);			
			delete $3;
			Tree::run();
		}
	|	ALTER TABLE NAME DROP NAME{
			$$=new DropAttributeTree($3,$5);
			Tree::setInstance($$);			
			delete $3,$5;
			Tree::run();
		}
	|	ALTER TABLE NAME RENAME TO NAME{
			$$=new TableRenameTree($3,$6);
			Tree::setInstance($$);			
			delete $3,$6;
			Tree::run();
		}

	|	INSERT INTO NAME VALUES valuelists{
			$$=new InsertTree($3,$5);
			Tree::setInstance($$);
			delete $3;
			Tree::run();
		}
	|	DELETE FROM NAME whereClauses{
			$$=new DeleteTree($3,$5);
			Tree::setInstance($$);
			delete $3;
			Tree::run();
		}
	|	UPDATE NAME SET setClauselist whereClauses{
			$$=new UpdateTree($2,$4,$5);
			Tree::setInstance($$);
			delete $2;
			Tree::run();
		}
	|	SELECT columnList FROM tableList whereClauses{
			$$=new SelectTree($2,$4,$5);
			Tree::setInstance($$);			
			Tree::run();
		}
	|	SELECT '*' FROM tableList whereClauses{
			$$=new SelectTree(nullptr,$4,$5);
			Tree::setInstance($$);			
			Tree::run();
		}
	;
	
whereClauses:	WHERE conditions{
			$$=new WhereClausesTree($2);
		}
	|	{
			$$=nullptr;
		}
	;
conditions:	comparison{
			$$=new conditionsTree();
			$$->append($1);
		}
	|	conditions AND comparison{
			$$->append($3);
		}
	;
comparison:	column op expr{
			 $$=new comparisonTree($1,$2,$3);
		}
	|	column IS NULL{
			$$=new comparisonTree($1,opName::IN,nullptr);
		}
	|	column IS NOT NULL{
			$$=new comparisonTree($1,opName::NN,nullptr);
		}
	;
tablelist: NAME{		
			$$=new tablelistTree();
			$$->append($1);
			delete $1;
		}
	|	tablelist ',' NAME{			
			$$->append($3);
			delete $3;
		}
	;
columnlist: column{		
			$$=new columnlistTree();
			$$->append($1);
		}
	|	columnlist ',' column{			
			$$->append($3);
		}
	;
column:	NAME '.' NAME{
			$$=new columnTree($1,$3);
			delete $1,$3;
		}
	|	NAME{
			$$=new columnTree($1);
			delete $1;
		}
	;
expr:	value{
			$$=new exprTree($1);
		}
	|	column{
			$$=new exprTree($1);
		}
	|	expr '+' expr{
			$$=new exprTree($1,clacopName::ADD,$3);
		}
	|	expr '-' expr{
			$$=new exprTree($1,clacopName::MINUS,$3);
		}
	|	expr '*' expr{
			$$=new exprTree($1,clacopName::MULTI,$3);
		}
	|	expr '/' expr{
			$$=new exprTree($1,clacopName::DIV,$3);
		}
	|	expr '%' expr{
			$$=new exprTree($1,clacopName::MOD,$3);
		}
	;
op:		EQ{
			$$=opName::EQ;
		}
	|	GT{
			$$=opName::EQ;
		}
	|	LT{
			$$=opName::EQ;
		}
	|	GE{
			$$=opName::EQ;
		}
	|	LE{
			$$=opName::EQ;
		}
	|	NE{
			$$=opName::EQ;
		}
	;
setClauselist: setClause{
			$$=new setClauselistTree();
			$$->append($1);
		}
	|	setClauseList ',' setClause{
			$$->append($3);
		}
	;
setClause:	column '=' expr{
			$$=new setClauseTree($1,$3);
		}
	;

attributelist: attribute{		
			$$=new attributelistTree();
			$$->append($1);
		}
	|	attributelist ',' attribute{			
			$$->append($3);
		}
	;
attribute:	NAME type{
			$$=new attributeTree($1,$2,false,false);
			delete $1;
		}
	|	NAME type NOT NULL{
			$$=new attributeTree($1,$2,true,false);
			delete $1;
		}
	|	NAME type DEFAULT NAME {
			$$=new attributeTree($1,$2,false,true,$4);
			delete $1,$4;
		}
	|	NAME type NOT NULL DEFAULT value{
			$$=new attributeTree($1,$2,true,true,$6);
			delete $1,$6;
		}
	|	PRIMARY KEY '(' NAME ')'{
			$$=new attributeTree(KeyName::Primary,$4);
			delete $4;
		}
	|	FOREIGN KEY '(' NAME ')' REFERENCES NAME '(' NAME ')'{
			$$=new attributeTree(KeyName::Foreign,$4,$7,$9);
			delete $4,$7,$9;
		}
	;

type:	INT {
			$$=new typeTree(TypeName::Int);
		}
	|	SMALLINT {
			$$=new typeTree(TypeName::SmallInt);
		}
	|	CHAR '(' NUM ')'{
			$$=new typeTree(TypeName::Char,$3);			
		}
	|	DOUBLE{
			$$=new typeTree(TypeName::Double);
		}
	|	FLOAT{
			$$=new typeTree(TypeName::Float);
		}
	|	DATE{
			$$=new typeTree(TypeName::Date);
		}
	|	NUMERIC '(' NUM ',' NUM ')'{
			$$=new typeTree(TypeName::Numeric,$3,$5);
		}
	;

valuelists:	'(' valueslist ')'{
			$$=new valuelistsTree();
			$$->append($2);
		}
	|	valueslists ',' '(' valueslist ')'{
			$$->append($4);
		}
	;

valuelist: value{
			$$=new valuelistTree();
			$$->append($1);
		}
	|	valuelist ',' value{
			$$->append($3);
		}
	;
value:	TEXT{
			$$=new valueTree(CharTypeName::TEXT,$1);
			delete $1;
		}
	|	INUM{
			$$=new valueTree(CharTypeName::INUM,$1);
			delete $1;
		}
	|	FNUM{
			$$=new valueTree(CharTypeName::FNUM,$1);
			delete $1;
		}
	|	DATE{
			$$=new valueTree(CharTypeName::DATE,$1);
			delete $1;
		}
	;

%%

/*支撑函数节  规则节用到的局部 C 函数定义,可选*/
void yyerror(const char *msg) {
    printf("YACC error: %s\n", msg);
}
void parseFile(){//程序主函数，读取命令，执行输出
	bool instd=false;
	bool outstd=false;
	char* inputname="input.txt";
	char* outputname="output.txt";	
	FILE* fin,fout;
	if (instd){
		fin = fopen(inputname, "r"); 
		yyin=fin;
		printf("input name is %s\n",inputname);
	}else
		printf("input is stdin\n");s
	if (outstd){
		fout = fopen(outputname ,"w");
		yyout=fout;
		printf("output name is %s\n",outputname);
	}else	
		printf("output is stdout\n");	
	printf("parse Begin!");	
	yyparse();	
	printf("parse End!");
	if (instd)fclose(fin);
    if (outstd)fclose(fout);
}