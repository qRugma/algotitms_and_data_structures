#include <iostream>

#include "tree/tree.hpp"

int main(){
    BinaryTree tree;
    tree.addNode(1);
    tree.addNode(2);
    tree.addNode(3);
    tree.addNode(4);
    tree.addNode(5);
    BinaryTree::IteratorBase iterbase(nullptr);
    for(auto i : tree){
        std::cout << i->getKey() << " ";
    }
    std::cout << std::endl;    
}