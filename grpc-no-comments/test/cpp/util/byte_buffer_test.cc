
// Copyright 2015 gRPC authors.

#include <grpc++/support/byte_buffer.h>
#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/support/slice.h>

#include <cstring>
#include <vector>

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

namespace grpc {

namespace {

const char* kContent1 = "hello xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char* kContent2 = "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy world";

class ByteBufferTest : public ::testing::Test {
 protected:
  static void SetUpTestSuite() { grpc_init(); }

  static void TearDownTestSuite() { grpc_shutdown(); }
};

TEST_F(ByteBufferTest, CopyCtor) {
  ByteBuffer buffer1;
  EXPECT_FALSE(buffer1.Valid());
  const ByteBuffer& buffer2 = buffer1;
  EXPECT_FALSE(buffer2.Valid());
}

TEST_F(ByteBufferTest, CreateFromSingleSlice) {
  Slice s(kContent1);
  ByteBuffer buffer(&s, 1);
  EXPECT_EQ(strlen(kContent1), buffer.Length());
}

TEST_F(ByteBufferTest, CreateFromVector) {
  std::vector<Slice> slices;
  slices.emplace_back(kContent1);
  slices.emplace_back(kContent2);
  ByteBuffer buffer(&slices[0], 2);
  EXPECT_EQ(strlen(kContent1) + strlen(kContent2), buffer.Length());
}

TEST_F(ByteBufferTest, Clear) {
  Slice s(kContent1);
  ByteBuffer buffer(&s, 1);
  buffer.Clear();
  EXPECT_EQ(0, buffer.Length());
}

TEST_F(ByteBufferTest, Length) {
  std::vector<Slice> slices;
  slices.emplace_back(kContent1);
  slices.emplace_back(kContent2);
  ByteBuffer buffer(&slices[0], 2);
  EXPECT_EQ(strlen(kContent1) + strlen(kContent2), buffer.Length());
}

bool SliceEqual(const Slice& a, grpc_slice b) {
  if (a.size() != GRPC_SLICE_LENGTH(b)) {
    return false;
  }
  for (size_t i = 0; i < a.size(); i++) {
    if (a.begin()[i] != GRPC_SLICE_START_PTR(b)[i]) {
      return false;
    }
  }
  return true;
}

TEST_F(ByteBufferTest, Dump) {
  grpc_slice hello = grpc_slice_from_copied_string(kContent1);
  grpc_slice world = grpc_slice_from_copied_string(kContent2);
  std::vector<Slice> slices;
  slices.push_back(Slice(hello, Slice::STEAL_REF));
  slices.push_back(Slice(world, Slice::STEAL_REF));
  ByteBuffer buffer(&slices[0], 2);
  slices.clear();
  (void)buffer.Dump(&slices);
  EXPECT_TRUE(SliceEqual(slices[0], hello));
  EXPECT_TRUE(SliceEqual(slices[1], world));
}

TEST_F(ByteBufferTest, SerializationMakesCopy) {
  grpc_slice hello = grpc_slice_from_copied_string(kContent1);
  grpc_slice world = grpc_slice_from_copied_string(kContent2);
  std::vector<Slice> slices;
  slices.push_back(Slice(hello, Slice::STEAL_REF));
  slices.push_back(Slice(world, Slice::STEAL_REF));
  ByteBuffer send_buffer;
  bool owned = false;
  ByteBuffer buffer(&slices[0], 2);
  slices.clear();
  auto status =
      SerializationTraits<ByteBuffer>::Serialize(buffer, &send_buffer, &owned);
  EXPECT_TRUE(status.ok());
  EXPECT_TRUE(owned);
  EXPECT_TRUE(send_buffer.Valid());
}

TEST_F(ByteBufferTest, TrySingleSliceWithSingleSlice) {
  std::vector<Slice> slices;
  slices.emplace_back(kContent1);
  ByteBuffer buffer(&slices[0], 1);
  Slice slice;
  EXPECT_TRUE(buffer.TrySingleSlice(&slice).ok());
  EXPECT_EQ(slice.size(), slices[0].size());
  EXPECT_EQ(memcmp(slice.begin(), slices[0].begin(), slice.size()), 0);
}

TEST_F(ByteBufferTest, TrySingleSliceWithMultipleSlices) {
  std::vector<Slice> slices;
  slices.emplace_back(kContent1);
  slices.emplace_back(kContent2);
  ByteBuffer buffer(&slices[0], 2);
  Slice slice;
  EXPECT_FALSE(buffer.TrySingleSlice(&slice).ok());
}

TEST_F(ByteBufferTest, DumpToSingleSlice) {
  std::vector<Slice> slices;
  slices.emplace_back(kContent1);
  slices.emplace_back(kContent2);
  ByteBuffer buffer(&slices[0], 2);
  Slice slice;
  EXPECT_TRUE(buffer.DumpToSingleSlice(&slice).ok());
  EXPECT_EQ(strlen(kContent1) + strlen(kContent2), slice.size());
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
