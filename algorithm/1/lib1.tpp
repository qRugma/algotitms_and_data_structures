#pragma once

#include <iostream>

template<typename T>
void print(const T& mas, int len){
    for(int i=0; i<len; i++)
        std::cout << mas[i] << " ";
    std::cout << std::endl;
}
