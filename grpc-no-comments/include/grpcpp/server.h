
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SERVER_H
#define GRPCPP_SERVER_H

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

#include <list>
#include <memory>
#include <vector>

struct grpc_server;

namespace grpc {
class AsyncGenericService;
class ServerContext;
class ServerInitializer;

namespace internal {
class ExternalConnectionAcceptorImpl;
}

class Server : public ServerInterface, private internal::GrpcLibrary {
 public:
  ~Server() ABSL_LOCKS_EXCLUDED(mu_) override;

  void Wait() ABSL_LOCKS_EXCLUDED(mu_) override;

  class GlobalCallbacks {
   public:
    virtual ~GlobalCallbacks() {}

    virtual void UpdateArguments(ChannelArguments* ) {}

    virtual void PreSynchronousRequest(ServerContext* context) = 0;

    virtual void PostSynchronousRequest(ServerContext* context) = 0;

    virtual void PreServerStart(Server* ) {}

    virtual void AddPort(Server* , const std::string& ,
                         ServerCredentials* , int ) {}
  };

  static void SetGlobalCallbacks(GlobalCallbacks* callbacks);

  grpc_server* c_server();

  HealthCheckServiceInterface* GetHealthCheckService() const {
    return health_check_service_.get();
  }

  std::shared_ptr<Channel> InProcessChannel(const ChannelArguments& args);

  /// NOTE: class experimental_type is not part of the public API of this class.

  class experimental_type {
   public:
    explicit experimental_type(Server* server) : server_(server) {}

    std::shared_ptr<Channel> InProcessChannelWithInterceptors(
        const ChannelArguments& args,
        std::vector<
            std::unique_ptr<experimental::ClientInterceptorFactoryInterface>>
            interceptor_creators);

   private:
    Server* server_;
  };

  /// NOTE: The function experimental() is not stable public API. It is a view

  experimental_type experimental() { return experimental_type(this); }

 protected:

  bool RegisterService(const std::string* addr, Service* service) override;

  int AddListeningPort(const std::string& addr,
                       ServerCredentials* creds) override;

  /// NOTE: This is *NOT* a public API. The server constructors are supposed to

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

  void Start(ServerCompletionQueue** cqs, size_t num_cqs) override;

  grpc_server* server() override { return server_; }

  /// NOTE: This method is not part of the public API for this class.
  void set_health_check_service(
      std::unique_ptr<HealthCheckServiceInterface> service) {
    health_check_service_ = std::move(service);
  }

  ContextAllocator* context_allocator() { return context_allocator_.get(); }

  /// NOTE: This method is not part of the public API for this class.
  bool health_check_service_disabled() const {
    return health_check_service_disabled_;
  }

 private:
  std::vector<std::unique_ptr<experimental::ServerInterceptorFactoryInterface>>*
  interceptor_creators() override {
    return &interceptor_creators_;
  }

  friend class AsyncGenericService;
  friend class ServerBuilder;
  friend class ServerInitializer;

  class SyncRequest;
  class CallbackRequestBase;
  template <class ServerContextType>
  class CallbackRequest;
  class UnimplementedAsyncRequest;
  class UnimplementedAsyncResponse;

  class SyncRequestThreadManager;

  void RegisterAsyncGenericService(AsyncGenericService* service) override;

  void RegisterCallbackGenericService(CallbackGenericService* service) override;

  void RegisterContextAllocator(
      std::unique_ptr<ContextAllocator> context_allocator) {
    context_allocator_ = std::move(context_allocator);
  }

  void PerformOpsOnCall(internal::CallOpSetInterface* ops,
                        internal::Call* call) override;

  void ShutdownInternal(gpr_timespec deadline)
      ABSL_LOCKS_EXCLUDED(mu_) override;

  int max_receive_message_size() const override {
    return max_receive_message_size_;
  }

  bool call_metric_recording_enabled() const override {
    return call_metric_recording_enabled_;
  }

  experimental::ServerMetricRecorder* server_metric_recorder() const override {
    return server_metric_recorder_;
  }

  CompletionQueue* CallbackCQ() ABSL_LOCKS_EXCLUDED(mu_) override;

  ServerInitializer* initializer();

  void Ref();
  void UnrefWithPossibleNotify() ABSL_LOCKS_EXCLUDED(mu_);
  void UnrefAndWaitLocked() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  std::vector<std::shared_ptr<internal::ExternalConnectionAcceptorImpl>>
      acceptors_;

  std::vector<std::unique_ptr<experimental::ServerInterceptorFactoryInterface>>
      interceptor_creators_;

  int max_receive_message_size_;

  std::shared_ptr<std::vector<std::unique_ptr<ServerCompletionQueue>>>
      sync_server_cqs_;

  std::vector<std::unique_ptr<SyncRequestThreadManager>> sync_req_mgrs_;

  internal::Mutex mu_;
  bool started_;
  bool shutdown_ ABSL_GUARDED_BY(mu_);
  bool shutdown_notified_
      ABSL_GUARDED_BY(mu_);
  internal::CondVar shutdown_done_cv_;
  bool shutdown_done_ ABSL_GUARDED_BY(mu_) = false;
  std::atomic_int shutdown_refs_outstanding_{1};

  internal::CondVar shutdown_cv_;

  std::shared_ptr<GlobalCallbacks> global_callbacks_;

  std::vector<std::string> services_;
  bool has_async_generic_service_ = false;
  bool has_callback_generic_service_ = false;
  bool has_callback_methods_ = false;

  grpc_server* server_;

  std::unique_ptr<ServerInitializer> server_initializer_;

  std::unique_ptr<ContextAllocator> context_allocator_;

  std::unique_ptr<HealthCheckServiceInterface> health_check_service_;
  bool health_check_service_disabled_;

  std::unique_ptr<CallbackGenericService> unimplemented_service_;

  std::unique_ptr<internal::MethodHandler> resource_exhausted_handler_;

  std::unique_ptr<internal::MethodHandler> generic_handler_;

  std::atomic<CompletionQueue*> callback_cq_{nullptr};

  std::vector<CompletionQueue*> cq_list_;

  bool call_metric_recording_enabled_ = false;

  experimental::ServerMetricRecorder* server_metric_recorder_ = nullptr;
};

}

#endif
