#pragma once

#include <iostream>
#include <stdint.h>
class BooleanVector {

    uint8_t *data_ = nullptr;
    uint32_t numBits_ = 0;

    uint32_t getByteIndex(uint32_t bit) const;
    uint32_t getBitIndex(uint32_t bit) const;
    uint32_t getNumBytes() const;

  public:
    class Component;
    class Component_const;
    BooleanVector();
    BooleanVector(const uint32_t, const bool);
    BooleanVector(const char *);

    ~BooleanVector();

    BooleanVector(const BooleanVector &);
    BooleanVector(BooleanVector &&);

    BooleanVector &operator=(const BooleanVector &);
    BooleanVector &operator=(BooleanVector &&);

    uint32_t getLenght() const;
    uint32_t getWeight() const;
    void swap(BooleanVector&);
    void invert_all();
    void invert(const uint32_t index);
    void set_value(bool value, uint32_t index);
    void set_value_from(bool value, uint32_t index, uint32_t k);
    void set_value_all(bool value);
    Component_const operator[](const uint32_t index) const;
    Component operator[](const uint32_t index);
    BooleanVector operator&(const BooleanVector &) const;
    BooleanVector &operator&=(const BooleanVector &);
    BooleanVector operator|(const BooleanVector &) const;
    BooleanVector &operator|=(const BooleanVector &);
    BooleanVector operator^(const BooleanVector &) const;
    BooleanVector &operator^=(const BooleanVector &);
    BooleanVector operator<<(int value) const;
    BooleanVector &operator<<=(int value);
    BooleanVector operator>>(int value) const;
    BooleanVector &operator>>=(int value);
    BooleanVector operator~() const;
};

std::istream &operator>>(std::istream &cin, BooleanVector::Component &comp);
std::ostream &operator<<(std::ostream &cout, const BooleanVector &vec);
std::istream &operator>>(std::istream &cin, BooleanVector &vec);

class BooleanVector::Component {
    uint8_t *bytePtr_;
    uint32_t bitIndex_;

  public:
    Component(uint8_t *const bytePtr, const uint8_t bitIndex);

    operator bool();
    Component &operator=(const bool value);
};

class BooleanVector::Component_const {
    uint8_t *bytePtr_;
    uint32_t bitIndex_;

  public:
    Component_const(uint8_t *const bytePtr, const uint8_t bitIndex);

    operator bool();
};