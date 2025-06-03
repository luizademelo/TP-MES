Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_WIRE_DECODE_H_
#define UPB_WIRE_DECODE_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/mem/arena.h"
#include "upb/message/message.h"
#include "upb/mini_table/extension_registry.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

// Decoding options bit flags
enum {
  // Create string aliases instead of copying when possible
  kUpb_DecodeOption_AliasString = 1,

  // Verify that all required fields are present in the message
  kUpb_DecodeOption_CheckRequired = 2,

  // Allow decoding messages even if their mini-tables are not linked
  kUpb_DecodeOption_ExperimentalAllowUnlinked = 4,

  // Always validate UTF-8 strings, even if not required by the proto definition
  kUpb_DecodeOption_AlwaysValidateUtf8 = 8,
};

// Creates a decode options value with the specified maximum recursion depth
// The depth is stored in the upper 16 bits of the returned uint32_t
UPB_INLINE uint32_t upb_DecodeOptions_MaxDepth(uint16_t depth) {
  return (uint32_t)depth << 16;
}

// Extracts the maximum recursion depth from decode options
// The depth is stored in the upper 16 bits of the options parameter
UPB_INLINE uint16_t upb_DecodeOptions_GetMaxDepth(uint32_t options) {
  return options >> 16;
}

// Returns the effective maximum depth considering implementation limits
uint16_t upb_DecodeOptions_GetEffectiveMaxDepth(uint32_t options);

// Adjusts the maximum depth in decode options to not exceed the specified limit
// Preserves all other option flags (lower 16 bits)
UPB_INLINE int upb_Decode_LimitDepth(uint32_t decode_options, uint32_t limit) {
  uint32_t max_depth = upb_DecodeOptions_GetMaxDepth(decode_options);
  if (max_depth > limit) max_depth = limit;
  return upb_DecodeOptions_MaxDepth(max_depth) | (decode_options & 0xffff);
}

// Status codes returned by the decoding functions
typedef enum {
  kUpb_DecodeStatus_Ok = 0,                  // Decoding succeeded
  kUpb_DecodeStatus_Malformed = 1,           // Input data was malformed
  kUpb_DecodeStatus_OutOfMemory = 2,         // Memory allocation failed
  kUpb_DecodeStatus_BadUtf8 = 3,             // Invalid UTF-8 encountered
  kUpb_DecodeStatus_MaxDepthExceeded = 4,    // Message nesting too deep
  kUpb_DecodeStatus_MissingRequired = 5,     // Required field was missing
  kUpb_DecodeStatus_UnlinkedSubMessage = 6,  // Sub-message type not linked
} upb_DecodeStatus;

// Main decoding function for protocol buffer messages
// buf: pointer to the serialized data
// size: size of the serialized data
// msg: pointer to the message structure to populate
// mt: mini-table describing the message layout
// extreg: extension registry for resolving extensions
// options: bitmask of decoding options (see enum above)
// arena: memory arena for allocations
// Returns: decoding status code
UPB_API upb_DecodeStatus upb_Decode(const char* buf, size_t size,
                                    upb_Message* msg, const upb_MiniTable* mt,
                                    const upb_ExtensionRegistry* extreg,
                                    int options, upb_Arena* arena);

// Decodes a length-prefixed protocol buffer message
// Similar to upb_Decode but handles length-prefixed wire format
// num_bytes_read: output parameter for bytes consumed
UPB_API upb_DecodeStatus upb_DecodeLengthPrefixed(
    const char* buf, size_t size, upb_Message* msg, size_t* num_bytes_read,
    const upb_MiniTable* mt, const upb_ExtensionRegistry* extreg, int options,
    upb_Arena* arena);

// Returns a human-readable string for a given decode status code
UPB_API const char* upb_DecodeStatus_String(upb_DecodeStatus status);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
```

The comments provide:
1. Explanation of the purpose of each function
2. Description of parameters and return values
3. Documentation of the bit flag options
4. Clarification of the status codes
5. Notes about implementation details where relevant
6. Context for the overall header file's purpose (protocol buffer decoding)

The comments are concise but comprehensive, helping future developers understand both the interface and the underlying concepts without being overly verbose.