/****************************************************************************

ModuleName:
    Matrix2

Abstract:
    Matrix class, designed for Programming Technology class, extended version.

Author:
    Lubinets Mike 1441 (Лубинец Михаил 1441)

Date:
    2016-03-20

Changes:
    Addded safe operator[][] semantics
    Resize method
    Rotate by n*90
    Copy constructor and Assign operator

****************************************************************************/

#ifndef PT_L1_T2_MATRIX2_H
#define PT_L1_T2_MATRIX2_H
#include "matrix.hpp"

namespace PT_l1_t2 {

class Matrix2 : public Matrix {
public:
    Matrix2();
    Matrix2(const Matrix2& copy_from);
    Matrix2(const Matrix2* copy_from);

    /* @brief Copy matrix */
    void Assign(const Matrix2& assign_from);
    void Assign(const Matrix2* assign_from);

    /* @brief Resize matrix
     * @param new_size -- new matrix size */
    void Resize(size_t new_size);

    /* @brief Rotate matrix by n*90 grad
     * n can be positive or negative, but it only makes sence to pass 1 <= n < 3,
     * as n > 3 will be translated to n % 4,
     * -3 => 1, -2 => 2, -1 => 3 */
    void Rotate(int n);

    /* Proxy class for safe implementation of operator[][] semantics */
    struct MatrixRow {
        explicit MatrixRow(int* row_ptr, size_t size);
        int& operator[](size_t ix);
    private:
        int*  _ptr;
        size_t _size;
    };

    /* Safe access to matrix elements */
    MatrixRow operator[](size_t iy);
};

}

#endif // PT_L1_T2_MATRIX2_HPP
