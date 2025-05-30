
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/mini_table/compat.h"

#include <gtest/gtest.h>
#include "google/protobuf/test_messages_proto2.upb_minitable.h"
#include "google/protobuf/test_messages_proto3.upb_minitable.h"

namespace {

TEST(GeneratedCode, EqualsTestProto2) {
  EXPECT_TRUE(upb_MiniTable_Equals(
      &protobuf_0test_0messages__proto2__ProtoWithKeywords_msg_init,
      &protobuf_0test_0messages__proto2__ProtoWithKeywords_msg_init));
}

TEST(GeneratedCode, EqualsTestProto3) {
  EXPECT_TRUE(upb_MiniTable_Equals(
      &protobuf_0test_0messages__proto3__TestAllTypesProto3_msg_init,
      &protobuf_0test_0messages__proto3__TestAllTypesProto3_msg_init));
}

}
