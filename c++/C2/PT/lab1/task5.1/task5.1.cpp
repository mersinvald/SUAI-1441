#include <iostream>
#include "matrix4.hpp"

using namespace std;
using namespace PT_l1_t5;


int main() {
    Matrix4 m;

    m.Init(6);
    m.Print();

    cout << "Det: " << m.Determinant() << endl;
}
