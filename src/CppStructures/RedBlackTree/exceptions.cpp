//
//  exceptions.cpp
//  projectOne
//
//  Created by Colin Mills on 9/17/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//

#include "exceptions.h"


NoSuchObject::NoSuchObject(string msg)  : logic_error(msg)
{
#ifdef DEBUG_EXCEPTIONS
    std::cout << "Entered NoSuchObject::NoSuchObject(string msg) " << endl;
#endif
    
    //member initialization list does all the work
    //nothing to do here
    /*
     ¯\_(ツ)_/¯
     */
    
#ifdef DEBUG_EXCEPTIONS
    std::cout << "Exiting constructor NoSuchObject::NoSuchObject(string msg)" << endl;
#endif
}// END NoSuchOBject contructor


DuplicateObject::DuplicateObject(string msg)  : logic_error(msg)
{
#ifdef DEBUG_EXCEPTIONS
    std::cout << "Entered constructor DuplicateObject::DuplicateObject(string msg)" << endl;
#endif
    
    //member initialization list does all the work
    //nothing to do here
    
#ifdef DEBUG_EXCEPTIONS
    std::cout << "Exiting constructor DuplicateObject::DuplicateObject(string msg)" << endl;
#endif
}// END DuplicateObject contructor

IllegalState::IllegalState(string msg)  : logic_error(msg)
{
#ifdef DEBUG_EXCEPTIONS
    std::cout << "Entered constructor IllegalState::IllegalState(string msg)" << endl;
#endif
    
    //member initialization list does all the work
    //nothing to do here
    
#ifdef DEBUG_EXCEPTIONS
    std::cout << "Exiting constructor IllegalState::IllegalState(string msg)" << endl;
#endif
}// END IllegalState contructor


