/*
 * File: pqchunklist.cpp
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
 *	struct pqchunklist;
 */
const int MaxElemsPerBlock=4;

template<typename T> 
struct chunklist{
    T array[MaxElemsPerBlock];
    int nums;
    chunklist* next;    
}

PQueue::PQueue()
{
}


PQueue::~PQueue()
{
}


bool PQueue::isEmpty()
{
    return (pqchunklist->nums==0);  
}

int PQueue::size()
{
	int num=1;
    chunklist* nextblock=pqchunklist->next;
    while(nextblock!=NULL){
        num++;
        nextblock=(*nextblock)->next;
    }
    return num*MaxElemsPerBlock;
}


/* Implementation notes: enqueue
 * -----------------------------
 * Since we're keeping the vector in no particular order, we just append this
 * new element to the end.  It's the easiest/fastest thing to do.
 */
template<typename T>
void PQueue::enqueue(T newValue)
{
    chunklist* nextblock=&pqchunklist;
    while(true){
        if((*nextblock)->nums==0) break;
        int num=(*nextblock)->nums;

        T low=(*nextblock)->array[nums-1];
        if(newValue<low&&num==MaxElemsPerBlock&&(*nextblock)->next!=NULL){
            nextblock=(*nextblock)->next;        
        }
        else break;
    }
    //insert the newValue
    int num1=(*nextblock)->nums;
    //if the block not full,insert the newValue directly
    if(num1!=MaxElemsPerBlock){
        for(int i=0;i<num1;i++){
            if((*nextblock)->array[i]<newValue){
                int tem=(*nextblock)->array[i];
                (*nextblock)->array[i]=newValue;
                newValue=tem;
            }    
        }
        (*nextblock)->array[i]=newValue;
    }
    //if the block is full ,then creat a new block ,the top of which is newValue
    else{
        chunklist* tem=(*nextblock)->next;
        chunklist a;
        (*nextblock)->next=&a;
        if((*nextblock)->array[MaxElemsPerBlock/2]>newValue) 
        

    }
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

