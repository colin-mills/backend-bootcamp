//
//  vertex.h
//  project5
//
//  Created by Colin Mills on 11/24/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//

#ifndef vertex_h
#define vertex_h

using namespace std;

enum class VertexLabel { visited, unvisited };

class Vertex
{    
public:
    string name;
    VertexLabel label;
    int index;
    // pointer to incident list? 
    
    Vertex();
    Vertex( const string & );
    
    string labelToString() const;
    bool operator==( const Vertex & ) const;
    bool unvisited() const {return label == VertexLabel::unvisited;}
};


/***********************************************************************************************
 *****************************VERTEX CONTRUCTING FUNCTIONS****************************************
 ***********************************************************************************************/
Vertex::Vertex()
{
    name = "";
    label = VertexLabel::unvisited;
    index = -1;
    
}//END default Contructor

Vertex::Vertex( const string & s)
{
    name = s;
    index = -1;
    label = VertexLabel::unvisited;
    
}//END string constuctor

/***********************************************************************************************
 ****************************VERTEX PUBLIC MEMBER FUNCTIONS***************************************
 ***********************************************************************************************/
string Vertex::labelToString() const
{
    string slabel = "";
    
    if (label == VertexLabel::unvisited)
        slabel = "unvisited";
    else
        slabel = "visited";
        
    
    return slabel;
}//END labelToString()

bool Vertex::operator==( const Vertex & otherV) const
{
    return this->index == otherV.index;
}//END operator==

#endif /* vertex_h */
