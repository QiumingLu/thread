#include "include/mirants/cache.h"

#include <vector>
#include "util/coding.h"
#include "util/testharness.h"

namespace mirants {

// Conversions between numeric keys/values and the types expected by Cache.
static std::string EncodeKey(int k) {
  std::string result;
  PutFixed32(&result, k);
  return result;
}

static int DecodeKey(const Slice& k) {
  assert(k.size() == 4);
  return DecodeFixed32(k.data());
}

static void* EncodeValue(uintptr_t v) {
  return reinterpret_cast<void*>(v);
}

static int DecodeValue(void* v) {
  return reinterpret_cast<uintptr_t>(v);
}

class CacheTest {
 public:
  static CacheTest* current_;

  static void Deleter(const Slice& key, void* v) {
    current_->deleted_keys_.push_back(DecodeKey(key));
    current_->deleted_values_.push_back(DecodeValue(v));
  }

  static const int kCacheSize = 1000;
  std::vector<int> deleted_keys_;
  std::vector<int> deleted_values_;
  Cache* cache_;

  CacheTest() : cache_(NewLRUCache(kCacheSize)) {
    current_ = this;
  }

  ~CacheTest() {
    delete cache_;
  }

  int Lookup(int key) {
    Cache::Handle* handle = cache_->Lookup(EncodeKey(key));
    printf("Lookup %d\n", DecodeValue(cache_->Value(handle)));
    const int r = (handle == NULL) ? -1 : DecodeValue(cache_->Value(handle));
    if (handle != NULL) {
      cache_->Release(handle);
    }
    return r;
  }

  void Insert(int key, int value, int charge = 1) {
    Cache::Handle* handle = cache_->Insert(EncodeKey(key), EncodeValue(value), charge,
                                   &CacheTest::Deleter);
    printf("Insert %d\n", DecodeValue(cache_->Value(handle)));
    cache_->Release(handle);
  }

  void Erase(int key) {
    cache_->Erase(EncodeKey(key));
  }
};

CacheTest* CacheTest::current_;

TEST(CacheTest, HitAndMiss) {
  ASSERT_EQ(-1, Lookup(100));

  Insert(100, 101);
  ASSERT_EQ(101, Lookup(100));
  ASSERT_EQ(-1, Lookup(200));
  ASSERT_EQ(-1, Lookup(300));

  Insert(200, 201);
  ASSERT_EQ(101, Lookup(100));
  ASSERT_EQ(201, Lookup(200));
  ASSERT_EQ(-1, Lookup(300));

  Insert(100, 102);
  ASSERT_EQ(102, Lookup(100));
  ASSERT_EQ(201, Lookup(200));
  ASSERT_EQ(-1, Lookup(300));

  ASSERT_EQ(1, static_cast<int>(deleted_keys_.size()));
  ASSERT_EQ(100, deleted_keys_[0]);
  ASSERT_EQ(101, deleted_values_[0]);
}

}  // namespace mirants

int main(int argc, char** argv) {
  return mirants::test::RunAllTests();
}
