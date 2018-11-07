CC = g++
BOOSTLIB = -std=c++11 -pthread

LIB = $(shell pkg-config --libs opencv)
INC = $(shell pkg-config --cflags opencv)
SRCFILE = FAST_test.cpp
DEBUGFLG=
all:
		$(CC) $(SRCFILE) $(DEBUGFLG) $(INC) $(BOOSTLIB) $(LIB) -o FAST_test
clean:
		rm -rf FAST_test
