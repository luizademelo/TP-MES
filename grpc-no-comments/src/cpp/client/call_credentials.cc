// Copyright 2024 The gRPC Authors

#include "src/core/credentials/call/call_credentials.h"

#include <grpc/support/port_platform.h>
#include <grpcpp/security/credentials.h>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"

namespace grpc {

CallCredentials::CallCredentials(grpc_call_credentials* c_creds)
    : c_creds_(c_creds) {
  CHECK_NE(c_creds, nullptr);
}

CallCredentials::~CallCredentials() { grpc_call_credentials_release(c_creds_); }

grpc::string CallCredentials::DebugString() {
  return absl::StrCat("CallCredentials{", c_creds_->debug_string(), "}");
}

bool CallCredentials::ApplyToCall(grpc_call* call) {
  return grpc_call_set_credentials(call, c_creds_) == GRPC_CALL_OK;
}

}
