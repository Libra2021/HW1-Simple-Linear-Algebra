#include "hw1.h"

static inline void check_square(int n_rows, int n_cols) {
    if (n_rows != n_cols) {
        throw std::logic_error("Matrix should be square!");
    }
}

namespace algebra {

Matrix zeros(size_t n, size_t m) {
    return Matrix(n, std::vector<double>(m, 0));
}

Matrix ones(size_t n, size_t m) {
    return Matrix(n, std::vector<double>(m, 1));
}

Matrix random(size_t n, size_t m, double min, double max) {
    if (min > max) {
        throw std::logic_error("Min should be smaller than max!");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(min, max);
    
    Matrix mat = zeros(n, m);
    for (auto &row : mat) {
        for (double &ele : row) {
            ele = distribution(gen);
        }
    }
    
    return mat;
}

void show(const Matrix& matrix) {
    if (matrix.empty()) {
        std::cout << "Empty!" << std::endl;
        return;
    }

    for (auto &row : matrix) {
        for (const double &ele : row) {
            // prevent situations like -0.000
            std::cout << std::fixed << std::setprecision(3) << std::left
                << ((abs(ele) < 0.0005) ? 0.000 : ele) << "\t";
        }
        std::cout << std::endl;
    }
}

Matrix multiply(const Matrix& matrix, double c) {
    if (matrix.empty()) {
        return matrix;
    }

    Matrix mat(matrix);
    for (auto &row : mat) {
        for (double &ele : row) {
            ele *= c;
        }
    }

    return mat;
}

Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.empty() && matrix2.empty()) {
        return Matrix{};
    } else if (matrix1.empty() || matrix2.empty()) {
        throw std::logic_error("Empty matrix is not allowed!");
    }

    int n_rows_1 = matrix1.size();
    int n_cols_1 = matrix1[0].size();
    int n_rows_2 = matrix2.size();
    int n_cols_2 = matrix2[0].size();

    if (n_cols_1 != n_rows_2) {
        throw std::logic_error("The column number of matrix1 should \
be equal to the row number of matrix2!");
    }

