#ifndef MIRANTS_UTIL_FILE_H_
#define MIRANTS_UTIL_FILE_H_

#include <string>

#include "util/macros.h"

namespace mirants {

// Only use in tests
class File {
 public:
  // Check if the file exists.
  static bool Exists(const std::string& name);

  // Read an entire file to a string. Return true if successful, false
  // otherwise.
  static bool ReadFileToString(const std::string& name, std::string* output);

  // Same as above, but crash on failure.
  static void ReadFileToStringOrDie(const std::string& name, 
                                    std::string* output);

  // Create a file and write a string to it.
  static bool WriteStringToFile(const std::string& contents,
                                const std::string& name);

  // Same as above, but crash on failure.
  static void WriteStringToFileOrDie(const std::string& contens,
                                     const std::string& name);

  // Create a directory and all parent directories if neccessary.
  static bool RecursivelyCreateDir(const std::string& path, int mode);

  // If "name" is a file, we delete it. If it is a directly, we 
  // call DeleteRecursively() for each file or directly (other than
  // dot and double-dot) within it, and then delete the directly itself.
  static void DeleteRecursively(const std::string& name, 
                                void* dummy1, void* dummy2);

  // Change working directory to given directly.
  static bool ChangeWorkingDiectory(const std::string& new_working_directory);

  static bool GetContents(
      const std::string& name, std::string* output, bool /* is_default */) {
  }

  static bool SetContents(const std::string& name, 
                          const std::string& contents, 
                          bool /* is_default*/) {
  }

 private:
  DISALLOW_EVIL_CONSTRUCTORS(File);
};

}  // namespace mirants

#endif  // MIRANTS_UTIL_FILE_H_
