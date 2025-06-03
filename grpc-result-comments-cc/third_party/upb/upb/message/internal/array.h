Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_INTERNAL_ARRAY_H_
#define UPB_MESSAGE_INTERNAL_ARRAY_H_

#include <stdint.h>
#include <string.h>

#include "upb/mem/arena.h"

#include "upb/port/def.inc"

// Bitmask flags for array metadata:
#define _UPB_ARRAY_MASK_IMM 0x4  // Flag indicating array is immutable/frozen
#define _UPB_ARRAY_MASK_LG2 0x3  // Mask for element size (log2)
#define _UPB_ARRAY_MASK_ALL (_UPB_ARRAY_MASK_IMM | _UPB_ARRAY_MASK_LG2)  // Combined mask

#ifdef __cplusplus
extern "C" {
#endif

// Structure representing a dynamic array in upb (protobuf runtime)
struct upb_Array {
  // The data pointer with metadata stored in lower bits (using bitmask)
  uintptr_t UPB_ONLYBITS(data);

  // Current number of elements in the array
  size_t UPB_ONLYBITS(size);
  // Maximum capacity of the array before reallocation is needed
  size_t UPB_PRIVATE(capacity);
};

// Marks an array as immutable/frozen (preventing further modifications)
UPB_INLINE void UPB_PRIVATE(_upb_Array_ShallowFreeze)(struct upb_Array* arr) {
  arr->UPB_ONLYBITS(data) |= _UPB_ARRAY_MASK_IMM;
}

// Checks if an array is frozen/immutable
UPB_API_INLINE bool upb_Array_IsFrozen(const struct upb_Array* arr) {
  return (arr->UPB_ONLYBITS(data) & _UPB_ARRAY_MASK_IMM) != 0;
}

// Stores a pointer with metadata (element size) in the array's data field
UPB_INLINE void UPB_PRIVATE(_upb_Array_SetTaggedPtr)(struct upb_Array* array,
                                                   void* data, size_t lg2) {
  UPB_ASSERT(lg2 != 1);  // Element size cannot be 2^1 (2 bytes)
  UPB_ASSERT(lg2 <= 4);  // Maximum element size is 2^4 (16 bytes)
  const size_t bits = lg2 - (lg2 != 0);  // Encode size as 2 bits
  array->UPB_ONLYBITS(data) = (uintptr_t)data | bits;
}

// Retrieves the log2 of the element size from the array's metadata
UPB_INLINE size_t
UPB_PRIVATE(_upb_Array_ElemSizeLg2)(const struct upb_Array* array) {
  const size_t bits = array->UPB_ONLYBITS(data) & _UPB_ARRAY_MASK_LG2;
  const size_t lg2 = bits + (bits != 0);  // Decode size from 2 bits
  return lg2;
}

// Returns a const pointer to the array's data (with metadata bits cleared)
UPB_API_INLINE const void* upb_Array_DataPtr(const struct upb_Array* array) {
  UPB_PRIVATE(_upb_Array_ElemSizeLg2)(array);  // Validate element size
  return (void*)(array->UPB_ONLYBITS(data) & ~(uintptr_t)_UPB_ARRAY_MASK_ALL);
}

// Returns a mutable pointer to the array's data
UPB_API_INLINE void* upb_Array_MutableDataPtr(struct upb_Array* array) {
  return (void*)upb_Array_DataPtr(array);
}

// Creates a new array with the specified initial capacity and element size
UPB_INLINE struct upb_Array* UPB_PRIVATE(_upb_Array_New)(upb_Arena* arena,
                                                       size_t init_capacity,
                                                       int elem_size_lg2) {
  UPB_ASSERT(elem_size_lg2 != 1);  // Element size cannot be 2^1 (2 bytes)
  UPB_ASSERT(elem_size_lg2 <= 4);  // Maximum element size is 2^4 (16 bytes)
  
  // Calculate memory needed for array header and elements
  const size_t array_size =
      UPB_ALIGN_UP(sizeof(struct upb_Array), UPB_MALLOC_ALIGN);
  const size_t bytes = array_size + (init_capacity << elem_size_lg2);
  
  // Allocate memory from arena
  struct upb_Array* array = (struct upb_Array*)upb_Arena_Malloc(arena, bytes);
  if (!array) return NULL;
  
  // Initialize array metadata
  UPB_PRIVATE(_upb_Array_SetTaggedPtr)
  (array, UPB_PTR_AT(array, array_size, void), elem_size_lg2);
  array->UPB_ONLYBITS(size) = 0;
  array->UPB_PRIVATE(capacity) = init_capacity;
  return array;
}

// Reallocates the array to accommodate at least min_size elements
bool UPB_PRIVATE(_upb_Array_Realloc)(struct upb_Array* array, size_t min_size,
                                   upb_Arena* arena);

// Ensures the array has capacity for at least 'size' elements
UPB_API_INLINE bool upb_Array_Reserve(struct upb_Array* array, size_t size,
                                    upb_Arena* arena) {
  UPB_ASSERT(!upb_Array_IsFrozen(array));  // Can't reserve on frozen array
  if (array->UPB_PRIVATE(capacity) < size)
    return UPB_PRIVATE(_upb_Array_Realloc)(array, size, arena);
  return true;
}

// Resizes the array (uninitialized elements) to the specified size
UPB_INLINE bool UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
    struct upb_Array* array, size_t size, upb_Arena* arena) {
  UPB_ASSERT(!upb_Array_IsFrozen(array));  // Can't resize frozen array
  UPB_ASSERT(size <= array->UPB_ONLYBITS(size) ||
             arena);  // Must have arena to grow
  if (!upb_Array_Reserve(array, size, arena)) return false;
  array->UPB_ONLYBITS(size) = size;
  return true;
}

// Sets the value at index i in the array
UPB_INLINE void UPB_PRIVATE(_upb_Array_Set)(struct upb_Array* array, size_t i,
                                          const void* data,
                                          size_t elem_size) {
  UPB_ASSERT(!upb_Array_IsFrozen(array));  // Can't modify frozen array
  UPB_ASSERT(i < array->UPB_ONLYBITS(size));  // Index must be in bounds
  UPB_ASSERT(elem_size == 1U << UPB_PRIVATE(_upb_Array_ElemSizeLg2)(array));
  char* arr_data = (char*)upb_Array_MutableDataPtr(array);
  memcpy(arr_data + (i * elem_size), data, elem_size);
}

// Returns the current size (number of elements) of the array
UPB_API_INLINE size_t upb_Array_Size(const struct upb_Array* arr) {
  return arr->UPB_ONLYBITS(size);
}

#ifdef __cplusplus
}
#endif

#undef _UPB_ARRAY_MASK_IMM
#undef _UPB_ARRAY_MASK_LG2
#undef _UPB_ARRAY_MASK_ALL

#include "upb/port/undef.inc"

#endif
```

The comments explain:
1. The purpose of each macro and constant
2. The structure and fields of upb_Array
3. The functionality of each method
4. Important preconditions and invariants
5. The bit-packing scheme used for metadata
6. Memory management considerations
7. Safety checks and assertions

The comments are concise but provide enough context for future maintainers to understand the implementation details and usage patterns.