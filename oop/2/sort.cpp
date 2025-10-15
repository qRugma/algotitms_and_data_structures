#include <utility>
void heapify(int* mas, int len, int i){
    int maxChild = (mas[2*i+1] < mas[2*i+2]) and !(2*i+2 == len) ? 2*i+2 : 2*i+1;
    if (mas[i] >= mas[maxChild])
        return;
    std::swap(mas[i], mas[maxChild]);
    if(maxChild <= (len-1) / 2)
        heapify(mas, len, maxChild);
}
void PiramSort(int* mas, int len){
    const int sep = (len-1) / 2;
    for(int i = sep; i >= 0; i--)
        heapify(mas, len, i);
    for(int i=len-1; i!=1; i--){
        std::swap(mas[0], mas[i]);
        heapify(mas, i, 0);
    }
    std::swap(mas[0], mas[1]);
}
