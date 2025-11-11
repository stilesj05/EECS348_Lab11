#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "Matrix.h"
using namespace std;

static void readSquareMatrixFromStream(istream& in, Matrix& M) {
    size_t n = M.size();
    for (size_t r = 0; r < n; ++r) {
        for (size_t c = 0; c < n; ++c) {
            int v;
            if (!(in >> v)) {
                throw runtime_error("Not enough numbers to fill the matrix");
            }
            M.at(r, c) = v;
        }
    }
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);

    try {
        // Get filename
        string filename;
        if (argc >= 2) {
            filename = argv[1];
        } else {
            cout << "Enter input filename: ";
            if (!(cin >> filename)) return 0;
        }

        ifstream fin(filename);
        if (!fin) {
            cerr << "Error: cannot open file: " << filename << "\n";
            return 1;
        }

        // Read N
        size_t N;
        if (!(fin >> N)) {
            cerr << "Error: failed to read matrix size N\n";
            return 1;
        }

        // Create two N x N matrices and read both back-to-back
        Matrix A(N), B(N);
        readSquareMatrixFromStream(fin, A);
        readSquareMatrixFromStream(fin, B);

        // Display both matrices neatly (Practice #1)
        cout << "Matrix size: " << N << " x " << N << "\n\n";
        cout << "Matrix A:\n" << A << "\n";
        cout << "Matrix B:\n" << B << "\n";

        // --- Practice #2: Addition via operator+ ---
        cout << "A + B:\n" << (A + B) << "\n";

        // --- Practice #3: Multiplication via operator* ---
        cout << "A * B:\n" << (A * B) << "\n";

        // --- Practice #4: Diagonal sums ---
        cout << "Diagonal sums (A):\n";
        cout << "  main = " << A.mainDiagonalSum()
             << ", secondary = " << A.secondaryDiagonalSum() << "\n\n";

        cout << "Diagonal sums (B):\n";
        cout << "  main = " << B.mainDiagonalSum()
             << ", secondary = " << B.secondaryDiagonalSum() << "\n\n";

        // --- Practice #5: Swap rows (by value) ---
        cout << "Would you like to swap rows manually? (y/n): ";
        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            long i, j; // use signed type to detect negatives
            cout << "Enter two row indices to swap (0-based, e.g., 1 3): ";
            cin >> i >> j;

            if (!cin.good()) {
                cout << "Invalid input. No swap performed.\n\n";
            } else if (i < 0 || j < 0
                       || static_cast<size_t>(i) >= A.size()
                       || static_cast<size_t>(j) >= A.size()) {
                cout << "Invalid indices! Must be between 0 and "
                     << (A.size() - 1) << ". No swap performed.\n\n";
            } else {
                cout << "Result of swapRows(A, " << i << ", " << j << "):\n";
                cout << swapRows(A, static_cast<size_t>(i),
                                    static_cast<size_t>(j)) << "\n";
            }
        } else {
            cout << "Using default swapRows(A) — swaps rows 0 and 1:\n";
            cout << swapRows(A) << "\n";
        }

        // --- Practice #6: Swap columns (by value) ---
        cout << "Would you like to swap columns manually? (y/n): ";
        char cchoice;
        cin >> cchoice;

        if (cchoice == 'y' || cchoice == 'Y') {
            long i, j; // signed to catch negatives
            cout << "Enter two column  indices to swap (0-based, e.g., 1 3): ";
            cin >> i >> j;

            if (i < 0 || j < 0 || static_cast<size_t>(i) >= A.size() || static_cast<size_t>(j) >= A.size()) {
                cout << "Invalid indices! Must be between 0 and " << (A.size() - 1) << ". No swap performed.\n\n";
            } else {
                cout << "Result of swapCols(A, " << i << ", " << j << "):\n";
                cout << swapCols(A, static_cast<size_t>(i), static_cast<size_t>(j)) << "\n";
            }
        } else {
            cout << "Using default swapCols(A) — swaps columns 0 and 1:\n";
            cout << swapCols(A) << "\n";
        }

        // --- Practice #7: Update a cell (by value) ---
        cout << "Would you like to update a cell manually? (y/n): ";
        char uchoice;
        cin >> uchoice;

        if (uchoice == 'y' || uchoice == 'Y') {
            long r, c;    // signed to catch negatives
            int value;
            cout << "Enter row col value (e.g., 2 3 100): ";
            cin >> r >> c >> value;

            if (!cin.good()) {
                cout << "Invalid input. No update performed.\n\n";
            } else if (r < 0 || c < 0
                       || static_cast<size_t>(r) >= A.size()
                       || static_cast<size_t>(c) >= A.size()) {
                cout << "Invalid indices! Must be between 0 and "
                     << (A.size() - 1) << ". No update performed.\n\n";
            } else {
                cout << "Result of updateCell(A, " << r << ", " << c
                     << ", " << value << "):\n";
                cout << updateCell(A,
                                   static_cast<size_t>(r),
                                   static_cast<size_t>(c),
                                   value)
                     << "\n";
            }
        } else {
            cout << "Using default updateCell(A) — sets (0,0) to 100:\n";
            cout << updateCell(A) << "\n";
        }

        return 0;
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
}

