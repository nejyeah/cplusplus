/* File : strutils.cpp
 * Last modified September 2011
 * -----------------------------------
 * Invalid conversions raise an ErrorException, 
 * which will be caught by init.cpp code 
 * unless the student chooses to handle them
 */


#include <sstream>
#include <string>
#include "genlib.h"

/*
 * Function: IntegerToString
 * Usage: s = IntegerToString(n);
 */

string IntegerToString(int num) {
    stringstream result;
    result << num;
    return result.str();
}

/*
 * Function: RealToString
 * Usage: s = RealToString(d);
 */

string RealToString(double num) {
    stringstream result;
    result << num;
    return result.str();
}

/*
 * Function: StringToInteger
 * Usage: n = StringToInteger(s);
 */

int StringToInteger(string str)
{
    int returnVal;
    istringstream result(str);
    string rest;

    if ((result >> returnVal).fail()) {
	Error("Not a valid number!");
    }
    result >> rest;
    if (rest != "") {
	Error("Extra characters not allowed");
    }
    return returnVal;
}

/*
 * Function: StringToReal
 * Usage: d = StringToReal(s);
 */

double StringToReal(string str) {
    double returnVal;
    istringstream result(str);
    string rest;

    if ((result >> returnVal).fail()) {
	Error("Not a valid number!");
    }
    result >> rest;
    if (rest != "") {
	Error("Extra characters not allowed");
    }
    return returnVal;
}

/*
 * Function: ConvertToLowerCase
 * Usage: s = ConvertToLowerCase(s);
 */

string ConvertToLowerCase(string str)
{
    const int length = str.length();
    for(int i=0; i < length; i++) {
	    str[i] = tolower(str[i]);
	}
    return str;
}

/*
 * Function: ConvertToUpperCase
 * Usage: s = ConvertToUpperCase(s);
 */

string ConvertToUpperCase(string str) {
    const int length = str.length();
    for(int i=0; i < length; i++) {
	    str[i] = toupper(str[i]);
	}
    return str;
}

