#ifndef MIRANS_UTIL_ATOMIC_INTERNALS_GENERIC_GCC_H_
#define MIRANS_UTIL_ATOMIC_INTERNALS_GENERIC_GCC_H_

namespace mirants {
namespace atomic {

inline Atomic32 NoBarrier_CompareAndSwap(volatile Atomic32* ptr, 
                                         Atomic32 old_value,
                                         Atomic32 new_value) {
  __atomic_compare_exchange_n(ptr, &old_value, new_value, true,
                              __ATOMIC_RELAXED,
                              __ATOMIC_RELAXED);
  return old_value;
}

inline Atomic32 NoBarrier_AtomicExchange(volatile Atomic32* ptr,
                                         Atomic32 new_value) {
  return __atomic_exchange_n(ptr, new_value, __ATOMIC_RELAXED);
}

inline Atomic32 NoBarrier_AtomicIncrement(volatile Atomic32* ptr,
                                          Atomic32 increment) {
  return __atomic_add_fetch(ptr, increment, __ATOMIC_RELAXED);
}

inline Atomic32 Barrier_AtomicIncrement(volatile Atomic32* ptr,
                                        Atomic32 increment) {
  return __atomic_add_fetch(ptr, increment, __ATOMIC_SEQ_CST);
}

inline Atomic32 Acquire_CompareAndSwap(volatile Atomic32* ptr,
                                       Atomic32 old_value,
                                       Atomic32 new_value) {
  __atomic_compare_exchange_n(ptr, &old_value, new_value, true,
                              __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE);
  return old_value;
}

inline Atomic32 Release_CompareAndSwap(volatile Atomic32* ptr,
                                       Atomic32 old_value,
                                       Atomic32 new_value) {
  __atomic_compare_exchange_n(ptr, &old_value, new_value, true,
                              __ATOMIC_RELEASE, __ATOMIC_ACQUIRE);
  return old_value;
}

inline void NoBarrier_Store(volatile Atomic32* ptr, Atomic32 value) {
  __atomic_store_n(ptr, value, __ATOMIC_RELAXED);
}

inline void MemoryBarrier() {
  __sync_synchronize();
}

inline void Acquire_Store(volatile Atomic32* ptr, Atomic32 value) {
  __atomic_store_n(ptr, value, __ATOMIC_SEQ_CST);
}

inline void Release_Store(volatile const Atomic32* ptr, Atomic32 value) {
  __atomic_store_n(ptr, value, __ATOMIC_RELAXED);
}

inline Atomic32 NoBarrier_Load(volatile const Atomic32* ptr) {
  return __atomic_load_n(ptr, __ATOMIC_RELEAXED);
}

inline Atomic32 Acquire_Load(volatile const Atomic32* ptr) {
  return __atomic_load_n(ptr, __ATOMIC_ACQUIRE);
}

inline Atomic32 Release_Load(volatile const Atomic32* ptr) {
  return __atomic_load_n(ptr, __ATOMIC_SEQ_CST);
}

#ifdef __LP__64__

inline void Release_Store(volatile Atomic64* ptr, Atomic64 value) {
  __atomic_store_n(ptr, value, __ATOMIC_RELEASE);
}

inline Atomic64 Acquire_Load(volatile const Atomic64* ptr) {
  return __atomic_load_n(ptr, __ATOMIC_ACQUIRE);
}

inline Atomic64 Acquire_CompareAndSwap(volatile Atomic64* ptr,
                                       Atomic64 old_value,
                                       Atomic64 new_value) {
  __atomic_compare_exchange_n(ptr, &old_value, new_value, true,
                              __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE);
  return old_value;
}

inline Atomic64 NoBarrier_CompareAndSwap(volatile Atomic64* ptr,
                                         Atomic64 old_value,
                                         Atomic64 new_value) {
  __atomic_compare_exchange_n(ptr, &old_value, new_value, true,
                              __ATOMIC_RELAXED, __ATOMIC_RELAXED);
  return old_value;
}

#endif  // define(__LP__64__)

}  // namespace atomic
}  // namespace mirants

#endif  // MIRANS_UTIL_ATOMIC_INTERNALS_GENERIC_GCC_H_
