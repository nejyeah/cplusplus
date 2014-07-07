#Filename:Makefile
CXX=g++-4.8
MOD= -std=c++11
DEBUG= -g
CFLAGS= -Wall -c $(DEBUG)
LFLAGS= -Wall $(DEBUG)
LIB=../lib/cs106lib.a
HPATH=../cs106lib-0.3.1/CS106
HPATH1=../cs106lib-0.3.1/headers
HPATH2=../cs106lib-0.3.1/assign/4_boggle
#PROG=project
#OBJS=$(PROG).o

handout1:
	$(CXX) $(CFLAGS) -I $(HPATH1) handout1.cpp 
	$(CXX) -o handout1 handout1.o $(LIB)

handout3:
	$(CXX) $(LFLAGS) handout3.cpp -o handout3

handout4:
	$(CXX) $(LFLAGS) handout4.cpp -o handout4

handout5:
	$(CXX) $(LFLAGS) handout5.cpp -o handout5

handout6:
	$(CXX) $(LFLAGS) handout6.cpp -o handout6

part1:
	$(CXX) $(CFLAGS) -I $(HPATH2) part1.cpp
	$(CXX) -o part1 part1.o $(HPATH2)/gboggle.o $(LIB)


cleanall:
	rm -f *.o handout1 handout3 handout4 handout5 handout6 part1
