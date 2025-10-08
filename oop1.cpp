#include <iostream>
#include <cmath>
#include "oop1.hpp"

FreeVector::FreeVector(double x, double y, double z){
    x_=x;
    y_=y;
    z_=z;
}

double FreeVector::getX() const{
    return x_;
}

double FreeVector::getY() const{
    return y_;
}

double FreeVector::getZ() const{
    return z_;
}

void FreeVector::newX(double x){
    x_ = x;
}
void FreeVector::newY(double y){
    y_ = y;
}
void FreeVector::newZ(double z){
    z_ = z;
}

void FreeVector::newCoors(double x, double y, double z){
    x_=x;
    y_=y;
    z_=z;
}

std::ostream & operator << (std::ostream &cout, const FreeVector &vec){
    cout << vec.x_ << " " << vec.y_ << " " << vec.z_;
    return cout;
}


std::istream & operator >> (std::istream &cin, FreeVector &vec){
    cin >> vec.x_ >> vec.y_ >> vec.z_;
    return cin;
}

double FreeVector::lenght() const{
    return sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
}

FreeVector FreeVector::orthonormal() const{
    FreeVector tmp;
    double len = lenght();
    tmp.x_ = x_ / len;
    tmp.y_ = y_ / len;
    tmp.z_ = z_ / len;
    return tmp;
}

FreeVector FreeVector::operator+(const FreeVector &rhs) const{
    FreeVector tmp = {rhs.x_ + x_, rhs.y_ + y_, rhs.z_ + z_};
    return tmp;
}

FreeVector FreeVector::operator+=(const FreeVector &rhs) const{
    return *this + rhs;
}

FreeVector FreeVector::operator-(const FreeVector &rhs) const{
    FreeVector tmp = {rhs.x_ - x_, rhs.y_ - y_, rhs.z_ - z_};
    return tmp;
}

FreeVector FreeVector::operator-=(const FreeVector &rhs) const{
    return *this - rhs;
}


FreeVector FreeVector::operator*(const double num) const{
    FreeVector tmp = {x_*num, y_*num, z_*num};
    return tmp;
}

FreeVector FreeVector::operator*=(const double num) const{
    return *this * num;
}


bool FreeVector::operator==(const FreeVector &rhs) const{
    if(
        x_ == rhs.x_ and
        y_ == rhs.y_ and
        z_ == rhs.z_
    ) return true;
    return false;
}

bool FreeVector::operator!=(const FreeVector &rhs) const{
    return !(*this == rhs);
}


double FreeVector::scalar(const FreeVector &rhs) const{
    return rhs.x_ * x_ + rhs.y_ * y_ + rhs.z_ * z_;
}

FreeVector FreeVector::vectorProduct(const FreeVector &rhs) const{
    FreeVector tmp;
    tmp.x_ = y_*rhs.z_ - z_*rhs.y_;
    tmp.y_ = z_*rhs.x_ - x_*rhs.z_;
    tmp.z_ = x_*rhs.y_ - y_*rhs.x_;
    return tmp;
}

double FreeVector::tripleProduct(const FreeVector &mhs, const FreeVector &rhs) const {
    return scalar(mhs.vectorProduct(rhs));
}

FreeVector FreeVector::doubleVectorProduct(const FreeVector &mhs, const FreeVector &rhs) const {
    return this->vectorProduct(mhs.vectorProduct(rhs));
}
