#include <string>
using namespace std;

class Code {
public:
    long long k;
    string code;

    Code();
    void atomic(string);
    void atomic(string, long long);
    void get();
    void put();
    void load(long long);
    void store(long long);
    void add(long long);
    void sub(long long);
    void shift(long long);
    void swap(long long);
    void reset(long long);
    void inc(long long);
    void dec(long long);
    void jump(long long);
    void jpos(long long);
    void jzero(long long);
    void jneg(long long);
    void halt();
    string getCode();
};
