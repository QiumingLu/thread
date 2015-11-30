#include "port/threadpool.h"
#include <algorithm>
#include "port/mutexlock.h"
#include <stdio.h>
namespace mirants {

ThreadPool::ThreadPool(int poolsize, const std::string& poolname)
    : mutex_(),
      not_empty_(&mutex_),
      poolname_(poolname),
      poolsize_(poolsize),
      running_(false) 
{ }

ThreadPool::~ThreadPool() { 
  if (running_) {
    ShutDown();
  }
}

void ThreadPool::Start() {
  assert(threads_.empty());
  running_ = true;
  threads_.reserve(poolsize_);
  for (int i= 0; i < poolsize_; ++i) {
    char id[32];
    snprintf(id, sizeof(id), "%d", i+1); 
    threads_.push_back(new mirants::Thread(
          std::bind(&ThreadPool::ThreadFunc, this), poolname_+id));
    threads_[i].Start();
  }
}

void ThreadPool::ShutDown() {
  {
  MutexLock l(&mutex_);
  running_ = false;
  not_empty_.SignalAll();
  }
  using namespace std::placeholders;
  for_each(threads_.begin(),
           threads_.end(),
           std::bind(&mirants::Thread::Join, _1));
}

const std::string& ThreadPool::PoolName() const {
  return poolname_;
}

size_t ThreadPool::QueueSize() const {
  MutexLock l(&mutex_);
  return queue_.size();
}

void ThreadPool::PushTaskInToPool(const Task& t) {
  MutexLock l(&mutex_);
  if (running_) {
    queue_.push_back(t);
    not_empty_.SignalAll();
  }
}


ThreadPool::Task ThreadPool::Take() {
  MutexLock l(&mutex_);
  while (queue_.empty() && running_) {
    not_empty_.Wait();
  }
  ThreadPool::Task t;
  if (!queue_.empty()) {
    t = queue_.front();
    queue_.pop_front();
  }
  return t;
}

void ThreadPool::ThreadFunc() {
  while (running_) {
    ThreadPool::Task task(Take());
    if (task) {
      task();
    }
  }
}

}  // namespace mirants
