#ifndef MYTHREAD_INCLUDE_THREAD_H_
#define MYTHREAD_INCLUDE_THREAD_H_

#include <pthread.h>

namespace mythread {

class Thread {
 public:
  Thread(void (*function)(void*), void* arg);
  ~Thread();

  void Start();
  void Join();

  bool Started() const { return started_; }
  pthread_t gettid() const { return thread_; }

 private:
  void PthreadCall(const char* label, int result);

  bool started_;
  bool joined_;
  pthread_t thread_;
  void (*function_)(void*);
  void* arg_;

  // No copying allowed
  Thread(const Thread&);
  void operator=(const Thread&);
};

}  // namespace mythread

#endif  // MYTHREAD_INCLUDE_THREAD_H_
