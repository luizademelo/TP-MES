Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/message/accessors.h"

#include <string.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include <gtest/gtest.h>
#include "google/protobuf/test_messages_proto2.upb.h"
#include "google/protobuf/test_messages_proto2.upb_minitable.h"
#include "google/protobuf/test_messages_proto3.upb.h"
#include "google/protobuf/test_messages_proto3.upb_minitable.h"
#include "upb/base/descriptor_constants.h"
#include "upb/base/status.h"
#include "upb/base/string_view.h"
#include "upb/base/upcast.h"
#include "upb/mem/arena.h"
#include "upb/message/array.h"
#include "upb/message/message.h"
#include "upb/mini_descriptor/decode.h"
#include "upb/mini_descriptor/internal/encode.hpp"
#include "upb/mini_descriptor/internal/modifiers.h"
#include "upb/mini_table/field.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

namespace {

// Field numbers for proto2 test message fields
const uint32_t kFieldOptionalInt32 = 1;
const uint32_t kFieldOptionalUInt32 = 3;
const uint32_t kFieldOptionalBool = 13;
const uint32_t kFieldOptionalString = 14;
const uint32_t kFieldOptionalNestedMessage = 18;
const uint32_t kFieldOptionalRepeatedInt32 = 31;
const uint32_t kFieldOptionalRepeatedNestedMessage = 48;
const uint32_t kFieldOptionalNestedMessageA = 1;
const uint32_t kFieldOptionalOneOfUInt32 = 111;
const uint32_t kFieldOptionalOneOfString = 113;

// Field numbers for proto3 test message fields
const uint32_t kFieldProto3OptionalInt64 = 2;
const uint32_t kFieldProto3OptionalUInt64 = 4;

// Test values for various field types
const char kTestStr1[] = "Hello1";
const char kTestStr2[] = "Hello2";
const int32_t kTestInt32 = 567;
const int32_t kTestUInt32 = 0xF1234567;
const uint64_t kTestUInt64 = 0xFEDCBAFF87654321;

// Helper function to find a field in proto3 test message by number
const upb_MiniTableField* find_proto3_field(int field_number) {
  return upb_MiniTable_FindFieldByNumber(
      &protobuf_0test_0messages__proto3__TestAllTypesProto3_msg_init,
      field_number);
}

// Helper function to find a field in proto2 test message by number
const upb_MiniTableField* find_proto2_field(int field_number) {
  return upb_MiniTable_FindFieldByNumber(
      &protobuf_0test_0messages__proto2__TestAllTypesProto2_msg_init,
      field_number);
}

// Test case for proto2 message field presence/has operations
TEST(GeneratedCode, HazzersProto2) {
  upb_Arena* arena = upb_Arena_New();
  protobuf_test_messages_proto2_TestAllTypesProto2* msg =
      protobuf_test_messages_proto2_TestAllTypesProto2_new(arena);

  // Test boolean field presence
  const upb_MiniTableField* optional_bool_field =
      find_proto2_field(kFieldOptionalBool);
  EXPECT_EQ(false,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_bool_field));
  protobuf_test_messages_proto2_TestAllTypesProto2_set_optional_bool(msg, true);
  EXPECT_EQ(true,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_bool_field));
  upb_Message_ClearBaseField(UPB_UPCAST(msg), optional_bool_field);
  EXPECT_EQ(false,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_bool_field));
  EXPECT_EQ(
      false,
      protobuf_test_messages_proto2_TestAllTypesProto2_optional_bool(msg));

  // Test string field presence
  const upb_MiniTableField* optional_string_field =
      find_proto2_field(kFieldOptionalString);
  EXPECT_EQ(false,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_string_field));
  protobuf_test_messages_proto2_TestAllTypesProto2_set_optional_string(
      msg, upb_StringView_FromString(kTestStr1));
  EXPECT_EQ(true,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_string_field));
  EXPECT_EQ(
      strlen(kTestStr1),
      protobuf_test_messages_proto2_TestAllTypesProto2_optional_string(msg)
          .size);
  upb_Message_ClearBaseField(UPB_UPCAST(msg), optional_string_field);
  EXPECT_EQ(false,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_string_field));
  EXPECT_EQ(
      0, protobuf_test_messages_proto2_TestAllTypesProto2_optional_string(msg)
             .size);

  // Test message field presence
  const upb_MiniTableField* optional_message_field =
      find_proto2_field(kFieldOptionalNestedMessage);
  EXPECT_EQ(false,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_message_field));
  protobuf_test_messages_proto2_TestAllTypesProto2_mutable_optional_nested_message(
      msg, arena);
  EXPECT_EQ(true,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_message_field));
  upb_Message_ClearBaseField(UPB_UPCAST(msg), optional_message_field);
  EXPECT_EQ(false,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_message_field));
  EXPECT_EQ(
      true,
      protobuf_test_messages_proto2_TestAllTypesProto2_optional_nested_message(
          msg) == nullptr);

  // Test oneof field presence
  const upb_MiniTableField* optional_oneof_uint32_field =
      find_proto2_field(kFieldOptionalOneOfUInt32);
  const upb_MiniTableField* optional_oneof_string_field =
      find_proto2_field(kFieldOptionalOneOfString);

  EXPECT_EQ(false, upb_Message_HasBaseField(UPB_UPCAST(msg),
                                            optional_oneof_uint32_field));
  EXPECT_EQ(false, upb_Message_HasBaseField(UPB_UPCAST(msg),
                                            optional_oneof_string_field));
  protobuf_test_messages_proto2_TestAllTypesProto2_set_oneof_uint32(msg, 123);
  EXPECT_EQ(true, upb_Message_HasBaseField(UPB_UPCAST(msg),
                                           optional_oneof_uint32_field));
  EXPECT_EQ(false, upb_Message_HasBaseField(UPB_UPCAST(msg),
                                            optional_oneof_string_field));
  protobuf_test_messages_proto2_TestAllTypesProto2_set_oneof_string(
      msg, upb_StringView_FromString(kTestStr1));
  EXPECT_EQ(false, upb_Message_HasBaseField(UPB_UPCAST(msg),
                                            optional_oneof_uint32_field));
  EXPECT_EQ(true, upb_Message_HasBaseField(UPB_UPCAST(msg),
                                           optional_oneof_string_field));
  upb_Message_ClearBaseField(UPB_UPCAST(msg), optional_oneof_uint32_field);
  EXPECT_EQ(false, upb_Message_HasBaseField(UPB_UPCAST(msg),
                                            optional_oneof_uint32_field));
  EXPECT_EQ(true, upb_Message_HasBaseField(UPB_UPCAST(msg),
                                           optional_oneof_string_field));
  upb_Message_ClearBaseField(UPB_UPCAST(msg), optional_oneof_string_field);
  EXPECT_EQ(false, upb_Message_HasBaseField(UPB_UPCAST(msg),
                                            optional_oneof_uint32_field));
  EXPECT_EQ(false, upb_Message_HasBaseField(UPB_UPCAST(msg),
                                            optional_oneof_string_field));

  upb_Arena_Free(arena);
}

