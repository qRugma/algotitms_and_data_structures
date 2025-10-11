class FreeVector{
    double x_, y_, z_;

    public:
    FreeVector(double x=0, double y=0, double z=0);

    void newCoors(double x=0, double y=0, double z=0);

    
    friend std::ostream & operator << (std::ostream &cout, const FreeVector &vec);
    friend std::istream & operator >> (std::istream &cin, FreeVector &vec);

    double getX() const;
    double getY() const;
    double getZ() const;
    
    void newX(double);
    void newY(double);
    void newZ(double);

    double lenght() const;

    FreeVector orthonormal() const;

    FreeVector operator+(const FreeVector &rhs) const;
    FreeVector operator+=(const FreeVector &rhs) const;

    FreeVector operator-(const FreeVector &rhs) const;
    FreeVector operator-=(const FreeVector &rhs) const;

    FreeVector operator*(const double num) const;
    FreeVector operator*=(const double num) const;

    bool operator==(const FreeVector &rhs) const;
    bool operator!=(const FreeVector &rhs) const;
    double scalar(const FreeVector &rhs) const;
    FreeVector vectorProduct(const FreeVector &rhs) const;
    double tripleProduct(const FreeVector &mhs, const FreeVector &rhs) const;
    FreeVector doubleVectorProduct(const FreeVector &mhs, const FreeVector &rhs) const;
};