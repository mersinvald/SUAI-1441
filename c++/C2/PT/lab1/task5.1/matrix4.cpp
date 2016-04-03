#include "matrix4.hpp"
#include <stdexcept>
#include <cmath>

namespace PT_l1_t5 {

int
Matrix4::Determinant() {
    if(!_memory || !_matrix) {
        throw std::logic_error("Matrix must be initialized first");
    }

    if(_size < 1) {
        throw std::logic_error("Matrix size mast be >= 1 to calculate discriminant");
    }



    return Determinant(_matrix, _size);
}

int
Matrix4::Determinant(int** matrix, size_t size) {
    if(size == 1) {
        return matrix[0][0];
    }

    if(size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    }

    int d = 0, k = 1;

#ifndef __GNUG__
    int** p = new int*[size-1];
#else
    int* p[size-1];
#endif


    uint j;
    for(uint i = 0; i < size; i++) {
        for(j = 0; j < size-1; j++) {
            if(j < i) {
                p[j] = matrix[j];
            } else {
                p[j] = matrix[j+1];
            }
        }

        k = ((i+j) % 2) ? -1 : 1;
        d += k * Determinant(p, size-1) * matrix[i][size-1];

    }

#ifndef __GNUG__
    delete[] p;
#endif

    return d;
}

}
