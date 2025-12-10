#include "linkedlist.hpp"
#include <cassert>
#include <cmath>
#include <utility>

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other) {
    for (auto it = other.cbegin(); it != other.cend(); it++, ++size_)
        push_back(*it);
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clean();
}

template <typename T>
LinkedList<T>::LinkedList(T *mas, size_t size) : size_(size) {
    for (size_t i = 0; i < size; i++)
        push_back(mas[i]);
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other) {
    clean();
    for (auto it = other.cbegin(); it != other.cend(); it++, ++size_)
        push_back(*it);
    return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T> &other) {
    std::swap(backptr_, other.backptr_);
    std::swap(frontptr_, other.frontptr_);
    std::swap(size_, other.size_);
}

template <typename T>
size_t LinkedList<T>::size() {
    // size_t size = 0;
    // if (empty())
    //     return 0;
    // for(auto it = begin(); it!=end(); it++) size++;
    return size_;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() {
    return iterator(frontptr_);
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() {
    return iterator(nullptr);
}

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::cbegin() const {
    return const_iterator(frontptr_);
}

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::cend() const {
    return const_iterator(nullptr);
}

template <typename T>
template <typename Predicate>
typename LinkedList<T>::iterator
LinkedList<T>::find_if(Predicate &&predicateObj) {
    for (auto i = begin(); i != end(); i++)
        if (predicateObj(*i))
            return i;
    return iterator(nullptr);
}

template <typename T>
void LinkedList<T>::push_front(const T &value) {
    ListNode *newnode = new ListNode(value, frontptr_);

    if (frontptr_)
        frontptr_->setPrev(newnode);

    frontptr_ = newnode;
    size_++;

    if (!backptr_)
        backptr_ = newnode;
}

template <typename T>
void LinkedList<T>::push_back(const T &value) {
    ListNode *newnode = new ListNode(value, nullptr, backptr_);

    if (backptr_)
        backptr_->setNext(newnode);

    backptr_ = newnode;
    size_++;

    if (!frontptr_)
        frontptr_ = newnode;
}

template <typename T>
template <typename Predicate>
typename LinkedList<T>::iterator
LinkedList<T>::insert_if(const T &value, Predicate &&predicateObj) {
    for (ListNode *it = frontptr_; it != nullptr; it = it->Next())
        if (predicateObj(it->Value())) {
            return insert(value, iterator(it));
        }
    return iterator(nullptr);
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::insert(const T &value,
                                                       iterator pos) {
    ListNode *cur = pos.Node();

    if (!cur) {
        push_back(value);
        return iterator(backptr_);
    }
    if (!cur->Prev()) {
        push_front(value);
        return iterator(frontptr_);
    }

    ListNode *newnode = new ListNode(value, cur, cur->Prev());
    cur->Prev()->setNext(newnode);
    cur->setPrev(newnode);
    return iterator(newnode);
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::insert(const T &value,
                                                       size_t pos) {
    if (empty() or (size_ <= pos)) {
        push_back(value);
        return iterator(backptr_);
    }
    iterator it = begin();
    for (size_t i = 0; i < pos; i++)
        it++;
    return insert(value, it);
}

template <typename T>
T LinkedList<T>::pop_back() {
    assert(!empty());
    T value = backptr_->Value_m();
    ListNode *ptr = backptr_->Prev();
    if (ptr)
        ptr->setNext(nullptr);
    else
        frontptr_ = nullptr;
    size_--;
    delete backptr_;
    backptr_ = ptr;
    return std::move(value);
}

template <typename T>
T LinkedList<T>::pop_front() {
    assert(!empty());
    T value = frontptr_->Value_m();
    ListNode *ptr = frontptr_->Next();
    if (ptr)
        ptr->setPrev(nullptr);
    else
        backptr_ = nullptr;
    size_--;
    delete frontptr_;
    frontptr_ = ptr;
    return std::move(value);
}

template <typename T>
T LinkedList<T>::erase(iterator pos) {
    assert(!empty());
    ListNode *node = pos.Node();
    T value = node->Value_m();

    if (node->Next())
        node->Next()->setPrev(node->Prev());
    else
        backptr_ = node->Prev();

    if (node->Prev())
        node->Prev()->setNext(node->Next());
    else
        frontptr_ = node->Next();

    delete node;
    --size_;
    return std::move(value);
}

template <typename T>
T LinkedList<T>::erase(size_t pos) {
    assert(!empty());
    assert(pos < size_);
    iterator it = begin();
    for (size_t i = 0; i < pos; i++, it++)
        ;
    return erase(it);
}

template <typename T>
T LinkedList<T>::erase(iterator start, iterator end) {
    assert(!empty());
    ListNode *prev = start.Node()->Prev();
    ListNode *node = start.Node();
    T value = node->Value_m();

    for (; start != end; start++) {
        node = start.Node();
        value = node->Value_m();
        delete node;
        --size_;
    }
    node = end.Node();

    if (node)
        node->setPrev(prev);
    else
        backptr_ = prev;

    if (prev)
        prev->setNext(node);
    else
        frontptr_ = node;

    return std::move(value);
}

template <typename T>
template <typename Predicate>
T LinkedList<T>::erase_if(Predicate &&predicateObj) {
    assert(!empty());
    for (ListNode *it = frontptr_; it != nullptr; it = it->Next())
        if (predicateObj(it->Value()))
            return erase(iterator(it));
    return T();
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::max() {
    assert(!empty());
    iterator res = begin();
    for (auto i = begin(); i != end(); i++) {
        if (*res < *i)
            res = i;
    }
    return res;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::min() {
    assert(!empty());
    iterator res = begin();
    for (auto i = begin(); i != end(); i++) {
        if (*res > *i)
            res = i;
    }
    return res;
}

template <typename T>
bool LinkedList<T>::empty() {
    return backptr_ == nullptr and frontptr_ == nullptr;
}

template <typename T>
void LinkedList<T>::clean() {
    for (iterator i = begin(); i != end();) {
        delete ((i++).Node());
    }
    frontptr_ = backptr_ = nullptr;
    size_ = 0;
}

template <typename T>
void LinkedList<T>::sort() {
    if (size_ <= 1)
        return;

    for (ListNode *j = backptr_; j != frontptr_; j = j->Prev()) {
        bool sorted = true;
        for (ListNode *i = frontptr_; i != j; i = i->Next()) {
            if (i->Value() > i->Next()->Value()) {
                std::swap(i->value_, i->Next()->value_);
                sorted = false;
            }
        }
        if (sorted)
            break;
    }
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &other) const {
    if (size_ != other.size_)
        return false;

    for (auto i = cbegin(), j = other.cbegin(); i != cend(); i++, j++)
        if (*i != *j)
            return false;
    return true;
}

template <typename T>
bool LinkedList<T>::operator!=(const LinkedList<T> &other) const {
    return !(operator==(other));
}

template <typename T>
T &LinkedList<T>::operator[](size_t index) {
    assert(!empty());
    assert(index < size_);
    iterator it = begin();
    for (size_t i = 0; i != index; i++)
        it++;
    return *it;
}

template <typename T>
const T &LinkedList<T>::operator[](size_t index) const {
    return this->operator[](index);
}

template <typename T>
LinkedList<T> LinkedList<T>::operator+(LinkedList<T> other) const {
    LinkedList tmp = *this;
    for (auto i = other.cbegin(); i != other.cend(); i++)
        tmp.push_back(*i);
    return tmp;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator+=(LinkedList<T> other) {
    for (auto i = other.cbegin(); i != other.cend(); i++)
        this->push_back(*i);
    return *this;
}

// ListNode

template <typename T>
LinkedList<T>::ListNode::ListNode(T value, ListNode *next, ListNode *prev)
    : value_(value), next_(next), prev_(prev) {}

template <typename T>
T &LinkedList<T>::ListNode::Value() {
    return value_;
}

template <typename T>
T LinkedList<T>::ListNode::Value_m() {
    return std::move(value_);
}

template <typename T>
const T &LinkedList<T>::ListNode::Value() const {
    return value_;
}

template <typename T>
typename LinkedList<T>::ListNode *LinkedList<T>::ListNode::Next() {
    return next_;
}

template <typename T>
const typename LinkedList<T>::ListNode *LinkedList<T>::ListNode::Next() const {
    return next_;
}

template <typename T>
typename LinkedList<T>::ListNode *LinkedList<T>::ListNode::Prev() {
    return prev_;
}

template <typename T>
const typename LinkedList<T>::ListNode *LinkedList<T>::ListNode::Prev() const {
    return prev_;
}

template <typename T>
void LinkedList<T>::ListNode::setNext(ListNode *node) {
    next_ = node;
}

template <typename T>
void LinkedList<T>::ListNode::setPrev(ListNode *node) {
    prev_ = node;
}

// iterator

template <typename T>
LinkedList<T>::iterator::iterator(LinkedList<T>::ListNode *node)
    : nodePtr_(node) {}

template <typename T>
bool LinkedList<T>::iterator::operator!=(const iterator &other) const {
    return nodePtr_ != other.nodePtr_;
}

template <typename T>
bool LinkedList<T>::iterator::operator==(const iterator &other) const {
    return nodePtr_ == other.nodePtr_;
}

template <typename T>
typename LinkedList<T>::iterator &LinkedList<T>::iterator::operator++() {
    nodePtr_ = nodePtr_->Next();
    return *this;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::iterator::operator++(int) {
    LinkedList<T>::iterator oldIterator(*this);
    nodePtr_ = nodePtr_->Next();
    return oldIterator;
}

template <typename T>
typename LinkedList<T>::iterator &LinkedList<T>::iterator::operator--() {
    nodePtr_ = nodePtr_->Prev();
    return *this;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::iterator::operator--(int) {
    iterator oldIterator(*this);
    nodePtr_ = nodePtr_->Prev();
    return oldIterator;
}

template <typename T>
T &LinkedList<T>::iterator::operator*() {
    return nodePtr_->Value();
}

template <typename T>
typename LinkedList<T>::ListNode *LinkedList<T>::iterator::Node() {
    return nodePtr_;
}

template <typename T>
const T &LinkedList<T>::const_iterator::operator*() const {
    return this->nodePtr_->Value();
}

template <typename T>
LinkedList<T>::const_iterator::const_iterator(ListNode *node)
    : iterator(node) {}

// iostream

template <typename T>
std::istream &operator>>(std::istream &cin, LinkedList<T> &list) {
    T value;
    cin >> value;
    list.push_front(value);
    return cin;
}

template <typename T>
std::ostream &operator<<(std::ostream &cout, const LinkedList<T> &list) {
    for (auto i = list.cbegin(); i != list.cend(); i++) {
        cout << *i << " ";
    }
    return cout;
}
