#pragma once

template<typename T>
void swap(T&, T&);

//Печать массива произвольной длины и типа
template<typename T>
void print(const T& mas, int len);

template<typename T>
T min(const T&, const T&);

// Запись следующей переставки, иначе возвращает false
bool nextPerm(int *P, int len);

//Возврат матрицы NxM
int** makeTwoDimMas(int n, int m);

//Возрат квадратной матрицы NxN
int** makeTwoDimMas(int n);



#include "lib1.tpp"
