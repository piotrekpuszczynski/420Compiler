#pragma once

class Symbol {
public:
    long long offset;

    Symbol(long long);
    long long getOffset();
    virtual Symbol* getSymbol(long long) = 0;
};

class Variable : public Symbol {
public:
    using Symbol::Symbol;
    using Symbol::getOffset;
    Symbol* getSymbol(long long);
};

class Array : public Symbol {
public:
    long long start;
    long long end;
    Variable** tab;

    Array(long long, long long, long long);
    using Symbol::getOffset;
    Symbol* getSymbol(long long);
};
