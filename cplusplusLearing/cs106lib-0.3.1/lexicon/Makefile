CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

PROG = testlex
OBJS = $(PROG).o \
	lexicon.o \
	genlib.o \
	init.o \
	strutils.o

all : $(PROG)

$(PROG) : $(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -o $(PROG)

$(PROG).o : $(PROG).cpp
	$(CC) $(CFLAGS) $(PROG).cpp
