#include <string>
#include "symbol.hpp"

extern int yyerror(std::string);

Symbol::Symbol(long long offset, Type type) : offset(offset), type(type) {}

long long Symbol::getOffset() {
    return this->offset;
}

Symbol* Variable::getSymbol(long long) {
    return this;
}

Variable::Variable(long long offset, Type type) : Symbol(offset, type) {
    if (type == Type::constant || type == Type::calc || type == Type::pointer) isInitialized(true);
    else isInitialized(false);
}

bool Variable::isInitialized() {
    return this->initialized;
}

void Variable::isInitialized(bool initialized) {
    this->initialized = initialized;
}

Array::Array(long long offset, long long start, long long end) : Symbol(offset, Type::array), start(start), end(end) {
    if (end < start) yyerror("incorrect array bounds");
    this->tab = new Variable*[end - start + 1];
    for (int i = 0; i < end - start + 1; i++)
        this->tab[i] = new Variable(this->getOffset() + i, Type::variable);
}

Symbol* Array::getSymbol(long long index) {
    return this->tab[index - start];
}
