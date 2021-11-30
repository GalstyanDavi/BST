#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert(const std::pair<const Key, Value>& new_item); // TODO
    virtual void remove(const Key& key);  // TODO
    bool find(const Key& key);
protected:
    virtual void nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2);

    // Add helper functions here

    AVLNode<Key, Value>* insertHelper(AVLNode<Key, Value>* root, AVLNode<Key, Value>* parent, const std::pair<const Key, Value>& new_item);
    AVLNode<Key, Value>* removeHelper(AVLNode<Key, Value>* root, const Key& key);
    AVLNode<Key, Value>* leftRotate(AVLNode<Key, Value>* x);
    AVLNode<Key, Value>* rightRotate(AVLNode<Key, Value>* x);

};

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value>& new_item)
{
    this->root_ = insertHelper(static_cast<AVLNode<Key, Value>*>(this->root_), NULL, new_item);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}
// Rotate right
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::rightRotate(AVLNode<Key, Value>* node) {
    AVLNode<Key, Value>* x = node->getLeft();
    AVLNode<Key, Value>* T2 = x->getRight();
    x->setRight(node);
    x->setParent(node->getParent());
    if (x->getParent())
        if (x->getParent()->getLeft() == x)
            x->getParent()->setLeft(x);
        else
            x->getParent()->setRight(x);
    x->getLeft()->setParent(x);
    node->setLeft(T2);
    node->setHeight(max(this->height(node->getLeft()), this->height(node->getRight())) + 1);
    x->setHeight(max(this->height(x->getLeft()), this->height(x->getRight())) + 1);
    return x;
}

template<class Key, class Value>
bool AVLTree<Key, Value>::find(const Key& key)
{
    if (this->internalFind(key))
        return true;
    return false;
}

// Rotate left
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::leftRotate(AVLNode<Key, Value>* x) {
    AVLNode<Key, Value>* y = x->getRight();
    AVLNode<Key, Value>* T2 = y->getLeft();
    y->setLeft(x);
    y->setParent(x->getParent());
    if (y->getParent())
        if (y->getParent()->getLeft() == y)
            y->getParent()->setLeft(y);
        else
            y->getParent()->setRight(y);
    y->getLeft()->setParent(y);
    x->setRight(T2);
    x->setHeight(max(this->height(x->getLeft()), this->height(x->getRight())) + 1);
    y->setHeight(max(this->height(y->getLeft()), this->height(y->getRight())) + 1);
    return y;
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::insertHelper(AVLNode<Key, Value>* root, AVLNode<Key, Value>* parent, const std::pair<const Key, Value>& new_item)
{
    /* 2. Insert node */
    // Find the correct postion and insert the node
    if (root == NULL)
    {
        root = new AVLNode<Key, Value>(new_item.first, new_item.second, parent);
        root->setRight(NULL);
        root->setLeft(NULL);
        return root;
    }
    if (new_item.first < root->getKey())
    {
        root->setLeft(insertHelper(root->getLeft(), root, new_item));
        //balance(root);
    }
    else if (new_item.first > root->getKey())
    {
        root->setRight(insertHelper(root->getRight(), root, new_item));
        // balance(root);
    }
    else {
        root->setValue(new_item.second);
        return root;
    }

    /* 2. Update height of this ancestor node */
    int r_h = 0;
    int l_h = 0;
    if (root->getLeft())
        l_h = root->getLeft()->getHeight();
    if (root->getRight())
        r_h = root->getRight()->getHeight();

     root->setHeight(1 + max(r_h,l_h));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = 0;
    if (root)
        balance = l_h - r_h;

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && new_item.first < root->getLeft()->getKey())
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && new_item.first  > root->getRight()->getKey())
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && new_item.first > root->getLeft()->getKey())
    {
        root->setLeft(leftRotate(root->getLeft()));
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && new_item.first < root->getRight()->getKey())
    {
        root->setRight(rightRotate(root->getRight()));
        return leftRotate(root);
    }

    /* return the (unchanged) node pointer */
    return root;
}
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    this->root_ = removeHelper(static_cast<AVLNode<Key, Value>*>(this->root_), key);
}
template<class Key, class Value>
int getBalance(AVLNode<Key, Value>* N)
{
    if (N == NULL)
        return 0;
    int r_h = 0;
    int l_h = 0;
    if (N->getLeft())
        l_h = N->getLeft()->getHeight();
    if (N->getRight())
        r_h = N->getRight()->getHeight();
    return l_h - r_h;
}
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::removeHelper(AVLNode<Key, Value>* root, const Key& key) {
    // start with the root node
    AVLNode<Key, Value>* curr = root;

    // search key in the BST and set its parent pointer
    curr = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));


    // return if the key is not found in the tree
    if (curr == nullptr) {
        return NULL;
    }

    // Case 1: node to be deleted has no children, i.e., it is a leaf node
    if (curr->getLeft() == nullptr && curr->getRight() == nullptr)
    {
        // if the node to be deleted is not a root node, then set its
        // parent left/right child to null
        if (curr != root)
        {
            if (curr->getParent()->getLeft() == curr) {
                curr->getParent()->setLeft(NULL);
            }
            else {
                curr->getParent()->setRight(NULL);
            }
        }
        // if the tree has only a root node, set it to null
        else {
            root = nullptr;
        }
    }

    // Case 2: node to be deleted has two children
    else if (curr->getLeft() && curr->getRight())
    {
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(curr));
        nodeSwap(curr, pred);
        if (curr->getParent()->getLeft() == curr) {
            curr->getParent()->setLeft(NULL);
        }
        else {
            curr->getParent()->setRight(NULL);
        }
    }
    // Case 3: node to be deleted has only one child
    else {
        // choose a child node
        AVLNode<Key, Value>* child = (curr->getLeft()) ? curr->getLeft() : curr->getRight();
        // if the node to be deleted is not a root node, set its parent
        // to its child
        if (curr != root)
        {
            if (curr == curr->getParent()->getLeft()) {
                curr->getParent()->setLeft(child);
                child->setParent(curr->getParent());
            }
            else {
                curr->getParent()->setRight(child);
                child->setParent(curr->getParent());
            }
        }

        // if the node to be deleted is a root node, then set the root to the child
        else {
            root = child;
        }
    }

  
        /* 2. Update height of this ancestor node */
    if (getBalance(root->getRight()) > getBalance(root->getLeft()))
        root->setHeight(1 + getBalance(root->getRight()));
    else
        root->setHeight(1 + getBalance(root->getLeft()));


    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(root);

    // If this node becomes unbalanced, then
    // there are 4 cases

      // Left Left Case
    if (balance > 1 &&
        getBalance(root->getLeft()) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 &&
        getBalance(root->getLeft()) < 0)
    {
        root->setLeft(leftRotate(root->getLeft()));
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 &&
        getBalance(root->getRight()) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 &&
        getBalance(root->getRight()) > 0)
    {
        root->setRight(rightRotate(root->getRight()));
        return leftRotate(root);
    }
    return root;
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


#endif
