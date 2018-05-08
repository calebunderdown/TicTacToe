CC=g++
CXXFLAGS=-g --std=c++11
WIDGET=term.o application.o keystream.o widget.o
TARGETS=tic 

all: $(TARGETS)
tic: $(WIDGET) pegPuzzles.o peg.o tic.o 
tic.o: tic.h tic.cpp
peg.o: peg.h peg.cpp
clean:
	rm -f $(TARGETS) *.o
