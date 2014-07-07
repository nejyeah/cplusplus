/* File: main.cpp
 * --------------
 * Simple main module for PQueue assignment.
 */
 
#include "pqueuetest.h"
#include "performance.h"
#include <iostream>
#include "genlib.h"


/*
 * Use these functions to test your PQueue implementation.
 * Comment out those tests you aren't interested in running
 * while you are mid-development.
 */
int main()
{
	BasicPQueueTest();
	MorePQueueTest();
	PQueueSortTest();
   	PQueuePerformance();
    cout << endl << "Goodbye and have a nice day!" << endl;
    return (0);
}

