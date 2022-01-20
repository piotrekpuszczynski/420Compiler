#include "data.hpp"

Data::Data() {
    this->offset = 0;
}

// TODO exception if variable is already defined
void Data::declareVariable(string id, Type type) {
    if (!this->isDeclared(id)) {
        this->variables[id] = new Variable(this->offset, type);
        this->offset++;
    }
}

// TODO exception if array is already defined
void Data::declareArray(string id, long long start, long long end) {
    if (!this->isDeclared(id)) {
        this->variables[id] = new Array(this->offset, start, end);
        this->offset += end - start + 1;
    }
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
