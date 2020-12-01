all:Parser.c Lexer.c Parser
Parser:Parser.o Lexer.o
	g++ -g Parser.o Lexer.o -o Parser
Lexer.c:Lexer.l
	flex Lexer.l
	mv lex.yy.c Lexer.c
Parser.c:Parser.y
	bison -vtd Parser.y -o Parser.c
Lexer.o:Lexer.c Parser.h
	g++ -g -c Lexer.c -o Lexer.o
Parser.o:Parser.c Lexer.c
	g++ -g -c Parser.c -o Parser.o
clean:
	rm -f Lexer.c Parser.c Parser.h Parser.output Lexer.o Parser.o Parser.exe