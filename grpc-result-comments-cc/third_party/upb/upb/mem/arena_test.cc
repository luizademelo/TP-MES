Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/mem/arena.h"

#include <stddef.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <thread>
#include <type_traits>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "absl/base/thread_annotations.h"
#include "absl/cleanup/cleanup.h"
#include "absl/container/flat_hash_map.h"
#include "absl/random/distributions.h"
#include "absl/random/random.h"
#include "absl/synchronization/mutex.h"
#include "absl/synchronization/notification.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "upb/mem/alloc.h"
#include "upb/mem/arena.hpp"

#include "upb/port/def.inc"

namespace {

// Custom allocator structure that tracks allocation count and cleanup status
struct CustomAlloc {
  upb_alloc alloc;  // Base allocator structure
  int counter;      // Tracks number of active allocations
  bool ran_cleanup; // Flag indicating if cleanup was executed
};

// Custom allocation function that increments/decrements counter based on operation
void* CustomAllocFunc(upb_alloc* alloc, void* ptr, size_t oldsize,
                      size_t size) {
  CustomAlloc* custom_alloc = reinterpret_cast<CustomAlloc*>(alloc);
  if (size == 0) {
    custom_alloc->counter--;  // Decrement for deallocation
  } else {
    custom_alloc->counter++;  // Increment for allocation
  }
  return upb_alloc_global.func(alloc, ptr, oldsize, size);
}

// Cleanup function that verifies all allocations were freed
void CustomAllocCleanup(upb_alloc* alloc) {
  CustomAlloc* custom_alloc = reinterpret_cast<CustomAlloc*>(alloc);
  EXPECT_THAT(custom_alloc->counter, 0);  // Verify no leaks
  custom_alloc->ran_cleanup = true;       // Mark cleanup as executed
}

// Test case for arena with custom allocator and cleanup
TEST(ArenaTest, ArenaWithAllocCleanup) {
  CustomAlloc alloc = {{&CustomAllocFunc}, 0, false};
  upb_Arena* arena =
      upb_Arena_Init(nullptr, 0, reinterpret_cast<upb_alloc*>(&alloc));
  EXPECT_EQ(alloc.counter, 1);  // Initial allocation should increment counter
  upb_Arena_SetAllocCleanup(arena, CustomAllocCleanup);
  upb_Arena_Free(arena);
  EXPECT_TRUE(alloc.ran_cleanup);  // Verify cleanup was called
}

// Structure to track allocation sizes
struct SizeTracker {
  upb_alloc alloc;              // Base allocator
  upb_alloc* delegate_alloc;    // Delegate allocator
  absl::flat_hash_map<void*, size_t>* sizes;  // Map of pointer to allocation size
};

static_assert(std::is_standard_layout<SizeTracker>());

// Allocation function that verifies and tracks allocation sizes
static void* size_checking_allocfunc(upb_alloc* alloc, void* ptr,
                                     size_t oldsize, size_t size) {
  SizeTracker* size_alloc = reinterpret_cast<SizeTracker*>(alloc);
  void* result = size_alloc->delegate_alloc->func(alloc, ptr, oldsize, size);
  if (ptr != nullptr) {
    UPB_ASSERT(size_alloc->sizes->at(ptr) == oldsize);  // Verify old size
    size_alloc->sizes->erase(ptr);                     // Remove old entry
  }
  if (result != nullptr) {
    size_alloc->sizes->emplace(result, size);  // Track new allocation
  }
  return result;
}

// Test case for sized allocations and frees
TEST(ArenaTest, SizedFree) {
  absl::flat_hash_map<void*, size_t> sizes;
  SizeTracker alloc;
  alloc.alloc.func = size_checking_allocfunc;
  alloc.delegate_alloc = &upb_alloc_global;
  alloc.sizes = &sizes;

  char initial_block[1000];

  upb_Arena* arena = upb_Arena_Init(initial_block, 1000, &alloc.alloc);
  (void)upb_Arena_Malloc(arena, 500);  // Allocate within initial block
  void* to_resize = upb_Arena_Malloc(arena, 2000);  // Allocate beyond initial block
  void* resized = upb_Arena_Realloc(arena, to_resize, 2000, 4000);  // Resize allocation
  upb_Arena_ShrinkLast(arena, resized, 4000, 1);  // Shrink allocation
  EXPECT_GT(sizes.size(), 0);  // Verify allocations are tracked
  upb_Arena_Free(arena);
  EXPECT_EQ(sizes.size(), 0);  // Verify all allocations were freed
}

// Test case for extending allocations within arena
TEST(ArenaTest, TryExtend) {
  upb_Arena* arena = upb_Arena_Init(nullptr, 1024, &upb_alloc_global);
  void* alloc = upb_Arena_Malloc(arena, 512);
  ASSERT_TRUE(upb_Arena_TryExtend(arena, alloc, 512, 700));  // Extend within block
  ASSERT_TRUE(upb_Arena_TryExtend(arena, alloc, 700, 750));  // Further extend

  ASSERT_FALSE(upb_Arena_TryExtend(arena, alloc, 750, 10000));  // Fail to extend beyond block
  (void)upb_Arena_Malloc(arena, 1);  // Allocate more to fragment arena

  ASSERT_FALSE(upb_Arena_TryExtend(arena, alloc, 750, 900));  // Fail to extend after fragmentation
  upb_Arena_Free(arena);
}

// Test case for realloc fast path (in-place reallocation)
TEST(ArenaTest, ReallocFastPath) {
  upb_Arena* arena = upb_Arena_Init(nullptr, 4096, &upb_alloc_global);
  void* initial = upb_Arena_Malloc(arena, 512);
  uintptr_t initial_allocated = upb_Arena_SpaceAllocated(arena, nullptr);
  void* extend = upb_Arena_Realloc(arena, initial, 512, 1024);  // Realloc in-place
  uintptr_t extend_allocated = upb_Arena_SpaceAllocated(arena, nullptr);
  EXPECT_EQ(initial, extend);  // Verify same pointer (in-place)
  EXPECT_EQ(initial_allocated, extend_allocated);  // Verify no new allocation
  upb_Arena_Free(arena);
}

// Test case for arena size hints
TEST(ArenaTest, SizeHint) {
  absl::flat_hash_map<void*, size_t> sizes;
  SizeTracker alloc;
  alloc.alloc.func = size_checking_allocfunc;
  alloc.delegate_alloc = &upb_alloc_global;
  alloc.sizes = &sizes;

  upb_Arena* arena = upb_Arena_Init(nullptr, 2459, &alloc.alloc);
  EXPECT_EQ(sizes.size(), 1);  // Initial block allocation
  EXPECT_NE(upb_Arena_Malloc(arena, 2459), nullptr);  // Allocate within initial block
  EXPECT_EQ(sizes.size(), 1);  // No new allocation
  EXPECT_NE(upb_Arena_Malloc(arena, 500), nullptr);  // Allocate more
  EXPECT_EQ(sizes.size(), 2);  // New allocation required
  upb_Arena_Free(arena);
  EXPECT_EQ(sizes.size(), 0);  // All freed
}

// Test fixture for measuring arena overhead
class OverheadTest {
 public:
  OverheadTest(const OverheadTest&) = delete;
  OverheadTest& operator=(const OverheadTest&) = delete;

