#include <cassert>
#include <utility>
#include "booleanmatrix.hpp"

BooleanMatrix::BooleanMatrix(): data_(), rows_(0), columns_(0) {}

BooleanMatrix::BooleanMatrix(const char* data[], size_t rows): data_(rows), rows_(rows) {
    for(size_t i=0; i<rows_; i++)
        data_[i] = BooleanVector(data[i]);
    columns_ = data_[0].getLenght();
}

BooleanMatrix::BooleanMatrix(size_t columns, size_t rows)
: data_(rows), rows_(rows), columns_(columns) {
    for(size_t i=0; i<rows_; i++)
        data_[i] = BooleanVector(columns_, 0);
}

int BooleanMatrix::columns() const{
    return columns_;
}
int BooleanMatrix::rows() const{
    return rows_;
}

void BooleanMatrix::swap(BooleanMatrix &other){
    Vector<BooleanVector> data = data_;
    size_t columns = columns_, rows = rows_;
    data_ = other.data_;
    columns_ = other.columns_;
    rows_ = other.rows_;
    other.data_ = data;
    other.columns_ = columns;
    other.rows_ = rows;
}

int BooleanMatrix::weight() const{
    int sum = 0;
    for(size_t i=0; i < rows_; i++)
        sum += data_[i].getWeight();
    return sum;
}

int BooleanMatrix::weight(size_t row) const{
    assert(row < rows_);
    return data_[row].getWeight();
}

BooleanVector BooleanMatrix::conjunction() const{
    BooleanVector result = data_[0];
    for(size_t i=1; i<rows_; i++)
        result &= data_[i];
    return result;
}

BooleanVector BooleanMatrix::disjunction() const{
    BooleanVector result = data_[0];
    for(size_t i=1; i<rows_; i++)
        result |= data_[i];
    return result;
}

void BooleanMatrix::invert(size_t row, size_t column){
    assert(row < rows_); assert(column < columns_);
    data_[row].invert(column);
}

void BooleanMatrix::invert_k(size_t row, size_t column, size_t k){
    assert(row < rows_); assert(column + k <= columns_);
    for(size_t i=column; i<column+k; i++)
        data_[row].invert(i);
}

void BooleanMatrix::set(size_t row, size_t column, bool value){
    assert(row < rows_); assert(column < columns_);
    data_[row].set_value(value, column);    
}

void BooleanMatrix::set_k(size_t row, size_t column, bool value, size_t k){
    assert(row < rows_); assert(column + k <= columns_);
    data_[row].set_value_from(value, column, k);
}

BooleanVector& BooleanMatrix::operator[](size_t index){
    assert(index < rows_);
    return data_[index];
}

const BooleanVector& BooleanMatrix::operator[](size_t index) const{
    assert(index < rows_);
    return data_[index];
}

BooleanMatrix BooleanMatrix::operator&(const BooleanMatrix& other) const{
    assert(rows_ == other.rows_); assert(columns_ == other.columns_);
    BooleanMatrix tmp = *this;
    for(size_t i=0; i < rows_; i++)
        tmp.data_[i] = data_[i] & other.data_[i];
    return tmp;
}

BooleanMatrix& BooleanMatrix::operator&=(const BooleanMatrix& other){
    assert(rows_ == other.rows_); assert(columns_ == other.columns_);
    for(size_t i=0; i < rows_; i++)
        data_[i] &= other.data_[i];
    return *this;
}

BooleanMatrix BooleanMatrix::operator|(const BooleanMatrix& other) const{
    assert(rows_ == other.rows_); assert(columns_ == other.columns_);
    BooleanMatrix tmp = *this;
    for(size_t i=0; i < rows_; i++)
        tmp.data_[i] = data_[i] | other.data_[i];
    return tmp;
}

BooleanMatrix& BooleanMatrix::operator|=(const BooleanMatrix& other){
    assert(rows_ == other.rows_); assert(columns_ == other.columns_);
    for(size_t i=0; i < rows_; i++)
        data_[i] |= other.data_[i];
    return *this;
}

BooleanMatrix BooleanMatrix::operator^(const BooleanMatrix& other) const{
    assert(rows_ == other.rows_); assert(columns_ == other.columns_);
    BooleanMatrix tmp = *this;
    for(size_t i=0; i < rows_; i++)
        tmp.data_[i] = data_[i] ^ other.data_[i];
    return tmp;
}

BooleanMatrix& BooleanMatrix::operator^=(const BooleanMatrix& other){
    assert(rows_ == other.rows_); assert(columns_ == other.columns_);
    for(size_t i=0; i < rows_; i++)
        data_[i] ^= other.data_[i];
    return *this;
}

BooleanMatrix BooleanMatrix::operator~() const{
    BooleanMatrix tmp = *this;
    for(size_t i=0; i < rows_; i++)
        tmp.data_[i].invert_all();
    return tmp;
}

std::ostream & operator << (std::ostream &cout, const BooleanMatrix &mat){
    for(size_t i=0; i<mat.rows(); i++)
        cout << mat[i] << std::endl;
    return cout;
}
std::istream & operator >> (std::istream &cin, BooleanMatrix &mat){
    

    return cin;
}

