#include <iostream>
#include "matrix.hpp"
#include "matrix2.hpp"

using namespace std;
using namespace PT_l1_t2;

void demo_matrix() {
    Matrix m1;

    /// Trying to print and rotate non-initialized matrix
    try { m1.Rotate(); } catch(std::exception& e) {
        std::cerr << e.what();
    }

    try { m1.Print(); } catch(std::exception& e) {
        std::cerr << e.what();
    }

    /// Trying to initialize woth wrong values
    try { m1.Init(-1); } catch(std::exception& e) {
        std::cerr << e.what();
    }

    try { m1.Init(41); } catch(std::exception& e) {
        std::cerr << e.what();
    }

    /// Finished trolling matrix class, testing main functionality
    m1.Init(10);

    cout << "Matrix with size " << m1.size() << endl;
    m1.Print();

    cout << endl << endl
         << "Rotated by 90 deg matrix with size " << m1.size() << endl;
    m1.Rotate();
    m1.Print();

    /// Reinitializing the matrix with size 15
    m1.Init(15);
    cout << "Matrix with size " << m1.size() << endl;
    m1.Print();

    cout << endl << endl
         << "Rotated by 90 deg matrix with size " << m1.size() << endl;
    m1.Rotate();
    m1.Print();
}

void demo_matrix2() {
    Matrix2 m1;
    Matrix2 m2;
    Matrix2 m3;

    m1.Init(2);
    m2.Init(4);
    m3.Init(10);

    cout << "Original matrix 2:\n";
    m2.Print();

    cout << "\nMatrix 2 rotated 2 times:\n";
    m2.Rotate(2);
    m2.Print();

    cout << "\nOriginal matrix 3:\n";
    m3.Print();

    cout << "\nMatrix 3 rotated 400000001 times:\n";
    m3.Rotate(400000001);
    m3.Print();

    cout << "\nOriginal matrix 1:\n";
    m1.Print();

    cout << "\nSet 0:1 and 1:1 in matrix 1 to 0:\n";
    m1[0][1] = 0;
    m1[1][1] = 0;
    m1.Print();

    cout << "\nTrying to set 10:1 of matrix 1:\n";
    try {
        m1[10][1] = 0;
    } catch(std::out_of_range& e) {
        std::cerr << e.what();
    }

    cout << "\nTrying to set 1:10 of matrix 1:\n";
    try {
        m1[1][10] = 0;
    } catch(std::out_of_range& e) {
        std::cerr <<  e.what();
    }

    cout << "\nCopy matrix 1 to matrix 3:\n";
    m3.Assign(m1);
    m3.Print();

}

int main() {
    //demo_matrix();
    //demo_matrix2();

    size_t matrix_size;

    cout << "Enter matrix size: ";
    cin  >> matrix_size;

    Matrix m1;
    try {
        m1.Init(matrix_size);
    } catch (std::exception& e) {
        std::cout << e.what();
        return 1;
    }

    cout << "Matrix with size " << m1.size() << endl;
    m1.Print();

    cout << endl << endl
         << "Rotated by 90 deg matrix with size " << m1.size() << endl;
    m1.Rotate();
    m1.Print();
}
