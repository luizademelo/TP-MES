Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

// Header file for ServerConfigSelectorFilter implementation
#include "src/core/server/server_config_selector_filter.h"

// Platform-specific support macros
#include <grpc/support/port_platform.h>

// Standard library includes
#include <functional>
#include <memory>
#include <optional>
#include <utility>

// Abseil library includes
#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"

// gRPC core includes
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/server/server_config_selector.h"
#include "src/core/service_config/service_config.h"
#include "src/core/service_config/service_config_call_data.h"
#include "src/core/util/latent_see.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/sync.h"

namespace grpc_core {

namespace {

// Filter implementation that applies server-side configuration selection
// based on incoming call metadata. This filter is used on the server side
// to select appropriate configurations for incoming RPCs.
class ServerConfigSelectorFilter final
    : public ImplementChannelFilter<ServerConfigSelectorFilter>,
      public InternallyRefCounted<ServerConfigSelectorFilter> {
 public:
  // Constructor taking a ServerConfigSelectorProvider
  explicit ServerConfigSelectorFilter(
      RefCountedPtr<ServerConfigSelectorProvider>
          server_config_selector_provider);

  // Returns the type name of this filter
  static absl::string_view TypeName() {
    return "server_config_selector_filter";
  }

  // Delete copy constructor and assignment operator
  ServerConfigSelectorFilter(const ServerConfigSelectorFilter&) = delete;
  ServerConfigSelectorFilter& operator=(const ServerConfigSelectorFilter&) =
      delete;

  // Factory method to create an instance of this filter
  static absl::StatusOr<OrphanablePtr<ServerConfigSelectorFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args);

  // Cleanup method called when the filter is being destroyed
  void Orphan() override;

  // Nested class representing call-specific state and operations
  class Call {
   public:
    // Handles client initial metadata and applies configuration selection
    absl::Status OnClientInitialMetadata(ClientMetadata& md,
                                         ServerConfigSelectorFilter* filter);
    
    // No-op interceptors for other call events
    static inline const NoInterceptor OnServerInitialMetadata;
    static inline const NoInterceptor OnServerTrailingMetadata;
    static inline const NoInterceptor OnClientToServerMessage;
    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnServerToClientMessage;
    static inline const NoInterceptor OnFinalize;
  };

  // Returns the current configuration selector
  absl::StatusOr<RefCountedPtr<ServerConfigSelector>> config_selector() {
    MutexLock lock(&mu_);
    return config_selector_.value();
  }

 private:
  // Watcher class for configuration selector updates
  class ServerConfigSelectorWatcher
      : public ServerConfigSelectorProvider::ServerConfigSelectorWatcher {
   public:
    explicit ServerConfigSelectorWatcher(
        RefCountedPtr<ServerConfigSelectorFilter> filter)
        : filter_(filter) {}
    
    // Callback for configuration selector updates
    void OnServerConfigSelectorUpdate(
        absl::StatusOr<RefCountedPtr<ServerConfigSelector>> update) override {
      MutexLock lock(&filter_->mu_);
      filter_->config_selector_ = std::move(update);
    }

   private:
    RefCountedPtr<ServerConfigSelectorFilter> filter_;
  };

  // Provider of configuration selector updates
  RefCountedPtr<ServerConfigSelectorProvider> server_config_selector_provider_;
  // Mutex protecting config_selector_
  Mutex mu_;
  // Current configuration selector, protected by mu_
  std::optional<absl::StatusOr<RefCountedPtr<ServerConfigSelector>>>
      config_selector_ ABSL_GUARDED_BY(mu_);
};

// Factory method implementation
absl::StatusOr<OrphanablePtr<ServerConfigSelectorFilter>>
ServerConfigSelectorFilter::Create(const ChannelArgs& args,
                                   ChannelFilter::Args) {
  // Get the ServerConfigSelectorProvider from channel args
  ServerConfigSelectorProvider* server_config_selector_provider =
      args.GetObject<ServerConfigSelectorProvider>();
  if (server_config_selector_provider == nullptr) {
    return absl::UnknownError("No ServerConfigSelectorProvider object found");
  }
  // Create and return a new filter instance
  return MakeOrphanable<ServerConfigSelectorFilter>(
      server_config_selector_provider->Ref());
}

// Constructor implementation
ServerConfigSelectorFilter::ServerConfigSelectorFilter(
    RefCountedPtr<ServerConfigSelectorProvider> server_config_selector_provider)
    : server_config_selector_provider_(
          std::move(server_config_selector_provider)) {
  // Ensure provider is not null
  CHECK(server_config_selector_provider_ != nullptr);
  // Create and register a watcher for configuration updates
  auto server_config_selector_watcher =
      std::make_unique<ServerConfigSelectorWatcher>(Ref());
  auto config_selector = server_config_selector_provider_->Watch(
      std::move(server_config_selector_watcher));
  MutexLock lock(&mu_);

  // Store initial configuration selector if not already set
  if (!config_selector_.has_value()) {
    config_selector_ = std::move(config_selector);
  }
}

// Cleanup method implementation
void ServerConfigSelectorFilter::Orphan() {
  // Cancel any ongoing watch when being destroyed
  if (server_config_selector_provider_ != nullptr) {
    server_config_selector_provider_->CancelWatch();
  }
  Unref();
}

// Handles client initial metadata and applies configuration selection
absl::Status ServerConfigSelectorFilter::Call::OnClientInitialMetadata(
    ClientMetadata& md, ServerConfigSelectorFilter* filter) {
  // Add latency tracing scope
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ServerConfigSelectorFilter::Call::OnClientInitialMetadata");
  
  // Get current configuration selector
  auto sel = filter->config_selector();
  if (!sel.ok()) return sel.status();
  
  // Get call-specific configuration based on metadata
  auto call_config = sel.value()->GetCallConfig(&md);
  if (!call_config.ok()) {
    return absl::UnavailableError(StatusToString(call_config.status()));
  }
  
  // Create and configure ServiceConfigCallData for this call
  auto* service_config_call_data =
      GetContext<Arena>()->New<ServiceConfigCallData>(GetContext<Arena>());
  service_config_call_data->SetServiceConfig(
      std::move(call_config->service_config), call_config->method_configs);
  
  return absl::OkStatus();
}

}  // namespace

// Global instance of the server configuration selector filter
const grpc_channel_filter kServerConfigSelectorFilter =
    MakePromiseBasedFilter<ServerConfigSelectorFilter,
                           FilterEndpoint::kServer>();

}  // namespace grpc_core
```