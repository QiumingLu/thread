#ifndef MIRANTS_PORT_THREADPOOL_H_
#define MIRANTS_PORT_THREADPOOL_H_

#include <string>
#include "port/port_posix.h"

namespace mirants {

class ThreadPool {
 public:
  explicit ThreadPool(const std::string& poolname = std::string("ThreadPool"));
  ~ThreadPool();

  void Start(int poolsize);
  void ShutDown();

 private:
  mutable port::Mutex mutex_;

  std::string poolname_;

  // No copying allow
  ThreadPool(const ThreadPool&);
  void operator=(const ThreadPool&);
};

}  // namespace mirants

#endif  // MIRANTS_PORT_THREADPOOL_H_
