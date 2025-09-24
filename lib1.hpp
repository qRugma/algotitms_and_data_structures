#pragma once

// Печать массива произвольной длины и типа
template<typename T>
void print(const T& mas, int len);

// Запись следующей переставки, иначе возвращает false
bool nextPerm(int* P, int len);

// Возврат матрицы NxM
int** makeTwoDimMas(int n, int m);

// Возрат квадратной матрицы NxN
template<typename T>
T** makeTwoDimMas(int n);

template<typename T>
void deleteTwoDimMas(T** mas, int n);

#include "lib1.tpp"
