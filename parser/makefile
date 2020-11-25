all:Lexer.c Parser.c
Lexer.c:Lexer.l
	flex Lexer.l
	mv lex.yy.c Lexer.c
Parser.c:Parser.y
	bison -vdt Parser.y
	mv Parser.tab.c Parser.c
	mv Parser.tab.h Parser.h
Lexer.o:Lexer.c Parser.h
	g++ -c Lexer.c -o Lexer.o
Parser.o:Parser.c Lexer.c Parser.h
	g++ -c Parser.c -o Parser.o
Parser:
	g++ Lexer.o Parser.o -o Parser
clean:
	rm Lexer.c Parser.c Parser.h Lexer.cpp Parser.cpp Parser.output