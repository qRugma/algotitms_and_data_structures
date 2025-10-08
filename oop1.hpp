#include <array>
class FreeVector{
    std::array<double, 3> start = {0, 0, 0};
    std::array<double, 3> end = {0, 0, 0};
    std::array<double, 3> radius = {0, 0, 0};
    int dim = 3;


    void calcRadius();

    public:

    FreeVector(){}

    //first three is start point, next is end point
    FreeVector(double xS, double yS, double zS,
               double xE, double yE, double zE);

    // size start and end need >= 3
    FreeVector(double *Start, double *End);
    // FreeVector(const FreeVector&);


    //first three is start point, next is end point
    // ~FreeVector(){}
    void newCoors(double *Start, double *End);

    // size start need >= 3
    void newStart(const double* Start);
    void newStart(double xS, double yS, double zS);

    // size end need >= 3
    void newEnd(const double* End);
    void newEnd(double xE, double yE, double zE);

    // size start and end need >= 3
    void newCoors(const double* Start, const double* End);
    
    void print();

    const double* getStart();

    const double* getEnd();
    
    const double* getRadius();

    double lenght() const;

    FreeVector orthonormal();

    FreeVector operator+(const FreeVector &rhs) const;

    FreeVector operator-(const FreeVector &rhs) const;

    FreeVector operator*(const double num) const;

    bool operator==(const FreeVector &rhs) const;
    double scalar(const FreeVector &rhs) const;
    FreeVector vectorProduct(const FreeVector &rhs) const;
    double tripleProduct(const FreeVector &mhs, const FreeVector &rhs) const;
    FreeVector doubleVectorProduct(const FreeVector &mhs, const FreeVector &rhs) const;
};