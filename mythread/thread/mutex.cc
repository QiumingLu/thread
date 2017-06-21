// Copyright (c) 2015 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mythread/mutex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace mythread {

static void PthreadCall(const char* label, int result) {
  if (result != 0) {
    fprintf(stderr, "%s: %s\n", label, strerror(result));
    abort();
  }
}

Mutex::Mutex() {
  PthreadCall("pthread_mutex_init", pthread_mutex_init(&mutex_, NULL));
}

Mutex::~Mutex() {
  PthreadCall("pthread_mutex_destroy", pthread_mutex_destroy(&mutex_));
}

void Mutex::Lock() {
  PthreadCall("pthread_mutex_lock", pthread_mutex_lock(&mutex_));
}

void Mutex::Unlock() {
  PthreadCall("pthread_mutex_unlock", pthread_mutex_unlock(&mutex_));
}

Condition::Condition(Mutex* mutex) : mutex_(mutex) {
  PthreadCall("pthread_cond_init", pthread_cond_init(&cond_, NULL));
}

Condition::~Condition() {
  PthreadCall("pthread_cond_destroy", pthread_cond_destroy(&cond_));
}

void Condition::Wait() {
  PthreadCall("pthread_cond_wait", pthread_cond_wait(&cond_, &mutex_->mutex_));
}

void Condition::Signal() {
  PthreadCall("pthread_cond_signal", pthread_cond_signal(&cond_));
}

void Condition::SignalAll() {
  PthreadCall("pthread_cond_broadcast", pthread_cond_broadcast(&cond_));
}

}  // namespace mythread
