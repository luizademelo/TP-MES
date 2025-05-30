
// Copyright 2020 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/port_platform.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/config/core_configuration.h"
#include "src/core/ext/filters/message_size/message_size_filter.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/service_config/service_config.h"
#include "src/core/service_config/service_config_call_data.h"
#include "src/core/service_config/service_config_impl.h"
#include "src/core/service_config/service_config_parser.h"
#include "src/core/util/latent_see.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

namespace {

class ServiceConfigChannelArgFilter final
    : public ImplementChannelFilter<ServiceConfigChannelArgFilter> {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "service_config_channel_arg"; }

  static absl::StatusOr<std::unique_ptr<ServiceConfigChannelArgFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args) {
    return std::make_unique<ServiceConfigChannelArgFilter>(args);
  }

  explicit ServiceConfigChannelArgFilter(const ChannelArgs& args) {
    auto service_config_str = args.GetOwnedString(GRPC_ARG_SERVICE_CONFIG);
    if (service_config_str.has_value()) {
      auto service_config =
          ServiceConfigImpl::Create(args, *service_config_str);
      if (!service_config.ok()) {
        LOG(ERROR) << service_config.status().ToString();
      } else {
        service_config_ = std::move(*service_config);
      }
    }
  }

  class Call {
   public:
    void OnClientInitialMetadata(ClientMetadata& md,
                                 ServiceConfigChannelArgFilter* filter);
    static inline const NoInterceptor OnServerInitialMetadata;
    static inline const NoInterceptor OnServerTrailingMetadata;
    static inline const NoInterceptor OnClientToServerMessage;
    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnServerToClientMessage;
    static inline const NoInterceptor OnFinalize;
  };

 private:
  RefCountedPtr<ServiceConfig> service_config_;
};

void ServiceConfigChannelArgFilter::Call::OnClientInitialMetadata(
    ClientMetadata& md, ServiceConfigChannelArgFilter* filter) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ServiceConfigChannelArgFilter::Call::OnClientInitialMetadata");
  const ServiceConfigParser::ParsedConfigVector* method_configs = nullptr;
  if (filter->service_config_ != nullptr) {
    method_configs = filter->service_config_->GetMethodParsedConfigVector(
        md.get_pointer(HttpPathMetadata())->c_slice());
  }
  auto* arena = GetContext<Arena>();
  auto* service_config_call_data = arena->New<ServiceConfigCallData>(arena);
  service_config_call_data->SetServiceConfig(filter->service_config_,
                                             method_configs);
}

const grpc_channel_filter ServiceConfigChannelArgFilter::kFilter =
    MakePromiseBasedFilter<ServiceConfigChannelArgFilter,
                           FilterEndpoint::kClient>();

}

void RegisterServiceConfigChannelArgFilter(
    CoreConfiguration::Builder* builder) {
  builder->channel_init()
      ->RegisterFilter<ServiceConfigChannelArgFilter>(
          GRPC_CLIENT_DIRECT_CHANNEL)
      .ExcludeFromMinimalStack()
      .IfHasChannelArg(GRPC_ARG_SERVICE_CONFIG)
      .Before<ClientMessageSizeFilter>();
}

}
