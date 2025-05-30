
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

std::vector<std::string> PathsToText(upb_FieldPathEntry* entry) {
  std::vector<std::string> ret;
  char buf[1024];
  while (entry->field) {
    upb_FieldPathEntry* before = entry;
    size_t len = upb_FieldPath_ToText(&entry, buf, sizeof(buf));
    EXPECT_LT(len, sizeof(buf));
    assert(len <= sizeof(buf));
    ret.push_back(buf);

    char shortbuf[4];
    size_t len2 = upb_FieldPath_ToText(&before, shortbuf, sizeof(shortbuf));
    EXPECT_EQ(len, len2);
    EXPECT_EQ(ret.back().substr(0, sizeof(shortbuf) - 1),
              std::string(shortbuf));
  }
  return ret;
}

template <typename T>
class RequiredFieldsTest : public testing::Test {
 public:
  void CheckRequired(absl::string_view json,
                     const std::vector<std::string>& missing) {
    upb::Arena arena;
    upb::DefPool defpool;
    auto* test_msg = T::NewMessage(arena.ptr());
    upb::MessageDefPtr m = T::GetMessageDef(defpool.ptr());
    upb::Status status;
    EXPECT_TRUE(upb_JsonDecode(json.data(), json.size(), UPB_UPCAST(test_msg),
                               m.ptr(), defpool.ptr(), 0, arena.ptr(),
                               status.ptr()))
        << status.error_message();
    upb_FieldPathEntry* entries = nullptr;
    EXPECT_EQ(!missing.empty(),
              upb_util_HasUnsetRequired(UPB_UPCAST(test_msg), m.ptr(),
                                        defpool.ptr(), &entries));
    if (entries) {
      EXPECT_EQ(missing, PathsToText(entries));
      free(entries);
    }

    EXPECT_EQ(!missing.empty(),
              upb_util_HasUnsetRequired(UPB_UPCAST(test_msg), m.ptr(),
                                        defpool.ptr(), nullptr));
  }
};

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

using MyTypes = ::testing::Types<Proto2Type, Edition2023Type>;
TYPED_TEST_SUITE(RequiredFieldsTest, MyTypes);

TYPED_TEST(RequiredFieldsTest, TestRequired) {
  TestFixture::CheckRequired(R"json({})json", {"required_message"});
  TestFixture::CheckRequired(R"json({"required_message": {}})json", {});
  TestFixture::CheckRequired(
      R"json(
      {
        "optional_message": {}
      }
      )json",
      {"required_message", "optional_message.required_message"});

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
