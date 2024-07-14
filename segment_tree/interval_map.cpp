#include <cassert>
#include <iostream>
#include <map>

void IntervalMapTest();

class CustomKey {
public:
  int value;

  CustomKey(int v) : value(v) {}

  bool operator<(const CustomKey &other) const { return value < other.value; }
};

template <typename K, typename V> class interval_map {
  friend void IntervalMapTest();
  V m_valBegin;
  std::map<K, V> m_map;

public:
  // constructor associates whole range of K with val
  interval_map(V const &val) : m_valBegin(val) {}

  void assign(K const &keyBegin, K const &keyEnd, V const &val) {
    // INSERT YOUR SOLUTION HERE
    if (!(keyBegin < keyEnd)) {
      return;
    }
    // Instead of a naive solution, I'm iterating through available intervals
    // and assignig the value to the intervals that are within the range of
    // [keyBegin, keyEnd)

    // m_map is organized as a stack. Each element indicating the start of new
    // interval
    auto it = m_map.lower_bound(keyBegin);

    V last_val = m_valBegin;

    auto before_start_it = m_map.upper_bound(keyBegin);
    // Check if before_start_it is not the first element
    if (before_start_it != m_map.begin()) {
      before_start_it--;
      last_val = before_start_it->second;
    }
    // We also need to erase all keys that are within the range of [keyBegin,
    // keyEnd)
    while (it != m_map.end() && it->first < keyEnd) {
      auto next = std::next(it);
      // If this is the start of new interval, we need to keep track of this so
      // that after the interval end we can assssing this
      last_val = it->second;
      m_map.erase(it);
      it = next;
    }
    m_map[keyBegin] = val;
    // Check if the end of interval collide
    it = m_map.lower_bound(keyEnd);
    if (keyEnd < it->first || it == m_map.end()) {
      m_map[keyEnd] = last_val;
    }
  }
  // look-up of the value associated with key
  V const &operator[](K const &key) const {
    auto it = m_map.upper_bound(key);
    if (it == m_map.begin()) {
      return m_valBegin;
    } else {
      return (--it)->second;
    }
  }
};

void IntervalMapTest() {
  interval_map<CustomKey, char> imap('A'); // initialize with default value 'A'

  // Assign intervals and test
  imap.assign(CustomKey(1), CustomKey(5), 'B');
  imap.assign(CustomKey(10), CustomKey(20), 'C');
  imap.assign(CustomKey(15), CustomKey(25), 'D');

  // Test values within the intervals
  assert(imap[CustomKey(0)] == 'A'); // Default value
  assert(imap[CustomKey(1)] == 'B'); // Interval [1, 5)
  assert(imap[CustomKey(2)] == 'B');
  assert(imap[CustomKey(4)] == 'B');
  assert(imap[CustomKey(5)] ==
         'A'); // Default value (5 is not included in the interval [1, 5))

  assert(imap[CustomKey(10)] == 'C'); // Interval [10, 20)
  assert(imap[CustomKey(15)] == 'D'); // Interval [15, 25)
  assert(imap[CustomKey(19)] == 'D');
  assert(imap[CustomKey(24)] == 'D');
  assert(imap[CustomKey(25)] ==
         'A'); // Default value (25 is not included in the interval [15, 25))

  // Test overlapping intervals
  imap.assign(CustomKey(3), CustomKey(8), 'E');
  assert(imap[CustomKey(2)] == 'B');
  assert(imap[CustomKey(3)] == 'E'); // Interval [3, 8)
  assert(imap[CustomKey(7)] == 'E');
  assert(imap[CustomKey(8)] ==
         'A'); // Default value (8 is not included in the interval [3, 8))

  // Additional Tests

  // Non-overlapping intervals
  imap.assign(CustomKey(30), CustomKey(35), 'F');
  assert(imap[CustomKey(29)] == 'A'); // Default value
  assert(imap[CustomKey(30)] == 'F'); // Interval [30, 35)
  assert(imap[CustomKey(34)] == 'F');
  assert(imap[CustomKey(35)] ==
         'A'); // Default value (35 is not included in the interval [30, 35))

  // Single element intervals
  imap.assign(CustomKey(40), CustomKey(41), 'G');
  assert(imap[CustomKey(39)] == 'A'); // Default value
  assert(imap[CustomKey(40)] == 'G'); // Interval [40, 41)
  assert(imap[CustomKey(41)] ==
         'A'); // Default value (41 is not included in the interval [40, 41))

  // Assigning the same value over existing intervals
  imap.assign(CustomKey(15), CustomKey(25), 'D'); // Already 'D' in this range
  assert(imap[CustomKey(15)] == 'D'); // Interval [15, 25) remains 'D'
  assert(imap[CustomKey(24)] == 'D');

  // Completely overlapping intervals
  imap.assign(CustomKey(5), CustomKey(30), 'H');
  assert(imap[CustomKey(4)] == 'E');
  assert(imap[CustomKey(5)] == 'H'); // Interval [5, 30)
  assert(imap[CustomKey(10)] == 'H');
  assert(imap[CustomKey(20)] == 'H');
  assert(imap[CustomKey(29)] == 'H');
  assert(imap[CustomKey(30)] == 'F'); // Still part of previous interval

  // Intervals that start before and end after existing intervals
  imap.assign(CustomKey(2), CustomKey(32), 'I');
  assert(imap[CustomKey(2)] == 'I'); // Interval [2, 32)
  assert(imap[CustomKey(15)] == 'I');
  assert(imap[CustomKey(31)] == 'I');
  assert(imap[CustomKey(32)] == 'F'); // Default value

  // Intervals that do not change the map
  imap.assign(CustomKey(32), CustomKey(32), 'J'); // Empty interval
  assert(imap[CustomKey(31)] == 'I');             // No change
  assert(imap[CustomKey(32)] == 'F');             // Default value

  std::cout << "All tests passed!" << std::endl;
}

int main() {
  IntervalMapTest();
  return 0;
}
