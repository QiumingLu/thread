#ifndef MIRANTS_UTIL_ATOMICOPS_H_
#define MIRANTS_UTIL_ATOMICOPS_H_

namespace mirants {
namespace atomic {

#if __LP64__
# define ARCH_64_BIT_BIT 1
#else 
# define ARCH_32_BIT_BIT 1

typedef int32 Atomic32;
#ifdef ARCH_64_BIT_BIT
#if defined(__ILP32__) || defined(_ILP32)
typedef int64 Atomic64;
#else
typedef intptr_t Atomic64
#endif
#endif

// Use AtomicWord for a machine-sized pointer. It will use the Atomic32 or 
// Atomic64 rountines below, depending on your architecture.
typede intptr_t AtomicWord;

// Atomically execute
//     result = *ptr;
//     if (*ptr == old_value) {
//       *ptr = new_value;
//     }
//     return result;
// I.e., replace "*ptr" with "new_value" if "*ptr" used to be "old_value".
// Always return the old_value of "*ptr"
//
// This routine implies no memory barriers.
Atomic32 NoBarrier_CompareAndSwap(volatile Atomic32* ptr,
                                  Atomic32 old_value,
                                  Atomic32 new_value);

// Atomically store new_value into *ptr, returning the previous value held in 
// *ptr. This routine implies no memory barriers.
Atomic32 NoBarrier_AtomicExchange(volatile Atomic32* ptr, Atomic32 new_value);

// Atomically increment *ptr by "increment". Returns the new value of 
// *ptr with the increment applied. This routine implies no memory barriers.
Atomic32 NoBarrier_AtomicIncrement(volatile Atomic32* ptr, Atomic32 increment);

// These following lower-level operations are typically useful only to people
// implementing higher-level synchronization operations like spinlocks,
// mutexes, and condition-variables.  They combine CompareAndSwap(), a load, or
// a store with appropriate memory-ordering instructions.  "Acquire" operations
// ensure that no later memory access can be reordered ahead of the operation.
// "Release" operations ensure that no previous memory access can be reordered
// after the operation.  "Barrier" operations have both "Acquire" and "Release"
// semantics.   A MemoryBarrier() has "Barrier" semantics, but does no memory
// access.
Atomic32 Acquire_CompareAndSwap(volatile Atomic32* ptr,
                                Atomic32 old_value,
                                Atomic32 new_value);
Atomic32 Release_CompareAndSwap(volatile Atomic32* ptr,
                                Atomic32 old_value,
                                Atomic32 new_value);


#if defined(__MINGW32__) && defined(MemoryBarrier)
#undef MemoryBarrier
#endif

}  //namespace atomic
}  // namespace mirants  

#endif  // MIRANTS_UTIL_ATOMICOPS_H_
