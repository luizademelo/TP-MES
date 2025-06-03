Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_CLIENT_CONTEXT_H
#define GRPCPP_CLIENT_CONTEXT_H

// Include necessary headers for gRPC functionality
#include <grpc/impl/compression_types.h>
#include <grpc/impl/propagation_bits.h>
#include <grpcpp/impl/create_auth_context.h>
#include <grpcpp/impl/metadata_map.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/security/auth_context.h>
#include <grpcpp/support/client_interceptor.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/slice.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/string_ref.h>
#include <grpcpp/support/time.h>

// Standard library includes
#include <map>
#include <memory>
#include <string>

// ABSL includes
#include "absl/log/absl_check.h"

// Forward declarations
struct census_context;
struct grpc_call;

namespace grpc {
// Forward declarations of server context classes
class ServerContext;
class ServerContextBase;
class CallbackServerContext;

namespace internal {
// Forward declarations of internal template classes
template <class InputMessage, class OutputMessage>
class CallbackUnaryCallImpl;
template <class Request, class Response>
class ClientCallbackReaderWriterImpl;
template <class Response>
class ClientCallbackReaderImpl;
template <class Request>
class ClientCallbackWriterImpl;
class ClientCallbackUnaryImpl;
class ClientContextAccessor;
class ClientAsyncResponseReaderHelper;
}

// Forward declarations of client template classes
template <class R>
class ClientReader;
template <class W>
class ClientWriter;
template <class W, class R>
class ClientReaderWriter;
template <class R>
class ClientAsyncReader;
template <class W>
class ClientAsyncWriter;
template <class W, class R>
class ClientAsyncReaderWriter;
template <class R>
class ClientAsyncResponseReader;

namespace testing {
// Forward declarations for testing classes
class InteropClientContextInspector;
class ClientContextTestPeer;
}

namespace internal {
// Forward declarations of internal classes
class RpcMethod;
template <class InputMessage, class OutputMessage>
class BlockingUnaryCallImpl;
class CallOpClientRecvStatus;
class CallOpRecvInitialMetadata;
class ServerContextImpl;
template <class InputMessage, class OutputMessage>
class CallbackUnaryCallImpl;
template <class Request, class Response>
class ClientCallbackReaderWriterImpl;
template <class Response>
class ClientCallbackReaderImpl;
template <class Request>
class ClientCallbackWriterImpl;
class ClientCallbackUnaryImpl;
class ClientContextAccessor;
}

// Forward declarations of credential and channel classes
class CallCredentials;
class Channel;
class ChannelInterface;
class CompletionQueue;

// Class for configuring propagation options in gRPC calls
class PropagationOptions {
 public:
  // Constructor initializes with default propagation flags
  PropagationOptions() : propagate_(GRPC_PROPAGATE_DEFAULTS) {}

  // Enable deadline propagation
  PropagationOptions& enable_deadline_propagation() {
    propagate_ |= GRPC_PROPAGATE_DEADLINE;
    return *this;
  }

  // Disable deadline propagation
  PropagationOptions& disable_deadline_propagation() {
    propagate_ &= ~GRPC_PROPAGATE_DEADLINE;
    return *this;
  }

  // Enable census stats propagation
  PropagationOptions& enable_census_stats_propagation() {
    propagate_ |= GRPC_PROPAGATE_CENSUS_STATS_CONTEXT;
    return *this;
  }

  // Disable census stats propagation
  PropagationOptions& disable_census_stats_propagation() {
    propagate_ &= ~GRPC_PROPAGATE_CENSUS_STATS_CONTEXT;
    return *this;
  }

  // Enable census tracing propagation
  PropagationOptions& enable_census_tracing_propagation() {
    propagate_ |= GRPC_PROPAGATE_CENSUS_TRACING_CONTEXT;
    return *this;
  }

  // Disable census tracing propagation
  PropagationOptions& disable_census_tracing_propagation() {
    propagate_ &= ~GRPC_PROPAGATE_CENSUS_TRACING_CONTEXT;
    return *this;
  }

  // Enable cancellation propagation
  PropagationOptions& enable_cancellation_propagation() {
    propagate_ |= GRPC_PROPAGATE_CANCELLATION;
    return *this;
  }

  // Disable cancellation propagation
  PropagationOptions& disable_cancellation_propagation() {
    propagate_ &= ~GRPC_PROPAGATE_CANCELLATION;
    return *this;
  }

