CXX=g++
CPPFLAGS=-g -pedantic -std=c++14 -Wall
SRCS=lab1.cc Point.cc
OBJS=$(SRCS:.cc=.o)
MAIN=lab1

.PHONY:
	clean

all: $(SRCS) $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) -o $(MAIN) $(OBJS)

.cc.o:
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -f *.o $(MAIN)

