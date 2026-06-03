#include <random>
#include <iostream>
#include <algorithm>
#include <queue>
#include <math.h>
#include <string>
#include <assert.h>
#include "tree.hpp"

BinaryTree::BinaryTree(std::vector<int> data){
    for(auto i : data)
        addNode(i);
}

BinaryTree::BinaryTree(BinaryTree& other){
    root_ = copySubTree(other.root_);
}

BinaryTree::BinaryTree(BinaryTree&& other){
    root_ = other.root_;
    other.root_ = nullptr;
}

BinaryTree::~BinaryTree() {
    clear();
}

BinaryTree::TreeNode* BinaryTree::getRoot() {
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
    TreeNode* prevNode = root_, *removed_node, *replace_node = nullptr;
    bool flag = false, root = false;

    for(auto node : *this){
        if (node->getKey() == key){
            flag = true;
            removed_node = node;
            break;
        }
        prevNode = node;
    }
    if (!flag)
        return false;
    
    if (root_->getKey() == key)
        root = true;

    TreeNode *prevReplaceNode = removed_node;
    
    if (removed_node->getLeftChild() && removed_node->getRightChild()){
        replace_node = removed_node->getRightChild();
        while (replace_node->getLeftChild() || replace_node->getRightChild()){
            prevReplaceNode = replace_node;
            if (replace_node->getLeftChild())
                replace_node = replace_node->getLeftChild();
            else 
                replace_node = replace_node->getRightChild();
        }
    }
    else if (removed_node->getRightChild()){
        replace_node = removed_node->getRightChild();
    }
    else if (removed_node->getLeftChild())
        replace_node = removed_node->getLeftChild();

    if (prevReplaceNode->getLeftChild() == replace_node)
        prevReplaceNode->setLeftChild(nullptr);
    else if (prevReplaceNode->getRightChild() == replace_node)
        prevReplaceNode->setRightChild(nullptr);

    replace_node->setRightChild(removed_node->getRightChild());
    replace_node->setLeftChild(removed_node->getLeftChild());

    if (root)
        root_ = replace_node;
    else 
        if (removed_node == prevNode->getLeftChild())
            prevNode->setLeftChild(replace_node);
        else
            prevNode->setRightChild(replace_node);

    delete removed_node;
    return true;
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

std::vector<int> BinaryTree::getAllKeys() const {
    std::vector<int> keys;
    for(auto i : *this)
        keys.push_back(i->getKey());
    return keys;
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
    //добавить учет длины чисел
    int i = 0;
    int end = std::pow(2, height()) - 1;
    int margin = std::pow(2, height()-1);
    int betwen = std::pow(2, height());
    int next = 2;
    std::cout << std::string(margin-1, ' ');
    for (auto node = beginWithSpace(); i < end; i++, node++){
        if (*node == nullptr){
            // std::cout << std::string(" ", 1);
            std::cout << " ";
        }
        else {
            std::cout << (*node)->getKey();
        }
        std::cout << std::string(betwen-1, ' ');
        if (i == (next - 2)){
            std::cout << std::endl;
            next *= 2;
            margin /= 2;
            betwen /= 2;
            if (margin > 1)
                std::cout << std::string(margin-1, ' ');
        }
    }
}
//
BinaryTree::IteratorInBreadth<BinaryTree::TreeNode> BinaryTree::begin() {
    return IteratorInBreadth<TreeNode>(root_);
}

BinaryTree::IteratorInBreadthAll<BinaryTree::TreeNode> BinaryTree::beginWithSpace() {
    return IteratorInBreadthAll<TreeNode>(root_); 
}

BinaryTree::IteratorBase<BinaryTree::TreeNode> BinaryTree::end() {
    return IteratorBase<TreeNode>(nullptr);
}

BinaryTree::IteratorInBreadth<const BinaryTree::TreeNode> BinaryTree::begin() const {
    return IteratorInBreadth<const TreeNode>(root_);
}

BinaryTree::IteratorInBreadthAll<const BinaryTree::TreeNode> BinaryTree::beginWithSpace() const{
    return IteratorInBreadthAll<const TreeNode>(root_); 
}

BinaryTree::IteratorBase<const BinaryTree::TreeNode> BinaryTree::end() const {
    return IteratorBase<const TreeNode>(nullptr);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    clear();
    root_ = copySubTree(other.root_);
    return *this;
}

BinaryTree& BinaryTree::operator=(BinaryTree&& other) {
    root_ = other.root_;
    other.root_ = nullptr;
    return *this;
}

std::vector<BinaryTree::TreeNode*> BinaryTree::getAllNodes() { 
    std::vector<TreeNode*> result;
    for (auto i : *this)
        result.push_back(i);
    return result;
}

BinaryTree::TreeNode* BinaryTree::copySubTree(const TreeNode* node) {
    if (node == nullptr)
        return nullptr;
    TreeNode *node_new = new TreeNode(node->getKey());
    if (node->getLeftChild())
        node_new->setLeftChild(copySubTree(node->getLeftChild()));
    if (node->getRightChild())
        node_new->setRightChild(copySubTree(node->getRightChild()));
    return node_new;
    
}

void BinaryTree::printHorizontal(TreeNode* root, int marginLeft, int levelSpacing) const {
    if (root == nullptr) 
        return;
    printHorizontal(root->getRightChild(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root->getKey() << std::endl;
    printHorizontal(root->getLeftChild(), marginLeft + levelSpacing, levelSpacing);
}
