#include "set.hpp"
#include <string>

const int SIZE = 128;


Set::Set(BooleanVector&& vec) : BooleanVector(vec) {}
Set::Set() : BooleanVector(SIZE,0) {}

Set::Set(const char *str) : BooleanVector(SIZE, 0){
    for(const char *i=str; *i!='\0'; i++)
        this->set_value(1, *i);
}

Set::Set(const Set &other) : BooleanVector(other){}

bool Set::includes(unsigned char item) const{
    return BooleanVector::operator[](item);
}

char Set::max() const{
    for(size_t i = SIZE-1; i>=0; i--)
        if (BooleanVector::operator[](i))
            return i;
    return 0;
}

char Set::min() const{
    for(size_t i = 1; i<256; i++)
        if (BooleanVector::operator[](i))
            return i;
    return 0;
}

int Set::weight() const{
    return BooleanVector::getWeight();
}

Set& Set::operator=(const Set &other){
    BooleanVector::operator=(other);
    return *this;
}

bool Set::operator==(const Set &other) const{
    if ((BooleanVector::operator^(other)).getWeight() == 0)
        return true;
    return false;
}

bool Set::operator!=(const Set &other) const{
    return !operator==(other);
}

Set Set::operator|(const Set &other) const{
    return BooleanVector::operator|(other);
}

Set &Set::operator|=(const Set &other) {
    BooleanVector::operator|=(other);
    return *this;
}

Set Set::operator&(const Set &other) const{
    return BooleanVector::operator&(other);
}

Set &Set::operator&=(const Set &other) {
    BooleanVector::operator&=(other);
    return *this;
}

Set Set::operator/(const Set &other) const{
    return BooleanVector::operator^(other&*this);
}

Set &Set::operator/=(const Set &other) {
    BooleanVector::operator^=(other&*this);
    return *this;
}

Set Set::operator~() const{
    return BooleanVector::operator~();
}

Set Set::operator+(char item) const{
    Set tmp = *this;
    tmp.set_value(1, item);
    return tmp;
}

Set &Set::operator+=(char item) {
    BooleanVector::set_value(1, item);
    return *this;
}

Set Set::operator-(char item) const{
    Set tmp = *this;
    tmp.set_value(0, item);
    return tmp;
}

Set &Set::operator-=(char item) {
    BooleanVector::set_value(0, item);
    return *this;
}

std::istream &operator>>(std::istream &cin, Set &set) {
    std::string str;
    cin >> str;
    for(char i : str)
        set += i;
    return cin;
}

std::ostream &operator<<(std::ostream &cout, const Set &set) {
    for(int i=0; i<SIZE; i++){
        if (set.includes(i))
            cout << (char) i;
    }
    return cout;
}
