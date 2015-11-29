#ifndef MIRANTS_PORT_THREAD_H_
#define MIRANTS_PORT_THREAD_H_

#include <memory>
#include <functional>
#include <string>
#include <pthread.h>
#include "port/atomic.h"

namespace mirants {

class Thread {
 public:
   typedef std::function<void ()> ThreadFunc;

   explicit Thread(const ThreadFunc&, const std::string& name = std::string());
#ifdef __GXX_EXPERIMENTAL_CXX0X__
   explicit Thread(ThreadFunc&&, const std::string& name = std::string());
#endif
   ~Thread();

 private:
  bool started_;
  bool joined_;
  pthread_t pthread_id_;
  std::shared_ptr<pid_t> tid_;
  ThreadFunc func_;
  std::string name_;

  static AtomicInt32 num_created_;
};

}  // namespace mirants

#endif  // MIRANTS_PORT_THREAD_H_
