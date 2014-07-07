CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

PROG = 	testgraphics
OBJS = $(PROG).o maze.o gboggle.o

all : test

test : $(PROG)

$(PROG) : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) ../CS106/cs106lib.a -o $(PROG) 

testgraphics.o : $(PROG).cpp $(PROG).h
	$(CC) $(CFLAGS) $(PROG).cpp

maze.o : maze.cpp maze.h
	$(CC) $(CFLAGS) maze.cpp

gboggle.o : gboggle.cpp gboggle.h
	$(CC) $(CFLAGS) gboggle.cpp

clean:
	rm -f *.o $(PROG)
