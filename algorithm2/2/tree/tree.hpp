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
    class IteratorLSR;
    class IteratorSLR;

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

    IteratorInBreadth<TreeNode> begin();
    IteratorBase<TreeNode> end();
    IteratorInBreadth<const TreeNode> begin() const;
    IteratorBase<const TreeNode> end() const;
    
    

    BinaryTree &operator=(const BinaryTree &);
    BinaryTree &operator=(BinaryTree &&);

    std::vector<TreeNode*> getAllNodes() const;

  private:
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

// class BinaryTree::IteratorSLR : public IteratorBase {
//   public:
//     public:
//     IteratorSLR(TreeNode *);
//     IteratorSLR &operator++();
//     IteratorSLR operator++(int);
// };



template<typename NodeType>
BinaryTree::IteratorBase<NodeType>::IteratorBase(NodeType * node)
: node_(node) {
    if (node_ == nullptr)
        isEnd_=true;
}

template<typename NodeType>
const NodeType* BinaryTree::IteratorBase<NodeType>::operator*() const { return node_; }

template<typename NodeType>
bool BinaryTree::IteratorBase<NodeType>::isEnd() { return isEnd_; }

template<typename NodeType>
NodeType* BinaryTree::IteratorBase<NodeType>::operator*() { return node_; }

template<typename NodeType>
bool BinaryTree::IteratorBase<NodeType>::operator==(const IteratorBase<NodeType>& other) const {
    return node_ == *other;
}

template<typename NodeType>
bool BinaryTree::IteratorBase<NodeType>::operator!=(const IteratorBase<NodeType>& other) const { 
    return node_ != *other;
}


template<typename NodeType>
BinaryTree::IteratorInBreadth<NodeType>::IteratorInBreadth(NodeType* node)
: IteratorBase<NodeType>(node) {
    if (node->getLeftChild())
        Queue.push(node->getLeftChild());
    if (node->getRightChild())
        Queue.push(node->getRightChild());
}

template<typename NodeType>
BinaryTree::IteratorInBreadth<NodeType>& BinaryTree::IteratorInBreadth<NodeType>::operator++(){
    if (Queue.empty()){
        IteratorBase<NodeType>::node_ = nullptr;
        IteratorBase<NodeType>::isEnd_ = true;
        return *this;
    }
    IteratorBase<NodeType>::node_ = Queue.front();
    Queue.pop();
    if (IteratorBase<NodeType>::node_->getLeftChild())
        Queue.push(IteratorBase<NodeType>::node_->getLeftChild());
    if (IteratorBase<NodeType>::node_->getRightChild())
        Queue.push(IteratorBase<NodeType>::node_->getRightChild());
    return *this;
}

template<typename NodeType>
BinaryTree::IteratorInBreadth<NodeType> BinaryTree::IteratorInBreadth<NodeType>::operator++(int) {
    BinaryTree::IteratorInBreadth copy(*this);
    this->operator++();
    return copy;
}
