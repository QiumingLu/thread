#ifndef MIRANTS_UTIL_STL_UTIL_H_
#define MIRANTS_UTIL_STL_UTIL_H_

#include <string>

namespace mirants {

// STLDeleteContainerPointers()
// For a range within a container of pointers, calls delete
// (non-array version) on these pointers.
template <class ForwardIterator>
void STLDeleteContainerPointers(ForwardIterator begin, 
                                ForwardIterator end) {
}

inline void STLStringResizeUninitialized(std::string* s, size_t new_size) {
}

// Return a mutable char* pointing to a string's internal buffer,
// which may not be null-terminated. Writing through this pointer will 
// modify the string.
//
// string_as_array(&str)[i] is valid for 0 <= i < str.size() until the 
// next call to a string method that invalidates iterators.
inline char* string_as_array(std::string* str) {
  // DO NOT USE const_cast<char*>(str->data())!
}

// STLDeleteElements() deletes all the elements in an STL container and clears
// the container. This function is suitable for use with a vector, set, 
// hash_set, or any other STL container which defines sensible begin(), end(),
// and clear() methods.
//
// if container is NULL, this function is a no-op.
//
// As an alternative to calling STLDeleteElements() directly, consider\
// ElementDeleter (defined below), which ensures that your container's elements
// are deleted when the ElementDeleter goes out of scope.
template <class T> 
void STLDeleteElements(T *container) {
}

// Given an STL container consisting of (key, value) pairs, STLDeleteValues
// deletes all the "value" components and clears the container. Does nothing
// in the case it's given a NULL, pointer.
template <class T>
void STLDeleteValues(T *v) {
}

}  // namespace mirants

#endif  // MIRANTS_UTIL_STL_UTIL_H_
