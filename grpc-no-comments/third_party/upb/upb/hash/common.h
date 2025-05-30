
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_HASH_COMMON_H_
#define UPB_HASH_COMMON_H_

#include <stdint.h>
#include <string.h>

#include "upb/base/string_view.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint64_t val;
} upb_value;

#define FUNCS(name, membername, type_t, converter)                   \
  UPB_INLINE void upb_value_set##name(upb_value* val, type_t cval) { \
    val->val = (uint64_t)cval;                                       \
  }                                                                  \
  UPB_INLINE upb_value upb_value_##name(type_t val) {                \
    upb_value ret;                                                   \
    upb_value_set##name(&ret, val);                                  \
    return ret;                                                      \
  }                                                                  \
  UPB_INLINE type_t upb_value_get##name(upb_value val) {             \
    return (type_t)(converter)val.val;                               \
  }

FUNCS(int32, int32, int32_t, int32_t)
FUNCS(int64, int64, int64_t, int64_t)
FUNCS(uint32, uint32, uint32_t, uint32_t)
FUNCS(uint64, uint64, uint64_t, uint64_t)
FUNCS(bool, _bool, bool, bool)
FUNCS(cstr, cstr, char*, uintptr_t)
FUNCS(uintptr, uptr, uintptr_t, uintptr_t)
FUNCS(ptr, ptr, void*, uintptr_t)
FUNCS(constptr, constptr, const void*, uintptr_t)

#undef FUNCS

UPB_INLINE void upb_value_setfloat(upb_value* val, float cval) {
  memcpy(&val->val, &cval, sizeof(cval));
}

UPB_INLINE void upb_value_setdouble(upb_value* val, double cval) {
  memcpy(&val->val, &cval, sizeof(cval));
}

UPB_INLINE upb_value upb_value_float(float cval) {
  upb_value ret;
  upb_value_setfloat(&ret, cval);
  return ret;
}

UPB_INLINE upb_value upb_value_double(double cval) {
  upb_value ret;
  upb_value_setdouble(&ret, cval);
  return ret;
}

typedef struct {
  uint32_t size;
  const char data[];
} upb_SizePrefixString;

typedef union {
  uintptr_t num;
  const upb_SizePrefixString* str;
} upb_key;

UPB_INLINE upb_StringView upb_key_strview(upb_key key) {
  return upb_StringView_FromDataAndSize(key.str->data, key.str->size);
}

typedef struct _upb_tabent {
  upb_value val;
  upb_key key;

  const struct _upb_tabent* next;
} upb_tabent;

typedef struct {
  upb_tabent* entries;

  uint32_t count;

  uint32_t mask;
} upb_table;

UPB_INLINE size_t upb_table_size(const upb_table* t) { return t->mask + 1; }

UPB_INLINE upb_key upb_key_empty(void) {
  upb_key ret;
  memset(&ret, 0, sizeof(upb_key));
  return ret;
}

UPB_INLINE bool upb_tabent_isempty(const upb_tabent* e) {
  upb_key key = e->key;
  UPB_ASSERT(sizeof(key.num) == sizeof(key.str));
  uintptr_t val;
  memcpy(&val, &key, sizeof(val));
  // Note: for upb_inttables a tab_key is a true integer key value, but the

  return val == 0;
}

uint32_t _upb_Hash(const void* p, size_t n, uint64_t seed);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
