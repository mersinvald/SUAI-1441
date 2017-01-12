/****************************************************************************

ModuleName:
    Matrix

Abstract:
    Matrix class, designed for Programming Technology class, extended version.

Author:
    Lubinets Mike 1441 (Лубинец Михаил 1441)

Date:
    2016-03-20

****************************************************************************/

#ifndef PT_L1_T2_MATRIX_H
#define PT_L1_T2_MATRIX_H

#include <string>
#include <stdint.h>
#include <stddef.h>

namespace PT_l1_t2 {

using std::string;

class Matrix {
public:
    Matrix();
    virtual ~Matrix();

    /* @brief Create and initialize matrix with passed size
     * @param size -- desired matrix size */
    void Init(size_t size);

    /* @brief Rotate matrix by 90 degrees */
    void Rotate();

    /* @brief Output matrix to stdout */
    void Print();

    /* Getters */
    size_t size() const;

protected:
    void InitMemory();
    void FreeMemory();

    int ColRowSum(size_t n);

    size_t _size;
    int** _matrix;        ///< Array of pointers to _memory (columns)
    int*  _memory;        ///< Continuous chunk of memory (to prevent memory fragmentation)
};

}

#endif // PT_L1_T2_MATRIX_H
