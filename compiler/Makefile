CC = g++
FLAGS = -W -pedantic -std=c++17 -O3
FILES = parser.o lexer.o main.o

all: compiler clean

compiler: $(FILES)
	$(CC) $(FLAGS) -o compiler $(FILES)

%.o: %.cpp
	$(CC) $(FLAGS) -c $^

parser.cpp: parser.ypp
	bison -d -o parser.cpp parser.ypp
	
lexer.cpp: lexer.l
	flex -o lexer.cpp lexer.l

clean:
	rm -f *.o parser.cpp parser.hpp lexer.cpp

cleanall: clean
	rm -f compiler
