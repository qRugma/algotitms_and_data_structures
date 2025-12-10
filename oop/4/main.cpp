#include "booleanmatrix.hpp"
#include <iostream>

int main() {
    // BooleanVector vec("111");
    // std::cin >> vec[1];

    const char *data[] = {"101", "010"};
    BooleanMatrix mat(data, 2), mat2(data, 2), mat3;
    bool flag = false;
    std::cout << "type 1 if need input matrix, 0 if no: ";
    std::cin >> flag;
    if (flag) {
        std::cout << "mat 2X3:" << std::endl;
        std::cin >> mat;
        std::cout << "mat2 2X3:" << std::endl;
        std::cin >> mat2;
        std::cout << std::endl;
    }

    std::cout << mat;
    std::cout << "mat.columns()" << std::endl;
    std::cout << mat.columns() << std::endl;
    std::cout << "mat.rows()" << std::endl;
    std::cout << mat.rows() << std::endl;
    std::cout << "mat.weight()" << std::endl;
    std::cout << mat.weight() << std::endl;
    std::cout << "mat.weight(row: 0)" << std::endl;
    std::cout << mat.weight(0) << std::endl;
    std::cout << "mat.conjunction()" << std::endl;
    std::cout << mat.conjunction() << std::endl;
    std::cout << "mat.disjunction()" << std::endl;
    std::cout << mat.disjunction() << std::endl;
    std::cout << "mat.invert(row: 0, column: 1)" << std::endl;
    mat.invert(0, 1);
    std::cout << mat << std::endl;
    std::cout << "mat.invert(row: 1, column: 0, k: 3)" << std::endl;
    mat.invert_k(1, 0, 3);
    std::cout << mat << std::endl;

    std::cout << "mat.set(row: 0, column: 1, value: 0)" << std::endl;
    mat.set(0, 1, 0);
    std::cout << mat << std::endl;

    std::cout << "mat.set_k(row: 1, column: 0, value: 1, k: 3)" << std::endl;
    mat.set_k(1, 0, 1, 3);
    std::cout << mat << std::endl;

    std::cout << "mat[0][1]" << std::endl;
    std::cout << mat[0][1] << std::endl << std::endl;

    std::cout << "mat & ~mat" << std::endl;
    std::cout << (mat & ~mat) << std::endl;
    mat3 = mat;
    std::cout << (mat3 &= ~mat3) << std::endl;
    std::cout << "mat | ~mat2" << std::endl;
    std::cout << (mat | mat2) << std::endl;
    mat3 = mat;
    std::cout << (mat3 |= mat2) << std::endl;
    std::cout << "mat ^ ~mat2" << std::endl;
    std::cout << (mat ^ mat2) << std::endl;
    mat3 = mat;
    std::cout << (mat3 ^= mat2) << std::endl;
    std::cout << "~mat" << std::endl;
    std::cout << ~mat << std::endl;
    std::cout << "mat.swap(mat2)" << std::endl;
    mat.swap(mat2);
    std::cout << mat << std::endl;
}