#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bst.h"

using namespace std;
/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
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
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a balance of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent),
      balance_(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    // Methods for inserting/erasing (removing) elements from the tree. 
    // You must implement both of these methods.
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    virtual void erase(const Key& key);

    void AVLTreePrint() const;

private:
    /* Helper functions are strongly encouraged to help separate the problem
       into smaller pieces. You should not need additional data members. */

    /* You should write these helpers for sure.  You may add others. */
    void rotateLeft (AVLNode<Key, Value> *n);
    void rotateRight (AVLNode<Key, Value> *n);

    void insertFix (AVLNode<Key, Value> *n);
    void removeFix(AVLNode<Key, Value> *n, int difference);
    bool isRight (AVLNode<Key, Value> *n);    
    AVLNode<Key, Value>* findSuccessor(AVLNode<Key, Value> *n);
    /* A provided helper function to swap 2 nodes location in the tree */
    void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{

    AVLNode<Key, Value> *temp = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);

    if (BinarySearchTree<Key, Value>::mRoot == NULL) {
        this->BinarySearchTree<Key, Value>::mRoot = temp;
        return;
    }

    //TRAVERSING THE AVL TREE NOW
    AVLNode<Key, Value> *curr_parent = NULL;
    AVLNode<Key, Value> *curr = static_cast<AVLNode<Key, Value>*>(this->mRoot);

    while (true) {
        curr_parent = curr;
        if (keyValuePair.second < curr_parent->getValue()) {

            if (curr_parent->getLeft() == NULL) {

                curr_parent->setLeft(temp);
                temp->setParent(curr_parent);
                break;
            }
            curr = curr_parent->getLeft();
        } else {
            if (curr_parent->getRight() == NULL) {
                curr_parent->setRight(temp);
                temp->setParent(curr_parent);
                break;
            }
            curr = curr_parent->getRight();
        }
        // update balance from parent
        if (curr_parent->getBalance() == -1 || curr_parent->getBalance() == 1) {
            curr_parent->setBalance(0);

        } else {
            if (curr_parent->getLeft() == temp) {
                curr_parent->setBalance(-1);
            } else {
                curr_parent->setBalance(1);
            }
            this->insertFix(temp);
        }
    }
}

