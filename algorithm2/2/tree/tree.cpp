#include <random>
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

