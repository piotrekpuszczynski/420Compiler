#include "symbol.hpp"
#include <iostream>
using namespace std;

Symbol::Symbol(long long offset) {
    this->offset = offset;
}

long long Symbol::getOffset() {
    return this->offset;
}

Symbol* Variable::getSymbol(long long) {
    return this;
}

Array::Array(long long offset, long long start, long long end) : Symbol(offset) {
    this->start = start;
    this->end = end;
    this->tab = new Variable*[end - start + 1];
    for (int i = 0; i < end - start + 1; i++)
        this->tab[i] = new Variable(this->getOffset() + i);
}

Symbol* Array::getSymbol(long long index) {
    return this->tab[index - start];
}
