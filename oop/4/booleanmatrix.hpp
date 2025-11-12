#include "vector.tpp"
#include "booleanvector.hpp"

class BooleanMatrix{
    Vector<BooleanVector> data_;
    size_t columns_, rows_;
    BooleanMatrix();
    BooleanMatrix(char*[], size_t rows);
    ~BooleanMatrix();
    int columns() const;
    int rows() const;
    void swap(BooleanMatrix);


    int weight() const;
    int weight(int row) const;
    BooleanVector conjunction() const;
    BooleanVector disjunction() const;
    void invert(int row, int column);
    void invert_k(int row, int column, int k);
    void set(int row, int column, int value);
    void set_k(int row, int column, int value, int k);

    BooleanMatrix& operator=(const BooleanMatrix&);
    BooleanMatrix& operator=(const BooleanMatrix&&);
    BooleanMatrix& operator[](size_t index);
    BooleanMatrix operator&(const BooleanMatrix&) const;
    BooleanMatrix& operator&=(const BooleanMatrix&);
    BooleanMatrix operator|(const BooleanMatrix&) const;
    BooleanMatrix& operator|=(const BooleanMatrix&);
    BooleanMatrix operator^(const BooleanMatrix&) const;
    BooleanMatrix& operator^=(const BooleanMatrix&);
    BooleanMatrix& operator~();

};