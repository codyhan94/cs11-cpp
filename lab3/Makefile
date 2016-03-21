CXX=g++
CPPFLAGS=-g -pedantic -std=c++14 -Wall
SRCS=tsp-main.cc tsp-ga.cc Point.cc
OBJS=$(SRCS:.cc=.o)
MAIN=tsp-ga

.PHONY:
	clean

all: $(SRCS) $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) -o $(MAIN) $(OBJS)

.cc.o:
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -f *.o $(MAIN)

