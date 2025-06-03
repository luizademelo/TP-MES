Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this header file
#ifndef UPB_WIRE_TYPES_H_
#define UPB_WIRE_TYPES_H_

/**
 * @enum upb_WireType
 * @brief Enumeration of Protocol Buffers wire types.
 *
 * These types represent the different encoding formats used in Protocol Buffers
 * wire format. Each field in a .proto file has a corresponding wire type that
 * determines how it is encoded on the wire.
 *
 * The values correspond to the Protocol Buffers wire types as follows:
 *   - kUpb_WireType_Varint: For int32, int64, uint32, uint64, sint32, sint64,
 *                           bool, enum (encoded as variable-length integers)
 *   - kUpb_WireType_64Bit: For fixed64, sfixed64, double (64-bit fixed length)
 *   - kUpb_WireType_Delimited: For string, bytes, embedded messages, packed
 *                              repeated fields (length-delimited)
 *   - kUpb_WireType_StartGroup: For groups (start group tag, deprecated)
 *   - kUpb_WireType_EndGroup: For groups (end group tag, deprecated)
 *   - kUpb_WireType_32Bit: For fixed32, sfixed32, float (32-bit fixed length)
 */
typedef enum {
  kUpb_WireType_Varint = 0,    // Variable-length integer encoding
  kUpb_WireType_64Bit = 1,     // 64-bit fixed-length encoding
  kUpb_WireType_Delimited = 2, // Length-delimited encoding
  kUpb_WireType_StartGroup = 3,// Start group tag (deprecated)
  kUpb_WireType_EndGroup = 4,  // End group tag (deprecated)
  kUpb_WireType_32Bit = 5      // 32-bit fixed-length encoding
} upb_WireType;

#endif // UPB_WIRE_TYPES_H_
```

The comments provide:
1. Explanation of the header guard purpose
2. Detailed documentation for the enum including:
   - Its purpose in Protocol Buffers
   - What each wire type represents
   - How each type maps to Protocol Buffer field types
3. Individual comments for each enum value
4. Proper closing comment for the header guard