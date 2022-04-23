//
//  btree.h
//  project3
//
//  Created by Colin Mills on 10/21/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//

#ifndef btree_h
#define btree_h

#include "exceptions.h"
#include <exception>
#include <algorithm> //for max fxn


//nescesary namespace
using namespace std;

template <typename K>
class BTree {
    
public:
    
    
    BTree( size_t t = 2 ); // throws out_of_range for t < 2
    ~BTree();
    void clear();
    bool empty() const {return sz == 0;}
    Position<K> find( const K & ) const; // throws NoSuchKey
    size_t height() const;
    void insert( const K & ); // throws DuplicateKey
    size_t nodes() const {return nn;} // returns the number of nodes in the tree
    void remove( const K & ); // throws NoSuchKey
    size_t size() const {return sz;}
    void printTree() const;
    
private:
    BTNode<K> *root;
    size_t t;  // order
    size_t nn; // number of nodes
    size_t sz; // number of keys
    
    void clear( BTNode<K> * );
    BTNode<K> *find( BTNode<K> *, const K & ) const;
    size_t height( BTNode<K> * ) const;
    void insert( BTNode<K> *, const K & );
    void remove( BTNode<K> *, const K & ); // figures out which case
    void case1( BTNode<K> *, const K & );
    void case2( BTNode<K> *, const size_t, const K & );
    void case3( BTNode<K> *, size_t &, const K & ); // 3a, calls case3b
    void case3b( BTNode<K> *, size_t &, const K & );
    K removeImmediatePredecessor( BTNode<K> *, const K & );
    K removeImmediateSuccessor( BTNode<K> *, const K & );
    void printTree(BTNode<K> *) const;
    
}; // BTree class

/***********************************************************************************************
 ******************************BST CONTRUCTING FUNCTIONS*****************************************
 ***********************************************************************************************/

//BTree( size_t t = 2 ); // throws out_of_range for t < 2
template <typename K>
BTree<K>::BTree(size_t t)
{
    if (t < 2)
        throw out_of_range("BTree<K>::BTree: below minimum order.");
    this->t = t;
    nn = 1;
    sz = 0;
    
    root = new BTNode<K>(t); //default state is empty leaf node
    
}//END constructor

//~BTree();
template <typename K>
BTree<K>::~BTree()
{
    clear();
    delete root;
    root = nullptr;
}//END destructor

/***********************************************************************************************
 *****************************BST PUBLIC MEMBER FUNCTIONS****************************************
 ***********************************************************************************************/

//void clear();
template <typename K>
void BTree<K>::clear()
{
    if (!empty())
    {
        if (!root->leaf)
        {
            for (size_t i = 0; i < root->nChildren() ; i++)
                clear(root->children[i]);
        }//If root is not leaf
        
        //delete root->leftPtr;
        
        nn = 1;
        sz = 0;
    }//END if not empty
    
    //delete root; //this is done in destructor
}//END clear()

//Position<K> find( const K & ) const; // throws NoSuchKey
template <typename K>
Position<K> BTree<K>::find(const K & key) const
{
    if (empty())
        throw NoSuchKey("BTree<K>::find(): tree is empty");
    BTNode<K>* z;
    z = find(root, key); //Call recursive search
    
    if (z == nullptr) //If not found
        throw NoSuchKey("BTree<K>::find(): Key was not found in tree");
    else
    {
        //Encapsulate node
        Position<K> foundKey(z);
        return foundKey;
        
    }//Else key found
}//END find(key)

//size_t height() const;
template <typename K>
size_t BTree<K>::height() const
{
    if (empty() || root->leaf)
        return 0;
    
    size_t h = 0;
    
    for (size_t i = 0; i < root->nChildren(); i++)
    {
        h = max(h, height(root->children[i]));
    }//for each child of root
    
    return h+1;
}//END height()

//void insert( const K & ); // throws DuplicateKey
template <typename K>
void BTree<K>::insert(const K & key)
{
    
    if (root->isFull())
    {
        BTNode<K> *s = new BTNode<K>(t);
        nn++; //new node
        s->leaf = false; //new root is not a leaf node
        
        s->children[0] = root;
        root = s;
        
        //Move up middle and split old root
        s->splitChild(0);
        nn++;
    }//If root is full make new node and split old root as child
    
    //recursively call
    insert(root, key);
        
}//END insert(key)

//void remove( const K & ); // throws NoSuchKey
template <typename K>
void BTree<K>::remove(const K & key)
{
    if (empty())
        throw NoSuchKey("remove(const K & key): Tree is empty");
    
    remove(root, key);
    
}//END remove

