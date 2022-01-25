#include <cmath>
#include "code.hpp"

extern int yyerror(string);

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
    this->code.push_back("JUMP");
    this->k++;
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
    if (!dynamic_cast<Variable*>(exp)->isInitialized())
        yyerror("use of uninitialized variable");
    if (dynamic_cast<Array*>(id) == nullptr)
        dynamic_cast<Variable*>(id)->isInitialized(true);
    this->getSymbolOffset(id);
    this->swap('c');

    this->reset('b');

    this->getSymbolOffset(exp);
    this->load('a');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');
}

void Code::read(Symbol* var) {
    dynamic_cast<Variable*>(var)->isInitialized(true);
    this->getSymbolOffset(var);
    this->swap('b');
    this->get();
    this->store('b');

    this->reset('a');
    this->reset('b');
}

void Code::write(Symbol* var) {
    if (!dynamic_cast<Variable*>(var)->isInitialized())
        yyerror("use of uninitialized variable");
    this->getSymbolOffset(var);
    this->load('a');
    this->put();

    this->reset('a');
    this->reset('b');
}

Symbol* Code::plus(Symbol* a, Symbol* b) {
    this->loadSymbols(b, a);
    
    this->add('c');

    this->swap('c');

    this->reset('a');

    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');
    return this->getSymbol("$$");
}

Symbol* Code::minus(Symbol* a, Symbol* b) {
    this->loadSymbols(b, a);

    this->sub('c');

    this->swap('c');

    this->reset('a');

    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');
    return this->getSymbol("$$");
}

Symbol* Code::times(Symbol* a, Symbol* b) {
    this->loadSymbols(a, b);
    
    this->inc('e');
    this->dec('d');

    // check a
    this->jzero(7);
    this->jpos(4);
    this->dec('h');
    this->swap('f');
    this->sub('f');
    this->swap('c');
    this->swap('g');
    this->swap('c');
    
    // check b
    this->jzero(20);
    this->swap('c');
    this->reset('f');
    this->swap('f');
    
    // parzystosc B
    this->add('c');
    this->shift('d');
    this->shift('e');
    this->sub('c');
    this->jzero(4);
    this->swap('f');
    this->add('g');
    this->jump(2);
    this->swap('f');
    this->swap('g');
    this->shift('e');
    this->swap('g');
    this->swap('c');
    this->shift('d');
    this->swap('c');
    this->jump(-20);
    this->swap('h');
    this->jzero(4);
    this->reset('a');
    this->sub('c');
    this->jump(2);
    this->swap('c');

    this->store('b');

    this->reset('a');
    this->reset('c');
    this->reset('d');
    this->reset('e');
    this->reset('f');
    this->reset('g');
    this->reset('h');

    return this->getSymbol("$$");
}

