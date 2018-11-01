CC = g++
BOOSTLIB = -std=c++11 -pthread

LIB = $(shell pkg-config --libs opencv)
INC = $(shell pkg-config --cflags opencv)
SRCFILE = histogram.cpp
DEBUGFLG=
all:
		$(CC) $(SRCFILE) $(DEBUGFLG) $(INC) $(BOOSTLIB) $(LIB) -o histogram
clean:
		rm -rf histogram
