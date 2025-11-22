#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>

class SparseMatrix {
private:
    static const int MAX_NONZERO = 100;
    int* rowIndex;
    int* colIndex;
    int* value;
    int numNonZero;
    int numRows;
    int numCols;

public:
    SparseMatrix(int rows, int cols);

    ~SparseMatrix();

    void buildFromDense(const int* dense, int rows, int cols);

    void print() const;

    int getNumNonZero() const { return numNonZero; }

    const int* getRowIndex() const { return rowIndex; }
    const int* getColIndex() const { return colIndex; }
    const int* getValue() const { return value; }
};

#endif