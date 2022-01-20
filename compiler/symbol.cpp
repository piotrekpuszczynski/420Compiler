#include "symbol.hpp"

Symbol::Symbol(long long offset, Type type) : offset(offset), type(type) {}

long long Symbol::getOffset() {
    return this->offset;
}

Symbol* Variable::getSymbol(long long) {
    return this;
}

Array::Array(long long offset, long long start, long long end) : Symbol(offset, Type::array), start(start), end(end) {
    this->tab = new Variable*[end - start + 1];
    for (int i = 0; i < end - start + 1; i++)
        this->tab[i] = new Variable(this->getOffset() + i, Type::variable);
}

Symbol* Array::getSymbol(long long index) {
    return this->tab[index - start];
}
