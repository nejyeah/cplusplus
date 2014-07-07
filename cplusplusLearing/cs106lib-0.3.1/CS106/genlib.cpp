/*
 * File: genlib.cpp
 * Last modified September 2011 by Colin
 * ----------------
 * This file implements the genlib.h interface
 * It is needed by programs using the Stanford CS106B libraries
 * If the ErrorException is unhandled by student code, it will
 * be caught by init.cpp code, which wraps around the student's
 * main() function
 */

#include "genlib.h"
#include <cstdlib>
#include <iostream>

ErrorException::ErrorException(string m="unspecified custom error") 
: msg(m) {
}

ErrorException::~ErrorException() throw() {}

const char* ErrorException::what() const throw() {
    return this->msg.c_str(); 
}

void Error(string str) {
    ErrorException err(str);
    throw err;
}


