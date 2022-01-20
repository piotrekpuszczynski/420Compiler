#include <cmath>
#include "code.hpp"

Code::Code() {
    this->k = 0;
    this->data = new Data();
    this->reset('a');
    this->reset('b');
    this->reset('c');
    this->reset('d');
    this->reset('e');
    this->reset('f');
    this->reset('g');
    this->reset('h');
    this->data->declareVariable("$$", Type::calc);
}

void Code::atomic(string instruction) {
    this->code.push_back(instruction + "\n");
    this->k++;
}

void Code::atomic(string instruction, long long value) {
    this->code.push_back(instruction + " " + to_string(value) + "\n");
    this->k++;
}

void Code::atomic(string instruction, char value) {
    this->code.push_back(instruction + " " + value + "\n");
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

void Code::jump() {
    this->atomic("JUMP");
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
    this->getSymbolOffset(id);
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getSymbolOffset(exp);
    this->load('a');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');
}

void Code::read(Symbol* var) {
    this->getSymbolOffset(var);
    this->swap('b');
    this->get();
    this->store('b');

    this->reset('a');
    this->reset('b');
}

void Code::write(Symbol* var) {
    this->getSymbolOffset(var);
    this->load('a');
    this->put();

    this->reset('a');
    this->reset('b');
}

Symbol* Code::plus(Symbol* a, Symbol* b) {
    this->getSymbolOffset(a);
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getSymbolOffset(b);
    this->load('a');
    this->add('c');

    this->swap('c');

    this->reset('a');
    // this->reset('b');

    // this->getOffset(0);
    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');
    return this->getSymbol("$$");
}

Symbol* Code::minus(Symbol* a, Symbol* b) {
    this->getSymbolOffset(b);
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getSymbolOffset(a);
    this->load('a');
    this->sub('c');

    this->swap('c');

    this->reset('a');
    // this->reset('b');

    // this->genOffset(0);
    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');
    return this->getSymbol("$$");
}

Symbol* Code::times(Symbol* a, Symbol* b) {
    this->getSymbolOffset(b);
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getSymbolOffset(a);
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
    // this->swap('c');
    this->reset('c');
    // this->genOffset(0);
    // this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    // this->reset('c');

    return this->getSymbol("$$");
}

Symbol* Code::div(Symbol* a, Symbol* b) {
    this->getSymbolOffset(a);
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getSymbolOffset(b);
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
    this->genOffset(0);
    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');

    return this->getSymbol("$$");
}

Symbol* Code::mod(Symbol* a, Symbol* b) {
    this->getSymbolOffset(a);
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getSymbolOffset(b);
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

    this->swap('c');
    this->sub('c');
    this->jneg(2);
    this->jump(-2);

    this->add('c');
    this->jump(8);

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
    this->genOffset(0);
    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');
    return this->getSymbol("$$");
}

Cond* Code::eq(Symbol* a, Symbol* b) {
    long long jumpTo = this->k;
    this->getSymbolOffset(b);
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getSymbolOffset(a);
    this->load('a');

    this->reset('b');

    this->sub('c');
    this->reset('c');

    this->jzero(2);
    long long start = this->k;
    this->jump();

    this->reset('a');
    return new Cond(start, jumpTo);
}

Cond* Code::neq(Symbol* a, Symbol* b) {
    long long jumpTo = this->k;
    this->getSymbolOffset(b);
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getSymbolOffset(a);
    this->load('a');

    this->reset('b');

    this->sub('c');
    this->reset('c');

    this->jzero(2);
    this->jump(2);
    long long start = this->k;
    this->jump();

    this->reset('a');
    return new Cond(start, jumpTo);
}

Cond* Code::le(Symbol* a, Symbol* b) {
    long long jumpTo = this->k;
    this->getSymbolOffset(b);
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getSymbolOffset(a);
    this->load('a');

    this->reset('b');

    this->sub('c');
    this->reset('c');

    this->jneg(2);
    long long start = this->k;
    this->jump();

    this->reset('a');
    return new Cond(start, jumpTo);
}

Cond* Code::ge(Symbol* a, Symbol* b) {
    long long jumpTo = this->k;
    this->getSymbolOffset(b);
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getSymbolOffset(a);
    this->load('a');

    this->reset('b');

    this->sub('c');
    this->reset('c');

    this->jpos(2);
    long long start = this->k;
    this->jump();

    this->reset('a');
    return new Cond(start, jumpTo);
}

Cond* Code::leq(Symbol* a, Symbol* b) {
    long long jumpTo = this->k;
    this->getSymbolOffset(b);
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getSymbolOffset(a);
    this->load('a');

    this->reset('b');

    this->sub('c');
    this->reset('c');

    this->jzero(3);
    this->jneg(2);
    long long start = this->k;
    this->jump();

    this->reset('a');
    return new Cond(start, jumpTo);
}

Cond* Code::geq(Symbol* a, Symbol* b) {
    long long jumpTo = this->k;
    this->getSymbolOffset(b);
    this->load('a');
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->getSymbolOffset(a);
    this->load('a');

    this->reset('b');

    this->sub('c');
    this->reset('c');

    this->jzero(3);
    this->jpos(2);
    long long start = this->k;
    this->jump();

    this->reset('a');
    return new Cond(start, jumpTo);
}

void Code::ifBlock(Cond* cond) {
    this->code[cond->start] += " " + to_string(this->k - cond->start) + "\n";
    this->reset('a');
}

void Code::ifElseFirstBlock(Cond* cond) {
    long long start = this->k;
    this->jump();
    this->ifBlock(cond);
    cond->start = start;
}

void Code::whileBlock(Cond* cond) {
    this->jump(cond->jumpTo - this->k);
    this->ifBlock(cond);
}

void Code::repeatUntilStart() {
    this->code.back() += "repeat";
}

void Code::repeatUntilBlock(Cond* cond) {
    long long jumpTo = 0;
    
    while (true) {
        jumpTo++;
        string s = "repeat";
        if (equal(s.rbegin(), s.rend(), code[code.size() - jumpTo].rbegin())) {
            code[code.size() - jumpTo] = code[code.size() - jumpTo].substr(0, code[code.size() - jumpTo].size() - 6);
            break;
        }
    }

    this->jump(-jumpTo);
    this->ifBlock(cond);
}

void Code::incForLoopCondition(string i, Symbol* a, Symbol* b) {
    this->data->declareVariable(i, Type::iterator);
    this->assign(getSymbol(i), a);
    Cond* cond = this->leq(getSymbol(i), b);
    this->code[cond->jumpTo] += "jumpto";
    this->code[cond->start] += "start";
    delete cond;
}

void Code::decForLoopCondition(string i, Symbol* a, Symbol* b) {
    this->data->declareVariable(i, Type::iterator);
    this->assign(getSymbol(i), a);
    Cond* cond = this->geq(getSymbol(i), b);
    this->code[cond->jumpTo] += "jumpto";
    this->code[cond->start] += "start";
    delete cond;
}

void Code::incForLoopEnd(string val) {
    long long jumpTo = 0;
    long long start = 0;

    this->getSymbolOffset(getSymbol(val));
    this->swap('b');
    this->load('b');
    this->inc('a');
    this->store('b');
    this->reset('a');
    this->reset('b');

    while (true) {
        jumpTo++;
        string s = "jumpto";
        if (equal(s.rbegin(), s.rend(), code[code.size() - jumpTo].rbegin())) {
            code[code.size() - jumpTo] = code[code.size() - jumpTo].substr(0, code[code.size() - jumpTo].size() - 6);
            break;
        }
    }

    while (true) {
        start++;
        string s = "start";
        if (equal(s.rbegin(), s.rend(), code[code.size() - start].rbegin())) {
            code[code.size() - start] = code[code.size() - start].substr(0, code[code.size() - start].size() - 5);
            break;
        }
    }

    this->jump(-jumpTo);
    this->code[this->k - start - 1] += " " + to_string(start + 1) + "\n";
    this->reset('a');
}

void Code::decForLoopEnd(string val) {
    long long jumpTo = 0;
    long long start = 0;
    
    this->getSymbolOffset(getSymbol(val));
    this->swap('b');
    this->load('b');
    this->dec('a');
    this->store('b');
    this->reset('a');
    this->reset('b');

    while (true) {
        jumpTo++;
        string s = "jumpto";
        if (equal(s.rbegin(), s.rend(), code[code.size() - jumpTo].rbegin())) {
            code[code.size() - jumpTo] = code[code.size() - jumpTo].substr(0, code[code.size() - jumpTo].size() - 6);
            break;
        }
    }

    while (true) {
        start++;
        string s = "start";
        if (equal(s.rbegin(), s.rend(), code[code.size() - start].rbegin())) {
            code[code.size() - start] = code[code.size() - start].substr(0, code[code.size() - start].size() - 5);
            break;
        }
    }

    this->jump(-jumpTo);
    this->code[this->k - start - 1] += " " + to_string(start + 1) + "\n";
    this->reset('a');
}

void Code::genOffset(long long offset) {
    if (offset == 0) return;
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

void Code::getSymbolOffset(Symbol* symbol) {
    this->genOffset(symbol->getOffset());

    if (symbol->type == Type::pointer)
        this->load('a');
}

void Code::genValue(long long value) {
    long long asAbs = abs(value);
    this->genOffset(asAbs);

    this->reset('b');
    
    if (value != asAbs) {
        this->swap('b');
        this->sub('b');
    }
}

void Code::declareVariable(string id, Type type) {
    this->data->declareVariable(id, type);
}

void Code::declareArray(string id, long long start, long long end) {
    this->data->declareArray(id, start, end);
}

bool Code::isDeclared(string id) {
    return this->data->isDeclared(id);
}

Symbol* Code::getSymbol(string id) {
    return this->data->getSymbol(id);
}

Symbol* Code::getSymbol(string arr, string index) {
    Array* array = reinterpret_cast<Array*>(this->getSymbol(arr));
    Symbol* indexSymbol = this->getSymbol(index);

    this->genOffset(this->getNumber(array->start)->getOffset());
    this->load('a');
    this->swap('c');
    this->reset('b');

    this->genOffset(indexSymbol->getOffset());
    this->load('a');
    this->sub('c');
    this->swap('c');
    this->reset('a');
    this->reset('b');

    this->genOffset(array->getOffset());
    this->reset('b');
    this->add('c');
    

    this->swap('c');
    this->reset('a');
    this->reset('b');
    string name = arr + "[" + index + "]";
    this->declareVariable(name, Type::pointer);
    this->genOffset(this->getSymbol(name)->getOffset());
    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');

    return this->getSymbol(name);
}

Symbol* Code::getSymbol(string id, long long index) {
    return this->data->getSymbol(id, index);
}

Symbol* Code::getNumber(long long value) {
    string asString = to_string(value);
    if (this->isDeclared(asString))
        return this->getSymbol(asString);

    this->declareVariable(asString, Type::constant);
    Symbol* var = this->getSymbol(asString);

    this->genOffset(var->getOffset());
    this->swap('c');

    this->reset('a');
    this->reset('b');

    this->genValue(value);
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');

    return var;
}

string Code::getCode() {
    string code = "";
    for (string command : this->code) code += command;
    return code;
}
