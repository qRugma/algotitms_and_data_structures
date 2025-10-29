#include <cstring>
#include <cassert>

// #include "sort.hpp"

template<typename T>
Vector<T>::Vector(const int capacity){
    capacity_ = capacity;
    data_ = new T[capacity_];
}

template<typename T>
Vector<T>::Vector(T *mas, int len){
    capacity_ = size_ = len;
    data_ = new T[capacity_];
    std::memcpy(data_, mas, size_*sizeof(T));
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T>& l){
    size_ = capacity_ = l.size();
    data_ = new T[capacity_];
    int j = 0;
    for(auto i = l.begin(); i != l.end(); i++)
        data_[j++] = *i;
}

template<typename T>
Vector<T>::Vector(const Vector<T> &other){
    capacity_ = size_ = other.size_;
    data_ = new T[capacity_];
    std::memcpy(data_, other.data_, size_*sizeof(int));
}

template<typename T>
Vector<T>::Vector(Vector<T> &&other){
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template<typename T>
Vector<T>::~Vector(){
    delete[] data_;
}

template<typename T>
int Vector<T>::size() const{
    return size_;
}

template<typename T>
void Vector<T>::swap(Vector<T> &other){
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

template<typename T>
int Vector<T>::find(const T& elem) const{
    for(size_t i=0; i<size_; i++)
        if (data_[i] == elem)
            return i;
    return -1;
}

template<typename T>
std::ostream & operator << (std::ostream &cout, const Vector<T> &vec){
    for (int i=0; i<vec.size_; i++)
        cout << vec.data_[i] << " ";
    return cout;
}

template<typename T>
std::istream & operator >> (std::istream &cin, Vector<T> &vec){
    for (int i=0; i<vec.capacity_; i++)
        cin >> vec.data_[i];
    return cin;
}

template<typename T>
void Vector<T>::sort(){
    PiramSort(data_, size_);
}

template<typename T>
bool Vector<T>::insert(const size_t index, const T &value){
    if ((index < 0) or (size_ < index))
        return false;
    else if (capacity_ < size_ + 1){
        capacity_ += 10;
        T *data = new T[capacity_];
        std::memcpy(data, data_, (index)*sizeof(T));
        data[index] = value;
        std::memcpy(&data[index+1], &data_[index], (size_ - index) * sizeof(T)); 
        delete[] data_;
        data_ = data;
    } else{
        std::memmove(&data_[index+1], &data_[index], (size_ - index)*sizeof(T));
        data_[index] = value;
    }
    size_++;
    return true;
}

template<typename T>
bool Vector<T>::insert(T* iter, const T& value){
    return insert(iter-data_, value);
}

template<typename T>
T Vector<T>::pop(const size_t index){
    assert(size_ > index);
    T poped = data_[index];
    std::memmove(&data_[index], &data_[index+1], (size_ - index)*sizeof(T));
    size_--;
    return poped;
}

template<typename T>
T Vector<T>::pop(T* iter){
    return pop(iter-data_);
}

template<typename T>
void Vector<T>::pop(T* begin, T* end){
    size_t count = end - begin;
    size_t index = begin - data_;
    assert(end <= data_ + size_); assert(data_ <= begin);
    std::memmove(begin, end, (data_ + size_ - end)*sizeof(T));
    size_ -= count;
}

template<typename T>
bool Vector<T>::remove(const T &value){
    bool find = false;
    for(size_t i=0; i < size_; i++){
        data_[i - find] = data_[i];
        if (data_[i] == value)
            find = true;
    }
    size_ -= find;
    return find;
}

template<typename T>
bool Vector<T>::remove_all(const T &value){
    int shift = 0;
    for(size_t i=0; i < size_; i++){
        data_[i - shift] = data_[i];
        if (data_[i] == value)
            shift++;
    }
    size_-= shift;
    return shift;
}

template<typename T>
T Vector<T>::max() const{
    int max=0;
    assert(size_ > 0);
    max = data_[0];
    for(size_t i=1; i<size_; i++)
        max = max < data_[i]? data_[i] : max;
    return max;
}

template<typename T>
T Vector<T>::min() const{
    int min=0;
    assert(size_ > 0);
    min = data_[0];
    for(size_t i=1; i<size_; i++)
        min = min > data_[i]? data_[i] : min;
    return min;
}

template<typename T>
T* Vector<T>::begin(){
    return data_;
}

template<typename T>
T* Vector<T>::end(){
    return &data_[size_];
}

template<typename T>
const T* Vector<T>::begin() const{
    return data_;
}

template<typename T>
const T* Vector<T>::end() const{
    return &data_[size_];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const{
    assert(size_ > index);
    return data_[index];
}

template<typename T>
T& Vector<T>::operator[](size_t index){
    assert(size_ > index);
    return data_[index];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &other){
    if (capacity_ < other.size_){
        delete[] data_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
    }
    size_ = other.size_;
    std::memcpy(data_, other.data_, size_*sizeof(T));
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator+(const T &value) const{
    Vector tmp(size_ + 1);
    std::memcpy(tmp.data_, data_, size_*sizeof(T));
    tmp.size_ = size_+1;
    tmp.data_[size_] = value;
    return tmp;
}

template<typename T>
Vector<T>& Vector<T>::operator+=(const T &value){
    if (size_ == capacity_){
        T* data = new T[capacity_ + 10];
        std::memcpy(data, data_, size_*sizeof(T));
        delete[] data_;
        data_ = data;
    }
    data_[size_++] = value;
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &&other){
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

template<typename T>
Vector<T> Vector<T>::operator+(const Vector &other) const{
    Vector tmp(size_ + other.size_);
    tmp.size_ = size_ + other.size_;
    std::memcpy(tmp.data_, data_, size_*sizeof(T));
    std::memcpy(&tmp.data_[size_], other.data_, other.size_*sizeof(T));
    return tmp;
}

template<typename T>
Vector<T>& Vector<T>::operator+=(const Vector &other){
    if (capacity_ < size_ + other.size_){
        capacity_ = size_ + other.size_;
        T *data = new T[capacity_];
        std::memcpy(data, data_, size_);
        delete[] data_;
        data_ = data;
    }
    std::memcpy(&data_[size_], other.data_, other.size_*sizeof(T));
    size_ += other.size_;
    return *this;
}

template<typename T>
bool Vector<T>::operator==(const Vector &other) const{
    if (size_ != other.size_)
        return false;
    for(size_t i=0; i<size_; i++){
        if(data_[i] != other.data_[i])
            return false;
    }
    return true;
}

template<typename T>
bool Vector<T>::operator!=(const Vector &other) const{
    return !(*this == other);
}
