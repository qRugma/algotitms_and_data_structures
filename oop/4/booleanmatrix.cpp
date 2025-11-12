#include "booleanmatrix.hpp"

BooleanMatrix::BooleanMatrix(): data_(), rows_(0), columns_(0) {}

BooleanMatrix::BooleanMatrix(char* data[], size_t rows): data_(rows), columns_(rows) {
    for(int i=0; i<rows_; i++)
        data_[i] = BooleanVector(data[i]);
    columns_ = data_[0].getLenght();
}

BooleanMatrix::~BooleanMatrix(){}
