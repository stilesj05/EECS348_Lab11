#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Matrix {
private:
    size_t n;                   // Matrix is n x n
    unique_ptr<int[]> data;     // Row-major: data[r*n + c]

public:
    // Constructors / Rule of Five
    Matrix();                           // 0x0
    explicit Matrix(size_t n_);         // n x n zero matrix
    Matrix(const Matrix& other);        // copy
    Matrix& operator=(const Matrix&);   // copy assign
    Matrix(Matrix&&) noexcept = default;
    Matrix& operator=(Matrix&&) noexcept = default;
    ~Matrix() = default;

    // Basic info
    size_t size() const { return n; }

    // Element access
    int& at(size_t r, size_t c);
    const int& at(size_t r, size_t c) const;

    // I/O
    void print(ostream& os = cout) const;
    friend ostream& operator<<(ostream& os, const Matrix& M);

    // File input (Practice #1)
    static Matrix fromFile(const string& filename);

    // Operator overloading (Practice #2 and #3)
    Matrix operator+(const Matrix& rhs) const;  // addition
    Matrix operator*(const Matrix& rhs) const;  // multiplication

    // Diagonal sums (Practice #4)
    long long mainDiagonalSum() const;
    long long secondaryDiagonalSum() const;

    // Row/Column swaps (Practice #5 and #6)
    // NOTE: Matrix is passed BY VALUE so original is not modified.
    friend Matrix swapRows(Matrix m, size_t i, size_t j);
    friend Matrix swapCols(Matrix m, size_t i, size_t j);

    // Update cell (Practice #7) — default r=0, c=0, value=100
    friend Matrix updateCell(Matrix m, size_t r, size_t c, int value);
};

// Convenience declarations with default arguments for callers
Matrix swapRows(Matrix m, size_t i = 0, size_t j = 1);
Matrix swapCols(Matrix m, size_t i = 0, size_t j = 1);
Matrix updateCell(Matrix m, size_t r = 0, size_t c = 0, int value = 100);


#endif // MATRIX_H
