#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include <chrono>

void bitsort(int l, int r, int k, int *mas){
    if (l>=r or k < 0)
        return;
    int i = l, j = r, mask = 1 << k;
    while (i <= j){
        while (i <= j and !(mas[i]&mask)) i++;
        while (i <= j and (mas[j]&mask)) j--;
        if (i < j)
            std::swap(mas[i++], mas[j--]);
    }
    bitsort(l, j, k-1, mas);
    bitsort(i, r, k-1, mas);
}

void bitsort(int mas[], int len){
    int i = 0, j = len-1, mask = 1 << 31;
    while (i <= j){
        while (i <= j and (mas[i]&mask)) i++;
        while (i <= j and !(mas[j]&mask)) j--;
        if (i < j)
            std::swap(mas[i++], mas[j--]);
    }

    bitsort(0, j, 30, mas);    
    bitsort(i, len-1, 30, mas);    
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
    const int len = 10;
    int mas[] = {-2, 12, 5, 8, 1, -0, 0, -12, -5, -8};
    bitsort(mas, len);
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
                bitsort(mas, size);
                std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = timeEnd - timeStart;
                sumdur += duration.count();
            }   
            std::cout << size << "\t\t" << d << "\t" << is_sorted(itermas, itermas+size) << "\t\t" << (sumdur / 3) << std::endl;
            delete[] mas;
            delete[] itermas;
        }
}
