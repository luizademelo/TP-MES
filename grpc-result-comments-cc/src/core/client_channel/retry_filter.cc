Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary headers for retry filter functionality
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

// Using declarations for retry configuration types
using grpc_core::internal::RetryGlobalConfig;
using grpc_core::internal::RetryMethodConfig;
using grpc_core::internal::RetryServiceConfigParser;
using grpc_event_engine::experimental::EventEngine;

namespace grpc_core {

// Constructor for RetryFilter
// Initializes retry filter with channel arguments and sets up retry configuration
RetryFilter::RetryFilter(const ChannelArgs& args, grpc_error_handle* error)
    : client_channel_(args.GetObject<ClientChannelFilter>()),  // Get client channel from args
      event_engine_(args.GetObject<EventEngine>()),           // Get event engine from args
      per_rpc_retry_buffer_size_(GetMaxPerRpcRetryBufferSize(args)),  // Get max retry buffer size
      service_config_parser_index_(
          internal::RetryServiceConfigParser::ParserIndex()) {  // Get service config parser index

  // Get service config from channel args
  auto* service_config = args.GetObject<ServiceConfig>();
  if (service_config == nullptr) return;  // No service config, nothing to do

  // Get global retry configuration from service config
  const auto* config = static_cast<const RetryGlobalConfig*>(
      service_config->GetGlobalParsedConfig(
          RetryServiceConfigParser::ParserIndex()));
  if (config == nullptr) return;  // No retry config, nothing to do

  // Get server URI from channel args
  auto server_uri = args.GetString(GRPC_ARG_SERVER_URI);
  if (!server_uri.has_value()) {
    *error = GRPC_ERROR_CREATE(
        "server URI channel arg missing or wrong type in client channel "
        "filter");
    return;  // Missing server URI is an error
  }

  // Parse server URI to extract server name
  absl::StatusOr<URI> uri = URI::Parse(*server_uri);
  if (!uri.ok() || uri->path().empty()) {
    *error = GRPC_ERROR_CREATE("could not extract server name from target URI");
    return;  // Invalid URI is an error
  }
  std::string server_name(absl::StripPrefix(uri->path(), "/"));

  // Get or create retry throttle data for this server
  retry_throttle_data_ =
      internal::ServerRetryThrottleMap::Get()->GetDataForServer(
          server_name, config->max_milli_tokens(), config->milli_token_ratio());
}

// Gets the retry policy for the current method call
// Returns nullptr if no retry policy is configured
const RetryMethodConfig* RetryFilter::GetRetryPolicy(Arena* arena) {
  // Get service config call data from arena
  auto* svc_cfg_call_data = arena->GetContext<ServiceConfigCallData>();
  if (svc_cfg_call_data == nullptr) return nullptr;  // No call data available
  // Return the method-specific retry configuration
  return static_cast<const RetryMethodConfig*>(
      svc_cfg_call_data->GetMethodParsedConfig(service_config_parser_index_));
}

// Channel filter vtable defining the retry filter operations
const grpc_channel_filter RetryFilter::kVtable = {
    RetryFilter::LegacyCallData::StartTransportStreamOpBatch,  // Start transport stream op
    RetryFilter::StartTransportOp,                             // Start transport op
    sizeof(RetryFilter::LegacyCallData),                       // Size of call data
    RetryFilter::LegacyCallData::Init,                         // Call data init
    RetryFilter::LegacyCallData::SetPollent,                   // Set pollent
    RetryFilter::LegacyCallData::Destroy,                      // Call data destroy
    sizeof(RetryFilter),                                       // Size of filter
    RetryFilter::Init,                                         // Filter init
    grpc_channel_stack_no_post_init,                           // No post-init
    RetryFilter::Destroy,                                      // Filter destroy
    RetryFilter::GetChannelInfo,                               // Get channel info
    GRPC_UNIQUE_TYPE_NAME_HERE("retry_filter"),                // Filter type name
};

}  // namespace grpc_core
```

Key aspects covered in the comments:
1. File purpose and copyright notice
2. Constructor initialization and parameter handling
3. Service configuration parsing
4. Server URI processing and validation
5. Retry throttle data management
6. Method-level retry policy retrieval
7. Channel filter vtable structure and operations

The comments explain both the high-level purpose of each section and important implementation details, making the code more maintainable and understandable for future developers.