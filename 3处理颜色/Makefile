CC = g++
BOOSTLIB = -std=c++11 -pthread

LIB = $(shell pkg-config --libs opencv)
INC = $(shell pkg-config --cflags opencv)
SRCFILE = Color_Process.cpp
DEBUGFLG=
all:
		$(CC) $(SRCFILE) $(DEBUGFLG) $(INC) $(BOOSTLIB) $(LIB) -o Color_Process
clean:
		rm -rf Color_Process
