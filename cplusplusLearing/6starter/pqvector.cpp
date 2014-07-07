/*
 * File: pqvector.cpp
 * ------------------
 * This file implements the priority queue class as a vector
 * of integers stored in no particular order.  This makes it easy
 * enqueue new elements, but hard to dequeue the max (have to search for it).
 *
 * Julie Zelenski, CS106
 */
 
#include "pqueue.h"
#include "genlib.h"
#include <iostream>

/* Implementation notes: PQueue class
 * ----------------------------------
 * The private section for the pqvector looks like this:
 *
 *	Vector<int> entries;
 */

PQueue::PQueue()
{
}


PQueue::~PQueue()
{
}


bool PQueue::isEmpty()
{
    return (entries.isEmpty());  
}

int PQueue::size()
{
	return (entries.size());
}


/* Implementation notes: enqueue
 * -----------------------------
 * Since we're keeping the vector in no particular order, we just append this
 * new element to the end.  It's the easiest/fastest thing to do.
 */
void PQueue::enqueue(int newValue)
{
	entries.add(newValue);
}


/* Implementation notes: dequeueMax
 * --------------------------------
 * Since we're keeping the vector in no particular order, we have to search to
 * find the largest element.  Once found, we remove it from the vector and
 * return that value.
 */
int PQueue::dequeueMax()
{	
	if (isEmpty())
		Error("Tried to dequeue max from an empty pqueue!");
		
	int maxIndex = 0;	// assume first element is largest until proven otherwise
	int maxValue = entries[0];
	for (int i = 1; i < entries.size(); i++) {
		if (entries[i] > maxValue) {
			maxValue = entries[i];
			maxIndex = i;
		}
	}
	entries.removeAt(maxIndex);	// remove entry from vector
	return maxValue;
}
		
int PQueue::bytesUsed() 
{
	return sizeof(*this) + entries.bytesUsed();
}


string PQueue::implementationName()
{
	return "unsorted vector";
}

void PQueue::printDebuggingInfo()
{
	cout << "------------------ START DEBUG INFO ------------------" << endl;
	cout << "Pqueue contains " << entries.size() << " entries" << endl;
	for (int i = 0; i < entries.size(); i++) 
		cout << entries[i] << " ";
	cout << endl;
	cout << "------------------ END DEBUG INFO ------------------" << endl;
}

