#ifndef MIRANTS_INCLUDE_MIRANTS_ENV_H_
#define MIRANTS_INCLUDE_MIRANTS_ENV_H_

#include <stdarg.h>
#include "include/mirants/status.h"

namespace mirants {
class WritableFile {
};

// C语言标准库中头文件 <stdarg.h> 索引的接口包含了一组能够遍历变长参数列表的宏。
// 主要包含下面几个：

// 1、va_list 用来声明一个表示参数表中各个参数的变量。

// 2、va_start 初始化一个指针来指向变长参数列表的头一个变量
//   （注意，...只能出现在参数表的最后）
// 3、va_arg每次调用时都会返回当前指针指向的变量，并将指针挪至下一个位置，
// 参数的类型需要在这个调用的第二个参数来指定，va_arg也是根据这个参数来判断偏移的距离。

// 4、va_end需要在函数最后调用，来进行一些清理工作。

// An interface for writing log messages.
class Logger {
 public:
  Logger() { }
  virtual ~Logger();

  // Write an entry to the log file with the specified format.
  virtual void  Logv(const char* format, va_list ap) = 0;

 private:
  // No copying allowed.
  Logger(const Logger&);
  void operator=(const Logger&);
};

// Identifies a locked file.
class FileLock {
 public:
  FileLock() { }
  virtual ~FileLock();

 private:
  // No copying allowed.
  FileLock(const FileLock&);
  void operator=(const FileLock&);
};

}  // namespace mirants

#endif  // MIRANTS_INCLUDE_MIRANTS_ENV_H_
