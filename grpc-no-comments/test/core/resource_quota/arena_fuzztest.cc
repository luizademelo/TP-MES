// Copyright 2025 gRPC authors.

#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/util/match.h"

namespace grpc_core {
namespace {

struct Pop {};
struct Push {
  int value;
};
using QueueOp = std::variant<Pop, Push>;

void ArenaSpscIsAQueue(std::vector<QueueOp> ops) {
  auto arena = SimpleArenaAllocator()->MakeArena();
  auto spsc = ArenaSpsc<int>(arena.get());
  std::queue<int> q;

  for (const auto& op : ops) {
    Match(
        op,
        [&](Pop) {
          if (q.empty()) {
            EXPECT_FALSE(spsc.Pop().has_value());
          } else {
            EXPECT_EQ(spsc.Pop().value(), q.front());
            q.pop();
          }
        },
        [&](Push push) {
          q.push(push.value);
          spsc.Push(push.value);
        });
  }
}
FUZZ_TEST(MyTestSuite, ArenaSpscIsAQueue);

struct Nothing {};

void ArenaSpscDoesNotLeak(std::vector<bool> ops) {
  auto arena = SimpleArenaAllocator()->MakeArena();
  auto spsc = ArenaSpsc<std::shared_ptr<Nothing>>(arena.get());
  std::queue<std::shared_ptr<Nothing>> q;

  for (const auto& op : ops) {

    if (op) {
      auto ptr = std::make_shared<Nothing>();
      q.push(ptr);
      spsc.Push(ptr);
    } else {
      if (q.empty()) {
        EXPECT_FALSE(spsc.Pop().has_value());
      } else {
        EXPECT_EQ(spsc.Pop().value(), q.front());
        q.pop();
      }
    }
  }
}
FUZZ_TEST(MyTestSuite, ArenaSpscDoesNotLeak);

}
}
