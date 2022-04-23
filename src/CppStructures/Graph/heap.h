//
//  heap.h
//  project5
//
//  Created by Colin Mills on 11/24/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//

#ifndef heap_h
#define heap_h

#include "exceptions.h"
#include "vertex.h"

#include <vector>

using namespace std;

/***********************************************************************************************
 **********************************HEAP NODE CLASS **********************************************
 ***********************************************************************************************/

template <typename K, typename T>
class HeapNode {
public:
    HeapNode(const K& = K(), const T& = T());
    
    K key;
    T name;
};//END HeapNode structure

//HeapNode();
template <typename K, typename T>
HeapNode<K,T>::HeapNode(const K& k, const T& t)
{
    key = k;
    name = t;
    
}//END contructor

/***********************************************************************************************
 ************************************HEAP CLASS ***********************************************
 ***********************************************************************************************/

template <typename K, typename T>
class Heap {
    
public:
    //K is the key/label/priority
    //T is the name
    Heap();
    ~Heap();
    bool empty() const {return last == 0;}
    void changeKey( const K &, const T & ); // throws NoSuchObject
    //Search for node of value T in the heap and change its K
    //Will only ever decrease the key
    void clear();
    void insert( const K &, const T & ); // priorities/keys are not unique
    T remove(); // throws NoSuchObject //Removes min at top
    bool inHeap(T name) const; // public search function
    
private:
    // It's better to move around pointers instead of nodes of big objects
    vector< HeapNode<K,T> * > heap;
    int last; //Stores bottom right index
    
    //Do this like 2xparent and stuff should be easy, maybe even in line implementation easy
    int getLeftChild( const int i) const {return 2*i;}
    int getRightChild( const int i) const {return (2*i + 1);}
    int getParent(const int i) const {return i/2;} //Should give floor becasue int math
    
    void upHeapBubble (const int);
    void downHeapBubble (const int);
    
};

/***********************************************************************************************
 ******************************HEAP CONTRUCTING FUNCTIONS*****************************************
 ***********************************************************************************************/
//Heap();
template <typename K, typename T>
Heap<K,T>::Heap()
{
    last = 0;
    heap.push_back(nullptr);
    
}//END contructor

//~Heap();
template <typename K, typename T>
Heap<K,T>::~Heap()
{
    clear();
}//END Destructor

/***********************************************************************************************
 *****************************HEAP PUBLIC MEMBER FUNCTIONS****************************************
 ***********************************************************************************************/
//void changeKey( const K &, const T & ); // throws NoSuchObject
template <typename K, typename T>
void Heap<K,T>::changeKey( const K & k, const T & t)
{
    int i = 1;
    bool found = false;
    //Find the right vertex
    while (!found && i <= last)
    {
        if (t == heap.at(i)->name)
            found = true;
        else
            i++;
    }//END while t not found
    
    if (i == last + 1)
        throw NoSuchObject("Heap<K,T>::changeKey: T not found");
    
    //change its value
    heap.at(i)->key = k;
    
    //Now upheap bubble if nescesary
    upHeapBubble(i);
    //TODO: what about downHeapBubbling? or do we assume it will only ever decrease
    
}//END changeKey( const K &, const T & )

//void clear();
template <typename K, typename T>
void Heap<K,T>::clear()
{
    for (size_t i = last; i >= 1; i--)
    {
        delete heap.at(i);
        heap.pop_back();
    }//END for length of heap
    
    last = 0;
    
}//END clear

template <typename K, typename T>
void Heap<K,T>::insert( const K & key, const T & name)
{
    HeapNode<K,T> * hN = new HeapNode<K,T>(key, name);
    heap.push_back(hN);
    
    last += 1;
    
    //Now bubble up
    upHeapBubble(last);
    
}//END insert( const K &, const T & )

//T remove(); // throws NoSuchObject
template <typename K, typename T>
T Heap<K,T>::remove()
{
    
    if (empty())
        throw NoSuchObject("Heap<K,T>::remove(): Heap is empty");
    //Store name
    T top = heap.at(1)->name;
    
    //move up last node to root and delete
    swap(heap[1], heap[last]);
    delete heap.at(last);
    heap.pop_back();
    last -= 1;
    
    downHeapBubble(1);
    
    return top;
    
}//END remove()

template <typename K, typename T>
bool Heap<K,T>::inHeap (T t) const
{
    
    int i = 1;
    bool found = false;
    
    while (!found && i <= last)
    {
        if (t == heap.at(i)->name)
            found = true;
        else
            i++;
    }//END while t not found
    
    return found;
}//END inHeap

/***********************************************************************************************
 *****************************HEAP PRIVATE MEMBER FUNCTIONS****************************************
 ***********************************************************************************************/

template <typename K, typename T>
void Heap<K,T>::upHeapBubble(const int node)
{
    //Now bubble up
    int parent = getParent(node);
    
    if (parent > 0 && heap.at(parent)->key > heap.at(node)->key)
    {
        swap(heap[parent], heap[node]);
        upHeapBubble(parent);
    }//if swap needed
    
}//END upHeapBubble

template <typename K, typename T>
void Heap<K,T>::downHeapBubble(const int node)
{
    //Now bubble down
    int left = getLeftChild(node);
    int right = getRightChild(node);

    if (left < last)
    {
        if (heap.at(left)->key <= heap.at(right)->key && heap.at(left)->key < heap.at(node)->key)
        {
            swap(heap[node], heap[left]);
            downHeapBubble(left);
        }//END if left is smaller
    }//END if within range
    
    if (right < last)
    {
        if (heap.at(right)->key < heap.at(left)->key && heap.at(right)->key < heap.at(node)->key)
        {
            swap(heap[node], heap[right]);
            downHeapBubble(right);
        }//if right swap needed
    }//END if right is within range
    
}//END downHeapBubble


#endif /* heap_h */

