#include <iostream>
#include <stdint.h>
#include <assert.h>
#include <string>

/// Function computing elements in row and collumn
inline uint16_t
row_col_sum(uint16_t** matrix, size_t msize, uint16_t num) {
    assert(matrix != NULL && msize <= 40);

    uint16_t sum = 0;

    /// Go through collumn
    for(uint16_t y = 0; y < msize; y++) {
        sum += matrix[y][num];
    }

    /// Go through row
    for(uint16_t x = 0; x < msize; x++) {
        sum += matrix[num][x];
    }

    return sum;
}

uint16_t**
init_matrix(size_t msize) {
    assert(msize <= 40 && "0 <= size <= 40");

    /// Creating array of pointers (collumns)
    uint16_t** matrix = new uint16_t*[msize];

    /// Initializing values in matrix
    for(uint16_t i = 0; i < msize; i++) {
        matrix[i] = new uint16_t[msize];

        for(uint16_t j = 0; j < msize; j++) {
            if(i == j) {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = (i+1) + (j+1);
            }
        }
    }

    /// Initializing main diagonal
    for(uint16_t i = 0; i < msize; i++) {
        matrix[i][i] = row_col_sum(matrix, msize, i);
    }

    return matrix;
}

void
rotate_90(uint16_t** matrix, size_t msize) {
    assert(matrix != NULL && msize <= 40);

    uint16_t temp;
    for(uint16_t i = 0; i < msize/2; i++) {
        for(uint16_t j = 0; j < msize/2; j++) {
            temp                         = matrix[msize-1-j][i];
            matrix[msize-1-j][i]         = matrix[msize-1-i][msize-1-j];
            matrix[msize-1-i][msize-1-j] = matrix[j]        [msize-1-i];
            matrix[j]        [msize-1-i] = matrix[i]        [j];
            matrix[i]        [j]         = temp;
        }
    }
}

void
print_matrix(uint16_t** matrix, size_t msize) {
    assert(matrix != NULL && msize <= 40);

    std::string out;
    for(uint16_t i = 0; i < msize; i++) {
        for(uint16_t j = 0; j < msize; j++) {
            out = std::to_string(matrix[i][j]);
            out.resize(4, ' ');
            std::cout << out;
        }
        std::cout<< "\n\n";
    }
}

int main() {
    const size_t msize = 5;

    uint16_t** matrix = init_matrix(msize);

    printf("Initialized matrix:\n");
    print_matrix(matrix, msize);

    printf("Rotated matrix\n:");
    rotate_90(matrix, msize);
    print_matrix(matrix, msize);

    return 0;
}
