//
//  edge.h
//  project5
//
//  Created by Colin Mills on 11/24/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//

#ifndef edge_h
#define edge_h

#include "vertex.h"

using namespace std;

enum class EdgeLabel { visited, unvisited, discovery, back, cross };

class Edge
{
public:
    string name;
    int w;
    int a; //This if you want to refer through indexes
    int b;

    EdgeLabel label;
    
    Edge();
    Edge( int a, int b, int w = 0 );
    //Edge( Vertex *a, Vertex *b, int w = 0 );
    string labelToString() const;
    int opposite( const Vertex &v ) const;
};

/***********************************************************************************************
 ******************************EDGE CONTRUCTING FUNCTIONS*****************************************
 ***********************************************************************************************/
Edge::Edge()
{
    w = a = b = -1;
    label = EdgeLabel::unvisited;
}//END default contructor

Edge::Edge( int a, int b, int w )
{
    this->w = w;
    this->a = a;
    this->b = b;
    label = EdgeLabel::unvisited;
    
}//END constructor

/***********************************************************************************************
 *****************************EDGE PUBLIC MEMBER FUNCTIONS****************************************
 ***********************************************************************************************/
string Edge::labelToString() const
{
    string slabel = "unvisited";
    
    //visited, unvisited, discovery, back, cross
    if (label == EdgeLabel::visited)
        slabel = "visited";
    else if (label == EdgeLabel::discovery)
        slabel = "discovery";
    else if (label == EdgeLabel::back)
        slabel = "back";
    else if (label == EdgeLabel::cross)
        slabel = "cross";
    
    return slabel;
}//END labelToString()

int Edge::opposite( const Vertex &v ) const
{
    int otherV = a;
    
    if (v.index == a)
        otherV = b;
    
    
    return otherV;
}//END opposite

#endif /* edge_h */
