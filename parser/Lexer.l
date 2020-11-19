%option caseless
%option case-insensitive

%{
/* 定义节:可选，包含头文件、宏定义或全局 C 代码*/
}%

/* 辅助定义节:可选，在此可以为正规式定义宏名字*/
DIGIT ([0-9])
ONECHAR ([^\\\n\'])
NAME ([a-zA-z][0-9a-zA-z_]*)
TEXT ([']ONECHAR*['])
INUM ([-]{0,1}DIGIT+)
FNUM ([-]{0,1}DIGIT*[.]DIGIT*)
DATE (DIGIT{4}-DIGIT{2}-DIGIT{2})

%%
/* 规则节:源程序的主体，不可或缺，由模式（Lex 正规表达式）和动作（C 语句或一段 C 程序）组成 */
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
NULL { return NULL; }
DEFAULT { return DEFAULT; }
PRIMARY { return PRIMARY; }
FOREIGN { return FOREIGN; }
KEY { return KEY; }
REFERENCES { return REFERENCES; }
RENAME { return RENAME; }
TO { return TO; }
Int { return INT; }
SmallInt { return SMALLINT; }
Char { return CHAR; }
Double { return DOUBLE; }
Float { return FLOAT; }
Date { return DATE; }
Numeric { return NUMERIC; }
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
{DATE} { yylval.string = get_text(yytext); return DATE; }
%%

/* C 语言用户子程序节:可选，包含规则节用到的局部 C 函数*/
int yywrap() { 
    return 1;
}