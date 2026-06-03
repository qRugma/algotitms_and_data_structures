#include <iostream>

#include "tree/tree.hpp"

int main(){
    BinaryTree tree;
    const BinaryTree *Ctree = &tree;
    std::cout << "nodeCount " << tree.nodeCount() << std::endl;
    std::cout << "empty " << tree.isEmpty() << std::endl;
    std::cout << "find 5 " << tree.find(5) << std::endl;
    std::cout << "height " << tree.height() << std::endl;
    std::cout << "isBalance "<< std::boolalpha << tree.isBalance() << std::endl;
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
    std::cout << "========== copy:" << std::endl;
    BinaryTree copytree = tree;
    copytree.outputByLevel();
    std::cout << "copy operator=" << std::endl;
    tree.clear();
    tree = copytree;
    tree.outputByLevel();
    
    std::cout << "move operator=" << std::endl;
    tree.clear();
    tree = std::move(copytree);
    tree.outputByLevel();

    std::cout << "remove 3" << std::endl;
    tree.removeByKey(3);
    tree.outputByLevel();
    std::cout << "remove 1" << std::endl;
    tree.removeByKey(1);
    tree.outputByLevel();
    std::cout << "remove 5" << std::endl;
    tree.removeByKey(5);
    tree.outputByLevel();

    std::cout << "getallnodes" << std::endl;

    for(auto i : tree.getAllNodes())
        std::cout << i->getKey() << " ";
    std::cout << std::endl;
    
    std::cout << "getallkeys" << std::endl;

    for(auto i : tree.getAllKeys())
        std::cout << i << " ";
    std::cout << std::endl;
}