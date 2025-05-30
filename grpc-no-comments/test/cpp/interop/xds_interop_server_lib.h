
// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CPP_INTEROP_XDS_INTEROP_SERVER_LIB_H
#define GRPC_TEST_CPP_INTEROP_XDS_INTEROP_SERVER_LIB_H
#include <grpcpp/server.h>

#include <optional>

#include "absl/strings/string_view.h"

namespace grpc {
namespace testing {

std::optional<grpc::Status> GetStatusForRpcBehaviorMetadata(
    absl::string_view header_value, absl::string_view hostname);

void RunServer(bool secure_mode, int port, const int maintenance_port,
               absl::string_view hostname, absl::string_view server_id,
               const std::function<void(Server*)>& server_callback);

}
}

#endif
