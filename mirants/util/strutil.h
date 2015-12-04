#ifndef MIRANTS_UTIL_STRUTIL_H_
#define MIRANTS_UTIL_STRUTIL_H_

#include <string>
#include <vector>

namespace mirants {

// --------------------------------------------------------------------------
// ascii_isalnum()
//    Check if an ASCII character is alphanumberic. We can't use ctype's
//    isalnum() because it is affected by locale. This function is applied
//    to indentifies in mirants, not to natural-language strings, so locale
//    should not be taken into account.
// ascii_isdigit() 
//    Like above, but only accepts digits.
// ascii_isspace()
//    Check if the character is a space character.
// ---------------------------------------------------------------------------

inline bool ascii_isalnum(char c) {
}

inline bool ascii_isdigit(char c) {
}

inline bool ascii_isspace(char c) {
}

inline bool ascii_isupper(char c) {
}

inline bool ascii_islower(char c) {
}

inline char ascii_toupper(char c) {
}

inline int hex_digit_to_int(char c) {
}

// --------------------------------------------------------------------------
// HasPrefixString() 
//    Check if a string begins with a given prefix.
// StringPrefixString() 
//    Given a string and a putative prefix, returns the string minus the
//    prefix string if the prefix matches, otherwise the original string.
// --------------------------------------------------------------------------
inline bool HasPrefixString(const std::string& str,
                            const std::string& prefix) {
}

inline std::string  StripSuffixString(const std::string& str, 
                            const std::string& suffix) {
}

// --------------------------------------------------------------------------
// StripString
//    Replaces ant occurrence of the character 'remove' (or the characters
//    in 'remove') with the character 'replacewith'.
// StripWhitespace
//    Removes whitespaces from both ends of the given string.
// --------------------------------------------------------------------------
void StripString(std::string* s, const char* remove,
                 char replaceWith);

void StripWhitespace(std::string* s);

// --------------------------------------------------------------------------
// LowerString()
// UpperString()
// ToUpper()
//    Convert the characters in "s" to lowercase or uppercase. ASCII-only:
//    these functions intentionally ignore locale because they are applied to 
//    identifiers used in the mirants, not to natural-language strings.
// --------------------------------------------------------------------------

inline void LowerString(std::string* s) {
}

inline void UpperString(std::string* s) {
}

inline void ToUpper(const std::string& s) {
}

// --------------------------------------------------------------------------
// StringReplace() 
//    Given me a string and two patterns "old" and "new", and I replace 
//    the first instance of "old" in the string with "new", if it
//    exsits. RETURN a new string, regardless of whether the replacement
//    happended or not.
// --------------------------------------------------------------------------
std::string StringReplace(const std::string& s, const std::string& oldsub,
                          const std::string& newsub, bool replace_all);

// --------------------------------------------------------------------------
// SplitStringUsing() 
//    Split a string using a character delimiter. Append the components
//    to 'result'. If there are consecutive delimiters, this function skips
//    over all of them.
// -------------------------------------------------------------------------
void SplitStringUsing(const std::string& full, const char* delim,
                      std::vector<std::string>* res);

// Split a string using one or more byte delimiters, presented
// as a nul-terminated c string. Append the components to 'result'.
// If there are consecutive delimiters, this function will return
// corresponding empty strings. If you want to drop the empty
// strings, try SplitStringUsing().
//
// If "full" is the empty string, yields an empty string as the only value.
// ------------------------------------------------------------------------
void SplitStringAllowEmpty(const std::string& full, 
                           const char* delim,
                           std::vector<std::string>* result);

// -------------------------------------------------------------------------
// Split()
//     Split a string using a character delimiter.
// -------------------------------------------------------------------------
inline std::vector<std::string> Split(std::string& full,
                                      const char* delim,
                                      const skip_empty = true) {
}

// -------------------------------------------------------------------------
// JoinStrings()
//    These methods concatenate a vector of strings into a C++ string, using
//    the C-string "delim" as a separator between components. There are two
//    flavors of the function, one flavor returns the concatenated string,
//    another takes a pointer to the target string. In the latter case the 
//    target string is cleared and overwritten.
// -------------------------------------------------------------------------
void JoinStrings(const std::vector<std::string>& components,
                 const char* delim, std::string* result);

}  // namespace mirants

#endif  // MIRANTS_UTIL_STRUTIL_H_
