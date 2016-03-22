CXX=g++
CPPFLAGS=-g -pedantic -std=c++14 -Wall
SRCS=maze.cc genmaze.cc
OBJS=$(SRCS:.cc=.o)
MAIN=genmaze

.PHONY:
	clean

all: $(SRCS) $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) -o $(MAIN) $(OBJS)

.cc.o:
	$(CXX) $(CPPFLAGS) -c $<

test: test.o
	$(CXX) $(CPPFLAGS) -o $@ $<

clean:
	rm -f *.o $(MAIN) test

