#include <iostream>
#include <vector>

// #include "vector.hpp"

#include "vector.tpp"

int main(){
    int choise = 0;
    int mas[] = {1, 2, 3, 4, 5}, mas2[] = {6, 7, 8};
    // Vector vec(mas, 5), vec2(mas2, 3);
    // Vector vecs = {0, 2, 3, 3, 3, 1, 6, 5, 4};
    Vector<int> vec(mas, 5), vec2(mas2, 3);
    Vector<short int> vecs = {0, 2, 3, 3, 3, 1, 6, 5, 4};
    std::cout << "0 - auto, 1 - write\n";
    std::cin >> choise;
    if (choise){
        std::cout << "write 5 elements: ";
        std::cin >> vec;
        std::cout << "\nwrite 3 elements: ";
        std::cin >> vec2;
    }
    std::cout << "vec.size: ";
    std::cout << vec.size() << std::endl;
    std::cout << "vec.swap(vec2)\n";
    vec.swap(vec2);
    std::cout << vec << std::endl;
    vec.swap(vec2);
    std::cout << "vec.find(vec[3]): " << vec.find(vec[3]) << std::endl;
    std::cout << "vec.insert(index: 3, value: 5)\n";
    vec.insert(3, 5);
    std::cout << vec << std::endl;
    std::cout << "vec.pop(index: 3)\n";
    vec.pop(3);
    std::cout << vec << std::endl;
    
    std::cout << "vecs.remove(value: 3)\n";
    vecs.remove(3);
    std::cout << vecs << std::endl;
    
    std::cout << "vecs.remove_all(value: 3)\n";
    vecs.remove_all(3);
    std::cout << vecs << std::endl;
    
    std::cout << "vec.max(): " << vec.max() << std::endl;
    std::cout << "vec.min(): " << vec.min() << std::endl;
    
    std::cout << "vec[2] = " << vec[2] << std::endl;
    
    std::cout << "vec (+) += 2\n";
    std::cout << (vec +  2) << std::endl;
    std::cout << (vec += 2) << std::endl;
    
    std::cout << "vec (+) += vec2\n";
    std::cout << (vec +  vec2) << std::endl;
    std::cout << (vec += vec2) << std::endl;

    std::cout << "vec == vec:  " << (vec == vec) << std::endl;
    std::cout << "vec == vec2: " << (vec == vec2) << std::endl;

    std::cout << "vec.sort()" << std::endl;
    vec.sort(); 
    std::cout << vec << std::endl;
}