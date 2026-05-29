#include <iostream>
#include "tree.hpp"

template<typename NodeType>
BinaryTree::IteratorInBreadth<NodeType>::IteratorInBreadth(NodeType* node)
: IteratorBase(node) {
    if (node->getLeftChild())
        Queue.push(node->getLeftChild());
    if (node->getRightChild())
        Queue.push(node->getRightChild());
}

BinaryTree::IteratorInBreadth& BinaryTree::IteratorInBreadth::operator++(){
    if (Queue.empty()){
        node_ = nullptr;
        isEnd_ = true;
        return *this;
    }
    node_ = Queue.front();
    Queue.pop();
    if (node_->getLeftChild())
        Queue.push(node_->getLeftChild());
    if (node_->getRightChild())
        Queue.push(node_->getRightChild());
    return *this;
}

BinaryTree::IteratorInBreadth BinaryTree::IteratorInBreadth::operator++(int) {
    BinaryTree::IteratorInBreadth copy(*this);
    this->operator++();
    return copy;
}

