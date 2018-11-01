CC = g++
BOOSTLIB = -std=c++11 -pthread

LIB = $(shell pkg-config --libs opencv)
INC = $(shell pkg-config --cflags opencv)
SRCFILE = rand_noise.cpp
DEBUGFLG=
all:
		$(CC) $(SRCFILE) $(DEBUGFLG) $(INC) $(BOOSTLIB) $(LIB) -o rand_noise
clean:
		rm -rf rand_noise
