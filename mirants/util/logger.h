#ifndef MIRANTS_UTIL_LOGGER_H_
#define MIRANTS_UTIL_LOGGER_H_

#include <string>

#include "util/status.h"

namespace mirants {

enum LogLevel {
  LOGLEVEL_INFO,
  LOGLEVEL_WARNING,
  LOGLEVEL_ERROR,
  LOGLEVEL_FATAL,

#ifdef NDEBUG
  LOGLEVEL_DFATAL = LOGLEVEL_ERROR
#else 
  LOGLEVEL_DFATAL = LOGLEVEL_FATAL
#endif
};

class LogMessage {
 public:
  LogMessage(LogLevel level, const char* filename, int line);
  ~LogMessage();

  LogMessage& operator<<(const std::string& value);
  LogMessage& operator<<(const char* value);
  LogMessage& operator<<(char value);
  LogMessage& operator<<(int value);
  // TODO
  //LogMessage& operator<<(uint value);
  LogMessage& operator<<(long value);
  LogMessage& operator<<(unsigned long value);
  LogMessage& operator<<(long long value);
  LogMessage& operator<<(unsigned long long value);
  LogMessage& operator<<(double value);
  LogMessage& operator<<(void* value);
  LogMessage& operator<<(const Status& status);

 private:
  friend class LogFinisher;
  void Finish();

  LogLevel level_;
  const char* filename_;
  int line_;
  std::string message_;
};

class LogFinisher {
 public:
  void operator=(LogMessage& other);
};

template<typename T>
bool IsOk(T status) { return status.ok(); }
template<>
inline bool IsOk(bool status) { return status; }

#define MIRANTS_LOG(LEVEL)                                      \
  ::mirants::LogFinisher() =                                    \
    ::mirants::LogMessage(                                      \
      ::mirants::LOGLEVEL_##LEVEL, __FILE__, __LINE__)
#define MIRANTS_LOG_IF(LEVEL, CONDITION) \
  !(CONDITION)? (void)0 : MIRANTS_LOG(LEVEL)

#define MIRANTS_CHECK(EXPRESSION) \
  MIRANTS_LOG_IF(FATAL, !(EXPRESSION)) << "CHECK failed: " #EXPRESSION ":"
#define MIRANTS_CHECK_OK(A) MIRANTS_CHECK(::mirants::IsOk(A))
#define MIRANTS_CHECK_EQ(A, B) MIRANTS_CHECK((A) == (B))
#define MIRANTS_CHECK_NE(A, B) MIRANTS_CHECK((A) != (B))
#define MIRANTS_CHECK_LT(A, B) MIRANTS_CHECK((A) < (B))
#define MIRANTS_CHECK_LE(A, B) MIRANTS_CHECK((A) <= (B))
#define MIRANTS_CHECK_GT(A, B) MIRANTS_CHECK((A) > (B))
#define MIRANTS_CHECK_GE(A, B) MIRANTS_CHECK((A) >= (B))

template<typename T>
T* CheckNotNull(const char* /* file */, int /* line */,
                const char* name, T* val) {
  if (val == NULL) {
    MIRANTS_LOG(FATAL) << name;
  }
  return val;
}

#define MIRANTS_CHECK_NOTNULL(A)  \
  ::mirants::CheckNotNull(\
      __FILE__, __LINE__, "'" #A "' must not be NULL", (A))

typedef void LogHandler(LogLevel level, const char* filename, int line,
                        const std::string& message);

LogHandler* SetLogHandler(LogHandler* new_func);

class LogSilencer {
 public:
  LogSilencer();
  ~LogSilencer();
};

}  // namespace mirants

#endif  // MIRANTS_UTIL_LOGGER_H_
