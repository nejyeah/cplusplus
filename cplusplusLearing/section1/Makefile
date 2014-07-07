#Filename:Makefile
CXX=g++
DEBUG= -g
CFLAGS= -Wall -c $(DEBUG)
LFLAGS= -Wall $(DEBUG)
LIB=../lib/cs106lib.a
MODEL=-std=c++11
HPATH=../include
PROG=project
OBJS=$(PROG).o

censorString:
	$(CXX) $(LFLAGS) censorString.cpp -o censorString 

fileStruct:
	$(CXX) $(LFLAGS) fileStruct.cpp -o fileStruct 

countLetters:
	$(CXX) $(LFLAGS) countLetters.cpp -o countLetters

perfectnumber:
	$(CXX) $(LFLAGS) perfectnumber.cpp -o perfectnumber

votetest:
	$(CXX) $(CFLAGS) -I $(HPATH) votetest.cpp
	$(CXX) -o votetest votetest.o $(LIB)

part3:
	$(CXX) $(CFLAGS) -I $(HPATH) part3.cpp
	$(CXX) -o part3 part3.o $(LIB)
ass3:
	$(CXX) $(CFLAGS) -I $(HPATH) ass3.cpp
	$(CXX) -o ass3 ass3.o $(LIB)

part4:
	$(CXX) $(CFLAGS) $(MODEL) -I $(HPATH) part4.cpp
	$(CXX) -o part4 part4.o $(LIB)

part5:
	$(CXX) $(LFLAGS) part5.cpp -o part5
test:
	$(CXX) $(LFLAGS) $(MODEL) test.cpp -o test
cleanall:
	rm -f *.o censorString fileStruct countLetters perfectnumber votetest part3 part4 part5 test ass3
