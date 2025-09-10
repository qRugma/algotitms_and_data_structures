#include "lib1.hpp"
#include <iostream>
#include <algorithm>

bool nextPerm(int *P, int len){
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
            swap(P[i], P[j]);
            std::sort(&P[i+1], &P[len]);
            return true;
        }
    }
    return false;
}

int** makeTwoDimMas(int n, int m){
    int** mas = new int*[n];
    for(int i=0; i<n; i++)
        mas[i] = new int[m];
    return mas;
}

int** makeTwoDimMas(int n){
    return makeTwoDimMas(n, n);
}

