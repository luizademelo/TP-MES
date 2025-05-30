
// Copyright 2023 gRPC authors.

#include "src/core/util/directory_reader.h"

#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

static constexpr absl::string_view kCrlDirectory =
    "test/core/tsi/test_creds/crl_data/crls/";

namespace grpc_core {
namespace testing {
namespace {

TEST(DirectoryReader, CanListFiles) {
  auto reader = MakeDirectoryReader(kCrlDirectory);
  std::vector<std::string> contents;
  absl::Status status = reader->ForEach([&](absl::string_view filename) {
    contents.push_back(std::string(filename));
  });
  ASSERT_TRUE(status.ok()) << status;

  EXPECT_THAT(contents,
              ::testing::IsSupersetOf({"ab06acdd.r0", "b9322cac.r0",
                                       "current.crl", "intermediate.crl"}));
}

TEST(DirectoryReader, NonexistentDirectory) {
  auto reader = MakeDirectoryReader("DOES_NOT_EXIST");
  absl::Status status = reader->ForEach([](absl::string_view) {});
  ASSERT_FALSE(status.ok()) << status;
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
