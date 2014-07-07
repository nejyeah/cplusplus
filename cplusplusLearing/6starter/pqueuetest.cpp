/*
 * File: pqueuetest.cpp
 * --------------------
 * Implementation file for the the module which test the
 * different operations of a PQueue.   You may want to edit
 * the code to add more specific or thorough tests of your own.
 *
 * Julie Zelenski, CS106, Fall 2007
 */

#include "genlib.h"
#include "pqueuetest.h"
#include "simpio.h"
#include "random.h"
#include <iostream>

bool ArrayIsSorted(int array[], int size);


/*
 * Function: BasicPQueueTest
 * Usage: BasicQueueTest();
 * ------------------------
 * Runs a test of the PQueue focusing on simple enqueue, dequeueMax.
 * Reports results of test to cout.
 */
void BasicPQueueTest()
{
	PQueue pq;
	
	cout << boolalpha;	// configure stream to print booleans as true/false instead of 1/0
	cout << endl << "-----------   Testing Basic PQueue functions -----------" << endl;
	cout << "The pqueue was just created.  Is it empty? " << pq.isEmpty() << endl;
	
	cout << endl << "Now enqueuing integers from 1 to 10 (increasing order)" << endl;
	for (int i = 1; i <= 10; i++)
		pq.enqueue(i);
	
	cout << "Pqueue should not be empty.  Is it empty? " << pq.isEmpty() << endl;
	cout << "Pqueue should have size = 10.  What is size? " << pq.size() << endl;
	pq.printDebuggingInfo();

	cout << "Dequeuing the top 5 elements: ";
	for (int j = 0; j < 5; j++)
		cout << pq.dequeueMax() << " ";
	cout << endl << "Pqueue should have size = 5.  What is size? " << pq.size() << endl;
	pq.printDebuggingInfo();
		
	cout << endl << "Dequeuing all the rest: ";
	while (!pq.isEmpty())
		cout << pq.dequeueMax() << " ";
	cout << endl << "Pqueue should be empty.  Is it empty? " << pq.isEmpty() << endl;
	pq.printDebuggingInfo();

	cout << endl << "Hit return to continue: ";
	GetLine();
}


/*
 * Function: MoreQueueTest
 * Usage: MoreQueueTest();
 * -----------------------
 * Tests a few more enqueue, dequeueMax, some boundary cases explored.
 * Reports results of test to cout.
 */
void MorePQueueTest()
{
	PQueue pq;
	
	cout << boolalpha;
	cout << endl << "-----------   More pqueue testing functions -----------" << endl;

	cout << endl << "Enqueuing integers from 15 downto 1 (decreasing order)" << endl;
	for (int i = 15; i > 0; i--)
		pq.enqueue(i);
	
	cout << "Enqueuing duplicates for even numbers 2 to 14" << endl;
	for (int j = 2; j <= 14; j += 2)
		pq.enqueue(j);

	cout << "Dequeuing the top 10 elements: ";
	for (int k = 0; k < 10; k++)
		cout << pq.dequeueMax() << " ";
		
	cout << endl << "Dequeuing all the rest: ";
	while (!pq.isEmpty())
		cout << pq.dequeueMax() << " ";
	cout << endl << "Pqueue should be empty.  Is it empty? " << pq.isEmpty() << endl;

	// The line below calling DequeueMax should cause your program to halt with an error.
	// Once you've verified that your PQueue correctly raises this error
	// you should comment out the call, so that you can continue on with the other tests.
	cout << endl << "This next test raises an error if your pqueue is working correctly." << endl;
	cout << "Once you verify the test, comment it out to move on to the other tests." << endl;
	cout << "(Comment out line " << __LINE__ + 1 << " in the file " << __FILE__ << ")." << endl;
	cout << "Dequeue from empty pqueue returns " << pq.dequeueMax() << endl;

	cout << endl << "Hit return to continue: ";
	GetLine();
}

		

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
void PQueueSortTest()
{
	const int SortSize = 500;
	int array[SortSize];
	
	cout << endl << "-----------   Testing use of pqueue to sort  -----------" << endl;
	
	cout << "Enqueuing " << SortSize << " numbers into pqueue in increasing order." << endl;
	for (int i = 0; i < SortSize; i++) array[i] = i;
	PQSort(array, SortSize);
	cout << "Using dequeue to pull out numbers in sorted order.  Are they sorted? " <<
		ArrayIsSorted(array, SortSize) << endl;

	cout << "Enqueuing " << SortSize << " random values into the pqueue." << endl;
	for (int j = 0; j < SortSize; j++) array[j] = RandomInteger(1, 1000);
	PQSort(array, SortSize);
	cout << "Using dequeue to pull out numbers in sorted order.  Are they sorted? " <<
		ArrayIsSorted(array, SortSize) << endl;
	
	cout << endl << "Hit return to continue: ";
	GetLine();
}

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

void PQSort(int array[], int nElems)
{
	PQueue pq;
	for (int i = 0; i < nElems; i++)	
		pq.enqueue(array[i]);
	for (int i = nElems-1; i >= 0; i--)
		array[i] = pq.dequeueMax();
}


// Simple prredicate to verify array is sorted in increasing order
bool ArrayIsSorted(int array[], int size)
{
	for (int i = 0; i < size-1; i++)	
		if (array[i] > array[i+1]) return false;
	return true;
}

