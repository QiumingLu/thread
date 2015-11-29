#include "port/threadpool.h"
#include <algorithm>
#include "port/mutexlock.h"

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
  running_ = true;
  threads_.reverse(poolsize_);
  for (int i= 0; i < poolsize_; ++i) {
    threads_.push_back(new mirants::Thread(
          std::bind(&ThreadPool::ThreadFunc, this), poolname_+i));
    threads_.Start();
  }
}

void ThreadPool::ShutDown() {
  {
  MutexLock l(&mutex_);
  running_ = false;
  not_empty_.SignalAll();
  }
  for_each(threads_.begin(),
           threads_.end(),
           std::bind(&mirants::Thread::Join, -1));
}

const std::string& PoolName() const {
  return poolname_;
}

size_t ThreadPool::QueueSize() const {
  MutexLock l(&mutex_);
  return queue_.size();
}

void ThreadPool::PushTaskInToPool(const Task& t) {
  MutexLock l(&mutex_);
  while (running_) {
    queue_.push_back(t);
    not_empty_.SignalAll();
  }
}

mirants::Task ThreadPool::Take() {
  MutexLock l(&mutex_);
  while (queue_.empty() && running_) {
    not_empty_.wait();
  }
  Task t;
  if (!queue_.empty()) {
    t = queue_.front();
    queue_.pop_front();
  }
  return t;
}

void ThreadPool::ThreadFunc() {
  while (running_) {
    Task task(Take());
    if (task) {
      task();
    }
  }
}

}  // namespace mirants
