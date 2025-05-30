
// Copyright 2018 gRPC authors.

#include <grpcpp/impl/service_type.h>
#include <grpcpp/server_builder.h>

#include <sstream>

#include "absl/flags/flag.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "test/core/test_util/test_config.h"
#include "test/core/tsi/alts/fake_handshaker/fake_handshaker_server.h"
#include "test/cpp/util/test_config.h"

ABSL_FLAG(int32_t, handshaker_port, 55056,
          "TCP port on which the fake handshaker server listens to.");
ABSL_FLAG(std::string, peer_identity, "peer_identity", "The peer identity.");

static void RunFakeHandshakerServer(const std::string& server_address,
                                    const std::string& peer_identity) {
  std::unique_ptr<grpc::Service> service =
      grpc::gcp::CreateFakeHandshakerService(peer_identity);
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(service.get());
  LOG(INFO) << "Fake handshaker server listening on " << server_address;
  std::unique_ptr<grpc::Server> server = builder.BuildAndStart();
  server->Wait();
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, true);

  CHECK_NE(absl::GetFlag(FLAGS_handshaker_port), 0);
  std::ostringstream server_address;
  server_address << "[::1]:" << absl::GetFlag(FLAGS_handshaker_port);

  RunFakeHandshakerServer(server_address.str(),
                          absl::GetFlag(FLAGS_peer_identity));
  return 0;
}
