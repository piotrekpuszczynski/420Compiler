COMPILER = g++
FLAGS = -std=c++17

all: compiler

compiler: parser.o lexer.o
	$(COMPILER) $(FLAGS) -o compiler parser.o lexer.o

parser.o: parser.tab.cpp
	$(COMPILER) $(FLAGS) -o parser.o -c parser.tab.cpp

lexer.o: lexer.c
	$(COMPILER) $(FLAGS) -o lexer.o -c lexer.cpp

parser.tab.cpp: parser.ypp
	bison -d parser.ypp
	
lexer.c: lexer.l
	flex -o lexer.cpp lexer.l