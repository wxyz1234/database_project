%option caseless
%option case-insensitive

%{
/* 定义节:可选，包含头文件、宏定义或全局 C 代码*/
#include "tree.h"
#include "../parser/Parser.h"

char *get_text(const char *text) {
    int length = strlen(text);
    char *buffer = new char[length + 1];
    memcpy(buffer, text, (length + 1) * sizeof(char));
    return buffer;
}
%}

/* 辅助定义节:可选，在此可以为正规式定义宏名字*/
DIGIT ([0-9])
ONECHAR ([^\\\n\'])
NAME ([a-zA-z][0-9a-zA-z_]*)
TEXT ([']ONECHAR*['])
INUM ([-]{0,1}DIGIT+)
FNUM ([-]{0,1}DIGIT*[.]DIGIT*)
DATENUM (DIGIT{4}-DIGIT{2}-DIGIT{2})

%%
CREATE { return CREATE; }
DROP { return DROP; }
USE { return USE; }
SHOW { return SHOW; }
DESC { return DESC; }
ADD { return ADD; }
DATABASE { return DATABASE; }
DATABASES { return DATABASES; }
TABLE { return TABLE; }
TABLES { return TABLES; }
INDEX { return INDEX; }
ALTER { return ALTER; }
INSERT { return INSERT; }
INTO { return INTO; }
VALUES { return VALUES; }
DELETE { return DELETE; }
FROM { return FROM; }
UPDATE { return UPDATE; }
SELECT { return SELECT; }
WHERE { return WHERE; }
IS { return IS; }
NOT { return NOT; }
NULL { return NULLC; }
DEFAULT { return DEFAULT; }
PRIMARY { return PRIMARY; }
FOREIGN { return FOREIGN; }
KEY { return KEY; }
REFERENCES { return REFERENCES; }
RENAME { return RENAME; }
TO { return TO; }
ON { return ON; }
AND { return AND; }
SET { return SET; }
Int { return INTEGER; }
SmallInt { return SMALLINT; }
Char { return CHAR; }
Double { return DOUBLE; }
Float { return FLOAT; }
Date { return DATETYPE; }
Numeric { return NUMERICTYPE; }
"(" { return '('; }
")" { return ')'; }
"," { return ','; }
";" { return ';'; }
"+"	{ return '+'; }
"-"	{ return '-'; }
"*"	{ return '*'; }
"/"	{ return '/'; }
"%"	{ return '%'; }
"=" { return EQ; }
">" { return GT; }
"<" { return LT; }
">=" { return GE; }
"<=" { return LE; }
"<>" { return NE; }
{NAME} { yylval.string = get_text(yytext); return NAME; }
{TEXT} { yylval.string = get_text(yytext); return TEXT; }
{INUM} { yylval.string = get_text(yytext); return INUM; }
{FNUM} { yylval.string = get_text(yytext); return FNUM; }
{DATENUM} { yylval.string = get_text(yytext); return DATENUM; }
%%

/* C 语言用户子程序节:可选，包含规则节用到的局部 C 函数*/
int yywrap() { 
    return 1;
}