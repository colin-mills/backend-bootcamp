/*
 * bstree.h
 */

#ifndef bstree_h
#define bstree_h

//#define DEBUG_BST

#include "iterator.h"
#include "treenode.h"
#include "position.h"

#include <list>
#include <algorithm> //for max fxn


using namespace std;

template <typename T>
class BSTree {

  public:
    BSTree();
    BSTree( const BSTree<T> & );
    ~BSTree();
    Iterator<T> begin() const;
    void clear()
    {
        clear(root->leftPtr);
        root->leftPtr = nullptr;
    }
    bool empty() const {return (root->leftPtr == nullptr);}
    Iterator<T> end() const;
    Position<T> find( const T & foundNode) const
        {return find(root->leftPtr, foundNode);} // throws NoSuchObject
    int height() const {return height(root->leftPtr);}
    void insert( const T & placeNode) {insert(root->leftPtr, placeNode);} // throws DuplicateObject
    const BSTree<T> &operator=( const BSTree<T> & );
    T remove( const T & ); // throws NoSuchObject
    list< Position<T> > preorderToList() const {return preorderToList(root->leftPtr);}

  private:
    TreeNode<T> *root; // points to super root 

    int height( TreeNode<T> *node ) const;
    void clear( TreeNode<T> * ); // use a post-order traversal
    TreeNode<T> *copy( TreeNode<T> *node ); // use a post-order traversal
    TreeNode<T> *find( TreeNode<T> *, const T & ) const;
    TreeNode<T> *getMinNode( TreeNode<T> * ) const;
    void insert( TreeNode<T> *, const T & ); // throws DuplicateObject
    void removeNodeWithFewerThanTwoChildren( TreeNode<T> * );
    void removeNodeWithTwoChildren( TreeNode<T> * );
    list< Position<T> > preorderToList( TreeNode<T> * ) const;
    

}; // BSTree<T> class

/***********************************************************************************************
 ******************************BST CONTRUCTING FUNCTIONS*****************************************
 ***********************************************************************************************/
template <typename T>
BSTree<T>::BSTree()
{
#ifdef DEBUG_BST
    std::cout << "Entered Default Contructor" << std::endl;
#endif
    
    //Initialize new superRoot
    //all of its nodes are set to null by node contructor
    //when first node is added that will be updated
    root = new TreeNode<T>;
  
#ifdef DEBUG_BST
    std::cout << "Exiting Default Contructor" << std::endl;
#endif
}//END default contructor


template <typename T>
BSTree<T>::BSTree(const BSTree<T> & otherTree)
{
#ifdef DEBUG_BST
    std::cout << "Entered Copy Contructor" << std::endl;
#endif
    
    //makes equal with overloaded equality operator
    root = new TreeNode<T>;
    *this = otherTree;
    
#ifdef DEBUG_BST
    std::cout << "Exiting Copy Contructor" << std::endl;
#endif
}//END copy contructor

