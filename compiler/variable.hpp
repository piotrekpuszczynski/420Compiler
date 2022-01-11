class Variable {
public:
    long long offset;

    Variable(long long);
    long long getOffset();
};

class Array : public Variable {
public:
    long long start;
    long long end;

    Array(long long, long long, long long);
    using Variable::getOffset;
    long long getOffset(long long);
};
