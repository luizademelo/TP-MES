Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary gRPC headers
#include <grpc/compression.h>
#include <grpc/grpc.h>
#include <grpc/impl/compression_types.h>
#include <grpc/status.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/impl/interceptor_common.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/client_interceptor.h>
#include <stdlib.h>

// Standard C++ includes
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Third-party includes
#include "absl/log/check.h"
#include "absl/strings/str_format.h"
#include "src/core/util/crash.h"

namespace grpc {

// Forward declaration
class Channel;

// Default implementation of GlobalCallbacks interface for ClientContext
class DefaultGlobalClientCallbacks final
    : public ClientContext::GlobalCallbacks {
 public:
  ~DefaultGlobalClientCallbacks() override {}
  // Empty implementations of callback methods
  void DefaultConstructor(ClientContext* ) override {}
  void Destructor(ClientContext* ) override {}
};

// Global callback instances
static DefaultGlobalClientCallbacks* g_default_client_callbacks =
    new DefaultGlobalClientCallbacks();
static ClientContext::GlobalCallbacks* g_client_callbacks =
    g_default_client_callbacks;

// ClientContext constructor initializes member variables
ClientContext::ClientContext()
    : initial_metadata_received_(false),
      wait_for_ready_(false),
      wait_for_ready_explicitly_set_(false),
      call_(nullptr),
      call_canceled_(false),
      // Set default deadline to infinity
      deadline_(gpr_inf_future(GPR_CLOCK_REALTIME)),
      census_context_(nullptr),
      propagate_from_call_(nullptr),
      compression_algorithm_(GRPC_COMPRESS_NONE),
      initial_metadata_corked_(false) {
  // Notify global callbacks about construction
  g_client_callbacks->DefaultConstructor(this);
}

// ClientContext destructor cleans up resources
ClientContext::~ClientContext() {
  if (call_) {
    // Release the gRPC call reference
    grpc_call_unref(call_);
    call_ = nullptr;
  }
  // Notify global callbacks about destruction
  g_client_callbacks->Destructor(this);
}

// Sets call credentials for this context
void ClientContext::set_credentials(
    const std::shared_ptr<CallCredentials>& creds) {
  creds_ = creds;

  // If call is already set, apply credentials immediately
  if (creds_ != nullptr && call_ != nullptr) {
    if (!creds_->ApplyToCall(call_)) {
      // On failure, cancel the call and notify interceptors
      SendCancelToInterceptors();
      grpc_call_cancel_with_status(call_, GRPC_STATUS_CANCELLED,
                                   "Failed to set credentials to rpc.",
                                   nullptr);
    }
  }
}

// Creates a ClientContext from a server context with propagation options
std::unique_ptr<ClientContext> ClientContext::FromInternalServerContext(
    const grpc::ServerContextBase& context, PropagationOptions options) {
  std::unique_ptr<ClientContext> ctx(new ClientContext);
  ctx->propagate_from_call_ = context.call_.call;
  ctx->propagation_options_ = options;
  return ctx;
}

// Public version of FromInternalServerContext
std::unique_ptr<ClientContext> ClientContext::FromServerContext(
    const grpc::ServerContextBase& server_context, PropagationOptions options) {
  return FromInternalServerContext(server_context, options);
}

// Creates ClientContext from a callback server context
std::unique_ptr<ClientContext> ClientContext::FromCallbackServerContext(
    const grpc::CallbackServerContext& server_context,
    PropagationOptions options) {
  return FromInternalServerContext(server_context, options);
}

// Adds metadata to be sent with the call
void ClientContext::AddMetadata(const std::string& meta_key,
                                const std::string& meta_value) {
  send_initial_metadata_.insert(std::pair(meta_key, meta_value));
}

// Associates a gRPC call with this context
void ClientContext::set_call(grpc_call* call,
                             const std::shared_ptr<Channel>& channel) {
  internal::MutexLock lock(&mu_);
  CHECK_EQ(call_, nullptr);
  call_ = call;
  channel_ = channel;
  
  // Apply credentials if they were set before the call
  if (creds_ && !creds_->ApplyToCall(call_)) {
    SendCancelToInterceptors();
    grpc_call_cancel_with_status(call, GRPC_STATUS_CANCELLED,
                                 "Failed to set credentials to rpc.", nullptr);
  }
  
  // If call was canceled before being set, cancel it now
  if (call_canceled_) {
    SendCancelToInterceptors();
    grpc_call_cancel(call_, nullptr);
  }
}

// Sets the compression algorithm for the call
void ClientContext::set_compression_algorithm(
    grpc_compression_algorithm algorithm) {
  compression_algorithm_ = algorithm;
  const char* algorithm_name = nullptr;
  if (!grpc_compression_algorithm_name(algorithm, &algorithm_name)) {
    grpc_core::Crash(absl::StrFormat(
        "Name for compression algorithm '%d' unknown.", algorithm));
  }
  CHECK_NE(algorithm_name, nullptr);
  // Add compression algorithm to metadata
  AddMetadata(GRPC_COMPRESSION_REQUEST_ALGORITHM_MD_KEY, algorithm_name);
}

// Attempts to cancel the call
void ClientContext::TryCancel() {
  internal::MutexLock lock(&mu_);
  if (call_) {
    // If call is active, cancel it and notify interceptors
    SendCancelToInterceptors();
    grpc_call_cancel(call_, nullptr);
  } else {
    // Otherwise mark for cancellation when call is set
    call_canceled_ = true;
  }
}

// Notifies all interceptors about cancellation
void ClientContext::SendCancelToInterceptors() {
  internal::CancelInterceptorBatchMethods cancel_methods;
  for (size_t i = 0; i < rpc_info_.interceptors_.size(); i++) {
    rpc_info_.RunInterceptor(&cancel_methods, i);
  }
}

// Returns the peer address as a string
std::string ClientContext::peer() const {
  std::string peer;
  if (call_) {
    char* c_peer = grpc_call_get_peer(call_);
    peer = c_peer;
    gpr_free(c_peer);
  }
  return peer;
}

// Sets global callbacks for all ClientContext instances
void ClientContext::SetGlobalCallbacks(GlobalCallbacks* client_callbacks) {
  CHECK(g_client_callbacks == g_default_client_callbacks);
  CHECK_NE(client_callbacks, nullptr);
  CHECK(client_callbacks != g_default_client_callbacks);
  g_client_callbacks = client_callbacks;
}

}  // namespace grpc
```