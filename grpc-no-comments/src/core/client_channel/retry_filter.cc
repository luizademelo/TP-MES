
// Copyright 2015 gRPC authors.

#include "src/core/client_channel/retry_filter.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <optional>
#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/strip.h"
#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/client_channel/retry_filter_legacy_call_data.h"
#include "src/core/client_channel/retry_service_config.h"
#include "src/core/client_channel/retry_throttle.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/service_config/service_config.h"
#include "src/core/service_config/service_config_call_data.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/uri.h"

using grpc_core::internal::RetryGlobalConfig;
using grpc_core::internal::RetryMethodConfig;
using grpc_core::internal::RetryServiceConfigParser;
using grpc_event_engine::experimental::EventEngine;

namespace grpc_core {

RetryFilter::RetryFilter(const ChannelArgs& args, grpc_error_handle* error)
    : client_channel_(args.GetObject<ClientChannelFilter>()),
      event_engine_(args.GetObject<EventEngine>()),
      per_rpc_retry_buffer_size_(GetMaxPerRpcRetryBufferSize(args)),
      service_config_parser_index_(
          internal::RetryServiceConfigParser::ParserIndex()) {

  auto* service_config = args.GetObject<ServiceConfig>();
  if (service_config == nullptr) return;
  const auto* config = static_cast<const RetryGlobalConfig*>(
      service_config->GetGlobalParsedConfig(
          RetryServiceConfigParser::ParserIndex()));
  if (config == nullptr) return;

  auto server_uri = args.GetString(GRPC_ARG_SERVER_URI);
  if (!server_uri.has_value()) {
    *error = GRPC_ERROR_CREATE(
        "server URI channel arg missing or wrong type in client channel "
        "filter");
    return;
  }
  absl::StatusOr<URI> uri = URI::Parse(*server_uri);
  if (!uri.ok() || uri->path().empty()) {
    *error = GRPC_ERROR_CREATE("could not extract server name from target URI");
    return;
  }
  std::string server_name(absl::StripPrefix(uri->path(), "/"));

  retry_throttle_data_ =
      internal::ServerRetryThrottleMap::Get()->GetDataForServer(
          server_name, config->max_milli_tokens(), config->milli_token_ratio());
}

const RetryMethodConfig* RetryFilter::GetRetryPolicy(Arena* arena) {
  auto* svc_cfg_call_data = arena->GetContext<ServiceConfigCallData>();
  if (svc_cfg_call_data == nullptr) return nullptr;
  return static_cast<const RetryMethodConfig*>(
      svc_cfg_call_data->GetMethodParsedConfig(service_config_parser_index_));
}

const grpc_channel_filter RetryFilter::kVtable = {
    RetryFilter::LegacyCallData::StartTransportStreamOpBatch,
    RetryFilter::StartTransportOp,
    sizeof(RetryFilter::LegacyCallData),
    RetryFilter::LegacyCallData::Init,
    RetryFilter::LegacyCallData::SetPollent,
    RetryFilter::LegacyCallData::Destroy,
    sizeof(RetryFilter),
    RetryFilter::Init,
    grpc_channel_stack_no_post_init,
    RetryFilter::Destroy,
    RetryFilter::GetChannelInfo,
    GRPC_UNIQUE_TYPE_NAME_HERE("retry_filter"),
};

}