Symbol* Code::div(Symbol* a, Symbol* b) {
    this->loadSymbols(b, a);

    this->swap('b');
    this->swap('c');

    this->inc('c');
    this->dec('d');

    this->jzero(66);
    this->jpos(6);
    this->inc('e');
    this->inc('e');
    this->swap('f');
    this->sub('f');
    this->reset('f');
    this->swap('b');
    this->jzero(58);
    this->jpos(5);
    this->inc('e');
    this->swap('f');
    this->sub('f');
    this->reset('f');
    // h = dlugosc bitowa a
    this->swap('g');
    this->add('g');
    this->jzero(4);
    this->shift('d');
    this->inc('h');
    this->jump(-3);
    this->swap('g');
    // g dlugosc a wartosc
    this->swap('b');
    // g = dlugosc bitowa b
    this->swap('f');
    this->add('f');
    this->jzero(4);
    this->shift('d');
    this->inc('g');
    this->jump(-3);
    this->swap('f');
    this->swap('b');
    this->swap('h');
    // roznica dlugosci
    this->sub('g');
    this->jneg(35);
    this->reset('f');
    this->swap('f');
    this->add('f');
    this->swap('f');
    this->inc('f');
    // a roznica h g
    // wyrownanie do lewej
    this->jzero(6);
    this->swap('b');
    this->shift('c');
    this->dec('b');
    this->swap('b');
    this->jump(-5);
    this->swap('h');
    // a i wyrownane b
    this->reset('h');
    this->swap('f');
    // petla
    this->jzero(19);
    this->reset('g');
    this->swap('g');
    this->add('f');
    this->sub('b');
    this->swap('h');
    this->shift('c');
    this->swap('h');
    this->jneg(5);
    this->inc('h');
    this->swap('f');
    this->sub('b');
    this->swap('f');
    this->swap('b');
    this->shift('d');
    this->swap('b');
    this->swap('g');
    this->dec('a');
    this->jump(-18);
    this->jump(6);
    this->swap('h');
    this->swap('f');
    this->add('f');
    this->swap('f');
    this->reset('h');
    this->swap('h');

    // spr
    this->swap('e');
    this->jzero(16);
    this->dec('a');
    this->jzero(4);
    this->dec('a');
    this->jzero(2);
    // dwa minusy
    this->jump(11);
    // jeden minus
    this->reset('g');
    this->swap('e');
    this->swap('g');
    this->sub('g');
    this->swap('e');
    this->swap('f');
    this->jzero(4);
    this->swap('e');
    this->sub('c');
    this->swap('e');
    this->swap('e');
    
    this->reset('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('d');
    this->reset('e');
    this->reset('f');
    this->reset('g');
    this->reset('h');

    return this->getSymbol("$$");
}

Symbol* Code::mod(Symbol* a, Symbol* b) {
    this->loadSymbols(b, a);

    this->swap('b');
    this->swap('c');
 
    this->dec('d');

    this->swap('c');
    this->add('c');
    this->swap('c');
    this->jzero(74);
    this->jpos(6);
    this->inc('e');
    this->inc('e');
    this->swap('f');
    this->sub('f');
    this->reset('f');
    this->swap('b');
    this->jzero(66);
    this->jpos(5);
    this->inc('e');
    this->swap('f');
    this->sub('f');
    this->reset('f');
    // h = dlugosc bitowa a
    this->swap('g');
    this->add('g');
    this->jzero(4);
    this->shift('d');
    this->inc('h');
    this->jump(-3);
    this->swap('g');
    // g dlugosc a wartosc
    this->swap('b');
    // g = dlugosc bitowa b
    this->swap('f');
    this->add('f');
    this->jzero(4);
    this->shift('d');
    this->inc('g');
    this->jump(-3);
    this->swap('f');
    this->swap('b');
    this->swap('h');
    // roznica dlugosci
    this->sub('g');
    this->jneg(44);
    this->reset('f');
    this->swap('f');
    this->add('f');
    this->swap('f');
    this->inc('f');
    // a roznica h g
    // wyrownanie do lewej
    this->jzero(10);
    this->swap('b');
    this->inc('d');
    this->inc('d');
    this->shift('d');
    this->dec('d');
    this->dec('d');
    this->dec('b');
    this->swap('b');
    this->jump(-9);
    this->swap('h');
    // a i wyrownane b
    this->reset('h');
    this->swap('f');
    // petla
    this->jzero(23);
    this->reset('g');
    this->swap('g');
    this->add('f');
    this->sub('b');
    this->swap('h');
    this->inc('d');
    this->inc('d');
    this->shift('d');
    this->dec('d');
    this->dec('d');
    this->swap('h');
    this->jneg(5);
    this->inc('h');
    this->swap('f');
    this->sub('b');
    this->swap('f');
    this->swap('b');
    this->shift('d');
    this->swap('b');
    this->swap('g');
    this->dec('a');
    this->jump(-22);
    this->swap('f');
    this->jump(2);
    this->swap('h');
    // spr
    this->swap('e');
    this->jzero(21);
    this->dec('a');
    this->jzero(13);
    this->dec('a');
    this->jzero(7);
    // dwa minusy
    this->reset('g');
    this->swap('e');
    this->swap('g');
    this->sub('g');
    this->swap('e');
    this->jump(11);
    // minus w B
    this->swap('e');
    this->add('c');
    this->swap('e');
    this->jump(7);
    // minus w A
    this->reset('g');
    this->swap('e');
    this->swap('g');
    this->sub('g');
    this->add('c');
    this->swap('e');
    this->swap('e');

    this->reset('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('d');
    this->reset('e');
    this->reset('f');
    this->reset('g');
    this->reset('h');
    return this->getSymbol("$$");
}

Cond* Code::eq(Symbol* a, Symbol* b) {
    long long jumpTo = this->k, start;
    this->loadSymbols(b, a);

    this->sub('c');
    this->reset('c');

    this->jzero(2);
    start = this->k;
    this->jump();

    this->reset('a');
    return new Cond(start, jumpTo);
}

Cond* Code::neq(Symbol* a, Symbol* b) {
    long long jumpTo = this->k, start;
    this->loadSymbols(b, a);

    this->sub('c');
    this->reset('c');

    this->jzero(2);
    this->jump(2);
    start = this->k;
    this->jump();

    this->reset('a');
    return new Cond(start, jumpTo);
}

Cond* Code::le(Symbol* a, Symbol* b) {
    long long jumpTo = this->k, start;
    this->loadSymbols(b, a);

    this->sub('c');
    this->reset('c');

    this->jneg(2);
    start = this->k;
    this->jump();

    this->reset('a');
    return new Cond(start, jumpTo);
}

Cond* Code::ge(Symbol* a, Symbol* b) {
    long long jumpTo = this->k, start;
    this->loadSymbols(b, a);

    this->sub('c');
    this->reset('c');

    this->jpos(2);
    start = this->k;
    this->jump();

    this->reset('a');
    return new Cond(start, jumpTo);
}

Cond* Code::leq(Symbol* a, Symbol* b) {
    long long jumpTo = this->k, start;
    this->loadSymbols(b, a);

    this->sub('c');
    this->reset('c');

    this->jzero(3);
    this->jneg(2);
    start = this->k;
    this->jump();

    this->reset('a');
    return new Cond(start, jumpTo);
}

Cond* Code::geq(Symbol* a, Symbol* b) {
    long long jumpTo = this->k, start;
    this->loadSymbols(b, a);

    this->sub('c');
    this->reset('c');

    this->jzero(3);
    this->jpos(2);
    start = this->k;
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
    this->declareVariable(i, Type::iterator);
    this->assign(this->getSymbol(i), a);

    string threshold = i + "-threshold";
    this->declareVariable(threshold, Type::constant);
    this->assign(this->getSymbol(threshold), b);
    Cond* cond = this->leq(this->getSymbol(i), this->getSymbol(threshold));

    this->code[cond->jumpTo] += "jumpto";
    this->code[cond->start] += "start";
    delete cond;
}

void Code::decForLoopCondition(string i, Symbol* a, Symbol* b) {
    this->declareVariable(i, Type::iterator);
    this->assign(this->getSymbol(i), a);
    
    string threshold = i + "-threshold";
    this->declareVariable(threshold, Type::constant);
    this->assign(this->getSymbol(threshold), b);
    Cond* cond = this->geq(this->getSymbol(i), this->getSymbol(threshold));

    this->code[cond->jumpTo] += "jumpto";
    this->code[cond->start] += "start";
    delete cond;
}

void Code::incForLoopEnd(string i) {
    long long jumpTo = 0;
    long long start = 0;

    this->getSymbolOffset(this->getSymbol(i));
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

    data->variables.erase(i);
    data->variables.erase(i + "-threshold");

    this->jump(-jumpTo);
    this->code[this->k - start - 1] += " " + to_string(start + 1) + "\n";
    this->reset('a');
}

void Code::decForLoopEnd(string i) {
    long long jumpTo = 0;
    long long start = 0;
    
    this->getSymbolOffset(this->getSymbol(i));
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

    data->variables.erase(i);
    data->variables.erase(i + "-threshold");

    this->jump(-jumpTo);
    this->code[this->k - start - 1] += " " + to_string(start + 1) + "\n";
    this->reset('a');
}

void Code::genValue(long long value) {
    bool negative = false;
    if (value < 0) negative = true;
    
    if (abs(value) < 8) {
        if (negative) for (long long i = 0; i > value; i--)
                this->dec('a');
        else for (long long i = 0; i < value; i++)
                this->inc('a');
    } else {
        long long binary[64];
        long long i = 0;
        while (value != 0) {
            binary[i] = abs(value % 2);
            value /= 2;
            i++;
        }
        i--;

        this->inc('b');
        
        for (; i > 0; i--) {
            if (binary[i] == 1) {
                if (negative) this->dec('a');
                else this->inc('a');
            }
            this->shift('b');
        }

        if (binary[i] == 1) {
            if (negative) this->dec('a');
            else this->inc('a');
        }
        this->reset('b');
    }
}

void Code::getSymbolOffset(Symbol* symbol) {
    this->genValue(symbol->getOffset());

    if (symbol->type == Type::pointer)
        this->load('a');
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

Symbol* Code::getPointer(string name) {
    if (!this->isDeclared(name))
        this->declareVariable(name, Type::pointer);
    return this->getSymbol(name);
}

Symbol* Code::getSymbol(string id) {
    return this->data->getSymbol(id);
}

Symbol* Code::getSymbol(string arr, string index) {
    Array* array = reinterpret_cast<Array*>(this->getSymbol(arr));
    Symbol* indexSymbol = this->getSymbol(index);

    this->loadSymbols(this->getNumber(array->start), indexSymbol);
    
    this->sub('c');
    this->swap('c');
    this->reset('a');

    this->genValue(array->getOffset());
    this->reset('b');
    this->add('c');
    
    this->swap('c');
    this->reset('a');
    this->reset('b');

    Symbol* pointer = this->getPointer(arr + "[" + index + "]");
    this->genValue(pointer->getOffset());
    this->swap('c');
    this->store('c');

    this->reset('a');
    this->reset('b');
    this->reset('c');

    return pointer;
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

    this->genValue(var->getOffset());
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

void Code::loadSymbols(Symbol* a, Symbol* b) {
    if (!dynamic_cast<Variable*>(a)->isInitialized() || !dynamic_cast<Variable*>(b)->isInitialized())
        yyerror("use of uninitialized variable");
    this->getSymbolOffset(a);
    this->load('a');
    this->swap('c');

    this->reset('b');

    this->getSymbolOffset(b);
    this->load('a');
    this->reset('b');
}

string Code::getCode() {
    string code = "";
    for (string command : this->code) code += command;
    return code;
}
