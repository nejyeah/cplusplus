# 
#
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG) 

simple_client_objects = ClientSocket.o \
						Socket.o \
						simple_client_main.o \
						../CS106/cs106lib.a

all : simple_client

simple_client: $(simple_client_objects)
	g++ $(LFLAGS) -o simple_client $(simple_client_objects)


Socket: Socket.cpp
ClientSocket: ClientSocket.cpp
simple_client_main: simple_client_main.cpp

clean:
	rm -f *.o simple_client
