#include <iostream>
#include <format>
#include <cmath>
#include <algorithm>
#include <array>
#include "oop1.hpp"


void FreeVector::calcRadius(){
        for(int i=0; i<dim; i++){
        radius[i] = end[i] - start[i]; 
        }
    }

    //first three is start point, next is end point
FreeVector::FreeVector(double xS, double yS, double zS,
                       double xE, double yE, double zE){
    start[0] = xS;
    start[1] = yS;
    start[2] = zS;

    end[0] = xE;
    end[1] = yE;
    end[2] = zE;
    calcRadius();
}

    // size start and end need >= 3
FreeVector::FreeVector(double *Start, double *End){
    for(int i=0; i<dim; i++){
        start[i] = Start[i];
        end[i] = End[i];
    }
    calcRadius();
}

const double* FreeVector::getStart(){
    return start.begin();
}

const double* FreeVector::getEnd(){
    return end.begin();
}

const double* FreeVector::getRadius(){
    return radius.begin();
}

//first three is start point, next is end point
void FreeVector::newCoors(double *Start, double *End){
    for (int i=0; i<dim; i++){
        start[i] = Start[i];
        end[i] = End[i];
    }
    calcRadius();
}

void FreeVector::newStart(double xS, double yS, double zS){
    start[0] = xS;
    start[1] = yS;
    start[2] = zS;
}

void FreeVector::newEnd(double xE, double yE, double zE){
    end[0] = xE;
    end[1] = yE;
    end[2] = zE;
}


void FreeVector::print(){
    std::cout << "start:\t" << std::format(
        "x={}, y={}, z={}", start[0], start[1], start[2]
    ) << std::endl;
    std::cout << "end:\t" << std::format(
        "x={}, y={}, z={}", end[0], end[1], end[2]
    ) << std::endl;
    std::cout << "radius:\t" << std::format(
        "x={}, y={}, z={}", radius[0], radius[1], radius[2]
    ) << std::endl;
}

// size start need >= 3
void FreeVector::newStart(const double* Start){
    for(int i=0; i<dim; i++){
        start[i] = Start[i];
    }
    calcRadius();
}

// size end need >= 3
void FreeVector::newEnd(const double* End){
    for(int i=0; i<dim; i++)
        end[i] = End[i];
    calcRadius();
}

// size start and end need >= 3
void FreeVector::newCoors(const double* Start, const double* End){
    for(int i=0; i<dim; i++){
        start[i] = Start[i];
        end[i] = End[i];
    }
    calcRadius();
}

double FreeVector::lenght() const{
    int sum = 0;
    for(int i=0; i<dim; i++)
        sum += pow(radius[i], 2);
    return sqrt(sum);
}

FreeVector FreeVector::orthonormal(){
    FreeVector tmp;
    tmp.start = start;
    double len = lenght();
    for(int i=0; i<dim; i++)
        tmp.end[i] = start[i] + (radius[i] / len);
    tmp.calcRadius();
    return tmp;
}

FreeVector FreeVector::operator+(const FreeVector &rhs) const{
    FreeVector tmp;
    
    for(int i=0; i<dim; i++){
        tmp.start[i] = start[i];
        tmp.end[i] = end[i] + rhs.radius[i];
    }

    tmp.calcRadius();
    return tmp;
}

FreeVector FreeVector::operator-(const FreeVector &rhs) const{
    FreeVector tmp;
    
    
    for(int i=0; i<dim; i++){
        tmp.start[i] = start[i];
        tmp.end[i] = end[i] - rhs.radius[i];
    }


    tmp.calcRadius();
    return tmp;
}

FreeVector FreeVector::operator*(const double num) const{
    FreeVector tmp;

    for(int i=0; i<dim; i++){
        tmp.start[i] = start[i];
        tmp.end[i] = start[i] + radius[i] * num;
    }
    tmp.calcRadius();
    return tmp;
}

bool FreeVector::operator==(const FreeVector &rhs) const{
    if(
        radius[0] == rhs.radius[0] and
        radius[1] == rhs.radius[1] and
        radius[2] == rhs.radius[2]
    ) return true;
    return false;
}

double FreeVector::scalar(const FreeVector &rhs) const{
    double sum=0;
    for(int i=0; i<dim; i++)
        sum += radius[i] * rhs.radius[i];
    return sum / (lenght() * rhs.lenght());
}

FreeVector FreeVector::vectorProduct(const FreeVector &rhs) const{
    FreeVector tmp;
    // dont work for another dim
    for(int i=0, l=1, r=dim-1; i<dim; i++, l++, r++, l%=dim, r%=dim){
        tmp.start[i] = start[i];
        tmp.end[i] = radius[l]*rhs.radius[r] - radius[r]*rhs.radius[l] + start[i];
    }
    tmp.calcRadius();
    return tmp;
}

double FreeVector::tripleProduct(const FreeVector &mhs, const FreeVector &rhs) const {
    return scalar(mhs.vectorProduct(rhs));
}

FreeVector FreeVector::doubleVectorProduct(const FreeVector &mhs, const FreeVector &rhs) const {
    return this->vectorProduct(mhs.vectorProduct(rhs));
}
