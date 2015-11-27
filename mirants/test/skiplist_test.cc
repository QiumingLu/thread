#include "core/skiplist.h"

#include <set>
#include "util/arena.h"
#include "util/testharness.h"

namespace mirants {

typedef uint64_t Key;

struct Comparator {
  int operator()(const Key& a, const Key& b) const {
    if (a < b) {
      return -1;
    } else if(a > b) {
      return +1;
    } else {
      return 0;
    }
  }
};

class SkipTest { };

TEST(SkipTest, Empty) {
  Arena arena;
  Comparator cmp;
  SkipList<Key, Comparator> list(cmp, &arena);
  ASSERT_TRUE(!list.Contains(10));

  SkipList<Key, Comparator>::Iterator iter(&list);
  ASSERT_TRUE(!iter.Valid());
  iter.SeekToFirst();
  ASSERT_TRUE(!iter.Valid());
  iter.Seek(100);
  ASSERT_TRUE(!iter.Valid());
  iter.SeekToLast();
  ASSERT_TRUE(!iter.Valid());
}

TEST(SkipTest, InsertAddLookup) {
  const int N = 200;
  const int R = 500;
  Random rnd(100);
  std::set<Key> keys;
  Arena arena;
  Comparator cmp;
  SkipList<Key, Comparator> list(cmp, &arena);
  for (int i = 0; i < N; ++i) {
    Key key = rnd.Next() % R;
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }

  for (int i = 0; i < R; ++i) {
    if (list.Contains(i)) {
      ASSERT_EQ(static_cast<int>(keys.count(i)), 1);
    } else {
      ASSERT_EQ(static_cast<int>(keys.count(i)), 0);
    }
  }

  // Simple iterator tests
  {
    SkipList<Key, Comparator>::Iterator iter(&list);
    ASSERT_TRUE(!iter.Valid());

    iter.Seek(0);
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(*(keys.begin()), iter.key());

    iter.SeekToFirst();
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(*(keys.begin()), iter.key());

    iter.SeekToLast();
    ASSERT_TRUE(iter.Valid());
    ASSERT_EQ(*(keys.rbegin()), iter.key());
  }

  // Forward iteration test
  for (int i = 0; i < R; ++i) {
    SkipList<Key, Comparator>::Iterator iter(&list);
    iter.Seek(i);

    std::set<Key>::iterator model_iter = keys.lower_bound(i);
    for (int j = 0; j < 3; ++j) {
      if (model_iter == keys.end()) {
        ASSERT_TRUE(!iter.Valid());
        break;
      } else {
        ASSERT_TRUE(iter.Valid());
        ASSERT_EQ(*model_iter, iter.key());
        ++model_iter;
        iter.Next();
      }
    }
  }

  // Backward iteration test
  {
    SkipList<Key, Comparator>::Iterator iter(&list);
    iter.SeekToLast();

    // Compare against model iterator
    for (std::set<Key>::reverse_iterator model_iter = keys.rbegin();
         model_iter != keys.rend();
         ++model_iter) {
      ASSERT_TRUE(iter.Valid());
      ASSERT_EQ(*model_iter, iter.key());
      iter.Prev();
    }
    ASSERT_TRUE(!iter.Valid());
  }
}

// We want to make sure that with a single writer and multiple
// concurrent readers (with no syncronization other than when a 
// reader's iterator is created), the reader always observers all the
// data that was present in the skip list when the iterator was
// constuctor. Because insertions are happending concurrently, we may
// also observer new values that were inserted since the iterator was
// constructed, but we should never miss any values that were present
// at iterator construction time.
//
// We generate multi-part keys:
//     <key, gen,hash>
// where:
//     key is in range [0..K-1]
//     gen is a generation number for key
//     hash is hash(key,gen)
//
// The insertion code picks a random key, sets gen to be 1 + the last
// generation number inserted for that key, and sets hash to Hash(key,gen).
//
// At the beginning of a read, we snapshot the last inserted 
// generation number for each key. We the iterate, including random 
// calls to Next() and Seek(). For every key we encounter, we 
// check that it is either expected given the initial snapshot or has 
// been concurrently added since the iterator started.
class ConcurrentTest {
 private:
  static const uint32_t K = 4;

  static uint64_t key(Key key) { return (key >> 40); }
  static uint64_t gen(Key key) { return (key >> 8) & 0xffffffffu; }
  static uint64_t hash(Key key) { return key & 0xff; }

  static uint64_t HashNumbers(uint64_t k, uint64_t g) {
    uint64_t data[2] = {k, g};
    return Hash(reinterpret_cast<char*>(data), sizeof(data), 0);
  }

  static Key MakeKey(uint64_t k, uint64_t g) {
    assert((sizeof(Key)) == sizeof(uint64_t));
    assert(k <= K); // We sometimes pass K to seek to the end of the skiplist
    assert(g <= 0xffffffffu);
    return ((k << 40 | g << 8) | (HashNumbers(k, g) & 0xff));
  }

  static bool IsValidKey(Key k) {
    return hash(k) == (HashNumbers(key(k), gen(k)) & 0xff);
  }

  static Key RandomTarget(Random* rnd) {
    switch (rnd->Next() % 10) {
      case 0:
        // Seek to beginning 
        return MakeKey(0, 0);
      case 1:
        return MakeKey(K, 0);
      default:
        // Seek to middle
        return MakeKey(rnd->Next() % K, 0);
    }
  }

  // Per-key generation
  struct State {
  };

}; 

}  // namespace mirants

int main(int argc, char** argv) {
  return mirants::test::RunAllTests();
}
