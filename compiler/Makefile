CC = g++
FLAGS = -W -Wall -pedantic -std=c++17 -O3
FILES = parser.o lexer.o data.o symbol.o code.o main.o

all: compiler

compiler: $(FILES)
	$(CC) -o compiler $(FILES)

%.o: %.cpp
	$(CC) $(FLAGS) -c $^

parser.cpp: parser.y
	bison -d -o parser.cpp parser.y
	
lexer.cpp: lexer.l
	flex -o lexer.cpp lexer.l

clean:
	rm -f *.o parser.cpp parser.hpp lexer.cpp

cleanall: clean
	rm -f compiler
