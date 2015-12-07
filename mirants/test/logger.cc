#include "util/logger.h"
#include "util/testharness.h"

namespace mirants {

class LoggerTest { };

TEST(LoggerTest, DefaultLogHandler) {
  int line = __LINE__;
  MIRANTS_LOG(INFO   ) << "A message.";
  MIRANTS_LOG(WARNING) << "A warning.";
  MIRANTS_LOG(ERROR  ) << "An error."; 

  ASSERT_EQ();
}

}  // namespace mirants 

int main(int argc, char** argv) {
  return mirants::test::RunAllTests();
}
