// Copyright 2021 gRPC authors.

#include <grpc/event_engine/memory_allocator.h>
#include <grpc/status.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/try_seq.h"

namespace grpc_core {

struct TestMap : public MetadataMap<TestMap, GrpcStatusMetadata> {
  using MetadataMap<TestMap, GrpcStatusMetadata>::MetadataMap;
};

TEST(PromiseTest, SucceedAndThenFail) {
  Poll<TestMap> r = TrySeq(
      [] {
        TestMap m;
        m.Set(GrpcStatusMetadata(), GRPC_STATUS_OK);
        return m;
      },
      []() {
        TestMap m;
        m.Set(GrpcStatusMetadata(), GRPC_STATUS_UNAVAILABLE);
        return m;
      })();
  EXPECT_EQ(r.value().get(GrpcStatusMetadata()), GRPC_STATUS_UNAVAILABLE);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
