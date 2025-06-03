Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#include "src/core/telemetry/stats_data.h"

#include <grpc/support/port_platform.h>
#include <stdint.h>

namespace grpc_core {
namespace {
// Union to allow type-punning between double and uint64_t for bit manipulation
union DblUint {
  double dbl;
  uint64_t uint;
};
}  // namespace

// Collects histogram data from buckets and adds to result histogram
void HistogramCollector_16777216_20_64::Collect(
    Histogram_16777216_20_64* result) const {
  for (int i = 0; i < 20; i++) {
    result->buckets_[i] += buckets_[i].load(std::memory_order_relaxed);
  }
}

// Subtracts right histogram from left histogram and returns result
Histogram_16777216_20_64 operator-(const Histogram_16777216_20_64& left,
                                   const Histogram_16777216_20_64& right) {
  Histogram_16777216_20_64 result;
  for (int i = 0; i < 20; i++) {
    result.buckets_[i] = left.buckets_[i] - right.buckets_[i];
  }
  return result;
}

// Similar collection methods for different histogram configurations
void HistogramCollector_100000_20_64::Collect(
    Histogram_100000_20_64* result) const {
  for (int i = 0; i < 20; i++) {
    result->buckets_[i] += buckets_[i].load(std::memory_order_relaxed);
  }
}

Histogram_100000_20_64 operator-(const Histogram_100000_20_64& left,
                                 const Histogram_100000_20_64& right) {
  Histogram_100000_20_64 result;
  for (int i = 0; i < 20; i++) {
    result.buckets_[i] = left.buckets_[i] - right.buckets_[i];
  }
  return result;
}

void HistogramCollector_10000_20_64::Collect(
    Histogram_10000_20_64* result) const {
  for (int i = 0; i < 20; i++) {
    result->buckets_[i] += buckets_[i].load(std::memory_order_relaxed);
  }
}

Histogram_10000_20_64 operator-(const Histogram_10000_20_64& left,
                                const Histogram_10000_20_64& right) {
  Histogram_10000_20_64 result;
  for (int i = 0; i < 20; i++) {
    result.buckets_[i] = left.buckets_[i] - right.buckets_[i];
  }
  return result;
}

void HistogramCollector_65536_26_64::Collect(
    Histogram_65536_26_64* result) const {
  for (int i = 0; i < 26; i++) {
    result->buckets_[i] += buckets_[i].load(std::memory_order_relaxed);
  }
}

Histogram_65536_26_64 operator-(const Histogram_65536_26_64& left,
                                const Histogram_65536_26_64& right) {
  Histogram_65536_26_64 result;
  for (int i = 0; i < 26; i++) {
    result.buckets_[i] = left.buckets_[i] - right.buckets_[i];
  }
  return result;
}

void HistogramCollector_100_20_64::Collect(Histogram_100_20_64* result) const {
  for (int i = 0; i < 20; i++) {
    result->buckets_[i] += buckets_[i].load(std::memory_order_relaxed);
  }
}

Histogram_100_20_64 operator-(const Histogram_100_20_64& left,
                              const Histogram_100_20_64& right) {
  Histogram_100_20_64 result;
  for (int i = 0; i < 20; i++) {
    result.buckets_[i] = left.buckets_[i] - right.buckets_[i];
  }
  return result;
}

void HistogramCollector_16777216_50_64::Collect(
    Histogram_16777216_50_64* result) const {
  for (int i = 0; i < 50; i++) {
    result->buckets_[i] += buckets_[i].load(std::memory_order_relaxed);
  }
}

Histogram_16777216_50_64 operator-(const Histogram_16777216_50_64& left,
                                   const Histogram_16777216_50_64& right) {
  Histogram_16777216_50_64 result;
  for (int i = 0; i < 50; i++) {
    result.buckets_[i] = left.buckets_[i] - right.buckets_[i];
  }
  return result;
}

void HistogramCollector_80_10_64::Collect(Histogram_80_10_64* result) const {
  for (int i = 0; i < 10; i++) {
    result->buckets_[i] += buckets_[i].load(std::memory_order_relaxed);
  }
}

Histogram_80_10_64 operator-(const Histogram_80_10_64& left,
                             const Histogram_80_10_64& right) {
  Histogram_80_10_64 result;
  for (int i = 0; i < 10; i++) {
    result.buckets_[i] = left.buckets_[i] - right.buckets_[i];
  }
  return result;
}

void HistogramCollector_1800000_40_64::Collect(
    Histogram_1800000_40_64* result) const {
  for (int i = 0; i < 40; i++) {
    result->buckets_[i] += buckets_[i].load(std::memory_order_relaxed);
  }
}

Histogram_1800000_40_64 operator-(const Histogram_1800000_40_64& left,
                                  const Histogram_1800000_40_64& right) {
  Histogram_1800000_40_64 result;
  for (int i = 0; i < 40; i++) {
    result.buckets_[i] = left.buckets_[i] - right.buckets_[i];
  }
  return result;
}

namespace {
// Precomputed tables for histogram bucket boundaries and mappings
const int kStatsTable0[21] = {
    0,     1,      3,      8,       19,      45,      106,
    250,   588,    1383,   3252,    7646,    17976,   42262,
    99359, 233593, 549177, 1291113, 3035402, 7136218, 16777216};
const uint8_t kStatsTable1[23] = {2,  3,  3,  4,  5,  6,  7,  8,
                                  8,  9,  10, 11, 12, 12, 13, 14,
                                  15, 16, 16, 17, 18, 19, 20};
const int kStatsTable2[21] = {0,    1,    2,    4,     8,     15,    27,
                              49,   89,   160,  288,   517,   928,   1666,
                              2991, 5369, 9637, 17297, 31045, 55719, 100000};
const uint8_t kStatsTable3[30] = {3,  3,  4,  4,  5,  6,  6,  7,  7,  8,
                                  9,  9,  10, 10, 11, 11, 12, 13, 13, 14,
                                  15, 15, 16, 16, 17, 17, 18, 19, 19, 20};
const int kStatsTable4[21] = {0,   1,    2,    4,    7,    12,   19,
                              30,  47,   74,   116,  182,  285,  445,
                              695, 1084, 1691, 2637, 4113, 6414, 10000};
const uint8_t kStatsTable5[23] = {3,  3,  4,  5,  5,  6,  7,  8,
                                  9,  9,  10, 11, 12, 12, 13, 14,
                                  15, 15, 16, 17, 18, 18, 19};
const int kStatsTable6[27] = {0,    1,     2,     4,     7,     11,   17,
                              26,   40,    61,    92,    139,   210,  317,
                              478,  721,   1087,  1638,  2468,  3719, 5604,
                              8443, 12721, 19166, 28875, 43502, 65536};
const uint8_t kStatsTable7[29] = {3,  3,  4,  5,  6,  6,  7,  8,  9,  10,
                                  11, 11, 12, 13, 14, 15, 16, 16, 17, 18,
                                  19, 20, 21, 21, 22, 23, 24, 25, 26};
const int kStatsTable8[9] = {0,     1,      11,      119,     1275,
                             13656, 146259, 1566467, 16777216};
const uint8_t kStatsTable9[11] = {2, 2, 3, 4, 4, 5, 5, 6, 6, 7, 8};
const int kStatsTable10[21] = {0,  1,  2,  3,  4,  5,  7,  9,  11, 14, 17,
                               21, 25, 30, 36, 43, 51, 61, 72, 85, 100};
const uint8_t kStatsTable11[16] = {6,  6,  7,  8,  9,  9,  10, 11,
                                   12, 13, 14, 15, 16, 17, 18, 19};
const int kStatsTable12[51] = {
    0,       1,        2,       3,       5,       7,       10,      14,
    20,      28,       39,      54,      75,      104,     144,     200,
    277,     383,      530,     733,     1014,    1402,    1939,    2681,
    3706,    5123,     7082,    9790,    13533,   18707,   25859,   35746,
    49412,   68303,    94416,   130512,  180408,  249380,  344720,  476509,
    658682,  910501,   1258592, 1739760, 2404882, 3324285, 4595181, 6351949,
    8780340, 12137120, 16777216};
const uint8_t kStatsTable13[88] = {
    4,  4,  5,  5,  6,  6,  7,  7,  8,  8,  9,  9,  10, 11, 11, 12, 12, 13,
    13, 14, 14, 15, 15, 16, 16, 17, 18, 18, 18, 19, 20, 20, 21, 21, 22, 22,
    23, 23, 24, 24, 25, 25, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32,
    32, 33, 33, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 42,
    42, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 48, 49, 50, 50};
const int kStatsTable14[11] = {0, 1, 2, 4, 7, 11, 17, 26, 38, 56, 80};
const uint8_t kStatsTable15[9] = {3, 3, 4, 5, 6, 6, 7, 8, 9};
const int kStatsTable16[41] = {
    0,      1,      2,      3,       5,      8,      12,     18,     26,
    37,     53,     76,     108,     153,    217,    308,    436,    617,
    873,    1235,   1748,   2473,    3499,   4950,   7003,   9907,   14015,
    19825,  28044,  39670,  56116,   79379,  112286, 158835, 224680, 317821,
    449574, 635945, 899575, 1272492, 1800000};
const uint8_t kStatsTable17[37] = {
    4,  5,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
    22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
}  // namespace

// Determines the appropriate bucket for a given value in 16777216_20_64 histogram
int Histogram_16777216_20_64::BucketFor(int value) {
  if (value < 2) {
    if (value < 0) {
      return 0;
    } else {
      return value;
    }
  } else {
    if (value < 8388609) {
      DblUint val;
      val.dbl = value;
      // Use bit manipulation and lookup tables to determine bucket
      const int bucket =
          kStatsTable1[((val.uint - 4611686018427387904ull) >> 52)];
      return bucket - (value < kStatsTable0[bucket]);
    } else {
      return 19;
    }
  }
}

// Similar bucket determination methods for different histogram configurations
int Histogram_100000_20_64::BucketFor(int value) {
  if (value < 3) {
    if (value < 0) {
      return 0;
    } else {
      return value;
    }
  } else {
    if (value < 65537) {
      DblUint val;
      val.dbl = value;
      const int bucket =
          kStatsTable3[((val.uint - 4613937818241073152ull) >> 51)];
      return bucket - (value < kStatsTable2[bucket]);
    } else {
      return 19;
    }
  }
}

int Histogram_10000_20_64::BucketFor(int value) {
  if (value < 3) {
    if (value < 0) {
      return 0;
    } else {
      return value;
    }
  } else {
    if (value < 6145) {
      DblUint val;
      val.dbl = value;
      const int bucket =
          kStatsTable5[((val.uint - 4613937818241073152ull) >> 51)];
      return bucket - (value < kStatsTable4[bucket]);
    } else {
      if (value < 6414) {
        return 18;
      } else {
        return 19;
      }
    }
  }
}

int Histogram_65536_26_64::BucketFor(int value) {
  if (value < 3) {
    if (value < 0) {
      return 0;
    } else {
      return value;
    }
  } else {
    if (value < 49153) {
      DblUint val;
      val.dbl = value;
      const int bucket =
          kStatsTable7[((val.uint - 4613937818241073152ull) >> 51)];
      return bucket - (value < kStatsTable6[bucket]);
    } else {
      return 25;
    }
  }
}

int Histogram_16777216_8_8::BucketFor(int value) {
  if (value < 2) {
    if (value < 0) {
      return 0;
    } else {
      return value;
    }
  } else {
    if (value < 2097153) {
      DblUint val;
      val.dbl = value;
      const int bucket =
          kStatsTable9[((val.uint - 4611686018427387904ull) >> 53)];
      return bucket - (value < kStatsTable8[bucket]);
    } else {
      return 7;
    }
  }
}

int Histogram_100_20_64::BucketFor(int value) {
  if (value < 6) {
    if (value < 0)