
// Copyright 2015 gRPC authors.

#include "src/core/util/string.h"

#include <ctype.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "absl/strings/str_cat.h"
#include "absl/time/time.h"
#include "src/core/util/crash.h"
#include "src/core/util/useful.h"

char* gpr_strdup(const char* src) {
  char* dst;
  size_t len;

  if (!src) {
    return nullptr;
  }

  len = strlen(src) + 1;
  dst = static_cast<char*>(gpr_malloc(len));

  memcpy(dst, src, len);

  return dst;
}

std::string gpr_format_timespec(gpr_timespec tm) {
  const std::string time_str =
      absl::FormatTime("%Y-%m-%d%ET%H:%M:%S", absl::FromUnixSeconds(tm.tv_sec),
                       absl::LocalTimeZone());

  char ns_buffer[11];
  snprintf(ns_buffer, 11, ".%09d", tm.tv_nsec);
  for (int i = 7; i >= 1; i -= 3) {
    if (ns_buffer[i] == '0' && ns_buffer[i + 1] == '0' &&
        ns_buffer[i + 2] == '0') {
      ns_buffer[i] = '\0';

      if (i == 1) {
        ns_buffer[0] = '\0';
      }
    } else {
      break;
    }
  }
  return absl::StrCat(time_str, ns_buffer, "Z");
}

struct dump_out {
  size_t capacity;
  size_t length;
  char* data;
};

static dump_out dump_out_create(void) {
  dump_out r = {0, 0, nullptr};
  return r;
}

static void dump_out_append(dump_out* out, char c) {
  if (out->length == out->capacity) {
    out->capacity = std::max(size_t{8}, 2 * out->capacity);
    out->data = static_cast<char*>(gpr_realloc(out->data, out->capacity));
  }
  out->data[out->length++] = c;
}

static void hexdump(dump_out* out, const char* buf, size_t len) {
  static const char* hex = "0123456789abcdef";

  const uint8_t* const beg = reinterpret_cast<const uint8_t*>(buf);
  const uint8_t* const end = beg + len;
  const uint8_t* cur;

  for (cur = beg; cur != end; ++cur) {
    if (cur != beg) dump_out_append(out, ' ');
    dump_out_append(out, hex[*cur >> 4]);
    dump_out_append(out, hex[*cur & 0xf]);
  }
}

static void asciidump(dump_out* out, const char* buf, size_t len) {
  const uint8_t* const beg = reinterpret_cast<const uint8_t*>(buf);
  const uint8_t* const end = beg + len;
  const uint8_t* cur;
  int out_was_empty = (out->length == 0);
  if (!out_was_empty) {
    dump_out_append(out, ' ');
    dump_out_append(out, '\'');
  }
  for (cur = beg; cur != end; ++cur) {
    dump_out_append(
        out, (isprint(*cur) ? *reinterpret_cast<const char*>(cur) : '.'));
  }
  if (!out_was_empty) {
    dump_out_append(out, '\'');
  }
}

char* gpr_dump_return_len(const char* buf, size_t len, uint32_t flags,
                          size_t* out_len) {
  dump_out out = dump_out_create();
  if (flags & GPR_DUMP_HEX) {
    hexdump(&out, buf, len);
  }
  if (flags & GPR_DUMP_ASCII) {
    asciidump(&out, buf, len);
  }
  dump_out_append(&out, 0);
  *out_len = out.length;
  return out.data;
}

char* gpr_dump(const char* buf, size_t len, uint32_t flags) {
  size_t unused;
  return gpr_dump_return_len(buf, len, flags, &unused);
}

int gpr_parse_bytes_to_uint32(const char* buf, size_t len, uint32_t* result) {
  uint32_t out = 0;
  uint32_t new_val;
  size_t i;

  if (len == 0) return 0;

  for (i = 0; i < len; i++) {
    if (buf[i] < '0' || buf[i] > '9') return 0;
    new_val = 10 * out + static_cast<uint32_t>(buf[i] - '0');
    if (new_val < out) return 0;
    out = new_val;
  }

  *result = out;
  return 1;
}

void gpr_reverse_bytes(char* str, int len) {
  char *p1, *p2;
  for (p1 = str, p2 = str + len - 1; p2 > p1; ++p1, --p2) {
    char temp = *p1;
    *p1 = *p2;
    *p2 = temp;
  }
}

int gpr_ltoa(long value, char* output) {
  long sign;
  int i = 0;

  if (value == 0) {
    output[0] = '0';
    output[1] = 0;
    return 1;
  }

  sign = value < 0 ? -1 : 1;
  while (value) {
    output[i++] = static_cast<char>('0' + (sign * (value % 10)));
    value /= 10;
  }
  if (sign < 0) output[i++] = '-';
  gpr_reverse_bytes(output, i);
  output[i] = 0;
  return i;
}

