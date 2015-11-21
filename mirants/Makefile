CXXFLAGS= -I. -I./include 
CXXFLAGS+=-g -Wall
CXXFLAGS+=-O2 

HEADERS=$(wildcard *.h)
TESTS= countdownlatch_test

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cc, $^) $(LDFLAGS) -lpthread

countdownlatch_test: test/countdownlatch_test.cc port/port_posix.cc
countdownlatch_test: LDFLAGS += -std=c++0x

.PHONY: clean
clean:
	rm -f $(TESTS)
