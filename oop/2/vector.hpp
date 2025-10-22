class Vector {
    size_t size_ = 0;
    size_t capacity_ = 8;
    int* data_ = nullptr;

    
    public:
    Vector(int capacity=0);
    
    Vector(int* mas, int len);
    
    Vector(const std::initializer_list<int>&);
    
    Vector(const Vector &vec);
    
    Vector(Vector &&vec);
    
    ~Vector();

    int size() const;

    void swap(Vector &other);

    int find(const int elem) const;

    friend std::ostream & operator << (std::ostream &cout, const Vector &vec);
    friend std::istream & operator >> (std::istream &cin, Vector &vec);

    void sort();

    bool insert(size_t index, int value);
    bool insert(int* iter, int value);
    bool pop(size_t index);
    bool pop(int* iter);
    void pop(int* begin, int* end);
    bool remove(int value);
    bool remove_all(int value);
    int max() const;
    int min() const;

    int* begin();
    int* end();
    const int* begin() const;
    const int* end() const;


    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    Vector& operator=(const Vector &other);
    Vector operator+(int value) const;
    Vector& operator+=(int value);
    Vector& operator=(Vector &&other);
    Vector operator+(const Vector &other) const;
    Vector& operator+=(const Vector &other);
    bool operator==(const Vector &other) const;
    bool operator!=(const Vector &other) const;

};
