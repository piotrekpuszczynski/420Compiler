CC = g++
FLAGS = -std=c++17

all: compiler

compiler: parser.o lexer.o
	$(CC) $(FLAGS) -o compiler parser.o lexer.o

parser.o: parser.cpp
	$(CC) $(FLAGS) -o parser.o -c parser.cpp

lexer.o: lexer.cpp
	$(CC) $(FLAGS) -o lexer.o -c lexer.cpp

parser.cpp: parser.ypp
	bison -d -o parser.cpp parser.ypp
	
lexer.cpp: lexer.l
	flex -o lexer.cpp lexer.l

clean:
	rm -f *.o parser.cpp parser.hpp lexer.cpp

cleanall: clean
	rm -f compiler
