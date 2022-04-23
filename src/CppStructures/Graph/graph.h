//
//  graph.h
//  project5
//
//  Created by Colin Mills on 11/24/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//

#ifndef graph_h
#define graph_h

#include "vertex.h"
#include "edge.h"
#include "heap.h"
#include "exceptions.h"

#include <vector>
#include <fstream>
#include <limits>

using namespace std;

class Graph
{
public:
    Graph();
    Graph(string filename);
    virtual ~Graph();
    int components(); // GTM Code Fragment 13.9, p. 617
    void dft( Vertex& ); // initialize() -> dfsTraversal
    int getDistance( const Vertex & ) const; // for Djikstra's algorithm
    Vertex &getVertexByName( const string &s );
    virtual void print();
    void read( istream &in = cin );
    void shortestPath( const Vertex& ); // Djikstra's algorithm
    
protected:
    void dfsTraversal( Vertex & );  // GTM Code Fragment 13.7, p. 616 //"actually does the labeling"
    //
    // Modifications of Code Fragments 13.4, 13.5, and 13.6
    //
    void initialize();              // resets vertex and edge labels
    virtual void startVisit( Vertex & ) {}
    virtual void traverseBack( Edge &e, Vertex& from ) { e.label = EdgeLabel::back; }
    virtual void traverseCross( Edge &e, Vertex& from ) { e.label = EdgeLabel::cross; }
    virtual void traverseDiscovery( Edge &e, Vertex& from ) { e.label = EdgeLabel::discovery; }
    virtual void finishVisit( Vertex & ) {}
    virtual bool isDone() const { return false; }
    void visit( Vertex &v ) { v.label = VertexLabel::visited; }
    void visit( Edge &e ) { e.label = EdgeLabel::visited; }
    void unvisit( Vertex &v ) { v.label = VertexLabel::unvisited; }
    void unvisit( Edge &e ) { e.label = EdgeLabel::unvisited; }
    bool isVisited( const Vertex &v ) const { return v.label == VertexLabel::visited; }
    bool isVisited( const Edge & e ) const { return e.label != EdgeLabel::unvisited; }
    
    //private:
    /** vertices */
    vector<Vertex> V;
    
    /** edges */
    vector<Edge> E;
    // ? vector<Edge *> E;
    
    /** adjacency list or adjacency matrix */
    vector<vector<int>> A;
    
    /** distances */
    vector<int> D; // for Djikstra's algorithm
    
}; // Graph class

/***********************************************************************************************
 ******************************GRAPH CONTRUCTING FUNCTIONS*****************************************
 ***********************************************************************************************/
Graph::Graph()
{
    //Nothing special I think
}//End Contructor

Graph::Graph(string filename)
{
    //should open an input file stream and pass it to read(istream &);
    ifstream inFile(filename);
    
    if (inFile)
        read(inFile);
    
    inFile.close();
    
    D = vector<int>(V.size());
    
}//End File Contructor

Graph::~Graph()
{
    
//Nothing to do here

}//END Destructor

/***********************************************************************************************
 *****************************GRAPH PUBLIC MEMBER FUNCTIONS****************************************
 ***********************************************************************************************/
int Graph::components() // GTM Code Fragment 13.9, p. 617
{
    int nComponents = 0;
    
    for (size_t i = 0; i < V.size(); i++)
    {
        if (!isVisited(V.at(i)))
            {
                dfsTraversal(V.at(i));
                nComponents += 1;
            }//IF unvisited
    }//END for Vectors in V
    
    return nComponents;
    
}//END components

void Graph::dft( Vertex& v)
{
    //Calls to initialize vectors and edges
    initialize();
    
    //Now it will iterate
    dfsTraversal(v);
    
}//END dft

int Graph::getDistance( const Vertex & v) const // for Djikstra's algorithm
{
    int dist = D.at(v.index);
    
    return dist;
}//END get Distance

Vertex& Graph::getVertexByName( const string &s ) //Throws NoSuchObject
{

    size_t i = 0;
    bool found = false;
    //Find the right vertex
    while (!found && i < V.size())
    {
        if (s == V.at(i).name)
            found = true;
        else
            i++;
    }//END while t not found
    
    if (i == V.size())
        throw NoSuchObject("getVertexByName( const string &s ): v not found");
    
    return V.at(i);
}//END getVertexByNAme

void Graph::print()
{
    //Print the name of each vertex and then go down the line and print the edges and their weights
    for (size_t i = 0; i < V.size(); i++)
    {
        cout << "Printing the edges of: " + V.at(i).name + " if any..\n";
        
        for (size_t j = 0; j < V.size(); j++)
        {
            if (A[i][j] != -1)
                cout << "Edge: " + V.at(i).name + "-" + V.at(j).name
                + " Weight: " << E.at(A[i][j]).w << endl;
        }//for each column
        cout << endl;
    }//for each row
}//END print

