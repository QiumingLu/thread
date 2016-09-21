CXXFLAGS= -I. -I./include 
CXXFLAGS+=-g -Wall
CXXFLAGS+=-O2 

HEADERS=$(wildcard *.h)
TESTS= blockingqueue_test       \
	   thread_test              \
	   threadlocal_storage_test \
	   threadpool_test          \

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cc, $^) $(LDFLAGS) -lpthread

LDFLAGS += -Werror -Wno-sign-conversion -Wconversion -Wall \
		   -Wno-unused-parameter -Woverloaded-virtual      \
		   -Wextra -Wpointer-arith -Wshadow

blockingqueue_test: tests/blockingqueue_test.cc include/mythread/thread.cc include/mythread/mutex.cc

thread_test: tests/thread_test.cc util/testharness.cc include/mythread/thread.cc

threadlocal_storage_test: tests/threadlocal_storage_test.cc include/mythread/thread.cc

threadpool_test: tests/threadpool_test.cc \
                 include/mythread/threadpool.cc \
				 include/mythread/thread.cc\
                 include/mythread/mutex.cc

.PHONY: clean
clean:
	rm -f $(TESTS)
