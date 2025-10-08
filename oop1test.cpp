#include <iostream>
#include "oop1.hpp"

void autotest(){
        FreeVector vec{0, 1, 0, 1, 2, 3}, vec2{0, 2, 3, 0, -2, 6}, vec3;
    // vec.print();
    // vec2.print();
    // for(int i=0; i<3; i++)
    //     vec.getRadius()[i] = 0;
        
    //геттеры
    std::cout << "getStart: ";
    for(int i=0; i<3; i++)
        std::cout << vec.getStart()[i] << " ";
    std::cout << std::endl << "getEnd: ";
    for(int i=0; i<3; i++)
        std::cout << vec.getEnd()[i] << " ";
    std::cout << std::endl << "getRadius: ";
    for(int i=0; i<3; i++)
        std::cout << vec.getRadius()[i] << " ";
    std::cout << std::endl;

    std::cout << "lenght=" << vec.lenght() << std::endl;
    
    std::cout << "sum: " << std::endl;
    vec3 = vec + vec2;
    vec3.print();
    std::cout << std::endl;
    
    std::cout << "subtraction: " << std::endl;
    vec3 = vec - vec2;
    vec3.print();
    std::cout << std::endl;

    std::cout << "multipcation: " << std::endl;
    vec3 = vec*2;
    vec3.print();
    std::cout << std::endl;

    std::cout << "equal: " << std::endl;
    std::cout << std::boolalpha;
    std::cout << "vec==vec: " << (vec == vec) << std::endl;
    std::cout << "vec==vec2: " << (vec == vec2) << std::endl;
    std::cout << std::endl;

    std::cout << "scalar: " << std::endl;
    std::cout << vec.scalar(vec2) << std::endl << std::endl;

    std::cout << "vector multiplication: " << std::endl;
    vec3 = vec.vectorProduct(vec2);
    vec3.print();
    std::cout << std::endl;

    std::cout << "tripleProduct: " << std::endl;
    std::cout << vec.tripleProduct(vec2, vec3) << std::endl;
    std::cout << vec.tripleProduct(vec3, vec2) << std::endl;
}


int main(){
    int choise=0;
    if (choise == 0)
        autotest();
}