//
//  path.h
//  project5
//
//  Created by Colin Mills on 11/24/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//

#ifndef path_h
#define path_h

#include "vertex.h"
#include <vector>

using namespace std;


class Path {
    
    friend ostream &operator<<( ostream &out, const Path &p );
    
public:
    Path();
    void push_back( const Vertex & );
    void pop_back();
    void clear();
    size_t size() const {return vertices.size();}
    
private:
    vector<Vertex> vertices;
    
}; // Path class

/***********************************************************************************************
 *****************************PATH FRIEND MEMBER FUNCTIONS****************************************
 ***********************************************************************************************/
ostream &operator<<( ostream &out, const Path &p)
{
    for (size_t i = 0 ; i < p.size() ; i++)
    {
        out << p.vertices.at(i).name << " ";
    }//END for each path
    
    out << endl;
    
    return out;
}//END overloaded stream insertion operator

/***********************************************************************************************
 ******************************PATH CONTRUCTING FUNCTIONS*****************************************
 ***********************************************************************************************/
Path::Path()
{
    //nothing
}//END constructor

/***********************************************************************************************
 *****************************PATH PUBLIC MEMBER FUNCTIONS****************************************
 ***********************************************************************************************/
void Path::push_back( const Vertex & v)
{
    vertices.push_back(v);
}//END push back

void Path::pop_back()
{
    vertices.pop_back();    
}//END pop back

void Path::clear()
{
    vertices.clear();
}//END pop back

#endif /* path_h */