int int64_ttoa(int64_t value, char* output) {
  int64_t sign;
  int i = 0;

  if (value == 0) {
    output[0] = '0';
    output[1] = 0;
    return 1;
  }

  sign = value < 0 ? -1 : 1;
  while (value) {
    output[i++] = static_cast<char>('0' + (sign * (value % 10)));
    value /= 10;
  }
  if (sign < 0) output[i++] = '-';
  gpr_reverse_bytes(output, i);
  output[i] = 0;
  return i;
}

int gpr_parse_nonnegative_int(const char* value) {
  char* end;
  long result = strtol(value, &end, 10);
  if (*end != '\0' || result < 0 || result > INT_MAX) return -1;
  return static_cast<int>(result);
}

char* gpr_leftpad(const char* str, char flag, size_t length) {
  const size_t str_length = strlen(str);
  const size_t out_length = str_length > length ? str_length : length;
  char* out = static_cast<char*>(gpr_malloc(out_length + 1));
  memset(out, flag, out_length - str_length);
  memcpy(out + out_length - str_length, str, str_length);
  out[out_length] = 0;
  return out;
}

char* gpr_strjoin(const char** strs, size_t nstrs, size_t* final_length) {
  return gpr_strjoin_sep(strs, nstrs, "", final_length);
}

char* gpr_strjoin_sep(const char** strs, size_t nstrs, const char* sep,
                      size_t* final_length) {
  const size_t sep_len = strlen(sep);
  size_t out_length = 0;
  size_t i;
  char* out;
  for (i = 0; i < nstrs; i++) {
    out_length += strlen(strs[i]);
  }
  out_length += 1;
  if (nstrs > 0) {
    out_length += sep_len * (nstrs - 1);
  }
  out = static_cast<char*>(gpr_malloc(out_length));
  out_length = 0;
  for (i = 0; i < nstrs; i++) {
    const size_t slen = strlen(strs[i]);
    if (i != 0) {
      memcpy(out + out_length, sep, sep_len);
      out_length += sep_len;
    }
    memcpy(out + out_length, strs[i], slen);
    out_length += slen;
  }
  out[out_length] = 0;
  if (final_length != nullptr) {
    *final_length = out_length;
  }
  return out;
}

int gpr_strincmp(const char* a, const char* b, size_t n) {
  int ca, cb;
  do {
    ca = tolower(*a);
    cb = tolower(*b);
    ++a;
    ++b;
    --n;
  } while (ca == cb && ca != 0 && cb != 0 && n != 0);
  return ca - cb;
}

int gpr_stricmp(const char* a, const char* b) {
  return gpr_strincmp(a, b, SIZE_MAX);
}

static void add_string_to_split(const char* beg, const char* end, char*** strs,
                                size_t* nstrs, size_t* capstrs) {
  char* out =
      static_cast<char*>(gpr_malloc(static_cast<size_t>(end - beg) + 1));
  memcpy(out, beg, static_cast<size_t>(end - beg));
  out[end - beg] = 0;
  if (*nstrs == *capstrs) {
    *capstrs = std::max(size_t{8}, 2 * *capstrs);
    *strs = static_cast<char**>(gpr_realloc(*strs, sizeof(*strs) * *capstrs));
  }
  (*strs)[*nstrs] = out;
  ++*nstrs;
}

void gpr_string_split(const char* input, const char* sep, char*** strs,
                      size_t* nstrs) {
  const char* next;
  *strs = nullptr;
  *nstrs = 0;
  size_t capstrs = 0;
  while ((next = strstr(input, sep))) {
    add_string_to_split(input, next, strs, nstrs, &capstrs);
    input = next + strlen(sep);
  }
  add_string_to_split(input, input + strlen(input), strs, nstrs, &capstrs);
}

void* gpr_memrchr(const void* s, int c, size_t n) {
  if (s == nullptr) return nullptr;
  char* b = const_cast<char*>(reinterpret_cast<const char*>(s));
  size_t i;
  for (i = 0; i < n; i++) {
    if (b[n - i - 1] == c) {
      return &b[n - i - 1];
    }
  }
  return nullptr;
}

bool gpr_parse_bool_value(const char* value, bool* dst) {
  const char* kTrue[] = {"1", "t", "true", "y", "yes"};
  const char* kFalse[] = {"0", "f", "false", "n", "no"};
  static_assert(sizeof(kTrue) == sizeof(kFalse), "true_false_equal");

  if (value == nullptr) {
    return false;
  }
  for (size_t i = 0; i < GPR_ARRAY_SIZE(kTrue); ++i) {
    if (gpr_stricmp(value, kTrue[i]) == 0) {
      *dst = true;
      return true;
    } else if (gpr_stricmp(value, kFalse[i]) == 0) {
      *dst = false;
      return true;
    }
  }
  return false;
}
