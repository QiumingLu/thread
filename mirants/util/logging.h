#ifndef MIRANTS_UTIL_LOGGING_H_
#define MIRANTS_UTIL_LOGGING_H_

#include <string>
#include <stdint.h>

namespace mirants {

class Slice;
  
// Append a human-readable printout of "num" to *str. 
extern void AppendNumberTo(std::string* str, uint64_t num);

// Append a human-readable printout of "value" to *str.
// Escapes any non-printable characters found in "value".
extern void AppendEscapedStringTo(std::string* str, const Slice& value);

// Return a human-readable printout of "num"
extern std::string NumberToString(uint64_t num);

// Return a human-readable version of "num"
extern std::string EscapeString(const Slice& value);

// Parse a human-readable number from "in" into *value. On success,
// advances "*in" past the consumed number and sets "*val" to the 
// numberic value. Otherwise, returns  false and leaves *in in an 
// unspecified state.
extern bool ConsumeDecimalNumber(Slice* in, uint64_t* val);

}  // namespace mirants

#endif  // MIRANTS_UTIL_LOGGING_H_
