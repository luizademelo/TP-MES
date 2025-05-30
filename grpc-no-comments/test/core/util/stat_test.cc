
// Copyright 2020 gRPC authors.

#include "src/core/util/stat.h"

#include <grpc/support/alloc.h>
#include <stdio.h>

#include <memory>

#include "gtest/gtest.h"
#include "src/core/util/tmpfile.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {
namespace {

TEST(STAT, GetTimestampOnTmpFile) {

  FILE* tmp = nullptr;
  char* tmp_name;
  tmp = gpr_tmpfile("prefix", &tmp_name);
  ASSERT_NE(tmp_name, nullptr);
  ASSERT_NE(tmp, nullptr);
  fclose(tmp);

  time_t timestamp = 0;
  absl::Status status = GetFileModificationTime(tmp_name, &timestamp);
  EXPECT_EQ(status.code(), absl::StatusCode::kOk);
  EXPECT_GT(timestamp, 0);

  remove(tmp_name);
  gpr_free(tmp_name);
}

TEST(STAT, GetTimestampOnFailure) {
  time_t timestamp = 0;
  absl::Status status = GetFileModificationTime("/DOES_NOT_EXIST", &timestamp);
  EXPECT_EQ(status.code(), absl::StatusCode::kInternal);

  EXPECT_EQ(timestamp, 0);
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
