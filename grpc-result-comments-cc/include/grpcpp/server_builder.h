Here's the commented version of the code:

```c++
// Copyright 2015-2016 gRPC authors.

#ifndef GRPCPP_SERVER_BUILDER_H
#define GRPCPP_SERVER_BUILDER_H

// Include necessary headers for gRPC server functionality
#include <grpc/compression.h>
#include <grpc/event_engine/event_engine.h>
#include <grpc/passive_listener.h>
#include <grpc/support/cpu.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/workaround_list.h>
#include <grpcpp/impl/channel_argument_option.h>
#include <grpcpp/impl/server_builder_option.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/passive_listener.h>
#include <grpcpp/security/authorization_policy_provider.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/server_interceptor.h>

// Standard library includes
#include <climits>
#include <map>
#include <memory>
#include <vector>

struct grpc_resource_quota;

namespace grpc {

// Forward declarations
class CompletionQueue;
class Server;
class ServerCompletionQueue;
class AsyncGenericService;
class ResourceQuota;
class ServerCredentials;
class Service;

namespace testing {
class ServerBuilderPluginTest;
}

namespace internal {
class ExternalConnectionAcceptorImpl;
}

class CallbackGenericService;

namespace experimental {

// Interface for handling external connections to the server
class ExternalConnectionAcceptor {
 public:
  // Parameters for new connections
  struct NewConnectionParameters {
    int listener_fd = -1;  // Listener file descriptor
    int fd = -1;           // Connection file descriptor
    ByteBuffer read_buffer; // Initial data received
  };
  virtual ~ExternalConnectionAcceptor() {}

  // Handle a new incoming connection
  virtual void HandleNewConnection(NewConnectionParameters* p) = 0;
};

}  // namespace experimental
}  // namespace grpc

namespace grpc {

// Builder class for creating and configuring gRPC servers
class ServerBuilder {
 public:
  ServerBuilder();
  virtual ~ServerBuilder();

  // Build and start the server with current configuration
  virtual std::unique_ptr<grpc::Server> BuildAndStart();

  // Register a service with the server
  ServerBuilder& RegisterService(grpc::Service* service);

  // Add a listening port to the server
  ServerBuilder& AddListeningPort(
      const std::string& addr_uri,
      std::shared_ptr<grpc::ServerCredentials> creds,
      int* selected_port = nullptr);

  // Add a completion queue to the server
  std::unique_ptr<grpc::ServerCompletionQueue> AddCompletionQueue(
      bool is_frequently_polled = true);

  // Register a service with a specific host
  ServerBuilder& RegisterService(const std::string& host,
                                 grpc::Service* service);

  // Register an asynchronous generic service
  ServerBuilder& RegisterAsyncGenericService(
      grpc::AsyncGenericService* service);

  // Set maximum receive message size
  ServerBuilder& SetMaxReceiveMessageSize(int max_receive_message_size) {
    max_receive_message_size_ = max_receive_message_size;
    return *this;
  }

  // Set maximum send message size
  ServerBuilder& SetMaxSendMessageSize(int max_send_message_size) {
    max_send_message_size_ = max_send_message_size;
    return *this;
  }

  // Set maximum message size (alias for SetMaxReceiveMessageSize)
  ServerBuilder& SetMaxMessageSize(int max_message_size) {
    return SetMaxReceiveMessageSize(max_message_size);
  }

  // Enable/disable compression algorithm support
  ServerBuilder& SetCompressionAlgorithmSupportStatus(
      grpc_compression_algorithm algorithm, bool enabled);

  // Set default compression level
  ServerBuilder& SetDefaultCompressionLevel(grpc_compression_level level);

  // Set default compression algorithm
  ServerBuilder& SetDefaultCompressionAlgorithm(
      grpc_compression_algorithm algorithm);

  // Set resource quota for the server
  ServerBuilder& SetResourceQuota(const grpc::ResourceQuota& resource_quota);

  // Set a custom server builder option
  ServerBuilder& SetOption(std::unique_ptr<grpc::ServerBuilderOption> option);

  // Options for synchronous server configuration
  enum SyncServerOption {
    NUM_CQS,         // Number of completion queues
    MIN_POLLERS,     // Minimum number of polling threads
    MAX_POLLERS,     // Maximum number of polling threads
    CQ_TIMEOUT_MSEC  // Completion queue timeout in milliseconds
  };

  // Set synchronous server option
  ServerBuilder& SetSyncServerOption(SyncServerOption option, int value);

  // Add a channel argument
  template <class T>
  ServerBuilder& AddChannelArgument(const std::string& arg, const T& value) {
    return SetOption(grpc::MakeChannelArgumentOption(arg, value));
  }

  // Internal method to add plugin factory
  static void InternalAddPluginFactory(
      std::unique_ptr<grpc::ServerBuilderPlugin> (*CreatePlugin)());

  // Enable workaround for known issues
  ServerBuilder& EnableWorkaround(grpc_workaround_list id);

  /// NOTE: class experimental_type is not part of the public API of this class
  /// Provides access to experimental features
  class experimental_type {
   public:
    explicit experimental_type(ServerBuilder* builder) : builder_(builder) {}

    // Set interceptor creators for the server
    void SetInterceptorCreators(
        std::vector<std::unique_ptr<
            grpc::experimental::ServerInterceptorFactoryInterface>>
            interceptor_creators) {
      builder_->interceptor_creators_ = std::move(interceptor_creators);
    }

    // Types of external connections
    enum class ExternalConnectionType {
      FROM_FD = 0  // Connection from file descriptor
    };

    // Add an external connection acceptor
    std::unique_ptr<grpc::experimental::ExternalConnectionAcceptor>
    AddExternalConnectionAcceptor(ExternalConnectionType type,
                                  std::shared_ptr<ServerCredentials> creds);

    // Set authorization policy provider
    void SetAuthorizationPolicyProvider(
        std::shared_ptr<experimental::AuthorizationPolicyProviderInterface>
            provider);

    // Enable call metric recording
    void EnableCallMetricRecording(
        experimental::ServerMetricRecorder* server_metric_recorder = nullptr);

    // Add a passive listener to the server
    ServerBuilder& AddPassiveListener(
        std::shared_ptr<grpc::ServerCredentials> creds,
        std::unique_ptr<grpc::experimental::PassiveListener>& passive_listener);

   private:
    ServerBuilder* builder_;
  };

  // Set context allocator for the server
  ServerBuilder& SetContextAllocator(
      std::unique_ptr<grpc::ContextAllocator> context_allocator);

  // Register a callback-based generic service
  ServerBuilder& RegisterCallbackGenericService(
      grpc::CallbackGenericService* service);

  /// NOTE: The function experimental() is not stable public API. It is a view
  /// to access experimental features
  experimental_type experimental() { return experimental_type(this); }

 protected:
  // Structure representing a listening port
  struct Port {
    std::string addr;  // Address to listen on
    std::shared_ptr<ServerCredentials> creds;  // Credentials for the port
    int* selected_port;  // Pointer to store selected port (if null is passed)
  };

  // Alias for host string pointer
  typedef std::unique_ptr<std::string> HostString;
  
  // Structure representing a named service
  struct NamedService {
    explicit NamedService(grpc::Service* s) : service(s) {}
    NamedService(const std::string& h, grpc::Service* s)
        : host(new std::string(h)), service(s) {}
    HostString host;  // Optional host name
    grpc::Service* service;  // Service implementation
  };

  // Get configured ports
  std::vector<Port> ports() { return ports_; }

  // Get registered services
  std::vector<NamedService*> services() {
    std::vector<NamedService*> service_refs;
    service_refs.reserve(services_.size());
    for (auto& ptr : services_) {
      service_refs.push_back(ptr.get());
    }
    return service_refs;
  }

  // Get configured options
  std::vector<grpc::ServerBuilderOption*> options() {
    std::vector<grpc::ServerBuilderOption*> option_refs;
    option_refs.reserve(options_.size());
    for (auto& ptr : options_) {
      option_refs.push_back(ptr.get());
    }
    return option_refs;
  }

  // Set server config fetcher
  void set_fetcher(grpc_server_config_fetcher* server_config_fetcher) {
    server_config_fetcher_ = server_config_fetcher;
  }

  // Build channel arguments from current configuration
  virtual ChannelArguments BuildChannelArgs();

 private:
  friend class grpc::testing::ServerBuilderPluginTest;

  // Structure for unstarted passive listeners
  struct UnstartedPassiveListener {
    std::weak_ptr<grpc_core::experimental::PassiveListenerImpl>
        passive_listener;
    std::shared_ptr<grpc::ServerCredentials> credentials;
    UnstartedPassiveListener(
        std::weak_ptr<grpc_core::experimental::PassiveListenerImpl> listener,
        std::shared_ptr<grpc::ServerCredentials> creds)
        : passive_listener(std::move(listener)),
          credentials(std::move(creds)) {}
  };

  // Settings for synchronous server
  struct SyncServerSettings {
    SyncServerSettings()
        : num_cqs(1), min_pollers(1), max_pollers(2), cq_timeout_msec(10000) {}

    int num_cqs;  // Number of completion queues

    int min_pollers;  // Minimum number of polling threads per CQ

    int max_pollers;  // Maximum number of polling threads per CQ

    int cq_timeout_msec;  // Completion queue timeout in milliseconds
  };

  // Member variables
  int max_receive_message_size_;  // Maximum size for received messages
  int max_send_message_size_;  // Maximum size for sent messages
  std::vector<std::unique_ptr<grpc::ServerBuilderOption>> options_;  // Configuration options
  std::vector<std::unique_ptr<NamedService>> services_;  // Registered services
  std::vector<Port> ports_;  // Listening ports
  std::vector<UnstartedPassiveListener> unstarted_passive_listeners_;  // Passive listeners

  SyncServerSettings sync_server_settings_;  // Synchronous server settings

  std::vector<grpc::ServerCompletionQueue*> cqs_;  // Completion queues

  std::shared_ptr<grpc::ServerCredentials> creds_;  // Server credentials
  std::vector<std::unique_ptr<grpc::ServerBuilderPlugin>> plugins_;  // Plugins
  grpc_resource_quota* resource_quota_;  // Resource quota
  grpc::AsyncGenericService* generic_service_{nullptr};  // Generic service
  std::unique_ptr<ContextAllocator> context_allocator_;  // Context allocator
  grpc::CallbackGenericService* callback_generic_service_{nullptr};  // Callback service

  // Compression settings
  struct {
    bool is_set;
    grpc_compression_level level;
  } maybe_default_compression_level_;
  struct {
    bool is_set;
    grpc_compression_algorithm algorithm;
  } maybe_default_compression_algorithm_;
  uint32_t enabled_compression_algorithms_bitset_;  // Enabled algorithms
  
  // Interceptors and connection handling
  std::vector<
      std::unique_ptr<grpc::experimental::ServerInterceptorFactoryInterface>>
      interceptor_creators_;
  std::vector<std::shared_ptr<grpc::internal::ExternalConnectionAcceptorImpl>>
      acceptors_;
      
  // Server configuration
  grpc_server_config_fetcher* server_config_fetcher_ = nullptr;
  std::shared_ptr<experimental::AuthorizationPolicyProviderInterface>
      authorization_provider_;
  experimental::ServerMetricRecorder* server_metric_recorder_ = nullptr;
};

}  // namespace grpc

#endif  // GRPCPP_SERVER_BUILDER_H
```