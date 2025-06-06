
// Copyright 2019 gRPC authors.

#include <grpc/grpc.h>

#include <string>

#include "absl/log/check.h"
#include "gtest/gtest.h"
#include "src/core/server/server.h"
#include "test/core/bad_client/bad_client.h"
#include "test/core/test_util/test_config.h"

#define APPEND_BUFFER(string, to_append) \
  ((string).append((to_append), sizeof(to_append) - 1))

namespace {

void verifier(grpc_server* server, grpc_completion_queue* cq,
              void* ) {
  while (grpc_core::Server::FromC(server)->HasOpenConnections()) {
    CHECK(grpc_completion_queue_next(
              cq, grpc_timeout_milliseconds_to_deadline(20), nullptr)
              .type == GRPC_QUEUE_TIMEOUT);
  }
}

void FrameVerifier(const std::string& attack_vector) {
  grpc_bad_client_arg args[2];
  args[0] = connection_preface_arg;
  args[1].client_validator = nullptr;
  args[1].client_payload = attack_vector.c_str();
  args[1].client_payload_length = attack_vector.size();
  grpc_run_bad_client_test(verifier, args, 2, GRPC_BAD_CLIENT_DISCONNECT);
}

TEST(OutOfBounds, MaxFrameSizeDataFrame) {
  std::string out_of_bounds_data;

  APPEND_BUFFER(out_of_bounds_data, "\x01\x00\x00\x00\x00\x00\x00\x00\x01");
  out_of_bounds_data.append(1 << 16, 'a');
  FrameVerifier(out_of_bounds_data);
}

TEST(OutOfBounds, BadSizePriorityFrame) {
  std::string bad_size_priority_frame;

  APPEND_BUFFER(bad_size_priority_frame,
                "\x00\x00\x03\x02\x00\x00\x00\x00\x01"
                "\x11\x11\x12");
  FrameVerifier(bad_size_priority_frame);
}

TEST(OutOfBounds, BadSizeRstStream) {
  std::string bad_size_rst_stream;

  APPEND_BUFFER(bad_size_rst_stream,
                "\x00\x00\x02\x03\x00\x00\x00\x00\x01"
                "\x11\x11");
  FrameVerifier(bad_size_rst_stream);
}

TEST(OutOfBounds, BadSizeSettings) {
  std::string bad_size_settings;

  APPEND_BUFFER(bad_size_settings,
                "\x00\x00\x05\x04\x00\x00\x00\x00\x00"
                "\x11\x11\x11\x11\x11");
  FrameVerifier(bad_size_settings);
}

TEST(OutOfBounds, BadSizePing) {
  std::string bad_size_ping;

  APPEND_BUFFER(bad_size_ping,
                "\x00\x00\x05\x06\x00\x00\x00\x00\x00"
                "\x11\x11\x11\x11\x11");
  FrameVerifier(bad_size_ping);
}

TEST(OutOfBounds, WindowUpdate) {
  std::string bad_size_window_update;

  APPEND_BUFFER(bad_size_window_update,
                "\x00\x00\x01\x08\x00\x00\x00\x00\x00"
                "\x11");
  FrameVerifier(bad_size_window_update);
}

}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int retval = RUN_ALL_TESTS();
  grpc_shutdown();
  return retval;
}
