class FreeVector{
    std::array<double, 3> start = {0, 0, 0};
    std::array<double, 3> end = {0, 0, 0};
    std::array<double, 3> radius = {0, 0, 0};
    int dim = 3;


    void calcRadius();

    public:

    FreeVector(){}

    //first three is start point, next is end point
    FreeVector(int xS, int yS, int zS,
               int xE, int yE, int zE);

    // size start and end need >= 3
    FreeVector(int *Start, int *End);
    // FreeVector(const FreeVector&);

    // ~FreeVector(){}

    const double* getStart();

    const double* getEnd();
    
    const double* getRadius();

    void print();
    //first three is start point, next is end point
    void newCoors(int xS, int yS, int zS,
                  int xE, int yE, int zE);

    // size start need >= 3
    void newStart(const int* Start);

    // size end need >= 3
    void newEnd(const int* End);

    // size start and end need >= 3
    void newCoors(const int* Start, const int* End);
    
    double lenght() const;

    FreeVector orthonormal();

    FreeVector operator+(const FreeVector &rhs) const;

    FreeVector operator-(const FreeVector &rhs) const;

    FreeVector operator*(const int num) const;

    bool operator==(const FreeVector &rhs) const;
    double scalar(const FreeVector &rhs) const;
    FreeVector vectorProduct(const FreeVector &rhs) const;
    double tripleProduct(const FreeVector &mhs, const FreeVector &rhs) const;
    FreeVector doubleVectorProduct(const FreeVector &mhs, const FreeVector &rhs) const;
};