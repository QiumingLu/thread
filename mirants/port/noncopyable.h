#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

class Noncopyable {
 protected:
  Noncopyable() {}                    //允许 derived 对象构造和析构
  ~Noncopyable() {}

 private:
  Noncopyable(const Noncopyable&);   // 但阻止 copying
  Noncopyable& operator= (const Noncopyable&);
};

#endif  // NONCOPYABLE_H