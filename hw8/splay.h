#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bst.h"

using namespace std;


template <typename Key, typename Value>
class SplayNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    SplayNode(const Key& key, const Value& value, SplayNode<Key, Value>* parent);
    virtual ~SplayNode();


    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to SplayNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual SplayNode<Key, Value>* getParent() const override;
    virtual SplayNode<Key, Value>* getLeft() const override;
    virtual SplayNode<Key, Value>* getRight() const override;

protected:

};

/*
--------------------------------------------
Begin implementations for the SplayNode class.
--------------------------------------------
*/

/**
* Constructor for an SplayNode. Nodes are initialized with a balance of 0.
*/
template<typename Key, typename Value>
SplayNode<Key, Value>::SplayNode(const Key& key, const Value& value, SplayNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
SplayNode<Key, Value>::~SplayNode()
{

}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
SplayNode<Key, Value>* SplayNode<Key, Value>::getParent() const
{
    return static_cast<SplayNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
SplayNode<Key, Value>* SplayNode<Key, Value>::getLeft() const
{
    return static_cast<SplayNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
SplayNode<Key, Value>* SplayNode<Key, Value>::getRight() const
{
    return static_cast<SplayNode<Key,Value>*>(this->mRight);
}

/*

End of SplayNode class


*/


/**
* A templated binary search tree implemented as an Splay tree.
*/
template <typename Key, typename Value, typename Comp = std::less<Key> >
class SplayTree : public BinarySearchTree<Key, Value>
{
public:
    SplayTree(const Comp &c = Comp());
    ~SplayTree();
    virtual void insert(const pair<const Key, Value>& keyValuePair) override;
    // Return NULL if the key doesn't exist in the map
    pair<const Key,Value>* find(const Key& key);
    // Do nothing if the key does not exist
    virtual void erase(const Key& key);
    // Splay Function
    void splay(SplayNode<Key,Value>*item);
 
    size_t size() const;
    bool empty() const;
    void SplayTreePrint(); 

 
private:
    /* Helper functions are strongly encouraged to help separate the problem
       into smaller pieces. You should not need additional data members. */
 
    void rotateLeft (SplayNode<Key, Value> *n);
    void rotateRight (SplayNode<Key, Value> *n);
 
    /* A provided helper function to swap 2 nodes location in the tree */
    void nodeSwap( SplayNode<Key,Value>* n1, SplayNode<Key,Value>* n2);
 
    /* Helper function to find successor of given node */

    SplayNode<Key, Value>* findSuccessor(SplayNode<Key, Value>* n);
    Comp c_;

};
template <typename Key, typename Value, typename Comp>
SplayTree<Key, Value, Comp>::SplayTree(const Comp &c) : c_(c)
{

}

template <typename Key, typename Value, typename Comp>
SplayTree<Key, Value, Comp>::~SplayTree()
{

}


template <typename Key, typename Value, typename Comp>
void SplayTree<Key, Value, Comp>::insert (const pair<const Key, Value>& keyValuePair) 
{
    SplayNode<Key, Value> *temp = new SplayNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);

    if (BinarySearchTree<Key, Value>::mRoot == NULL) {
    	temp->setLeft(NULL);
        temp->setRight(NULL);
        this->BinarySearchTree<Key, Value>::mRoot = temp;
        return;
    }

    SplayNode<Key, Value> *curr = static_cast<SplayNode<Key, Value>*>(BinarySearchTree<Key,Value>::mRoot);

    while (curr != NULL) {
        if (c_(keyValuePair.first,curr->getKey())) {

            if (curr->getLeft() == NULL) {
                temp->setParent(curr);
                curr->setLeft(temp);
                splay(temp);
                return;
            }
            curr = curr->getLeft();
        } 
        else if (keyValuePair.first == curr->getKey()) {
        	//overwrite even if it's equal
        	curr->setValue(keyValuePair.second);
        	splay(curr);
        	return;
        }
        else {
            if (curr->getRight() == NULL) {
                temp->setParent(curr);
                curr->setRight(temp);
                splay(temp);
                return;
            }
            curr = curr->getRight();
        }
    }
}

template <typename Key, typename Value, typename Comp>
pair<const Key,Value>* SplayTree<Key,Value,Comp>::find(const Key& key)
{
    typename BinarySearchTree<Key, Value>::iterator bst_it = internalFind(key);
    if (bst_it == NULL) {
        return NULL;
    }

    SplayNode<Key,Value>* temp = static_cast<SplayNode<Key,Value>*>(this->internalFind(key));
    splay(temp);
    return *bst_it;
}

template <typename Key, typename Value, typename Comp >
void SplayTree<Key,Value,Comp>::erase(const Key& key)
{
    SplayNode<Key, Value> *temp = static_cast<SplayNode<Key, Value>*>(this->internalFind(key));
        //if node doesn't exist
    if (temp == NULL) { return;}

    splay(temp);
    //if temp has both children
    if (findSuccessor(temp) != NULL) {
        // find in-order successor
        SplayNode<Key, Value> *succ = findSuccessor(temp);
        nodeSwap(temp, succ);
    }

	if (temp->getParent() != NULL) {
        SplayNode<Key,Value>* parent = temp->getParent();
        //if temp is parent's LC
        if (parent->getLeft() == temp) {
            // If n has any children, set as parent's child
            if (temp->getLeft() != NULL || temp->getRight() != NULL) {
                if (temp->getLeft() != NULL) {
                	SplayNode<Key,Value>* left_child = temp->getLeft();
                    parent->setLeft(left_child);
                    left_child->setParent(parent);
                }
                else {
                	SplayNode<Key,Value>* right_child = temp->getRight();
                    parent->setLeft(right_child);
                    right_child->setParent(parent);
                }
            }
            else {
                parent->setLeft(NULL);
            }
        }
        // temp is RC
        else {
            if (temp->getLeft() != NULL || temp->getRight() != NULL) {
                if (temp->getLeft() != NULL) {
                 	SplayNode<Key,Value>* left_child = temp->getLeft();
                    parent->setRight(left_child);
                    left_child->setParent(parent);
                }
                else {
                	SplayNode<Key,Value>* right_child = temp->getRight();
                    parent->setRight(right_child);
                    right_child->setParent(parent);
                }
            }
            else {
                parent->setRight(NULL);
            }
        }
        delete temp;
        return;
    }
    // temp is the root
    else {
        if (temp->getLeft() != NULL) {
            BinarySearchTree<Key,Value>::mRoot = temp->getLeft();
            BinarySearchTree<Key,Value>::mRoot->setParent(NULL);
        }
        else if (temp->getLeft() != NULL) {
            BinarySearchTree<Key,Value>::mRoot = temp->getRight();
            BinarySearchTree<Key,Value>::mRoot->setParent(NULL);
        }
        else {
            BinarySearchTree<Key,Value>::mRoot = NULL;
        }
        delete temp;
    }
}

template <typename Key, typename Value, typename Comp >
void SplayTree<Key,Value,Comp>::rotateLeft (SplayNode<Key, Value> *n)
{
    SplayNode<Key, Value>* child = n->getRight();
    // child's LC will become n's right
    if (child->getLeft() != NULL) {
    	SplayNode<Key, Value>* childs_left = child->getLeft();
        n->setRight(childs_left);
        childs_left->setParent(n);
    }
    else {
        n->setRight(NULL);
    }
    // n's parent becomes child's parent
    if (n->getParent() != NULL) {
    	SplayNode<Key, Value>* parent = n->getParent();
        // If n is LC
        if (parent->getLeft() == n) {
            parent->setLeft(child);
        }
        // n is RC
        else {
            parent->setRight(child);
        }
        child->setParent(parent);
    }
    // n is root
    else {
        child->setParent(NULL);
        BinarySearchTree<Key,Value>::mRoot = child;
    }
    child->setLeft(n);
    n->setParent(child);
}

template <typename Key, typename Value, typename Comp >
void SplayTree<Key,Value,Comp>::rotateRight (SplayNode<Key, Value> *n)
{
    SplayNode<Key, Value>* child = n->getLeft();
    // child's LC will become n's right
    if (child->getRight() != NULL) {
    	SplayNode<Key, Value>* childs_right = child->getRight();
        n->setLeft(childs_right);
        childs_right->setParent(n);
    }
    else {
        n->setLeft(NULL);
    }
    // n's parent becomes child's parent
    if (n->getParent() != NULL) {
    	SplayNode<Key, Value>* parent = n->getParent();
        // If n is LC
        if (parent->getRight() == n) {
            parent->setRight(child);
        }
        // n is RC
        else {
            parent->setLeft(child);
        }
        child->setParent(parent);
    }
    // n is root
    else {
        child->setParent(NULL);
        BinarySearchTree<Key,Value>::mRoot = child;
    }
    child->setRight(n);
    n->setParent(child);
}

template <typename Key, typename Value, typename Comp >
void SplayTree<Key,Value,Comp>::splay(SplayNode<Key, Value> *item)
{
    if (BinarySearchTree<Key,Value>::mRoot == item) {
        return;
    }
    // item isn't the root, so get parent
    SplayNode<Key, Value>* parent = item->getParent();
    // gparent if possible
    if (parent->getParent() != NULL) {
        SplayNode<Key, Value>* grandParent = parent->getParent();
        // if parent is GP's LC
        if (grandParent->getLeft() == parent) {
            // Zig-Zig
            if (parent->getLeft() == item) {
                rotateRight(grandParent);
                rotateRight(parent);
                splay(item);
            }
            // Zig-Zag case
            else {
                rotateLeft(parent);
                rotateRight(grandParent);
                splay(item);
            }
        }
        // parent is GP's RC
        else {
            // Zig-Zag
            if (parent->getLeft() == item) {
                rotateRight(parent);
                rotateLeft(grandParent);
                splay(item);
            }
            // Zig-Zig
            else {
                rotateLeft(grandParent);
                rotateLeft(parent);
                splay(item);
            }
        }
    }
    // Zig-case 
    else {
        // if item is P's LC
        if (parent->getLeft() == item) {
            rotateRight(parent);
        }
        else {
            rotateLeft(parent);
        }
        return;
    }
}

template <typename Key, typename Value, typename Comp >
void SplayTree<Key,Value,Comp>::nodeSwap( SplayNode<Key,Value>* n1, SplayNode<Key,Value>* n2)
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

template <typename Key, typename Value, typename Comp >
SplayNode<Key, Value>* SplayTree<Key,Value,Comp>::findSuccessor(SplayNode<Key, Value> *n)
{
    if (n->getRight() != NULL) {
        n = n->getRight();
        while (n->getLeft() != NULL) {
            n = n->getLeft();
        }
        return n;
    }

    SplayNode<Key, Value> *node_parent = n->getParent();
    while ((node_parent != NULL) && (n == node_parent->getRight())) {
        n = node_parent;
        node_parent = node_parent->getParent();
    }
    return node_parent;
}

template <typename Key, typename Value, typename Comp >
void SplayTree<Key,Value,Comp>::SplayTreePrint() 
{
    this->print();
}  

#endif