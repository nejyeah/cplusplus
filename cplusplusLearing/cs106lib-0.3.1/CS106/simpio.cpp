/* File : simpio.cpp
 * Last modified September 2011 by Colin
 *
 * Based on the discussion in the CS106L Course Reader, chapter 3
 * http://www.stanford.edu/class/cs106l/course_reader.html
 */

#include <iostream>
#include <sstream>
#include "genlib.h"


/*
 * Function: GetLine
 * Usage: s = GetLine();
 */
 
string GetLine() {
    string result;

	getline(cin, result);
	if (cin.fail()) {
	    result = "";
	    cin.clear();
	}

    return result;
}

/*
 * Function: GetInteger
 * Usage: n = GetInteger();
 */
 
int GetInteger() {
    while(true) {
	stringstream converter;
	converter << GetLine();

	int result;
	if (converter >> result) {
	    char remaining;
	    if(converter >> remaining)
		cout << "Unexpected character: " << remaining << endl;
	    else
		return result;
	} else
	    cout << "Please enter an integer." << endl;      
    }
}


/*
 * Function: GetLong
 * Usage: n = GetLong();
 */
 
long GetLong() {
    while(true) {
	stringstream converter;
	converter << GetLine();

	long result;
	if(converter >> result) {
	    char remaining;
	    if(converter >> remaining)
		cout << "Unexpected character: " << remaining << endl;
	    else
		return result;
	}
	else
	    cout << "Please enter an integer (long)." << endl;      
   }
}

/*
 * Function: GetReal
 * Usage: x = GetReal();
 */

double GetReal() {
    while(true)	{
	stringstream converter;
	converter << GetLine();

	double result;
	if (converter >> result) {
	    char remaining;
	    if (converter >> remaining)
		cout << "Unexpected character: " << remaining << endl;
	    else
		return result;
	}
	else
	    cout << "Please enter a floating-point number.";      
    }
}


