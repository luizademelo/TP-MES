
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/varint.h"

#include <grpc/slice.h>

#include <memory>

#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

template <uint8_t kPrefixBits>
static void test_varint(uint32_t value, uint8_t prefix_or,
                        const char* expect_bytes, size_t expect_length) {
  grpc_core::VarintWriter<kPrefixBits> w(value);
  grpc_slice expect =
      grpc_slice_from_copied_buffer(expect_bytes, expect_length);
  grpc_slice slice;
  VLOG(2) << absl::StrFormat("Test: 0x%08x", value);
  ASSERT_EQ(w.length(), expect_length);
  slice = grpc_slice_malloc(w.length());
  w.Write(prefix_or, GRPC_SLICE_START_PTR(slice));
  ASSERT_TRUE(grpc_slice_eq(expect, slice));
  grpc_slice_unref(expect);
  grpc_slice_unref(slice);
}

#define TEST_VARINT(value, prefix_bits, prefix_or, expect) \
  test_varint<prefix_bits>(value, prefix_or, expect, sizeof(expect) - 1)

TEST(VarintTest, MainTest) {
  TEST_VARINT(0, 1, 0, "\x00");
  TEST_VARINT(128, 1, 0, "\x7f\x01");
  TEST_VARINT(16384, 1, 0, "\x7f\x81\x7f");
  TEST_VARINT(2097152, 1, 0, "\x7f\x81\xff\x7f");
  TEST_VARINT(268435456, 1, 0, "\x7f\x81\xff\xff\x7f");
  TEST_VARINT(0xffffffff, 1, 0, "\x7f\x80\xff\xff\xff\x0f");
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  return RUN_ALL_TESTS();
}
