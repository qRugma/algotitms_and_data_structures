#include <iostream>
#include <cstring>
#include <cassert>

#include "sort.hpp"
#include "vector.hpp"

Vector::Vector(const int capacity){
    capacity_ = capacity;
    data_ = new int[capacity_];
}

Vector::Vector(int* mas, int len){
    capacity_ = size_ = len;
    data_ = new int[capacity_];
    std::memcpy(data_, mas, size_*sizeof(int));
}

Vector::Vector(const Vector &other){
    capacity_ = size_ = other.size_;
    data_ = new int[capacity_];
    std::memcpy(data_, other.data_, size_*sizeof(int));
}

Vector::Vector(const std::initializer_list<int>& l){
    size_ = capacity_ = l.size();
    data_ = new int[capacity_];
    int j = 0;
    for(auto i = l.begin(); i != l.end(); i++)
        data_[j++] = *i;
}

Vector::Vector(Vector &&other){
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

Vector::~Vector(){
    delete[] data_;
}


int Vector::size() const{
    return size_;
}

void Vector::swap(Vector &other){
    int size = other.size_;
    int capacity = other.capacity_;
    int *data = other.data_;
    other.size_ = size_;
    other.capacity_ = capacity_;
    other.data_ = data_;
    size_ = size;
    capacity_ = capacity;
    data_ = data;
}

int Vector::find(const int elem) const{
    for(int i=0; i<size_; i++)
        if (data_[i] == elem)
            return i;
    return -1;
}

std::ostream & operator << (std::ostream &cout, const Vector &vec){
    for (int i=0; i<vec.size_; i++)
        cout << vec.data_[i] << " ";
    return cout;
}

std::istream & operator >> (std::istream &cin, Vector &vec){
    for (int i=0; i<vec.capacity_; i++)
        cin >> vec.data_[i];
    return cin;
}

void Vector::sort(){
    PiramSort(data_, size_);
}

bool Vector::insert(size_t index, const int value){
    if ((index < 0) or (size_ < index))
        return false;
    else if (capacity_ < size_ + 1){
        capacity_ += 10;
        int *data = new int[capacity_];
        std::memcpy(data, data_, (index)*sizeof(int));
        data[index] = value;
        std::memcpy(&data[index+1], &data_[index], (size_ - index) * sizeof(int)); 
        delete[] data_;
        data_ = data;
    } else{
        std::memmove(&data_[index+1], &data_[index], (size_ - index)*sizeof(int));
        data_[index] = value;
    }
    size_++;
    return true;
}

bool Vector::insert(int* iter, int value){
    return insert(iter-data_, value);
}

bool Vector::pop(const size_t index){
    if (size_ < index)
        return false;
    std::memmove(&data_[index], &data_[index+1], (size_ - index)*sizeof(int));
    size_--;
    return true;
}

bool Vector::pop(int* iter){
    return pop(iter-data_);
}

void Vector::pop(int* begin, int* end){
    size_t count = end - begin;
    size_t index = begin - data_;
    assert(end <= data_ + size_); assert(data_ <= begin);
    std::memmove(begin, end, (data_ + size_ - end)*sizeof(int));
    size_ -= count;
}



bool Vector::remove(const int value){
    bool find = false;
    for(size_t i=0; i < size_; i++){
        data_[i - find] = data_[i];
        if (data_[i] == value)
            find = true;
    }
    size_ -= find;
    return find;
}

bool Vector::remove_all(const int value){
    int shift = 0;
    for(size_t i=0; i < size_; i++){
        data_[i - shift] = data_[i];
        if (data_[i] == value)
            shift++;
    }
    size_ -= shift;
    return shift;
}

int Vector::max() const{
    int max=0;
    assert(size_ > 0);
    max = data_[0];
    for(size_t i=1; i<size_; i++)
        max = max < data_[i]? data_[i] : max;
    return max;
}

int Vector::min() const{
    int min=0;
    assert(size_ > 0);
    min = data_[0];
    for(size_t i=1; i<size_; i++)
        min = min > data_[i]? data_[i] : min;
    return min;
}

int* Vector::begin(){
    return data_;
}

int* Vector::end(){
    return &data_[size_];
}

const int* Vector::begin() const{
    return data_;
}

const int* Vector::end() const{
    return &data_[size_];
}

const int& Vector::operator[](size_t index) const{
    assert(size_ > index);
    return data_[index];
}

int& Vector::operator[](size_t index){
    assert(size_ > index);
    return data_[index];
}

Vector& Vector::operator=(const Vector &other){
    if (capacity_ < other.size_){
        delete[] data_;
        capacity_ = other.capacity_;
        data_ = new int[capacity_];
    }
    size_ = other.size_;
    std::memcpy(data_, other.data_, size_*sizeof(int));
    return *this;
}

Vector Vector::operator+(int value) const{
    Vector tmp(size_ + 1);
    std::memcpy(tmp.data_, data_, size_*sizeof(int));
    tmp.size_ = size_+1;
    tmp.data_[size_] = value;
    return tmp;
}

Vector& Vector::operator+=(int value){
    if (size_ == capacity_){
        int* data = new int[capacity_ + 10];
        std::memcpy(data, data_, size_*sizeof(int));
        delete[] data_;
        data_ = data;
    }
    data_[size_++] = value;
    return *this;
}

Vector& Vector::operator=(Vector &&other){
    if(this != &other){
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

Vector Vector::operator+(const Vector &other) const{
    Vector tmp(size_ + other.size_);
    tmp.size_ = size_ + other.size_;
    std::memcpy(tmp.data_, data_, size_*sizeof(int));
    std::memcpy(&tmp.data_[size_], other.data_, other.size_*sizeof(int));
    return tmp;
}

Vector& Vector::operator+=(const Vector &other){
    if (capacity_ < size_ + other.size_){
        capacity_ = size_ + other.size_;
        int *data = new int[capacity_];
        std::memcpy(data, data_, size_);
        delete[] data_;
        data_ = data;
    }
    std::memcpy(&data_[size_], other.data_, other.size_*sizeof(int));
    size_ += other.size_;
    return *this;
}

bool Vector::operator==(const Vector &other) const{
    if (size_ != other.size_)
        return false;
    for(int i=0; i<size_; i++){
        if(data_[i] != other.data_[i])
            return false;
    }
    return true;
}

bool Vector::operator!=(const Vector &other) const{
    return !(*this == other);
}
