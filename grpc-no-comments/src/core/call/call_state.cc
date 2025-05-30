// Copyright 2024 gRPC authors.

#include "src/core/call/call_state.h"

namespace grpc_core {

std::string CallState::DebugString() const {
  return absl::StrCat(
      "client_to_server_pull_state:", client_to_server_pull_state_,
      " client_to_server_push_state:", client_to_server_push_state_,
      " server_to_client_pull_state:", server_to_client_pull_state_,
      " server_to_client_message_push_state:", server_to_client_push_state_,
      " server_trailing_metadata_state:", server_trailing_metadata_state_,
      client_to_server_push_waiter_.DebugString(),
      " server_to_client_push_waiter:",
      server_to_client_push_waiter_.DebugString(),
      " client_to_server_pull_waiter:",
      client_to_server_pull_waiter_.DebugString(),
      " server_to_client_pull_waiter:",
      server_to_client_pull_waiter_.DebugString(),
      " server_trailing_metadata_waiter:",
      server_trailing_metadata_waiter_.DebugString());
}

static_assert(sizeof(CallState) <= 16, "CallState too large");

}
