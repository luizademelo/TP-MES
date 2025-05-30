
// Copyright 2023 gRPC authors.

#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/proto_buffer_writer.h>

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace {

TEST(ProtoBufferWriterTest, Next) {
  ByteBuffer buffer;
  ProtoBufferWriter writer(&buffer, 16, 256);

  void* data1;
  int size1;
  EXPECT_TRUE(writer.Next(&data1, &size1));
  EXPECT_GT(size1, 0);
  memset(data1, 1, size1);

  void* data2;
  int size2;
  EXPECT_TRUE(writer.Next(&data2, &size2));
  EXPECT_GT(size2, 0);
  memset(data2, 2, size2);

  EXPECT_EQ(writer.ByteCount(), size1 + size2);
  EXPECT_EQ(buffer.Length(), size1 + size2);
  Slice slice;
  EXPECT_TRUE(buffer.DumpToSingleSlice(&slice).ok());
  EXPECT_EQ(memcmp(slice.begin(), data1, size1), 0);
  EXPECT_EQ(memcmp(slice.begin() + size1, data2, size2), 0);
}

#ifdef GRPC_PROTOBUF_CORD_SUPPORT_ENABLED

TEST(ProtoBufferWriterTest, WriteCord) {
  ByteBuffer buffer;
  ProtoBufferWriter writer(&buffer, 16, 4096);

  absl::Cord cord;
  std::string str1 = std::string(1024, 'a');
  cord.Append(str1);
  std::string str2 = std::string(1024, 'b');
  cord.Append(str2);
  writer.WriteCord(cord);

  EXPECT_EQ(writer.ByteCount(), str1.size() + str2.size());
  EXPECT_EQ(buffer.Length(), str1.size() + str2.size());
  Slice slice;
  EXPECT_TRUE(buffer.DumpToSingleSlice(&slice).ok());
  EXPECT_EQ(memcmp(slice.begin() + str1.size(), str2.c_str(), str2.size()), 0);
}

#endif

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