  // Initialize with optional initial block size and max block size
  explicit OverheadTest(size_t first = 0, size_t max_block_size = 0) {
    if (max_block_size) {
      upb_Arena_SetMaxBlockSize(max_block_size);
    }
    alloc_.alloc.func = size_checking_allocfunc;
    alloc_.delegate_alloc = &upb_alloc_global;
    alloc_.sizes = &sizes_;
    arena_ = upb_Arena_Init(nullptr, first, &alloc_.alloc);
    arena_alloced_ = 0;
    arena_alloc_count_ = 0;
  }

  // Allocate memory and track statistics
  void Alloc(size_t size) {
    upb_Arena_Malloc(arena_, size);
    arena_alloced_ += size;
    arena_alloc_count_++;
  }

  // Get total space allocated by arena
  uintptr_t SpaceAllocated() {
    return upb_Arena_SpaceAllocated(arena_, nullptr);
  }

  // Calculate waste percentage (overhead)
  double WastePct() {
    uintptr_t backing_alloced = upb_Arena_SpaceAllocated(arena_, nullptr);
    double waste = backing_alloced - arena_alloced_;
    return waste / backing_alloced;
  }

  // Calculate amortized allocation count
  double AmortizedAlloc() {
    return ((double)sizes_.size()) / arena_alloc_count_;
  }

