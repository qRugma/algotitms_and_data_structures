#include "booleanvector.hpp"
#include <iostream>
#include <string>

#pragma once

class Set :  BooleanVector {

    Set(BooleanVector&&);
  public:

    Set();
    Set(const char* str);
    Set(const Set&);

    bool includes(unsigned char) const;
    char max() const;
    char min() const;
    int weight() const;

    Set& operator=(const Set&);

    bool operator==(const Set&) const;
    bool operator!=(const Set&) const;
    Set operator|(const Set&) const;
    Set& operator|=(const Set&);
    Set operator&(const Set&) const;
    Set& operator&=(const Set&);
    Set operator/(const Set&) const;
    Set& operator/=(const Set&);
    Set operator~() const;
    Set operator+(char) const;
    Set& operator+=(char);
    Set operator-(char) const;
    Set& operator-=(char);

    virtual std::string input();
    virtual std::string output() const;
};

std::istream& operator>>(std::istream &cin, Set& set);
std::ostream& operator<<(std::ostream &cout, const Set& set);