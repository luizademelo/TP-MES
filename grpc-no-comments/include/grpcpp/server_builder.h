
// Copyright 2015-2016 gRPC authors.

#ifndef GRPCPP_SERVER_BUILDER_H
#define GRPCPP_SERVER_BUILDER_H

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

#include <climits>
#include <map>
#include <memory>
#include <vector>

struct grpc_resource_quota;

namespace grpc {

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

class ExternalConnectionAcceptor {
 public:
  struct NewConnectionParameters {
    int listener_fd = -1;
    int fd = -1;
    ByteBuffer read_buffer;
  };
  virtual ~ExternalConnectionAcceptor() {}

  virtual void HandleNewConnection(NewConnectionParameters* p) = 0;
};

}
}

namespace grpc {

class ServerBuilder {
 public:
  ServerBuilder();
  virtual ~ServerBuilder();

  virtual std::unique_ptr<grpc::Server> BuildAndStart();

  ServerBuilder& RegisterService(grpc::Service* service);

  ServerBuilder& AddListeningPort(
      const std::string& addr_uri,
      std::shared_ptr<grpc::ServerCredentials> creds,
      int* selected_port = nullptr);

  std::unique_ptr<grpc::ServerCompletionQueue> AddCompletionQueue(
      bool is_frequently_polled = true);

  ServerBuilder& RegisterService(const std::string& host,
                                 grpc::Service* service);

  ServerBuilder& RegisterAsyncGenericService(
      grpc::AsyncGenericService* service);

  ServerBuilder& SetMaxReceiveMessageSize(int max_receive_message_size) {
    max_receive_message_size_ = max_receive_message_size;
    return *this;
  }

  ServerBuilder& SetMaxSendMessageSize(int max_send_message_size) {
    max_send_message_size_ = max_send_message_size;
    return *this;
  }

  ServerBuilder& SetMaxMessageSize(int max_message_size) {
    return SetMaxReceiveMessageSize(max_message_size);
  }

  ServerBuilder& SetCompressionAlgorithmSupportStatus(
      grpc_compression_algorithm algorithm, bool enabled);

  ServerBuilder& SetDefaultCompressionLevel(grpc_compression_level level);

  ServerBuilder& SetDefaultCompressionAlgorithm(
      grpc_compression_algorithm algorithm);

  ServerBuilder& SetResourceQuota(const grpc::ResourceQuota& resource_quota);

  ServerBuilder& SetOption(std::unique_ptr<grpc::ServerBuilderOption> option);

  enum SyncServerOption {
    NUM_CQS,
    MIN_POLLERS,
    MAX_POLLERS,
    CQ_TIMEOUT_MSEC
  };

  ServerBuilder& SetSyncServerOption(SyncServerOption option, int value);

  template <class T>
  ServerBuilder& AddChannelArgument(const std::string& arg, const T& value) {
    return SetOption(grpc::MakeChannelArgumentOption(arg, value));
  }

  static void InternalAddPluginFactory(
      std::unique_ptr<grpc::ServerBuilderPlugin> (*CreatePlugin)());

  ServerBuilder& EnableWorkaround(grpc_workaround_list id);

  /// NOTE: class experimental_type is not part of the public API of this class.

  class experimental_type {
   public:
    explicit experimental_type(ServerBuilder* builder) : builder_(builder) {}

    void SetInterceptorCreators(
        std::vector<std::unique_ptr<
            grpc::experimental::ServerInterceptorFactoryInterface>>
            interceptor_creators) {
      builder_->interceptor_creators_ = std::move(interceptor_creators);
    }

    enum class ExternalConnectionType {
      FROM_FD = 0
    };

    std::unique_ptr<grpc::experimental::ExternalConnectionAcceptor>
    AddExternalConnectionAcceptor(ExternalConnectionType type,
                                  std::shared_ptr<ServerCredentials> creds);

    void SetAuthorizationPolicyProvider(
        std::shared_ptr<experimental::AuthorizationPolicyProviderInterface>
            provider);

