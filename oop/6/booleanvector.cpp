#include <string>
#include <cassert>

#include "booleanvector.hpp"

inline uint32_t BooleanVector::getByteIndex(uint32_t bit) const{
    return bit / (8*sizeof(uint8_t));
}
inline uint32_t BooleanVector::getBitIndex(uint32_t bit) const{
    return bit % (8*sizeof(uint8_t));
}

inline uint32_t BooleanVector::getNumBytes() const{
    uint32_t numBytes = numBits_ / (8 * sizeof(uint8_t));
    if (numBits_ % (8*sizeof(uint8_t)) > 0)
        numBytes += 1;
    return numBytes;
}


BooleanVector::BooleanVector(): data_(nullptr), numBits_(0){}

BooleanVector::BooleanVector(const uint32_t numBits, const bool initialValue)
    : numBits_(numBits){
    uint32_t numBytes = getNumBytes();
    data_ = new uint8_t[numBytes];

    uint8_t localInitialValue = initialValue ? 255 : 0;

    for(uint32_t byteIndex = 0; byteIndex < numBytes; byteIndex++)
        data_[byteIndex] = localInitialValue;
}

BooleanVector::BooleanVector(const char* value){
    for(const char* i = value; *i!='\0';i++)
        numBits_++;
    uint32_t numBytes = getNumBytes();

    data_ = new uint8_t[numBytes];
    
    for(size_t i=0; i < numBytes; i++)
        data_[i] = 0;

    for(size_t bit=0; bit < numBits_; bit++){
        if (value[bit] == '1'){
            uint32_t byteIndex = getByteIndex(bit);
            uint32_t bitIndex = getBitIndex(bit);
            data_[byteIndex] |= (1 << bitIndex);
        }
    }
}

BooleanVector::~BooleanVector(){
    delete[] data_;
}

BooleanVector::BooleanVector(const BooleanVector& other){
    numBits_ = other.numBits_;
    uint32_t numBytes = getNumBytes();
    data_ = new uint8_t[numBytes];
    for(uint32_t byte=0; byte<numBytes; byte++)
        data_[byte] = other.data_[byte];
}
BooleanVector::BooleanVector(BooleanVector&& other){
    numBits_ = other.numBits_;
    other.numBits_ = 0;
    data_ = other.data_;
    other.data_ = nullptr;
}

BooleanVector& BooleanVector::operator=(const BooleanVector& other){
    if (this == &other)
        return *this;    
    delete[] data_;
    numBits_ = other.numBits_;
    uint32_t numBytes = getNumBytes();
    data_ = new uint8_t[numBytes];
    for(uint32_t byte=0; byte<numBytes; byte++)
        data_[byte] = other.data_[byte];
    return *this;
}
BooleanVector& BooleanVector::operator=(BooleanVector&& other){
    delete[] data_;
    numBits_ = other.numBits_;
    other.numBits_ = 0;
    data_ = other.data_;
    other.data_ = nullptr;
    return *this;
}

uint32_t BooleanVector::getLenght() const{
    return numBits_;
}

uint32_t BooleanVector::getWeight() const{
    uint32_t weight = 0;

    for(uint32_t bit=0; bit < numBits_; bit++){
        uint32_t byteIndex = getByteIndex(bit);
        uint32_t bitIndex = getBitIndex(bit);
    
        if (data_[byteIndex] & (1 << bitIndex))
            weight++;
    }
    return weight;
}

void BooleanVector::swap(BooleanVector other){
    uint8_t *data = data_;
    uint32_t numBits = numBits_;
    data_ = other.data_;
    numBits_ = other.numBits_;
    other.data_ = data;
    other.numBits_ = numBits;
}

std::ostream & operator << (std::ostream &cout, const BooleanVector &vec){
    for(uint32_t bit=0; bit < vec.getLenght(); bit++){
        cout << vec[bit];
    }
    return cout;
}

std::istream & operator >> (std::istream &cin, BooleanVector &vec){
    std::string str;
    cin >> str;
    vec = str.c_str();
    return cin;
}

void BooleanVector::invert_all(){
    for(int byte=0; byte<getNumBytes(); byte++)
        data_[byte] = ~data_[byte];
}

void BooleanVector::invert(const uint32_t index){
    uint32_t byteIndex = getByteIndex(index);
    uint32_t bitIndex = getBitIndex(index);
    data_[byteIndex] ^= (1 << bitIndex);
}

void BooleanVector::set_value(const bool value, const uint32_t index){
    uint32_t byteIndex = getByteIndex(index);
    uint32_t bitIndex = getBitIndex(index);
    if(value)
        data_[byteIndex] |= (1 << bitIndex);
    else
        data_[byteIndex] &= ~(1 << bitIndex);
}


void BooleanVector::set_value_from(const bool value, const uint32_t index, const uint32_t k){
    for(uint32_t bit=index; (bit < numBits_) and (bit < (index + k)); bit++)
        set_value(value, bit);
}

void BooleanVector::set_value_all(const bool value){
    uint32_t numBytes = getNumBytes();
    uint8_t elem = 0;
    if(value)
        elem = 255;
    for(uint32_t byte=0; byte < numBytes; byte++)
        data_[byte] = elem;
}

