Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_INTERNAL_SUB_H_
#define UPB_MINI_TABLE_INTERNAL_SUB_H_

// Include platform-specific definitions
#include "upb/port/def.inc"

// Internal union type for storing either a submessage or subenum mini table
// This is an internal implementation detail and should not be used directly
typedef union {
  const struct upb_MiniTable* const* UPB_PRIVATE(submsg);  // Pointer to submessage mini table
  const struct upb_MiniTableEnum* UPB_PRIVATE(subenum);    // Pointer to enum mini table
} upb_MiniTableSubInternal;

// Public union type for storing either a submessage or subenum mini table
// This is the type that should be used in public APIs
union upb_MiniTableSub {
  const struct upb_MiniTable* UPB_PRIVATE(submsg);       // Pointer to submessage mini table
  const struct upb_MiniTableEnum* UPB_PRIVATE(subenum);  // Pointer to enum mini table
};

#ifdef __cplusplus
extern "C" {
#endif

// Creates a MiniTableSub union from an enum mini table
// @param subenum Pointer to the enum mini table
// @return MiniTableSub union containing the enum mini table
UPB_API_INLINE union upb_MiniTableSub upb_MiniTableSub_FromEnum(
    const struct upb_MiniTableEnum* subenum) {
  union upb_MiniTableSub out;
  out.UPB_PRIVATE(subenum) = subenum;
  return out;
}

// Creates a MiniTableSub union from a message mini table
// @param submsg Pointer to the message mini table
// @return MiniTableSub union containing the message mini table
UPB_API_INLINE union upb_MiniTableSub upb_MiniTableSub_FromMessage(
    const struct upb_MiniTable* submsg) {
  union upb_MiniTableSub out;
  out.UPB_PRIVATE(submsg) = submsg;
  return out;
}

// Extracts the enum mini table from a MiniTableSub union
// @param sub MiniTableSub union to extract from
// @return Pointer to the enum mini table (or NULL if not an enum)
UPB_API_INLINE const struct upb_MiniTableEnum* upb_MiniTableSub_Enum(
    const union upb_MiniTableSub sub) {
  return sub.UPB_PRIVATE(subenum);
}

// Extracts the message mini table from a MiniTableSub union
// @param sub MiniTableSub union to extract from
// @return Pointer to the message mini table (or NULL if not a message)
UPB_API_INLINE const struct upb_MiniTable* upb_MiniTableSub_Message(
    const union upb_MiniTableSub sub) {
  return sub.UPB_PRIVATE(submsg);
}

#ifdef __cplusplus
}
#endif

// Undefine platform-specific definitions
#include "upb/port/undef.inc"

#endif  // UPB_MINI_TABLE_INTERNAL_SUB_H_
```

The comments explain:
1. The purpose of each union type and the difference between them
2. The functionality of each API function
3. The parameters and return values for each function
4. The purpose of the include guards and platform-specific includes
5. The C linkage specification for C++ compatibility

The comments are written to help future developers understand:
- What the code does
- How to use the public API
- Implementation details they need to be aware of
- The distinction between public and internal types