    void EnableCallMetricRecording(
        experimental::ServerMetricRecorder* server_metric_recorder = nullptr);

    ServerBuilder& AddPassiveListener(
        std::shared_ptr<grpc::ServerCredentials> creds,
        std::unique_ptr<grpc::experimental::PassiveListener>& passive_listener);

   private:
    ServerBuilder* builder_;
  };

  ServerBuilder& SetContextAllocator(
      std::unique_ptr<grpc::ContextAllocator> context_allocator);

  ServerBuilder& RegisterCallbackGenericService(
      grpc::CallbackGenericService* service);

  /// NOTE: The function experimental() is not stable public API. It is a view

  experimental_type experimental() { return experimental_type(this); }

 protected:

  struct Port {
    std::string addr;
    std::shared_ptr<ServerCredentials> creds;
    int* selected_port;
  };

  typedef std::unique_ptr<std::string> HostString;
  struct NamedService {
    explicit NamedService(grpc::Service* s) : service(s) {}
    NamedService(const std::string& h, grpc::Service* s)
        : host(new std::string(h)), service(s) {}
    HostString host;
    grpc::Service* service;
  };

  std::vector<Port> ports() { return ports_; }

  std::vector<NamedService*> services() {
    std::vector<NamedService*> service_refs;
    service_refs.reserve(services_.size());
    for (auto& ptr : services_) {
      service_refs.push_back(ptr.get());
    }
    return service_refs;
  }

  std::vector<grpc::ServerBuilderOption*> options() {
    std::vector<grpc::ServerBuilderOption*> option_refs;
    option_refs.reserve(options_.size());
    for (auto& ptr : options_) {
      option_refs.push_back(ptr.get());
    }
    return option_refs;
  }

  void set_fetcher(grpc_server_config_fetcher* server_config_fetcher) {
    server_config_fetcher_ = server_config_fetcher;
  }

  virtual ChannelArguments BuildChannelArgs();

 private:
  friend class grpc::testing::ServerBuilderPluginTest;

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

  struct SyncServerSettings {
    SyncServerSettings()
        : num_cqs(1), min_pollers(1), max_pollers(2), cq_timeout_msec(10000) {}

    int num_cqs;

    int min_pollers;

    int max_pollers;

    int cq_timeout_msec;
  };

  int max_receive_message_size_;
  int max_send_message_size_;
  std::vector<std::unique_ptr<grpc::ServerBuilderOption>> options_;
  std::vector<std::unique_ptr<NamedService>> services_;
  std::vector<Port> ports_;
  std::vector<UnstartedPassiveListener> unstarted_passive_listeners_;

  SyncServerSettings sync_server_settings_;

  std::vector<grpc::ServerCompletionQueue*> cqs_;

  std::shared_ptr<grpc::ServerCredentials> creds_;
  std::vector<std::unique_ptr<grpc::ServerBuilderPlugin>> plugins_;
  grpc_resource_quota* resource_quota_;
  grpc::AsyncGenericService* generic_service_{nullptr};
  std::unique_ptr<ContextAllocator> context_allocator_;
  grpc::CallbackGenericService* callback_generic_service_{nullptr};

  struct {
    bool is_set;
    grpc_compression_level level;
  } maybe_default_compression_level_;
  struct {
    bool is_set;
    grpc_compression_algorithm algorithm;
  } maybe_default_compression_algorithm_;
  uint32_t enabled_compression_algorithms_bitset_;
  std::vector<
      std::unique_ptr<grpc::experimental::ServerInterceptorFactoryInterface>>
      interceptor_creators_;
  std::vector<std::shared_ptr<grpc::internal::ExternalConnectionAcceptorImpl>>
      acceptors_;
  grpc_server_config_fetcher* server_config_fetcher_ = nullptr;
  std::shared_ptr<experimental::AuthorizationPolicyProviderInterface>
      authorization_provider_;
  experimental::ServerMetricRecorder* server_metric_recorder_ = nullptr;
};

}

#endif
