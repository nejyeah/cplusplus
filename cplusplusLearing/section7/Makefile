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

path:
	$(CXX) $(CFLAGS) -I $(HPATH1) pathfinder.cpp 
	$(CXX) -o pathfinder pathfinder.o $(LIB)

test:
	$(CXX) $(CFLAGS) -I $(HPATH1) -I ../include test.cpp
	$(CXX) -o test test.o $(LIB1)

cleanall:
	rm -f *.o pathfinder part1 test
