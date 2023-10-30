
#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
        std::cout << "Test random:" << std::endl;
        std::cout << "---------------------" << std::endl;
        algebra::Matrix matrix = algebra::random(3, 4, 0, 10);
        algebra::show(matrix);
        std::cout << "=====================" << std::endl;

        std::cout << "Test multiply/sum c:" << std::endl;
        std::cout << "---------------------" << std::endl;
        algebra::Matrix matrix_m1 = algebra::multiply(matrix, 2);
        std::cout << "New matrix after mutilpy by 2:" << std::endl;
        algebra::show(matrix_m1);
        std::cout << "---------------------" << std::endl;
        algebra::Matrix matrix_s1 = algebra::sum(matrix, 2);
        std::cout << "New matrix after sum by 2:" << std::endl;
        algebra::show(matrix_s1);
        std::cout << "---------------------" << std::endl;
        std::cout << "Previous matrix:" << std::endl;
        algebra::show(matrix);
        std::cout << "=====================" << std::endl;

        std::cout << "Test multiply/sum matrix:" << std::endl;
        std::cout << "---------------------" << std::endl;
        algebra::Matrix matrix_m21 = {{1, 2, 3}, {4, 5, 6}};
        algebra::Matrix matrix_m22 = {{1, 4}, {2, 5}, {3, 6}};
        algebra::Matrix matrix_m2 = algebra::multiply(matrix_m21, matrix_m22);
        std::cout << "New matrix after mutilpy:" << std::endl;
        algebra::show(matrix_m2);
        std::cout << "---------------------" << std::endl;
        algebra::Matrix matrix_s2 = algebra::sum(matrix, matrix_s1);
        std::cout << "New matrix after sum:" << std::endl;
        algebra::show(matrix_s2);
        std::cout << "=====================" << std::endl;

        std::cout << "Test transpose:" << std::endl;
        std::cout << "---------------------" << std::endl;
        algebra::Matrix matrix_t = algebra::transpose(matrix);
        algebra::show(matrix_t);
        std::cout << "=====================" << std::endl;

        std::cout << "Test minor:" << std::endl;
        std::cout << "---------------------" << std::endl;
        algebra::Matrix matrix_minor = algebra::minor(matrix, 1, 2);
        algebra::show(matrix_minor);
        std::cout << "=====================" << std::endl;

        std::cout << "Test determinant:" << std::endl;
        std::cout << "---------------------" << std::endl;
        algebra::Matrix matrix_determinant = algebra::ones(3, 3);
        matrix_determinant[0][1] = 0;
        matrix_determinant[2][0] = 0;
        double determinant = algebra::determinant(matrix_determinant);
        algebra::show(matrix_determinant);
        std::cout << "determinant: " << determinant << std::endl;
        std::cout << "=====================" << std::endl;

        std::cout << "Test inverse:" << std::endl;
        std::cout << "---------------------" << std::endl;
        algebra::Matrix matrix_inverse = algebra::inverse(matrix_determinant);
        algebra::show(matrix_inverse);
        std::cout << "=====================" << std::endl;

        std::cout << "Test concatenate:" << std::endl;
        std::cout << "---------------------" << std::endl;
        algebra::Matrix matrix_concat1 = algebra::zeros(3, 3);
        algebra::Matrix matrix_concat2 = algebra::ones(3, 3);
        algebra::Matrix matrix_concat3 = algebra::concatenate(matrix_concat1,
            matrix_concat2);
        algebra::Matrix matrix_concat4 = algebra::concatenate(matrix_concat1,
            matrix_concat2, 1);
        std::cout << "axis=0: " << std::endl;
        algebra::show(matrix_concat3);
        std::cout << "---------------------" << std::endl;
        std::cout << "axis=1: " << std::endl;
        algebra::show(matrix_concat4);
        std::cout << "---------------------" << std::endl;
        std::cout << "Changing the concated won't influence the original: " << std::endl;
        matrix_concat3[0][0] = 9;
        matrix_concat4[0][5] = 9;
        algebra::show(matrix_concat3);
        std::cout << "---------------------" << std::endl;
        algebra::show(matrix_concat4);
        std::cout << "---------------------" << std::endl;
        algebra::show(matrix_concat1);
        std::cout << "---------------------" << std::endl;
        algebra::show(matrix_concat2);
        std::cout << "=====================" << std::endl;

        std::cout << "Test ero:" << std::endl;
        std::cout << "---------------------" << std::endl;
        algebra::Matrix matrix_ero = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        std::cout << "original: " << std::endl;
        algebra::show(matrix_ero);
        std::cout << "---------------------" << std::endl;
        std::cout << "ero_swap 0 1: " << std::endl;
        algebra::show(algebra::ero_swap(matrix_ero, 0, 1));
        std::cout << "---------------------" << std::endl;
        std::cout << "ero_multiply 0 2: " << std::endl;
        algebra::show(algebra::ero_multiply(matrix_ero, 0, 2));
        std::cout << "---------------------" << std::endl;
        std::cout << "ero_sum 0 2 1: " << std::endl;
        algebra::show(algebra::ero_sum(matrix_ero, 0, 2, 1));
        std::cout << "---------------------" << std::endl;
        std::cout << "ero won't influence the original: " << std::endl;
        algebra::show(matrix_ero);
        std::cout << "=====================" << std::endl;

        std::cout << "Test upper_triangular:" << std::endl;
        std::cout << "---------------------" << std::endl;
        algebra::Matrix matrix_triangular = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        std::cout << "original: " << std::endl;
        algebra::show(matrix_triangular);
        std::cout << "---------------------" << std::endl;
        std::cout << "upper_triangular: " << std::endl;
        algebra::show(algebra::upper_triangular(matrix_triangular));
        std::cout << "---------------------" << std::endl;
        std::cout << "operation won't influence the original: " << std::endl;
        algebra::show(matrix_triangular);
        std::cout << "=====================" << std::endl;
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}