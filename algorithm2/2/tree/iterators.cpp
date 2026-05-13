#include <iostream>
#include "tree.hpp"

BinaryTree::IteratorBase::IteratorBase(TreeNode * node)
: node_(node) {
    if (node_ == nullptr)
        isEnd_=true;
}

const BinaryTree::TreeNode* BinaryTree::IteratorBase::operator*() const { return node_; }

bool BinaryTree::IteratorBase::isEnd() { return isEnd_; }

BinaryTree::TreeNode* BinaryTree::IteratorBase::operator*() { return node_; }

bool BinaryTree::IteratorBase::operator==(const IteratorBase& other) const {
    return node_ == *other;
}

bool BinaryTree::IteratorBase::operator!=(const IteratorBase& other) const { 
    return node_ != *other;
}

BinaryTree::IteratorInBreadth::IteratorInBreadth(TreeNode* node)
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

