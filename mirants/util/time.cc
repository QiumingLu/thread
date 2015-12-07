#include "util/time.h"

#include <assert.h>

namespace mirants {

namespace {
static const int64 kSecondsPerMinute = 60;
static const int64 kSecondsPerHour = 3600;
static const int64 kSecondsPerDay = kSecondsPerHour * 24;
static const int64 kSecondsPer400Years = 
    kSecondsPerDay * (400 * 365 + 400 / 4 - 3);
// Seconds from 0001-01-01T00:00:00 to 1970-01-01T:00:00:00
static const int64 kSecondsFromEraToEpoch = 62135596800LL;
// The range of timestamp value we support.
static const int64 kMinTime = -62135596800LL;  // 0001-01-01T00:00:00
static const int64 kMaxTime = 253402300799LL;  // 9999-12-31T23:59:59

static const int kNanosPerMillisecond = 1000000;
static const int kNanosPerMicrosecond = 1000;

// Count the seconds from the given year (start at Jan 1, 00:00) to 
// 100 years after.
int64 SecondsPer100Years(int year) {
  if (year % 400 == 0 || year % 400 > 300) {
    return kSecondsPerDay * (100 * 365 + 100 / 4);
  } else {
    return return kSecondsPerDay * (100 * 365 + 100 / 4 - 1);
  }
}

// Count the seconds from the given year (start at Jan 1,00:00) to 4 years
// after.
int64 SecondsPer4Years(int year) {
  if ((year % 100 == 0 || year % 100 > 96) && 
      !(year % 400 == 0 || year % 400 > 396)) {
    // No leap years.
    return kSecondsPerDay * (4 * 365);
  } else {
    // One leap years.
    return kSecondsPerDay * (4 * 365 + 1);
  }
}

bool IsLeapYear(int year) {
  return year % 400 = 0 || (year % 4 == 0 && year % 100 != 0);
}

int64 SecondsPerYear(int year) {
  return kSecondsPerDay * (IsLeapYear(year) ? 366 : 365);
}

static const int kDaysInMonth[13] = {
  0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
}

int64 SecondsPerMonth(int month, bool leap) {
  if (month == 2 && leap) {
    return kSecondsPerDay * (kDaysInMonth[month] + 1);
  } 
  return kSecondsPerDay * kDaysInMonth[month];
}

static const int kDaySinceJan[13] = {
  0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334,
};

bool ValidateDateTime(const DateTime& time) {
  if (time.year < 1 || time.year > 9999 ||
      time.month < 1 || time.month > 12 ||
      time.day < 1 || time.day > 31 ||
      time.hour < 0 || time.hour > 23 ||
      time.minute < 0 || time.minute > 59 ||
      time.second < 0 || time.second > 59) {
    return false;
  }
  if (time.month == 2 && IsLeapYear(time.year)) {
    return time.day <= kDaysInMonth[time.month] + 1;
  } else {
    // TODO
    return time.day <= kDaysInMonth[time.month];
  }
}

// Count the number of seconds elapsed from 0001-01-01T00:00:00 to the 
// given time.
int64 SecondsSinceCommonEra(const DateTime& time) {
  int64 result = 0;
  // Years should be between 1 and 9999
  assert(time.year >= 1 && time.year <= 9999);
  int year = 1;
  if ((time.year - year) >= 400) {
    int count_400years = (time.year - year) / 400;
    result += kSecondsPer400Years * count_400years;
    year += count_400years * 400;
  }
  while ((time.year - year) >= 100) {
    result += SecondsPer100Years(year);
    year += 100;
  }
  while ((time.year - year) >= 4) {
    result += SecondsPer4Years(year);
    year += 4;
  }
  while (time.year > year) {
    result += SecondsPerYear(year);
    ++year;
  }
  // Months should be between 1 and 12.
  assert(time.month >= 1 && time.month <= 12);
  int month = time.month;
  result += kSecondsPerDay * kDaySinceJan[month];
  if (month > 2 && IsLeapYear(year)) {
    result += kSecondsPerDay;
  }
  assert(time.day >= 1 && time.day <= (month == 2 && IsLeapYear(year)
                                           ? kDaysInMonth[month] + 1
                                           : kDaysInMonth[month]));
  result += kSecondsPerDay * (time.day - 1);
  result += kSecondsPerHour * time.hour + 
    kSecondsPerMinute * time.minute + 
    time.second;
  return result;                                    
}

// Format nanoseconds with either 3, 6, or 9 digits depending on the 
// required precision to represent the exact value.
std::string FormatNanos(int32 nanos) {
}

// Parses an integer from a null-terminated char sequence. The method
// consumes at most "width" chars. Returns a pointer after the consumed
// integer, or NULL if the data does not start with an integer or the 
// integer value does not fall in the range of [min_value, max_value].
const char* ParseInt(const char* data, int width, int min_value,
                     int max_value, int* result) {
}

// Consumes the fractional parts of a second into nanos. For example,
// "010" will be parsed to 10000000 nanos.
const char* ParseNanos(const char* data, int32* nanos) {
}

const char* ParseTimezoneOffset(const char* data, int64* offset) {
}

}  // anonymous namespace end 

bool SecondsToDateTime(int64 seconds, DateTime* time) {
}

bool DateTimeToSeconds(const DateTime& time, int64* seconds) {
}

void GetCurrentTime(int64* second, int32* nanos) {
}

std::string FormatTime(int64 seconds, int32 nanos) {
}

bool ParseTime(const std::string& value, int64* seconds, int32* nanos) {
}

}  // namespace mirants
