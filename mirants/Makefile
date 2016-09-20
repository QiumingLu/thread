CXXFLAGS= -I. -I./include 
CXXFLAGS+=-g -Wall
CXXFLAGS+=-O2 

HEADERS=$(wildcard *.h)
TESTS= countdownlatch_test      \
	   atomic_test              \
	   thread_test              \
	   blockingqueue_test       \
	   threadlocal_storage_test \
	   threadpool_test          \

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cc, $^) $(LDFLAGS) -lpthread

countdownlatch_test: test/countdownlatch_test.cc port/mutex.cc
countdownlatch_test: LDFLAGS += -std=c++0x

atomic_test: test/atomic_test.cc util/testharness.cc

thread_test: test/thread_test.cc util/testharness.cc port/thread.cc
thread_test: LDFLAGS += -std=c++0x

blockingqueue_test: test/blockingqueue_test.cc port/thread.cc port/mutex.cc
blockingqueue_test: LDFLAGS += -std=c++0x

threadlocal_storage_test: test/threadlocal_storage_test.cc port/thread.cc
threadlocal_storage_test: LDFLAGS += -std=c++0x

threadpool_test: test/threadpool_test.cc port/threadpool.cc port/thread.cc port/mutex.cc
threadpool_test: LDFLAGS += -std=c++0x

.PHONY: clean
clean:
	rm -f $(TESTS)
