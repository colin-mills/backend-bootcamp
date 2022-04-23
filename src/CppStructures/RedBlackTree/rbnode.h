/*
 * rbnode.h
 */

#ifndef rbnode_h
#define rbnode_h


//#define DEBUG_TN
//using namespace std;
enum Color {RED, BLACK};

template<typename T>
class RBNode {
    
public:
    RBNode( const T & = T(),  RBNode<T> *setParent = nullptr, RBNode<T> *sentinel = nullptr);
    //RBNode(const RBNode &);
    ~RBNode();
    // ...
    T object;
    RBNode<T> *parent;
    RBNode<T> *leftPtr;
    RBNode<T> *rightPtr;
    Color color; // e.g., color = BLACK;  Feel free to do something else.

    
    
}; // RBNode class


/*************************************************************************************************
 ******************************NODE CONSTRUCTOR FUNCTION*****************************************
 *************************************************************************************************/

/**********************************
 *                                *
 *    NODE default constructor    *
 *                                *
 **********************************/
template <class T>
RBNode<T>::RBNode(const T & value,  RBNode<T>* setParent, RBNode<T>* sentinel)
{
#ifdef DEBUG_NODE
    std::cout << "Entered default constructor RBNode<T>" << endl;
#endif
    //Initialize to default values or will fully initialize if arguments are provided
    object = value;
    parent = setParent;
    leftPtr = rightPtr = sentinel;
    color = RED;
    
#ifdef DEBUG_NODE
    std::cout << "Exiting default constructor RBNode<T>" << endl;
#endif
}//END Constructor


/**********************************
 *                                *
 *     NODE copy constructor      *
 *                                *
 **********************************/
/*
 template <class T>
 RBNode<T>::RBNode(const RBNode<T> & otherNode)
 {
 #ifdef DEBUG_NODE
 std::cout << "Entered copy constructor RBNode<T>" << endl;
 #endif
 
 
 #ifdef DEBUG_NODE
 std::cout << "Exiting copy constructor RBNode<T>" << endl;
 #endif
 }//END Copy Constructor
 */
/**********************************
 *                                *
 *         NODE destructor        *
 *                                *
 **********************************/
template <class T>
RBNode<T>::~RBNode()
{
#ifdef DEBUG_NODE
    std::cout << "Entered destructor RBNode<T>" << endl;
#endif
    
    //No dangling pointers
    parent = leftPtr = rightPtr = nullptr;
    
#ifdef DEBUG_NODE
    std::cout << "Exiting destructor RBNode<T>" << endl;
#endif
}//END Copy Constructor


#endif //rbnode_h
