#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include <chrono>

// пример рекурсивной реализации
void sort3(int A[], int l, int r){
    if (l >= r)
        return;
    int i=l, j=r, xm=A[(l+r)/2];
    while(i<=j){
        while(A[i]<xm) i++;
        while(A[j]>xm) j--;
        if(i<=j){
            std::swap(A[i], A[j]);
            i++;
            j--;
        }
    }
    sort3(A, l, j);
    sort3(A, i, r);
}

void sort3(int A[], int len){
    sort3(A, 0, len-1);
}

struct elem{int L, R;};

void nonRecH(int mas[], int size){
    elem *S = new elem[(int) ceil(log2(size))];
    int k=0; S[0].L=0; S[0].R=size-1;
    while(k>=0){
        int l = S[k].L, r = S[k].R; k--;
        if (l >= r)
            continue;
        int i=l, j=r, xm=mas[(l+r)/2];
        while(i<=j){
            while(mas[i]<xm) i++;
            while(mas[j]>xm) j--;
            if(i<=j){
                std::swap(mas[i], mas[j]);
                i++;
                j--;
            }
        }
        if (j-l < r-i){
            k++; S[k].L=i; S[k].R=r;
            k++; S[k].L=l; S[k].R=j;
        } else {
            k++; S[k].L=l; S[k].R=j;
            k++; S[k].L=i; S[k].R=r;
        }
    }
}

bool is_sorted(int* begin, int* end){
    begin++;
    for(; begin!=end; begin++)
        if(*(begin-1) > *begin)
            return false;
    return true;
}

int main(){
    std::ifstream fin;
    const int len = 8;
    int mas[] = {6, 7, 11, 4, 3, 1, 2, 9};
    nonRecH(mas, len);
    for(int i=0; i<len; i++)
        std::cout << mas[i] << " ";
    std::cout << std::endl;
    std::cout << is_sorted(mas, mas + len) << std::endl;
    std::cout << "size\t\td\tis_sorted\ttime\n";
    for(int size=10000; size<=1000000; size*=10)
        for(int d=10; d<=100000; d*=100){
            char buf[100];
            snprintf(buf, sizeof(buf), "../data/S%dD%d.txt", size, d);
            fin.open(buf);
            int *mas = new int[size];
            for(int i=0; i<size; i++)
                fin >> mas[i];
                fin.close();
                double sumdur = 0;
            int *itermas = new int[size];
            for(int i = 0; i<3; i++){
                std::memcpy(itermas, mas, size*sizeof(int));
                std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
                nonRecH(itermas, size);
                std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = timeEnd - timeStart;
                sumdur += duration.count();
            }   
            std::cout << size << "\t\t" << d << "\t" << is_sorted(itermas, itermas+size) << "\t\t" << (sumdur / 3) << std::endl;
            delete[] mas;
            delete[] itermas;
        }
}
