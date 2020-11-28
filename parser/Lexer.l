%option noyywrap
%option caseless

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
%}

/* 辅助定义节:可选，在此可以为正规式定义宏名字*/
NAME ([a-zA-z][0-9a-zA-z_]*)
TEXT (['][^\\\n\']*['])
INUM ([-]{0,1}[0-9]+)
FNUM ([-]{0,1}[0-9]*[.][0-9]*)
DATENUM ([0-9]{4}-[0-9]{2}-[0-9]{2})
BLANKCHAR ([ \f\r\t\v\n]+)

%%
CREATE { printf("CREATE"); return CREATE; }
DROP { printf("DROP"); return DROP; }
USE { printf("USE"); return USE; }
SHOW { printf("SHOW"); return SHOW; }
DESC { printf("DESC"); return DESC; }
ADD { printf("ADD"); return ADD; }
DATABASE { printf("DATABASE"); return DATABASE; }
DATABASES { printf("DATABASES"); return DATABASES; }
TABLE { printf("TABLE"); return TABLE; }
TABLES { printf("TABLES"); return TABLES; }
INDEX { printf("INDEX"); return INDEX; }
ALTER { printf("ALTER"); return ALTER; }
INSERT { printf("INSERT"); return INSERT; }
INTO { printf("INTO"); return INTO; }
VALUES { printf("VALUES"); return VALUES; }
DELETE { printf("DELETE"); return DELETE; }
FROM { printf("FROM"); return FROM; }
UPDATE { printf("UPDATE"); return UPDATE; }
SELECT { printf("SELECT"); return SELECT; }
WHERE { printf("WHERE"); return WHERE; }
IS { printf("IS"); return IS; }
NOT { printf("NOT"); return NOT; }
NULL { printf("NULL"); return NULLC; }
DEFAULT { printf("DEFAULT"); return DEFAULT; }
PRIMARY { printf("PRIMARY"); return PRIMARY; }
FOREIGN { printf("FOREIGN"); return FOREIGN; }
KEY { printf("KEY"); return KEY; }
REFERENCES { printf("REFERENCES"); return REFERENCES; }
RENAME { printf("RENAME"); return RENAME; }
TO { printf("TO"); return TO; }
ON { printf("ON"); return ON; }
AND { printf("AND"); return AND; }
SET { printf("SET"); return SET; }
Int { printf("INTEGER"); return INTEGER; }
SmallInt { printf("SMALLINT"); return SMALLINT; }
Char { printf("CHAR"); return CHAR; }
Double { printf("DOUBLE"); return DOUBLE; }
Float { printf("FLOAT"); return FLOAT; }
Date { printf("DATETYPE"); return DATETYPE; }
Numeric { printf("NUMERICTYPE"); return NUMERICTYPE; }
"(" { printf("("); return '('; }
")" { printf(")"); return ')'; }
";" { printf(";"); return ';'; }
"," { printf(","); return ','; }
"+"	{ printf("+"); return '+'; }
"-"	{ printf("-"); return '-'; }
"*"	{ printf("*"); return '*'; }
"/"	{ printf("/"); return '/'; }
"%"	{ printf("%"); return '%'; }
"=" { printf("EQ"); return EQ; }
">" { printf("GT"); return GT; }
"<" { printf("LT"); return LT; }
">=" { printf("GE"); return GE; }
"<=" { printf("LE"); return LE; }
"<>" { printf("NE"); return NE; }
{NAME} { yylval.string = get_text(yytext); printf("NAME"); return NAME; }
{TEXT} { yylval.string = get_text(yytext); printf("TEXT"); return TEXT; }
{INUM} { yylval.string = get_text(yytext); printf("INUM"); return INUM; }
{FNUM} { yylval.string = get_text(yytext); printf("FNUM"); return FNUM; }
{DATENUM} { yylval.string = get_text(yytext); printf("DATENUM"); return DATENUM; }
{BLANKCHAR} { printf("\n"); }
%%

/* C 语言用户子程序节:可选，包含规则节用到的局部 C 函数*/
//int yywrap() { return 1; }