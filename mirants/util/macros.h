#ifndef MIRANTS_UTIL_MAROCS_H_
#define MIRANTS_UTIL_MAROCS_H_

namespace mirants {

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
