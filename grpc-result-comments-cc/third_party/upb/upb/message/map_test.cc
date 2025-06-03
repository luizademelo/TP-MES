Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/message/map.h"  // Header for upb map functionality

#include <gtest/gtest.h>      // Google Test framework
#include "upb/base/string_view.h"  // String view utilities
#include "upb/mem/arena.hpp"  // Memory arena management

// Test case for verifying map deletion functionality, specifically checking for
// regression in delete operations.
TEST(MapTest, DeleteRegression) {
  // Create a memory arena for memory allocation
  upb::Arena arena;
  
  // Create a new map with int32 keys and string values
  upb_Map* map = upb_Map_New(arena.ptr(), kUpb_CType_Int32, kUpb_CType_String);

  // Create a key for the map entry (int32 type)
  upb_MessageValue key;
  key.int32_val = 0;  // Set key to integer value 0

  // Create a value to insert into the map (string type)
  upb_MessageValue insert_value;
  insert_value.str_val = upb_StringView_FromString("abcde");  // Set value to "abcde"

  // Insert the key-value pair into the map and verify insertion was successful
  upb_MapInsertStatus st = upb_Map_Insert(map, key, insert_value, arena.ptr());
  EXPECT_EQ(kUpb_MapInsertStatus_Inserted, st);

  // Attempt to delete the entry using the same key
  upb_MessageValue delete_value;
  bool removed = upb_Map_Delete(map, key, &delete_value);
  EXPECT_TRUE(removed);  // Verify the deletion was successful

  // Verify that the deleted value matches the originally inserted value
  EXPECT_TRUE(
      upb_StringView_IsEqual(insert_value.str_val, delete_value.str_val));
}
```

The comments explain:
1. The purpose of the test case (verifying delete functionality)
2. Each major operation (arena creation, map creation, insertion, deletion)
3. The verification steps and what they're checking
4. The types and values being used at each step
5. The expected outcomes of each operation

The comments are placed to flow with the code and provide context without being overly verbose. They help future maintainers understand both what the code is doing and why each step is important for the test case.