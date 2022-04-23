/*
 * rbtree.h
 */

#ifndef rbtree_h
#define rbtree_h

//#define DEBUG_BST

#include "iterator.h"
#include "rbnode.h"
#include "position.h"

#include <list>
#include <algorithm> //for max fxn


using namespace std;

template <typename T>
class RBTree {
    
public:
    RBTree();
    RBTree( const RBTree<T> & );
    ~RBTree();
    Iterator<T> begin() const;
    void clear();
    bool empty() const {return (root->leftPtr == sentinel);}
    Iterator<T> end() const;
    Position<T> find( const T & foundNode) const ; // throws NoSuchObject
    int height() const {return height(root->leftPtr);}
    void insert( const T & placeObj);
    const RBTree<T> &operator=( const RBTree<T> & rhsTree);
    T remove( const T & ); // throws NoSuchObject
    list< Position<T> > preorderToList() const {return preorderToList(root->leftPtr);}
    
private:
    RBNode<T> *root; // points to super root (GTM, p. 435)
    RBNode<T> *sentinel; // points to the black sentinel/external node

    
    int height( RBNode<T> *node ) const;
    void clear( RBNode<T> * ); // use a post-order traversal
    RBNode<T> *copy( RBNode<T> *node ); // use a post-order traversal
    RBNode<T> *find( RBNode<T> *, const T & ) const;
    RBNode<T> *getMinNode( RBNode<T> * ) const;
    RBNode<T>* insert( RBNode<T> *, const T & ); // throws DuplicateObject

    void removeNodeWithFewerThanTwoChildren( RBNode<T> * );
    void removeNodeWithTwoChildren( RBNode<T> * );
    list< Position<T> > preorderToList( RBNode<T> * ) const;
    
    //New functions to implement red balck tree
    RBNode<T>* restructure(RBNode<T>* x);
    void remedyDoubleRed(RBNode<T>* z);
    RBNode<T>* getSibling(RBNode<T>* ) const;
    void recolorOrRemedy(RBNode<T>* x, RBNode<T>* r, Color c);
    void remedyDoubleBlack(RBNode<T>* x, RBNode<T>* r);
    
}; // RBTree<T> class

/***********************************************************************************************
 ******************************BST CONTRUCTING FUNCTIONS*****************************************
 ***********************************************************************************************/
template <typename T>
RBTree<T>::RBTree()
{
#ifdef DEBUG_BST
    std::cout << "Entered Default Contructor" << std::endl;
#endif
    
    
    //Sentinel node is a BLACK external node
    sentinel = new RBNode<T>;
    sentinel->color = BLACK;
    //Initialize new superRoot
    //Sets left and right ptr to sentinel and parent to nullptr
    root = new RBNode<T>(T(), nullptr, sentinel);
    
#ifdef DEBUG_BST
    std::cout << "Exiting Default Contructor" << std::endl;
#endif
}//END default contructor


template <typename T>
RBTree<T>::RBTree(const RBTree<T> & otherTree)
{
#ifdef DEBUG_BST
    std::cout << "Entered Copy Contructor" << std::endl;
#endif
    
    
    sentinel = new RBNode<T>;
    sentinel->color = BLACK;
    root = new RBNode<T>(T(), nullptr, sentinel);
    
    //makes equal with overloaded equality operator
    *this = otherTree;
    
#ifdef DEBUG_BST
    std::cout << "Exiting Copy Contructor" << std::endl;
#endif
}//END copy contructor

template <typename T>
RBTree<T>::~RBTree()
{
#ifdef DEBUG_BST
    std::cout << "Entered Destructor" << std::endl;
#endif
    
    if (!empty())
        clear(); //clear and delete all nodes
    
    delete root; //delete dynamically allocated super root
    delete sentinel; //delete dynamically allocated sentinel
    root = nullptr;
    sentinel = nullptr; //fix last pointer
    
#ifdef DEBUG_BST
    std::cout << "Exiting Destructor" << std::endl;
#endif
}//END Destructor

/***********************************************************************************************
 *****************************BST PUBLIC MEMBER FUNCTIONS****************************************
 ***********************************************************************************************/
//Creates and returns iterator to min node of tree
//uses getMinNode
template <typename T>
Iterator<T> RBTree<T>::begin() const
{
#ifdef DEBUG_BST
    std::cout << "Entered Begin" << std::endl;
#endif
    
    Iterator<T> it;
    it.v = getMinNode(root);
    it.s = sentinel;
    
#ifdef DEBUG_BST
    std::cout << "Exiting Begin" << std::endl;
#endif
    
    return it;
}//END Begin

