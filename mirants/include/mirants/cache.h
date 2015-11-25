// A Cache is an interface that maps keys to values. It has internal 
// syncronization and may be safetyly accessed concurrently from 
// multiple threads. It may automatically evict entries to make room
// for new entries. Values have a specified charge against the cache 
// capacity. For example, a cache where the values are available
// length strings, may use the length of the strings as the charge for 
// the string.
//
// A builtin cache implementation with a least-recently-used eviction
// policy is provided. Clients may use their own implementations if 
// they want something more sophisticated (like scan-resistance, 
// acustom eviction policy, variable cache sizing, etc.)


#ifndef MIRANTS_INCLUDE_MIRANTS_CACHE_H_
#define MIRANTS_INCLUDE_MIRANTS_CACHE_H_

#include <stdint.h>
#include "mirants/slice.h"

namespace mirants {

class Cache {
 public:
  Cache() { }

  // Destory all existing entries by calling the "deleter"
  // function that was passed to the constructor.
  virtual ~Cache();

  // Opaque handle to an entry stored in the cache.
  struct Handle { };

  // Insert a mapping from key->value into the cache and assign it 
  // the specified charge against the total cache capacity.
  //
  // Returns a handle that corresponds to the mapping. The caller
  // must call this->Release(handle) when the returned mapping is no
  // longer needed.
  //
  // When the inserted entry is no longer needed, the key and 
  // value will be passed to "deleter".

  virtual Handle* Insert(const Slice& key, void* value, size_t charge,
                         void (*deleter)(const Slice& key, void* value)) = 0;

  // If the cache has no mapping for "key", returns NULL.
  //
  // Else return a handle that corresponds to the mapping. The caller 
  // must call this->Release(handle) when the returned mapping is no
  // longer need.
  virtual Handle* Lookup(const Slice& key) = 0;

  // Release a mapping returned by a previous Lookup().
  // REQUIRES: handle must not have been released yet.
  // REQUIRES: handle must have been returned by a method on *this.
  virtual void Release(Handle* handle) = 0;

  // Return the value encapsulated in a handle returned by a 
  // successful Lookup().
  // REQUIRES: handle must not have been released yet.
  // REQUIRES: handle must have been returned by a method on *this.
  virtual void* Value(Handle* handle) = 0;

  // If the cache contains entry for key, erase it. Note that the 
  // underlying entry will be kept around util all exsiting handles
  // to it have been released.
  virtual void Erase(const Slice& key) = 0;

  // Return a new numberic id. May be used by multiple clients who are 
  // sharing the same cache to partition the key space. Typically the 
  // client will allocate a new id at startup and prepend the id to 
  // its cache keys.
  virtual uint64_t NewId() = 0;

 private:
  void LRU_Remove(Handle* e);
  void LRU_Append(Handle* e);
  void Unref(Handle* e);

  struct Rep;
  Rep* rep_;

  // No copying allowed
  Cache(const Cache&);
  void operator=(const Cache&);
};

}  // namespace mirants

#endif  // MIRANTS_INCLUDE_MIRANTS_CACHE_H_
