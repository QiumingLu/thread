#ifndef MIRANTS_PORT_THREADPOOL_H_
#define MIRANTS_PORT_THREADPOOL_H_

#include <functional>
#include <deque>
#include <string>
#include <boost/ptr_container/ptr_vector.hpp>
#include "port/port_posix.h"
#include "port/thread.h"
#include "port/blockingqueue.h"

namespace mirants {

class ThreadPool {
 public:
  typedef std::function<void ()> Task;

  explicit ThreadPool(int poolsize,
                      const std::string& poolname = std::string("ThreadPool"));
  ~ThreadPool();

  void Start(int poolsize);
  void ShutDown();

  const std::string& PoolName() const;
  size_t QueueSize() const;

  void PushTaskInToPool(const Task& f);


 private:
  void ThreadFunc();
  Task Take();

  mutable port::Mutex mutex_;
  port::CondVar not_empty_;
  std::string poolname_;
  Task thread_init_callback_;
  int poolsize_;
  boost::ptr_vector<mirants::Thread> threads_;
  BlockingQueue<Task> queue_;
  bool running_;

  // No copying allow
  ThreadPool(const ThreadPool&);
  void operator=(const ThreadPool&);
};

}  // namespace mirants

#endif  // MIRANTS_PORT_THREADPOOL_H_
