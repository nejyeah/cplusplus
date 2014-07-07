#Filename:Makefile
CXX=g++-4.8
MOD= -std=c++11
DEBUG= -g
CFLAGS= -Wall -c $(DEBUG)
LFLAGS= -Wall $(DEBUG)
LIB=../lib/cs106lib.a
LIB1=../lib/MysterySort.lib
HPATH=../cs106lib-0.3.1/CS106
HPATH1=../cs106lib-0.3.1/headers
HPATH2=../cs106lib-0.3.1/assign/4_boggle
#PROG=project
#OBJS=$(PROG).o
test:
	$(CXX) $(CFLAGS) -I $(HPATH) main.cpp performance.cpp pqueuetest.cpp pqvector.cpp
	$(CXX) -o main main.o performance.o pqueuetest.o pqvector.o 

cleanall:
	rm -f *.o main
