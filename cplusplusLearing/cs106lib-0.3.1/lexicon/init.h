/*
 * File: init.h
 * Last modified on Jul 18 2011 by Colin Leach
 * -----------------------------------------------------
 * A cut-down version of genlib.h
 * init.cpp puts a wrapper around the student program, to catch any
 * ErrorException raised and output a novice-friendly error message.
 * This isn't much documented in Stanford code, but presumably they
 * want to prevent the program barfing a long, confusing error message
 * (machine-dependent - maybe even a stack dump).
 * This is a least-bad-guess implementation by someone who doesn't
 * really know what he's doing, but hopefully it will be adequate.
 */

#ifndef _init_h
#define _init_h

#include <string>
#include <exception>
using namespace std;

extern int Main();

/*
 * Class: ErrorException
 * ---------------------
 * This exception is raised by calls to the Error function, which
 * makes it possible for clients to respond to error conditions
 * without having their programs bomb completely.
 */

class ErrorException : public exception {
public:
    ErrorException(string msg);
    virtual ~ErrorException() throw ();
    virtual const char* what() const throw ();
    //virtual string getMessage();
private:
    string msg;
};

#endif
