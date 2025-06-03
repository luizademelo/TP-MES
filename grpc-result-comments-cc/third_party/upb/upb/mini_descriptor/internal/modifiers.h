Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this header file
#ifndef UPB_MINI_DESCRIPTOR_INTERNAL_MODIFIERS_H_
#define UPB_MINI_DESCRIPTOR_INTERNAL_MODIFIERS_H_

// Include platform-specific definitions
#include "upb/port/def.inc"

/**
 * Enumeration of field modifiers used in protocol buffers.
 * These bit flags represent various attributes/properties of protobuf fields.
 */
typedef enum {
  kUpb_FieldModifier_IsRepeated = 1 << 0,      // Field is repeated (array-like)
  kUpb_FieldModifier_IsPacked = 1 << 1,        // Repeated field uses packed encoding
  kUpb_FieldModifier_IsClosedEnum = 1 << 2,    // Enum field is closed (only defined values allowed)
  kUpb_FieldModifier_IsProto3Singular = 1 << 3,// Field is singular in proto3 syntax
  kUpb_FieldModifier_IsRequired = 1 << 4,      // Field is required (proto2 only)
  kUpb_FieldModifier_ValidateUtf8 = 1 << 5,    // Field requires UTF-8 validation
} kUpb_FieldModifier;

/**
 * Enumeration of message-level modifiers used in protocol buffers.
 * These bit flags represent various attributes/properties of protobuf messages.
 */
typedef enum {
  kUpb_MessageModifier_ValidateUtf8 = 1 << 0,  // Message requires UTF-8 validation
  kUpb_MessageModifier_DefaultIsPacked = 1 << 1, // Repeated fields are packed by default
  kUpb_MessageModifier_IsExtendable = 1 << 2,  // Message can be extended with extensions
} kUpb_MessageModifier;

// Undo platform-specific definitions
#include "upb/port/undef.inc"

#endif  // UPB_MINI_DESCRIPTOR_INTERNAL_MODIFIERS_H_
```

The comments I've added:
1. Explained the purpose of the header guard
2. Noted the inclusion of platform-specific definitions
3. Added detailed documentation for each enum and its values
4. Explained the purpose of each modifier flag
5. Noted the closing of platform-specific definitions
6. Added the matching endif comment for the header guard

The comments provide clear explanations of each enum value's purpose and the overall structure of the header file, which will help maintainers understand the code's functionality without needing to consult external documentation.