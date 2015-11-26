// Simple hash function used for internal data structues.

#ifndef MIRANTS_UTIL_HASH_H_
#define MIRANTS_UTIL_HASH_H_

#include <stddef.h>
#include <stdint.h>

namespace mirants {

extern uint32_t Hash(const char* data, size_t n, uint32_t seed);

}  // mirants

#endif  // MIRANTS_UTIL_HASH_H_
