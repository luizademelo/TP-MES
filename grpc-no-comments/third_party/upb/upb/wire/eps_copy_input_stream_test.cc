
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/wire/eps_copy_input_stream.h"

#include <string.h>

#include <string>

#include <gtest/gtest.h>
#include "upb/mem/arena.hpp"

namespace {

TEST(EpsCopyInputStreamTest, ZeroSize) {
  upb_EpsCopyInputStream stream;
  const char* ptr = nullptr;
  upb_EpsCopyInputStream_Init(&stream, &ptr, 0, false);
  EXPECT_TRUE(
      upb_EpsCopyInputStream_IsDoneWithCallback(&stream, &ptr, nullptr));
}

}
