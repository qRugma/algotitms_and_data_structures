#include "lib1.hpp"
#include <iostream>
#include <chrono>
#include <random>

int main(){

    // std::random_device randomDevice;
    // std::mt19937_64 generator(randomDevice());
    // int rangeStart, rangeEnd;

    // std::cin >> rangeStart >> rangeEnd;

    // std::uniform_int_distribution<int> distribution(rangeStart, rangeEnd);

    // std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
    
    // for(int i=0; i < 20; i++){
    //     std::cout << distribution(generator) << " ";
    // }
    // std::cout << std::endl;

    // std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
    
    // std::chrono::duration<double> duration = timeEnd - timeStart;

    // std::cout << duration.count() << std::endl;
    int P[] = {1, 2, 3, 4, 1}, len = 5;
    while (nextPerm(P+1, len-2))
        print(P, len);
    
}