#include "thread.h"

#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#include "port/current_thread.h"

namespace mirants {

namespace currentthread {

__thread int  t_cached_tid = 0;
__thread char t_tid_string[32];
__thread int  t_tid_string_length = 6;
__thread const char* t_thread_name = "unkown";

}  // namespace currentthread

namespace {

pid_t GetTid() {
  return static_cast<pid_t>(::syscall(SYS_gettid));
}

void AfterFork() {
  mirants::currentthread::t_cached_tid = 0;
  mirants::currentthread::t_thread_name = "main";
  currentthread::Tid();
}

class ThreadNameInitializer {
 public:
  ThreadNameInitializer() {
    mirants::currentthread::t_thread_name = "main";
    currentthread::Tid();
    pthread_atfork(NULL, NULL, &AfterFork);
  }
};

ThreadNameInitializer init;

struct ThreadData {
  typedef mirants::Thread::ThreadFunc ThreadFunc;
  ThreadFunc user_function;
  std::string thread_name;
  std::weak_ptr<pid_t> thread_weak_tid;

  ThreadData(const ThreadFunc& func,
             const std::string name,
             const std::weak_ptr<pid_t>& tid)
      : user_function(func),
        thread_name(name),
        thread_weak_tid(tid) 
  { }

  void RunInThread() {
    pid_t tid = mirants::currentthread::Tid();
    std::shared_ptr<pid_t> ptid = thread_weak_tid.lock();
    if (ptid) {
      *ptid = tid;
      ptid.reset();
    }

    mirants::currentthread::t_thread_name = thread_name.c_str();
    user_function();
    mirants::currentthread::t_thread_name = "finished";
  }
};

void* StartThread(void* obj) {
  ThreadData* data = static_cast<ThreadData*>(obj);
  data->RunInThread();
  delete data;
  return NULL;
}

}  // end anonymous namespace

void currentthread::CacheTid() {
  if (t_cached_tid == 0) {
    t_cached_tid = GetTid();
    t_tid_string_length = snprintf(t_tid_string, 
                                   sizeof(t_tid_string),
                                   "%5d",
                                   t_cached_tid);
  }
}

bool currentthread::IsMainThread() {
  return Tid() == ::getpid();
}

AtomicInt32 Thread::num_created_;

Thread::Thread(const ThreadFunc& func, const std::string& name) 
     : started_(false),
       joined_(false),
       pthread_id_(0),
       tid_(new pid_t(0)),
       func_(func),
       name_(name) {
  SetDefaultName();
}

Thread::~Thread() {
  if (started_ && !joined_) {
    pthread_detach(pthread_id_);
  }
}

void Thread::SetDefaultName() {
  int num = num_created_.IncrementAndGet();
  if (name_.empty()) {
    char buf[32];
    snprintf(buf, sizeof(buf), "Thread %d", num);
    name_ = buf;
  }
}

void Thread::PthreadCall(const char* label, int result) {
  if (result != 0) {
    fprintf(stderr, "pthread %s: %s\n", label, strerror(result));
    abort();
  }
}

void Thread::Start() {
  assert(!started_);
  started_ = true;
  ThreadData* data = new ThreadData(func_, name_, tid_);
  PthreadCall("start thread", 
              pthread_create(&pthread_id_, NULL, &StartThread, data));
}

void Thread::Join() {
  assert(started_);
  assert(!joined_);
  joined_ = true;
  PthreadCall("join thread", pthread_join(pthread_id_, NULL));
}

}  // namespace mirants
