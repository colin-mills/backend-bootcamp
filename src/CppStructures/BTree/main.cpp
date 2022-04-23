//
//  main.cpp
//  project3
//
//  Created by Colin Mills on 10/21/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//

#include "main.h"


int main(int argc, const char * argv[]) {
    try {
        int testingLvl = 4;
        string dashes = " ";
        dashes.assign(78,'-');
        
        if (testingLvl == 1) //Tests node and position
        {
            // insert code here...
            cout << dashes << endl;
            cout <<"Testing 1...nodes \n\n";
            cout << dashes << endl;
            
            BTNode<int> newNode(3);
            
            cout << "confirming node is not full: " << newNode.isFull() << endl;
            cout << "confirming node is internal: " << newNode.isInternal() << endl;
            cout << "confirming node has one child: " <<newNode.nChildren() << endl;
            
            //Position<int> newPos(&newNode);
            
            //newPos[2];
            
           
        }//if Testinglvl 1
        
        if (testingLvl == 2) //insertion
        {
            cout << dashes << endl;
            cout <<"Testing 2... \n\n";
            
        
        
            BTree<int> t;
            
            t.insert(1);
            cout << "Height should be 0: " << t.height() << endl;
            t.insert(2);
            t.insert(3);
            t.insert(4);
            t.insert(5);
            t.insert(6);
            
            for (int i = 7; i < 10; i++)
                t.insert(i);
            
            cout << "Height should be 2: " << t.height() << endl;
            t.printTree();
            
            cout << dashes << endl;
            //t.find(47);
            
        
        
        }//if testing lvl 2
        
        if (testingLvl == 3) //removal HW1
        {
            cout << dashes << endl;
            cout <<"Test 3 removals... \n\n";
            cout << dashes << endl;
            
            BTree<char> t;
            
            
            
            t.insert('e');
            t.insert('h');
            t.insert('m');
            t.insert('p');
            t.insert('d');
            t.insert('f');
            t.insert('o');
            t.insert('s');
            t.insert('q');
            t.insert('r');
            t.insert('t');
            t.insert('u');
            
            //t.printTree();
            
            t.remove('s'); //case 2b, case 1
            t.remove('d'); //case 3a, case 1
            t.remove('h'); //case 2a
            t.remove('q'); //case (2a, 3b, 1)
            //t.printTree();
            t.remove('m'); //case 3b, 1
            
            t.remove('f'); //case(2c, 1)
            t.remove('r'); //case(3a, 1)
            t.printTree();
            
            cout <<"Test special case 2c... \n\n";
            cout << dashes << endl;
            
            BTree<int> tt;
            tt.insert(1);
            tt.insert(2);
            tt.insert(3);
            tt.insert(4);
            
            tt.remove(4);
            tt.printTree();
            tt.remove(2);
            tt.printTree();
        }//if testing lvl 3
        if (testingLvl == 4) //tests special case 2c
        {
            cout << dashes << endl;
            cout <<"Test 4 autograder fixes... \n\n";
            cout << dashes << endl;
            
            
        }//if max testing lvl 4
        
    } // try
    catch ( NoSuchKey &e ) {
        cout << "NoSuchKey Error caught " << e.what() << endl;
    } // catch
    catch (DuplicateKey &e) {
        cout << "Dupe Key error caught " <<e.what() << endl;
    } // catch
    catch (IllegalState &e) {
        cout << "Illegal State error caught " <<e.what() << endl;
    } // catch
    catch (out_of_range &e) {
        cout << "Out Of Range error caught " <<e.what() << endl;
    } // catch
    catch (...)
    {
        cout << "Unknown error caught in main \n" ;
    }
    return 0;
    
    
    
}
