// Copyright (c) 2015 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mythread/bounded_blockingqueue.h"
#include "mythread/countdownlatch.h"
#include "mythread/thread.h"

#include <stdio.h>

#include <string>
#include <vector>

namespace mythread {

class BoundedBlockingQueueTest {
 public:
  BoundedBlockingQueueTest(int threads_size)
      : queue_(18), latch_(threads_size), threads_size_(threads_size) {
    assert(threads_size_ > 0);
    for (size_t i = 0; i < static_cast<size_t>(threads_size_); ++i) {
      threads_.push_back(
          new Thread(&BoundedBlockingQueueTest::ThreadFunc, this));
      threads_[i]->Start();
    }
  }

  void Task(int num) {
    printf("waiting for all threads start...\n");
    latch_.Wait();
    for (int i = 1; i <= num; ++i) {
      char task[32];
      snprintf(task, sizeof(task), "task %d", i);
      queue_.push(task);
    }
  }

  void Join() {
    for (int i = 0; i < threads_size_; ++i) {
      queue_.push("No task, stop!");
    }
    for (size_t i = 0; i < threads_.size(); ++i) {
      threads_[i]->Join();
      delete threads_[i];
    }
  }

 private:
  static void ThreadFunc(void* obj) {
    BoundedBlockingQueueTest* t =
        reinterpret_cast<BoundedBlockingQueueTest*>(obj);
    t->RunFunc();
  }

  void RunFunc() {
    latch_.CountDown();
    while (true) {
      std::string task(queue_.take());
      if (task == "No task, stop!") {
        printf("All taskes have been done! Yelp!\n");
        break;
      }
    }
  }

  BoundedBlockingQueue<std::string> queue_;
  CountDownLatch latch_;
  int threads_size_;
  std::vector<Thread*> threads_;
};

}  // namespace mythread

int main() {
  mythread::BoundedBlockingQueueTest t(4);
  t.Task(100);
  t.Join();
  return 0;
}
