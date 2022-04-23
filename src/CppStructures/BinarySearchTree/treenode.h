/*
 * treenode.h
 */

#ifndef treenode_h
#define treenode_h


//#define DEBUG_TN
//using namespace std;

template<typename T>
class TreeNode {

  public:
    TreeNode( const T & = T(),  TreeNode<T>* = nullptr,
              TreeNode<T>* = nullptr,  TreeNode<T>* = nullptr );
    //TreeNode(const TreeNode &);
    ~TreeNode();
    // ...
    T object;
    TreeNode<T> *parent;
    TreeNode<T> *leftPtr;
    TreeNode<T> *rightPtr;

    
}; // TreeNode class


/*************************************************************************************************
 ******************************NODE CONSTRUCTOR FUNCTION*****************************************
 *************************************************************************************************/

/**********************************
 *                                *
 *    NODE default constructor    *
 *                                *
 **********************************/
template <class T>
TreeNode<T>::TreeNode(const T & value,  TreeNode<T>* setParent,
                       TreeNode<T>* setLeft,  TreeNode<T>* setRight)
{
#ifdef DEBUG_NODE
    std::cout << "Entered default constructor TreeNode<T>" << endl;
#endif
    //Initialize to default values or will fully initialize if arguments are provided
    object = value;
    parent = setParent;
    leftPtr = setLeft;
    rightPtr = setRight;
    
#ifdef DEBUG_NODE
    std::cout << "Exiting default constructor TreeNode<T>" << endl;
#endif
}//END Constructor


/**********************************
 *                                *
 *     NODE copy constructor      *
 *                                *
 **********************************/
/*
template <class T>
TreeNode<T>::TreeNode(const TreeNode<T> & otherNode)
{
#ifdef DEBUG_NODE
    std::cout << "Entered copy constructor TreeNode<T>" << endl;
#endif

    
#ifdef DEBUG_NODE
    std::cout << "Exiting copy constructor TreeNode<T>" << endl;
#endif
}//END Copy Constructor
*/
/**********************************
 *                                *
 *         NODE destructor        *
 *                                *
 **********************************/
template <class T>
TreeNode<T>::~TreeNode()
{
#ifdef DEBUG_NODE
    std::cout << "Entered destructor TreeNode<T>" << endl;
#endif
    
    //No dangling pointers 
    parent = leftPtr = rightPtr = nullptr;

#ifdef DEBUG_NODE
    std::cout << "Exiting destructor TreeNode<T>" << endl;
#endif
}//END Copy Constructor


#endif //treenode_h