    Matrix mat = zeros(n_rows_1, n_cols_2);
    for (int i = 0; i < n_rows_1; i++) {
        for (int j = 0; j < n_cols_2; j++) {
            mat[i][j] = 0;
            for (int k = 0; k < n_cols_1; k++) {
                mat[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return mat;
}

Matrix sum(const Matrix& matrix, double c) {
    if (matrix.empty()) {
        return matrix;
    }

    Matrix mat(matrix);
    for (auto &row : mat) {
        for (double &ele : row) {
            ele += c;
        }
    }

    return mat;
}

Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.empty() && matrix2.empty()) {
        return Matrix{};
    } else if (matrix1.empty() || matrix2.empty()) {
        throw std::logic_error("Empty matrix is not allowed!");
    }

    int n_rows_1 = matrix1.size();
    int n_cols_1 = matrix1[0].size();
    int n_rows_2 = matrix2.size();
    int n_cols_2 = matrix2[0].size();

    if (n_rows_1 != n_rows_2 || n_cols_1 != n_cols_2) {
        throw std::logic_error("Matrices with different size is not permitted!");
    }

    Matrix mat = zeros(n_rows_1, n_cols_1);
    for (int i = 0; i < n_rows_1; i++) {
        for (int j = 0; j < n_cols_1; j++) {
            mat[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return mat;
}

Matrix transpose(const Matrix& matrix) {
    if (matrix.empty()) {
        return matrix;
    }

    int n_rows = matrix.size();
    int n_cols = matrix[0].size();

    Matrix mat = zeros(n_cols, n_rows);
    for (int i = 0; i < n_cols; i++) {
        for (int j = 0; j < n_rows; j++) {
            mat[i][j] = matrix[j][i];
        }
    }

    return mat;
}

Matrix minor(const Matrix& matrix, size_t n, size_t m) {
    int n_rows = matrix.size();
    int n_cols = matrix[0].size();

    Matrix mat = zeros(n_rows - 1, n_cols - 1);
    for (int i = 0; i < n_rows; i ++) {
        if (i == n) {
            continue;
        }
        for (int j = 0; j < n_cols; j++) {
            if (j == m) {
                continue;
            }
            mat[i < n ? i : i-1][j < m ? j : j-1] = matrix[i][j];
        }
    }

    return mat;
}

double determinant(const Matrix& matrix) {
    int n_rows = matrix.size();
    if (n_rows == 0) {
        return 1;
    }
    int n_cols = matrix[0].size();
    if (n_cols == 0) {
        return 1;
    }

    if (n_rows == 1 && n_cols == 1) {
        return matrix[0][0];
    }

    check_square(n_rows, n_cols);

    double det = 0;
    for (int j = 0; j < n_cols; j++) {
        det += std::pow(-1, j) * matrix[0][j] * determinant(minor(matrix, 0, j));
    }

    return det;
}

static Matrix adjoint(const Matrix& matrix) {
    if (matrix.empty()) {
        return matrix;
    }

    int n_rows = matrix.size();
    int n_cols = matrix[0].size();

    Matrix mat = zeros(n_rows, n_cols);
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            mat[j][i] = std::pow(-1, i + j) * determinant(minor(matrix, i, j));
        }
    }

    return mat;
}

Matrix inverse(const Matrix& matrix) {
    if (matrix.empty()) {
        return matrix;
    }

    int n_rows = matrix.size();
    int n_cols = matrix[0].size();

    check_square(n_rows, n_cols);

    double det = determinant(matrix);
    if (det == 0) {
        throw std::logic_error("The matrix should be non_singular_matrix!");
    }
    Matrix adjoint_mat = adjoint(matrix);

    return multiply(adjoint_mat, 1 / det);
}

Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
    if (matrix1.empty()) {
        return matrix2;
    }
    if (matrix2.empty()) {
        return matrix1;
    }

    int n_rows_1 = matrix1.size();
    int n_cols_1 = matrix1[0].size();
    int n_rows_2 = matrix2.size();
    int n_cols_2 = matrix2[0].size();

    Matrix mat;

    if (axis == 0) {
        if (n_cols_1 != n_cols_2) {
            throw std::logic_error("Matrices with different column numbers \
is not permitted when using axis 0!");
        }
        mat = zeros(0, 0);
        mat.insert(mat.end(), matrix1.begin(), matrix1.end());
        mat.insert(mat.end(), matrix2.begin(), matrix2.end());
    }

    if (axis == 1) {
        if (n_rows_1 != n_rows_2) {
            throw std::logic_error("Matrices with different column numbers \
is not permitted when using axis 1!");
        }
        mat = zeros(n_rows_1, 0);
        for (int i = 0; i < n_rows_1; i++) {
            mat[i].insert(mat[i].end(), matrix1[i].begin(), matrix1[i].end());
            mat[i].insert(mat[i].end(), matrix2[i].begin(), matrix2[i].end());
        }
    }

    return mat;
}

Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
    if (matrix.empty()) {
        throw std::logic_error("Empty matrix is not allowed!");
    }
    int n_rows = matrix.size();
    if (r1 >= n_rows || r2 >= n_rows) {
        throw std::logic_error("r1 or r2 is out of range!");
    }

    Matrix mat(matrix);
    auto row_temp = mat[r1];
    mat[r1] = mat[r2];
    mat[r2] = row_temp;

    return mat;
}

Matrix ero_multiply(const Matrix& matrix, size_t r, double c) {
    if (matrix.empty()) {
        throw std::logic_error("Empty matrix not allowed!");
    }
    int n_rows = matrix.size();
    if (r >= n_rows) {
        throw std::logic_error("r is out of range!");
    }
    
    Matrix mat(matrix);
    for (auto &ele : mat[r]) {
        ele *= c;
    }

    return mat;
}

Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
    if (matrix.empty()) {
        throw std::logic_error("Empty matrix not allowed!");
    }
    int n_rows = matrix.size();
    if (r1 >= n_rows) {
        throw std::logic_error("r is out of range!");
    }
    
    int n_cols = matrix[0].size();
    
    Matrix mat(matrix);
    auto &row = mat[r2];
    for (int j = 0; j < n_cols; j++) {
        row[j] += c * mat[r1][j];
    }

    return mat;
}

Matrix upper_triangular(const Matrix& matrix) {
    if (matrix.empty()) {
        return matrix;
    }

    int n_rows = matrix.size();
    int n_cols = matrix[0].size();

    check_square(n_rows, n_cols);

    Matrix mat(matrix);
    int loop_times = n_rows - 1;
    for (int k = 0; k < loop_times; k++) {
        for (int i = k + 1; i < n_rows; i++) {
            // come across a zero on the main diagonal 
            if (mat[k][k] == 0) {
                bool swapped = false;
                for (int j = k + 1; j < n_rows; j++) {
                    if (mat[j][k] != 0) {
                        mat = ero_swap(mat, k, j);
                        swapped = true;
                        break;
                    }
                }
                if (!swapped) {
                    // throw an error if there must be a 0 on the main diagonal
                    throw std::logic_error("There is a 0 on the main diagonal!");
                }
            }
            mat = ero_sum(mat, k, -mat[i][k]/mat[k][k], i);
        }
    }

    return mat;
}

}