// Test case for proto2 scalar field operations
TEST(GeneratedCode, ScalarsProto2) {
  upb_Arena* arena = upb_Arena_New();
  protobuf_test_messages_proto2_TestAllTypesProto2* msg =
      protobuf_test_messages_proto2_TestAllTypesProto2_new(arena);

  // Test int32 field operations
  const upb_MiniTableField* optional_int32_field =
      find_proto2_field(kFieldOptionalInt32);

  EXPECT_EQ(
      0, protobuf_test_messages_proto2_TestAllTypesProto2_optional_int32(msg));

  EXPECT_EQ(0, upb_Message_GetInt32(UPB_UPCAST(msg), optional_int32_field, 0));
  upb_Message_SetBaseFieldInt32(UPB_UPCAST(msg), optional_int32_field,
                                kTestInt32);
  EXPECT_EQ(true,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_int32_field));
  EXPECT_EQ(kTestInt32,
            upb_Message_GetInt32(UPB_UPCAST(msg), optional_int32_field, 0));
  EXPECT_EQ(
      kTestInt32,
      protobuf_test_messages_proto2_TestAllTypesProto2_optional_int32(msg));

  // Test uint32 field operations
  const upb_MiniTableField* optional_uint32_field =
      find_proto2_field(kFieldOptionalUInt32);

  EXPECT_EQ(
      0, protobuf_test_messages_proto2_TestAllTypesProto2_optional_uint32(msg));
  EXPECT_EQ(0,
            upb_Message_GetUInt32(UPB_UPCAST(msg), optional_uint32_field, 0));
  upb_Message_SetBaseFieldUInt32(UPB_UPCAST(msg), optional_uint32_field,
                                 kTestUInt32);
  EXPECT_EQ(kTestUInt32,
            upb_Message_GetUInt32(UPB_UPCAST(msg), optional_uint32_field, 0));
  EXPECT_EQ(
      kTestUInt32,
      protobuf_test_messages_proto2_TestAllTypesProto2_optional_uint32(msg));

  upb_Arena_Free(arena);
}

