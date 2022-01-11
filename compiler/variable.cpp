#include "variable.hpp"

Variable::Variable(long long offset) {
    this->offset = offset;
}

long long Variable::getOffset() {
    return this->offset;
}

Array::Array(long long offset, long long start, long long end) : Variable(offset) {
    this->start = start;
    this->end = end;
}

long long Array::getOffset(long long index) {
    return this->getOffset() - this->start + index;
}
