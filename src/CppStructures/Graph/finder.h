//
//  finder.h
//  project5
//
//  Created by Colin Mills on 11/24/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//

#ifndef finder_h
#define finder_h

#include "path.h"
#include "graph.h"

#include <string>

using namespace std;

class PathFinder : public Graph
{
public:
    PathFinder();
    PathFinder( string );
    Path find( Vertex & s, Vertex & t); //Will depth first search a path between the two vertex
    
protected:
    virtual void startVisit( Vertex & v); //visit vertex
    virtual void finishVisit( Vertex & v);//finished with vertex
    virtual bool isDone() const {return done;} //done yet?
    
private:
    //These are updated as the protected functions work
    Path path;
    Vertex target;
    bool done;
};

/***********************************************************************************************
 ******************************PATHF CONTRUCTING FUNCTIONS*****************************************
 ***********************************************************************************************/
//USE graph construction functions also these
PathFinder::PathFinder()
{
    done = false;
}//END default construct

PathFinder::PathFinder(string s):Graph(s)
{
    done = false;
}//END string contruct

/***********************************************************************************************
 *****************************PATHF PUBLIC MEMBER FUNCTIONS****************************************
 ***********************************************************************************************/
Path PathFinder::find( Vertex & s, Vertex & t)
{
    path.clear();
    target = t;
    done = false;
    dft(s);
    
    return path;
}//END find

/***********************************************************************************************
 ***************************PATHF PROTECTED MEMBER FUNCTIONS**************************************
 ***********************************************************************************************/
void PathFinder::startVisit( Vertex & v)
{
    path.push_back(v);
    
    if (v == target)
        done = true;
    
}//END startVisit

void PathFinder::finishVisit( Vertex & v)
{
    if (!isDone())
        path.pop_back();
        
}//END finishVisit


#endif /* finder_h */
