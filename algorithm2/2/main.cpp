#include <iostream>

#include "tree/tree.hpp"

int main(){
    BinaryTree tree;
    const BinaryTree *Ctree = &tree;
    std::cout << "nodeCount " << tree.nodeCount() << std::endl;
    std::cout << "find 5 " << tree.find(5) << std::endl;
    std::cout << "height " << tree.height() << std::endl;
    tree.addNode(1);
    tree.addNode(2);
    tree.addNode(3);
    std::cout << "isbalance " << tree.isBalance() << std::endl;
    tree.addNode(4);
    tree.addNode(5);
    std::cout << "nodeCount " << tree.nodeCount() << std::endl;
    std::cout << "iterator: " << std::endl;
    for(auto i : tree){
        std::cout << i->getKey() << " ";
    }
    std::cout << std::endl;
    std::cout << "output: " << std::endl;
    tree.output();
    std::cout << "find 5 " << tree.find(5) << std::endl;
    std::cout << "const find 5 " << Ctree->find(5) << std::endl;
    std::cout << "height " << tree.height() << std::endl;
    std::cout << "minkey " << tree.getMinKey() << std::endl;
    std::cout << "maxkey " << tree.getMaxKey() << std::endl;
    for(auto i : *Ctree){
        std::cout << "key " << i->getKey() << "  level " << Ctree->nodeLevel(i) << std::endl;
    }
    std::cout << "outputBylevel" << std::endl;
    tree.outputByLevel();
}