#include <iostream>
#include "matrix4.hpp"

using namespace std;
using namespace PT_l1_t5;


int main(int argc, char** argv) {
    Matrix4 m;

    int size = atoi(argv[1]);

    m.Init(size);
    m.Print();

    cout << "Det: " << m.Determinant() << endl;
}