/**
* Erase function for a given key. Finds the node, reattaches pointers, and then balances when finished.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::erase(const Key& key)
{
    // TODO
    AVLNode<Key, Value> *temp = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
        //if node doesn't exist
    if (temp == NULL) {
        return;  
    }
    //if temp has both children
    if (temp->getLeft() != NULL && temp->getRight() != NULL) {
        // find in-order successor
        AVLNode<Key, Value> *succ = this->findSuccessor(temp);
        // swap node with in-order successor
        int temp_value = succ->getValue();
        succ->setValue(temp->getValue());
        temp->setValue(temp_value);
        nodeSwap(temp, succ);
    }

    // find child node (left or right)
    AVLNode<Key, Value> *temp_child = temp->getLeft();
    if (temp->getRight() != NULL) {
        temp_child = temp->getRight();
    }

    // update parents (including root)
    AVLNode<Key, Value> *temp_parent = temp->getParent();
    if (temp_child != NULL) {
        temp_child->setParent(temp_parent);
    }

    int difference;
    if (temp_parent == NULL) {
        BinarySearchTree<Key,Value>::mRoot = temp_child;
    } else {
            // If n is not in the root position determine its relationship with its parent
        if (temp == temp_parent->getLeft()) {
            temp_parent->setLeft(temp_child);
            difference = 1;
        } else {
            temp_parent->setRight(temp_child);
            difference = -1;
        }
    }
    delete temp;
    removeFix(temp_parent, difference);
}
template<typename Key, typename Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value> *n, int difference) 
{
    if (n == NULL) { return; }

    AVLNode<Key, Value> *node_parent = n->getParent();
    int ndifference = -1;

    if ((n != NULL) && (n == node_parent->getLeft())) {
        ndifference = 1;
    }
    if (n->getBalance() == -1 && difference == -1) { 
        AVLNode<Key, Value> *child = n->getLeft();
        // zig-zig case
        if (child->getBalance() <= 0) { 
            rotateRight(child);

            if (child->getBalance() == -1) {
                n->setBalance(0);
                child->setBalance(0);
                removeFix(node_parent, ndifference);
            } else { 
                n->setBalance(-1);
                child->setBalance(1);
            }
        // zig-zag case
        } else { 
            AVLNode<Key, Value> *grandchild = child->getRight();
            rotateLeft(child);
            rotateRight(n);

            if (grandchild->getBalance() == 1) {
                n->setBalance(0);
                child->setBalance(-1);

            } else if (grandchild->getBalance() == 0) {
                n->setBalance(0);
                child->setBalance(0);

            } else {
                n->setBalance(1);
                child->setBalance(0);
            }
            grandchild->setBalance(0);
            removeFix(node_parent, ndifference);
        }

    } else if ((n->getBalance() == 1) && (difference == 1)) { 
        AVLNode<Key, Value> *child = n->getRight();
        if (child->getBalance() >= 0) { // zig-zig case
            rotateLeft(child);

        if (child->getBalance() == 1) {
            n->setBalance(0);
            child->setBalance(0);
            removeFix(node_parent, ndifference);

        } else { 
            n->setBalance(1);
            child->setBalance(-1);
        }

    } else { // zig-zag case
        AVLNode<Key, Value> *grandchild = child->getLeft();
        rotateRight(child);
        rotateLeft(n);

        if (grandchild->getBalance() == -1) {
            n->setBalance(0);
            child->setBalance(1);

        } else if (grandchild->getBalance() == 0) {
            n->setBalance(0);
            child->setBalance(0);

        } else {
            n->setBalance(-1);
            child->setBalance(0);
        }
        grandchild->setBalance(0);
        removeFix(node_parent, ndifference);
    }

    } else {
        if (n->getBalance() == 0) {
            n->updateBalance(difference);
            return;

        } else {
            n->setBalance(0);
        }
        removeFix(node_parent, ndifference);
    }
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::findSuccessor(AVLNode<Key, Value> *n)
{
    if (n->getRight() != NULL) {
        n = n->getRight();
        while (n->getLeft() != NULL) {
            n = n->getLeft();
        }
        return n;
    }

    AVLNode<Key, Value> *node_parent = n->getParent();
    while ((node_parent != NULL) && (n == node_parent->getRight())) {
        n = node_parent;
        node_parent = node_parent->getParent();
    }
    return node_parent;
}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::isRight (AVLNode<Key, Value> *n) 
{
    if (n->getParent()->getRight() == n)
        return true;
    else
        return false;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::insertFix (AVLNode<Key, Value> *n)
{
    // TODO

    // parent and grandparent should not be NULL
    if (n->getParent() == NULL || n->getParent()->getParent() == NULL) {
        return;
    }

    AVLNode<Key, Value> *grandparent = n->getParent()->getParent();
    AVLNode<Key, Value> *parent = n->getParent();

    //if parent is left child of gParent
    if (parent == grandparent->getLeft()) {
        grandparent->updateBalance(-1);

        if (grandparent->getBalance() == 0) {
            return; 
        }

        if (grandparent->getBalance() == -1) {
            insertFix(parent);
            return;
        }

        if (n == parent->getLeft()) { // zig-zig (left left) 
            rotateRight(grandparent);
            parent->setBalance(0);
            grandparent->setBalance(0);

        } else { // zig-zag (left right) 
            rotateLeft(parent);
            rotateRight(grandparent);

            if (n->getBalance() == -1) {
                parent->setBalance(0);
                grandparent->setBalance(1);

            } else if (n->getBalance() == 0) {
                parent->setBalance(0);
                grandparent->setBalance(0);

            } else {
                parent->setBalance(-1);
                grandparent->setBalance(0);
             
            }
            n->setBalance(0);
        }

    } 
    //parent is the right child of gParent
    else { 
        grandparent->updateBalance(1);

        if (grandparent->getBalance() == 0) {
            return;
        }

        if (grandparent->getBalance() == 1) {
            insertFix(parent);
            return;
        }
        if (n == parent->getRight()) { // zig-zig (right right)
            rotateLeft(grandparent);
            parent->setBalance(0);
            grandparent->setBalance(0);

        } else { // zig-zag (right left)
            rotateRight(parent);
            rotateLeft(grandparent);

            if (n->getBalance() == 1) {
                parent->setBalance(0);
                grandparent->setBalance(-1);

            } else if (n->getBalance() == 0) {
                parent->setBalance(0);
                grandparent->setBalance(0);

            } else {
                 parent->setBalance(1);
                grandparent->setBalance(0);
            }
            n->setBalance(0);
        }
    }
}
/**
* Rotates n down and to the left
*/

template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value> *n)
{
    AVLNode<Key,Value> *nParent = n->getParent();
    AVLNode<Key, Value> *nGrand = nParent->getParent();
    if (nParent == NULL) {
        this->mRoot = nGrand;
    }
    else {
        if (nParent == nGrand->getLeft()) {
            nGrand->setLeft(n);
        }
        else {
            nGrand->setRight(n);
        }
    }

    nParent = nGrand;
    nGrand = n;

    if (!(this->isRight(n))) {
        nParent->setRight(n->getLeft());
        if (n->getLeft() != NULL) {
            n->getLeft()->setParent(nParent);
        }
        n->setLeft(nParent);
    }
}

/**
* Rotates n down and to the right
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value> *n)
{
    cout << "rotateRight entered" << endl;
    AVLNode<Key,Value> *nParent = n->getParent();
    AVLNode<Key, Value> *nGrand = nParent->getParent();
    if (nParent == NULL) {
        this->mRoot = nGrand;
    }
    else {
        if (nParent == nGrand->getLeft()) {
            nGrand->setLeft(n);
        }
        else {
            nGrand->setRight(n);
        }
    }

    nParent = nGrand;
    nGrand = n;


    if (this->isRight(n)) {
        nParent->setLeft(n->getRight());
        if (n->getRight() != NULL) {
            n->getRight()->setParent(nParent);
        }
        n->setRight(nParent);
    }
    cout << "rotateRight exited" << endl;

}

/**
 * Given a correct AVL tree, this functions relinks the tree in such a way that
 * the nodes swap positions in the tree.  Balances are also swapped.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    char temp2 = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(temp2);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->mRoot == n1) {
        this->mRoot= n2;
    }
    else if(this->mRoot == n2) {
        this->mRoot = n1;
    }

}
template<typename Key, typename Value>
void AVLTree<Key, Value>::AVLTreePrint() const 
{
    this->print();
}   
/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
