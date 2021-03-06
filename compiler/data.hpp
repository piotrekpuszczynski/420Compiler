#pragma once

#include <string>
#include <unordered_map>
#include "symbol.hpp"
using namespace std;

class Data {
public:
    long long offset;
    unordered_map<string, Symbol*> variables;

    Data();
    void declareVariable(string, Type);
    void declareArray(string, long long, long long);
    bool isDeclared(string);
    Symbol* getSymbol(string);
    Symbol* getSymbol(string, long long);
};

struct Cond {
    long long start;
    long long jumpTo;

    Cond(long long start, long long jumpTo) {
        this->start = start;
        this->jumpTo = jumpTo;
    }
};
