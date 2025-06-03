Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#include <gtest/gtest.h>
#include "google/protobuf/test_messages_proto2.upb_minitable.h"
#include "upb/mini_table/field.h"
#include "upb/mini_table/message.h"
#include "upb/test/proto3_test.upb.h"

// Test case for verifying oneof field iteration in proto2 messages
TEST(MiniTableOneofTest, OneOfIteratorProto2) {
  // Define the expected field numbers for the oneof fields
  constexpr int oneof_first_field_number = 111;
  constexpr int oneof_test_field_number = 116;

  // Get the mini table for the proto2 test message
  const upb_MiniTable* google_protobuf_table =
      &protobuf_0test_0messages__proto2__TestAllTypesProto2_msg_init;
  
  // Find a specific field within the oneof by its field number
  const upb_MiniTableField* field =
      upb_MiniTable_FindFieldByNumber(google_protobuf_table, oneof_test_field_number);
  ASSERT_TRUE(field != nullptr);  // Verify the field exists
  
  // Get the first field in the oneof that contains the found field
  const upb_MiniTableField* ptr = upb_MiniTable_GetOneof(google_protobuf_table, field);
  
  // Iterate through all fields in the oneof and verify their field numbers
  int field_num = oneof_first_field_number;
  do {
    EXPECT_EQ(upb_MiniTableField_Number(ptr), field_num++);
  } while (upb_MiniTable_NextOneofField(google_protobuf_table, &ptr));
}

// Test case for verifying behavior when the first field is part of a oneof
TEST(MiniTableOneofTest, InitialFieldOneOf) {
  // Get the mini table for the test message with oneof initial field
  const upb_MiniTable* table = &upb__test__TestOneOfInitialField_msg_init;
  
  // Find field number 1 (which is part of a oneof in this message)
  const upb_MiniTableField* field = upb_MiniTable_FindFieldByNumber(table, 1);
  ASSERT_TRUE(field != nullptr);  // Verify the field exists
  
  // Verify that when we get the oneof for this field, we get back the same field
  // (since it's the first/only field in the oneof)
  const upb_MiniTableField* ptr = upb_MiniTable_GetOneof(table, field);
  EXPECT_TRUE(ptr == field);
}

// Test case for verifying behavior when the first field is not part of a oneof
TEST(MiniTableOneofTest, InitialFieldNotOneOf) {
  constexpr int test_field_number = 1;
  
  // Get the mini table for the proto2 test message
  const upb_MiniTable* google_protobuf_table =
      &protobuf_0test_0messages__proto2__TestAllTypesProto2_msg_init;
  
  // Find field number 1 (which is not part of a oneof in this message)
  const upb_MiniTableField* field =
      upb_MiniTable_FindFieldByNumber(google_protobuf_table, test_field_number);
  ASSERT_TRUE(field != nullptr);  // Verify the field exists
  
  // Verify that when we try to get the oneof for this field, we get nullptr
  // (since it's not part of a oneof)
  const upb_MiniTableField* first_field =
      upb_MiniTable_GetOneof(google_protobuf_table, field);
  EXPECT_EQ(first_field, nullptr);
}
```

The comments explain:
1. The purpose of each test case
2. The significance of the constants and variables used
3. The expected behavior of each operation
4. The assertions being made in each test
5. The flow of operations within each test case

The comments are designed to help future developers understand:
- What each test is verifying
- Why certain operations are performed
- What the expected outcomes should be
- The context of the test cases within the broader codebase