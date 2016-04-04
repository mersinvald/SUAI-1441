#include <iostream>
#include "rational.hpp"

using namespace std;
using namespace msvd::math;

int main(int argc, char *argv[]) {
    Rational pi(22, 7);
    Rational e(8, 3);
    Rational y;

    double dfract;
    std::cout << "Enter your double: ";
    std::cin  >> dfract;

    y = dfract;

    std::cout << "PI: " << pi << std::endl
              << "E:  " << e  << std::endl
              << "Y:  " << y  << std::endl << std::endl;

    std::cout << "PI + E = "       << pi + e       << std::endl;
    std::cout << "PI - E = "       << pi - e       << std::endl;
    std::cout << "PI * E = "       << pi * e       << std::endl;
    std::cout << "PI / E = "       << pi / e       << std::endl;

    Rational d = pi * e;
    std::cout << "\nD = PI * E = " << d << std::endl;

    std::cout << "D + Y = "       << d + y       << std::endl;
    std::cout << "D - Y = "       << d - y       << std::endl;
    std::cout << "D * Y = "       << d * y       << std::endl;
    std::cout << "D / Y = "       << d / y       << std::endl;

    return 0;
}
