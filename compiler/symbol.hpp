#pragma once

enum class Type {
    calc,
    variable,
    array,
    pointer,
    iterator,
    constant
};

class Symbol {
public:
    long long offset;
    Type type;

    Symbol(long long, Type);
    long long getOffset();
    virtual Symbol* getSymbol(long long) = 0;
};

class Variable : public Symbol {
    bool initialized;
public:
    Variable(long long, Type);
    using Symbol::Symbol;
    using Symbol::getOffset;
    Symbol* getSymbol(long long);
    bool isInitialized();
    void isInitialized(bool);
};

class Array : public Symbol {
public:
    long long start;
    long long end;
    Variable** tab;

    Array(long long, long long, long long);
    using Symbol::getOffset;
    Symbol* getSymbol(long long);
    void declareVariable(long long);
};