  // Get the current propagation bitmask
  uint32_t c_bitmask() const { return propagate_; }

 private:
  uint32_t propagate_;  // Bitmask storing propagation options
};

// Main class representing client context for gRPC calls
class ClientContext {
 public:
  ClientContext();
  ~ClientContext();

  // Create a ClientContext from a ServerContext with propagation options
  static std::unique_ptr<ClientContext> FromServerContext(
      const grpc::ServerContextBase& server_context,
      PropagationOptions options = PropagationOptions());
      
  // Create a ClientContext from a CallbackServerContext with propagation options
  static std::unique_ptr<ClientContext> FromCallbackServerContext(
      const grpc::CallbackServerContext& server_context,
      PropagationOptions options = PropagationOptions());

  // Add metadata to be sent to the server
  void AddMetadata(const std::string& meta_key, const std::string& meta_value);

  // Get server's initial metadata (requires metadata to have been received)
  const std::multimap<grpc::string_ref, grpc::string_ref>&
  GetServerInitialMetadata() const {
    ABSL_CHECK(initial_metadata_received_);
    return *recv_initial_metadata_.map();
  }

  // Get server's trailing metadata
  const std::multimap<grpc::string_ref, grpc::string_ref>&
  GetServerTrailingMetadata() const {
    return *trailing_metadata_.map();
  }

  // Set the deadline for the RPC call
  template <typename T>
  void set_deadline(const T& deadline) {
    grpc::TimePoint<T> deadline_tp(deadline);
    deadline_ = deadline_tp.raw_time();
  }

  // Set whether to wait for server to be ready
  void set_wait_for_ready(bool wait_for_ready) {
    wait_for_ready_ = wait_for_ready;
    wait_for_ready_explicitly_set_ = true;
  }

  // Set fail fast option (inverse of wait_for_ready)
  void set_fail_fast(bool fail_fast) { set_wait_for_ready(!fail_fast); }

  // Get the deadline as a time point
  std::chrono::system_clock::time_point deadline() const {
    return grpc::Timespec2Timepoint(deadline_);
  }

  // Get the raw deadline value
  gpr_timespec raw_deadline() const { return deadline_; }

  // Set the authority header (virtual host name)
  void set_authority(const std::string& authority) { authority_ = authority; }

  // Get the authentication context
  std::shared_ptr<const grpc::AuthContext> auth_context() const {
    if (auth_context_ == nullptr) {
      auth_context_ = grpc::CreateAuthContext(call_);
    }
    return auth_context_;
  }

  // Set call credentials
  void set_credentials(const std::shared_ptr<grpc::CallCredentials>& creds);

  // Get current call credentials
  std::shared_ptr<grpc::CallCredentials> credentials() { return creds_; }

  // Get current compression algorithm
  grpc_compression_algorithm compression_algorithm() const {
    return compression_algorithm_;
  }

  // Set compression algorithm for the call
  void set_compression_algorithm(grpc_compression_algorithm algorithm);

  // Set whether initial metadata should be corked
  void set_initial_metadata_corked(bool corked) {
    initial_metadata_corked_ = corked;
  }

  // Get peer address as string
  std::string peer() const;

  // Set census context for distributed tracing
  void set_census_context(struct census_context* ccp) { census_context_ = ccp; }

  // Get current census context
  struct census_context* census_context() const { return census_context_; }

  // Attempt to cancel the RPC
  void TryCancel();

  // Interface for global callbacks
  class GlobalCallbacks {
   public:
    virtual ~GlobalCallbacks() {}
    virtual void DefaultConstructor(ClientContext* context) = 0;
    virtual void Destructor(ClientContext* context) = 0;
  };
  
  // Set global callbacks for ClientContext lifecycle events
  static void SetGlobalCallbacks(GlobalCallbacks* callbacks);

  // Get the underlying C call object
  grpc_call* c_call() { return call_; }

  // Get debug error string
  std::string debug_error_string() const { return debug_error_string_; }

 private:
  // Disable copy constructor and assignment operator
  ClientContext(const ClientContext&);
  ClientContext& operator=(const ClientContext&);

