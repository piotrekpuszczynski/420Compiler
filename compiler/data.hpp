#include <string>
#include <unordered_map>
#include "variable.hpp"
using namespace std;

class Data {
public:
    long long offset;
    unordered_map<string, Variable*> variables;

    Data();
    void declareVariable(string);
    void declareArray(string, long long, long long);
    bool isDeclared(string);
};
