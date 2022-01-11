#include <string>
#include <cmath>
#include "code.hpp"
#include "data.hpp"
using namespace std;

Code::Code(Data* data) {
    this->k = 0;
    this->code = "";
    this->data = data;
}

void Code::atomic(string instruction) {
    this->code += instruction + "\n";
    this->k++;
}

void Code::atomic(string instruction, long long value) {
    this->code += instruction + " " + to_string(value) + "\n";
    this->k++;
}

void Code::atomic(string instruction, char value) {
    this->code += instruction + " " + value + "\n";
    this->k++;
}

void Code::get() {
    this->atomic("GET");
}

void Code::put() {
    this->atomic("PUT");
}

void Code::load(char x) {
    this->atomic("LOAD", x);
}

void Code::store(char x) {
    this->atomic("STORE", x);
}

void Code::add(char x) {
    this->atomic("ADD", x);
}

void Code::sub(char x) {
    this->atomic("SUB", x);
}

void Code::shift(char x) {
    this->atomic("SHIFT", x);
}

void Code::swap(char x) {
    this->atomic("SWAP", x);
}

void Code::reset(char x) {
    this->atomic("RESET", x);
}

void Code::inc(char x) {
    this->atomic("INC", x);
}

void Code::dec(char x) {
    this->atomic("DEC", x);
}

void Code::jump(long long j) {
    this->atomic("JUMP", j);
}

void Code::jpos(long long j) {
    this->atomic("JPOS", j);
}

void Code::jzero(long long j) {
    this->atomic("JZERO", j);
}

void Code::jneg(long long j) {
    this->atomic("JNEG", j);
}

void Code::halt() {
    this->atomic("HALT");
}

void Code::assign(long long value) {
    
}

void Code::read(Variable* var) {
    long long offset = var->getOffset();
    long long memory = 0;

    while (offset > 0) {
        offset /= 2;
        memory++;
    }

    offset = var->getOffset();
    offset = offset - pow(2, memory);

    this->reset('b');
    for (int i = 0; i < memory; i++) this->inc('b');

    this->reset('a');
    this->inc('a');
    this->shift('b');
    for (int i = 0; i < offset; i++) this->inc('a');
    this->swap('b');
    this->get();
    this->store('b');
}

void Code::write(Variable* var) {
    long long offset = var->getOffset();
    long long memory = 0;

    while (offset > 0) {
        offset /= 2;
        memory++;
    }

    offset = var->getOffset();
    offset = offset - pow(2, memory);

    this->reset('b');
    for (int i = 0; i < memory; i++) this->inc('b');

    this->reset('a');
    this->inc('a');
    this->shift('b');
    for (int i = 0; i < offset; i++) this->inc('a');
    this->load('a');
    this->put();
}

string Code::getCode() {
    return this->code;
}

Variable* Code::getVariable(string id) {
    return this->data->getVariable(id);
}

Variable* Code::getVariable(string id, string index) {
    return this->data->getVariable(id);
}

Variable* Code::getVariable(string id, long long index) {
    return this->data->getVariable(id);
}

Variable* Code::getNumber(long long value) {
    if (this->data->isDeclared(to_string(value))) {
        return this->getVariable(to_string(value));
    }
    this->data->declareVariable(to_string(value));
    return this->getVariable(to_string(value));
}
