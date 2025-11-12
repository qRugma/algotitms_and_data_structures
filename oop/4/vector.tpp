#include <iostream>
#include <initializer_list>

template<typename T>
class Vector {
    size_t size_ = 0;
    size_t capacity_ = 0;
    T* data_ = nullptr;

    
    public:
    Vector(int capacity=0);
    
    Vector(T* mas, int len);

    Vector(const std::initializer_list<T>&);
    
    Vector(const Vector &vec);

    Vector(Vector &&vec);

    ~Vector();
    
    int size() const;

    void swap(Vector &other);

    int find(const T& elem) const;

    template<typename I>
    friend std::ostream & operator << (std::ostream &cout, const Vector<I> &vec);
    template<typename I>
    friend std::istream & operator >> (std::istream &cin, Vector<I> &vec);

    void sort();

    bool insert(const size_t index, const T& value);
    bool insert(T* iter, const T& value);
    T pop(const size_t index);
    T pop(T* iter);
    void pop(T* begin, T* end);
    bool remove(const T &value);
    bool remove_all(const T &value);
    T max() const;
    T min() const;

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;


    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    Vector& operator=(const Vector &other);
    Vector operator+(const T &value) const;
    Vector& operator+=(const T &value);
    Vector& operator=(Vector &&other);
    Vector operator+(const Vector &other) const;
    Vector& operator+=(const Vector &other);
    bool operator==(const Vector &other) const;
    bool operator!=(const Vector &other) const;

};

#include "vector.inl"
