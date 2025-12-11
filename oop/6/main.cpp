#include "set.hpp"
#include <iostream>

int main(){
    Set a("asd"), b("52"), c("ascv");
    std::cin >> a;
    std::cout << a << std::endl;
    std::cout << "weight: " << a.weight() << std::endl;
    a += 'O';
    std::cout << a << std::endl;
    std::cout << "weight: " << a.weight() << std::endl;
    a -= 'O';
    std::cout << a << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "a|b: ";
    std::cout << (a|b) << std::endl;
    std::cout << "a/c: ";
    std::cout << (a/c) << std::endl;
    std::cout << "c/a: ";
    std::cout << (c/a) << std::endl;
    std::cout << "c/=a: ";
    std::cout << (c/=a) << std::endl;
    std::cout << "a&c: ";
    std::cout << (a&c) << std::endl;
    b = a;
    Set h = c;
    std::cout << "h!=c: ";
    std::cout << (h!=c) << std::endl;
    std::cout << "a==b: ";
    std::cout << (a==b) << std::endl;
    std::cout << "a==c: ";
    std::cout << (a==c) << std::endl;
    std::cout << "a max: "<< a.max() << std::endl; 
    std::cout << "a min: "<< a.min() << std::endl;
    std::cout << "a.includes(a): "<< a.includes('a') << std::endl;
    std::cout << "~a" << std::endl;
    std::cout << ~a << std::endl;

    BooleanVector bol = "01010100101", *ptr;

    ptr = &bol;
    ptr->output();
    std::cout << std::endl;
    ptr = (BooleanVector*) &a;
    ptr->output();
    std::cout << std::endl;

}