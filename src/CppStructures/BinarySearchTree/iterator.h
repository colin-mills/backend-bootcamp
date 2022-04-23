/*
 * iterator.h
 */


#ifndef iterator_h
#define iterator_h

//#define DEBUG_ITERATOR



#include "treenode.h"
#include "position.h"
#include "bstree.h"

using namespace std;

template <typename> class Position; // required forward declarations
template <typename> class BSTree;

// Inorder iterator

template <typename T>
class Iterator {
    

  friend class Position<T>;
  friend class BSTree<T>;

  public:
    Iterator();
    Iterator( const Iterator<T> & );
    Iterator( const Position<T> & );
    ~Iterator() {v = nullptr;}
    const T &operator*(); // throws IllegalState
    Iterator<T> &operator++( int ); // throws IllegalState and NoSuchObject
    bool operator==( const Iterator & ) const;
    bool operator!=( const Iterator & ) const;
    bool empty() const {return (v == nullptr);}
    const T& getObj() const {return v->object;}

  private:
    TreeNode<T> *v;

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
    
#ifdef DEBUG_ITERATOR
    std::cout << "Exiting default constructor Iterator<T>" << endl;
#endif
}//END Constructor

/**********************************
 *                                *
 *      Itr copy constructor      *
 *                                *
 **********************************/
//Iterator( const Position<T> & );
template <class T>
Iterator<T>::Iterator(const Iterator<T> & otherIt)
{
#ifdef DEBUG_ITERATOR
    std::cout << "Entered position constructor Iterator<T>" << endl;
#endif
    
    v = otherIt.v;
    
    
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
    
    
#ifdef DEBUG_ITERATOR
    std::cout << "Exiting position constructor Iterator<T>" << endl;
#endif
}//END position Constructor

/**********************************
 *                                *
 *       Itr overloaded *         *
 *                                *
 **********************************/
//const T &operator*(); // throws IllegalState
template <class T>
const T& Iterator<T>::operator*()
{
#ifdef DEBUG_ITERATOR
    std::cout << "Entered overloaded * Iterator<T>" << endl;
#endif
    
    if (v == nullptr)
        throw IllegalState("Position<T>::operator*(): v is set to nullPtr");
    if (v->parent == nullptr)
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
    
    TreeNode<T> *w = v->rightPtr;
    
    if (w != nullptr)
    {
        while (w != nullptr)
        {
            v = w;
            w = w->leftPtr;
        }//While w not null
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
            
            if (w->parent == nullptr) //w == nullptr || 
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
    
    if (empty() || otherIt.empty())
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

    if (empty() || otherIt.empty())
        throw IllegalState("Position<T>::operator!=: v is set to nullPtr");
    
    return v != otherIt.v;
    
#ifdef DEBUG_ITERATOR
    std::cout << "Exiting overloaded != Iterator<T>" << endl;
#endif
    
}//END overloaded !=

#endif //iterator_h
