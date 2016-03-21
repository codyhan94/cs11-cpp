CXX=g++
CPPFLAGS=-g -pedantic -std=c++14 -Wall
SRCS=tsp.cc Point.cc
OBJS=$(SRCS:.cc=.o)
MAIN=tsp

.PHONY:
	clean

all: $(SRCS) $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) -o $(MAIN) $(OBJS)

.cc.o:
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -f *.o $(MAIN)

