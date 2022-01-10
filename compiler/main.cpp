#include <iostream>
#include <fstream>
using namespace std;

extern void runParser(FILE* data);

int main(int argc, char** argv) {
    cout << "\033[91m";

    if (argc < 2 || argc > 3) {
        cout << "incorrect number of arguments, valid run arguments:" << endl;
        cout << "./compiler <input file> <output file>" << endl;
        cout << "./compiler <input file>" << endl;
        return -1;
    }

    FILE * data = fopen(argv[1], "r");
    if (data == nullptr) {
        cout << "file " << argv[1] << " does not exist" << endl;
        return -2;
    }

  	runParser(data);
    
    string out = "out";
    if (argv[2] != nullptr) {
        out = argv[2];
    }

    ofstream binary(out);
    binary.close();

    cout << "\033[0m";

    return 0;
}
