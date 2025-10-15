#include <iostream>
#include <cstring>
#include <cassert>
#include <initializer_list>
#include "sort.cpp"

template<typename T>
class Vector {
    int size_ = 0;
    int capacity_ = 0;
    T* data_ = nullptr;

    
    public:
    Vector(int capacity=0);
    
    Vector(T* mas, int len);

    Vector(const std::initializer_list<T>&);
    
    Vector(Vector &&vec);

    ~Vector();
    
    int size() const;

    void swap(Vector &other);

    int find(T& elem) const;

    template<typename I>
    friend std::ostream & operator << (std::ostream &cout, const Vector<I> &vec);
    template<typename I>
    friend std::istream & operator >> (std::istream &cin, Vector<I> &vec);

    void sort();

    bool insert(const size_t index, const T& value);
    T pop(const size_t index);
    bool remove(const T &value);
    bool remove_all(const T &value);
    T max() const;
    T min() const;

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

    T& operator[](int index);
    const T& operator[](int index) const;
    Vector& operator=(const Vector &other);
    Vector operator+(const T &value) const;
    Vector& operator+=(const T &value);
    Vector& operator=(Vector &&other);
    Vector operator+(const Vector &other) const;
    Vector& operator+=(const Vector &other);
    bool operator==(const Vector &other) const;
    bool operator!=(const Vector &other) const;

};


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
Vector<T>::Vector(Vector<T> &&vec){
    size_ = vec.size_;
    capacity_ = vec.capacity_;
    data_ = vec.data_;
    vec.data_ = nullptr;
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
int Vector<T>::find(T& elem) const{
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
        std::memcpy(&data[index+1], &data_[index], (size_ - index) * sizeof(TMP_MAX)); 
        delete[] data_;
        data_ = data;
    } else
        std::memmove(&data_[index+1], &data_[index], (size_ - index)*sizeof(T));
    size_++;
    return true;
}

template<typename T>
T Vector<T>::pop(const size_t index){
    assert(index >= 0); assert(size_ > index);
    T poped = data_[index];
    std::memmove(&data_[index], &data_[index+1], (size_ - index)*sizeof(T));
    size_--;
    return poped;
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
    assert(size_ != 0);
    max = data_[0];
    for(size_t i=1; i<size_; i++)
        max = max < data_[i]? data_[i] : max;
    return max;
}

template<typename T>
T Vector<T>::min() const{
    int min=0;
    assert(size_ != 0);
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
const T& Vector<T>::operator[](int index) const{
    assert(index >= 0); assert(size_ > index);
    return data_[index];
}

template<typename T>
T& Vector<T>::operator[](int index){
    assert(index >= 0); assert(size_ > index);
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
