Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_ACCESSORS_SPLIT64_H_
#define UPB_MESSAGE_ACCESSORS_SPLIT64_H_

#include "upb/message/accessors.h"
#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

// Gets the upper 32 bits of a 64-bit integer field from a protobuf message.
// @param msg The message containing the field
// @param field The field descriptor
// @param default_value Default value to return if field is not present
// @return Upper 32 bits of the 64-bit value, or default_value if not present
UPB_API_INLINE uint32_t upb_Message_GetInt64Hi(const upb_Message* msg,
                                               const upb_MiniTableField* field,
                                               uint32_t default_value) {
  return (uint32_t)(upb_Message_GetInt64(msg, field, default_value) >> 32);
}

// Gets the lower 32 bits of a 64-bit integer field from a protobuf message.
// @param msg The message containing the field
// @param field The field descriptor
// @param default_value Default value to return if field is not present
// @return Lower 32 bits of the 64-bit value, or default_value if not present
UPB_API_INLINE uint32_t upb_Message_GetInt64Lo(const upb_Message* msg,
                                               const upb_MiniTableField* field,
                                               uint32_t default_value) {
  return (uint32_t)upb_Message_GetInt64(msg, field, default_value);
}

// Sets a 64-bit integer field in a protobuf message using split 32-bit values.
// @param msg The message to modify
// @param field The field descriptor
// @param hi Upper 32 bits of the value
// @param lo Lower 32 bits of the value
// @param arena Memory arena for allocation
// @return True if successful, false otherwise
UPB_API_INLINE bool upb_Message_SetInt64Split(upb_Message* msg,
                                              const upb_MiniTableField* field,
                                              uint32_t hi, uint32_t lo,
                                              upb_Arena* arena) {
  return upb_Message_SetInt64(msg, field, ((int64_t)hi << 32) | lo, arena);
}

// Gets the upper 32 bits of a 64-bit unsigned integer field from a protobuf message.
// @param msg The message containing the field
// @param field The field descriptor
// @param default_value Default value to return if field is not present
// @return Upper 32 bits of the 64-bit value, or default_value if not present
UPB_API_INLINE uint32_t upb_Message_GetUInt64Hi(const upb_Message* msg,
                                                const upb_MiniTableField* field,
                                                uint32_t default_value) {
  return (uint32_t)(upb_Message_GetUInt64(msg, field, default_value) >> 32);
}

// Gets the lower 32 bits of a 64-bit unsigned integer field from a protobuf message.
// @param msg The message containing the field
// @param field The field descriptor
// @param default_value Default value to return if field is not present
// @return Lower 32 bits of the 64-bit value, or default_value if not present
UPB_API_INLINE uint32_t upb_Message_GetUInt64Lo(const upb_Message* msg,
                                                const upb_MiniTableField* field,
                                                uint32_t default_value) {
  return (uint32_t)upb_Message_GetUInt64(msg, field, default_value);
}

// Sets a 64-bit unsigned integer field in a protobuf message using split 32-bit values.
// @param msg The message to modify
// @param field The field descriptor
// @param hi Upper 32 bits of the value
// @param lo Lower 32 bits of the value
// @param arena Memory arena for allocation
// @return True if successful, false otherwise
UPB_API_INLINE bool upb_Message_SetUInt64Split(upb_Message* msg,
                                               const upb_MiniTableField* field,
                                               uint32_t hi, uint32_t lo,
                                               upb_Arena* arena) {
  return upb_Message_SetUInt64(msg, field, ((uint64_t)hi << 32) | lo, arena);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_MESSAGE_ACCESSORS_SPLIT64_H_
```

The comments explain:
1. The purpose of each function
2. The parameters and their meanings
3. The return values and their meanings
4. The basic operation being performed
5. The relationship between the split 32-bit values and the underlying 64-bit value

The comments follow a consistent format and provide enough information for a developer to understand how to use these functions without needing to examine the implementation details.