Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_HASH_INT_TABLE_H_
#define UPB_HASH_INT_TABLE_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/hash/common.h"
#include "upb/mem/arena.h"

#include "upb/port/def.inc"

// Structure representing an integer-keyed hash table with array optimization
// Contains both a hash table and an array for efficient storage of dense keys
typedef struct {
  upb_table t;            // Base hash table structure

  const upb_value* array; // Array for storing values (used for dense keys)
  
  const uint8_t* presence_mask; // Bitmask tracking which array positions are occupied
  uint32_t array_size;    // Total allocated size of the array
  uint32_t array_count;   // Number of elements currently in the array
} upb_inttable;

#ifdef __cplusplus
extern "C" {
#endif

// Initializes a new integer table. Returns true on success, false on failure.
bool upb_inttable_init(upb_inttable* table, upb_Arena* a);

// Returns the number of elements in the table
size_t upb_inttable_count(const upb_inttable* t);

// Inserts a key-value pair into the table. Returns true on success.
// The arena is used for memory allocation if needed.
bool upb_inttable_insert(upb_inttable* t, uintptr_t key, upb_value val,
                         upb_Arena* a);

// Looks up a key in the table. Returns true if found, with value stored in *v.
bool upb_inttable_lookup(const upb_inttable* t, uintptr_t key, upb_value* v);

// Removes a key from the table. If val is non-NULL, stores the removed value.
// Returns true if the key was found and removed.
bool upb_inttable_remove(upb_inttable* t, uintptr_t key, upb_value* val);

// Replaces the value for an existing key. Returns true if the key existed.
bool upb_inttable_replace(upb_inttable* t, uintptr_t key, upb_value val);

// Compacts the table's memory usage. Returns true on success.
bool upb_inttable_compact(upb_inttable* t, upb_Arena* a);

// Removes all entries from the table
void upb_inttable_clear(upb_inttable* t);

// Special iterator constant representing the beginning of iteration
#define UPB_INTTABLE_BEGIN -1

// Advances to the next key-value pair in the table. Returns true if successful.
// The iterator is updated in *iter. Initialize *iter to UPB_INTTABLE_BEGIN.
bool upb_inttable_next(const upb_inttable* t, uintptr_t* key, upb_value* val,
                       intptr_t* iter);

// Removes the current iterator position from the table
void upb_inttable_removeiter(upb_inttable* t, intptr_t* iter);

// Sets the value at the current iterator position
void upb_inttable_setentryvalue(upb_inttable* t, intptr_t iter, upb_value v);

// Returns true if iteration has completed (no more elements)
bool upb_inttable_done(const upb_inttable* t, intptr_t i);

// Returns the key at the current iterator position
uintptr_t upb_inttable_iter_key(const upb_inttable* t, intptr_t iter);

// Returns the value at the current iterator position
upb_value upb_inttable_iter_value(const upb_inttable* t, intptr_t iter);

// Checks if a key exists in the array portion of the table (inline function)
UPB_INLINE bool upb_inttable_arrhas(const upb_inttable* t, uintptr_t key) {
  return (t->presence_mask[key / 8] & (1 << (key % 8))) != 0;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_HASH_INT_TABLE_H_
```

The comments explain:
1. The overall purpose of the integer table (combining hash table and array storage)
2. The meaning of each struct field
3. The behavior and purpose of each function
4. The iterator functionality and constants
5. The bitmask checking for array presence
6. Memory management through arenas

The comments are concise but provide enough information for a developer to understand how to use and maintain the table implementation. They explain both what each component does and, where relevant, how it does it.