
// Copyright 2015 gRPC authors.

#include "test/cpp/interop/server_helper.h"

#include <grpcpp/security/server_credentials.h>

#include <memory>

#include "absl/flags/declare.h"
#include "absl/flags/flag.h"
#include "src/core/lib/surface/call_test_only.h"
#include "src/core/lib/transport/transport.h"
#include "test/cpp/util/test_credentials_provider.h"

ABSL_DECLARE_FLAG(bool, use_alts);
ABSL_DECLARE_FLAG(bool, use_tls);
ABSL_DECLARE_FLAG(std::string, custom_credentials_type);

namespace grpc {
namespace testing {

std::shared_ptr<ServerCredentials> CreateInteropServerCredentials() {
  if (!absl::GetFlag(FLAGS_custom_credentials_type).empty()) {
    return GetCredentialsProvider()->GetServerCredentials(
        absl::GetFlag(FLAGS_custom_credentials_type));
  } else if (absl::GetFlag(FLAGS_use_alts)) {
    return GetCredentialsProvider()->GetServerCredentials(kAltsCredentialsType);
  } else if (absl::GetFlag(FLAGS_use_tls)) {
    return GetCredentialsProvider()->GetServerCredentials(kTlsCredentialsType);
  } else {
    return GetCredentialsProvider()->GetServerCredentials(
        kInsecureCredentialsType);
  }
}

InteropServerContextInspector::InteropServerContextInspector(
    const grpc::ServerContext& context)
    : context_(context) {}

grpc_compression_algorithm
InteropServerContextInspector::GetCallCompressionAlgorithm() const {
  return grpc_call_test_only_get_compression_algorithm(context_.call_.call);
}

uint32_t InteropServerContextInspector::GetEncodingsAcceptedByClient() const {
  return grpc_call_test_only_get_encodings_accepted_by_peer(
      context_.call_.call);
}

bool InteropServerContextInspector::WasCompressed() const {
  return (grpc_call_test_only_get_message_flags(context_.call_.call) &
          GRPC_WRITE_INTERNAL_COMPRESS) ||
         (grpc_call_test_only_get_message_flags(context_.call_.call) &
          GRPC_WRITE_INTERNAL_TEST_ONLY_WAS_COMPRESSED);
}

std::shared_ptr<const AuthContext>
InteropServerContextInspector::GetAuthContext() const {
  return context_.auth_context();
}

bool InteropServerContextInspector::IsCancelled() const {
  return context_.IsCancelled();
}

}
}
