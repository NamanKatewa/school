#include "SparseMatrix.h"
#include <iostream>

SparseMatrix::SparseMatrix(int rows, int cols)
    : numNonZero(0), numRows(rows), numCols(cols) {
    rowIndex = new int[MAX_NONZERO];
    colIndex = new int[MAX_NONZERO];
    value = new int[MAX_NONZERO];
}

SparseMatrix::~SparseMatrix() {
    delete[] rowIndex;
    delete[] colIndex;
    delete[] value;
}

void SparseMatrix::buildFromDense(const int* dense, int rows, int cols) {
    numNonZero = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (dense[i * cols + j] != 0) {
                if (numNonZero < MAX_NONZERO) {
                    rowIndex[numNonZero] = i;
                    colIndex[numNonZero] = j;
                    value[numNonZero] = dense[i * cols + j];
                    numNonZero++;
                } else {
                    std::cout << "Warning: Sparse storage capacity reached. Not all non-zero entries stored." << std::endl;
                    return;
                }
            }
        }
    }
    std::cout << "Sparse matrix built from dense representation." << std::endl;
}

void SparseMatrix::print() const {
    std::cout << "Sparse Matrix (row, col, value) triplets:" << std::endl;
    if (numNonZero == 0) {
        std::cout << "  No sparse entries." << std::endl;
        return;
    }
    for (int i = 0; i < numNonZero; ++i) {
        std::cout << "  (" << rowIndex[i] << ", " << colIndex[i] << ", " << value[i] << ")" << std::endl;
    }
}