Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Include necessary headers
#include "upb/mini_table/compat.h"  // UPB mini-table compatibility utilities
#include <gtest/gtest.h>  // Google Test framework
// Generated protocol buffer message descriptors:
#include "google/protobuf/test_messages_proto2.upb_minitable.h"
#include "google/protobuf/test_messages_proto3.upb_minitable.h"

namespace {

// Test case for verifying equality of Protocol Buffers v2 message descriptors
// using the UPB mini-table format.
TEST(GeneratedCode, EqualsTestProto2) {
  // Verify that a Protocol Buffers v2 message descriptor is equal to itself
  // using the upb_MiniTable_Equals function.
  EXPECT_TRUE(upb_MiniTable_Equals(
      &protobuf_0test_0messages__proto2__ProtoWithKeywords_msg_init,
      &protobuf_0test_0messages__proto2__ProtoWithKeywords_msg_init));
}

// Test case for verifying equality of Protocol Buffers v3 message descriptors
// using the UPB mini-table format.
TEST(GeneratedCode, EqualsTestProto3) {
  // Verify that a Protocol Buffers v3 message descriptor is equal to itself
  // using the upb_MiniTable_Equals function.
  EXPECT_TRUE(upb_MiniTable_Equals(
      &protobuf_0test_0messages__proto3__TestAllTypesProto3_msg_init,
      &protobuf_0test_0messages__proto3__TestAllTypesProto3_msg_init));
}

}  // namespace
```

Key comments added:
1. Explained the purpose of each include header
2. Added overview comments for each test case
3. Explained what each test is verifying
4. Clarified the use of upb_MiniTable_Equals function
5. Added namespace closing comment
6. Noted the Protocol Buffers version being tested in each case

The comments maintain a professional tone while providing clear explanations of both the high-level purpose and specific details of each code segment.