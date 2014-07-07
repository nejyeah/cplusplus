#Filename:Makefile
CXX=g++
DEBUG= -g
CFLAGS= -Wall -c $(DEBUG)
LFLAGS= -Wall $(DEBUG)
LIBSA=$(LIBPATH)/libalgorithms.a
LIBDY=$(LIBPATH)/libalgorithms.a
LIBPATH=./lib
MODEL=-std=c++11
HPATH=./lib
PROG=project
OBJS=$(PROG).o

sort:
	$(CXX) $(CFLAGS) -I $(HPATH) testSort.cpp
	$(CXX) -o test testSort.o  $(LIBSA)

sortd:
	$(CXX) $(CFLAGS) -I $(HPATH) testSort.cpp
	$(CXX) -o test1 testSort.o $(LIBDY)

cleanall:
	rm -f *.o test test1 
