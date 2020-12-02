all:Parser.c Lexer.c Parser
Parser:Parser.c Lexer.c
	g++ -g Parser.cpp -o Parser	
Lexer.c:Lexer.l
	flex Lexer.l
	mv lex.yy.c Lexer.cpp
Parser.c:Parser.y
	bison -vtd Parser.y -o Parser.c
	mv Parser.c Parser.cpp
clean:
	rm -f Lexer.cpp Parser.cpp Parser.h Parser.output Lexer.o Parser.o Parser.exe