// Test case for proto3 scalar field operations
TEST(GeneratedCode, ScalarProto3) {
  upb_Arena* arena = upb_Arena_New();
  protobuf_test_messages_proto3_TestAllTypesProto3* msg =
      protobuf_test_messages_proto3_TestAllTypesProto3_new(arena);

  const upb_MiniTableField* optional_int64_field =
      find_proto3_field(kFieldProto3OptionalInt64);
  const upb_MiniTableField* optional_uint64_field =
      find_proto3_field(kFieldProto3OptionalUInt64);

  // Test int64 field operations
  EXPECT_EQ(
      0, protobuf_test_messages_proto3_TestAllTypesProto3_optional_int64(msg));
  upb_Message_SetBaseFieldInt64(UPB_UPCAST(msg), optional_int64_field, -1);
  EXPECT_EQ(
      -1, protobuf_test_messages_proto3_TestAllTypesProto3_optional_int64(msg));
  EXPECT_EQ(-1, upb_Message_GetInt64(UPB_UPCAST(msg), optional_int64_field, 0));

  // Test uint64 field operations
  EXPECT_EQ(
      0, protobuf_test_messages_proto3_TestAllTypesProto3_optional_uint64(msg));
  upb_Message_SetBaseFieldUInt64(UPB_UPCAST(msg), optional_uint64_field,
                                 kTestUInt64);
  EXPECT_EQ(
      kTestUInt64,
      protobuf_test_messages_proto3_TestAllTypesProto3_optional_uint64(msg));
  EXPECT_EQ(kTestUInt64,
            upb_Message_GetUInt64(UPB_UPCAST(msg), optional_uint64_field, 0));

  upb_Arena_Free(arena);
}

// Test case for string field operations
TEST(GeneratedCode, Strings) {
  upb_Arena* arena = upb_Arena_New();
  protobuf_test_messages_proto2_TestAllTypesProto2* msg =
      protobuf_test_messages_proto2_TestAllTypesProto2_new(arena);

  const upb_MiniTableField* optional_string_field =
      find_proto2_field(kFieldOptionalString);

  EXPECT_EQ(false,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_string_field));

  // Test string field set/get operations
  protobuf_test_messages_proto2_TestAllTypesProto2_set_optional_string(
      msg, upb_StringView_FromString(kTestStr1));
  EXPECT_EQ(true,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_string_field));
  upb_StringView value = upb_Message_GetString(
      UPB_UPCAST(msg), optional_string_field, upb_StringView{nullptr, 0});
  std::string read_value = std::string(value.data, value.size);
  EXPECT_EQ(kTestStr1, read_value);

  // Test string field clear operations
  upb_Message_ClearBaseField(UPB_UPCAST(msg), optional_string_field);
  EXPECT_EQ(false,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_string_field));
  EXPECT_EQ(
      false,
      protobuf_test_messages_proto2_TestAllTypesProto2_has_optional_string(
          msg));
  
  // Test setting string via base field API
  upb_Message_SetBaseFieldString(UPB_UPCAST(msg), optional_string_field,
                                 upb_StringView_FromString(kTestStr2));
  EXPECT_EQ(true,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_string_field));
  EXPECT_EQ(
      true,
      protobuf_test_messages_proto2_TestAllTypesProto2_has_optional_string(
          msg));
  value = protobuf_test_messages_proto2_TestAllTypesProto2_optional_string(msg);
  read_value = std::string(value.data, value.size);
  EXPECT_EQ(kTestStr2, read_value);

  upb_Arena_Free(arena);
}

