/****************************************************************************

ModuleName:
    Matrix

Abstract:
    Matrix class, designed for Programming Technology class, double extended version.

Author:
    Lubinets Mike 1441 (Лубинец Михаил 1441)

Date:
    2016-03-20

Changes
    Arithmetic operators

****************************************************************************/

#ifndef MATRIX3_H
#define MATRIX3_H
#include "matrix2.hpp"

namespace PT_l1_t3 {

class Matrix3 : public PT_l1_t2::Matrix2 {
public:
    using Matrix2::Matrix2;

    Matrix3& operator= (Matrix3& b);
    Matrix3& operator= (int b);

    /* Operations with matrices */
    friend Matrix3 operator+ (const Matrix3& a, const Matrix3& b);
    friend Matrix3 operator- (const Matrix3& a, const Matrix3& b);
    friend Matrix3 operator* (const Matrix3& a, const Matrix3& b);

    /* Operations with natural numbers */
    friend Matrix3 operator* (const Matrix3& a, int b);

};

}

#endif // MATRIX3_H
