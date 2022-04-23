/*
 * position.h
 */

#ifndef position_h
#define position_h

#include "rbtree.h"
#include "iterator.h"
#include "exceptions.h"

//#define DEBUG_POSITION

using namespace std;

template <typename T> class RBTree;   // required forward declarations
template <typename T> class Iterator;

template <typename T>
class Position {
    
    friend class RBTree<T>;
    friend class Iterator<T>;
    
public:
    Position(RBNode<T>* otherNode= nullptr, RBNode<T>* sentinel= nullptr);
    const T &operator*() const; // throws IllegalState and NoSuchObject
    const T& getObj () {return node->object;}
    
private:
    RBNode<T> *node;
    RBNode<T> *s;   // pointer to RBTree<T>::sentinel    
    
}; // Position<T> class

/*************************************************************************************************
 ***************************Position CONSTRUCTOR FUNCTION*****************************************
 *************************************************************************************************/

/**********************************
 *                                *
 *  Position default constructor  *
 *                                *
 **********************************/
template <typename T>
Position<T>::Position(RBNode<T>* otherNode, RBNode<T>* sentinel)
{
#ifdef DEBUG_NODE
    std::cout << "Entered default constructor Position<T>" << endl;
#endif
    
    node = otherNode;
    s = sentinel;
    
#ifdef DEBUG_NODE
    std::cout << "Exiting default constructor Position<T>" << endl;
#endif
}//END Constructor


/**********************************
 *                                *
 *      Position overloaded *     *
 *                                *
 **********************************/
//Throws illegal state and nosuchobject
template <typename T>
const T & Position<T>::operator*() const
{
#ifdef DEBUG_NODE
    std::cout << "Entered Overloaded * in Position<T>" << endl;
#endif
    
    if (node == nullptr)
        throw IllegalState("Position<T>::operator*(): node is set to nullPtr");
    else if (node == s)
        throw IllegalState("Position<T>::operator*(): v is set to sentinel node");
    else if (node->parent == nullptr)
        throw NoSuchObject("Position<T>::operator*(): v is pointing to SuperRoot");
    else 
        return node->object;
    
#ifdef DEBUG_NODE
    std::cout << "Exiting Overloaded * in Position<T>" << endl;
#endif
}//END overloaded *


#endif //position_h
