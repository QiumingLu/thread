// Copyright (c) 2015 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mythread/thread.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace mythread {

struct ThreadData {
  void (*user_function)(void*);
  void* user_arg;
};

void* StartThread(void* arg) {
  ThreadData* data = reinterpret_cast<ThreadData*>(arg);
  data->user_function(data->user_arg);
  delete data;
  return NULL;
}

Thread::Thread(void (*function)(void* arg), void* arg)
     : started_(false),
       joined_(false),
       thread_(0),
       function_(function),
       arg_(arg) {
}

Thread::~Thread() {
  if (started_ && !joined_) {
    pthread_detach(thread_);
  }
}

void Thread::Start() {
  assert(!started_);
  started_ = true;
  ThreadData* data = new ThreadData();
  data->user_function = function_;
  data->user_arg = arg_;
  PthreadCall("start thread",
              pthread_create(&thread_, NULL, &StartThread, data));
}

void Thread::Join() {
  assert(started_);
  assert(!joined_);
  joined_ = true;
  PthreadCall("join thread", pthread_join(thread_, NULL));
}

void Thread::PthreadCall(const char* label, int result) {
  if (result != 0) {
    fprintf(stderr, "pthread %s: %s\n", label, strerror(result));
    abort();
  }
}

}  // namespace mythread
