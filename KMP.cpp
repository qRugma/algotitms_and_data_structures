// #include "lib1.hpp"
#include <iostream>
#include <string>

int* getNewJ(int* P, int len){
    int j=0, k=-1, m=len;
    int* NewJ = new int[m];
    NewJ[0] = -1;

    while(j<m-1){
        if (k>=0 and P[j]!=P[k]){
            k=NewJ[k];
            continue;
        }
        k++; j++;
        if (P[j] == P[k])
            NewJ[j] = NewJ[k];
        else
            NewJ[j] = k;
    }
    return NewJ;
}

int KMP_Search(int* P, int* NewJ, int lenJ, int* str, int lenS){
    int i=0, j=0, m=lenJ, n=lenS;
    while(true){
        if (j>=m)
            return i-m;
        if (i>=n){
            return -1;
        }
        while(j>=0 and str[i] != P[j])
            j = NewJ[j];
        i++; j++;
    }
}



int main(){
    int P[] = {1, 0, 0, 1, 0, 1, 1, 0};
    int S[] = {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0};
    int lenP= 8, lenS = 17;
    int* NewJ = getNewJ(P, lenP);
    for(int i=0; i<lenP; i++){
        std::cout << NewJ[i] << " ";
    }
    std::cout << std::endl;
    
    int answer = KMP_Search(P, NewJ, lenP, S, lenS);
    std::cout << "Answer: " << answer << std::endl;
    for(int i=0; i<lenS; i++){
        std::cout << S[i] << " ";
    }
    std::cout << std::endl;
    for(int i=0; i<answer; i++)
        std::cout << "  ";
    for(int i=answer; i<answer+8; i++){
        std::cout << S[i] << " ";
    }
    std::cout << std::endl;

}