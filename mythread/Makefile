# Copyright (c) 2015 Mirants Lu. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

CXXFLAGS= -I. -I./include 
CXXFLAGS+=-g
CXXFLAGS+=-O2 
CXXFLAGS+= -Wno-sign-conversion -Wconversion -Wall \
           -Wno-unused-parameter -Woverloaded-virtual -Wextra \
	       -Wpointer-arith -Wshadow

LDFLAGS=-lpthread

TESTS= \
	tests/blockingqueue_test         \
	tests/bounded_blockingqueue_test \
	tests/singleton_test             \
	tests/thread_test                \
	tests/threadlocal_storage_test   \
	tests/threadlocal_singleton_test \
	tests/threadpool_test            \

OBJS=thread/mutex.o thread/thread.o thread/threadpool.o
LIB=libmythread.a

all: $(TESTS) $(LIB)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cc, $^) $(LDFLAGS)

$(LIB) : $(OBJS)
	rm -f $@
	ar cr $@ $(OBJS)
	rm -f $(OBJS)

tags :
	ctags -R *

tests/blockingqueue_test: tests/blockingqueue_test.cc thread/thread.cc \
  thread/mutex.cc

tests/bounded_blockingqueue_test: tests/bounded_blockingqueue_test.cc \
  thread/thread.cc thread/mutex.cc

tests/singleton_test: tests/singleton_test.cc thread/thread.cc

tests/thread_test: tests/thread_test.cc thread/thread.cc

tests/threadlocal_storage_test: tests/threadlocal_storage_test.cc \
  thread/thread.cc

tests/threadlocal_singleton_test: tests/threadlocalstorage_singleton_test.cc\
  thread/thread.cc

tests/threadpool_test: tests/threadpool_test.cc thread/threadpool.cc \
  thread/thread.cc thread/mutex.cc

.PHONY: clean
clean:
	rm -f $(TESTS) $(OBJS) $(LIB)
