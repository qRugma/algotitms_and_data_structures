class Vector {
    int size_ = 0;
    int capacity_ = 8;
    int* data_ = nullptr;

    
    public:
    Vector(int capacity=0);
    
    Vector(int* mas, int len);
    
    Vector(const std::initializer_list<int>&);
    
    Vector(const Vector &vec);

    Vector(Vector &&vec);
    
    int size() const;

    void swap(Vector &other);

    int find(int elem) const;

    friend std::ostream & operator << (std::ostream &cout, const Vector &vec);
    friend std::istream & operator >> (std::istream &cin, Vector &vec);

    void sort();

    bool insert(const int index, const int value);
    bool pop(const int index);
    bool remove(const int value);
    bool remove_all(const int value);
    int max() const;
    int min() const;

    int* begin();
    int* end();
    const int* begin() const;
    const int* end() const;

    int& operator[](int index);
    const int& operator[](int index) const;
    Vector& operator=(const Vector &other);
    Vector operator+(int value) const;
    Vector& operator+=(int value);
    Vector& operator=(Vector &&other);
    Vector operator+(const Vector &other) const;
    Vector& operator+=(const Vector &other);
    bool operator==(const Vector &other) const;
    bool operator!=(const Vector &other) const;

};
