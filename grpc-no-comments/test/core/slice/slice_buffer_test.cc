// Copyright 2022 The gRPC Authors

#include "src/core/lib/slice/slice_buffer.h"

#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <memory>
#include <utility>

#include "absl/log/check.h"
#include "gtest/gtest.h"
#include "src/core/lib/slice/slice.h"

using ::grpc_core::Slice;
using ::grpc_core::SliceBuffer;

static constexpr int kNewSliceLength = 100;

Slice MakeSlice(size_t len) {
  CHECK_GT(len, 0);
  unsigned char* contents = static_cast<unsigned char*>(gpr_malloc(len));
  memset(contents, 'a', len);
  return Slice(grpc_slice_new(contents, len, gpr_free));
}

TEST(SliceBufferTest, AddAndRemoveTest) {
  SliceBuffer sb;
  Slice first_slice = MakeSlice(kNewSliceLength);
  Slice second_slice = MakeSlice(kNewSliceLength);
  Slice first_slice_copy = first_slice.Copy();
  sb.Append(std::move(first_slice));
  sb.Append(std::move(second_slice));
  ASSERT_EQ(sb.Count(), 2);
  ASSERT_EQ(sb.Length(), 2 * kNewSliceLength);
  Slice popped = sb.TakeFirst();
  ASSERT_EQ(popped, first_slice_copy);
  ASSERT_EQ(sb.Count(), 1);
  ASSERT_EQ(sb.Length(), kNewSliceLength);
  sb.Prepend(std::move(popped));
  ASSERT_EQ(sb.Count(), 2);
  ASSERT_EQ(sb.Length(), 2 * kNewSliceLength);
  sb.Clear();
  ASSERT_EQ(sb.Count(), 0);
  ASSERT_EQ(sb.Length(), 0);
}

TEST(SliceBufferTest, SliceRefTest) {
  SliceBuffer sb;
  Slice first_slice = MakeSlice(kNewSliceLength);
  Slice second_slice = MakeSlice(kNewSliceLength + 1);
  Slice first_slice_copy = first_slice.Copy();
  Slice second_slice_copy = second_slice.Copy();
  ASSERT_EQ(sb.AppendIndexed(std::move(first_slice)), 0);
  ASSERT_EQ(sb.AppendIndexed(std::move(second_slice)), 1);
  Slice first_reffed = sb.RefSlice(0);
  Slice second_reffed = sb.RefSlice(1);
  ASSERT_EQ(first_reffed, first_slice_copy);
  ASSERT_EQ(second_reffed, second_slice_copy);
  ASSERT_EQ(sb.Count(), 2);
  ASSERT_EQ(sb.Length(), 2 * kNewSliceLength + 1);
  sb.Clear();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
