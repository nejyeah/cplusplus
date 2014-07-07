/*
 * File: pqueuetest.h
 * ------------------
 * This module exports some functions to test the different
 * operations of a PQueue object.  These functions are useful for
 * testing a new implementation for correctness.
 * 
 * Julie Zelenski, CS106
 */

#ifndef _pqueuetest_h
#define _pqueuetest_h

#include "pqueue.h"

/*
 * Function: BasicPQueueTest
 * Usage: BasicQueueTest();
 * ------------------------
 * Runs a test of the PQueue focusing on simple enqueue, dequeueMax.
 * Reports results of test to cout.
 */
void BasicPQueueTest();

/*
 * Function: MoreQueueTest
 * Usage: MoreQueueTest();
 * -----------------------
 * Tests a few more enqueue, dequeueMax, some boundary cases explored.
 * Reports results of test to cout.
 */
void MorePQueueTest();

/*
 * Function: PQueueSortTest
 * Usage: PQueueSortTest();
 * ------------------------
 * Tests the use of the priority queue to implement a sort algorithm.  Enqueues
 * a bunch of values into pqueue and then pull them out using dequeueMax to arrange in
 * array in sorted order.  Tries it with random data inserted and then two more times
 * with data inserted in sorted order (both forward and backward) to learn how
 * the performance is affected by already sorted data.
 */
void PQueueSortTest();


/*
 * Function: PQSort
 * Usage: PQSort(arr, n);
 * ----------------------
 * Uses the priority queue to sort an array.  Inserts all values from array into
 * a pqueue and then pulls them out with dequeueMax and assigns into array into
 * sorted order.  Depending on the running times of the underlying PQueue, this 
 * can be a pretty decent sorting algorithm (for example, when using heap implementation
 * this is effectively HeapSort). This routine is exported since it is used by
 * the performance module as well as the test module.
 */
void PQSort(int array[], int nElems);

#endif
