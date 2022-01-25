#include <string>
#include "data.hpp"

extern int yyerror(string);

Data::Data() {
    this->offset = 0;
}

void Data::declareVariable(string id, Type type) {
    if (this->isDeclared(id))
        yyerror("variable " + id + " is already declared");
    this->variables[id] = new Variable(this->offset, type);
    this->offset++;
}

void Data::declareArray(string id, long long start, long long end) {
    if (this->isDeclared(id))
        yyerror("variable " + id + " is already declared");
    this->variables[id] = new Array(this->offset, start, end);
    this->offset += end - start + 1;
}

bool Data::isDeclared(string id) {
    return this->variables[id] != nullptr;
}

Symbol* Data::getSymbol(string id) {
    if (!isDeclared(id))
        yyerror("variable " + id + " isn't declared yet");
    return this->variables[id];
}

Symbol* Data::getSymbol(string id, long long index) {
    dynamic_cast<Array*>(this->variables[id])->declareVariable(index);
    dynamic_cast<Variable*>(this->variables[id]->getSymbol(index))->isInitialized(true);
    if (!isDeclared(id))
        yyerror("variable " + id + " isn't declared yet");
    return this->variables[id]->getSymbol(index);
}
