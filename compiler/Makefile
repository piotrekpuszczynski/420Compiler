CC = g++
FLAGS = -std=c++17

all: compiler

compiler: parser.o lexer.o
	$(CC) $(FLAGS) -o compiler parser.o lexer.o

parser.o: parser.tab.cpp
	$(CC) $(FLAGS) -o parser.o -c parser.tab.cpp

lexer.o: lexer.tab.cpp
	$(CC) $(FLAGS) -o lexer.o -c lexer.tab.cpp

parser.tab.cpp: parser.ypp
	bison -d parser.ypp
	
lexer.tab.cpp: lexer.l
	flex -o lexer.tab.cpp lexer.l

clean:
	rm -f *.o *.tab.cpp *.tab.hpp

cleanall: clean
	rm -f compiler