template <typename K>
void BTree<K>::printTree() const
{
    cout << "PRINTING TREE" << endl;
    cout << "NODES: " << nn << " KEYS: " << sz << endl;
    printTree(root);
}//END print root
/***********************************************************************************************
 *****************************BST PRIVATE MEMBER FUNCTIONS****************************************
 ***********************************************************************************************/

template <typename K>
void BTree<K>::clear(BTNode<K>* node)
{
    if (node->isInternal())
    {
        for (size_t i = 0; i<node->nChildren() ; i++)
        {
            clear(node->children[i]);
        }//END for
    }//END if not leaf
    
    delete node;
    node = nullptr;
    
    //delete root; //this is done in destructor
}//END clear()

template <typename K>
BTNode<K> * BTree<K>::find( BTNode<K> * searchNode, const K & key) const
{
    size_t i = 0;

    //iterate i until at end or if passed key
    while (i < searchNode->n && key > searchNode->keys[i])
        i++;
    
    if (searchNode->n && key == searchNode->keys[i])
        return searchNode;
    else if (searchNode->leaf)
        throw NoSuchKey("find( BTNode<K> * searchNode, const K & key): Key not found");
    else
        searchNode = find(searchNode->children[i], key);
    
    //If its a match
    return searchNode;
    
}//END find(key)

template <typename K>
size_t BTree<K>::height(BTNode<K>* node) const
{
    if (node->leaf)
        return 0;
    
    size_t h = 0;
    
    for (size_t i = 0; i < node->nChildren(); i++)
    {
        h = max(h, height(node->children[i]));
    }//for each child of root
    
    return h+1;
}//END height()

//void insert( BTNode<K> *, const K & );
template <typename K>
void BTree<K>::insert(BTNode<K> * x, const K & k)
{

    size_t i = 0;
    
    if (x->leaf)
    {
        //iterate i until at end or if passed key
        while (i < x->n && k > x->keys[i])
            i++;
        
        //If its a match
        if (i < x->n && k == x->keys[i])
            throw DuplicateKey("insert(BTNode<K> * x, const K & k): Key already in tree");
        
        i = x->n;
        
        while (i >= 1 && k < x->keys[i-1])
        {
            x->keys[i] = x->keys[i-1];
            i--;
        }//While not at end or key is smaller
        
        x->keys[i] = k;
        x->n = x->n+1;
        sz++;
    }//If leaf insert
    else
    {
        i = x->n;
        i--;
        //find child
        while (i >= 0 && k < x->keys[i])
            i--;
        
        i = i+1;
        
        if (x->children[i]->isFull())
        {
            x->splitChild(i);
            nn++;
            if (k > x->keys[i]) //if it should go to right of new key
                i++;
        }//if child is full
        //pass child recursively
        insert(x->children[i], k);
    }//Else determine correct child and determine if full
    
}//END insert(BTNode<K> *, const K & )

//void remove( BTNode<K> *, const K & ); // figures out which case
template <typename K>
void BTree<K>::remove( BTNode<K> * node, const K & key)
{
    if (node->leaf)
    {
        if (node->n == 1 && node == root)
        {
            node->n = (node->n-1);
            sz--;
            
        }//If last key in root
        else
            case1(node, key);
    }//If leaf node
    else
    {
        size_t i = 0;
        
        //iterate i until at end or if passed key
        while (i < node->n && key > node->keys[i])
            i++;
        
        //If its in this node
        if (i < node->n && key == node->keys[i])
            case2(node, i, key);//Case 2
        else //look at its child
        {
            if ((node->children[i])->n == t-1)
            {
                case3(node, i, key);//case 3s
            }//If case 3
            else
                remove(node->children[i], key); //recurse on child
        }//else do appropriate recursions on child
    }//Else node is internal
}//END remove( BTNode<K> *, const K & )

//void case1( BTNode<K> *, const K & );
template <typename K>
void BTree<K>::case1( BTNode<K> * node, const K & key)
{
    size_t i = 0;
    
    //iterate i until at end or if passed key
    while (i < node->n && key != node->keys[i])
        i++;
    
    //If its in this node
    if (i < node->n && key == node->keys[i])
    {
        while (i < (node->n)-1)
        {
            node->keys[i] = node->keys[i+1];
            i++;
        }//shift over keys
    
    node->n = node->n-1;
    sz--;
    }//if it is in the node
    else //Only other place that calls no such key, b/c algorithm will try to find unil a leaf node
        throw NoSuchKey("case1( BTNode<K> * node, const K & key): In leaf node and key is not found.");
}//END case1