// Test case for submessage field operations
TEST(GeneratedCode, SubMessage) {
  upb_Arena* arena = upb_Arena_New();
  protobuf_test_messages_proto2_TestAllTypesProto2* msg =
      protobuf_test_messages_proto2_TestAllTypesProto2_new(arena);

  const upb_MiniTableField* optional_message_field =
      find_proto2_field(kFieldOptionalNestedMessage);

  // Test initial submessage state
  const upb_Message* test_message =
      upb_Message_GetMessage(UPB_UPCAST(msg), optional_message_field);
  EXPECT_EQ(nullptr, test_message);

  EXPECT_EQ(false,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_message_field));

  // Test creating and manipulating a submessage
  protobuf_test_messages_proto2_TestAllTypesProto2_NestedMessage* nested_message =
      protobuf_test_messages_proto2_TestAllTypesProto2_mutable_optional_nested_message(
          msg, arena);
  EXPECT_EQ(true, nested_message != nullptr);
  EXPECT_EQ(true,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_message_field));
  protobuf_test_messages_proto2_TestAllTypesProto2_NestedMessage_set_a(
      nested_message, 5);

  // Verify submessage content
  const upb_Message* sub_message =
      upb_Message_GetMessage(UPB_UPCAST(msg), optional_message_field);
  EXPECT_EQ(true, sub_message != nullptr);

  const upb_MiniTableField* nested_message_a_field =
      upb_MiniTable_FindFieldByNumber(
          &protobuf_0test_0messages__proto2__TestAllTypesProto2__NestedMessage_msg_init,
          kFieldOptionalNestedMessageA);
  EXPECT_EQ(5, upb_Message_GetInt32(sub_message, nested_message_a_field, 0));

  // Test clearing submessage
  upb_Message_ClearBaseField(UPB_UPCAST(msg), optional_message_field);
  EXPECT_EQ(
      nullptr,
      protobuf_test_messages_proto2_TestAllTypesProto2_optional_nested_message(
          msg));
  EXPECT_EQ(false,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_message_field));

  // Test setting submessage via message API
  upb_Message* new_nested_message = UPB_UPCAST(
      protobuf_test_messages_proto2_TestAllTypesProto2_NestedMessage_new(
          arena));
  upb_Message_SetBaseFieldInt32(new_nested_message, nested_message_a_field,
                                123);
  upb_Message_SetMessage(UPB_UPCAST(msg), optional_message_field,
                         new_nested_message);

  // Verify submessage content after setting
  upb_Message* mutable_message = upb_Message_GetOrCreateMutableMessage(
      UPB_UPCAST(msg),
      &protobuf_0test_0messages__proto2__TestAllTypesProto2_msg_init,
      optional_message_field, arena);
  EXPECT_EQ(
      true,
      protobuf_test_messages_proto2_TestAllTypesProto2_optional_nested_message(
          msg) != nullptr);
  EXPECT_EQ(true,
            upb_Message_HasBaseField(UPB_UPCAST(msg), optional_message_field));
  EXPECT_EQ(123,
            upb_Message_GetInt32(mutable_message, nested_message_a_field, 0));

  upb_Arena_Free(arena);
}

// Test case for repeated scalar field operations
TEST(GeneratedCode, RepeatedScalar) {