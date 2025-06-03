Here's the commented version of the code snippet:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this header file
#ifndef UPB_WIRE_INTERNAL_CONSTANTS_H_
#define UPB_WIRE_INTERNAL_CONSTANTS_H_

// Default maximum depth limit for nested message structures in the wire format.
// This helps prevent stack overflow from excessively deep recursion.
#define kUpb_WireFormat_DefaultDepthLimit 100

// Enum defining constants for Message Set wire format field numbers.
// Message Set is a historical wire format for protocol buffers.
enum {
  kUpb_MsgSet_Item = 1,     // Field number for Message Set item
  kUpb_MsgSet_TypeId = 2,    // Field number for type identifier in Message Set
  kUpb_MsgSet_Message = 3,   // Field number for actual message in Message Set
};

#endif  // UPB_WIRE_INTERNAL_CONSTANTS_H_
```

The comments explain:
1. The purpose of the header guard
2. The meaning and purpose of the depth limit constant
3. The significance of each enum value in the context of Message Set wire format
4. The closing comment for the header guard

The comments are concise yet informative, providing context about both the technical implementation and the conceptual purpose of each element.