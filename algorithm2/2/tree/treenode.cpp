#include "tree.hpp"

BinaryTree::TreeNode::TreeNode(int key, TreeNode* left, TreeNode* right) 
: key_(key), leftChild_(left), rightChild_(right) {}

int BinaryTree::TreeNode::getKey() const {
    return key_;
}

void BinaryTree::TreeNode::setKey(const int key) {
    key_ = key;
}

BinaryTree::TreeNode* BinaryTree::TreeNode::getLeftChild() const {
    return leftChild_;
}

void BinaryTree::TreeNode::setLeftChild(BinaryTree::TreeNode* child) {
    leftChild_ = child;
}

BinaryTree::TreeNode* BinaryTree::TreeNode::getRightChild() const {
    return rightChild_;
}

void BinaryTree::TreeNode::setRightChild(BinaryTree::TreeNode* child) {
    rightChild_ = child;
}
