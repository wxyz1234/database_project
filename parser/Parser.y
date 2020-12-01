%{
/*声明节  将被原样拷贝,可选*/
#include <stdio.h>
#include "../parser/global.h"
#include "../parser/tree.h"
//#include "../RecordManageSystem/utils/Myhash.h"

void yyerror(const char *);
int yylex(void); 
int parseFile();
Tree* Tree::tree = nullptr;
%}

/*辅助定义节  定义文法相关的名称和属性,可选*/

%union{
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
}
%token CREATE DROP USE SHOW DESC ADD
%token DATABASE DATABASES TABLE TABLES INDEX
%token ALTER INSERT INTO VALUES DELETEC FROM UPDATE SELECT WHERE
%token IS NOT NULLC DEFAULT PRIMARY FOREIGN KEY
%token REFERENCES RENAME TO ON AND SET
%token INTEGER  SMALLINT  CHARTYPE  DOUBLETYPE  FLOATTYPE  DATETYPE  NUMERICTYPE
%token '(' ')' ';' ',' '+' '-' '*' '/' '%'
%token EQ GT LT GE LE NE
%token <string> NAME TEXT INUM FNUM DATENUM

%type <tree> command
%type <WhereClausestree> whereClauses
%type <conditionstree> conditions
%type <comparisontree> comparison
%type <opname> op
%type <columntree> column
%type <columnlisttree> columnlist
%type <tablelisttree> tablelist
%type <exprtree> expr
%type <setClauselisttree> setClauselist
%type <setClausetree> setClause;
%type <attributelisttree> attributelist
%type <attributetree> attribute
%type <typetree> type
%type <valueliststree> valuelists
%type <valuelisttree> valuelist
%type <valuetree> value

%left '+' '-'
%left '*' '/' '%'

%%
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
			delete $2;
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
	|	DELETEC FROM NAME whereClauses{
			$$=new DeleteTree($3,$4);
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
	|	SELECT columnlist FROM tablelist whereClauses{
			$$=new SelectTree($2,$4,$5);
			Tree::setInstance($$);			
			Tree::run();
		}
	|	SELECT '*' FROM tablelist whereClauses{
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
	|	column IS NULLC{
			$$=new comparisonTree($1,opName::INULL,nullptr);
		}
	|	column IS NOT NULLC{
			$$=new comparisonTree($1,opName::NNULL,nullptr);
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
			$$=new exprTree($1,clacopName::MODC,$3);
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
	|	setClauselist ',' setClause{
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
	|	NAME type NOT NULLC{
			$$=new attributeTree($1,$2,true,false);
			delete $1;
		}
	|	NAME type DEFAULT value {
			$$=new attributeTree($1,$2,false,true,$4);
			delete $1,$4;
		}
	|	NAME type NOT NULLC DEFAULT value{
			$$=new attributeTree($1,$2,true,true,$6);
			delete $1,$6;
		}
	|	PRIMARY KEY NAME {
			$$=new attributeTree(KeyName::Primary,$3);
			delete $3;
		}
	|	FOREIGN KEY NAME REFERENCES NAME '(' NAME ')'{
			$$=new attributeTree(KeyName::Foreign,$3,$5,$7);
			delete $3,$5,$7;
		}
	;

type:	INTEGER {
			$$=new typeTree(TypeName::Int);
		}
	|	SMALLINT {
			$$=new typeTree(TypeName::SmallInt);
		}
	|	CHARTYPE '(' INUM ')'{
			$$=new typeTree(TypeName::Char,$3);			
		}
	|	DOUBLETYPE{
			$$=new typeTree(TypeName::Double);
		}
	|	FLOATTYPE{
			$$=new typeTree(TypeName::Float);
		}
	|	DATETYPE{
			$$=new typeTree(TypeName::Date);
		}
	|	NUMERICTYPE '(' INUM ',' INUM ')'{
			$$=new typeTree(TypeName::Numeric,$3,$5);
		}
	;

valuelists:	'(' valuelist ')'{
			$$=new valuelistsTree();
			$$->append($2);
		}
	|	valuelists ',' '(' valuelist ')'{
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
	|	DATENUM{
			$$=new valueTree(CharTypeName::DATENUM,$1);
			delete $1;
		}
	;

%%

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