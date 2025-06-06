// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/arena_promise.h"

#include <grpc/event_engine/memory_allocator.h>

#include <array>
#include <memory>

#include "gtest/gtest.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/ref_counted_ptr.h"
#include "test/core/promise/test_context.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {

TEST(ArenaPromiseTest, DefaultInitializationYieldsNoValue) {
  auto arena = SimpleArenaAllocator()->MakeArena();
  TestContext<Arena> context(arena.get());
  ArenaPromise<int> p;
  EXPECT_FALSE(p.has_value());
}

TEST(ArenaPromiseTest, AllocatedWorks) {
  ExecCtx exec_ctx;
  auto arena = SimpleArenaAllocator()->MakeArena();
  TestContext<Arena> context(arena.get());
  int x = 42;
  ArenaPromise<int> p([x] { return Poll<int>(x); });
  EXPECT_TRUE(p.has_value());
  EXPECT_EQ(p(), Poll<int>(42));
  p = ArenaPromise<int>([] { return Poll<int>(43); });
  EXPECT_EQ(p(), Poll<int>(43));
}

TEST(ArenaPromiseTest, DestructionWorks) {
  ExecCtx exec_ctx;
  auto arena = SimpleArenaAllocator()->MakeArena();
  TestContext<Arena> context(arena.get());
  auto x = std::make_shared<int>(42);
  auto p = ArenaPromise<int>([x] { return Poll<int>(*x); });
  ArenaPromise<int> q(std::move(p));
  EXPECT_EQ(q(), Poll<int>(42));
}

TEST(ArenaPromiseTest, MoveAssignmentWorks) {
  ExecCtx exec_ctx;
  auto arena = SimpleArenaAllocator()->MakeArena();
  TestContext<Arena> context(arena.get());
  auto x = std::make_shared<int>(42);
  auto p = ArenaPromise<int>([x] { return Poll<int>(*x); });
  p = ArenaPromise<int>();
}

TEST(ArenaPromiseTest, AllocatedUniquePtrWorks) {
  ExecCtx exec_ctx;
  auto arena = SimpleArenaAllocator()->MakeArena();
  TestContext<Arena> context(arena.get());
  std::array<int, 5> garbage = {0, 1, 2, 3, 4};
  auto freer = [garbage](int* p) { free(p + garbage[0]); };
  using Ptr = std::unique_ptr<int, decltype(freer)>;
  Ptr x(([] {
          int* p = static_cast<decltype(p)>(malloc(sizeof(*p)));
          *p = 42;
          return p;
        })(),
        freer);
  static_assert(sizeof(x) > sizeof(arena_promise_detail::ArgType),
                "This test assumes the unique ptr will go down the allocated "
                "path for ArenaPromise");
  ArenaPromise<Ptr> initial_promise(
      [x = std::move(x)]() mutable { return Poll<Ptr>(std::move(x)); });
  ArenaPromise<Ptr> p(std::move(initial_promise));
  EXPECT_EQ(*p().value(), 42);
}

}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment give_me_a_name(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
