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

handout1:
	$(CXX) $(CFLAGS) -I $(HPATH) handout1.cpp 
	$(CXX) -o handout1 handout1.o $(LIB)

handout3:
	$(CXX) $(LFLAGS) handout3.cpp -o handout3

handout4:
	$(CXX) $(LFLAGS) handout4.cpp -o handout4

handout5:
	$(CXX) $(LFLAGS) handout5.cpp -o handout5

handout6:
	$(CXX) $(LFLAGS) handout6.cpp -o handout6

handout7:
	$(CXX) $(LFLAGS) handout7.cpp -o handout7

handout8:
	$(CXX) $(LFLAGS) handout8.cpp -o handout8

warmup1:
	$(CXX) $(LFLAGS) warmup1.cpp -o warmup1

warmup2:
	$(CXX) $(LFLAGS) warmup2.cpp -o warmup2

lecture1:
	$(CXX) $(LFLAGS) lecture1.cpp -o lecture1

lecture2:
	$(CXX) $(LFLAGS) lecture2.cpp -o lecture2

lecture3:
	$(CXX) $(CFLAGS) -I ../include lecture3.cpp
	$(CXX) -o lecture3 lecture3.o $(LIB)

part1:
	$(CXX) $(LFLAGS) part1.cpp -o part1

part2:
	$(CXX) $(CFLAGS) -I $(HPATH) part2.cpp
	$(CXX) -o part2 part2.o $(LIB)

part3:
	$(CXX) $(LFLAGS) part3.cpp -o part3

part4:
	$(CXX) $(CFLAGS) -I ../cs106lib-0.3.1/assign/3_recursion part4.cpp
	$(CXX) -o part4 part4.o $(LIB)

part5:
	$(CXX) $(CFLAGS) -I $(HPATH) part5.cpp
	$(CXX) -o part5 part5.o $(LIB)

part6:
	$(CXX) $(CFLAGS) -I $(HPATH) part6.cpp
	$(CXX) -o part6 part6.o $(LIB)

cleanall:
	rm -f *.o warmup1 warmup2 lecture1 lecture2 lecture3 part1 part2 part3 part4 part5 part6 handout1 handout3 handout4 handout5 handout6 handout7 handout8
