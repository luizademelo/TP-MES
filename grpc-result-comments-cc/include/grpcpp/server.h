Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPCPP_SERVER_H
#define GRPCPP_SERVER_H

// Include necessary gRPC headers
#include <grpc/compression.h>
#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/channel.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_interface.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/support/client_interceptor.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/status.h>

// Standard library includes
#include <list>
#include <memory>
#include <vector>

// Forward declaration of grpc_server struct
struct grpc_server;

namespace grpc {
class AsyncGenericService;
class ServerContext;
class ServerInitializer;

namespace internal {
class ExternalConnectionAcceptorImpl;
}

// Main Server class that implements ServerInterface and inherits from GrpcLibrary
class Server : public ServerInterface, private internal::GrpcLibrary {
 public:
  // Destructor with thread safety annotation
  ~Server() ABSL_LOCKS_EXCLUDED(mu_) override;

  // Wait for the server to shutdown
  void Wait() ABSL_LOCKS_EXCLUDED(mu_) override;

  // Global callbacks interface for server events
  class GlobalCallbacks {
   public:
    virtual ~GlobalCallbacks() {}

    // Update channel arguments
    virtual void UpdateArguments(ChannelArguments* ) {}

    // Called before handling a synchronous request
    virtual void PreSynchronousRequest(ServerContext* context) = 0;

    // Called after handling a synchronous request
    virtual void PostSynchronousRequest(ServerContext* context) = 0;

    // Called before server starts
    virtual void PreServerStart(Server* ) {}

    // Called when a port is added to the server
    virtual void AddPort(Server* , const std::string& ,
                         ServerCredentials* , int ) {}
  };

  // Set global callbacks for the server
  static void SetGlobalCallbacks(GlobalCallbacks* callbacks);

  // Get the underlying C server object
  grpc_server* c_server();

  // Get the health check service
  HealthCheckServiceInterface* GetHealthCheckService() const {
    return health_check_service_.get();
  }

  // Create an in-process channel with given arguments
  std::shared_ptr<Channel> InProcessChannel(const ChannelArguments& args);

  /// NOTE: class experimental_type is not part of the public API of this class.
  // Experimental features interface
  class experimental_type {
   public:
    explicit experimental_type(Server* server) : server_(server) {}

    // Create in-process channel with interceptors
    std::shared_ptr<Channel> InProcessChannelWithInterceptors(
        const ChannelArguments& args,
        std::vector<
            std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
            interceptor_creators);

   private:
    Server* server_;  // Pointer to the parent server
  };

  /// NOTE: The function experimental() is not stable public API. It is a view
  // Get the experimental interface
  experimental_type experimental() { return experimental_type(this); }

 protected:
  // Register a service with the server
  bool RegisterService(const std::string* addr, Service* service) override;

  // Add a listening port to the server
  int AddListeningPort(const std::string& addr,
                       ServerCredentials* creds) override;

  /// NOTE: This is *NOT* a public API. The server constructors are supposed to
  // Protected constructor with various configuration options
  Server(ChannelArguments* args,
         std::shared_ptr<std::vector<std::unique_ptr<ServerCompletionQueue>>>
             sync_server_cqs,
         int min_pollers, int max_pollers, int sync_cq_timeout_msec,
         std::vector<std::shared_ptr<internal::ExternalConnectionAcceptorImpl>>
             acceptors,
         grpc_server_config_fetcher* server_config_fetcher = nullptr,
         grpc_resource_quota* server_rq = nullptr,
         std::vector<
             std::unique_ptr<experimental::ServerInterceptorFactoryInterface>>
             interceptor_creators = std::vector<std::unique_ptr<
                 experimental::ServerInterceptorFactoryInterface>>(),
         experimental::ServerMetricRecorder* server_metric_recorder = nullptr);

  // Start the server with given completion queues
  void Start(ServerCompletionQueue** cqs, size_t num_cqs) override;

  // Get the underlying server object
  grpc_server* server() override { return server_; }

  /// NOTE: This method is not part of the public API for this class.
  // Set health check service
  void set_health_check_service(
      std::unique_ptr<HealthCheckServiceInterface> service) {
    health_check_service_ = std::move(service);
  }

  // Get context allocator
  ContextAllocator* context_allocator() { return context_allocator_.get(); }

  /// NOTE: This method is not part of the public API for this class.
  // Check if health check service is disabled
  bool health_check_service_disabled() const {
    return health_check_service_disabled_;
  }

