// Copyright 2021 gRPC authors.

#include "src/core/call/call_finalization.h"

#include <grpc/event_engine/memory_allocator.h>

#include <memory>
#include <string>

#include "absl/strings/str_cat.h"
#include "gtest/gtest.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/ref_counted_ptr.h"
#include "test/core/promise/test_context.h"

namespace grpc_core {

TEST(CallFinalizationTest, Works) {
  auto arena = SimpleArenaAllocator()->MakeArena();
  std::string evidence;
  TestContext<Arena> context(arena.get());
  CallFinalization finalization;
  auto p = std::make_shared<int>(42);
  finalization.Add([&evidence, p](const grpc_call_final_info* final_info) {
    evidence += absl::StrCat("FIRST", final_info->error_string, *p, "\n");
  });
  finalization.Add([&evidence, p](const grpc_call_final_info* final_info) {
    evidence += absl::StrCat("SECOND", final_info->error_string, *p, "\n");
  });
  grpc_call_final_info final_info{};
  final_info.error_string = "123";
  finalization.Run(&final_info);
  EXPECT_EQ(evidence, "SECOND12342\nFIRST12342\n");
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