template <typename T>
BSTree<T>::~BSTree()
{
#ifdef DEBUG_BST
    std::cout << "Entered Destructor" << std::endl;
#endif
    
    if (!empty())
        clear(); //clear and delete all nodes
    delete root; //delete dynamically allocated super root
    root = nullptr; //fix last pointer
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
Iterator<T> BSTree<T>::begin() const
{
#ifdef DEBUG_BST
    std::cout << "Entered Begin" << std::endl;
#endif
    
    Iterator<T> it;
    it.v = getMinNode(root);

#ifdef DEBUG_BST
    std::cout << "Exiting Begin" << std::endl;
#endif
    
    return it;
}//END Begin

//Creates iterator and sets it to super root
template <typename T>
Iterator<T> BSTree<T>::end() const
{
#ifdef DEBUG_BST
    std::cout << "Entered End" << std::endl;
#endif
    
    Iterator<T> endIt;
    endIt.v = root;
    
  
#ifdef DEBUG_BST
    std::cout << "Exiting End" << std::endl;
#endif
    
    return endIt;
}//END End


/**
 Checks to see if they are not the same
    clears if not already empty
    Checks to see if rhsTree is empty and will clear if this is not empty
    Otherwise it will call copy

 @param rhsTree other Tree that will be copied
 @return *this so it can be used with multiple chaining of =
 */
template <typename T>
const BSTree<T> & BSTree<T>::operator= ( const BSTree<T> & rhsTree)
{
#ifdef DEBUG_BST
    std::cout << "Entered Overloaded = Operator" << std::endl;
#endif
    
    //TODO: TEST
    if (this != &rhsTree) //if not already same
    {
        if (!empty())
            clear();
        
        if (!rhsTree.empty()) //If RHs empty and this isn't
        {
            this->root->leftPtr = copy((rhsTree.root)->leftPtr);
        }//If empty
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
T BSTree<T>::remove(const T & removeNode)
{
#ifdef DEBUG_BST
    std::cout << "Entered Remove" << std::endl;
#endif

    if (empty())
        throw NoSuchObject("BSTree<T>::remove: Cannot remove becasue tree is empty");
    
    TreeNode<T> *node;
    node = (find(removeNode)).node; //Will throw NoSuchObject
    if (node->leftPtr == nullptr || node->rightPtr == nullptr)
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
int BSTree<T>::height(TreeNode<T> *node ) const
{
#ifdef DEBUG_BST
    std::cout << "Entered Private Height" << std::endl;
#endif
    if (node == nullptr)
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
void BSTree<T>::clear(TreeNode<T> * node)
{
#ifdef DEBUG_BST
    std::cout << "Entered Private Clear" << std::endl;
#endif
    
    if (node != nullptr)
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
 this gets a list in preorder of other tree
 and inserts the values
 and pops list until the list is empty

 @param node Root node of other tree
 @return return created node
 */
template <typename T>
TreeNode<T>* BSTree<T>::copy(TreeNode<T> *node )
{
#ifdef DEBUG_BST
    std::cout << "Entered Private Copy" << std::endl;
#endif
    
    TreeNode<T>* nodeN = nullptr;
    //TODO: TEST
    if (node != nullptr)
    {
        
        nodeN = new TreeNode<T>(node->object);
        
        nodeN->leftPtr = copy(node->leftPtr); //visit left
        nodeN->rightPtr = copy(node->rightPtr); //visit right
        
        if (nodeN->leftPtr != nullptr)
            nodeN->leftPtr->parent = nodeN;
        
        if (nodeN->rightPtr != nullptr)
            nodeN->rightPtr->parent = nodeN;
        
    }//if not empty
    
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
TreeNode<T>* BSTree<T>::find(TreeNode<T> * thisNode, const T & foundNode) const
{
#ifdef DEBUG_BST
    std::cout << "Entered Private Find" << std::endl;
#endif
    
    
    if(thisNode == nullptr)
    {
        throw NoSuchObject("BSTree<T>::find(TreeNode<T> * thisNode, const T & foundNode)");
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
TreeNode<T>* BSTree<T>::getMinNode(TreeNode<T> * node) const
{
#ifdef DEBUG_BST
    std::cout << "Entered Get Min Node" << std::endl;
#endif
    
    TreeNode<T> *nextNode = node;
    
    if (!empty())
    {
        while (nextNode->leftPtr != nullptr)
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
void BSTree<T>::insert(TreeNode<T> * node, const T & value)
{
#ifdef DEBUG_BST
    std::cout << "Entered Private Insert" << std::endl;
#endif
    
    if (empty())
    {
        root->leftPtr = new TreeNode<T>(value, root);
    }//If first node
    else if (node->object == value)
    {
        throw DuplicateObject("insert(TreeNode<T> * node, const T & value)");
    }//Else if already exists
    else if (node->object > value)
    {
        if (node->leftPtr == nullptr)
            node->leftPtr = new TreeNode<T>(value, node);
        else
            insert (node->leftPtr, value);
    }//If less than
    else
    {
        if (node->rightPtr == nullptr)
            node->rightPtr = new TreeNode<T>(value, node);
        else
            insert (node->rightPtr, value);

    }//Else greater than
    
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
void BSTree<T>::removeNodeWithFewerThanTwoChildren(TreeNode<T> * node)
{
#ifdef DEBUG_BST
    std::cout << "Entered Remove Node With Fewer Than Two Children" << std::endl;
#endif
    
    
    //Empty (case 1) and no such object (Case 2) exceptions handled in the public method
    TreeNode<T> *parent = node->parent;
    if (node->rightPtr == nullptr && node->leftPtr == nullptr && node->parent == root)
    {
        delete node;
        parent->leftPtr = nullptr;
        parent = nullptr;
    }//If last node (case 3)
    else
    {
         TreeNode<T> *childV = nullptr;
        
        if (node->leftPtr == nullptr) //find non external if there is one
            childV = node->rightPtr;
        else
            childV = node->leftPtr;
        
        if (node == parent->rightPtr) //assign correct parent ptr to non-external
            parent->rightPtr = childV;
        else
            parent->leftPtr = childV;
        
        if (childV != nullptr)
            childV->parent = parent;
        
        delete node;
        parent = childV = nullptr;
            
    }//Else you have one child (case 4)
    
    
#ifdef DEBUG_BST
    std::cout << "Exiting Remove Node With Fewer Than Two Children" << std::endl;
#endif
}//END Remove Node With Fewer Than Two Children

/**
 This will handle case 5 of tree node removal
 First promotes min in right subtree
 Then unlinks and deletes node
 
 @param node to be deleted
 */
template <typename T>
void BSTree<T>::removeNodeWithTwoChildren(TreeNode<T> * node)
{
#ifdef DEBUG_BST
    std::cout << "Entered Remove Node With Two Children" << std::endl;
#endif
    
    //Case 5
    //promote min key in right subtree
    TreeNode<T> *min = getMinNode(node->rightPtr);
    node->object = min->object;
    
    removeNodeWithFewerThanTwoChildren(min);
    
    /*
    TreeNode<T> *parent = min->parent;
    TreeNode<T> *childV = nullptr;
    
    //now handle like case 4
    if (node->leftPtr == nullptr) //find non external if there is one
        childV = node->rightPtr;
    else
        childV = node->leftPtr;
    
    if (node == parent->rightPtr) //assign correct parent ptr to non-external
        parent->rightPtr = childV;
    else
        parent->leftPtr = childV;
    
    if (childV != nullptr)
        childV->parent = parent;
    
    delete node;
    parent = childV = min = nullptr;
    
     */
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
list< Position<T> > BSTree<T>::preorderToList( TreeNode<T> * node) const
{
#ifdef DEBUG_BST
    std::cout << "Entered Private Pre Order to List" << std::endl;
#endif
    list<Position<T>> addList;
    Position<T> pos(node);
    
    if (node != nullptr)
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

#endif //bstree_h