//void case2( BTNode<K> *, const size_t, const K & );
template <typename K>
void BTree<K>::case2( BTNode<K> * node, const size_t i, const K & key)
{

    K promoteKey;
    
    if ((node->children[i])->n >= t)
    {
        //Promote predecessor will handle any case 3s if child is also internal
        promoteKey = removeImmediatePredecessor(node->children[i], key);
        node->keys[i] = promoteKey;
    }// if case 2a
    else if ((node->children[i+1])->n >= t)
    {
        //Promote predecessor will handle any case 3s if child is also internal
        promoteKey = removeImmediateSuccessor(node->children[i+1], key);
        node->keys[i] = promoteKey;
    }// if case 2b
    else
    {
        BTNode<K>* y = node->children[i];
        BTNode<K>* z = node->children[i+1];
        
        for (size_t iChild  = 0; iChild  < z->n ; iChild ++) //Merge z into y
            y->keys[iChild + y->n] = z->keys[iChild];
        
        //adjust number keys in y
        //will always be t for case 2c
        y->n = t;
        
        //unhook and delete
        node->children[i+1] = nullptr;
        delete z;
        nn--;
        
        if (node == root && node->n == 1)
        {
            delete root;
            nn--;
            root = y;
            sz--;
            node = root;
        }//if node is root
        else
        {
            for (size_t iKey = i; iKey < node->n ; iKey++)
            {
                node->keys[iKey] = node->keys[iKey+1];
                node->children[iKey+1] = node->children[iKey+2];
            }//For shift over keys and children
        
        
            node->children[(node->n)+1] = nullptr;
            node->n = (node->n)-1;
            sz--;
        }//Else normal case
        
    }// else case 2c
    
}//END case 2

//void case3( BTNode<K> *, size_t &, const K & ); // 3a, calls case3b
template <typename K>
void BTree<K>::case3( BTNode<K> * node, size_t & i, const K & key)
{
    BTNode<K> * sibling = nullptr;
    BTNode<K> * child = node->children[i];
    if (i > 0 && node->children[i-1]->n >= t)
    {
        sibling = node->children[i-1];

        
        //make room for drop key b/c left sibling will be min key
        for (size_t iKey = child->n; iKey > 0; iKey--)
        {
            child->keys[iKey] = child->keys[(iKey-1)];
        }//Move over children for swap key
        
        //and drop down key
        child->keys[0] = node->keys[i-1];
        child->n = (child->n)+1;
        
        //make room for new child
        for (size_t iChild = child->n; iChild > 0; iChild--)
        {
            child->children[iChild] = child->children[iChild-1];
        }//Move over children for swap node
        
        //swap node
        child->children[0] = sibling->children[sibling->n];
        sibling->children[child->n] = nullptr;
        
        //now promote sibling key
        sibling->n = (sibling->n)-1;
        node->keys[i-1] = sibling->keys[sibling->n];

        remove(node->children[i], key);
    }//if look left
    else if (i < (node->n) && node->children[i+1]->n >= t)
    {
        sibling = node->children[i+1];
        
            
        //drop down key to child
        child->keys[child->n] = node->keys[i];
        child->n = (child->n)+1;
        
        //swap sibling child node
        child->children[child->n] = sibling->children[0];
        sibling->children[0] = nullptr;
        
        //now promote sibling key
        node->keys[i] = sibling->keys[0];
        sibling->n = (sibling->n)-1;
        
        //shift over sibling keys
        //shift over sibling children
        for (size_t iKey = 0; iKey < sibling->n ; iKey++)
        {
            sibling->keys[iKey] = sibling->keys[iKey+1];
            sibling->children[iKey] = sibling->children[iKey+1];
        }//For shift over keys and children
        
        //last shift for child nodes
        sibling->children[sibling->n] = sibling->children[(sibling->n)+1];
        remove(node->children[i], key);
        
    }//Else look right
    else
    {
        case3b(node, i, key);
    }//case 3b
    
    sibling = child = nullptr;
}//END case 3

