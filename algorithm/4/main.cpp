#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include <chrono>

int next_H1(int h){
    return h/2;
}

int next_H2(int m){
    return pow(2, m) - 1;
}

int next_H3(int i){
    if (i%2==0)
        return 9*pow(2, i) - 9*pow(2, i/2) +1;
    return 8*pow(2, i) - 6*pow(2, i/2) +1;
}

void ShelSort1(int* mas, int len){
    int t = log2(len);
    int s = len;
    for(int i=log2(len); i>=0; i--){
        s = next_H1(s);
        for(int b=0; b < s; b++){
            int j = b+s;
            while(j < len){
                int x = mas[j];
                int k = j - s;
                while(k >= 0 and mas[k] > x){
                    mas[k+s] = mas[k];
                    k = k-s;
                }
                mas[k+s] = x;
                j += s;
            }
        }
        
    }
}

void ShelSort2(int* mas, int len){
    for(int i=log2(len); i>=0; i--){
        int s = next_H2(i);
        for(int b=0; b < s; b++){
            int j = b+s;
            while(j < len){
                int x = mas[j];
                int k = j - s;
                while(k >= 0 and mas[k] > x){
                    mas[k+s] = mas[k];
                    k = k-s;
                }
                mas[k+s] = x;
                j += s;
            }
        }
    }
}

void ShelSort3(int* mas, int len){
    for(int i=log2(len); i>=0; i--){
        int s = next_H3(i);
        for(int b=0; b < s; b++){
            int j = b+s;
            while(j < len){
                int x = mas[j];
                int k = j - s;
                while(k >= 0 and mas[k] > x){
                    mas[k+s] = mas[k];
                    k = k-s;
                }
                mas[k+s] = x;
                j += s;
            }
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
    const int len = 9;
    int mas[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    ShelSort2(mas, len);
    for(int i=0; i<len; i++)
        std::cout << mas[i] << " ";
    std::cout << std::endl;
    std::cout << is_sorted(mas, mas + len) << std::endl;
    std::cout << "size\t\td\tis_sorted\ttime\n";
    for(int size=10000; size<=1000000; size*=10)
        for(int d=10; d<=100000; d*=100){
            char buf[100];
            snprintf(buf, sizeof(buf), "S%dD%d.txt", size, d);
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
                ShelSort2(itermas, size);
                std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = timeEnd - timeStart;
                sumdur += duration.count();
                
            }
                
            std::cout << size << "\t\t" << d << "\t" << is_sorted(itermas, itermas+size) << "\t\t" << (sumdur / 3) << std::endl;

            delete[] mas;
            delete[] itermas;
    }
}