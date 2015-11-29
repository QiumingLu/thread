#ifndef MIRANTS_PORT_CURRENT_THREAD_H_
#define MIRANTS_PORT_CURRENT_THREAD_H_

#include <stdint.h>

namespace mirants {
namespace currentthread {

extern __thread int  t_cached_tid;
extern __thread char t_tid_string[32];
extern __thread int  t_tid_string_length;
extern __thread const char* t_thread_name;
extern void CacheTid();

// __builtin_expect 指令是gcc引入的，
// 作用是"允许程序员将最有可能执行的分支告诉编译器"。
// 这个指令的写法为：__builtin_expect(EXP, N)。意思是：EXP==N的概率很大。
// 一般的使用方法是将__builtin_expect指令封装为LIKELY和UNLIKELY宏。
// 这两个宏的写法如下：
// #define LIKELY(x) __builtin_expect(!!(x), 1) //x很可能为真
// #define UNLIKELY(x) __builtin_expect(!!(x), 0) //x很可能为假
// __builtin_expect((x),1) 表示 x 的值为真的可能性更大； 
// __builtin_expect((x),0) 表示 x 的值为假的可能性更大。

inline int Tid() {
  if (__builtin_expect(t_cached_tid == 0, 0)) {
    CacheTid();
  }
  return t_cached_tid;
}

inline const char* TidString() {
  return t_tid_string;
}

inline int TidStringLength() {
  return t_tid_string_length;
}

inline const char* Name() {
  return t_thread_name;
}

extern bool IsMainThread();

}  // namespace currentthread
}  // namespace mirants

#endif  // MIRANTS_PORT_CURRENT_THREAD_H_
