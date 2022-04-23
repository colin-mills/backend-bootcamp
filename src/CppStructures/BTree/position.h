//
//  position.h
//  project3
//
//  Created by Colin Mills on 10/21/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//

#ifndef position_h
#define position_h
#include "btnode.h"
#include "exceptions.h"

//nescesary namespace
using namespace std;

template <typename K> class BTree;

template <typename K>
class Position {
    
    friend class BTree<K>;
    
public:
    Position(BTNode<K>* = nullptr);
    /*
     * Since we are not storing values, operator[] should return the
     * position of the key in the node [0, n-1].
     */
    size_t operator[](const K &k) const; // throws IllegalState and NoSuchKey
    //Helpful for splitting
    
private:
    BTNode<K> *v;
    
}; // Position<K> class


/**********************************
 *                                *
 *  Position default constructor  *
 *                                *
 **********************************/
template <typename K>
Position<K>::Position(BTNode<K>* givenNode)
{

    v = givenNode;
    
}//END Constructor

/**********************************
 *                                *
 *     Position overloaded []     *
 *                                *
 **********************************/

//size_t operator[](const K &k) const; // throws IllegalState and NoSuchKey
template <typename K>
size_t Position<K>::operator[](const K& key) const
{
    
    if (v == nullptr)
        throw IllegalState("Position<T>::operator[]: node does not exist");
    
    for (size_t i = 0; i < v->n; i++)
    {
        if (key == v->keys[i])
            return i;
    }//for keys in v
    
    throw NoSuchKey("Position<T>::operator[]: key not in node");
    
}//End overloaded [] operator

#endif /* position_h */
