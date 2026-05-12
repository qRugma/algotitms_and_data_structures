#include <vector>
#include <stack>
#include <queue>

class BinaryTree {  
  public:
    class TreeNode;
    class IteratorInBreadth;
    class IteratorLSR;

    BinaryTree() = default;
    // BinaryTree(); copy, move
    ~BinaryTree();


    TreeNode* getRoot() const;
    void clear();
    void destroyNode(TreeNode*);
    bool isEmpty() const;
    int height();
    int nodeCount();
    int getMinKey() const;
    int getMaxKey() const;
    TreeNode* addNode(const int);
    bool removeByKey(int key);
    TreeNode* find(int key);
    bool isBalance() const;
    int nodeLevel(TreeNode*) const;
    std::vector<int> getAllKeys() const;
    void output() const;
    void outputByLevel() const;
    

    BinaryTree &operator=(const BinaryTree &);
    BinaryTree &operator=(BinaryTree &&);

    std::vector<TreeNode*> getAllNodes() const;

  private:
    class IteratorBase;
    TreeNode *root_ = nullptr;
};


class  BinaryTree::TreeNode {
    int key_ = 0;
    TreeNode *leftChild_ = nullptr, *rightChild_ = nullptr;
  public:
    TreeNode() = default;
    TreeNode(int key, TreeNode* = nullptr, TreeNode* = nullptr);
    
    ~TreeNode() = default;

    int getKey() const;
    void setKey(const int);

    TreeNode* getLeftChild() const;
    void setLeftChild(TreeNode* const);
    TreeNode* getRightChild() const;
    void setRightChild(TreeNode* const);
};

class BinaryTree::IteratorBase {
  public:  
    IteratorBase(TreeNode *);

    bool operator!=(const IteratorBase &) const;
    bool operator==(const IteratorBase &) const;
    // IteratorBase &operator++();
    // IteratorBase operator++(int);
    TreeNode* operator*();
    const TreeNode* operator*() const;
  protected:
    TreeNode* node_;

};

class BinaryTree::IteratorInBreadth : public IteratorBase {  
  
  public:
    std::queue<TreeNode*> Queue;
    IteratorInBreadth(TreeNode *);
    IteratorInBreadth &operator++();
    IteratorInBreadth operator++(int);
    static IteratorInBreadth getEnd(const TreeNode* root);
};