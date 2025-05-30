
// Copyright 2023 Google LLC.  All rights reserved.

#include <gtest/gtest.h>
#include "upb/test/test_import_empty_srcs.upb_minitable.h"

TEST(Test, Reexport) {

  ASSERT_GT(sizeof(upb_0test__ContainsImported_msg_init), 0);
}
