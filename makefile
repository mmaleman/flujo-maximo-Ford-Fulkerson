.PHONY: all clean

CC=g++
CPP_STANDARD=c++14
LFLAGS= -std=$(CPP_STANDARD) -g 
CFLAGS=-c -std=$(CPP_STANDARD) -g

OBJS=grafo.o FF.o

all: flujoMaximo

flujoMaximo: $(OBJS) main.cpp
	$(CC) $(LFLAGS) $(OBJS) main.cpp -o flujoMaximo
grafo.o: grafo.h grafo.cpp
	$(CC) $(CFLAGS) grafo.cpp -o grafo.o
FF.o: FF.h FF.cpp
	$(CC) $(CFLAGS) FF.cpp -o FF.o

clean: 
	rm *.o flujoMaximo