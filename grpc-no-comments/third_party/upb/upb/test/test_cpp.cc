
// Copyright 2023 Google LLC.  All rights reserved.

#include <string.h>

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

#include "google/protobuf/timestamp.upb.h"
#include "google/protobuf/timestamp.upbdefs.h"
#include <gtest/gtest.h>
#include "upb/base/upcast.h"
#include "upb/json/decode.h"
#include "upb/json/encode.h"
#include "upb/reflection/def.h"
#include "upb/reflection/def.hpp"
#include "upb/test/test_cpp.upb.h"
#include "upb/test/test_cpp.upbdefs.h"

#include "upb/port/def.inc"

TEST(Cpp, Iteration) {
  upb::DefPool defpool;
  upb::MessageDefPtr md(upb_test_TestMessage_getmsgdef(defpool.ptr()));

  int field_count = 0;
  for (auto field : md.fields()) {
    UPB_UNUSED(field);
    field_count++;
  }
  EXPECT_EQ(field_count, md.field_count());

  int oneof_count = 0;
  for (auto oneof : md.oneofs()) {
    UPB_UNUSED(oneof);
    oneof_count++;
  }
  EXPECT_EQ(oneof_count, md.oneof_count());
}

TEST(Cpp, Default) {
  upb::DefPool defpool;
  upb::Arena arena;
  upb::MessageDefPtr md(upb_test_TestMessage_getmsgdef(defpool.ptr()));
  upb_test_TestMessage* msg = upb_test_TestMessage_new(arena.ptr());
  size_t size = upb_JsonEncode(UPB_UPCAST(msg), md.ptr(), nullptr, 0, nullptr,
                               0, nullptr);
  EXPECT_EQ(2, size);
}

TEST(Cpp, JsonNull) {
  upb::DefPool defpool;
  upb::MessageDefPtr md(upb_test_TestMessage_getmsgdef(defpool.ptr()));
  upb::FieldDefPtr i32_f = md.FindFieldByName("i32");
  upb::FieldDefPtr str_f = md.FindFieldByName("str");
  ASSERT_TRUE(i32_f);
  ASSERT_TRUE(str_f);
  EXPECT_EQ(5, i32_f.default_value().int32_val);
  EXPECT_EQ(0, strcmp(str_f.default_value().str_val.data, "abc"));
  EXPECT_EQ(3, str_f.default_value().str_val.size);
}

TEST(Cpp, TimestampEncoder) {
  upb::DefPool defpool;
  upb::Arena arena;
  upb::MessageDefPtr md(google_protobuf_Timestamp_getmsgdef(defpool.ptr()));
  google_protobuf_Timestamp* timestamp_upb =
      google_protobuf_Timestamp_new(arena.ptr());
  google_protobuf_Timestamp* timestamp_upb_decoded =
      google_protobuf_Timestamp_new(arena.ptr());

  int64_t timestamps[] = {
      253402300799,
      1641006000,
      0,
      -31525200,
      -2208988800,
      -62135596800,
  };

  for (int64_t timestamp : timestamps) {
    google_protobuf_Timestamp_set_seconds(timestamp_upb, timestamp);

    char json[128];
    size_t size = upb_JsonEncode(UPB_UPCAST(timestamp_upb), md.ptr(), nullptr,
                                 0, json, sizeof(json), nullptr);
    bool result = upb_JsonDecode(json, size, UPB_UPCAST(timestamp_upb_decoded),
                                 md.ptr(), nullptr, 0, arena.ptr(), nullptr);
    const int64_t timestamp_decoded =
        google_protobuf_Timestamp_seconds(timestamp_upb_decoded);

    ASSERT_TRUE(result);
    EXPECT_EQ(timestamp, timestamp_decoded);
  }
}
