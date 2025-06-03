Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_COMPARE_H_
#define UPB_MESSAGE_COMPARE_H_

#include <stddef.h>

// Include necessary headers for upb (universal protobuf) functionality
#include "upb/base/descriptor_constants.h"
#include "upb/message/message.h"
#include "upb/message/value.h"
#include "upb/mini_table/extension.h"
#include "upb/mini_table/field.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

// Comparison options bit flags
enum {
  // When set, unknown fields will be included in comparison
  kUpb_CompareOption_IncludeUnknownFields = (1 << 0)
};

#ifdef __cplusplus
extern "C" {
#endif

// Checks if a protobuf message is empty (all fields have default values)
// @param msg: The message to check
// @param m: Mini table containing message layout information
// @return: True if message is empty, false otherwise
UPB_API bool upb_Message_IsEmpty(const upb_Message* msg,
                                 const upb_MiniTable* m);

// Compares two protobuf messages for equality
// @param msg1: First message to compare
// @param msg2: Second message to compare
// @param m: Mini table containing message layout information
// @param options: Bitmask of comparison options (see enum above)
// @return: True if messages are equal, false otherwise
UPB_API bool upb_Message_IsEqual(const upb_Message* msg1,
                                 const upb_Message* msg2,
                                 const upb_MiniTable* m, int options);

// Compares two message values of a given type for equality
// @param val1: First value to compare
// @param val2: Second value to compare
// @param ctype: The C type of the values being compared
// @param m: Mini table for message types (used when comparing submessages)
// @param options: Comparison options (see enum above)
// @return: True if values are equal, false otherwise
UPB_API_INLINE bool upb_MessageValue_IsEqual(upb_MessageValue val1,
                                             upb_MessageValue val2,
                                             upb_CType ctype,
                                             const upb_MiniTable* m,
                                             int options) {
  switch (ctype) {
    case kUpb_CType_Bool:
      return val1.bool_val == val2.bool_val;

    case kUpb_CType_Float:
    case kUpb_CType_Int32:
    case kUpb_CType_UInt32:
    case kUpb_CType_Enum:
      // Compare 32-bit values (float, int32, uint32, enum)
      return val1.int32_val == val2.int32_val;

    case kUpb_CType_Double:
    case kUpb_CType_Int64:
    case kUpb_CType_UInt64:
      // Compare 64-bit values (double, int64, uint64)
      return val1.int64_val == val2.int64_val;

    case kUpb_CType_String:
    case kUpb_CType_Bytes:
      // Compare string/bytes using string view comparison
      return upb_StringView_IsEqual(val1.str_val, val2.str_val);

    case kUpb_CType_Message:
      // Recursively compare message types
      return upb_Message_IsEqual(val1.msg_val, val2.msg_val, m, options);

    default:
      // Should never be reached with valid input
      UPB_UNREACHABLE();
      return false;
  }
}

#ifdef __cplusplus
}  // extern "C"
#endif

#include "upb/port/undef.inc"

#endif  // UPB_MESSAGE_COMPARE_H_
```

Key improvements made:
1. Added detailed comments for each function explaining purpose, parameters, and return values
2. Added comments for the enum value explaining its purpose
3. Added section comments within the switch statement to group related cases
4. Added closing comments for #endif directives to show what they're closing
5. Added comment explaining the default case behavior
6. Maintained consistent comment style throughout
7. Added brief explanation of header includes

The comments now provide clear documentation for anyone who needs to use or maintain this header file, explaining both the high-level purpose and the detailed implementation choices.