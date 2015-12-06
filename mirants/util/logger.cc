#include "util/logger.h"

#include "port/port_posix.h"

namespace mirants {

void DefaultLogHandler(LogLevel level, const char* filename, int line,
                       const std::string& message) {
  static const char* level_names[] = { "INFO", "WARNING", "ERROR", "FATAL" };
  // We use fprintf() instead of cerr because we want this work at static 
  // initialization time.
  fprintf(stderr, "mirants %s %s:%d] %s\n",
          level_names[level], filename, line, message.c_str());
  fflush(stderr);
}

void NullLogHandler(LogLevel /* level */, const char* /* filename */,
                    int /* line */, const std::string& /* message */) {
  // Nothing
}

static LogHandler* log_handler_ = &DefaultLogHandler;

LogMessage::LogMessage(LogLevel level, const char* filename, int line)
    : level_(level), filename_(filename), line_(line) 
{ }

LogMessage::~LogMessage() { }

LogMessage& LogMessage::operator<<(const std:string& value) {
  message_ += value;
  return *this;
}

LogMessage& LogMessage::operator<<(const char* value) {
  message_ += value;
  return *this;
}

LogMessage& LogMessage::operator<<(const Slice& slice) {
  message_ += slice.ToString();
  return *this;
}

LogMessage& LogMessage::operator<<(const Status& status) {
  message_ += status.ToString();
  return *this;
}


// Since this is just for logging, we don't care if the current locale 
// changes the results -- in fact, we probaly prefer that. So we use 
// snprintf() instead of Simple*toa().
#undef DECLARE_STREAM_OPERATOR
#define DECLARE_STREAM_OPERATOR(TYPE, FORMAT)                       \
  LogMessage& LogMessage::operator<<(TYPE value) {                  \
    /* 128 bytes should be big enough for any of the primitive */   \
    /* values which we print with this, but well use snprintf() */  \
    /* anyway to be extra safe. */                                  \
    char buffer[128];                                               \
    snprintf(buffer, sizeof(buffer), FORMAT, value);                \
    /* Guard against broken MSVC snprintf(). */                     \
    buffer[sizeof(buffer)-1] = '\0';                                \
    message_ += buffer;                                             \
    return *this;                                                   \
  }

DECLARE_STREAM_OPERATOR(char         , "%c" )
DECLARE_STREAM_OPERATOR(int          , "%d" )
DECLARE_STREAM_OPERATOR(unsigned int , "%u" )
DECLARE_STREAM_OPERATOR(long         , "%ld")
DECLARE_STREAM_OPERATOR(unsigned long, "%lu")
DECLARE_STREAM_OPERATOR(double       , "%g" )
DECLARE_STREAM_OPERATOR(void*        , "%p" )
//TODO
DECLARE_STREAM_OPERATOR(long long         , "%lld")
DECLARE_STREAM_OPERATOR(unsigned long long, "%llu")
#undef DECLARE_STREAM_OPERATOR

// TODO
void LogMessage::Finish() {
  log_handler_(level_, filename_, line_, message_);
}

void LogFinisher::operator=(LogMessage& other) {
  other.Finish();
}

LogHandler* SetLogHandler(LogHandler* new_func) {
  LogHandler* old = log_handler_;
  if (old == &NullLogHandler) {
    old = NULL;
  }
  if (new_func == NULL) {
    log_handler_ = &NullLogHandler;
  } else {
    log_handler_ = new_func;
  }
  return old;
}

/*
static Mutex* log_silencer_count_mutex_ = NULL;

void InitLogSilencerCount() {
  log_silencer_count_mutex_ = new Mutex();
}

void InitLogSilencerCountOnce() {
  mirants::port::InitOnce()
}
*/
LogSilencer::LogSilencer() {
}

LogSilencer::~LogSilencer() {
}

}  // namespace mirants
