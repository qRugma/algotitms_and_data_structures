#include <stdint.h>
#include <iostream>
class BooleanVector{

    uint8_t *data_ = nullptr;
    uint32_t numBits_ = 0;
    class Component;

    uint32_t getByteIndex(uint32_t bit) const;
    uint32_t getBitIndex(uint32_t bit) const;
    uint32_t getNumBytes() const;

    
    public:
    BooleanVector();
    BooleanVector(const uint32_t, const bool);
    BooleanVector(const char*);

    ~BooleanVector();

    BooleanVector(const BooleanVector&);
    BooleanVector(BooleanVector&&);

    BooleanVector& operator=(const BooleanVector&);
    BooleanVector& operator=(BooleanVector&&);
    
    uint32_t getLenght() const;
    uint32_t getWeight() const;
    void swap(BooleanVector);
    friend std::ostream & operator << (std::ostream &cout, const BooleanVector &vec);
    friend std::istream & operator >> (std::istream &cin, BooleanVector &vec);
    void invert_all();
    void invert(const uint32_t index);
    void set_value(const bool value, const uint32_t index);
    void set_value_from(const bool value, const uint32_t index);
    void set_value_all(const bool value);
    Component operator[](const uint32_t index) const;
    BooleanVector operator&(const BooleanVector&) const;
    BooleanVector& operator&=(const BooleanVector&);
    BooleanVector operator|(const BooleanVector&) const;
    BooleanVector& operator|=(const BooleanVector&);
    BooleanVector operator^(const BooleanVector&) const;
    BooleanVector& operator^=(const BooleanVector&);
    BooleanVector operator<<(int value) const;
    BooleanVector& operator<<=(int value);
    BooleanVector operator>>(int value) const;
    BooleanVector& operator>>=(int value);
    BooleanVector operator~() const;
};



class BooleanVector::Component{
    uint8_t *bytePtr_;
    uint32_t bitIndex_;

    public:
    Component(uint8_t* const bytePtr, const uint8_t bitIndex);

    operator bool();
    Component& operator=(const bool value);
};