all:
	bison -d -Wall grammar.yy
	flex flex.l
	g++ -c lex.yy.c -o lexer.o -L"C:/gnuwin32/lib" -lfl -O3 -Wall
	g++ -c func.cpp -o func.o -O3 -Wall
	g++ -c Parser.cpp -o parser.o -L . -lfunc -llexer -L"C:/gnuwin32/lib" -lfl -O3 -Wall
	g++ -c ast.cpp -o ast.o  -O3 -Wall
	g++ -c parser_value.cpp -o parser_value.o  -O3 -Wall
	g++ -c spline.cpp -o spline.o  -O3 -Wall
	ar rcs libparser.a parser.o ast.o lexer.o func.o spline.o parser_value.o
	g++ main.cpp -L .  -lparser -lfl -o inter.exe  -L"C:/gnuwin32/lib" -lfl -Wall -O3
