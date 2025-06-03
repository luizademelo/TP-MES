Here's the commented version of the code:

```c++
// Copyright 2015-2016 gRPC authors.

// Include necessary gRPC headers
#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/impl/compression_types.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <grpc/support/workaround_list.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/impl/server_builder_option.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/resource_quota.h>
#include <grpcpp/security/authorization_policy_provider.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/server_interface.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/support/server_interceptor.h>
#include <limits.h>
#include <string.h>

// Standard library includes
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Third-party includes
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/ext/transport/chttp2/server/chttp2_server.h"
#include "src/core/server/server.h"
#include "src/core/util/string.h"
#include "src/core/util/useful.h"
#include "src/cpp/server/external_connection_acceptor_impl.h"

namespace grpc {
namespace {

// Wrapper class for PassiveListener that maintains shared ownership
class PassiveListenerOwner final
    : public grpc_core::experimental::PassiveListener {
 public:
  // Constructor taking a shared_ptr to a PassiveListener
  explicit PassiveListenerOwner(std::shared_ptr<PassiveListener> listener)
      : listener_(std::move(listener)) {}

  // Accepts a connected endpoint and delegates to the wrapped listener
  absl::Status AcceptConnectedEndpoint(
      std::unique_ptr<grpc_event_engine::experimental::EventEngine::Endpoint>
          endpoint) override {
    return listener_->AcceptConnectedEndpoint(std::move(endpoint));
  }

  // Accepts a connected file descriptor and delegates to the wrapped listener
  absl::Status AcceptConnectedFd(int fd) override {
    return listener_->AcceptConnectedFd(fd);
  }

 private:
  std::shared_ptr<PassiveListener> listener_;  // The wrapped listener
};

}  // namespace

// Static variables for plugin management
static std::vector<std::unique_ptr<ServerBuilderPlugin> (*)()>*
    g_plugin_factory_list;
static gpr_once once_init_plugin_list = GPR_ONCE_INIT;

// Initializes the plugin factory list
static void do_plugin_list_init(void) {
  g_plugin_factory_list =
      new std::vector<std::unique_ptr<ServerBuilderPlugin> (*)()>();
}

// ServerBuilder constructor
ServerBuilder::ServerBuilder()
    : max_receive_message_size_(INT_MIN),
      max_send_message_size_(INT_MIN),
      sync_server_settings_(SyncServerSettings()),
      resource_quota_(nullptr) {
  // Initialize plugin list once
  gpr_once_init(&once_init_plugin_list, do_plugin_list_init);
  // Create all registered plugins
  for (const auto& value : *g_plugin_factory_list) {
    plugins_.emplace_back(value());
  }

  // Initialize compression settings
  enabled_compression_algorithms_bitset_ =
      (1u << GRPC_COMPRESS_ALGORITHMS_COUNT) - 1;
  memset(&maybe_default_compression_level_, 0,
         sizeof(maybe_default_compression_level_));
  memset(&maybe_default_compression_algorithm_, 0,
         sizeof(maybe_default_compression_algorithm_));
}

// ServerBuilder destructor
ServerBuilder::~ServerBuilder() {
  // Release resource quota if set
  if (resource_quota_ != nullptr) {
    grpc_resource_quota_unref(resource_quota_);
  }
}

// Adds a completion queue to the server
std::unique_ptr<grpc::ServerCompletionQueue> ServerBuilder::AddCompletionQueue(
    bool is_frequently_polled) {
  grpc::ServerCompletionQueue* cq = new grpc::ServerCompletionQueue(
      GRPC_CQ_NEXT,
      is_frequently_polled ? GRPC_CQ_DEFAULT_POLLING : GRPC_CQ_NON_LISTENING,
      nullptr);
  cqs_.push_back(cq);
  return std::unique_ptr<grpc::ServerCompletionQueue>(cq);
}

// Registers a service with the server
ServerBuilder& ServerBuilder::RegisterService(Service* service) {
  services_.emplace_back(new NamedService(service));
  return *this;
}

// Registers a service with a specific host
ServerBuilder& ServerBuilder::RegisterService(const std::string& host,
                                              Service* service) {
  services_.emplace_back(new NamedService(host, service));
  return *this;
}

// Registers an asynchronous generic service
ServerBuilder& ServerBuilder::RegisterAsyncGenericService(
    AsyncGenericService* service) {
  if (generic_service_ || callback_generic_service_) {
    LOG(ERROR) << "Adding multiple generic services is unsupported for now. "
                  "Dropping the service "
               << service;
  } else {
    generic_service_ = service;
  }
  return *this;
}

// Registers a callback generic service
ServerBuilder& ServerBuilder::RegisterCallbackGenericService(
    CallbackGenericService* service) {
  if (generic_service_ || callback_generic_service_) {
    LOG(ERROR) << "Adding multiple generic services is unsupported for now. "
                  "Dropping the service "
               << service;
  } else {
    callback_generic_service_ = service;
  }
  return *this;
}

// Sets the context allocator for the server
ServerBuilder& ServerBuilder::SetContextAllocator(
    std::unique_ptr<grpc::ContextAllocator> context_allocator) {
  context_allocator_ = std::move(context_allocator);
  return *this;
}

// Adds an external connection acceptor
std::unique_ptr<grpc::experimental::ExternalConnectionAcceptor>
ServerBuilder::experimental_type::AddExternalConnectionAcceptor(
    experimental_type::ExternalConnectionType type,
    std::shared_ptr<ServerCredentials> creds) {
  std::string name_prefix("external:");
  char count_str[GPR_LTOA_MIN_BUFSIZE];
  gpr_ltoa(static_cast<long>(builder_->acceptors_.size()), count_str);
  builder_->acceptors_.emplace_back(
      std::make_shared<grpc::internal::ExternalConnectionAcceptorImpl>(
          name_prefix.append(count_str), type, creds));
  return builder_->acceptors_.back()->GetAcceptor();
}

// Sets the authorization policy provider
void ServerBuilder::experimental_type::SetAuthorizationPolicyProvider(
    std::shared_ptr<experimental::AuthorizationPolicyProviderInterface>
        provider) {
  builder_->authorization_provider_ = std::move(provider);
}

// Enables call metric recording
void ServerBuilder::experimental_type::EnableCallMetricRecording(
    experimental::ServerMetricRecorder* server_metric_recorder) {
  builder_->AddChannelArgument(GRPC_ARG_SERVER_CALL_METRIC_RECORDING, 1);
  CHECK_EQ(builder_->server_metric_recorder_, nullptr);
  builder_->server_metric_recorder_ = server_metric_recorder;
}

// Sets a generic server option
ServerBuilder& ServerBuilder::SetOption(
    std::unique_ptr<ServerBuilderOption> option) {
  options_.push_back(std::move(option));
  return *this;
}

// Sets a synchronous server option
ServerBuilder& ServerBuilder::SetSyncServerOption(
    ServerBuilder::SyncServerOption option, int val) {
  switch (option) {
    case NUM_CQS:
      sync_server_settings_.num_cqs = val;
      break;
    case MIN_POLLERS:
      sync_server_settings_.min_pollers = val;
      break;
    case MAX_POLLERS:
      sync_server_settings_.max_pollers = val;
      break;
    case CQ_TIMEOUT_MSEC:
      sync_server_settings_.cq_timeout_msec = val;
      break;
  }
  return *this;
}

// Sets compression algorithm support status
ServerBuilder& ServerBuilder::SetCompressionAlgorithmSupportStatus(
    grpc_compression_algorithm algorithm, bool enabled) {
  if (enabled) {
    grpc_core::SetBit(&enabled_compression_algorithms_bitset_, algorithm);
  } else {
    grpc_core::ClearBit(&enabled_compression_algorithms_bitset_, algorithm);
  }
  return *this;
}

// Sets default compression level
ServerBuilder& ServerBuilder::SetDefaultCompressionLevel(
    grpc_compression_level level) {
  maybe_default_compression_level_.is_set = true;
  maybe_default_compression_level_.level = level;
  return *this;
}

// Sets default compression algorithm
ServerBuilder& ServerBuilder::SetDefaultCompressionAlgorithm(
    grpc_compression_algorithm algorithm) {
  maybe_default_compression_algorithm_.is_set = true;
  maybe_default_compression_algorithm_.algorithm = algorithm;
  return *this;
}

// Sets resource quota for the server
ServerBuilder& ServerBuilder::SetResourceQuota(
    const grpc::ResourceQuota& resource_quota) {
  if (resource_quota_ != nullptr) {
    grpc_resource_quota_unref(resource_quota_);
  }
  resource_quota_ = resource_quota.c_resource_quota();
  grpc_resource_quota_ref(resource_quota_);
  return *this;
}

// Adds a passive listener to the server
ServerBuilder& ServerBuilder::experimental_type::AddPassiveListener(
    std::shared_ptr<grpc::ServerCredentials> creds,
    std::unique_ptr<experimental::PassiveListener>& passive_listener) {
  auto core_passive_listener =
      std::make_shared<grpc_core::experimental::PassiveListenerImpl>();
  builder_->unstarted_passive_listeners_.emplace_back(core_passive_listener,
                                                      std::move(creds));
  passive_listener =
      std::make_unique<PassiveListenerOwner>(std::move(core_passive_listener));
  return *builder_;
}

// Adds a listening port to the server
ServerBuilder& ServerBuilder::AddListeningPort(
    const std::string& addr_uri, std::shared_ptr<ServerCredentials> creds,
    int* selected_port) {
  // Handle DNS URI scheme
  const std::string uri_scheme = "dns:";
  std::string addr = addr_uri;
  if (addr_uri.compare(0, uri_scheme.size(), uri_scheme) == 0) {
    size_t pos = uri_scheme.size();
    while (addr_uri[pos] == '/') ++pos;
    addr = addr_uri.substr(pos);
  }
  Port port = {addr, std::move(creds), selected_port};
  ports_.push_back(port);
  return *this;
}

// Builds channel arguments based on current configuration
ChannelArguments ServerBuilder::BuildChannelArgs() {
  ChannelArguments args;
  // Set message size limits if specified
  if (max_receive_message_size_ >= -1) {
    args.SetInt(GRPC_ARG_MAX_RECEIVE_MESSAGE_LENGTH, max_receive_message_size_);
  }
  if (max_send_message_size_ >= -1) {
    args.SetInt(GRPC_ARG_MAX_SEND_MESSAGE_LENGTH, max_send_message_size_);
  }
  
  // Apply all options
  for (const auto& option : options_) {
    option->UpdateArguments(&args);
    option->UpdatePlugins(&plugins_);
  }
  
  // Set compression settings
  args.SetInt(GRPC_COMPRESSION_CHANNEL_ENABLED_ALGORITHMS_BITSET,
              enabled_compression_algorithms_bitset_);
  if (maybe_default_compression_level_.is_set) {
    args.SetInt(GRPC_COMPRESSION_CHANNEL_DEFAULT_LEVEL,
                maybe_default_compression_level_.level);
  }
  if (maybe_default_compression_algorithm_.is_set) {
    args.SetInt(GRPC_COMPRESSION_CHANNEL_DEFAULT_ALGORITHM,
                maybe_default_compression_algorithm_.algorithm);
  }
  
  // Set resource quota if specified
  if (resource_quota_ != nullptr) {
    args.SetPointerWithVtable(GRPC_ARG_RESOURCE_QUOTA, resource_quota_,
                              grpc_resource_quota_arg_vtable());
  }
  
  // Update plugins and collect their arguments
  for (const auto& plugin : plugins_) {
    plugin->UpdateServerBuilder(this);
    plugin->UpdateChannelArguments(&args);
  }
  
  // Set authorization provider if specified
  if (authorization_provider_ != nullptr) {
    args.SetPointerWithVtable(GRPC_ARG_AUTHORIZATION_POLICY_PROVIDER,
                              authorization_provider_->c_provider(),
                              grpc_authorization_policy_provider_arg_vtable());
  }
  return args;
}

// Builds and starts the server
std::unique_ptr<grpc::Server> ServerBuilder::BuildAndStart() {
  ChannelArguments args = BuildChannelArgs();

  // Check for synchronous methods in services
  bool has_sync_methods = false;
  for (const auto& value : services_) {
    if (value->service->has_synchronous_methods()) {
      has_sync_methods = true;
      break;
    }
  }

  // Check for synchronous methods in plugins
  if (!has_sync_methods) {
    for (const auto& value : plugins_) {
      if (value->has_sync_methods()) {
        has_sync_methods = true;
        break;
      }
    }
  }

  // Create completion queues for synchronous server
  std::shared_ptr<std::vector<std::unique_ptr<grpc::ServerCompletionQueue>>>
      sync_server_cqs(
          std::make_shared<
              std::vector<std::unique_ptr<grpc::ServerCompletionQueue>>>());

  // Check for frequently polled CQs
  bool has_frequently_polled_cqs = false;
  for (const auto& cq : cqs_) {
    if (cq->IsFrequentlyPolled()) {
      has_frequently_polled_cqs = true;
      break;
    }
  }

  // Check for callback methods
  bool has_callback_methods = false;
  for (const auto& service : services_) {
    if (service->service->has_callback_methods()) {
      has_callback_methods = true;
      has_frequently_polled_cqs = true;
      break;
    }
  }

  if (callback_generic_service_ != nullptr) {
    has_frequently_polled_cqs = true;
  }

  // Determine if this is a hybrid server
  const bool is_hybrid_server = has_sync_methods && has_frequently_polled_cqs;

  // Create completion queues for synchronous methods
  if (has_sync_methods) {
    grpc_cq_polling_type polling_type =
        is_hybrid_server ? GRPC_CQ_NON_POLLING : GRPC_CQ_DEFAULT_POLLING;

    for (int i = 0; i < sync_server_settings_.num_cqs; i++) {
      sync_server_cqs->emplace_back(
          new grpc::ServerCompletionQueue(GRPC_CQ_NEXT, polling_type, nullptr));
    }
  }

  // Log server configuration
  if (has_sync_methods) {
    VLOG(2) << "Synchronous server. Num CQs: " << sync_server_settings_.num_cqs
            << ", Min pollers: " << sync_server_settings_.min_pollers
            << ", Max Pollers: " << sync_server_settings_.max_pollers
            << ", CQ timeout (msec): " << sync_server_settings_.cq_timeout_msec;
  }

  if (has_callback_methods) {
    VLOG(2) << "Callback server.";
  }

  // Create the server instance
  std::unique_ptr<grpc::Server> server(new grpc::Server(
      &args, sync_server_cqs, sync_server_settings_.min_pollers,
      sync_server_settings_.max_pollers, sync_server_settings_.cq_timeout_msec,
      std::move(acceptors_), server_config_fetcher_, resource_quota_,
      std::move(interceptor_creators_), server_metric_recorder_));

  ServerInitializer* initializer = server->initializer();

  // Register completion queues
  for (const auto& cq : *sync_server_cqs) {
    grpc_server_register_completion_queue(server->server_, cq->cq(), nullptr);
    has_frequently_polled_cqs = true;
  }

  // Register callback CQ if needed
  if (has_callback_methods || callback_generic_service_ != nullptr) {
    auto* cq = server->CallbackCQ();
    grpc_server_register_completion_queue(server->server_, cq->cq(), nullptr);
  }

  // Register all CQs and associate them with the server
  for (const auto& cq : cqs_) {
    grpc_server_register_completion_queue(server->server_, cq->cq(), nullptr);
    cq->RegisterServer(server.get());
  }

  // Add passive listeners if any
  for (auto& unstarted_listener : unstarted_passive_listeners_) {
    has_frequently_polled_cqs = true;
    auto passive_listener = unstarted_listener.passive_listener.lock();
    auto* core_server = grpc_core::Server::FromC(server->c_server());
    if (passive_listener != nullptr) {
      auto* creds = unstarted_listener.credentials->c_creds();
      if (creds == nullptr) {
        LOG(ERROR) << "Credentials missing for PassiveListener";
        return nullptr;
      }
      auto success = grpc_server_add_passive_listener(
          core_server, creds, std::move(passive_listener));
      if (!success.ok()) {