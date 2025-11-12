#include <iostream>
#include "booleanmatrix.cpp"

int main(){
    const char* data[] = {"101", "010"};
    BooleanMatrix mat(data, 2), mat2(data, 2), mat3;
    std::cout << mat;
    std::cout << "mat.columns()" << std::endl;
    std::cout << mat.columns() << std::endl;
    std::cout << "mat.rows()" << std::endl;
    std::cout << mat.rows() << std::endl;
    std::cout << "mat.weight()" << std::endl;
    std::cout << mat.weight() << std::endl;
    std::cout << "mat.weight(0)" << std::endl;
    std::cout << mat.weight(0) << std::endl;
    std::cout << "mat.conjunction" << std::endl;
    std::cout << mat.conjunction() << std::endl;
    std::cout << "mat.disjunction" << std::endl;
    std::cout << mat.disjunction() << std::endl;
    std::cout << "mat.invert(0, 1)" << std::endl;
    mat.invert(0, 1);
    std::cout << mat << std::endl;
    std::cout << "mat.invert(1, 0, 3)" << std::endl;
    mat.invert_k(1, 0, 3);
    std::cout << mat << std::endl;
    
    std::cout << "mat.set(0, 1, 0)" << std::endl;
    mat.set(0, 1, 0);
    std::cout << mat << std::endl;
    
    std::cout << "mat.set_k(1, 0, 1, 3)" << std::endl;
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