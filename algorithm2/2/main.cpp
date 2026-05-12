#include <iostream>

#include "tree/tree.hpp"

int main(){
    BinaryTree tree;
    tree.addNode(1);
    tree.addNode(2);
    tree.addNode(3);
    tree.addNode(4);
    tree.addNode(5);
    BinaryTree::TreeNode *n1, *n2;
    // std::cout << tree.getRoot()->getKey() << std::endl;
    BinaryTree::IteratorInBreadth iter(tree.getRoot());
    std::cout << tree.getRoot()->getLeftChild()->getKey() << std::endl;
    std::cout << tree.getRoot()->getRightChild()->getKey() << std::endl;
    for(int i=0; i<5; i++){
        std::cout << (*iter)->getKey() << " ";
        ++iter;
    }
    std::cout << std::endl;
    // iter.Queue.
    // while (!iter.Queue.empty()){
    //     std::cout << iter.Queue.back()->getKey() << " ";
    //     iter.Queue.pop();
    // }
}