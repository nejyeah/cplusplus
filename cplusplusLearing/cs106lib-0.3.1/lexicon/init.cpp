#include "init.h"
#include <iostream>
#include <cstdlib>

/* File : init.cpp
 * Last modified September 2011 by Colin
 * --------------------------------------------------
 * It is important NOT to include genlib.h here,
 * as that renames main() to Main()
 * 
 * This function becomes the entry point for all student programs,
 * responsible for default handling of any ErrorException
 *
 * Limitation: note that this will fail if the student tries to 
 * use command-line parameters with syntax
 *   int main(argc, char * argv[])
 */

int main() {
    int retCode;
    try {
	retCode = Main(); // transfer control to the student's program
    }
    catch(ErrorException e) { // handle uncaught errors
	cerr << "***" << endl
	     << "***  ERROR:  " << e.what() << endl 
	     << "***" << endl;
	exit(EXIT_FAILURE);
    }
    exit(retCode);
}
