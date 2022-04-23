/*
 * exceptions.h
 *
 */


#ifndef exceptions_h
#define exceptions_h

//#define DEBUG_EXCEPTIONS

//nescesary preprocessor directives
#include <iostream>
#include <stdexcept>
#include <exception>

//nescesary namespace
using namespace std;

class NoSuchObject : public std::logic_error
{
public:
    NoSuchObject(string msg = "");
    //the only thing this class does is provide a more accurate error
}; // END NoSuchObject


class DuplicateObject : public std::logic_error
{
public:
    DuplicateObject(string msg = "");
    //the only thing this class does is provide a more accurate error
}; // END DuplicateObject

class IllegalState : public std::logic_error
{
public:
    IllegalState(string msg = "");
    //the only thing this class does is provide a more accurate error
}; // END IllegalState



#endif /* exceptions_h */

