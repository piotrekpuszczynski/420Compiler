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
    void declareVariable(string);
    void declareArray(string, long long, long long);
    bool isDeclared(string);
    Symbol* getSymbol(string);
    Symbol* getSymbol(string, long long);
};

struct Cond {
    long long start;
    Symbol* symbol;

    Cond(long long start, Symbol* symbol) {
        this->start = start;
        this->symbol = symbol;
    }
};
