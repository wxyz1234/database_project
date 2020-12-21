%option noyywrap

%{
/* 定义节:可选，包含头文件、宏定义或全局 C 代码*/
#include "../parser/tree.h"
#include "../parser/Parser.h"

char *get_text(const char *text) {
    int length = strlen(text);
    char *buffer = new char[length + 1];
    memcpy(buffer, text, (length + 1) * sizeof(char));
    return buffer;
}
char *get_text2(const char *text) {
    int length = strlen(text);
    char *buffer = new char[length - 1];
    memcpy(buffer, text+1, (length -2) * sizeof(char));
    buffer[length-2] = '\0';
    return buffer;
}
%}

/* 辅助定义节:可选，在此可以为正规式定义宏名字*/
DATENUM (\'[0-9]{4}-[0-9]{2}-[0-9]{2}\')
NAME ([a-zA-z][0-9a-zA-z_]*)
SINQ (\\\')
TEXT (\'({SINQ}|[^\\\n'])*\')
INUM ([0-9]+)
FNUM ([-]{0,1}[0-9]+[.][0-9]+)
BLANKCHAR ([ \f\r\t\v\n]+)

%%
CREATE { printf("CREATE\n"); return CREATE; }
DROP { printf("DROP\n"); return DROP; }
USE { printf("USE\n"); return USE; }
SHOW { printf("SHOW\n"); return SHOW; }
DESC { printf("DESC\n"); return DESC; }
ADD { printf("ADD\n"); return ADD; }
DATABASE { printf("DATABASE\n"); return DATABASE; }
DATABASES { printf("DATABASES\n"); return DATABASES; }
TABLE { printf("TABLE\n"); return TABLE; }
TABLES { printf("TABLES\n"); return TABLES; }
INDEX { printf("INDEX\n"); return INDEX; }
ALTER { printf("ALTER\n"); return ALTER; }
INSERT { printf("INSERT\n"); return INSERT; }
INTO { printf("INTO\n"); return INTO; }
VALUES { printf("VALUES\n"); return VALUES; }
DELETE { printf("DELETE\n"); return DELETEC; }
FROM { printf("FROM\n"); return FROM; }
UPDATE { printf("UPDATE\n"); return UPDATE; }
SELECT { printf("SELECT\n"); return SELECT; }
WHERE { printf("WHERE\n"); return WHERE; }
IS { printf("IS\n"); return IS; }
NOT { printf("NOT\n"); return NOT; }
NULL { printf("NULL\n"); return NULLC; }
DEFAULT { printf("DEFAULT\n"); return DEFAULT; }
PRIMARY { printf("PRIMARY\n"); return PRIMARY; }
FOREIGN { printf("FOREIGN\n"); return FOREIGN; }
KEY { printf("KEY\n"); return KEY; }
REFERENCES { printf("REFERENCES\n"); return REFERENCES; }
RENAME { printf("RENAME\n"); return RENAME; }
TO { printf("TO\n"); return TO; }
ON { printf("ON\n"); return ON; }
AND { printf("AND\n"); return AND; }
SET { printf("SET\n"); return SET; }
CONSTRAINT { printf("CONSTRAINT\n"); return CONSTRAINT; }
INT { printf("INTEGER\n"); return INTEGER; }
SMALLINT { printf("SMALLINT\n"); return SMALLINT; }
CHAR { printf("CHAR\n"); return CHARTYPE; }
DOUBLE { printf("DOUBLE\n"); return DOUBLETYPE; }
FLOAT { printf("FLOAT\n"); return FLOATTYPE; }
DATE { printf("DATETYPE\n"); return DATETYPE; }
NUMERIC { printf("NUMERICTYPE\n"); return NUMERICTYPE; }
"(" { /*printf("(\n");*/ return '('; }
")" { /*printf(")\n");*/ return ')'; }
";" { printf(";\n"); return ';'; }
"," { /*printf(",\n");*/ return ','; }
"." { /*printf(".\n");*/ return '.'; }
"+"	{ /*printf("+\n");*/ return '+'; }
"-"	{ /*printf("-\n");*/ return '-'; }
"*"	{ /*printf("*\n");*/ return '*'; }
"/"	{ /*printf("/\n");*/ return '/'; }
"%"	{ /*printf("%\n");*/ return '%'; }
"=" { /*printf("EQ\n");*/ return EQ; }
">" { /*printf("GT\n");*/ return GT; }
"<" { /*printf("LT\n");*/ return LT; }
">=" { /*printf("GE\n");*/ return GE; }
"<=" { /*printf("LE\n");*/ return LE; }
"<>" { /*printf("NE\n");*/ return NE; }
{DATENUM} { yylval.string = get_text2(yytext); /*printf("DATENUM\n");*/ return DATENUM; }
{NAME} { yylval.string = get_text(yytext); /*printf("NAME\n");*/ return NAME; }
{TEXT} { yylval.string = get_text2(yytext); /*printf("TEXT\n");*/ return TEXT; }
{INUM} { yylval.string = get_text(yytext); /*printf("INUM\n");*/ return INUM; }
{FNUM} { yylval.string = get_text(yytext); /*printf("FNUM\n");*/ return FNUM; }
{BLANKCHAR} { /*printf("\n");*/ }
%%

/* C 语言用户子程序节:可选，包含规则节用到的局部 C 函数*/
//int yywrap() { return 1; }