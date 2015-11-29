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

  ~Thread();

  void Start();
  void Join();  // return pthread_join()

  bool Started() const { return started_; }
  pthread_t PthreadId() const { return pthread_id_; }
  pid_t Tid() const { return *tid_; }
  const std::string& Name() const { return name_; }

  static int NumCreated() { return num_created_.Get(); }

 private:
  void SetDefaultName();
  void PthreadCall(const char* label, int result);

  bool started_;
  bool joined_;
  pthread_t pthread_id_;
  std::shared_ptr<pid_t> tid_;
  ThreadFunc func_;
  std::string name_;

  static AtomicInt32 num_created_;

  // No copying allow
  Thread(const Thread&);
  void operator=(const Thread&);
};

}  // namespace mirants

#endif  // MIRANTS_PORT_THREAD_H_