  ~OverheadTest() {
    upb_Arena_Free(arena_);
    upb_Arena_SetMaxBlockSize(UPB_PRIVATE(kUpbDefaultMaxBlockSize));
  }
  upb_Arena* arena_;

 protected:
  absl::flat_hash_map<void*, size_t> sizes_;  // Tracks allocation sizes
  SizeTracker alloc_;                         // Custom allocator
  uintptr_t arena_alloced_;                   // Total requested allocation size
  uintptr_t arena_alloc_count_;               // Number of allocations
};

// Test case for overhead with large block followed by small allocations
TEST(OverheadTest, SingleMassiveBlockThenLittle) {
  OverheadTest test;

  // Small allocations
  for (int i = 0; i < 4; i++) {
    test.Alloc(32);
  }

  // Large allocation followed by more small allocations
  test.Alloc(16000);
  for (int i = 0; i < 50; i++) {
    test.Alloc(64);
  }
  if (!UPB_ASAN) {
#ifdef __ANDROID__
    EXPECT_NEAR(test.WastePct(), 0.075, 0.025);  // Expected waste percentage
    EXPECT_NEAR(test.AmortizedAlloc(), 0.09, 0.025);  // Expected amortized allocs
#else
    EXPECT_NEAR(test.WastePct(), 0.08, 0.025);
    EXPECT_NEAR(test.AmortizedAlloc(), 0.09, 0.025);
#endif
  }
}

// Test case for overhead with alternating small and large blocks
TEST(OverheadTest, Overhead_AlternatingSmallLargeBlocks) {
  OverheadTest test(512, 4096);  // Initial block size 512, max block size 4096
  for (int i = 0; i < 100; i++) {
    test.Alloc(5000);  // Large allocation
    test.Alloc(64);    // Small allocation
  }
  if (!UPB_ASAN) {
    EXPECT_NEAR(test.WastePct(), 0.007, 0.0025);  // Low waste expected
    EXPECT_NEAR(test.AmortizedAlloc(), 0.52, 0.025);
  }
}

// Test case for overhead with allocations near max block size
TEST(OverheadTest, PartialMaxBlocks) {
  OverheadTest test(512, 4096);
  for (int i = 0; i < 10; i++) {
    test.Alloc(2096 + i);  // Allocations slightly larger than half max block size
  }
  if (!UPB_ASAN) {
    EXPECT_NEAR(test.WastePct(), 0.16, 0.025);  // Moderate waste expected
    EXPECT_NEAR(test.AmortizedAlloc(), 1.1, 0.25);
  }
}

// Test case for small blocks larger than initial block size
TEST(OverheadTest, SmallBlocksLargerThanInitial) {
  OverheadTest test;
  size_t initial_block_size = upb_Arena_SpaceAllocated(test.arena_, nullptr);
  for (int i = 0; i < 10; i++) {
    test.Alloc(initial_block_size * 2 + 1);  // Allocations larger than initial block
  }
  if (!UPB_ASAN && sizeof(void*) == 8) {
    EXPECT_NEAR(test.WastePct(), 0.37, 0.025);  // Higher waste expected
    EXPECT_NEAR(test.AmortizedAlloc(), 0.5, 0.025);
  }
}

// Test case for many small blocks larger than initial block size
TEST(OverheadTest, SmallBlocksLargerThanInitial_many) {
  OverheadTest test;
  size_t initial_block_size = upb_Arena_SpaceAllocated(test.arena_, nullptr);
  for (int i = 0; i < 100; i++) {
    test.Alloc(initial_block_size * 2 + 1);  // Many allocations
  }
  if (!UPB_ASAN) {
#ifdef __ANDROID__
    EXPECT_NEAR(test.WastePct(), 0.09, 0.025);  // Waste decreases with many allocs
    EXPECT_NEAR(test.AmortizedAlloc(), 0.12, 0.025);
#else
    EXPECT_NEAR(test.WastePct(), 0.12, 0.03);
    EXPECT_NEAR(test.AmortizedAlloc(), 0.08, 0.025);
#endif
  }
  for (int i = 0; i < 900; i++) {
    test.Alloc(initial_block_size * 2 + 1);  // Even more allocations
  }
  if (!UPB_ASAN) {
#ifdef __ANDROID__
    EXPECT_NEAR(test.WastePct(), 0.05, 0.03);  // Waste decreases further
    EXPECT_NEAR(test.AmortizedAlloc(), 0.08, 0.025);
#else
    EXPECT_NEAR(test.WastePct(), 0.04, 0.025);
    EXPECT_NEAR(test.AmortizedAlloc(), 0.05, 0.025);
#endif
  }
}

// Test case for default max block size behavior
TEST(OverheadTest, DefaultMaxBlockSize) {
  OverheadTest test;

  for (int i = 0; i < 600; ++i) {
    test.Alloc(1024);  // Many 1KB allocations
  }
  EXPECT_LE(test.SpaceAllocated(), 700 * 1024);  // Verify total within expected bounds
}

// Test case for fusing arenas
TEST(ArenaTest, ArenaFuse) {
  upb_Arena* arena1 = upb_Arena_New();
  upb_Arena* arena2 = upb_Arena_New();

  EXPECT_TRUE(upb_Arena_Fuse(arena1, arena2));  // Fuse should succeed

  upb_Arena_Free(arena1);
  upb_Arena_Free(arena2);
}

// Test case for fusing arenas with initial blocks
TEST(ArenaTest, FuseWithInitialBlock) {
  char buf1[1024];
  char buf2[1024];
  upb_Arena* arenas[] = {upb_Arena_Init(buf1, 1024, &upb_alloc_global),
                         upb_Arena_Init(buf2, 1024, &upb_alloc_global),
                         upb_Arena_Init(nullptr, 0, &upb_alloc_global)};
  int size = sizeof(arenas) / sizeof(arenas[0]);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (i == j) {
        EXPECT_TRUE(upb_Arena_Fuse(arenas[i], arenas[j]));  // Self-fuse should succeed
      } else {
        EXPECT_FALSE(upb_Arena_Fuse(arenas[i], arenas[j]));  // Fuse with initial blocks should fail
      }
    }
  }

  for (int i = 0; i < size; ++i) upb_Arena_Free(arenas[i]);
}

// Environment class for multi-threaded testing
class Environment {
 public:
  // Randomly create or free an arena
  void RandomNewFree(absl::BitGen& gen, size_t min_index = 0) {
    auto a = std::make_shared<const upb::Arena>();
    SwapRandomArena(gen, a, min_index);
  }

  // Randomly increment and decrement reference count
  void RandomIncRefCount(absl::BitGen& gen) {
    std::shared_ptr<const upb::Arena> a = RandomNonNullArena(gen);
    upb_Arena_IncRefFor(a->ptr(), nullptr);
    upb_Arena_DecRefFor(a->ptr(), nullptr);
  }

  // Randomly fuse two arenas
  void RandomFuse(absl::BitGen& gen) {
    std::shared_ptr<const upb::Arena> a = RandomNonNullArena(gen);
    std::shared_ptr<const upb::Arena> b = RandomNonNullArena(gen);
    EXPECT_TRUE(upb_Arena_Fuse(a->ptr(), b->ptr()));
  }

  // Randomly perform an operation (new/free or fuse)
  void RandomPoke(absl::BitGen&