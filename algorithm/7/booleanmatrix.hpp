#pragma once

#include "booleanvector.hpp"
#include "vector.tpp"

class BooleanMatrix {
    Vector<BooleanVector> data_;
    size_t columns_, rows_;

  public:
    BooleanMatrix();
    BooleanMatrix(const char *[], size_t rows);
    BooleanMatrix(size_t columns, size_t rows);
    BooleanMatrix(const BooleanMatrix &) = default;
    ~BooleanMatrix() = default;
    int columns() const;
    int rows() const;
    void swap(BooleanMatrix &);

    int weight() const;
    int weight(size_t row) const;
    BooleanVector conjunction() const;
    BooleanVector disjunction() const;
    void invert(size_t row, size_t column);
    void invert_k(size_t row, size_t column, size_t k);
    void set(size_t row, size_t column, bool value);
    void set_k(size_t row, size_t column, bool value, size_t k);

    BooleanVector &operator[](size_t index);
    const BooleanVector &operator[](size_t index) const;
    BooleanMatrix operator&(const BooleanMatrix &) const;
    BooleanMatrix &operator&=(const BooleanMatrix &);
    BooleanMatrix operator|(const BooleanMatrix &) const;
    BooleanMatrix &operator|=(const BooleanMatrix &);
    BooleanMatrix operator^(const BooleanMatrix &) const;
    BooleanMatrix &operator^=(const BooleanMatrix &);
    BooleanMatrix operator~() const;

    void swap_rows(size_t row1, size_t row2);
    void swap_columns(size_t column1, size_t column2);

    bool connected(size_t X, size_t Y);

};

std::istream &operator>>(std::istream &cin, BooleanMatrix &mat);
std::ostream &operator<<(std::ostream &cout, const BooleanMatrix &mat);
