#include "util/strutil.h"

namespace mirants {

// -------------------------------------------------------------------------
// StripString
//    Replaces any occurrence of the character 'remove' (or the characters)
//    in 'remove') with the character 'replacewith'.
// -------------------------------------------------------------------------
void StripString(std::string* s, const char* remove, char replacewith) {
  const char* str_start = s->c_str();
  const char* str = str_start;
  for (str = strpbrk(str, remove);
       str != NULL;
       str = strpbrk(str + 1, remove)) {
    (*s)[str - str_start] = replacewith;
  }
}

void StripWhitespace(std::string* str) {
  int str_length = str->length();

  // Strip off leading whitespace.
  int first = 0;
  while (first < str_length && ascii_isspace(str->at(first))) {
    ++first;
  }
  // If entire string is white space.
  if (first == str_length) {
    str->clear();
    return;
  }
  if (first > 0) {
    str->erase(0, first);
    str_length -= first;
  }

  // Strip off trailing whitespace.
  int last = str_length - 1;
  while (last >= 0 && ascii_isspace(str->at(last))) {
    --last;
  }
  if (last != (str_length - 1) && last >= 0) {
    str->erase(last + 1, std::string::npos);
  }
}

// -------------------------------------------------------------------------
// StringReplace() 
//    Replace the "old" pattern with the "new" pattern in a string,
//    and append the result to "res". If replace_all is false,
//    it only replaces the first instance of "old".
// -------------------------------------------------------------------------

void StringReplace(const std::string& s, const std::string& oldsub,
                   const std::string& newsub, bool replace_all,
                   std::string* res) {
  if (oldsub.empty()) {
    res->append(s);   // if empty, append the given string.
    return;
  }
  std::string::size_type start_pos = 0;
  std::string::size_type pos;
  do {
    pos = s.find(oldsub, start_pos);
    if (pos == std::string::npos) {
      break;
    }
    res->append(s, start_pos, pos - start_pos);
    res->append(newsub);
    start_pos = pos + oldsub.size(); //start searching again after the "old"
  } while (replace_all);
  res->append(s, start_pos, s.length() - start_pos);
}

// -------------------------------------------------------------------------
// StringReplace()
//    Give me a string and two patterns "old" and "new", and I replace
//    the first instance of "old" in the string with "new", if it
//    exists. If "global" is true; call this repeatedly until it
//    fails. RETURN a new string, regardless of whether the replacement
//    happened or not.
// -------------------------------------------------------------------------

std::string StringReplace(const std::string& s, const std::string& oldsub,
                          const std::string& newsub, bool replace_all) {
  std::string ret;
  StringReplace(s, oldsub, newsub, replace_all, &ret);
  return ret;
}

// -------------------------------------------------------------------------
// SplitStringUsing()
//    Split a string using a character delimiter. Append the components
//    to 'result'.
//
// Note: For multi-character delimiters, this routine will spilt on *ANY* 
// of the characters in the string, not the entire string as a single 
// delimiter.
// -------------------------------------------------------------------------

template <typename ITR>
static inline 
void SplitStringToIteratorUsing(const std::string& full,
                                const char* delim,
                                ITR& result) {
  // Optimize the common case where delim is a single character.
  if (delim[0] != '\0' && delim[1] == '\0') {
    char c = delim[0];
    const char* p = full.data();
    const char* end = p + full.size();
    while (p != end) {
      if (*p == c) {
        ++p;
      } else {
        const char* start = p;
        while (++p != end && *p != c);
        *result++ = std::string(start, p - start);
      }
    } 
    return;
  }

  std::string::size_type begin_index, end_index;
  begin_index = full.find_first_not_of(delim);
  while (begin_index != std::string::npos) {
    end_index = full.find_first_of(delim, begin_index);
    if (end_index == std::string::npos) {
      *result++ = full.substr(begin_index);
      return;
    }
    *result++ = full.substr(begin_index, (end_index - begin_index));
    begin_index = full.find_first_not_of(delim, end_index);
  }
}

void SplitStringUsing(const std::string& full, 
                      const char* delim,
                      std::vector<std::string>* result) {
  std::back_insert_iterator< std::vector<std::string> > it(*result);
  SplitStringToIteratorUsing(full, delim, it);
}

// Split a string using a character delimiter. Append the components
// to 'result'. If there are consecutive delimiters, this function
// will return corrensponding empty strings. The string is split into
// at most the specified number of pieces greedily. This means that the
// last piece may possibly be split further. To spilt into as many pieces
// as possible, specify 0 as the number of pieces.
//
// If "full" is the empty string, yields an empty string as the only value.
//
// If "pieces" is negative for some reason, it returns the whole string
// ------------------------------------------------------------------------

template <typename StringType, typename ITR>
static inline 
void SplitStringToIteratorAllowEmpty(const StringType& full,
                                     const char* delim, 
                                     int pieces,
                                     ITR& result) {
}

void SplitStringAllowEmpty(const std::string& full, const char* delim,
                           std::vector<std::string>* result) {
}

// -------------------------------------------------------------------------
// JoinStrings() 
//    This merges a vector of string components with delim inserted
//    as separaters between components.
// -------------------------------------------------------------------------

template <class ITERATOR>
static void JoinStringsIterator(const ITERATOR& start, 
                                const ITERATOR& end,
                                const char* delim,
                                std::string* result) {
}

void JoinStrings(const std::vector<std::string>& components,
                 const char* delim,
                 std::string* result) {
}

}  // namespace mirants
