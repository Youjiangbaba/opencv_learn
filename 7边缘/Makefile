CC = g++
BOOSTLIB = -std=c++11 -pthread

LIB = $(shell pkg-config --libs opencv)
INC = $(shell pkg-config --cflags opencv)
SRCFILE = canny.cpp
DEBUGFLG=
all:
		$(CC) $(SRCFILE) $(DEBUGFLG) $(INC) $(BOOSTLIB) $(LIB) -o canny
clean:
		rm -rf canny
