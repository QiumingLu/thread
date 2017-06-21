// Copyright (c) 2015 Mirants Lu. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>
#include <unistd.h>
#include <string>
#include <thread>

#include "mythread/countdownlatch.h"

static int counter = 0;
static int number = 2;
static mirants::CountDownLatch controller(number);

void Arrive() {
  printf("%d has arrived.\n", ++counter);
  controller.CountDown();
}

void Run() {
  printf("VideoConference: Initialization: %d participants.\n",
         controller.GetCount());
  controller.Wait();
  printf("VideoConference: All the participants have come.\n");
  printf("VideoConference: Let's start ...\n");
}

int main() {
  std::thread t1(Run);
  sleep(10);
  std::thread t2(Arrive);
  std::thread t3(Arrive);
  t1.join();
  t2.join();
  t3.join();
  return 0;
}
