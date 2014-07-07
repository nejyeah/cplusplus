CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

CSLIB = cs106lib.a

PROG = 	testgraphics

OBJS = 	genlib.o \
	init.o \
	random.o \
	lexicon.o \
	strutils.o \
	simpio.o \
	graphics.o \
	graphicsclient.o \
	ClientSocket.o \
	Socket.o \
	extgraph.o \
	sound.o \
	scanner.o  ## needs fixing!

all : $(CSLIB)  # TAGS

test : $(PROG)

$(PROG) : $(OBJS) $(PROG).o $(PROG).h
	$(CC) $(LFLAGS) $(OBJS) $(PROG).o -o $(PROG) 

# Collect the various object files into a single library file
$(CSLIB): $(OBJS)
	-rm -f $(CSLIB)
	ar cr $(CSLIB) $(OBJS)
	ranlib $(CSLIB)

genlib.o : genlib.cpp genlib.h
	$(CC) $(CFLAGS) genlib.cpp

testgraphics.o : $(PROG).cpp
	$(CC) $(CFLAGS) $(PROG).cpp

init.o : init.cpp init.h
	$(CC) $(CFLAGS) init.cpp

random.o : random.cpp random.h
	$(CC) $(CFLAGS) random.cpp

lexicon.o : lexicon.cpp lexicon.h
	$(CC) $(CFLAGS) lexicon.cpp

strutils.o : strutils.cpp strutils.h
	$(CC) $(CFLAGS) strutils.cpp

simpio.o : simpio.cpp simpio.h
	$(CC) $(CFLAGS) simpio.cpp

graphics.o : graphics.cpp private/graphics.h graphicsclient.h
	$(CC) $(CFLAGS) graphics.cpp

graphicsclient.o : graphicsclient.cpp private/graphics.h graphicsclient.h
	$(CC) $(CFLAGS) graphicsclient.cpp

sound.o : sound.cpp sound.h
	$(CC) $(CFLAGS) sound.cpp

clean :
	rm -f $(CSLIB) $(PROG) *.o

# What follows is for etags output 
# This is only for Emacs users, others can ignore it

SRCS = 	genlib.cpp \
	init.cpp \
	random.cpp \
	lexicon.cpp \
	strutils.cpp \
	simpio.cpp \
	Socket.cpp \
	ClientSocket.cpp \
	graphics.cpp \
	graphicsclient.cpp \
	extgraph.cpp

HDRS = 	genlib.h \
	init.h \
	random.h \
	lexicon.h \
	strutils.h \
	simpio.h \
	ClientSocket.h \
	SocketException.h \
	graphics.h \
	graphicsclient.h \
	private/graphics.h \
	extgraph.h

TAGS : $(SRCS) $(HDRS)
	etags $(SRCS) $(HDRS)


