CXX=g++
CPPFLAGS=-g -pedantic -std=c++14 -Wall
SRCS=engine.cc regex.cc testbase.cc test-regex.cc
OBJS=$(SRCS:.cc=.o)
MAIN=test-regex

.PHONY:
	clean

all: $(SRCS) $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) -o $(MAIN) $(OBJS)

.cc.o:
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -f *.o $(MAIN)

