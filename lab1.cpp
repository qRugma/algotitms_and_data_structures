#include "lib1.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include <string.h>

struct Result{
    int distance = __INT_MAX__;
    int* way = nullptr;
};


Result exactSol(int** table, int countCity, int startCity=1, bool MIN=1){
    int *P = new int[countCity+1];
    for(int i=0; i<countCity; i++)
        P[i] = i;
    startCity -= 1;
    P[countCity] = startCity;
    P[0] = startCity;
    
    int lenP = countCity + 1;
    bool cont = true;
    Result minRes;
    minRes.way = new int[countCity+1];
    if (!MIN)
        minRes.distance = 0;
    while (cont){
        int res = 0;
        // print(P, lenP);
        for(int i=0; i<lenP; i++){
            res += table[P[i]][P[i+1]];
        }
        // std::cout << res << " ";
        if (MIN)
            minRes.distance = min(res, minRes.distance);
        else 
            minRes.distance = max(res, minRes.distance);
            
        memcpy(minRes.way, P, (countCity+1) * sizeof(int));
        cont = nextPerm(P+1, lenP-2);
    }
    delete P;
    return minRes;
}


Result heuristSol(int** table, int countCity){
    Result minRes;
    minRes.distance = 0;
    minRes.way = new int[countCity+1];
    minRes.way[0] = 1;
    minRes.way[countCity] = 1;
    int curCity = 0;
    int* J = new int[countCity];
    for(int j=0; j<countCity; J[j++]=j);
    int way = 0;
    int prevCity = 0;
    for(int i=0; i<countCity-1; i++){
        int minDis = __INT_MAX__;
        int minWay = -1;
        for(int k=1, j=J[1]; k<countCity; j=J[++k]){
            if (table[way][j] == 0 or j == -1 or j == prevCity)
                continue;
            if (table[way][j] < minDis){
                minDis = table[way][j];
                minWay = j;
            }
        }
        minRes.distance += minDis;
        minRes.way[i+1] = minWay+1;
        J[minWay] = -1;
        prevCity = way;
        way = minWay;
    }
    minRes.distance += table[way][0];
    return minRes;
}


int main(){
    std::random_device randomDevice;
    std::mt19937_64 generator(randomDevice());
    int rangeStart, rangeEnd, countCity, startCity = 1;
    std::cout << "Rstart, Rend, count\n";
    std::cin >> rangeStart >> rangeEnd >> countCity;
    std::uniform_int_distribution<int> distribution(rangeStart, rangeEnd);

    int** table = makeTwoDimMas(countCity);
    
    for(int i=0; i < countCity; i++){
        for(int j=0; j<countCity; j++)
            if (i==j)
                table[i][j] = 0;
            else
                table[i][j] = distribution(generator);
        
        // print(table[i], countCity);
    }

    Result res0 = exactSol(table, countCity, startCity, false);
    std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
    Result res = exactSol(table, countCity, startCity);
    std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationex = timeEnd - timeStart;
    
    
    timeStart = std::chrono::high_resolution_clock::now();
    Result res2 = heuristSol(table, countCity);
    timeEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = timeEnd - timeStart;
    
    std::cout << "лудший= "<< res.distance << std::endl;
    std::cout << "худший= "<< res0.distance << std::endl;
    std::cout << "exact duration= " << durationex.count() << std::endl;
    std::cout << "эвристика= "<< res2.distance << std::endl;
    std::cout << "heurist duration= " << duration.count() << std::endl;

    delete res.way, res2.way;
    deleteTwoDimMas(table, countCity, countCity);
}