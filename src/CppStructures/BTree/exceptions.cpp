//
//  exceptions.cpp
//  projectOne
//
//  Created by Colin Mills on 9/17/20.
//  Copyright © 2020 Colin Mills. All rights reserved.
//

#include "exceptions.h"


NoSuchKey::NoSuchKey(string msg)  : logic_error(msg)
{
#ifdef DEBUG_EXCEPTIONS
    std::cout << "Entered NoSuchKey::NoSuchKey(string msg) " << endl;
#endif
    
    //member initialization list does all the work
    //nothing to do here
    /*
     ¯\_(ツ)_/¯
     */
    
#ifdef DEBUG_EXCEPTIONS
    std::cout << "Exiting constructor NoSuchKey::NoSuchKey(string msg)" << endl;
#endif
}// END NoSuchKey contructor


DuplicateKey::DuplicateKey(string msg)  : logic_error(msg)
{
#ifdef DEBUG_EXCEPTIONS
    std::cout << "Entered constructor DuplicateKey::DuplicateKey(string msg)" << endl;
#endif
    
    //member initialization list does all the work
    //nothing to do here
    
#ifdef DEBUG_EXCEPTIONS
    std::cout << "Exiting constructor DuplicateKey::DuplicateKey(string msg)" << endl;
#endif
}// END DuplicateKey contructor

IllegalState::IllegalState(string msg)  : logic_error(msg)
{
#ifdef DEBUG_EXCEPTIONS
    std::cout << "Entered constructor IllegalState::IllegalState(string msg)" << endl;
#endif
    //TODO: is this included?
    //member initialization list does all the work
    //nothing to do here
    
#ifdef DEBUG_EXCEPTIONS
    std::cout << "Exiting constructor IllegalState::IllegalState(string msg)" << endl;
#endif
}// END IllegalState contructor