template <typename T>
void RBTree<T>::clear()
{
#ifdef DEBUG_BST
    std::cout << "Entered Clear" << std::endl;
#endif
    
    clear(root->leftPtr);
    root->leftPtr = sentinel;
    
#ifdef DEBUG_BST
    std::cout << "Exiting Clear" << std::endl;
#endif
}//END Begin

//Creates iterator and sets it to super root
template <typename T>
Iterator<T> RBTree<T>::end() const
{
#ifdef DEBUG_BST
    std::cout << "Entered End" << std::endl;
#endif
    
    Iterator<T> endIt;
    endIt.v = root;
    endIt.s = sentinel;
    
    
#ifdef DEBUG_BST
    std::cout << "Exiting End" << std::endl;
#endif
    
    return endIt;
}//END End

template <typename T>
Position<T> RBTree<T>::find( const T & foundNode) const //Throws NSO
{
    RBNode<T>* node = find(root->leftPtr, foundNode);
    
    if (node == sentinel)
        throw NoSuchObject("RBTree<T>::find( const T & foundNode): Node not found");
    
    Position<T> pos(node, sentinel);
    
    return pos;
    
}
//^ throws NoSuchObject
// throws DuplicateObject
//void insert( const T & placeObj);
template <typename T>
void RBTree<T>::insert( const T & placeObj)
{
#ifdef DEBUG_BST
    std::cout << "Entered public insert" << std::endl;
#endif
    
    RBNode<T>* z = insert(root->leftPtr, placeObj);
    
    if (z == root->leftPtr)
        z->color = BLACK;
    else
        remedyDoubleRed(z);
    
#ifdef DEBUG_BST
    std::cout << "Exiting public insert" << std::endl;
#endif
    
}//END insert


/**
 Checks to see if they are not the same
 clears if not already empty
 Checks to see if rhsTree is empty and if not it will call copy
 
 @param rhsTree other Tree that will be copied
 @return *this so it can be used with multiple chaining of =
 */
template <typename T>
const RBTree<T> & RBTree<T>::operator= ( const RBTree<T> & rhsTree)
{
#ifdef DEBUG_BST
    std::cout << "Entered Overloaded = Operator" << std::endl;
#endif
    
    if (this != &rhsTree) //if not already same
    {
        if (!empty())
            clear();
        
        if (!rhsTree.empty())
        {
            this->root->leftPtr = copy((rhsTree.root)->leftPtr);
            this->root->leftPtr->parent = root;
        }//If RHs empty and this isn't
    }
#ifdef DEBUG_BST
    std::cout << "Exiting Overloaded = Operator" << std::endl;
#endif
    
    return *this;
}//END Overloaded = Operator



/**
 throws NoSuchObject
 If not empty then it will find node and call according remove function
 Will implicitly call NoSuchObject from find
 
 @param removeNode is the node that is being searched for and deleted
 @return will return object that is deleted
 */
template <typename T>
T RBTree<T>::remove(const T & removeNode)
{
#ifdef DEBUG_BST
    std::cout << "Entered Remove" << std::endl;
#endif
    
    if (empty())
        throw NoSuchObject("RBTree<T>::remove: Cannot remove becasue tree is empty");
    
    RBNode<T>* node = (find(removeNode)).node; //Will throw NoSuchObject
    
    if (node->leftPtr == sentinel || node->rightPtr == sentinel)
        removeNodeWithFewerThanTwoChildren(node);
    else
        removeNodeWithTwoChildren(node);
    
#ifdef DEBUG_BST
    std::cout << "Exiting Remove" << std::endl;
#endif
    
    return removeNode;
}//END



/***********************************************************************************************
 *****************************BST PRIVATE MEMBER FUNCTIONS****************************************
 ***********************************************************************************************/
/**
 Recursively finds height of tree
 
 @param node this is the current node passed to method by itself
 @return returns the value
 */
template <typename T>
int RBTree<T>::height(RBNode<T> *node ) const
{
#ifdef DEBUG_BST
    std::cout << "Entered Private Height" << std::endl;
#endif
    if (node == sentinel)
        return 0;
    else
    {
        int h = 0;
        h = std::max(height(node->leftPtr), height(node->rightPtr));
#ifdef DEBUG_BST
        std::cout << "Exiting Private Height" << std::endl;
#endif
        return h + 1;
    }//ELSE recurse
    
}//END Private Height


/**
 Recursively removes the top node until empty
 @param node root node that is passed to self
 */
