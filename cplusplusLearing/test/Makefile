#Filename:Makefile
CXX=g++
DEBUG= -g
CFLAGS= -Wall -c $(DEBUG)
LFLAGS= -Wall $(DEBUG)
LIB=../lib/cs106lib.a
MODEL=-std=c++11
HPATH=../include
PROG=test
OBJS=$(PROG).o

test:
	$(CXX) $(LFLAGS) test.cpp -o test

iterator:
	$(CXX) $(LFLAGS) iterator.cpp -o iterator

set:
	$(CXX) $(LFLAGS) set.cpp -o set

cleanall:
	rm -f *.o test iterator set
