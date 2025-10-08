#include <iostream>
#include "oop1.hpp"

void autotest(FreeVector vec, FreeVector vec2){
    FreeVector  vec3;

    std::cout << "vec: " << vec.getX() << " " << vec.getY() << " " << vec.getZ() << std::endl;

    vec3.newCoors(1, 5, 2);
    std::cout << "vec3: " << vec3 << std::endl;

    std::cout << "lenght=" << vec.lenght() << std::endl << std::endl;
    
    std::cout << "orthonormal: " << (vec3 = vec.orthonormal()).lenght() << std::endl;

    std::cout << "sum: " << std::endl;
    vec3 = vec + vec2;
    std::cout << vec3;
    std::cout << std::endl;
    
    std::cout << "subtraction: " << std::endl;
    vec3 = vec - vec2;
    std::cout << vec3;
    std::cout << std::endl;

    std::cout << "multipcation: " << std::endl;
    vec3 = vec*2;
    std::cout << vec3;
    std::cout << std::endl;

    std::cout << "equal: " << std::endl;
    std::cout << std::boolalpha;
    std::cout << "vec==vec: " << (vec == vec) << std::endl;
    std::cout << "vec!=vec: " << (vec != vec) << std::endl;
    std::cout << "vec==vec2: " << (vec == vec2) << std::endl;
    std::cout << std::endl;

    std::cout << "scalar: " << std::endl;
    std::cout << vec.scalar(vec2) << std::endl << std::endl;

    std::cout << "vector multiplication: " << std::endl;
    vec3 = vec.vectorProduct(vec2);
    std::cout << vec3;
    std::cout << std::endl;

    std::cout << "tripleProduct: " << std::endl;
    std::cout << vec.tripleProduct(vec2, vec3) << std::endl;
    std::cout << vec.tripleProduct(vec3, vec2) << std::endl;

    std::cout << "doubleVectorProduct: " << std::endl;
    vec3 = vec.doubleVectorProduct(vec2, vec3);
    std::cout << vec3;
}


int main(){
    FreeVector vec{1, 1, 3}, vec2{1, -2, 6};
    int choise=0;
    std::cout << "0=standart, 1=input vectors: ";
    std::cin >> choise;
    std::cout << std::endl;
    if (choise == 0)
        autotest(vec, vec2);
    else if (choise == 1){
        std::cin >> vec >> vec2;
        autotest(vec, vec2);
    }
        
}