#ifndef MIRANTS_PORT_ATOMIC_H_
#define MIRANTS_PORT_ATOMIC_H_

#include <stdint.h>

namespace mirants {
namespace port {

template<typename T>
class AtomicIntegerT {
 public:
  AtomicIntegerT() : value_(0) { }

  T Get() const { 
    return __sync_val_compare_and_swap(const_cast<volatile T*>(&value_), 0, 0);
  }

  T GetAndAdd(T x) { return __sync_fetch_and_add(&value_, x); }

  T AddAndGet(T x) { return GetAndAdd(x) + x; }

  T IncrementAndGet() { return AddAndGet(1); }

  T DecrementAndGet() { return AddAndGet(-1); }

  void Add(T x) { GetAndAdd(x); }
  
  void Increnment() { GetAndAdd(1); }

  void Decrement() { GetAndAdd(-1); }

  T GetAndSet(T v) { return __sync_lock_test_and_set(&value_, v); }

 private:
  volatile T value_;

  // No copying allow.
  AtomicIntegerT(const AtomicIntegerT&);
  void operator=(const AtomicIntegerT&);
};

}  // namespace port

typedef port::AtomicIntegerT<int32_t> AtomicInt32;
typedef port::AtomicIntegerT<int64_t> AtomicInt64;

}  // namespace mirants

#endif  // MIRANTS_PORT_ATOMIC_H_
