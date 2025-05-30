
// Copyright 2023 Google LLC.  All rights reserved.

#include <gtest/gtest.h>
#include "upb/base/descriptor_constants.h"
#include "upb/mem/arena.hpp"
#include "upb/reflection/def.hpp"
#include "upb/test/editions_test.upb.h"
#include "upb/test/editions_test.upbdefs.h"

TEST(EditionsTest, PlainField) {
  upb::DefPool defpool;
  upb::MessageDefPtr md(upb_test_2023_EditionsMessage_getmsgdef(defpool.ptr()));
  upb::FieldDefPtr f(md.FindFieldByName("plain_field"));
  EXPECT_TRUE(f.has_presence());
}

TEST(EditionsTest, ImplicitPresenceField) {
  upb::DefPool defpool;
  upb::MessageDefPtr md(upb_test_2023_EditionsMessage_getmsgdef(defpool.ptr()));
  upb::FieldDefPtr f(md.FindFieldByName("implicit_presence_field"));
  EXPECT_FALSE(f.has_presence());
}

TEST(EditionsTest, DelimitedField) {
  upb::DefPool defpool;
  upb::MessageDefPtr md(upb_test_2023_EditionsMessage_getmsgdef(defpool.ptr()));
  upb::FieldDefPtr f(md.FindFieldByName("delimited_field"));
  EXPECT_EQ(kUpb_FieldType_Group, f.type());
}

TEST(EditionsTest, RequiredField) {
  upb::DefPool defpool;
  upb::MessageDefPtr md(upb_test_2023_EditionsMessage_getmsgdef(defpool.ptr()));
  upb::FieldDefPtr f(md.FindFieldByName("required_field"));
  EXPECT_EQ(kUpb_Label_Required, f.label());
}

TEST(EditionsTest, ClosedEnum) {
  upb::DefPool defpool;
  upb::MessageDefPtr md(upb_test_2023_EditionsMessage_getmsgdef(defpool.ptr()));
  upb::FieldDefPtr f(md.FindFieldByName("enum_field"));
  ASSERT_TRUE(f.enum_subdef().is_closed());
}

TEST(EditionsTest, PackedField) {
  upb::DefPool defpool;
  upb::MessageDefPtr md(upb_test_2023_EditionsMessage_getmsgdef(defpool.ptr()));
  upb::FieldDefPtr f(md.FindFieldByName("unpacked_field"));
  ASSERT_FALSE(f.packed());
}

TEST(EditionsTest, ConstructProto) {

  upb::Arena arena;
  upb_test_2023_EditionsMessage_new(arena.ptr());
}
