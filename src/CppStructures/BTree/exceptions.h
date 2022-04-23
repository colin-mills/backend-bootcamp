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

class NoSuchKey : public std::logic_error
{
public:
    NoSuchKey(string msg = "");
    //the only thing this class does is provide a more accurate error
}; // END NoSuchKey


class DuplicateKey : public std::logic_error
{
public:
    DuplicateKey(string msg = "");
    //the only thing this class does is provide a more accurate error
}; // END DuplicateKey

class IllegalState : public std::logic_error
{
public:
    IllegalState(string msg = "");
    //the only thing this class does is provide a more accurate error
}; // END IllegalState



#endif /* exceptions_h */

