//
//  main.cpp
//  project5
//
//  Created by Colin Mills on 11/24/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//


#include "main.h"

int main(int argc, const char * argv[]) {
    try {
        int testingLvl = 4;
        std::string dashes = " ";
        dashes.assign(78,'-');
        string test = "10";
        
        if (testingLvl >= 1) //Tests treeNode and position
        {
            // insert code here...
            cout << dashes << endl;
            std::cout << "Testing Heap...\n\n";
            cout << dashes << endl;
            
            Heap<int, string> pile;
            
            cout << "Testing empty.. should be 1: " << pile.empty() << endl;
            cout << "Testing insert (66, \"CAR\"): \n";
            pile.insert(66, "CAR");
            cout << "Testing empty again.. should be 0: " << pile.empty() << endl;
            
            cout << "Testing insert (99, \"TRUCK\"): \n";
            pile.insert(99, "TRUCK");

            cout << "Testing insert (63, \"T\"), (19, \"T\"), (100, \"T\"), (70, \"T\"), (86, \"T\"): \n";
            pile.insert(63, "T");
            pile.insert(19, "T");
            pile.insert(100, "T");
            pile.insert(70, "T");
            pile.insert(86, "T");
            
            cout << "Testing insert (5, \"S\"), (15, \"R\"): \n";
            pile.insert(5, "S");
            pile.insert(15, "R");
            
            cout << dashes << endl;
            
            cout << "Removing root which should be 5 and should output S: " << pile.remove() << endl;
            
            cout << "Changing the key with value S to 1, which should upHeapBubble \n";
            pile.changeKey(1, "T");
            
            cout << dashes << endl;
            
            cout << "Clearing... \n";
            pile.clear();
            
            cout << "Now it should be empty and print 1: " << pile.empty() << endl;
            
            //cout << pile.remove() << endl;
            cout << dashes << endl;
    
            
        }//if Testinglvl 1
        
        if (testingLvl >= 2) //tests edge, vertex and path
        {
            cout << dashes << endl;
            std::cout << "Testing edge, vertex, and path...\n\n";
            cout << dashes << endl;
            
            cout << "Starting with edge...\n";
            
            Edge one;
            Edge two(0,1,100);
            
            two.label = EdgeLabel::visited;
            
            cout << "one is uninitialzied, evidenced by all values of -1 (a,b,w respectively): "
            << one.a << one.b << one.w << endl;
            
            cout << "two is initialzied, evidenced by all values of 01100 (a,b,w respectively): "
            << two.a << two.b << two.w << endl;
            
            cout << one.labelToString() << " is what edge one is labeled as\n";
            cout << two.labelToString() << " is what edge one is labeled as\n";
            
            Vertex a, b;
            
            a.index = 0;
            b.index = 1;
            
            cout << "Printing opposite of edge two's vertex a (0) which should be vertex b (1): "
            << two.opposite(a) << endl;
            
            cout << dashes << endl;
            cout << "Now testing vertex...\n";
            cout << dashes << endl;
            
            Vertex v1;
            Vertex v2("v2");
            
            //v1.index = 20;
            v2.index = 10000;
            
            v2.label = VertexLabel::visited;
            
            cout << "v1 is uninitialzied, evidenced by values of \"\", unvisited, -1: "
            << endl << v1.name << endl << v1.labelToString() << endl << v1.index << endl;
            
            cout << "v2 is initialzied, evidenced by all values of v2, visited, 10000: "
            <<endl << v2.name << endl << v2.labelToString() << endl << v2.index << endl;
            
            cout << v1.labelToString() << " is what edge one is labeled as\n";
            cout << "Therefore v1 is unvisited and this should be 1: " << v1.unvisited() <<endl;
            cout << v2.labelToString() << " is what edge one is labeled as\n";
            
            cout << "Testing if v1 == v2, should be 0: " << (v1 == v2) << endl;
            
            cout << dashes << endl;
            cout << "Now testing path...\n";
            cout << dashes << endl;
            
            Path p;
            
            v1.name = "v1";
            a.name = "a";
            b.name = "b";
            
            cout << "Pushing v1, v2, a, b onto vector\n";
            p.push_back(v1);
            p.push_back(v2);
            p.push_back(a);
            p.push_back(b);
            
            cout << "The size of p is: " << p.size() << endl;
            cout << "The path of p is: " << p << endl;
            p.pop_back();
            p.pop_back();
            p.clear();
            cout << "p should now be clear..\n";
            cout << dashes << endl;
            
            
        }//if testing lvl 2 edge, vertex, path
        
        if (testingLvl >= 3) //tests graph
        {
            cout << dashes << endl;
            std::cout << "Testing graph...\n\n";
            cout << dashes << endl;
            
            Graph g("/Users/colinmills/Desktop/COSC160/projectFive/project5/project5/france-graph.dta");
            
            g.print();
            
            cout << "Testing components.. should be 1: " << g.components() << endl;
            
            cout << "Tring get vertex by name with \"Nice\": " << g.getVertexByName("nice").name << endl;

            cout << dashes << endl;

            cout << "Trying shortestPath (Djikstra's)\n";

            g.shortestPath(g.getVertexByName("strasbourg"));

            cout << "Distance to paris should be 517: " << g.getDistance(g.getVertexByName("paris")) << endl;

            
        }//if max testing lvl 3
        
        if (testingLvl == 4) //tests finder
        {
            cout << dashes << endl;
            std::cout << "Testing finder...\n\n";
            cout << dashes << endl;
            
            PathFinder p("/Users/colinmills/Desktop/COSC160/projectFive/project5/project5/france-graph.dta");
            
            //france-graph.dta
            Path path = p.find(p.getVertexByName("nice"), p.getVertexByName("montpellier"));
            
            cout << path;
            
        }//if max testing lvl 4
        
    } // try
    catch ( NoSuchObject &e ) {
        cout << "NoSuchObject Error caught " << e.what() << endl;
    } // catch
    catch (DuplicateObject &e) {
        cout << "Dupe Object error caught " <<e.what() << endl;
    } // catch
    catch (IllegalState &e) {
        cout << "Illegal State error caught " <<e.what() << endl;
    } // catch
    catch (...)
    {
        cout << "Unknown error caught in main \n" ;
    }
    return 0;
}//END main

