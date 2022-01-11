#include <string>
#include "code.hpp"
#include "data.hpp"
using namespace std;

Code::Code() {
    this->k = 0;
    this->code = "";
}

void Code::atomic(string instruction) {
    this->code += instruction + "\n";
    this->k++;
}

void Code::atomic(string instruction, long long value) {
    this->code += instruction + " " + to_string(value) + "\n";
    this->k++;
}

void Code::get() {
    this->atomic("GET");
}

void Code::put() {
    this->atomic("PUT");
}

void Code::load(long long x) {
    this->atomic("LOAD", x);
}

void Code::store(long long x) {
    this->atomic("STORE", x);
}

void Code::add(long long x) {
    this->atomic("ADD", x);
}

void Code::sub(long long x) {
    this->atomic("SUB", x);
}

void Code::shift(long long x) {
    this->atomic("SHIFT", x);
}

void Code::swap(long long x) {
    this->atomic("SWAP", x);
}

void Code::reset(long long x) {
    this->atomic("RESET", x);
}

void Code::inc(long long x) {
    this->atomic("INC", x);
}

void Code::dec(long long x) {
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

string Code::getCode() {
    return this->code;
}
