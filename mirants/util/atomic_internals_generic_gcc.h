#ifndef MIRANS_UTIL_ATOMIC_INTERNALS_GENERIC_GCC_H_
#define MIRANS_UTIL_ATOMIC_INTERNALS_GENERIC_GCC_H_

namespace mirants {
namespace atomic {

inline Atomic32 NoBarrier_CompareAndSwap(volatile Atomic32* ptr, 
                                         Atomic32 old_value,
                                         Atomic32 new_value) {
}

inline Atomic32 NoBarrier_AtomicExchange(volatile Atomic32* ptr,
                                         Atomic32 new_value) {
}

inline Atomic32 NoBarrier_AtomicIncrement(volatile Atomic32* ptr,
                                          Atomic32 increment) {
}

inline Atomic32 Barrier_AtomicIncrement(volatile Atomic32* ptr,
                                        Atomic32 increment) {
}

inline Atomic32 Acquire_CompareAndSwap(volatile Atomic32* ptr,
                                       Atomic32 old_value,
                                       Atomic32 new_value) {
}

inline Atomic32 Release_CompareAndSwap(volatile Atomic32* ptr,
                                       Atomic32 old_value,
                                       Atomic32 new_value) {
}

inline void NoBarrier_Store(volatile Atomic32* ptr, Atomic32 value) {
}

inlint void MemoryBarrier() {
}

inline void Acquire_Store(volatile Atomic32* ptr, Atomic32 value) {
}

inline void Release_Store(volatile const Atomic32* ptr, Atomic32 value) {
}

inline Atomic32 NoBarrier_Load(volatile const Atomic32* ptr) {
}

inline Atomic32 Acquire_Load(volatile const Atomic32* ptr) {
}

inline Atomic32 Release_Load(volatile const Atomic32* ptr) {
}

#ifdef __LP__64__

inline void Release_Store(volatile Atomic64* ptr, Atomic64 value) {
}

inline Atomic64 Acquire_Load(volatile const Atomic64* ptr) {
}

inline Atomic64 Acquire_CompareAndSwap(volatile Atomic64* ptr,
                                       Atomic64 old_value,
                                       Atomic64 new_value) {
}

inline Atomic64 NoBarrier_CompareAndSwap(volatile Atomic64* ptr,
                                         Atomic64 old_value,
                                         Atomic64 new_value) {
}

#endif  // define(__LP__64__)

}  // namespace atomic
}  // namespace mirants

#endif  // MIRANS_UTIL_ATOMIC_INTERNALS_GENERIC_GCC_H_
