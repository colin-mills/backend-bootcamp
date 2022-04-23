/*
 * iterator.h
 * Copyright (c) 2020 Mark Maloof.  All Rights Reserved.  See LICENSE.
 */


#ifndef iterator_h
#define iterator_h

//#define DEBUG_ITERATOR



#include "rbnode.h"
#include "position.h"
#include "rbtree.h"

using namespace std;

template <typename> class Position; // required forward declarations
template <typename> class RBTree;

// Inorder iterator (GTM, p. 434)

template <typename T>
class Iterator {
    
    
    friend class Position<T>;
    friend class RBTree<T>;
    
public:
    Iterator();
    Iterator( const Iterator<T> & );
    Iterator( const Position<T> & );
    const T &operator*(); // throws IllegalState and NoSuchObject
    Iterator<T> &operator++( int ); // throws IllegalState and NoSuchObject
    bool operator==( const Iterator & ) const; // throws IllegalState
    bool operator!=( const Iterator & ) const; // throws IllegalState
    
    bool illegal() const {return (v == nullptr);}
    const T& getObj() const {return v->object;}
    
private:
    RBNode<T> *v;
    RBNode<T> *s; // pointer to RBTree<T>::sentinel
    
}; // Iterator<T> class

//Iterator();


/**********************************
 *                                *
 *    Itr default constructor     *
 *                                *
 **********************************/
template <class T>
Iterator<T>::Iterator()
{
#ifdef DEBUG_ITERATOR
    std::cout << "Entered default constructor Iterator<T>" << endl;
#endif
    
    v = nullptr;
    s = nullptr;
    
#ifdef DEBUG_ITERATOR
    std::cout << "Exiting default constructor Iterator<T>" << endl;
#endif
}//END Constructor

/**********************************
 *                                *
 *      Itr copy constructor      *
 *                                *
 **********************************/
//Iterator( const Iterator<T> & );
template <class T>
Iterator<T>::Iterator(const Iterator<T> & otherIt)
{
#ifdef DEBUG_ITERATOR
    std::cout << "Entered position constructor Iterator<T>" << endl;
#endif
    
    v = otherIt.v;
    s = otherIt.s;
    
#ifdef DEBUG_ITERATOR
    std::cout << "Exiting position constructor Iterator<T>" << endl;
#endif
}//END position Constructor

/**********************************
 *                                *
 *    Itr position constructor    *
 *                                *
 **********************************/
//Iterator( const Position<T> & );
template <class T>
Iterator<T>::Iterator(const Position<T> & otherPosition)
{
#ifdef DEBUG_ITERATOR
    std::cout << "Entered position constructor Iterator<T>" << endl;
#endif
    
    v = otherPosition.node;
    s = otherPosition.s;
    
    
#ifdef DEBUG_ITERATOR
    std::cout << "Exiting position constructor Iterator<T>" << endl;
#endif
}//END position Constructor

/**********************************
 *                                *
 *       Itr overloaded *         *
 *                                *
 **********************************/
//const T &operator*(); // throws IllegalState and NoSuchObject
template <class T>
const T& Iterator<T>::operator*()
{
#ifdef DEBUG_ITERATOR
    std::cout << "Entered overloaded * Iterator<T>" << endl;
#endif
    
    if (v == nullptr)
        throw IllegalState("Position<T>::operator*(): v is set to nullPtr");
    else if (v == s)
        throw IllegalState("Position<T>::operator*(): v is set to sentinel node");
    else if (v->parent == nullptr)
        throw NoSuchObject("Position<T>::operator*(): v is pointing to SuperRoot");
    else
        return v->object;
    
    
#ifdef DEBUG_ITERATOR
    std::cout << "Exiting overloaded * Iterator<T>" << endl;
#endif
}//END overloaded *

/**********************************
 *                                *
 *      Itr overloaded ++         *
 *                                *
 **********************************/
//Iterator<T> &operator++( int ); // throws IllegalState and NoSuchObject
//postfix increment operator
template <class T>
Iterator<T>& Iterator<T>::operator++(int)
{
#ifdef DEBUG_ITERATOR
    std::cout << "Entered overloaded ++ Iterator<T>" << endl;
#endif
    
    if (v == nullptr)
        throw IllegalState("Iterator<T>::operator++(int): v is pointing to nullptr");
    else if (v == s)
        throw IllegalState("Position<T>::operator*(): v is set to sentinel node");
    
    RBNode<T> *w = v->rightPtr;
    
    if (w != s)
    {
        while (w != s)
        {
            v = w;
            w = w->leftPtr;
        }//While w not at sentinel
    }//If W not null
    else
    {
        w = v->parent;
        if (w != nullptr)
        {
            while (v == w->rightPtr)
            {
                v = w;
                w = w->parent;
            }//Iterate up tree
            v = w;
            
            if (w->parent == nullptr) //w == nullptr
                throw NoSuchObject("Iterator<T>::operator++(int): v has reached superRoot");
        }//If not already at superroot
    }//Else it is the left ptr
    
    
#ifdef DEBUG_ITERATOR
    std::cout << "Exiting overloaded ++ Iterator<T>" << endl;
#endif
    
    return *this;
}//END overloaded ++

/**********************************
 *                                *
 *      Itr overloaded ==         *
 *                                *
 **********************************/
//bool operator==( const Iterator & ) const; //Throws IllegalState
template <class T>
bool Iterator<T>::operator==(const Iterator & otherIt) const
{
#ifdef DEBUG_ITERATOR
    std::cout << "Entered overloaded == Iterator<T>" << endl;
#endif
    
    if (illegal() || otherIt.illegal())
        throw IllegalState("Position<T>::operator==: v is set to nullPtr");
    
    return v == otherIt.v;
    
#ifdef DEBUG_ITERATOR
    std::cout << "Exiting overloaded == Iterator<T>" << endl;
#endif
}//END overlaoded ==


/**********************************
 *                                *
 *      Itr overloaded !=         *
 *                                *
 **********************************/
//bool operator!=( const Iterator & ) const; //Throws IllegalState
template <class T>
bool Iterator<T>::operator!=(const Iterator & otherIt) const
{
#ifdef DEBUG_ITERATOR
    std::cout << "Entered overloaded != Iterator<T>" << endl;
#endif
    
    if (illegal() || otherIt.illegal())
        throw IllegalState("Position<T>::operator!=: v is set to nullPtr");
    
    return v != otherIt.v;
    
#ifdef DEBUG_ITERATOR
    std::cout << "Exiting overloaded != Iterator<T>" << endl;
#endif
    
}//END overloaded !=

#endif //iterator_h
