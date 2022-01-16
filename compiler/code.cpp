#include <string>
#include <cmath>
#include <iostream>
#include "code.hpp"
#include "data.hpp"
using namespace std;

Code::Code(Data* data) {
    this->k = 0;
    this->code = "";
    this->data = data;
    this->reset('a');
    this->reset('b');
    this->reset('c');
    this->reset('d');
    this->reset('e');
    this->reset('f');
    this->reset('g');
    this->reset('h');
    this->data->declareVariable("$$");
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

void Code::assign(Symbol* id, Symbol* exp) {
    this->getMemory(id->getOffset());
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getMemory(exp->getOffset());
    this->load('a');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');
}

void Code::read(Symbol* var) {
    this->getMemory(var->getOffset());
    this->swap('b');
    this->get();
    this->store('b');

    this->reset('a');
    this->reset('b');
}

void Code::write(Symbol* var) {
    this->getMemory(var->getOffset());
    this->load('a');
    this->put();

    this->reset('a');
    this->reset('b');
}

Symbol* Code::plus(Symbol* a, Symbol* b) {
    this->getMemory(b->getOffset());
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getMemory(a->getOffset());
    this->load('a');
    this->add('c');

    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getMemory(0);
    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');
    return this->data->getSymbol("$$");
}

Symbol* Code::minus(Symbol* a, Symbol* b) {
    this->getMemory(b->getOffset());
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getMemory(a->getOffset());
    this->load('a');
    this->sub('c');

    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getMemory(0);
    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');
    return this->data->getSymbol("$$");
}

Symbol* Code::times(Symbol* a, Symbol* b) {
    this->getMemory(b->getOffset());
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getMemory(a->getOffset());
    this->load('a');

    this->reset('b');

    this->jzero(15);

    this->jneg(7);
    this->dec('a');
    this->swap('b');
    this->add('c');
    this->swap('b');
    this->jzero(9);
    this->jump(-5);

    this->jpos(7);
    this->inc('a');
    this->swap('b');
    this->sub('c');
    this->swap('b');
    this->jzero(2);
    this->jump(-5);

    this->swap('b');
    this->swap('c');
    this->reset('a');
    this->getMemory(0);
    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');

    return this->data->getSymbol("$$");
}

Symbol* Code::div(Symbol* a, Symbol* b) {
    this->getMemory(a->getOffset());
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getMemory(b->getOffset());
    this->load('a');

    this->reset('b');

    this->jzero(18);

    this->swap('c');
    this->jpos(4); // if a is neg changes it to pos
    this->swap('b');
    this->sub('b');
    this->reset('b');

    this->swap('c');
    this->jneg(6);
    //b+
    this->swap('c');
    this->sub('c');
    this->jneg(8);
    this->inc('b');
    this->jump(-3);
    //b-
    this->swap('c');
    this->add('c');
    this->jneg(3);
    this->dec('b');
    this->jump(-3);

    this->swap('b');
    this->swap('c');
    this->reset('a');
    this->reset('b');
    this->getMemory(0);
    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');

    return this->data->getSymbol("$$");
}

Symbol* Code::mod(Symbol* a, Symbol* b) {

    this->getMemory(a->getOffset());
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getMemory(b->getOffset());
    this->load('a');

    this->reset('b');

    this->jzero(19);

    this->swap('c');
    this->jpos(4);
    this->swap('b');
    this->sub('b');
    this->reset('b');

    this->swap('c');
    this->jneg(7);
    //b+
    this->swap('c');
    this->sub('c');
    this->jneg(2);
    this->jump(-2);

    this->add('c');
    this->jump(6);

    //b-
    this->swap('c');
    this->add('c');
    this->jneg(2);
    this->jump(-2);

    this->sub('c');
    this->swap('b');
    this->sub('b');

    this->swap('c');
    this->reset('a');
    this->reset('b');
    this->getMemory(0);
    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');
    return this->data->getSymbol("$$");
}

void Code::incLoop(long long) {

}

void Code::decLoop(long long) {

}

void Code::getMemory(long long offset) {
    long long temp = offset;
    long long memory = 0;

    while (temp > 1) {
        temp /= 2;
        memory++;
    }

    temp = offset;
    temp = temp - pow(2, memory);

    for (int i = 0; i < memory; i++) this->inc('b');
    this->inc('a');
    this->shift('b');
    for (int i = 0; i < temp; i++) this->inc('a');
}

void Code::getValue(long long value) {
    long long asAbs = abs(value);
    this->getMemory(asAbs);

    this->reset('b');
    
    if (value != asAbs) {
        this->swap('b');
        this->sub('b');
    }
}

string Code::getCode() {
    return this->code;
}

Symbol* Code::getSymbol(string id) {
    return this->data->getSymbol(id);
}

Symbol* Code::getSymbol(string id, string index) {
    this->getMemory(this->data->getSymbol(index)->getOffset());

    return this->data->getSymbol(id, 0);
}

Symbol* Code::getSymbol(string id, long long index) {
    return this->data->getSymbol(id, index);
}

Symbol* Code::getNumber(long long value) {
    string asString = to_string(value);
    if (this->data->isDeclared(asString))
        return this->getSymbol(asString);

    this->data->declareVariable(asString);
    Symbol* var = this->getSymbol(asString);

    this->getMemory(var->getOffset());
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getValue(value);
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');

    return var;
}
