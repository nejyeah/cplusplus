/*
 * File: performance.cpp
 * ---------------------
 * Implementation for the the performance testing module.  These
 * functions allow you to test a PQueue implementation in order
 * to evaluate its performance, both in time trials and in memory usage.
 * You shouldn't need to edit any code in this module.
 *
 * Julie Zelenski, CS106, Winter 2008
 */
 
#include "pqueue.h"
#include "performance.h"
#include "pqueuetest.h"
#include "genlib.h"
#include "random.h"
#include "simpio.h"
#include <ctime>
#include <iostream>

const int NumRepetitions = 1000;	// enough repetitions to register on system clock
const int MinTrialSize =  10000;
const int MaxTrialSize = 1000000;

void RunEnqueueDequeueTrial(int size);
void RunSortTrial(int size);
void RunMemoryTrial(int size);
double GetCurrentTime();
void RunPerformanceTrial(int size);


void PQueuePerformance()
{
    cout << endl << "Now, let's run an empirical time trial." << endl;
    
    while (true) {
        int size;
    	while (true) {
	    	cout << endl << "How large a pqueue to time? (" 
	    	     << MinTrialSize << " to " << MaxTrialSize << ", or 0 to quit): ";
	    	size = GetInteger();
	    	if (size == 0) return;
	        if (size >= MinTrialSize && size <= MaxTrialSize) break;
			cout << "Please use a size in the supported range." << endl;
    	}
	    RunPerformanceTrial(size);
    }
}

/*
 * Function: RunPerformanceTrial
 * -----------------------------
 * Runs a time trial using pqueues of specified size.  The first 2 time trials report
 * the amount of time necessary to enqueue/dequeue and use pqueue to sort.
 * The last trial reports on memory usage.
 */
void RunPerformanceTrial(int size)
{
	Randomize();
	PQueue pq;
	cout << endl << "---- Performance for " << size << "-element pqueue (" << pq.implementationName() << ")" << " -----" << endl << endl;
	RunEnqueueDequeueTrial(size);
	RunSortTrial(size);
    RunMemoryTrial(size);
    cout << endl << "------------------- End of trial ---------------------" << endl << endl;
}




/*
 * Function: RunEnqueueDequeueTrial
 * --------------------------------
 * Runs the enqueue & dequeue time trials for the specified
 * pqueue size.  Reports results to cout.
 * Note that we just randomly choose numbers to insert.
 * The amount of time it takes to do one enqueue/dequeue is
 * too small to be accurately measured, so we do many iterations in 
 * a loop and time that.
 */
void RunEnqueueDequeueTrial(int size)
{
	PQueue pq;
	
	for (int i = 0; i < size; i++)
		pq.enqueue(RandomInteger(1,size));
	
    cout << "Time to enqueue into " << size << "-element pqueue: " << flush;
    double start = GetCurrentTime();
    for (int j = 0; j < NumRepetitions; j++) 
	    pq.enqueue(RandomInteger(1, 2*size));
    cout << 1000*(GetCurrentTime() - start)/NumRepetitions << " usecs" << endl;

    cout << "Time to dequeue from " << size << "-element pqueue: " << flush;
    start = GetCurrentTime();
    for (int k = 0; k < NumRepetitions; k++) 
	    pq.dequeueMax();
    cout << 1000*(GetCurrentTime() - start)/NumRepetitions << " usecs" << endl;
}




/*
 * Function: RunSortTrial
 * ----------------------
 * Runs the sorting time trial for the specified pqueue size.
 * Reports results to cout.
 */
void RunSortTrial(int size)
{
	int *array = new int[size];
	for (int i = 0; i < size; i++)		// put random data into array
		array[i] = RandomInteger(1, size);
		
    cout << "Time to pqsort random sequence of " << size << " elements: " << flush;
	double start = GetCurrentTime();
	PQSort(array, size);
    cout << GetCurrentTime() - start << " msecs" << endl;
	
    cout << "Time to pqsort sorted sequence of " << size << " elements: " << flush;
	for (int j = 0; j < size; j++)		// put data in array already sorted 
		array[j] = j;
	start = GetCurrentTime();
	PQSort(array, size);
    cout << GetCurrentTime() - start << " msecs" << endl;
	
    cout << "Time to pqsort reverse-sorted sequence of " << size << " elements: " << flush;
	for (int k = 0; k < size; k++)		// put data in array already reverse sorted 
		array[k] = size - k;
	start = GetCurrentTime();
	PQSort(array, size);
    cout << GetCurrentTime() - start << " msecs" << endl;

	delete [] array;
}

/*
 * Function: RunMemoryTrial
 * ------------------------
 * Fills a pqueue to specified size and reports memory usage.  Then does
 * a bunch of enqueue-dequeue operations to jumble things up and reports
 * on the memory usage again. Reports results to cout.
 */
void RunMemoryTrial(int size)
{
    PQueue pq;
    cout << endl << "Running memory trial on " << size << "-element pqueue" << endl;
    for (int i = 0; i < size; i++)
		pq.enqueue(RandomInteger(1, size));
    cout << "After consecutive enqueues, " << size << "-element pqueue is using "
         << pq.bytesUsed()/1000 << " KB of memory" << endl;
    int num = size;
    for (int j = 0; j < NumRepetitions; j++) { /* do a bunch of enqueue/dequeue ops */
	    if (RandomChance(.5)) { 
	        pq.enqueue(RandomInteger(0, size));
	        num++;
        } else {
	        pq.dequeueMax();
	        num--;
	    }
    }
    cout << "After more enqueue/dequeue, " << num << "-element pqueue is using "
         << pq.bytesUsed()/1000 << " KB of memory" << endl;
}

double GetCurrentTime()
{
      return (clock()*1000.0/CLOCKS_PER_SEC);
}
