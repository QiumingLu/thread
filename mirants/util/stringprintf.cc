#include "util/stringprintf.h"

#include <stdio.h>
namespace mirants {

void StringAppendV(std::string* dst, const char* format, va_list ap) {
  // First try with a small fixed size buffer
  static const int kSpaceLeght = 1024;
  char space[kSpaceLeght];

  // It's possible for methods that use a va_list to invalidate
  // the data in it upon use. The fix is to make a copy of 
  // the structure before using it and use that copying instead.
}

std::string StringPrintf(const char* format, ...) {
}

const std::string& SStringPrintf(std::string* dst, 
                                 const char* format, ...) {
}

void StringAppendF(std::string* dst, const char* format, ...) {
}

// Max arguments supported by StringPrintfVector
const int kStringPrintfVectorMaxArgs = 32;

static const char string_printf_empty_block[256] = { '\0' };

std::string StringPrintfVector(const char* format, 
                               const std::vector<std::string>& v) {
}

} // namespace mirants
