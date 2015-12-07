#ifndef MIRANTS_UTIL_SHARDED_PTR_H_
#define MIRANTS_UTIL_SHARDED_PTR_H_

#include "util/atomicops.h"

namespace mirants {

#ifdef __GXX_EXPERIMENTAL_CXX0X__

using std::enable_shared_from_this;
using std::shared_ptr;
using std::static_pointer_cast;
using std::weak_ptr;

#else

inline bool RefCountDec(volatile Atomic32* ptr) {
}

inline void RefCountInc(volatile Atomic32* ptr) {
}

template<typename T> class shared_ptr;
template<typename T> class weak_ptr;

// This class is an internal implementation detail for shared_ptr. 
// If two shared_ptr point to the same object, they also share a control 
// block. An "empty" shared_pointer refers to NULL and  also has a NULL 
// control block. It contains all of the state that's needed for reference 
// counting or any other kind of resource management. In this implemention 
// the control block happens to consist of two atomic words, the reference 
// count (the number of shared_ptrs that share ownership of the object) and
// the weak count (the number of weak_ptrs that observe the object, plus 1 
// if the refcount is nonzero).
//
// The "plus 1" is to prevent a race condition in the shared_ptr and
// weak_ptr destructors. We need to make sure the control block is
// only deleted once, so we need to make sure that at most one
// object sees the weak count decrement from 1 to 0.
class SharedPtrControlBlock {
  template<typename T> friend class shared_ptr;
  template<typename T> friend class weak_ptr;
 private:
  SharedPtrControlBlock() : refcount_(1), weak_count_(1) { }
  Atomic32 refcount_;
  Atomic32 weak_count_;
};

// Forward declaration. The class is defined below.
template<typename T> class enable_shared_from_this;

template<typename T>
class shared_ptr {
};

// Matches the interface of std::swap as an aid to generic programing.
template<typename T> void swap(shared_ptr<T>& r, shared_ptr<T>& s) {
}

template<typename T, typename U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U>& rhs) {
}

#endif

}  // namespace mirants

#endif  // MIRANTS_UTIL_SHARDED_PTR_H_
