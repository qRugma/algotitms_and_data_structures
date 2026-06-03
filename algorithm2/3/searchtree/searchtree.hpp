#include "../../2/tree/tree.hpp"

class TreeSearch : public BinaryTree {
    TreeSearch();
    TreeSearch(TreeSearch&);
    TreeSearch(TreeSearch&&);
    ~TreeSearch();

    int getMinKey() const;
    int getMaxKey() const;
    TreeNode* addNode(const int);
    bool removeByKey(int key);
    TreeNode* find(int key);
    TreeNode const* find(int key) const;
    int height() const;
    std::vector<int> getAllKeys() const;

    BinaryTree &operator=(const BinaryTree &);
    BinaryTree &operator=(BinaryTree &&);
};