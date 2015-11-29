#include "port/thread.h"
#include "port/current_thread.h"

#include <sys/types.h>
#include <unistd.h>

#include "util/testharness.h"

namespace mirants {

void ThreadFunc() {
  printf("tid=%d\n", currentthread::Tid());
}

void ThreadFunc2(int x) {
  printf("tid=%d, x=%d\n", currentthread::Tid(), x);
}

class Foo {
 public:
  explicit Foo(double x) : x_(x) { }
  void MemberFunc() {
    printf("tid=%d, Foo::x_=%f\n", currentthread::Tid(), x_);
  }

  void MemberFunc2(const std::string& text) {
    printf("tid=%d, Foo::x_=%f, text=%s\n", currentthread::Tid(), x_, text.c_str());
  }

 private:
  double x_;
};


class ThreadTest { };

TEST(ThreadTest, Tid) {
  ASSERT_EQ(::getpid(), currentthread::Tid());
  printf("pid=%d, tid=%d\n", getpid(), currentthread::Tid());

  port::Thread t1(ThreadFunc);
  t1.Start();
  t1.Join();

  port::Thread t2(std::bind(ThreadFunc2, 42), 
                  "thread for free function with argument");
  t2.Start();
  t2.Join();

  Foo foo(87.53);
  port::Thread t3(std::bind(&Foo::MemberFunc, &foo),
                  "thread for member function without argument");
  t3.Start();
  t3.Join();

  port::Thread t4(std::bind(&Foo::MemberFunc2, std::ref(foo), std::string("test thread")));
  t4.Start();
  t4.Join();

  ASSERT_EQ(4, port::Thread::NumCreated());
}

}  // namespace mirants

int main(int argc, char** argv) {
  return mirants::test::RunAllTests();
}