template <typename T>
void RBTree<T>::clear(RBNode<T> * node)
{
#ifdef DEBUG_BST
    std::cout << "Entered Private Clear" << std::endl;
#endif
    
    if (node != sentinel)
    {
        
        clear(node->leftPtr);
        clear(node->rightPtr);
        
        delete node;
        node = nullptr;
        
    }//If not at end of tree
#ifdef DEBUG_BST
    std::cout << "Exiting Private Clear" << std::endl;
#endif
}//END Private Clear

/**
 This recursively builds the tree in a preorder fashion
 
 @param node Root node of other tree
 @return return created node
 */
template <typename T>
RBNode<T>* RBTree<T>::copy(RBNode<T> *node )
{
#ifdef DEBUG_BST
    std::cout << "Entered Private Copy" << std::endl;
#endif
    
    RBNode<T>* nodeN = sentinel;
    
    if (node->leftPtr == nullptr)
    {
        nodeN = new RBNode<T>(node->object, nullptr, sentinel); //TODO: do i need to set parent?
        
        nodeN->color = node->color;
        
        nodeN->leftPtr = copy(node->leftPtr); //visit left
        nodeN->rightPtr = copy(node->rightPtr); //visit right
        
        if (nodeN->leftPtr != sentinel)
            nodeN->leftPtr->parent = nodeN;
        
        if (nodeN->rightPtr != sentinel)
            nodeN->rightPtr->parent = nodeN;
        
    }//if not at bottom of list
    
    return nodeN;
    
#ifdef DEBUG_BST
    std::cout << "Exiting Private Copy" << std::endl;
#endif
    
    
}//END Private Copy


/**
 Recursively calls until it is either found or not
 
 @param thisNode currentNode passed to self
 @param foundNode value of object
 @return Returns a ptr to the node that is found
 */
template <typename T>
RBNode<T>* RBTree<T>::find(RBNode<T> * thisNode, const T & foundNode) const
{
#ifdef DEBUG_BST
    std::cout << "Entered Private Find" << std::endl;
#endif
    
    
    if(thisNode == sentinel)
    {
        throw NoSuchObject("RBTree<T>::find(RBNode<T> * thisNode, const T & foundNode)");
    }//IF not external node
    else
    {
        if (thisNode->object > foundNode) //If less than
            return find((thisNode)->leftPtr, foundNode);
        else if (thisNode->object < foundNode) //if greater than
            return find((thisNode)->rightPtr, foundNode);
        else //just right
            return thisNode;
    }//Else recurse
    
}//END Private Find


/**
 Follows left ptr until it is the last internal node
 
 @param node starting point of subtree
 @return returns a ptr to the node that is found
 */
template <typename T>
RBNode<T>* RBTree<T>::getMinNode(RBNode<T> * node) const
{
#ifdef DEBUG_BST
    std::cout << "Entered Get Min Node" << std::endl;
#endif
    
    RBNode<T> *nextNode = node;
    
    if (!empty())
    {
        while (nextNode->leftPtr != sentinel)
        {
            nextNode = nextNode->leftPtr;
        }//While not at bottom
        
    }//if not empty
    
#ifdef DEBUG_BST
    std::cout << "Exiting Get Min Node" << std::endl;
#endif
    
    return nextNode;
}//END Get Min Node

/**
 throws DuplicateObject
 Recursively iterates until it finds place to insert
 
 @param node root of tree
 @param value to be inserted
 */
template <typename T>
RBNode<T>* RBTree<T>::insert(RBNode<T> * node, const T & value)
{
#ifdef DEBUG_BST
    std::cout << "Entered Private Insert" << std::endl;
#endif
    
    if (empty())
    {
        root->leftPtr = new RBNode<T>(value, root, sentinel);
        return root->leftPtr;
    }//If first node
    else if (node->object == value)
    {
        throw DuplicateObject("insert(RBNode<T> * node, const T & value)");
    }//Else if already exists
    else if (node->object > value)
    {
        if (node->leftPtr == sentinel)
        {
            node->leftPtr = new RBNode<T>(value, node, sentinel);
            //return node->leftPtr;
            node = node->leftPtr;
        }//If bottom left
        else
            node = insert(node->leftPtr, value);
    }//If less than
    else
    {
        if (node->rightPtr == sentinel)
        {
            node->rightPtr = new RBNode<T>(value, node, sentinel);
            //return node->rightPtr;
            node = node->rightPtr;
            
        }//If bottom right
        else
        {
            node = insert(node->rightPtr, value);
        }//Else add to right
    }//Else greater than
    
    return node;
    
#ifdef DEBUG_BST
    std::cout << "Exiting Private Insert" << std::endl;
#endif
    
}//END