BooleanVector::Component_const BooleanVector::operator[](const uint32_t index) const{
    uint32_t byteIndex = getByteIndex(index);
    uint32_t bitIndex = getBitIndex(index);

    return BooleanVector::Component_const(&data_[byteIndex], bitIndex);
}

BooleanVector::Component BooleanVector::operator[](const uint32_t index){
    uint32_t byteIndex = getByteIndex(index);
    uint32_t bitIndex = getBitIndex(index);

    return BooleanVector::Component(&data_[byteIndex], bitIndex);
}

BooleanVector BooleanVector::operator&(const BooleanVector& other) const{
    assert(numBits_ == other.numBits_);
    BooleanVector tmp = *this;
    uint32_t numBytes = getNumBytes();
    for(uint32_t byte=0; byte<numBytes; byte++)
        tmp.data_[byte] &= other.data_[byte];
    return tmp;
}

BooleanVector& BooleanVector::operator&=(const BooleanVector& other){
    assert(numBits_ == other.numBits_);
    uint32_t numBytes = getNumBytes();
    for(uint32_t byte=0; byte<numBytes; byte++)
        data_[byte] &= other.data_[byte];
    return *this;
}

BooleanVector BooleanVector::operator|(const BooleanVector& other) const{
    assert(numBits_ == other.numBits_);
    BooleanVector tmp = *this;
    uint32_t numBytes = getNumBytes();
    for(uint32_t byte=0; byte<numBytes; byte++)
        tmp.data_[byte] |= other.data_[byte];
    return tmp;
}

BooleanVector& BooleanVector::operator|=(const BooleanVector& other){
    assert(numBits_ == other.numBits_);
    uint32_t numBytes = getNumBytes();
    for(uint32_t byte=0; byte<numBytes; byte++)
        data_[byte] |= other.data_[byte];
    return *this;
}

BooleanVector BooleanVector::operator^(const BooleanVector& other) const{
    assert(numBits_ == other.numBits_);
    BooleanVector tmp = *this;
    uint32_t numBytes = getNumBytes();
    for(uint32_t byte=0; byte<numBytes; byte++)
        tmp.data_[byte] ^= other.data_[byte];
    return tmp;
}

BooleanVector& BooleanVector::operator^=(const BooleanVector& other){
    assert(numBits_ == other.numBits_);
    uint32_t numBytes = getNumBytes();
    for(uint32_t byte=0; byte<numBytes; byte++)
        data_[byte] ^= other.data_[byte];
    return *this;
}

BooleanVector BooleanVector::operator<<(int value) const{
    BooleanVector tmp = *this;
    for(uint32_t bit=0; bit+value<numBits_; bit++)
        tmp[bit] = (bool) tmp[bit+value];
    tmp.set_value_from(0, numBits_-value, value);
    return tmp;
}

BooleanVector& BooleanVector::operator<<=(int value){
    for(uint32_t bit=0; bit+value<numBits_; bit++)
        (*this)[bit] = (bool) (*this)[bit+value];
    set_value_from(0, numBits_-value, value);
    return *this;
}

BooleanVector BooleanVector::operator>>(int value) const{
    BooleanVector tmp = *this;
    for(uint32_t bit=numBits_; bit>value; bit--){
        tmp[bit] = (bool) tmp[bit-value];
    }
    for(uint32_t bit=0; bit < value; bit++){
        tmp[bit] = 0;
    }
    tmp.set_value_from(0, 0, value);
    return tmp;
}

BooleanVector& BooleanVector::operator>>=(int value){
    for(uint32_t bit=numBits_; bit>value; bit--){
        (*this)[bit] = (bool) (*this)[bit-value];
    }
    for(uint32_t bit=0; bit < value; bit++){
        (*this)[bit] = 0;
    }
    set_value_from(0, 0, value);
    return *this;
}

BooleanVector BooleanVector::operator~() const{
    BooleanVector tmp = *this;
    uint32_t numBytes = getNumBytes();
    for(uint32_t byte=0; byte<numBytes; byte++)
        tmp.data_[byte] = ~tmp.data_[byte];
    return tmp;
}

BooleanVector::Component::Component(uint8_t* const bytePtr, const uint8_t bitIndex)
 : bytePtr_(bytePtr), bitIndex_(bitIndex) {}

BooleanVector::Component::operator bool(){
    return *bytePtr_ & (1 << bitIndex_);
}

BooleanVector::Component& BooleanVector::Component::operator=(const bool value){
    uint8_t mask = 1 << bitIndex_;
    if (value)
        *bytePtr_ |= mask;
    else 
        *bytePtr_ &= ~mask;
    return *this;
}

BooleanVector::Component_const::Component_const(uint8_t* const bytePtr, const uint8_t bitIndex)
 : bytePtr_(bytePtr), bitIndex_(bitIndex) {}

BooleanVector::Component_const::operator bool(){
    return *bytePtr_ & (1 << bitIndex_);
}

void BooleanVector::input(){
    std::cin >> *this;
}

void BooleanVector::output() const{
    std::cout << *this;
}