  // Friend declarations for internal and testing classes
  friend class grpc::testing::InteropClientContextInspector;
  friend class grpc::testing::ClientContextTestPeer;
  friend class grpc::internal::CallOpClientRecvStatus;
  friend class grpc::internal::CallOpRecvInitialMetadata;
  friend class grpc::Channel;
  template <class R>
  friend class grpc::ClientReader;
  template <class W>
  friend class grpc::ClientWriter;
  template <class W, class R>
  friend class grpc::ClientReaderWriter;
  template <class R>
  friend class grpc::ClientAsyncReader;
  template <class W>
  friend class grpc::ClientAsyncWriter;
  template <class W, class R>
  friend class grpc::ClientAsyncReaderWriter;
  template <class R>
  friend class grpc::ClientAsyncResponseReader;
  friend class grpc::internal::ClientAsyncResponseReaderHelper;
  template <class InputMessage, class OutputMessage>
  friend class grpc::internal::BlockingUnaryCallImpl;
  template <class InputMessage, class OutputMessage>
  friend class grpc::internal::CallbackUnaryCallImpl;
  template <class Request, class Response>
  friend class grpc::internal::ClientCallbackReaderWriterImpl;
  template <class Response>
  friend class grpc::internal::ClientCallbackReaderImpl;
  template <class Request>
  friend class grpc::internal::ClientCallbackWriterImpl;
  friend class grpc::internal::ClientCallbackUnaryImpl;
  friend class grpc::internal::ClientContextAccessor;

  // Set debug error string
  void set_debug_error_string(const std::string& debug_error_string) {
    debug_error_string_ = debug_error_string;
  }

  // Get the underlying C call object
  grpc_call* call() const { return call_; }
  
  // Set the underlying C call object and associated channel
  void set_call(grpc_call* call, const std::shared_ptr<grpc::Channel>& channel);

  // Set RPC info for interceptors
  grpc::experimental::ClientRpcInfo* set_client_rpc_info(
      const char* method, const char* suffix_for_stats,
      grpc::internal::RpcMethod::RpcType type, grpc::ChannelInterface* channel,
      const std::vector<std::unique_ptr<
          grpc::experimental::ClientInterceptorFactoryInterface>>& creators,
      size_t interceptor_pos) {
    rpc_info_ = grpc::experimental::ClientRpcInfo(this, type, method,
                                                  suffix_for_stats, channel);
    rpc_info_.RegisterInterceptors(creators, interceptor_pos);
    return &rpc_info_;
  }

  // Get flags for initial metadata
  uint32_t initial_metadata_flags() const {
    return (wait_for_ready_ ? GRPC_INITIAL_METADATA_WAIT_FOR_READY : 0) |
           (wait_for_ready_explicitly_set_
                ? GRPC_INITIAL_METADATA_WAIT_FOR_READY_EXPLICITLY_SET
                : 0);
  }

  // Get authority string
  std::string authority() { return authority_; }

  // Send cancellation to interceptors
  void SendCancelToInterceptors();

  // Internal method to create ClientContext from ServerContext
  static std::unique_ptr<ClientContext> FromInternalServerContext(
      const grpc::ServerContextBase& server_context,
      PropagationOptions options);

  // Member variables
  bool initial_metadata_received_;          // Flag for received initial metadata
  bool wait_for_ready_;                     // Whether to wait for server ready
  bool wait_for_ready_explicitly_set_;      // Whether wait_for_ready was explicitly set
  std::shared_ptr<grpc::Channel> channel_;  // Associated channel
  grpc::internal::Mutex mu_;               // Mutex for thread safety
  grpc_call* call_;                        // Underlying gRPC call object
  bool call_canceled_;                     // Whether call was canceled
  gpr_timespec deadline_;                  // Call deadline
  grpc::string authority_;                 // Authority header
  std::shared_ptr<grpc::CallCredentials> creds_;  // Call credentials
  mutable std::shared_ptr<const grpc::AuthContext> auth_context_;  // Auth context
  struct census_context* census_context_;  // Census context for tracing
  std::multimap<std::string, std::string> send_initial_metadata_;  // Outgoing metadata
  mutable grpc::internal::MetadataMap recv_initial_metadata_;      // Received initial metadata
  mutable grpc::internal::MetadataMap trailing_metadata_;          // Received trailing metadata

  grpc_call* propagate_from_call_;         // Call to propagate context from
  PropagationOptions propagation_options_;  // Propagation options

  grpc_compression_algorithm compression_algorithm_;  // Compression algorithm
  bool initial_metadata_corked_;                      // Whether metadata is corked

  std::string debug_error_string_;  // Debug error information

  grpc::experimental::ClientRpcInfo rpc_info_;  // RPC info for interceptors
};

}  // namespace grpc

#endif  // GRPCPP_CLIENT_CONTEXT_H
```