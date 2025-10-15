#include <iostream>
#include <fstream>
#include <random>
#include <chrono>


void heapify(int* mas, int len, int i){
    //2
    int maxChild = (mas[2*i+1] < mas[2*i+2]) and (2*i+2 < len) ? 2*i+2 : 2*i+1;
    //3
    if (mas[i] >= mas[maxChild])
        return;
    //4
    std::swap(mas[i], mas[maxChild]);
    if(maxChild <= len/2 - 1)
        heapify(mas, len, maxChild);
}

void PiramSort(int* mas, int len){
    const int sep = len/2-1;
    for(int i = sep; i >= 0; i--)
        heapify(mas, len, i);
    for(int i=len-1; i>=0; i--){
        std::swap(mas[0], mas[i]);
        heapify(mas, i, 0);
        // for(int i=0; i<len; i++)
        //     std::cout << mas[i] << " ";
        // std::cout << std::endl;
    }
    std::swap(mas[0], mas[1]);
}

bool is_sorted(int* begin, int* end){
    begin++;
    for(; begin!=end; begin++)
        if(*(begin-1) > *begin)
            return false;
    return true;
}


int main(){
    std::random_device randomDevice;
    std::mt19937_64 generator(randomDevice());
    std::ofstream fout;
    int len = 10;
    int mas[len] = {22, 90, 44, 15, 2, 36, 53, 23, 82, 5};
    PiramSort(mas, len);
    for(int i=0; i<len; i++)
        std::cout << mas[i] << " ";
    std::cout << std::endl;
    std::cout << is_sorted(mas, mas + len) << std::endl;
    std::cout << "size\t\td\tis_sorted\ttime\n";
    for(int size=10000; size<=1000000; size*=10)
        for(int d=10; d<=100000; d*=100){
            char buf[100];
            snprintf(buf, sizeof(buf), "S%dD%d.txt", size, d);
            fout.open(buf);
            std::uniform_int_distribution<int> distribution(-d, d);
            int *mas = new int[size];
            for(int i=0; i<size; i++)
                fout << (mas[i] = distribution(generator)) << " ";
            fout.close();
            double sumdur = 0;
            for(int i = 0; i<3; i++){
                std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
                PiramSort(mas, size);
                std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = timeEnd - timeStart;
                sumdur += duration.count();
            }
                
            std::cout << size << "\t\t" << d << "\t" << is_sorted(mas, mas+size) << "\t\t" << (sumdur / 3) << std::endl;

            delete[] mas;
        }
}