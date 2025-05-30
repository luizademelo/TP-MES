// Copyright 2024 gRPC authors.

#include "src/core/lib/surface/call_utils.h"

#include <grpc/grpc.h>

#include <initializer_list>

#include "gtest/gtest.h"

namespace grpc_core {

TEST(CallUtils, AreWriteFlagsValid) {
  EXPECT_TRUE(AreWriteFlagsValid(0));
  EXPECT_TRUE(AreWriteFlagsValid(GRPC_WRITE_BUFFER_HINT));
  EXPECT_TRUE(AreWriteFlagsValid(GRPC_WRITE_NO_COMPRESS));
  EXPECT_FALSE(AreWriteFlagsValid(0xffffffff));
}

TEST(CallUtils, AreInitialMetadataFlagsValid) {
  EXPECT_TRUE(AreInitialMetadataFlagsValid(0));
  EXPECT_TRUE(
      AreInitialMetadataFlagsValid(GRPC_INITIAL_METADATA_WAIT_FOR_READY));
  EXPECT_TRUE(AreInitialMetadataFlagsValid(GRPC_WRITE_THROUGH));
  EXPECT_FALSE(AreInitialMetadataFlagsValid(0xffffffff));
}

namespace {
template <typename... T>
std::vector<grpc_op> TestOps(T... ops) {
  std::vector<grpc_op> out;
  auto add_op = [&out](grpc_op_type type) {
    grpc_op op;
    op.op = type;
    out.push_back(op);
    return 1;
  };
  (add_op(ops), ...);
  return out;
}
}

TEST(BatchOpIndex, Basic) {
  const auto ops = TestOps(GRPC_OP_SEND_INITIAL_METADATA, GRPC_OP_SEND_MESSAGE,
                           GRPC_OP_SEND_CLOSE_FROM_CLIENT);
  BatchOpIndex idx(ops.data(), ops.size());
  EXPECT_EQ(idx.op(GRPC_OP_SEND_INITIAL_METADATA), &ops[0]);
  EXPECT_EQ(idx.op(GRPC_OP_SEND_MESSAGE), &ops[1]);
  EXPECT_EQ(idx.op(GRPC_OP_SEND_CLOSE_FROM_CLIENT), &ops[2]);
  EXPECT_EQ(idx.op(GRPC_OP_SEND_STATUS_FROM_SERVER), nullptr);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
