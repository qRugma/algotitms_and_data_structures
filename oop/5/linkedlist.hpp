#pragma once

#include <iostream>

template <typename T>
class LinkedList {

    class ListNode;

    ListNode *backptr_ = nullptr;
    ListNode *frontptr_ = nullptr;
    size_t size_ = 0;

  public:
    class iterator;
    class const_iterator;

    LinkedList() = default;
    LinkedList(T *mas, size_t size);
    LinkedList(const LinkedList<T> &);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &);

    void swap(LinkedList<T> &);

    size_t size();

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

    template <typename Predicate>
    iterator find_if(Predicate &&predicateObj);

    void push_back(const T &);
    void push_front(const T &);

    T pop_back();
    T pop_front();
    iterator insert(const T &value, size_t pos);
    iterator insert(const T &value, iterator pos);
    template <typename Predicate>
    iterator insert_if(const T &value, Predicate &&predicateObj);

    T erase(size_t pos);
    T erase(iterator pos);
    T erase(iterator start, iterator end);
    template <typename Predicate>
    T erase_if(Predicate &&predicateObj);
    iterator max();
    iterator min();

    bool empty();
    void clean();
    void sort();

    T &operator[](size_t index);
    const T &operator[](size_t index) const;
    bool operator==(const LinkedList<T> &other) const;
    bool operator!=(const LinkedList<T> &other) const;
    LinkedList operator+(LinkedList<T> other) const;
    LinkedList &operator+=(LinkedList<T> other);
};

template <typename T>
class LinkedList<T>::ListNode {

    T value_;
    ListNode *prev_;
    ListNode *next_;
    friend LinkedList;

  public:
    ListNode(T = T(), ListNode *next = nullptr, ListNode *prev = nullptr);

    T &Value();
    T Value_m();
    const T &Value() const;

    ListNode *Next();
    ListNode *Prev();

    const ListNode *Next() const;
    const ListNode *Prev() const;

    void setNext(ListNode *);
    void setPrev(ListNode *);
};

template <typename T>
class LinkedList<T>::iterator {

  protected:
    ListNode *nodePtr_;

    friend LinkedList;
    ListNode *Node();

  public:
    iterator(ListNode *);

    bool operator!=(const iterator &) const;
    bool operator==(const iterator &) const;
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    T &operator*();
};

template <typename T>
class LinkedList<T>::const_iterator : public LinkedList<T>::iterator {
  public:
    const_iterator(ListNode *);
    const T &operator*() const;
};

template <typename T>
std::istream &operator>>(std::istream &cin, LinkedList<T> &list);
template <typename T>
std::ostream &operator<<(std::ostream &cout, const LinkedList<T> &list);

#include "linkedlist.tpp"