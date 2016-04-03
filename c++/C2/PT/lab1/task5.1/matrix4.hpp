/****************************************************************************

ModuleName:
    Matrix

Abstract:
    Matrix class, designed for Programming Technology class, triple extended version.

Author:
    Lubinets Mike 1441 (Лубинец Михаил 1441)

Date:
    2016-03-21

Changes
    Determinant calculation

****************************************************************************/


#ifndef MATRIX4_H
#define MATRIX4_H
#include "matrix3.hpp"

namespace PT_l1_t5 {

class Matrix4 : public PT_l1_t3::Matrix3 {
public:
    using Matrix3::Matrix3;

    int Determinant();

private:
    static int Determinant(int** matrix, size_t size);
};

}

#endif // MATRIX4_H
