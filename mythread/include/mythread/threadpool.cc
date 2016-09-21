#include "mythread/threadpool.h"

#include <assert.h>

#include "mythread/mutexlock.h"
#include "mythread/thread.h"

namespace mythread {

ThreadPool::ThreadPool(int size)
    : mutex_(),
      cond_(&mutex_),
      started_(false),
      size_(size) {
}

ThreadPool::~ThreadPool() {
  if (started_) {
    Stop();
  }
}

void ThreadPool::Start() {
  assert(!started_);
  assert(threads_.empty());
  started_ = true;
  for (int i= 0; i < size_; ++i) {
    threads_.push_back(new Thread(&ThreadPool::ThreadFunc, this));
    threads_[i]->Start();
  }
}

void ThreadPool::Stop() {
  {
    MutexLock lock(&mutex_);
    started_ = false;
    cond_.SignalAll();
  }
  for (size_t i = 0; i < threads_.size(); ++i) {
    threads_[i]->Join();
    delete threads_[i];
  }
}

size_t ThreadPool::QueueSize() const {
  MutexLock lock(&mutex_);
  return queue_.size();
}

void ThreadPool::Put(void (*function)(void*), void* arg) {
  MutexLock lock(&mutex_);
  queue_.push(RunItem(function, arg));
  cond_.SignalAll();
}

ThreadPool::RunItem ThreadPool::Take() {
  MutexLock lock(&mutex_);
  while (queue_.empty() && started_) {
    cond_.Wait();
  }

  RunItem item;
  if (!queue_.empty()) {
    item = queue_.front();
    queue_.pop();
  }
  return item;
}

void ThreadPool::ThreadFunc(void* obj) {
  ThreadPool* pool = reinterpret_cast<ThreadPool*>(obj);
  while (pool->started_) {
    ThreadPool::RunItem item(pool->Take());
    if (item.function != NULL) {
      item.function(item.arg);
    }
  }
}

}  // namespace mythread
