#include "lib1.hpp"
#include <iostream>
#include <chrono>
#include <random>

int main(){

    std::random_device randomDevice;
    std::mt19937_64 generator(randomDevice());
    int rangeStart, rangeEnd, countCity, startCity = 0;

    std::cin >> rangeStart >> rangeEnd >> countCity;
    int **table = new int *[countCity];

    for(int i=0; i < countCity; i++){
        table[i] = new int[countCity];
    }

    std::uniform_int_distribution<int> distribution(rangeStart, rangeEnd);

    std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
    
    for(int i=0; i < countCity; i++){
        for(int j=0; j<countCity; j++)
            if (i==j)
                table[i][j] = 0;
            else
                table[i][j] = distribution(generator);
        
        print(table[i], countCity);
    }
    int *P = new int[countCity+1];
    for(int i=0; i<countCity; i++)
        P[i] = i;
    P[countCity] = 0;
    print(P, countCity+1);

    int lenP = countCity + 1;
    bool cont = true;
    while (cont){
        int res = 0;
        print(P, lenP);
        for(int i=0; i<lenP; i++){
            res += table[P[i]][P[i+1]];
        }
        std::cout << "res=" << res << std::endl;
        cont = nextPerm(P+1, lenP-2);
    }   
    std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = timeEnd - timeStart;

    std::cout << duration.count() << std::endl;

}