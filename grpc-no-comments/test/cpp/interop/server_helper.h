
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_INTEROP_SERVER_HELPER_H
#define GRPC_TEST_CPP_INTEROP_SERVER_HELPER_H

#include <grpc/compression.h>
#include <grpc/support/atm.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <condition_variable>
#include <memory>

namespace grpc {
namespace testing {

std::shared_ptr<ServerCredentials> CreateInteropServerCredentials();

class InteropServerContextInspector {
 public:
  explicit InteropServerContextInspector(const grpc::ServerContext& context);

  std::shared_ptr<const AuthContext> GetAuthContext() const;
  bool IsCancelled() const;
  grpc_compression_algorithm GetCallCompressionAlgorithm() const;
  uint32_t GetEncodingsAcceptedByClient() const;
  bool WasCompressed() const;

 private:
  const grpc::ServerContext& context_;
};

namespace interop {

extern gpr_atm g_got_sigint;

struct ServerStartedCondition {
  std::mutex mutex;
  std::condition_variable condition;
  bool server_started = false;
};

void RunServer(const std::shared_ptr<ServerCredentials>& creds);

void RunServer(const std::shared_ptr<ServerCredentials>& creds, int port,
               ServerStartedCondition* server_started_condition);

void RunServer(
    const std::shared_ptr<ServerCredentials>& creds,
    std::unique_ptr<std::vector<std::unique_ptr<ServerBuilderOption>>>
        server_options);

void RunServer(
    const std::shared_ptr<ServerCredentials>& creds, const int port,
    ServerStartedCondition* server_started_condition,
    std::unique_ptr<std::vector<std::unique_ptr<grpc::ServerBuilderOption>>>
        server_options);

}
}
}

#endif
