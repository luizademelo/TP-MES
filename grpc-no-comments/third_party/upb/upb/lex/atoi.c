
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/lex/atoi.h"

#include "upb/port/def.inc"

const char* upb_BufToUint64(const char* ptr, const char* end, uint64_t* val) {
  uint64_t u64 = 0;
  while (ptr < end) {
    unsigned ch = *ptr - '0';
    if (ch >= 10) break;
    if (u64 > UINT64_MAX / 10 || u64 * 10 > UINT64_MAX - ch) {
      return NULL;
    }
    u64 *= 10;
    u64 += ch;
    ptr++;
  }

  *val = u64;
  return ptr;
}

const char* upb_BufToInt64(const char* ptr, const char* end, int64_t* val,
                           bool* is_neg) {
  bool neg = false;
  uint64_t u64;

  if (ptr != end && *ptr == '-') {
    ptr++;
    neg = true;
  }

  ptr = upb_BufToUint64(ptr, end, &u64);
  if (!ptr || u64 > (uint64_t)INT64_MAX + neg) {
    return NULL;
  }

  *val = neg ? -u64 : u64;
  if (is_neg) *is_neg = neg;
  return ptr;
}
