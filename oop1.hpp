class FreeVector{
    double x_, y_, z_;
    int dim = 3;

    public:
    FreeVector(const double& x=0, const double& y=0, const double& z=0);

    void newCoors(const double& x=0, const double& y=0, const double& z=0);

    
    friend std::ostream & operator << (std::ostream &cout, FreeVector vec);
    friend std::istream & operator >> (std::istream &cin, FreeVector vec);

    const double& getX();
    const double& getY();
    const double& getZ();

    double lenght() const;

    FreeVector orthonormal();

    FreeVector operator+(const FreeVector &rhs) const;

    FreeVector operator-(const FreeVector &rhs) const;

    FreeVector operator*(const double num) const;

    bool operator==(const FreeVector &rhs) const;
    bool operator!=(const FreeVector &rhs) const;
    double scalar(const FreeVector &rhs) const;
    FreeVector vectorProduct(const FreeVector &rhs) const;
    double tripleProduct(const FreeVector &mhs, const FreeVector &rhs) const;
    FreeVector doubleVectorProduct(const FreeVector &mhs, const FreeVector &rhs) const;
};