/**
 This will handle case 3 and 4 of tree node removal
 Unlinks and deletes node
 
 @param node to be deleted
 */
template <typename T>
void RBTree<T>::removeNodeWithFewerThanTwoChildren(RBNode<T> * node)
{
#ifdef DEBUG_BST
    std::cout << "Entered Remove Node With Fewer Than Two Children" << std::endl;
#endif
    
    
    //Empty (case 1) and no such object (Case 2) exceptions handled in the public method
    RBNode<T> *parent = node->parent;
    Color c = node->color;
    
    
    if (node->rightPtr == sentinel && node->leftPtr == sentinel && node->parent == root)
    {
        delete node;
        parent->leftPtr = sentinel;
        parent = nullptr;
    }//If last node (case 3)
    else
    {
        RBNode<T> *childV = nullptr;
        
        if (node->leftPtr == sentinel) //find non external if there is one
            childV = node->rightPtr;
        else
            childV = node->leftPtr;
        
        if (node == parent->rightPtr) //assign correct parent ptr to non-external
            parent->rightPtr = childV;
        else
            parent->leftPtr = childV;
        
        if (childV != sentinel)
            childV->parent = parent;
        
        delete node;
        
        recolorOrRemedy(parent, childV, c);
        
    }//Else you have one child (case 4)
    
    
#ifdef DEBUG_BST
    std::cout << "Exiting Remove Node With Fewer Than Two Children" << std::endl;
#endif
}//END Remove Node With Fewer Than Two Children

/**
 This will handle case 5 of tree node removal
 First promotes min in right subtree
 Then calls removeNodesWithFewerThanTwoChildren on the min node
 
 @param node to be deleted
 */
template <typename T>
void RBTree<T>::removeNodeWithTwoChildren(RBNode<T> * node)
{
#ifdef DEBUG_BST
    std::cout << "Entered Remove Node With Two Children" << std::endl;
#endif
    
    //Case 5
    //promote min key in right subtree
    RBNode<T> *min = getMinNode(node->rightPtr);
    node->object = min->object;
    
    removeNodeWithFewerThanTwoChildren(min);
    

#ifdef DEBUG_BST
    std::cout << "Exiting Remove Node With Two Children" << std::endl;
#endif
}//END Remove Node With Two Children


/**
 Recursively creates list of Position
 
 @param node root of tree
 @return LL of tree in preorder
 */
template <typename T>
list< Position<T> > RBTree<T>::preorderToList( RBNode<T> * node) const
{
#ifdef DEBUG_BST
    std::cout << "Entered Private Pre Order to List" << std::endl;
#endif
    list<Position<T>> addList;
    Position<T> pos(node, sentinel);
    
    if (node != sentinel)
    {
        addList.push_front(pos); //"Visit"
        addList.splice(addList.end(), preorderToList(node->leftPtr)); //Add returned list to end
        addList.splice(addList.end(), preorderToList(node->rightPtr)); //Add returned list to end
    }//if not empty
    
#ifdef DEBUG_BST
    std::cout << "Exiting Private Pre Order to List" << std::endl;
#endif
    
    return addList;
}//END Pre Order to List

