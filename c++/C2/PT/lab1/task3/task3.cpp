#include <iostream>
#include "matrix3.hpp"

using namespace std;
using namespace PT_l1_t3;

int main() {
    Matrix3 m1;
    Matrix3 m2;

    m1.Init(3);
    m2.Init(3);

    cout << "M1:\n";
    m1.Print();

    cout << "M2:\n";
    m2.Print();

    cout << "M1+M2=\n";
    (m1+m2).Print();

    cout << "M1-M2=\n";
    (m1-m2).Print();

    cout << "M1*M2=\n";
    (m1*m2).Print();

    cout << "M1*10=\n";
    (m1*10).Print();

    cout << "M3 = (M1 + M2)\n";
    Matrix3 m3 = (m1 + m2);
    m3.Print();

    return 0;
}
