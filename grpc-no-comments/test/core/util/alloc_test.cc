
// Copyright 2015 gRPC authors.

#include <grpc/support/alloc.h>
#include <stdint.h>
#include <string.h>

#include <memory>

#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

TEST(AllocTest, MallocAligned) {
  for (size_t size = 1; size <= 256; ++size) {
    void* ptr = gpr_malloc_aligned(size, 16);
    ASSERT_NE(ptr, nullptr);
    ASSERT_EQ(((intptr_t)ptr & 0xf), 0);
    memset(ptr, 0, size);
    gpr_free_aligned(ptr);
  }
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
