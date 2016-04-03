#include "matrix.hpp"
#include <iostream>
#include <stdexcept>

namespace PT_l1_t2 {

Matrix::Matrix() :
    _size(0),
    _matrix(nullptr),
    _memory(nullptr) {}

Matrix::~Matrix() {
    FreeMemory();
}

void
Matrix::Init(size_t size) {
    if(size > 40) {
        throw std::logic_error("ERROR: Size range must be: 0 <= size <= 40");
    }

    _size = size;
    InitMemory();

    /// Do values initialization
    for(uint i = 0; i < size; i++) {
        for(uint j = 0; j < size; j++) {
            if(i == j) {
                _matrix[i][j] = 0;
            } else {
                _matrix[i][j] = (i+1) + (j+1);
            }
        }
    }

    /// Initializing main diagonal
    for(uint i = 0; i < size; i++) {
        _matrix[i][i] = ColRowSum(i);
    }
}

void
Matrix::Rotate() {
    if(!_matrix || !_memory) {
        throw std::logic_error("ERROR: Matrix was not initialized, can't rotate");
    }

    for(uint y = 0; y < _size/2; y++) {
        size_t s = _size;
        for(uint x = 0; x < s/2; x++) {
            int temp             = _matrix[s-1-x][y];
            _matrix[s-1-x][y]     = _matrix[s-1-y][s-1-x];
            _matrix[s-1-y][s-1-x] = _matrix[x]    [s-1-y];
            _matrix[x]    [s-1-y] = _matrix[y]    [x];
            _matrix[y]    [x]     = temp;
        }
    }
}

void
Matrix::Print() {
    if(!_matrix || !_memory) {
        throw std::logic_error("ERROR: Matrix was not initialized, can't print");
    }

    std::string out;

    for(uint16_t i = 0; i < _size; i++) {
        for(uint16_t j = 0; j < _size; j++) {
            /// Pretty print
            out = std::to_string(_matrix[i][j]);
            out.resize(4, ' ');

            std::cout << out;
        }
        std::cout << "\n\n";
    }
}

size_t
Matrix::size() const {
    return _size;
}

void
Matrix::InitMemory() {
    /// Checking if matrix was initialized previously to prevent memory leak
    if(_matrix || _memory) {
        FreeMemory();
    }

    /// Allocating memory for the matrix and collumns
    _memory = new int [_size*_size];
    _matrix = new int*[_size];

    /// Setting up collumn pointers
    for(size_t i = 0; i < _size; i++) {
        _matrix[i] = _memory + i*_size;
    }
}

void
Matrix::FreeMemory() {
    if(_matrix != nullptr) {
        std::clog << "TRACE: Freeing collumn pointers memory" << std::endl;
        delete[] _matrix;
    }

    if(_memory != nullptr) {
        std::clog << "TRACE: Freeing matrix memory" << std::endl;
        delete[] _memory;
    }
}

int
Matrix::ColRowSum(size_t n) {
    uint16_t sum = 0;

    /// Go through collumn
    for(uint y = 0; y < _size; y++) {
        sum += _matrix[y][n];
    }

    /// Go through row
    for(uint x = 0; x < _size; x++) {
        sum += _matrix[n][x];
    }

    return sum;
}


}
