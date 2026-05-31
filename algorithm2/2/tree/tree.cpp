#include <random>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include "tree.hpp"

BinaryTree::~BinaryTree() {
    clear();
}

BinaryTree::TreeNode* BinaryTree::getRoot() const {
    return root_;
}

void BinaryTree::clear() {
    if (root_){
        destroyNode(root_);
        root_ = nullptr;
    }
}

void BinaryTree::destroyNode(BinaryTree::TreeNode* treeNode)
{
    if (treeNode->getLeftChild()) destroyNode(treeNode->getLeftChild());
    if (treeNode->getRightChild()) destroyNode(treeNode->getRightChild());
    delete treeNode;
}

bool BinaryTree::isEmpty() const {
    if (root_)
        return false;
    return true;
}

int BinaryTree::height() const{
    if (root_ == nullptr)
        return 0;
    return 1 + std::max(height(root_->getLeftChild()), height(root_->getRightChild()));
}

int BinaryTree::height(TreeNode * root) const{
    if (root == nullptr)
        return 0;
    return 1 + std::max(height(root->getLeftChild()), height(root->getRightChild()));
}


int BinaryTree::nodeCount() {
    int counter=0;
    for(auto _ : *this)
        counter++;
    return counter;
}

int BinaryTree::getMinKey() const {
    assert(root_ != nullptr);
    int key = root_->getKey();
    for(auto node : *this)
        key = std::min(key, node->getKey());
    return key;
}

int BinaryTree::getMaxKey() const { 
    assert(root_ != nullptr);
    int key = root_->getKey();
    for(auto node : *this)
        key = std::max(key, node->getKey());
    return key;
 }

BinaryTree::TreeNode* BinaryTree::addNode(const int key)
{
    if (!root_)
    {
        root_ = new TreeNode(key);
        return root_;
    }

    TreeNode *currentNode = root_;

    while (true)
    {
        int randomValue = rand() % 2;

        if (randomValue == 0)
        {
            if (!currentNode->getLeftChild())
            {
                currentNode->setLeftChild(new TreeNode(key));
                return currentNode->getLeftChild();
            }
            else
            {
                currentNode = currentNode->getLeftChild();
            }
        }
        else
        {
            if (!currentNode->getRightChild())
            {
                currentNode->setRightChild(new TreeNode(key));
                return currentNode->getRightChild();
            }
            else
            {
                currentNode = currentNode->getRightChild();
            }
        }
    }    
}

bool BinaryTree::removeByKey(int key) { 
    for(auto node : *this){
        if (node->getKey() == key){
            destroyNode(node);
            return true;
        }
    }
    return false;
}

BinaryTree::TreeNode* BinaryTree::find(int key) {
    for(auto node : *this)
        if (node->getKey() == key)
            return node;
    return nullptr;
}

BinaryTree::TreeNode const* BinaryTree::find(int key) const{
    for(auto node : *this)
        if (node->getKey() == key)
            return node;
    return nullptr;
}

bool BinaryTree::isBalance() const { 
    if (root_ == nullptr)
        return true;
    return isBalance(root_->getLeftChild()) && isBalance(root_->getRightChild());
}

bool BinaryTree::isBalance(const TreeNode* node) const { 
    if (node == nullptr)
        return true;
    return isBalance(node->getLeftChild()) && isBalance(node->getRightChild());
}

int BinaryTree::nodeLevel(const TreeNode* node) const {
    if (root_ == nullptr)
        return -1;
    return nodeLevel(node, root_, 0);
}

int BinaryTree::nodeLevel(const TreeNode* node, const TreeNode* root, int level) const {
    if (root == node)
        return level;
    if (root == nullptr)
        return -1;
    return std::max(
        nodeLevel(node, root->getLeftChild(), level+1),
        nodeLevel(node, root->getRightChild(), level+1)
    );
}

void BinaryTree::output() const {
    if (root_ == nullptr) 
        return;
    int marginLeft = 2, levelSpacing = 1;
    printHorizontal(root_->getRightChild(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root_->getKey() << std::endl;
    printHorizontal(root_->getLeftChild(), marginLeft + levelSpacing, levelSpacing);
}

void BinaryTree::outputByLevel() const {
    int height_ = height();
    int margin = std::pow(2, height_) - 1;
    for(auto node : *this){
        std::cout << (' ' * margin) << node->getKey();
    }
}

BinaryTree::IteratorInBreadth<BinaryTree::TreeNode> BinaryTree::begin() {
    return IteratorInBreadth<TreeNode>(root_);
}

BinaryTree::IteratorBase<BinaryTree::TreeNode> BinaryTree::end() {
    return IteratorBase<TreeNode>(nullptr);
}

BinaryTree::IteratorInBreadth<const BinaryTree::TreeNode> BinaryTree::begin() const {
    return IteratorInBreadth<const TreeNode>(root_);
}

BinaryTree::IteratorBase<const BinaryTree::TreeNode> BinaryTree::end() const {
    return IteratorBase<const TreeNode>(nullptr);
}

BinaryTree& BinaryTree::operator=(const BinaryTree&) {
    // TODO: insert return statement here
    return *this;
}

BinaryTree& BinaryTree::operator=(BinaryTree&& other) {
    root_ = other.root_;
    other.root_ = nullptr;
    return *this;
}

std::vector<BinaryTree::TreeNode*> BinaryTree::getAllNodes() const { return std::vector<TreeNode*>(); }

void BinaryTree::printHorizontal(TreeNode* root, int marginLeft, int levelSpacing) const{
    if (root == nullptr) 
        return;
    printHorizontal(root->getRightChild(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root->getKey() << std::endl;
    printHorizontal(root->getLeftChild(), marginLeft + levelSpacing, levelSpacing);
}
