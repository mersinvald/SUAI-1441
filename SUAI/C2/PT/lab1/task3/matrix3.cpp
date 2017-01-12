#include "matrix3.hpp"
#include <stdexcept>
namespace PT_l1_t3 {



Matrix3&
Matrix3::operator= (Matrix3& b) {
    Assign(b);
    return *this;
}

Matrix3 operator+ (const Matrix3& a, const Matrix3& b) {
    if(a.size() != b.size()) {
        throw std::logic_error("a.size() != b.size()");
    }

    size_t size  = a.size();
    size_t msize = size*size;

    Matrix3 c;
    c.Resize(size);

    for(uint i = 0; i < msize; i++) {
        c._memory[i] = a._memory[i] + b._memory[i];
    }

    return c;
}

Matrix3 operator- (const Matrix3& a, const Matrix3& b) {
    if(a.size() != b.size()) {
        throw std::logic_error("a.size() != b.size()");
    }

    size_t size  = a.size();
    size_t msize = size*size;

    Matrix3 c;
    c.Resize(size);

    for(uint i = 0; i < msize; i++) {
        c._memory[i] = a._memory[i] - b._memory[i];
    }

    return c;
}

Matrix3 operator* (const Matrix3& a, const Matrix3& b) {
    if(a.size() != b.size()) {
        throw std::logic_error("a.size() != b.size()");
    }

    size_t size  = a.size();

    Matrix3 c;
    c.Resize(size);

    for(uint i = 0; i < size; i++) {
        for(uint j = 0; j < size; j++) {
            int c_ij = 0;
            for(uint k = 0; k < size; k++) {
                c_ij += a._matrix[i][k] + a._matrix[k][j];
            }
            c[i][j] = c_ij;
        }
    }

    return c;
}

Matrix3 operator* (const Matrix3& a, int b) {
    size_t size  = a.size();
    size_t msize = size*size;

    Matrix3 c;
    c.Resize(size);

    for(uint i = 0; i < msize; i++) {
        c._memory[i] = a._memory[i] * b;
    }

    return c;
}

}