//void case3b( BTNode<K> *, size_t &, const K & );
template <typename K>
void BTree<K>::case3b( BTNode<K> * node , size_t & i, const K & key)
{
    
    
    
    BTNode<K> * sibling = nullptr;
    BTNode<K> * child = node->children[i];
    
    if (i > 0)
    {
        //merging into the sibling
       sibling = node->children[i-1];
        
        //Add parent key down to sibling
        sibling->keys[sibling->n] = node->keys[i-1];
        sibling->n = (sibling->n) + 1;
        
        
        
        for (size_t iChild = 0; iChild < child->n ; iChild ++) //Merge child into sibling
            sibling->keys[iChild + sibling->n] = child->keys[iChild];
        
        
            for (size_t iChild = 0; iChild < child->nChildren() ; iChild ++) //merge children in sibling
            {
                sibling->children[iChild + sibling->n] = child->children[iChild];
                child->children[iChild] = nullptr;
            }//for children merge
        
        //adjust number keys in sibling
        //will always be t+1 for case 3b
        sibling->n = t+1;
        
        //unhook and delete
        node->children[i] = nullptr;
        delete child;
        nn--;
        
        if (node == root && node->n == 1)
        {
            delete root;
            nn--;
            root = sibling;
            node = root;
            //iterate i until at end or if passed key
            while (i < node->n && key > node->keys[i])
                i++;
            remove(node->children[i], key);
        }//if node is root
        else
        {
            node->n = (node->n)-1;
            for (size_t iKey = i-1; iKey < node->n ; iKey++)
            {
                node->keys[iKey] = node->keys[iKey+1];
                node->children[iKey+1] = node->children[iKey+2];
            }//For shift over keys and children
        
        
            node->children[(node->n)+1] = nullptr;
        }//Else normal case
    }//if merge left
    else
    {
        sibling = node->children[i+1];
        
        //Add parent key down to child
        child->keys[child->n] = node->keys[i];
        child->n = (child->n) + 1;
        
        for (size_t iSib = 0; iSib < sibling->n ; iSib ++) //Merge sibling into child
            child->keys[iSib + child->n] = sibling->keys[iSib];
        
        for (size_t iSib = 0; iSib < sibling->nChildren() ; iSib ++) //merge children to child
        {
            child->children[iSib + child->n] = sibling->children[iSib];
            sibling->children[iSib] = nullptr;
        }//for children merge
        
        //adjust number keys in sibling
        //will always be t+1 for case 3b
        child->n = t+1;
        
        //unhook and delete
        node->children[i+1] = nullptr;
        delete sibling;
        nn--;
        
        if (node == root && node->n == 1)
        {
            delete root;
            nn--;
            root = child;
            node = root;
            
            //iterate i until at end or if passed key
            while (i < node->n && key > node->keys[i])
                i++;
            remove(node->children[i], key);
        }//if node is root
        else
        {
            node->n = (node->n)-1;
            for (size_t iKey = i; iKey < node->n ; iKey++)
            {
                node->keys[iKey] = node->keys[iKey+1];
                node->children[iKey+1] = node->children[iKey+2];
            }//For shift over keys and children
        
            node->children[(node->n)+1] = nullptr;
            remove(node->children[i], key);
        }//else normal case
    }//Else merge right
    
    sibling = child = nullptr;
}//END case 3b

//K removeImmediatePredecessor( BTNode<K> *, const K & );
template <typename K>
K BTree<K>::removeImmediatePredecessor( BTNode<K> * node, const K & key)
{
    K predecessor;
    if (node->leaf)
    {
        predecessor = node->keys[(node->n)-1];
        case1(node, predecessor);
        return predecessor;
    }//if leaf node
    else
    {
        size_t i = 0;
        
        //iterate i until at end or if passed key
        while (i < node->n && key > node->keys[i])
            i++;
        
        //Recurse down
        if ((node->children[i])->n == t-1)
        {
            case3(node, i, key);//case 3s
            i--;
        }//If case 3 called
        
        
        predecessor = removeImmediatePredecessor(node->children[i], key); //recurse on child
        
    }//Else node is internal and need to keep looking
    
    return predecessor;
    
}//END removeImmediatePredecessor( BTNode<K> *, const K & )

//K removeImmediateSuccessor( BTNode<K> *, const K & );
template <typename K>
K BTree<K>::removeImmediateSuccessor( BTNode<K> * node, const K & key)
{
    K predecessor;
    if (node->leaf)
    {
        predecessor = node->keys[0];
        case1(node, predecessor);
        return predecessor;
    }//if leaf node
    else
    {
        size_t i = 0;
        
        //iterate i until at end or if passed key
        while (i < node->n && key > node->keys[i])
            i++;
        
        //Recurse down
        if ((node->children[i])->n == t-1)
            case3(node, i, key);//case 3s
        
        predecessor = removeImmediatePredecessor(node->children[i], key); //recurse on child
        
    }//Else node is internal
    
    return predecessor;
    
}//END removeImmediateSuccessor( BTNode<K> *, const K & )

//void printTree(BTNode<K> *) const;
template <typename K>
void BTree<K>::printTree(BTNode<K> * node) const
{
    if (node->leaf)
    {
        cout << "Printing leaf node: " << endl;
        node->printKeys();
    }//If leaf
    else
    {
        cout << "Printing internal node with #children= " << node->nChildren() << endl;
        node->printKeys();
        for (size_t i = 0; i < node->nChildren(); i++)
            printTree(node->children[i]);
        
    }//else internal
}//END print tree

#endif /* btree_h */
