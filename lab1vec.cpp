#include <iostream>
#include <chrono>
#include <random>
#include <cstring>
#include <utility>
#include <algorithm>
#include <vector>

// компилировать с флагом -O2 для g++
// иначе вычисления дольше в 29 раз

inline bool nextPerm(std::vector<int>::iterator P, int len){
    int i = len - 2, j = len - 1;
    bool flag = true;
    for(; i>=0; i--){
        if (P[i] < P[i+1]){
            flag = false;
            break;
        }
    }
    if (flag){
        return false;
    }
    for(; j>i; j--){
        if (P[i] < P[j]){
            std::swap(P[i], P[j]);
            std::reverse(P+i+1, P+len);
            return true;
        }
    }
    return false;
}

#define table_type std::vector<std::vector<int>> 

struct Result{
    int distance = __INT_MAX__;
    std::vector<int> way;
};
// вектора не позволяют выйти за пределы, но замедляют код в 5 раз

Result exactSol(table_type table, int countCity, int startCity=1, bool MIN=true){
    int lenP = countCity + 1;
    std::vector<int> P(lenP);
    for(int i=0; i<countCity; i++){
        if (startCity < i)
            P[i] = i;
        else
            P[i] = i-1;
    }
    P[countCity] = startCity;
    P[0] = startCity;
    
    bool cont = true;
    Result minRes{__INT_MAX__, std::vector<int>(lenP)};
    if (!MIN)
        minRes.distance = 0;
    while (cont){
        int res = 0;
        for(int i=0; i<lenP-1; i++){
            res += table[P[i]][P[i+1]];
        }
        if ((MIN and (res < minRes.distance)) or (!MIN and (res > minRes.distance))){
            minRes.distance = res;
            minRes.way = P;
        }
        cont = nextPerm(P.begin()+1, lenP-2);
    }
    return minRes;
}


Result heuristSol(table_type table, int countCity){
    Result minRes{0, std::vector<int>(countCity+1)};
    minRes.way[0] = 1;
    minRes.way[countCity] = 1;
    
    std::vector<int> J(countCity+1);
    for(int j=0; j<countCity; J[j++]=j);
    int way = 0;
    int prevCity = 0;
    for(int i=0; i<countCity-1; i++){
        int minDis = __INT_MAX__;
        int minWay = -1;
        for(int k=1, j=J[1]; k<countCity; j=J[++k]){
            if (j == -1 or table[way][j] == 0 or j == prevCity)
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
    table_type tablevec(countCity, std::vector<int>(countCity));
    std::uniform_int_distribution<int> distribution(rangeStart, rangeEnd);

    
    for(int i=0; i < countCity; i++){
        for(int j=0; j<countCity; j++){
            if (i==j)
                tablevec[i][j] = 0;
            else
                tablevec[i][j] = distribution(generator);
        }
        // print(table[i], countCity);
    }

    while (true){
        // Result res0 = exactSol(tablevec, countCity, startCity, false);
        std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
        Result res = exactSol(tablevec, countCity, startCity);
        std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationex = timeEnd - timeStart;
        

        timeStart = std::chrono::high_resolution_clock::now();
        Result res2 = heuristSol(tablevec, countCity);
        timeEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = timeEnd - timeStart;
        // for(auto i : res.way){
        //     std::cout << i << " ";
        // }
        // std::cout << std::endl;
        // for(auto i : res2.way){
        //     std::cout << i << " ";
        // }
        std::cout << std::endl;
        std::cout << "лучший= "<< res.distance << std::endl;
        // std::cout << "худший= "<< res0.distance << std::endl;
        std::cout << "exact duration= " << durationex.count() << std::endl;
        std::cout << "эвристика= "<< res2.distance << std::endl;
        std::cout << "heurist duration= " << duration.count() << std::endl;
        std::cout << (res2.distance < res.distance) << std::endl;
        std::cout << "start\n";
        std::cin >> startCity;
    }
}