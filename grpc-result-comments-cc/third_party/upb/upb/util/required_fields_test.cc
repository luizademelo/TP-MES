Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/util/required_fields.h"

#include <stdlib.h>

#include <gtest/gtest.h>
#include "absl/strings/string_view.h"
#include "upb/base/status.hpp"
#include "upb/base/upcast.h"
#include "upb/json/decode.h"
#include "upb/mem/arena.h"
#include "upb/mem/arena.hpp"
#include "upb/reflection/common.h"
#include "upb/reflection/def.hpp"
#include "upb/util/required_fields_editions_test.upb.h"
#include "upb/util/required_fields_editions_test.upbdefs.h"
#include "upb/util/required_fields_test.upb.h"
#include "upb/util/required_fields_test.upbdefs.h"

// Converts a upb_FieldPathEntry linked list into a vector of string paths
// Each entry represents a path to an unset required field
std::vector<std::string> PathsToText(upb_FieldPathEntry* entry) {
  std::vector<std::string> ret;
  char buf[1024];
  while (entry->field) {
    upb_FieldPathEntry* before = entry;
    // Convert field path entry to text representation
    size_t len = upb_FieldPath_ToText(&entry, buf, sizeof(buf));
    EXPECT_LT(len, sizeof(buf));
    assert(len <= sizeof(buf));
    ret.push_back(buf);

    // Test that the path can also be written to a small buffer
    char shortbuf[4];
    size_t len2 = upb_FieldPath_ToText(&before, shortbuf, sizeof(shortbuf));
    EXPECT_EQ(len, len2);
    EXPECT_EQ(ret.back().substr(0, sizeof(shortbuf) - 1),
              std::string(shortbuf));
  }
  return ret;
}

// Template class for testing required fields functionality
// Works with both proto2 and editions (2023) message types
template <typename T>
class RequiredFieldsTest : public testing::Test {
 public:
  // Checks that the JSON input either has or doesn't have the expected missing required fields
  // Args:
  //   json: JSON string to parse into a message
  //   missing: vector of expected missing required field paths
  void CheckRequired(absl::string_view json,
                     const std::vector<std::string>& missing) {
    upb::Arena arena;
    upb::DefPool defpool;
    // Create new message instance of the template type
    auto* test_msg = T::NewMessage(arena.ptr());
    // Get message definition
    upb::MessageDefPtr m = T::GetMessageDef(defpool.ptr());
    upb::Status status;
    
    // Decode JSON into the message
    EXPECT_TRUE(upb_JsonDecode(json.data(), json.size(), UPB_UPCAST(test_msg),
                               m.ptr(), defpool.ptr(), 0, arena.ptr(),
                               status.ptr()))
        << status.error_message();
    
    // Check for unset required fields and get their paths
    upb_FieldPathEntry* entries = nullptr;
    EXPECT_EQ(!missing.empty(),
              upb_util_HasUnsetRequired(UPB_UPCAST(test_msg), m.ptr(),
                                        defpool.ptr(), &entries));
    if (entries) {
      // Verify the paths match expected missing fields
      EXPECT_EQ(missing, PathsToText(entries));
      free(entries);
    }

    // Verify the same result when not requesting the actual paths
    EXPECT_EQ(!missing.empty(),
              upb_util_HasUnsetRequired(UPB_UPCAST(test_msg), m.ptr(),
                                        defpool.ptr(), nullptr));
  }
};

// Message type wrapper for proto2 required fields test messages
class Proto2Type {
 public:
  using MessageType = upb_util_test_TestRequiredFields;
  static MessageType* NewMessage(upb_Arena* arena) {
    return upb_util_test_TestRequiredFields_new(arena);
  }
  static upb::MessageDefPtr GetMessageDef(upb_DefPool* defpool) {
    return upb::MessageDefPtr(
        upb_util_test_TestRequiredFields_getmsgdef(defpool));
  }
};

// Message type wrapper for editions (2023) required fields test messages
class Edition2023Type {
 public:
  using MessageType = upb_util_2023_test_TestRequiredFields;
  static MessageType* NewMessage(upb_Arena* arena) {
    return upb_util_2023_test_TestRequiredFields_new(arena);
  }
  static upb::MessageDefPtr GetMessageDef(upb_DefPool* defpool) {
    return upb::MessageDefPtr(
        upb_util_2023_test_TestRequiredFields_getmsgdef(defpool));
  }
};

// Define the test types to run the tests against
using MyTypes = ::testing::Types<Proto2Type, Edition2023Type>;
TYPED_TEST_SUITE(RequiredFieldsTest, MyTypes);

// Test cases for required fields validation
TYPED_TEST(RequiredFieldsTest, TestRequired) {
  // Test empty message has required field missing
  TestFixture::CheckRequired(R"json({})json", {"required_message"});
  
  // Test message with required field set has no missing fields
  TestFixture::CheckRequired(R"json({"required_message": {}})json", {});
  
  // Test nested required fields in optional message
  TestFixture::CheckRequired(
      R"json(
      {
        "optional_message": {}
      }
      )json",
      {"required_message", "optional_message.required_message"});

  // Test required fields in repeated messages
  TestFixture::CheckRequired(
      R"json(
      {
        "optional_message": {
          "repeated_message": [
            {"required_int32": 1},
            {},
            {"required_int32": 2}
          ]
        }
      }
      )json",
      {"required_message", "optional_message.required_message",
       "optional_message.repeated_message[1].required_int32"});

  // Test required fields in int32 map values
  TestFixture::CheckRequired(
      R"json(
      {
        "required_message": {},
        "map_int32_message": {
          "1": {"required_int32": 1},
          "5": {},
          "9": {"required_int32": 1}
        }
      }
      )json",
      {"map_int32_message[5].required_int32"});

  // Test required fields in int64 map values
  TestFixture::CheckRequired(
      R"json(
      {
        "required_message": {},
        "map_int64_message": {
          "1": {"required_int32": 1},
          "5": {},
          "9": {"required_int32": 1}
        }
      }
      )json",
      {"map_int64_message[5].required_int32"});

  // Test required fields in uint32 map values
  TestFixture::CheckRequired(
      R"json(
      {
        "required_message": {},
        "map_uint32_message": {
          "1": {"required_int32": 1},
          "5": {},
          "9": {"required_int32": 1}
        }
      }
      )json",
      {"map_uint32_message[5].required_int32"});

  // Test required fields in uint64 map values
  TestFixture::CheckRequired(
      R"json(
      {
        "required_message": {},
        "map_uint64_message": {
          "1": {"required_int32": 1},
          "5": {},
          "9": {"required_int32": 1}
        }
      }
      )json",
      {"map_uint64_message[5].required_int32"});

  // Test required fields in bool map values
  TestFixture::CheckRequired(
      R"json(
      {
        "required_message": {},
        "map_bool_message": {
          "false": {"required_int32": 1},
          "true": {}
        }
      }
      )json",
      {"map_bool_message[true].required_int32"});

  // Test required fields in string map values (including escaped characters)
  TestFixture::CheckRequired(
      R"json(
      {
        "required_message": {},
        "map_string_message": {
          "abc": {"required_int32": 1},
          "d\"ef": {}
        }
      }
      )json",
      {R"(map_string_message["d\"ef"].required_int32)"});
}
```