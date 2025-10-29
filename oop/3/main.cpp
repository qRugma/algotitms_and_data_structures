#include <iostream>

#include "booleanvector.cpp"

int main(){
    BooleanVector vec = "10101";

    for(int i=0; i < vec.getLenght(); i++)
        std::cout << vec[i];
    std::cout << std::endl;
    
    std::cout << "weight = " << vec.getWeight() << std::endl;
    
    std::cout << "invert_all() "<< std::endl;
    vec.invert_all();
    std::cout << vec << std::endl;
    
    std::cout << "invert(index: 2) "<< std::endl;
    vec.invert(2);
    std::cout << vec << std::endl;
    
    std::cout << "set_value(value: 1, index: 2)"<< std::endl;
    vec.set_value(1, 2);
    std::cout << vec << std::endl;
    std::cout << "set_value(value: 0, index: 2)"<< std::endl;
    vec.set_value(0, 2);
    std::cout << vec << std::endl;
    std::cout << "set_value(value: 0, index: 2)"<< std::endl;
    vec.set_value(0, 2);
    std::cout << vec << std::endl;

    std::cout << "set_value_all(value: 0)"<< std::endl;
    vec.set_value_all(0);
    std::cout << vec << std::endl;

    std::cout << "set_value_from(value: 1, index: 2)"<< std::endl;
    vec.set_value_from(1, 2);
    std::cout << vec << std::endl;


    BooleanVector vec0 = "0000000001", vec1="1111110011";
    std::cout << "vec0 = " << vec0 << std::endl;
    std::cout << "vec1 = " << vec1 << std::endl;

    std::cout << "vec0 & vec1"<< std::endl;
    std::cout << (vec0 & vec1) << std::endl;
    std::cout << "vec0 | vec1"<< std::endl;
    std::cout << (vec0 | vec1) << std::endl;
    std::cout << "vec0 ^ vec1"<< std::endl;
    std::cout << (vec0 ^ vec1) << std::endl;
    std::cout << "vec1 << 2"<< std::endl;
    std::cout << (vec1 << 2) << std::endl;
    vec1 <<= 2;
    std::cout << vec1 << std::endl;
    std::cout << "vec1 >> 2"<< std::endl;
    std::cout << (vec1 >> 2) << std::endl;
    vec1 >>= 2;
    std::cout << vec1 << std::endl;
    std::cout << "~vec1"<< std::endl;
    std::cout << (~vec1) << std::endl;

}