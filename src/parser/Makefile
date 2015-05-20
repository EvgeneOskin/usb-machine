all:
	bison -d -Wall grammar.yy
	flex flex.l
	g++ -c lex.yy.c -o lexer.o -O3 -Wall
	g++ -c parsertypes.cpp -o parsertypes.o -O3 -Wall
	g++ -c Parser.cpp -o parser.o -O3 -Wall
	g++ -c ast.cpp -o ast.o  -O3 -Wall
	g++ -c parser_value.cpp -o parser_value.o  -O3 -Wall
	g++ -c spline.cpp -o spline.o  -O3 -Wall
	ar rcs libparser.a parser.o ast.o lexer.o parsertypes.o spline.o parser_value.o
	g++ main.cpp -L . -lparser -o inter.exe  -L"C:/gnuwin32/lib" -lfl -Wall -O3
