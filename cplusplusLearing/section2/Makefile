#Filename:Makefile
CXX=g++-4.8
MOD= -std=c++11
DEBUG= -g
CFLAGS= -Wall -c $(DEBUG)
LFLAGS= -Wall $(DEBUG)
LIB=../lib/cs106lib.a
HPATH=../cs106lib-0.3.1/CS106
#PROG=project
#OBJS=$(PROG).o

part1:
	$(CXX) $(CFLAGS) -I $(HPATH) part1.cpp
	$(CXX) -o part1 part1.o $(LIB)

part2:
	$(CXX) -c -I ../cs106lib-0.3.1/assign/2_ADTs maze.cpp
	$(CXX) $(CFLAGS) -I ../cs106lib-0.3.1/assign/2_ADTs  part2.cpp
	$(CXX) -o part2 part2.o maze.o $(LIB)

handout1:
	$(CXX) $(CFLAGS) -I $(HPATH) handout1.cpp
	$(CXX) -o handout1 handout1.o $(LIB)

handout2:
	$(CXX) $(CFLAGS) -I $(HPATH) handout2.cpp
	$(CXX) -o handout2 handout2.o $(LIB)
	
handout3:
	$(CXX) $(CFLAGS) -I $(HPATH) handout3.cpp
	$(CXX) -o handout3 handout3.o $(LIB)

handout4:
	$(CXX) $(CFLAGS) -I $(HPATH) handout4.cpp
	$(CXX) -o handout4 handout4.o $(LIB)
	
handout5:
	$(CXX) $(CFLAGS) -I ../include handout5.cpp
	$(CXX) -o handout5 handout5.o $(LIB)

cleanall:
	rm -f *.o part1 part2 handout1 handout2 handout3 handout4 handout5
