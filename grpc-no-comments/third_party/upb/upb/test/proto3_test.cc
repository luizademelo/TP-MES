
// Copyright 2023 Google LLC.  All rights reserved.

#include <gtest/gtest.h>
#include "upb/reflection/def.hpp"
#include "upb/test/proto3_test.upb.h"
#include "upb/test/proto3_test.upbdefs.h"

TEST(Proto3Test, SyntheticOneofExtension) {
  upb::DefPool defpool;
  upb::MessageDefPtr md(upb_test_TestMessage3_getmsgdef(defpool.ptr()));
  ASSERT_EQ(md.field_count(), 6);
}
