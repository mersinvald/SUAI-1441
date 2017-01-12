#include "matrix2.hpp"
#include <stdexcept>

namespace PT_l1_t2 {

using std::to_string;

Matrix2::Matrix2()                         : Matrix() {}
Matrix2::Matrix2(const Matrix2* copy_from) : Matrix2(*copy_from) {}
Matrix2::Matrix2(const Matrix2& copy_from) : Matrix(copy_from) {
    Assign(copy_from);
}

void
Matrix2::Assign(const Matrix2* from) {
    return Assign(*from);
}

void
Matrix2::Assign(const Matrix2& from) {
    _size = from.size();
    InitMemory();

    size_t mem_size = _size*_size;
    for(size_t i = 0; i < mem_size; i++) {
        _memory[i] = from._memory[i];
    }
}

void
Matrix2::Resize(size_t new_size) {
    _size = new_size;
    InitMemory();
}

void
Matrix2::Rotate(int n) {
    bool neg = (n < 0) ? true : false;

    n = abs(n) % 4;
    if(n == 0 || n == 4) {
        return;
    }

    n = (neg) ? 4 - n
              : n;

    for(int i = 0; i < n; i++) {
        Matrix::Rotate();
    }
}

Matrix2::MatrixRow::MatrixRow(int* row_ptr, size_t size)
    : _ptr(row_ptr), _size(size) {}

int&
Matrix2::MatrixRow::operator[](size_t ix) {
    if(ix >= _size) {
        throw std::out_of_range (
            "ERROR: Row index " + to_string(ix) + " is out-of-range (0.." + to_string(_size-1) + ")"
        );
    }
    return _ptr[ix];
}

Matrix2::MatrixRow
Matrix2::operator[](size_t iy) {
    if(iy >= _size) {
        throw std::out_of_range (
            "ERROR: Col index " + to_string(iy) + " is out-of-range (0.." + to_string(_size-1) + ")"
        );
    }
    return MatrixRow(_matrix[iy], _size);
}

}
