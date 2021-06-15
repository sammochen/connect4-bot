class TranspositionTable {
public:
  static const int NOT_EXIST = 255;
  static const size_t n = (1LL << 23) + 9;

  typedef uint32_t key_t;
  typedef uint8_t value_t;

  TranspositionTable() {
    reset();
  }

  void put(uint64_t key, uint8_t value) {
    keys[index(key)] = key;
    values[index(key)] = value;
  }

  key_t get(uint64_t key) const {
    if (keys[index(key)] == (key_t)key) {
      return values[index(key)];
    }
    return NOT_EXIST;
  }

  void reset() { // fill everything with 0, because 0 value means missing data
    memset(keys, 0, n * sizeof(key_t));
    memset(values, 0, n * sizeof(value_t));
  }

private:
  key_t keys[n];
  value_t values[n];

  key_t index(uint64_t key) const {
    return key % n;
  }
};
