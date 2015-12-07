#ifndef MIRANTS_UTIL_BASE_H_
#define MIRANTS_UTIL_BASE_H_ 

namespace mirants {

typedef signed char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

#define MIRANTS_LONGLONG(x) x##LL
#define MIRANTS_ULONGLONG(X) X##ULL
#define MIRANTS_LL_FORMAT "ll"

static const int32 kint32max = 0x7FFFFFFF;
static const int32 kint32min = -kint32max - 1;
static const int64 kint64max = MIRANTS_LONGLONG(0x7FFFFFFFFFFFFFFF);
static const int64 kint64min = -kint64max - 1;
static const uint32 kuint32max = 0xFFFFFFFFu;
static const uint64 kuint64max = MIRANTS_ULONGLONG(0xFFFFFFFFFFFFFFFF);

}  // namespace mirants

#endif  // MIRANTS_UTIL_BASE_H_
