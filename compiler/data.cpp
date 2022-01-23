#include <string>
#include "data.hpp"

extern int yyerror(string);

Data::Data() {
    this->offset = 0;
}

void Data::declareVariable(string id, Type type) {
    if (this->isDeclared(id))
        yyerror("variable" + id + "is already declared");
    this->variables[id] = new Variable(this->offset, type);
    this->offset++;
}

void Data::declareArray(string id, long long start, long long end) {
    if (this->isDeclared(id))
        yyerror("variable" + id + "is already declared");
    this->variables[id] = new Array(this->offset, start, end);
    this->offset += end - start + 1;
}

bool Data::isDeclared(string id) {
    return this->variables.find(id) != variables.end();
}

Symbol* Data::getSymbol(string id) {
    return this->variables[id];
}

Symbol* Data::getSymbol(string id, long long index) {
    return this->variables[id]->getSymbol(index);
}
