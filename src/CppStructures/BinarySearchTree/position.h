/*
 * position.h
 */

#ifndef position_h
#define position_h

#include "bstree.h"
#include "iterator.h"
#include "exceptions.h"

//#define DEBUG_POSITION

using namespace std;

template <typename T> class BSTree;   // required forward declarations
template <typename T> class Iterator;

template <typename T>
class Position {

  friend class BSTree<T>;
    friend class Iterator<T>;

  public:
    Position(TreeNode<T>* = nullptr);
    const T &operator*() const; // throws IllegalState
    const T& getObj () {return node->object;}

  private:
    TreeNode<T> *node;

    
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
Position<T>::Position(TreeNode<T>* otherNode)
{
#ifdef DEBUG_NODE
    std::cout << "Entered default constructor Position<T>" << endl;
#endif
    
    node = otherNode;
    
#ifdef DEBUG_NODE
    std::cout << "Exiting default constructor Position<T>" << endl;
#endif
}//END Constructor


/**********************************
 *                                *
 *      Position overloaded *     *
 *                                *
 **********************************/
template <typename T>
const T & Position<T>::operator*() const
{
#ifdef DEBUG_NODE
    std::cout << "Entered Overloaded * in Position<T>" << endl;
#endif
    
    if (node == nullptr)
        throw IllegalState("Position<T>::operator*(): node is set to nullPtr");
    else
        return node->object;
    
#ifdef DEBUG_NODE
    std::cout << "Exiting Overloaded * in Position<T>" << endl;
#endif
}//END overloaded *


#endif //position_h
