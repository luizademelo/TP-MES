
// Copyright 2015 gRPC authors.

#include "src/core/util/ring_buffer.h"

#include <grpc/support/port_platform.h>

#include "gtest/gtest.h"

namespace grpc_core {

constexpr int kBufferCapacity = 1000;

TEST(RingBufferTest, BufferAppendPopTest) {
  RingBuffer<int, kBufferCapacity> buffer;
  EXPECT_FALSE(buffer.PopIfNotEmpty().has_value());

  for (int i = 0; i < (3 * kBufferCapacity) / 2; ++i) {
    buffer.Append(i);
  }

  int j = kBufferCapacity / 2;
  for (int i = 0; i < kBufferCapacity / 2; ++i) {
    EXPECT_EQ(buffer.PopIfNotEmpty(), j++);
  }
  EXPECT_EQ(j, kBufferCapacity);

  for (auto it = buffer.begin(); it != buffer.end(); ++it) {
    EXPECT_EQ(*it, j++);
  }

  EXPECT_EQ(j, (3 * kBufferCapacity) / 2);

  for (int i = 0; i < kBufferCapacity / 2; ++i) {
    buffer.Append(j++);
  }

  j = kBufferCapacity;
  while (true) {
    auto ret = buffer.PopIfNotEmpty();
    if (!ret.has_value()) break;
    EXPECT_EQ(*ret, j++);
  }
  EXPECT_EQ(j, 2 * kBufferCapacity);
}

TEST(RingBufferTest, BufferAppendIterateTest) {
  RingBuffer<int, kBufferCapacity> buffer;
  for (int i = 0; i < 5 * kBufferCapacity; ++i) {
    buffer.Append(i);
    int j = std::max(0, i + 1 - kBufferCapacity);

    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
      EXPECT_EQ(*it, j++);
    }

    EXPECT_EQ(j, i + 1);
  }
  buffer.Clear();
  EXPECT_EQ(buffer.begin(), buffer.end());
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