template <typename T>
RBNode<T>* RBTree<T>::restructure(RBNode<T>* x)
{
#ifdef DEBUG_BST
    std::cout << "Entered Restructure" << std::endl;
#endif
    
    RBNode<T>* y = x->parent;
    RBNode<T>* z = y->parent;
    RBNode<T>* t1 = sentinel;
    RBNode<T>* t2 = sentinel;
    
    
    if (z->object > y->object)
    {
        if (y->object > x->object)
        {
            //Attatch the subtree
            y->parent = z->parent;
            if (z == z->parent->leftPtr)
                z->parent->leftPtr = y;
            else
                z->parent->rightPtr = y;
            
            //restructure
            t2 = y->rightPtr;
            
            y->rightPtr = z;
            z->parent = y;
            
            z->leftPtr = t2;
            t2->parent = z; //could be sentinel but sentinel parent doesnt rlly matter
            
            return y;
            
        }//If Y is B and X is A (case 1)
        else
        {
            
            //Attatch the subtree
            x->parent = z->parent;
            if (z == z->parent->leftPtr)
                z->parent->leftPtr = x;
            else
                z->parent->rightPtr = x;
            
            //Restructure
            t1 = x->leftPtr;
            t2 = x->rightPtr;
            
            x->leftPtr = y;
            y->parent = x;
            y->rightPtr = t1;
            t1->parent = y;
            
            x->rightPtr = z;
            z->parent = x;
            z->leftPtr = t2;
            t2->parent = z;
            
            return x;
            
        }//Else Y is A and X is B (case 2)
    }//If Z is C
    else
    {
        if (y->object > x->object)
        {
            //Attatch the subtree
            x->parent = z->parent;
            if (z == z->parent->leftPtr)
                z->parent->leftPtr = x;
            else
                z->parent->rightPtr = x;
            
            //Restructure
            t1 = x->leftPtr;
            t2 = x->rightPtr;
            
            x->leftPtr = z;
            z->parent = x;
            z->rightPtr = t1;
            t1->parent = z;
            
            x->rightPtr = y;
            y->parent = x;
            y->leftPtr = t2;
            t2->parent = y;
            
            return x;
            
        }//If Y is C and X is B (case 3)
        else
        {
            //Attatch the subtree
            y->parent = z->parent;
            if (z == z->parent->leftPtr)
                z->parent->leftPtr = y;
            else
                z->parent->rightPtr = y;
            
            //Restructure
            t1 = y->leftPtr;
            
            y->leftPtr = z;
            z->parent = y;
            
            z->rightPtr = t1;
            t1->parent = z;
            
            return y;
            
        }//Y is B and X is C (case 4)
    }//Z is A
    
#ifdef DEBUG_BST
    std::cout << "Exiting Restructure" << std::endl;
#endif
}//END  restructure

//void remedyDoubleRed(RBNode<T>* z);
template <typename T>
void RBTree<T>::remedyDoubleRed(RBNode<T>* z)
{
    RBNode<T>* v = z->parent;
    RBNode<T>* u = v->parent;
    if (v->color == RED)
    {
        RBNode<T>* w = getSibling(v);
        if (w->color == BLACK)
        {
            u = restructure(z);
            u->color = BLACK;
            u->leftPtr->color = RED;
            u->rightPtr->color = RED;
        }//case 1
        else
        {
            v->color = BLACK;
            w->color = BLACK;
            if (u != root->leftPtr)
            {
                u->color = RED;
                remedyDoubleRed(u);
            }//If u is not the root
        }//Else case 2
    }//If double red
        
}//END remedy double red

//RBNode<T>* getSibbling(RBNode<T>* ) const;
template <typename T>
RBNode<T>* RBTree<T>::getSibling(RBNode<T>* otherSib) const
{
    RBNode<T>* node = otherSib->parent;
    
    if (node->leftPtr == otherSib)
        node = node->rightPtr;
    else
        node = node->leftPtr;
    
    return node;
}//END get sibling

template <typename T>
void RBTree<T>::recolorOrRemedy(RBNode<T>* x, RBNode<T>* r, Color c)
{
    if (c == BLACK)
    {
        if (r->color == RED)//If internal child was red
            r->color = BLACK; //Case 0b
        else
            remedyDoubleBlack(x,r);
    }//If v was black
    
}//END recolorOrRemedy

template <typename T>
void RBTree<T>::remedyDoubleBlack(RBNode<T>* x, RBNode<T>* r)
{
    if (x != root)
    {
        RBNode<T>* y = nullptr;
        RBNode<T>* z = nullptr;
        
        if (r != sentinel)
            y = getSibling(r);
        else if (x->leftPtr == sentinel)
            y = x->rightPtr;
        else
            y = x->leftPtr;
        
        
        
        if (y->color == RED)
        {
            if (y == x->leftPtr)
                z = y->leftPtr;
            else
                z = y->rightPtr;
            
            y = restructure(z);
            y->color = BLACK;
            x->color = RED;
            r->color = BLACK;
            
            remedyDoubleBlack(x,r);
        }//If y is red (case 3 -- can only be one)
        else if (y->leftPtr->color == RED || y->rightPtr->color == RED)
        {
            Color c = x->color;
            
            if (y->leftPtr->color == RED)
                z = y->leftPtr;
            else
                z = y->rightPtr;
            
            x = restructure(z);
            x->color = c;
            x->leftPtr->color = BLACK;
            x->rightPtr->color = BLACK;
            r->color = BLACK;
        }//Else if r has a red child (case 1)
        else
        {
            r->color = BLACK;
            y->color = RED;
            if (x->color == RED)
                x->color = BLACK;
            else
                remedyDoubleBlack(x->parent, x); //TODO: else or if sibling is black?
        }//Else case 2 -- just a recoloring
    }//if x is not the super root
    
}//END RemedyDoubleBlack
#endif //rbtree_h






