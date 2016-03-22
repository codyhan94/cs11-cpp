CXX=g++
CPPFLAGS=-g -pedantic -std=c++14 -Wall
SRCS=maze.cc testbase.cc test-maze.cc
OBJS=$(SRCS:.cc=.o)
MAIN=test-maze

.PHONY:
	clean

all: $(SRCS) $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) -o $(MAIN) $(OBJS)

.cc.o:
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -f *.o $(MAIN)

