
// Copyright 2015 gRPC authors.

#include "src/core/lib/slice/slice_string_helpers.h"

#include <grpc/support/alloc.h>

#include <memory>

#include "absl/log/log.h"
#include "gtest/gtest.h"
#include "src/core/util/string.h"

static void expect_slice_dump(grpc_slice slice, uint32_t flags,
                              const char* result) {
  char* got = grpc_dump_slice(slice, flags);
  ASSERT_STREQ(got, result);
  gpr_free(got);
  grpc_slice_unref(slice);
}

TEST(SliceStringHelpersTest, DumpSlice) {
  static const char* text = "HELLO WORLD!";
  static const char* long_text =
      "It was a bright cold day in April, and the clocks were striking "
      "thirteen. Winston Smith, his chin nuzzled into his breast in an effort "
      "to escape the vile wind, slipped quickly through the glass doors of "
      "Victory Mansions, though not quickly enough to prevent a swirl of "
      "gritty dust from entering along with him.";

  LOG(INFO) << "test_dump_slice";

  expect_slice_dump(grpc_slice_from_copied_string(text), GPR_DUMP_ASCII, text);
  expect_slice_dump(grpc_slice_from_copied_string(long_text), GPR_DUMP_ASCII,
                    long_text);
  expect_slice_dump(grpc_slice_from_copied_buffer("\x01", 1), GPR_DUMP_HEX,
                    "01");
  expect_slice_dump(grpc_slice_from_copied_buffer("\x01", 1),
                    GPR_DUMP_HEX | GPR_DUMP_ASCII, "01 '.'");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