void Graph::read( istream & in )
{
    char graphType = 'U';
    int graphSize = 0;
    string name = "";
    int weight = 0;
    
    in >> graphType;
    in >> graphSize;
    
    this->A = vector<vector<int>>(graphSize, vector<int> (graphSize, -1));
    
    
    for (int i = 0; i < graphSize; i++)
    {
        in >> name;
        Vertex v(name);
        v.index = i;
        V.push_back(v);
    }//for each named vector
    
    for (int i = 0; i < graphSize; i++)
    {
        for (int j = 0; j < graphSize; j++)
        {
            in >> weight;
            
            if (weight > 0)
            {
                if (graphType == 'D')
                {
                    Edge e(i, j, weight);
                    E.push_back(e);
                    A[i][j] = (static_cast<int>(E.size()) - 1);
                }//if directed
                else
                {
                    if (A[j][i] == -1)
                    {
                        Edge e(i, j, weight);
                        E.push_back(e);
                        A[i][j] = (static_cast<int>(E.size()) -1);
                        A[j][i] = (static_cast<int>(E.size()) -1);
                    }//If symetric pair not set
                }//else undirected
            }//If there is an edge
        }//for each column
    }//for each row
    

}//END read

void Graph::shortestPath( const Vertex& v) // Djikstra's algorithm
{
    //Keys (K) are int distances
    //values/name (T) are indexes -- should be the same between V and D
    Heap<int, int> priorityQ;
    
    int u;
    int dV = 0;
    int dU = numeric_limits<int>::max();
    
    for (size_t i = 0; i < V.size(); i++)
    {
        if (static_cast<int>(i) == v.index)
        {
            D.at(i) = dV;
            priorityQ.insert(dV, static_cast<int>(i));
        }//If starting index
        else
        {
            D.at(i) = dU;
            priorityQ.insert(dU, static_cast<int>(i));
        }//else infinity
    }//END for each vertex add to D and priorityQ
    
    while (!priorityQ.empty())
    {
        u = priorityQ.remove();

        //Find and evaluate adjacent edges
        for (size_t z = 0; z < A.size(); z++)
        {
            if (A[u][z] != -1)
            {
                if (priorityQ.inHeap(static_cast<int>(z))) //z is the index of the other vertex
                {
                    if (D.at(u) + E.at(A[u][z]).w < D.at(z))
                    {
                        D.at(z) = (D.at(u) + E.at(A[u][z]).w);
                        priorityQ.changeKey(D.at(z), static_cast<int>(z));
                    }//If shorter path found
                }//If vertex at other end of edge is still in heap
            }//If adjacent edge
        }//For each vertex
    }//While queue not empty

}//END shortest path

/***********************************************************************************************
 ***************************GRAPH PROTECTED MEMBER FUNCTIONS***************************************
 ***********************************************************************************************/
void Graph::dfsTraversal( Vertex & v)  // GTM Code Fragment 13.7, p. 616
{
    startVisit(v); //This is for overidden subclass
    visit(v);
    
    //row of matrix
    int row = v.index;
    vector<Edge*> incidentList;
    
    //incidentEdge list
    for (size_t j = 0; j < A.size(); j++)
    {
        if (A[row][j] != -1)
            incidentList.push_back(&(E.at(A[row][j])));
    }//For find incident edges
    
    //index for while loop
    size_t i = 0;
    
    while (!isDone() && i < incidentList.size())
    {
        Edge* e = incidentList.at(i);
        if (!isVisited(*e))
        {
            visit(*e);
            Vertex* w = &(V.at((*e).opposite(v)));
            if (!isVisited(*w))
            {
                traverseDiscovery(*e, v);
                if (!isDone())
                    dfsTraversal(*w);
            }//If vertex is unvisited
            else
            {
                traverseBack(*e, v);
            }//Else vertex has been visited
        }//If edge is unvisited
        i++;
        e = nullptr;
    }//While not done and for each incident edge
    
    if (!isDone()) //finished with v
        finishVisit(v);
    
}//END dfs Traversal

void Graph::initialize()              // resets vertex and edge labels
{
    //Initialize vertex to unvisited
    for (size_t i = 0; i < V.size(); i++)
    {
        if (isVisited(V.at(i)))
        {
            V.at(i).label = VertexLabel::unvisited;
        }//IF unvisited
    }//For Vectors in V
    
    //initialize edges to unvisited
    for (size_t i = 0; i < E.size(); i++)
    {
        if (isVisited(E.at(i)))
        {
            E.at(i).label = EdgeLabel::unvisited;
        }//IF unvisited
    }//END for Vectors in E
    
}//END initialize

#endif /* graph_h */
