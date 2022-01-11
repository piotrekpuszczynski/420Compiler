#include "data.hpp"
using namespace std;

class Code {
public:
    long long k;
    string code;
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
    void jump(long long);
    void jpos(long long);
    void jzero(long long);
    void jneg(long long);
    void halt();

    Variable* getVariable(string);
    Variable* getVariable(string, string);
    Variable* getVariable(string, long long);
    Variable* getNumber(long long);
    void assign(long long);
    void read(Variable*);
    void write(Variable*);
    string getCode();
};
