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
    if (node == nullptr)
        return;
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

template <typename NodeType>
BinaryTree::IteratorInBreadthAll<NodeType>::IteratorInBreadthAll(NodeType* node) 
: IteratorBase<NodeType>(node) {
    Queue.push(node->getLeftChild());
    Queue.push(node->getRightChild());
}

template<typename NodeType>
BinaryTree::IteratorInBreadthAll<NodeType>& BinaryTree::IteratorInBreadthAll<NodeType>::operator++(){
    if (Queue.empty()){
        IteratorBase<NodeType>::node_ = nullptr;
        IteratorBase<NodeType>::isEnd_ = true;
        return *this;
    }
    IteratorBase<NodeType>::node_ = Queue.front();
    Queue.pop();
    if (IteratorBase<NodeType>::node_){
        Queue.push(IteratorBase<NodeType>::node_->getLeftChild());
        Queue.push(IteratorBase<NodeType>::node_->getRightChild());
    } else {
        Queue.push(nullptr);
        Queue.push(nullptr);
    }
    return *this;
}

template<typename NodeType>
BinaryTree::IteratorInBreadthAll<NodeType> BinaryTree::IteratorInBreadthAll<NodeType>::operator++(int) {
    BinaryTree::IteratorInBreadthAll<NodeType> copy(*this);
    this->operator++();
    return copy;
}