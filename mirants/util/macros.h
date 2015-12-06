#ifndef MIRANTS_UTIL_MAROCS_H_
#define MIRANTS_UTIL_MAROCS_H_

namespace mirants {

typedef unsigned int uint;

#ifdef _MSC_VER
typedef signed __int8  int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;

typedef unsigned __int8  uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
#else
typedef signed char  int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
#endif

// long long macros to be used because gcc and vc++ use different suffixes,
// and different size specifiers in format strings
#undef MIRANTS_LONGLONG
#undef MIRANTS_ULONGLONG
#undef MIRANTS_LL_FORMAT

#ifdef _MSC_VER
#define MIRANTS_LONGLONG(x) x##I64
#define MIRANTS_ULONGLONG(x) x##UI64
#define MIRANTS_LL_FORMAT "I64"  // As in printf("%I64d", ...)
#else
#define MIRANTS_LONGLONG(x) x##LL
#define MIRANTS_ULONGLONG(x) x##ULL
#define MIRANTS_LL_FORMAT "ll"  // As in "%lld". Note that "q" is poor form also.
#endif

static const int32 kint32max = 0x7FFFFFFF;
static const int32 kint32min = -kint32max - 1;
static const int64 kint64max = MIRANTS_LONGLONG(0x7FFFFFFFFFFFFFFF);
static const int64 kint64min = -kint64max - 1;
static const uint32 kuint32max = 0xFFFFFFFFu;
static const uint64 kuint64max = MIRANTS_ULONGLONG(0xFFFFFFFFFFFFFFFF);



#undef DISALLOW_EVIL_CONSTRUCTORS
#define DISALLOW_EVIL_CONSTRUCTORS(TypeName)     \
  TypeName(const TypeName&);                     \
  void operator=(const TypeName&)                \

#undef DISALLOW_IMPLICIT_CONSTRUCTORS
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName();                                    \
  TypeName(const TypeName&);                     \
  void operator=(const TypeName&)                \

}  // namespace mirants

#endif  // MIRANTS_UTIL_MAROCS_H_