 private:
  // Get interceptor creators
  std::vector<std::unique_ptr<experimental::ServerInterceptorFactoryInterface>>*
  interceptor_creators() override {
    return &interceptor_creators_;
  }

  // Friend declarations
  friend class AsyncGenericService;
  friend class ServerBuilder;
  friend class ServerInitializer;

  // Private nested class declarations
  class SyncRequest;
  class CallbackRequestBase;
  template <class ServerContextType>
  class CallbackRequest;
  class UnimplementedAsyncRequest;
  class UnimplementedAsyncResponse;

  class SyncRequestThreadManager;

  // Register async generic service
  void RegisterAsyncGenericService(AsyncGenericService* service) override;

  // Register callback generic service
  void RegisterCallbackGenericService(CallbackGenericService* service) override;

  // Register context allocator
  void RegisterContextAllocator(
      std::unique_ptr<ContextAllocator> context_allocator) {
    context_allocator_ = std::move(context_allocator);
  }

  // Perform operations on a call
  void PerformOpsOnCall(internal::CallOpSetInterface* ops,
                        internal::Call* call) override;

  // Internal shutdown method with deadline
  void ShutdownInternal(gpr_timespec deadline)
      ABSL_LOCKS_EXCLUDED(mu_) override;

  // Get maximum receive message size
  int max_receive_message_size() const override {
    return max_receive_message_size_;
  }

  // Check if call metric recording is enabled
  bool call_metric_recording_enabled() const override {
    return call_metric_recording_enabled_;
  }

  // Get server metric recorder
  experimental::ServerMetricRecorder* server_metric_recorder() const override {
    return server_metric_recorder_;
  }

  // Get callback completion queue
  CompletionQueue* CallbackCQ() ABSL_LOCKS_EXCLUDED(mu_) override;

  // Get server initializer
  ServerInitializer* initializer();

  // Reference counting methods
  void Ref();
  void UnrefWithPossibleNotify() ABSL_LOCKS_EXCLUDED(mu_);
  void UnrefAndWaitLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  // Member variables
  std::vector<std::shared_ptr<internal::ExternalConnectionAcceptorImpl>>
      acceptors_;  // Connection acceptors

  std::vector<std::unique_ptr<experimental::ServerInterceptorFactoryInterface>>
      interceptor_creators_;  // Interceptor factories

  int max_receive_message_size_;  // Max message size configuration

  std::shared_ptr<std::vector<std::unique_ptr<ServerCompletionQueue>>>
      sync_server_cqs_;  // Synchronous completion queues

  std::vector<std::unique_ptr<SyncRequestThreadManager>> sync_req_mgrs_;  // Sync request managers

  // Synchronization primitives and server state
  internal::Mutex mu_;
  bool started_;
  bool shutdown_ ABSL_GUARDED_BY(mu_);
  bool shutdown_notified_ ABSL_GUARDED_BY(mu_);
  internal::CondVar shutdown_done_cv_;
  bool shutdown_done_ ABSL_GUARDED_BY(mu_) = false;
  std::atomic_int shutdown_refs_outstanding_{1};

  internal::CondVar shutdown_cv_;

  // Global callbacks
  std::shared_ptr<GlobalCallbacks> global_callbacks_;

  // Service registration tracking
  std::vector<std::string> services_;
  bool has_async_generic_service_ = false;
  bool has_callback_generic_service_ = false;
  bool has_callback_methods_ = false;

  // Core server objects
  grpc_server* server_;
  std::unique_ptr<ServerInitializer> server_initializer_;
  std::unique_ptr<ContextAllocator> context_allocator_;

  // Health check service
  std::unique_ptr<HealthCheckServiceInterface> health_check_service_;
  bool health_check_service_disabled_;

  // Special services
  std::unique_ptr<CallbackGenericService> unimplemented_service_;
  std::unique_ptr<internal::MethodHandler> resource_exhausted_handler_;
  std::unique_ptr<internal::MethodHandler> generic_handler_;

  // Completion queue management
  std::atomic<CompletionQueue*> callback_cq_{nullptr};
  std::vector<CompletionQueue*> cq_list_;

  // Metrics configuration
  bool call_metric_recording_enabled_ = false;
  experimental::ServerMetricRecorder* server_metric_recorder_ = nullptr;
};

}  // namespace grpc

#endif  // GRPCPP_SERVER_H
```