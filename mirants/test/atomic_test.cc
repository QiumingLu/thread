#include "port/atomic.h"

#include "util/testharness.h"

namespace mirants {

class AtomicTest { };

TEST(AtomicTest, TestInt64) {
  AtomicInt64 a;
  ASSERT_EQ(0, static_cast<int>(a.Get()));
  ASSERT_EQ(0, static_cast<int>(a.GetAndAdd(1)));
  ASSERT_EQ(1, static_cast<int>(a.Get()));
  ASSERT_EQ(3, static_cast<int>(a.AddAndGet(2)));
  ASSERT_EQ(3, static_cast<int>(a.Get()));
  ASSERT_EQ(4, static_cast<int>(a.IncrementAndGet()));
  ASSERT_EQ(4, static_cast<int>(a.Get()));
  ASSERT_EQ(3, static_cast<int>(a.DecrementAndGet()));
  ASSERT_EQ(3, static_cast<int>(a.Get()));
  a.Increnment();
  ASSERT_EQ(4, static_cast<int>(a.Get()));
  a.Decrement();
  ASSERT_EQ(3, static_cast<int>(a.Get()));
  ASSERT_EQ(0, static_cast<int>(a.AddAndGet(-3)));
  ASSERT_EQ(0, static_cast<int>(a.GetAndAdd(5)));
  ASSERT_EQ(5, static_cast<int>(a.Get()));
  ASSERT_EQ(5, static_cast<int>(a.GetAndSet(4)));
  ASSERT_EQ(4, static_cast<int>(a.Get()));
}

TEST(AtomicTest, TestInt32) {
  AtomicInt32 a;
  ASSERT_EQ(0, static_cast<int>(a.Get()));
  ASSERT_EQ(0, static_cast<int>(a.GetAndAdd(1)));
  ASSERT_EQ(1, static_cast<int>(a.Get()));
  ASSERT_EQ(3, static_cast<int>(a.AddAndGet(2)));
  ASSERT_EQ(3, static_cast<int>(a.Get()));
  ASSERT_EQ(4, static_cast<int>(a.IncrementAndGet()));
  ASSERT_EQ(4, static_cast<int>(a.Get()));
  ASSERT_EQ(3, static_cast<int>(a.DecrementAndGet()));
  ASSERT_EQ(3, static_cast<int>(a.Get()));
  a.Increnment();
  ASSERT_EQ(4, static_cast<int>(a.Get()));
  a.Decrement();
  ASSERT_EQ(3, static_cast<int>(a.Get()));
  ASSERT_EQ(0, static_cast<int>(a.AddAndGet(-3)));
  ASSERT_EQ(0, static_cast<int>(a.GetAndAdd(5)));
  ASSERT_EQ(5, static_cast<int>(a.Get()));
  ASSERT_EQ(5, static_cast<int>(a.GetAndSet(4)));
  ASSERT_EQ(4, static_cast<int>(a.Get()));
}

}  // namespace mirants

int main(int argc, char** argv) {
  return mirants::test::RunAllTests();
}
