#include <iostream>
#include <cmath>
#include "oop1.hpp"

FreeVector::FreeVector(const double& x, const double& y, const double& z){
    x_=x;
    y_=y;
    z_=z;
}

const double& FreeVector::getX(){
    return x_;
}

const double& FreeVector::getY(){
    return y_;
}

const double& FreeVector::getZ(){
    return z_;
}

//first three is start point, next is end point
void FreeVector::newCoors(const double& x, const double& y, const double& z){
    x_=x;
    y_=y;
    z_=z;
}

std::ostream & operator << (std::ostream &cout, FreeVector vec){
    cout << vec.x_ << " " << vec.y_ << " " << vec.z_;
    return cout;
}


std::istream & operator >> (std::istream &cin, FreeVector vec){
    cin >> vec.x_ >> vec.y_ >> vec.z_;
    return cin;
}

double FreeVector::lenght() const{
    return sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
}

FreeVector FreeVector::orthonormal(){
    FreeVector tmp;
    double len = lenght();
    tmp.x_ = x_ / len;
    tmp.y_ = y_ / len;
    tmp.z_ = z_ / len;
    return tmp;
}

FreeVector FreeVector::operator+(const FreeVector &rhs) const{
    FreeVector tmp = {rhs.x_ + x_, rhs.z_ + y_, rhs.z_ + z_};
    return tmp;
}

FreeVector FreeVector::operator-(const FreeVector &rhs) const{
    FreeVector tmp = {rhs.x_ - x_, rhs.z_ - y_, rhs.z_ - z_};
    return tmp;

}

FreeVector FreeVector::operator*(const double num) const{
    FreeVector tmp = {x_*num, y_*num, z_*num};
    return tmp;
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
    double sum = rhs.x_ * x_ + rhs.y_ * y_ + rhs.z_ * z_;
    return sum / (lenght() * rhs.lenght());
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
