#include "port/blockingqueue.h"
#include "port/current_thread.h"
#include "port/countdownlatch.h"
#include "port/thread.h"
#include <functional>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <boost/ptr_container/ptr_vector.hpp>

namespace mirants {

class BlockingQueueTest {
 public:
  BlockingQueueTest(int threads_size)
       : latch_(threads_size),
         threads_(threads_size) {
    for (int i = 0; i < threads_size; ++i) {
      char name[32];
      snprintf(name, sizeof(name), "thread %d", i);
      threads_.push_back(new mirants::Thread(
           std::bind(&BlockingQueueTest::ThreadFunc, this), 
           std::string(name)));
    }
    using namespace std::placeholders;
    for_each(threads_.begin(), threads_.end(), 
             std::bind(&mirants::Thread::Start, _1));
  }

  void Task(int num) {
    printf("waiting for count down latch\n");
    latch_.Wait();
    for (int i = 1; i <= num; ++i) {
      char task[32];
      snprintf(task, sizeof(task), "task %d", i);
      queue_.Push(task);
      printf("tid=%d, put task = %s, queue_size = %zd\n", 
             mirants::currentthread::Tid(), task, queue_.Size());
    }
  }

  void JoinAll() {
    for (size_t i = 0; i < threads_.size(); ++i) {
      queue_.Push("No task, stop!");
    }
    using namespace std::placeholders;
    for_each(threads_.begin(), threads_.end(), 
             std::bind(&mirants::Thread::Join, _1));
  }

 private:
  void ThreadFunc() {
    printf("tid=%d, %s started\n",
           mirants::currentthread::Tid(),
           mirants::currentthread::Name());
    latch_.CountDown();
    while (true) {
      std::string task(queue_.Take());
      if (task == "No task, stop!") {
        printf("All taskes have been done! yelp!\n");
        printf("tid=%d, %s stopped!\n",
                mirants::currentthread::Tid(), 
                mirants::currentthread::Name());
        break;
      }
      printf("tid=%d, get task = %s, queue_size = %zd\n",
             mirants::currentthread::Tid(), task.c_str(), queue_.Size());
    }

  }

  mirants::BlockingQueue<std::string> queue_;
  mirants::CountDownLatch latch_;
  boost::ptr_vector<mirants::Thread> threads_;
};

}  // namespace mirants

int main(int argc, char** argv) {
  printf("pid=%d, tid=%d\n", ::getpid(), mirants::currentthread::Tid());
  mirants::BlockingQueueTest t(5);
  t.Task(100);
  t.JoinAll();
  return 0;
}
