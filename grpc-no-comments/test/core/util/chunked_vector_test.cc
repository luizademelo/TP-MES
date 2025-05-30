// Copyright 2021 gRPC authors.

#include "src/core/util/chunked_vector.h"

#include <grpc/event_engine/memory_allocator.h>

#include <algorithm>
#include <memory>

#include "gtest/gtest.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {
namespace testing {

static constexpr size_t kInitialArenaSize = 1024;
static constexpr size_t kChunkSize = 3;

TEST(ChunkedVectorTest, Noop) {
  auto arena = SimpleArenaAllocator(kInitialArenaSize)->MakeArena();
  ChunkedVector<int, kChunkSize> v(arena.get());
  EXPECT_EQ(0, v.size());
}

TEST(ChunkedVectorTest, Stack) {
  auto arena = SimpleArenaAllocator(kInitialArenaSize)->MakeArena();
  ChunkedVector<int, kChunkSize> v(arena.get());

  EXPECT_EQ(0, v.size());
  v.EmplaceBack(1);
  EXPECT_EQ(1, v.size());
  v.EmplaceBack(2);
  EXPECT_EQ(2, v.size());
  v.EmplaceBack(3);
  EXPECT_EQ(3, v.size());
  v.EmplaceBack(4);
  EXPECT_EQ(4, v.size());
  v.EmplaceBack(5);
  EXPECT_EQ(5, v.size());
  v.EmplaceBack(6);
  EXPECT_EQ(6, v.size());
  v.EmplaceBack(7);
  EXPECT_EQ(7, v.size());
  v.EmplaceBack(8);
  EXPECT_EQ(8, v.size());

  EXPECT_EQ(8, v.PopBack());
  EXPECT_EQ(7, v.size());
  EXPECT_EQ(7, v.PopBack());
  EXPECT_EQ(6, v.size());
  EXPECT_EQ(6, v.PopBack());
  EXPECT_EQ(5, v.size());
  EXPECT_EQ(5, v.PopBack());
  EXPECT_EQ(4, v.size());
  EXPECT_EQ(4, v.PopBack());
  EXPECT_EQ(3, v.size());
  EXPECT_EQ(3, v.PopBack());
  EXPECT_EQ(2, v.size());
  EXPECT_EQ(2, v.PopBack());
  EXPECT_EQ(1, v.size());
  EXPECT_EQ(1, v.PopBack());
  EXPECT_EQ(0, v.size());
}

TEST(ChunkedVectorTest, Iterate) {
  auto arena = SimpleArenaAllocator(kInitialArenaSize)->MakeArena();
  ChunkedVector<int, kChunkSize> v(arena.get());
  v.EmplaceBack(1);
  v.EmplaceBack(2);
  v.EmplaceBack(3);
  v.EmplaceBack(4);
  v.EmplaceBack(5);
  v.EmplaceBack(6);
  v.EmplaceBack(7);
  v.EmplaceBack(8);

  auto it = v.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  ++it;
  EXPECT_EQ(3, *it);
  ++it;
  EXPECT_EQ(4, *it);
  ++it;
  EXPECT_EQ(5, *it);
  ++it;
  EXPECT_EQ(6, *it);
  ++it;
  EXPECT_EQ(7, *it);
  ++it;
  EXPECT_EQ(8, *it);
  ++it;
  EXPECT_EQ(v.end(), it);
}

TEST(ChunkedVectorTest, ConstIterate) {
  auto arena = SimpleArenaAllocator(kInitialArenaSize)->MakeArena();
  ChunkedVector<int, kChunkSize> v(arena.get());
  v.EmplaceBack(1);
  v.EmplaceBack(2);
  v.EmplaceBack(3);
  v.EmplaceBack(4);
  v.EmplaceBack(5);
  v.EmplaceBack(6);
  v.EmplaceBack(7);
  v.EmplaceBack(8);

  auto it = v.cbegin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  ++it;
  EXPECT_EQ(3, *it);
  ++it;
  EXPECT_EQ(4, *it);
  ++it;
  EXPECT_EQ(5, *it);
  ++it;
  EXPECT_EQ(6, *it);
  ++it;
  EXPECT_EQ(7, *it);
  ++it;
  EXPECT_EQ(8, *it);
  ++it;
  EXPECT_EQ(v.cend(), it);
}

TEST(ChunkedVectorTest, Clear) {
  auto arena = SimpleArenaAllocator(kInitialArenaSize)->MakeArena();
  ChunkedVector<int, kChunkSize> v(arena.get());
  v.EmplaceBack(1);
  EXPECT_EQ(v.size(), 1);
  v.Clear();
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.begin(), v.end());
}

TEST(ChunkedVectorTest, RemoveIf) {
  auto arena = SimpleArenaAllocator(kInitialArenaSize)->MakeArena();
  ChunkedVector<int, kChunkSize> v(arena.get());
  v.EmplaceBack(1);
  v.SetEnd(std::remove_if(v.begin(), v.end(), [](int i) { return i == 1; }));
  EXPECT_EQ(v.size(), 0);
}

}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
