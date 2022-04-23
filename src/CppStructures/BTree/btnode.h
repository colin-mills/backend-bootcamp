//
//  btnode.h
//  project3
//
//  Created by Colin Mills on 10/21/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//

#ifndef btnode_h
#define btnode_h

//nescesary namespace
using namespace std;

template <typename K>
class BTNode {
    
public:
    BTNode( size_t t = 2 );
    ~BTNode();
    bool isFull() const {return n == maxKeys;}
    bool isInternal() const {return (!leaf);} // instead of "is not leaf."
    size_t nChildren() const {return (n+1);}
    void splitChild( const size_t i );
    void printKeys();
    
//private:
    size_t t;  // order
    size_t n;  // number of keys in this node (Cormen uses n)
    size_t maxKeys; //maximum keys allowed based off of order (2t-1)
    bool leaf;
    K *keys; //Dynamically allocated 2t-1 keys
    BTNode<K> **children; // allocate same way as hash table bucket array
    
}; // BTNode<K> class

/**********************************
 *                                *
 *    NODE default constructor    *
 *                                *
 **********************************/
template <typename K>
BTNode<K>::BTNode(size_t t)
{
    this->t = t; 
    n = 0;
    maxKeys = (2 * t) - 1;
    leaf = true;
    
    //Set up arrays
    keys = new K[maxKeys];
    children = new BTNode<K>*[(2 * t)];
    for (size_t i = 0; i < (2*t); i++) //set all node pointers to null
    {
        children[i] = nullptr;
    }//FOR initialize to null
}//END default contructor

/**********************************
 *                                *
 *         NODE destructor        *
 *                                *
 **********************************/
template <typename K>
BTNode<K>::~BTNode()
{
    
    delete[] keys;
    delete[] children; 
    //TODO: dangling pointers?
}//END destructor

/**********************************
 *                                *
 *        NODE split child        *
 *                                *
 **********************************/
template <typename K>
void BTNode<K>::splitChild(const size_t i)
{
    
    BTNode<K> *z = new BTNode<K>(t);
    BTNode<K> *y = children[i];
    
    z->leaf = y->leaf;
    z->n = t-1;
    
    for (size_t j = 0; j < (t-1); j++)
    {
        z->keys[j] = y->keys[j+t];
    }//For second half of keys
    
    if (y->isInternal()) //adjust children nodes
    {
        for (size_t j = 0; j < (t); j++)
        {
            z->children[j] = y->children[j+t];
        }//For second half of children
    }//If internal
    
    y->n = t-1;
    
    for (size_t j = n; j > i; j--)
    {
        children[j+1] = children[j];
    }//For moving children of parent over
    
    children[i+1] = z;
    
    if (n != 0)
    {
    for (size_t j = n ; j > i; j--)
        {
            keys[j] = keys[j-1];
        }//For moving keys of parent over
    }//If n is not 0
    //Move up key
    keys[i] = y->keys[t-1];
    n = n+1;
    
}//END splitChild

/**********************************
 *                                *
 *         NODE print keys        *
 *                                *
 **********************************/

template <typename K>
void BTNode<K>::printKeys()
{
    //cout << "Is this node internal? " << isInternal() << endl;
    for (size_t i = 0; i < n; i++)
    {
        cout << "Key " << i << " is " << keys[i] << endl;
        
    }//For keys in key
}//END destructor

#endif /* btnode_h */
