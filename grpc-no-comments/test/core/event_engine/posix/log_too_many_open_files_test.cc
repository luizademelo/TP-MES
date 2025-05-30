// Copyright 2023 gRPC authors.

#include <errno.h>
#include <sys/socket.h>

#include <string>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/event_engine/posix_engine/tcp_socket_utils.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/util/strerror.h"
#include "test/core/test_util/test_config.h"

using ::grpc_event_engine::experimental::PosixSocketWrapper;

TEST(LogTooManyOpenFilesTest, MainTest) {
  const auto mock_socket_factory = [](int, int, int) {
    errno = EMFILE;
    return -1;
  };
  auto addr = grpc_event_engine::experimental::URIToResolvedAddress(
      "ipv4:127.0.0.1:80");
  ASSERT_TRUE(addr.ok());
  PosixSocketWrapper::DSMode dsmode;
  absl::StatusOr<PosixSocketWrapper> result =
      PosixSocketWrapper::CreateDualStackSocket(mock_socket_factory, *addr,
                                                SOCK_STREAM, AF_INET, dsmode);
  EXPECT_FALSE(result.ok());
  std::string emfile_message = grpc_core::StrError(EMFILE);
  EXPECT_THAT(result.status().message(), ::testing::HasSubstr(emfile_message));
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
