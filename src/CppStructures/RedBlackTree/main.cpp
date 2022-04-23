//
//  main.cpp
//  project2
//
//  Created by Colin Mills on 9/25/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//


#include "main.h"


//#include <chrono>


int main(int argc, const char * argv[]) {
    try {
        int testingLvl = 5;
        std::string dashes = " ";
        dashes.assign(78,'-');
        string test = "10";
        
        if (testingLvl == 1) //Tests treeNode and position
        {
            // insert code here...
            cout << dashes << endl;
            std::cout << "Testing default RBNode...\n\n";
            cout << dashes << endl;
            
            RBNode<string> defaultNode;
            
            cout << "Default string value in Tree Node " << defaultNode.object << endl;
            
            cout << "Default parent value in Tree Node " << defaultNode.parent << endl;
            
            cout << "Default left ptr value in Tree Node " << defaultNode.leftPtr << endl;
            
            cout << "Default right ptr value in Tree Node " << defaultNode.rightPtr << endl << endl;
            cout << dashes << endl;
            
            std::cout << "Testing set RBNode with initializer list...\n\n";
            
            
            RBNode<string> testNode(test);
            RBNode<string>* testPtr = &testNode;
            cout << "test Tree Node has addrress of " << testPtr
            << " which will be parent of set Node."
            << endl;
            RBNode<string> setNode (test, testPtr, nullptr);
            
            cout << "Set string value in Tree Node " << setNode.object << endl;
            
            cout << "Set parent value in Tree Node " << setNode.parent << endl;
            
            cout << "Set left ptr value in Tree Node " << setNode.leftPtr << endl;
            
            cout << "Set right ptr value in Tree Node " << setNode.rightPtr << endl <<endl;
            cout << dashes << endl;
            
            
            std::cout << "Testing position...\n\n";
            
            Position<string> pos(testPtr);
            
            cout << "Testing testPtr value of position which should be 10: " << *pos << endl;
            
            testPtr = &defaultNode;
            
            Position<string> def(testPtr);
            
            cout << "Testing default value of string which should be 0: " << *def << endl;
            
            cout << dashes << endl;
        }//if Testinglvl 1
        
        if (testingLvl == 2) //tests iterator
        {
            cout << dashes << endl;
            std::cout << "Testing iterator...\n\n";
            cout << dashes << endl;
            
            RBNode<string> testNode(test); //test node set to 10 and null
            RBNode<string>* testPtr = &testNode;
            Position<string> pos(testPtr);
            
            //Create two of the same iterator
            Iterator<string> one(pos);
            Iterator<string> two(pos);
            
            cout << "Testing dereferencing operator of one to see value of 10: "
            << (*one) << endl;
            
            cout << dashes << endl;
            
            cout << "Testing if equality operator works for equal iterators, "
            << "should output 1: " << (one==two) << endl;
            
            cout << "Testing if in-equality operator works for equal iterators, "
            << "should output 0: " << (one!=two) << endl;
            
            cout << dashes << endl;
            
            cout << "Testing if equality operator works for the same iterators, "
            << "should output 1: " << (one==one) << endl;
            
            cout << "Testing if in-equality operator works for the same iterators, "
            << "should output 0: " << (two!=two) << endl;
            
            cout << dashes << endl;
            
            RBNode<string> defaultNode;//(12, testPtr); //default node set to 0 and null
            testPtr = &defaultNode;
            Position<string> posTwo(testPtr);
            //Creat diferent iterator
            Iterator<string> three(posTwo); //(posTwo);
            
            
            
            cout << "Testing if equality operator works for different iterators,"
            << " should output 0: " << (three==one) << endl;
            
            cout << "Testing if in-equality operator works with diferent iterators,"
            << " should output 1: " << (two!=three) << endl;
            
            cout << dashes << endl;
            
        }//if testing lvl 2 (iterator)
        
        if (testingLvl == 3) //tests RBTree
        {
            cout << dashes << endl;
            std::cout << "Testing  RBTree...\n\n";
            cout << dashes << endl;
            
            std::cout << "Testing  default contructor...\n\n";
            cout << dashes << endl;
            RBTree<char> first;
            
            std::cout << "Testing begin() and end() which should be the same... \n";
            Iterator<char> f(first.begin());
            cout << "Begin: " << f.getObj() << endl;
            Iterator<char> s(first.end());
            cout << "End: " << s.getObj() << endl;
            std::cout << "Testing begin() == end ()which should be 1: " << (s == f) << endl;
            std::cout << "Testing clear() which should do nothing..." << endl;
            first.clear();
            std::cout << "Testing empty() which should be 1: " << first.empty() << endl;
            //std::cout << "Testing find('e') which should be throw error: " <<  endl;
            //first.find('e');
            std::cout << "Testing height() which should be 0: " << first.height() << endl;
//            std::cout << "Testing insert('e') " << endl;
//            first.insert('e');
//            std::cout << "Testing height() which should be 1: " << first.height() << endl;
//            std::cout << "Testing insert(h,m,k,l,p,d,f,o,s,q,r) " << endl;
//            first.insert('h');
//            first.insert('m');
//            first.insert('k');
//            first.insert('l');
//            first.insert('p');
//            first.insert('d');
//            first.insert('f');
//            first.insert('o');
//            first.insert('s');
//            first.insert('q');
//            first.insert('r');
            
            //e, h, m, p, d, f, o, s, q, r, t, u
            std::cout << "Testing insert(e, h, m, p, d, f, o, s, q, r, t, u) " << endl;
            first.insert('e');
            first.insert('h');
            first.insert('m');
            first.insert('p');
            first.insert('d');
            first.insert('f');
            first.insert('o');
            first.insert('s');
            first.insert('q');
            first.insert('r');
            first.insert('t');
            first.insert('u');
            
            std::cout << "Testing height() which should be 5: " << first.height() << endl; //Not 7 anymore
            std::cout << "Testing find('e') : " ;
            cout << (*first.find('e')) << endl;
            
            //Measure run time of preordertolist
            std::cout << "Testing preordertolist()... " << endl;
            //std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            list<Position<char>> thisList(first.preorderToList());
            //std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            
            //print this time diference
            //Code to measure time diference used from stack overflow
            //Credits: https://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
            //cout << "Time difference = " <<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
            //cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
            while (!thisList.empty())
            {
                cout << (*(thisList.front())) << endl;
                thisList.pop_front();
            }//While not empty
//            std::cout << "Testing remove: " << first.remove('m') << endl;
//            std::cout << "Testing remove: " << first.remove('h') << endl;
//            std::cout << "Testing remove: " << first.remove('q') << endl;
//            std::cout << "Testing remove: " << first.remove('r') << endl;
//            std::cout << "Testing remove: " << first.remove('f') << endl;
//            std::cout << "Testing remove: " << first.remove('e') << endl;
//            std::cout << "Testing height() which should be 4: " << first.height() << endl;
            std::cout << "Testing remove: " << first.remove('m') << endl;
            std::cout << "Testing remove: " << first.remove('u') << endl;
            std::cout << "Testing remove: " << first.remove('t') << endl;
            std::cout << "Testing remove: " << first.remove('f') << endl;
//            std::cout << "Testing remove: " << first.remove('o') << endl;
//            std::cout << "Testing remove: " << first.remove('r') << endl;
//            std::cout << "Testing remove: " << first.remove('e') << endl;
//            std::cout << "Testing remove: " << first.remove('h') << endl;
//            std::cout << "Testing remove: " << first.remove('p') << endl;
//            std::cout << "Testing remove: " << first.remove('d') << endl;
//            std::cout << "Testing remove: " << first.remove('s') << endl;
//            std::cout << "Testing remove: " << first.remove('q') << endl;

            std::cout << "Testing height() which should be 4: " << first.height() << endl;

            //std::cout << "Testing clear()" << endl;
            //first.clear();
            //std::cout << "Testing height() which should now be 0: " << first.height() << endl;
            
            cout << dashes << endl;
            std::cout << "Testing  copy contructor...\n\n";
            cout << dashes << endl;
            RBTree<char> second(first);
            
            std::cout << "Testing begin() and end() which should not be the same... \n";
            Iterator<char> ff(second.begin());
            cout << "Begin: " << ff.getObj() << endl;
            Iterator<char> ss(second.end());
            cout << "End: " << ss.getObj() << endl;
            std::cout << "Testing begin() == end() which should be 0: " << (ss == ff) << endl;
            //std::cout << "Testing clear() which should do nothing..." << endl;
            //first.clear();
            std::cout << "Testing empty() which should be 0: " << second.empty() << endl;
            //std::cout << "Testing find('e') which should be throw error: " <<  endl;
            //first.find('e');
            std::cout << "Testing height() which should be 4: " << second.height() << endl;
            //            std::cout << "Testing insert('e') " << endl;
            //            first.insert('e');
            //            std::cout << "Testing height() which should be 1: " << first.height() << endl;
            //            std::cout << "Testing insert(h,m,k,l,p,d,f,o,s,q,r) " << endl;
            //            first.insert('h');
            //            first.insert('m');
            //            first.insert('k');
            //            first.insert('l');
            //            first.insert('p');
            //            first.insert('d');
            //            first.insert('f');
            //            first.insert('o');
            //            first.insert('s');
            //            first.insert('q');
            //            first.insert('r');
            //            std::cout << "Testing height() which should be 7: " << first.height() << endl;
            std::cout << "Testing preordertolist()... " << endl;
            list<Position<char>> thatList(second.preorderToList());
            while (!thatList.empty())
            {
                cout << (*(thatList.front())) << endl;
                thatList.pop_front();
            }//While not empty
            //            std::cout << "Testing remove: " << first.remove('m') << endl;
            //            std::cout << "Testing remove: " << first.remove('h') << endl;
            //            std::cout << "Testing remove: " << first.remove('q') << endl;
            //            std::cout << "Testing remove: " << first.remove('r') << endl;
            //            std::cout << "Testing remove: " << first.remove('f') << endl;
            //            std::cout << "Testing remove: " << first.remove('e') << endl;
            //            std::cout << "Testing height() which should be 4: " << first.height() << endl;
            //            std::cout << "Testing clear()" << endl;
            second.clear();
            std::cout << "Testing height() which should now be 0: " << second.height() << endl;
            
            cout << dashes << endl;
            std::cout << "Testing copy list run time...\n\n";
            cout << dashes << endl;
            
            RBTree<int> third;
            RBTree<int> fourth;
            
            //srand(static_cast<unsigned int>(time(nullptr))); //Initialize random seed
            
            for (int i = 0; i < 100; i++)
            {
                third.insert(rand());
            }//for add tree values
     
            
            std::cout << "Testing height(): " << third.height() << endl;
            //Measure run time of preordertolist
            
            std::cout << "Testing preordertolist()... " << endl;
            //begin = std::chrono::steady_clock::now();
//            list<Position<int>> anotherList(third.preorderToList());
//            while (!anotherList.empty())
//            {
//                cout << (*(anotherList.front())) << endl;
//                anotherList.pop_front();
//            }//While not empty
            //end = std::chrono::steady_clock::now();
            
            //print this time diference
            //cout << "Time difference = " <<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
            //cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
            
            
            std::cout << "Testing overloaded = ... " << endl;
            //begin = std::chrono::steady_clock::now();
            fourth = third;
            std::cout << "Testing height(): " << fourth.height() << endl;
            //end = std::chrono::steady_clock::now();
            
            //cout << "Time difference = " <<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
            //cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
            
            cout << dashes << endl;
 
        }//if max testing lvl 3
        
        if (testingLvl == 4) //tests RBTree special cases
        {
            RBTree<string> first;
            
            //            test 33: Empty BST, Iterator, opreator*, exception
            //            RBTree<int> first;
            //            Iterator<int> it(first.begin());
            //            cout << *it << endl;
            //            test 34: Empty BST, Iterator, opreator++, exception: FAIL (Error code 11)
            
            //            it++;
            
            
            
            
            //            test 35: Characters, Iterator: FAIL (E)
            //RBTree<char> first;
            
            std::cout << "Testing insert('e') " << endl;
            first.insert("e");
            std::cout << "Testing insert(h,m,k,l,p,d,f,o,s,q,r) " << endl;
            first.insert("h");
            first.insert("m");
            first.insert("k");
            first.insert("l");
            first.insert("p");
            first.insert("d");
            //first.insert("d");
            first.insert("f");
            first.insert("o");
            first.insert("s");
            first.insert("q");
            first.insert("r");
            
            
            std::cout << "Testing remove: " << first.remove("m") << endl;
            std::cout << "Testing remove: " << first.remove("h") << endl;
            std::cout << "Testing remove: " << first.remove("q") << endl;
            std::cout << "Testing remove: " << first.remove("r") << endl;
            std::cout << "Testing remove: " << first.remove("f") << endl;
            std::cout << "Testing remove: " << first.remove("e") << endl;
            
            //Iterator<string>
            
            //            first.remove("e");
            //            first.remove("h");
            //            first.remove("m");
            //            first.remove("k");
            //            first.remove("l");
            //            first.remove("p");
            //            first.remove("d");
            //            first.remove("f");
            //            first.remove("o");
            //            first.remove("s");
            //            first.remove("q");
            //            first.remove("r");
            
            
            
            Iterator<string> it(first.begin());
            
            Iterator<string> itt(first.find("d"));
            
            cout << (itt == it) << endl;
            
            cout << (itt != it) << endl;
            
            
            //            while (it.getObj() != "")
            //            {
            //                cout << "Value: " << *it << endl;
            //                it++;
            //            }
        }//if max testing lvl 4
        if (testingLvl == 5) //Tests treeNode and position
        {
            cout << dashes << endl;
            std::cout << "Testing special cases p4...\n\n";
            cout << dashes << endl;
            
            RBTree<int> t;
            t.insert(1);
            t.insert(2);
            t.insert(3);
            
            Iterator<int> it(t.find(1));
            
            it++;
            it++;
            it++;
            
        }//if Testinglvl 1
        

        
//        test 44: Iterator, opreator++, Exception: FAIL
//        test 45: GTM Fig. 10.32(q), Iterator: FAIL (E)

        
//        test 48: GTM Fig. 10.32(q), find, Iterator: FAIL (E)

        
//        test 51: GTM Fig. 10.32(q), copy constructor, remove roots, valgrind: FAIL (E)
//        test 52: GTM Fig. 10.32(q), empty.operator=, remove roots, valgrind: FAIL (E)
//        test 53: GTM Fig. 10.32(q), operator=, remove roots, valgrind: FAIL (E)
        
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
    
    
    
}
