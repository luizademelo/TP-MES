
// Copyright 2015 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/port_platform.h>

#include <optional>

#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/client_channel/client_channel_service_config.h"
#include "src/core/client_channel/retry_service_config.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/surface/channel_stack_type.h"

namespace grpc_core {

void BuildClientChannelConfiguration(CoreConfiguration::Builder* builder) {
  internal::ClientChannelServiceConfigParser::Register(builder);
  internal::RetryServiceConfigParser::Register(builder);
  builder->channel_init()
      ->RegisterV2Filter<ClientChannelFilter>(GRPC_CLIENT_CHANNEL)
      .Terminal();
}

}
