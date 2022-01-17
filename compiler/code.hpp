#include <vector>
#include "data.hpp"
using namespace std;

class Code {
public:
    long long k;
    vector<string> code;
    Data* data;

    Code(Data*);

    void atomic(string);
    void atomic(string, long long);
    void atomic(string, char);

    void get();
    void put();
    void load(char);
    void store(char);
    void add(char);
    void sub(char);
    void shift(char);
    void swap(char);
    void reset(char);
    void inc(char);
    void dec(char);
    void jump();
    void jump(long long);
    void jpos(long long);
    void jzero(long long);
    void jneg(long long);
    void halt();

    void read(Symbol*);
    void write(Symbol*);
    void assign(Symbol*, Symbol*);
    Symbol* plus(Symbol*, Symbol*);
    Symbol* minus(Symbol*, Symbol*);
    Symbol* times(Symbol*, Symbol*);
    Symbol* div(Symbol*, Symbol*);
    Symbol* mod(Symbol*, Symbol*);
    Cond* eq(Symbol*, Symbol*);
    Cond* neq(Symbol*, Symbol*);
    Cond* le(Symbol*, Symbol*);
    Cond* ge(Symbol*, Symbol*);
    Cond* leq(Symbol*, Symbol*);
    Cond* geq(Symbol*, Symbol*);

    void ifBlock(Cond*);

    Symbol* getSymbol(string);
    Symbol* getSymbol(string, string);
    Symbol* getSymbol(string, long long);
    Symbol* getNumber(long long);
    void getMemory(long long);
    void getValue(long long);
    void incLoop(long long);
    void decLoop(long long);
    string getCode();
};
