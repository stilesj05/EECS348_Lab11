#include "Matrix.h"
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <sstream>
using namespace std;

Matrix::Matrix() : n(0), data(nullptr) {}

Matrix::Matrix(size_t n_) : n(n_), data(n_ ? make_unique<int[]>(n_ * n_) : nullptr) {
    for (size_t i = 0; i < n * n; ++i) data[i] = 0;
}

Matrix::Matrix(const Matrix& other)
    : n(other.n), data(other.n ? make_unique<int[]>(other.n * other.n) : nullptr) {
    for (size_t i = 0; i < n * n; ++i) data[i] = other.data[i];
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;
    n = other.n;
    data = (n ? make_unique<int[]>(n * n) : nullptr);
    for (size_t i = 0; i < n * n; ++i) data[i] = other.data[i];
    return *this;
}

int& Matrix::at(size_t r, size_t c) {
    if (r >= n || c >= n) throw out_of_range("Matrix::at index out of range");
    return data[r * n + c];
}

const int& Matrix::at(size_t r, size_t c) const {
    if (r >= n || c >= n) throw out_of_range("Matrix::at index out of range");
    return data[r * n + c];
}

void Matrix::print(ostream& os) const {
    // Find max width for neat columns
    int width = 1;
    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            std::ostringstream tmp;
            tmp << at(r, c);
            width = max(width, (int)tmp.str().size());
        }
    }
    width = max(width, 2); // at least 2 for readability

    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            os << setw(width + 1) << at(r, c);
        }
        os << '\n';
    }
}

ostream& operator<<(ostream& os, const Matrix& M) {
    M.print(os);
    return os;
}

// NOTE: This reads a SINGLE square matrix from a file that contains
// N followed by N*N integers. The assignment's input has TWO matrices
// back-to-back; we will handle reading both in main by opening the file
// once and filling two Matrix objects sequentially.
Matrix Matrix::fromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) throw runtime_error("Cannot open file: " + filename);

    size_t N;
    if (!(fin >> N)) throw runtime_error("Failed to read N");

    Matrix M(N);
    for (size_t r = 0; r < N; ++r) {
        for (size_t c = 0; c < N; ++c) {
            int v;
            if (!(fin >> v)) throw runtime_error("Not enough elements for matrix");
            M.at(r, c) = v;
        }
    }
    return M;
}

// Addition
Matrix Matrix::operator+(const Matrix& rhs) const {
    if (n != rhs.n) throw runtime_error("Matrix sizes differ for addition");
    Matrix R(n);
    for (size_t i = 0; i < n * n; ++i) {
        R.data[i] = this->data[i] + rhs.data[i];
    }
    return R;
}

// Multiplication
Matrix Matrix::operator*(const Matrix& rhs) const {
    if (n != rhs.n) throw runtime_error("Matrix sizes differ for multiplication");
    Matrix R(n);
    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            long long sum = 0;
            for (size_t k = 0; k < n; ++k) {
                sum += static_cast<long long>(at(r, k)) * rhs.at(k, c);
            }
            R.at(r, c) = static_cast<int>(sum);
        }
    }
    return R;
}

// Diagonals
long long Matrix::mainDiagonalSum() const {
    long long s = 0;
    for (size_t i = 0; i < n; ++i) s += at(i, i);
    return s;
}

long long Matrix::secondaryDiagonalSum() const {
    long long s = 0;
    for (size_t i = 0; i < n; ++i) s += at(i, n - 1 - i);
    return s;
}

// Swaps (by value)
Matrix swapRows(Matrix m, size_t i, size_t j) {
    if (m.n == 0) return m;
    if (i >= m.n || j >= m.n) return m; // silently ignore invalid
    if (i == j) return m;
    for (size_t c = 0; c < m.n; ++c) {
        std::swap(m.at(i, c), m.at(j, c));
    }
    return m;
}

Matrix swapCols(Matrix m, size_t i, size_t j) {
    if (m.n == 0) return m;
    if (i >= m.n || j >= m.n) return m; // silently ignore invalid
    if (i == j) return m;
    for (size_t r = 0; r < m.n; ++r) {
        std::swap(m.at(r, i), m.at(r, j));
    }
    return m;
}

Matrix updateCell(Matrix m, size_t r, size_t c, int value) {
    if (m.n == 0) return m;
    if (r < m.n && c < m.n) m.at(r, c) = value;
    return m;
}
