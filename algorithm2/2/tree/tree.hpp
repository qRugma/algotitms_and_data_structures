#include <vector>
#include <stack>
#include <queue>

class BinaryTree {  
  public:
    class TreeNode;
    template <typename NodeType>
    class IteratorBase;
    template <typename NodeType>
    class IteratorInBreadth;
    template <typename NodeType>
    class IteratorInBreadthAll;
    class IteratorLSR;
    class IteratorSLR;

    BinaryTree() = default;
    BinaryTree(std::vector<int>);
    BinaryTree(BinaryTree&);
    BinaryTree(BinaryTree&&);
    // BinaryTree(); copy, move
    ~BinaryTree();


    TreeNode* getRoot();
    void clear();
    void destroyNode(TreeNode*);
    bool isEmpty() const;
    int height() const;
    int height(TreeNode * root) const;
    int nodeCount();
    int getMinKey() const;
    int getMaxKey() const;
    TreeNode* addNode(const int);
    bool removeByKey(int key);
    TreeNode* find(int key);
    TreeNode const* find(int key) const;
    bool isBalance() const;
    bool isBalance(const TreeNode*) const;
    int nodeLevel(const TreeNode*) const;
    int nodeLevel(const TreeNode*, const TreeNode*, int level=0) const;
    std::vector<int> getAllKeys() const;
    void output() const;
    void outputByLevel() const;

    IteratorInBreadth<TreeNode> begin();
    IteratorInBreadthAll<TreeNode> beginWithSpace();
    IteratorBase<TreeNode> end();
    IteratorInBreadth<const TreeNode> begin() const;
    IteratorInBreadthAll<const TreeNode> beginWithSpace() const;
    IteratorBase<const TreeNode> end() const;
    
    

    BinaryTree &operator=(const BinaryTree &);
    BinaryTree &operator=(BinaryTree &&);

    std::vector<TreeNode*> getAllNodes() const;

  private:
    TreeNode *root_ = nullptr;
    TreeNode* copySubTree(const TreeNode*);
    void printHorizontal(TreeNode *, int marginLeft=2, int levelSpacing=1) const;
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

template<typename NodeType>
class BinaryTree::IteratorBase {
  public:  
    IteratorBase(NodeType *);

    bool operator!=(const IteratorBase<NodeType> &) const;
    bool operator==(const IteratorBase<NodeType> &) const;
    // IteratorBase &operator++();
    // IteratorBase operator++(int);
    NodeType* operator*();
    const NodeType* operator*() const;
    bool isEnd();
  protected:
    NodeType* node_;
    bool isEnd_=false;

};

template<typename NodeType>
class BinaryTree::IteratorInBreadth : public IteratorBase<NodeType> {  
    std::queue<NodeType*> Queue;

  public:
    IteratorInBreadth(NodeType *);
    IteratorInBreadth &operator++();
    IteratorInBreadth operator++(int);
};

template<typename NodeType>
class BinaryTree::IteratorInBreadthAll : public IteratorBase<NodeType> {  
    std::queue<NodeType*> Queue;

  public:
    IteratorInBreadthAll(NodeType *);
    IteratorInBreadthAll &operator++();
    IteratorInBreadthAll operator++(int);
};

// class BinaryTree::IteratorSLR : public IteratorBase {
//   public:
//     public:
//     IteratorSLR(TreeNode *);
//     IteratorSLR &operator++();
//     IteratorSLR operator++(int);
// };



#include "tree.inl"

