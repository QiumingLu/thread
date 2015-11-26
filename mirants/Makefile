CXXFLAGS= -I. -I./include 
CXXFLAGS+=-g -Wall
CXXFLAGS+=-O2 

HEADERS=$(wildcard *.h)
TESTS= countdownlatch_test \
	   arena_test          \
	   skiplist_test       \
	   coding_test         \

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cc, $^) $(LDFLAGS) -lpthread

countdownlatch_test: test/countdownlatch_test.cc port/port_posix.cc
countdownlatch_test: LDFLAGS += -std=c++0x

arena_test: test/arena_test.cc util/arena.cc util/testharness.cc 

skiplist_test: test/skiplist_test.cc util/testharness.cc util/arena.cc

coding_test: test/coding_test.cc util/testharness.cc util/coding.cc

.PHONY: clean
clean:
	rm -f $(TESTS)
