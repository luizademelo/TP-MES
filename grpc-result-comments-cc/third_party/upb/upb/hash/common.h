Here's the commented version of the code:

```c++
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

// A generic value container that stores values as 64-bit unsigned integers
typedef struct {
  uint64_t val;
} upb_value;

// Macro to generate type-specific functions for upb_value
// Creates setter, getter, and constructor functions for various types
// Parameters:
//   name: suffix for function names (e.g., "int32" creates upb_value_setint32)
//   membername: unused parameter (legacy?)
//   type_t: the C type being handled
//   converter: type to cast to/from uint64_t
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

// Generate functions for various primitive types
FUNCS(int32, int32, int32_t, int32_t)    // 32-bit signed integer functions
FUNCS(int64, int64, int64_t, int64_t)    // 64-bit signed integer functions
FUNCS(uint32, uint32, uint32_t, uint32_t) // 32-bit unsigned integer functions
FUNCS(uint64, uint64, uint64_t, uint64_t) // 64-bit unsigned integer functions
FUNCS(bool, _bool, bool, bool)           // Boolean functions
FUNCS(cstr, cstr, char*, uintptr_t)       // C-string functions
FUNCS(uintptr, uptr, uintptr_t, uintptr_t) // uintptr_t functions
FUNCS(ptr, ptr, void*, uintptr_t)         // void pointer functions
FUNCS(constptr, constptr, const void*, uintptr_t) // const void pointer functions

#undef FUNCS

// Special functions for floating point types that require memcpy due to different representations

// Sets a float value in upb_value (using memcpy for type safety)
UPB_INLINE void upb_value_setfloat(upb_value* val, float cval) {
  memcpy(&val->val, &cval, sizeof(cval));
}

// Sets a double value in upb_value (using memcpy for type safety)
UPB_INLINE void upb_value_setdouble(upb_value* val, double cval) {
  memcpy(&val->val, &cval, sizeof(cval));
}

// Creates a upb_value from a float
UPB_INLINE upb_value upb_value_float(float cval) {
  upb_value ret;
  upb_value_setfloat(&ret, cval);
  return ret;
}

// Creates a upb_value from a double
UPB_INLINE upb_value upb_value_double(double cval) {
  upb_value ret;
  upb_value_setdouble(&ret, cval);
  return ret;
}

// A string type that stores size-prefixed string data
typedef struct {
  uint32_t size;      // Length of the string
  const char data[];  // Flexible array member for string data
} upb_SizePrefixString;

// Union for table keys that can be either numeric or string pointers
typedef union {
  uintptr_t num;                     // Numeric key
  const upb_SizePrefixString* str;   // String key
} upb_key;

// Converts a upb_key to a upb_StringView
UPB_INLINE upb_StringView upb_key_strview(upb_key key) {
  return upb_StringView_FromDataAndSize(key.str->data, key.str->size);
}

// Hash table entry structure
typedef struct _upb_tabent {
  upb_value val;          // The stored value
  upb_key key;            // The key for this entry
  const struct _upb_tabent* next;  // Pointer to next entry in case of collisions
} upb_tabent;

// Hash table structure
typedef struct {
  upb_tabent* entries;  // Array of hash table entries
  uint32_t count;       // Number of active entries
  uint32_t mask;        // Bitmask for hash values (size-1)
} upb_table;

// Returns the size (capacity) of the hash table
UPB_INLINE size_t upb_table_size(const upb_table* t) { return t->mask + 1; }

// Creates an empty key
UPB_INLINE upb_key upb_key_empty(void) {
  upb_key ret;
  memset(&ret, 0, sizeof(upb_key));
  return ret;
}

// Checks if a hash table entry is empty
UPB_INLINE bool upb_tabent_isempty(const upb_tabent* e) {
  upb_key key = e->key;
  UPB_ASSERT(sizeof(key.num) == sizeof(key.str));
  uintptr_t val;
  memcpy(&val, &key, sizeof(val));
  // Note: for upb_inttables a tab_key is a true integer key value, but the
  // empty check remains the same (key == 0)
  return val == 0;
}

// Hash function declaration
// Parameters:
//   p: pointer to data to hash
//   n: size of data
//   seed: hash seed
// Returns: 32-bit hash value
uint32_t _upb_Hash(const void* p, size_t n, uint64_t seed);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_HASH_COMMON_H_
```