Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Header file for server load reporting filter implementation
#include "src/core/ext/filters/load_reporting/server_load_reporting_filter.h"

// Standard includes for gRPC security, channel arguments, status codes, etc.
#include <grpc/grpc_security.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <stdint.h>
#include <stdlib.h>

// C++ standard includes
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <utility>

// Abseil includes for containers, logging, strings, etc.
#include "absl/container/inlined_vector.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/ascii.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"

// OpenCensus includes for metrics collection
#include "opencensus/stats/stats.h"
#include "opencensus/tags/tag_key.h"

// gRPC core includes
#include "src/core/call/call_finalization.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/config/core_configuration.h"
#include "src/core/ext/filters/load_reporting/registered_opencensus_objects.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_utils.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/transport/auth_context.h"
#include "src/core/util/latent_see.h"
#include "src/core/util/uri.h"

// Load reporting constants
#include "src/cpp/server/load_reporter/constants.h"

namespace grpc_core {

// Constants for encoded IP address lengths
constexpr char kEncodedIpv4AddressLengthString[] = "08";
constexpr char kEncodedIpv6AddressLengthString[] = "32";
constexpr char kEmptyAddressLengthString[] = "00";

// Creates a new ServerLoadReportingFilter instance
absl::StatusOr<std::unique_ptr<ServerLoadReportingFilter>>
ServerLoadReportingFilter::Create(const ChannelArgs& channel_args,
                                  ChannelFilter::Args) {
  // Create a new filter instance
  auto filter = std::make_unique<ServerLoadReportingFilter>();
  
  // Get authentication context from channel args
  const auto* auth_context = channel_args.GetObject<grpc_auth_context>();
  
  // If peer is authenticated, extract peer identity
  if (auth_context != nullptr &&
      grpc_auth_context_peer_is_authenticated(auth_context)) {
    grpc_auth_property_iterator auth_it =
        grpc_auth_context_peer_identity(auth_context);
    const grpc_auth_property* auth_property =
        grpc_auth_property_iterator_next(&auth_it);
    if (auth_property != nullptr) {
      filter->peer_identity_ =
          std::string(auth_property->value, auth_property->value_length);
    }
  }
  return std::move(filter);
}

namespace {

// Helper function to get client IP address in a format safe for Census
std::string GetCensusSafeClientIpString(
    const ClientMetadata& initial_metadata) {
  // Get client URI from metadata
  const Slice* client_uri_slice = initial_metadata.get_pointer(PeerString());
  if (client_uri_slice == nullptr) {
    LOG(ERROR) << "Unable to extract client URI string (peer string) from gRPC "
                  "metadata.";
    return "";
  }
  
  // Parse client URI
  absl::StatusOr<URI> client_uri =
      URI::Parse(client_uri_slice->as_string_view());
  if (!client_uri.ok()) {
    LOG(ERROR) << "Unable to parse the client URI string (peer string) to a "
                  "client URI. Error: "
               << client_uri.status();
    return "";
  }

  // Resolve address from URI
  grpc_resolved_address resolved_address;
  bool success = grpc_parse_uri(*client_uri, &resolved_address);
  if (!success) {
    LOG(ERROR) << "Unable to parse client URI into a grpc_resolved_address.";
    return "";
  }

  // Convert address to appropriate format based on IP version
  grpc_sockaddr* addr = reinterpret_cast<grpc_sockaddr*>(resolved_address.addr);
  if (addr->sa_family == GRPC_AF_INET) {
    // Handle IPv4 address
    grpc_sockaddr_in* addr4 = reinterpret_cast<grpc_sockaddr_in*>(addr);
    return absl::StrFormat("%08x", grpc_ntohl(addr4->sin_addr.s_addr));
  } else if (addr->sa_family == GRPC_AF_INET6) {
    // Handle IPv6 address
    grpc_sockaddr_in6* addr6 = reinterpret_cast<grpc_sockaddr_in6*>(addr);
    std::string client_ip;
    client_ip.reserve(32);
    uint32_t* addr6_next_long = reinterpret_cast<uint32_t*>(&addr6->sin6_addr);
    for (size_t i = 0; i < 4; ++i) {
      absl::StrAppendFormat(&client_ip, "%08x", grpc_ntohl(*addr6_next_long++));
    }
    return client_ip;
  } else {
    // Unsupported address family
    GPR_UNREACHABLE_CODE(abort());
  }
}

// Creates a combined string of client IP and load reporting token
std::string MakeClientIpAndLrToken(absl::string_view lr_token,
                                   const ClientMetadata& initial_metadata) {
  std::string client_ip = GetCensusSafeClientIpString(initial_metadata);
  absl::string_view prefix;
  switch (client_ip.length()) {
    case 0:  // Empty address
      prefix = kEmptyAddressLengthString;
      break;
    case 8:  // IPv4 address
      prefix = kEncodedIpv4AddressLengthString;
      break;
    case 32:  // IPv6 address
      prefix = kEncodedIpv6AddressLengthString;
      break;
    default:  // Invalid length
      GPR_UNREACHABLE_CODE(abort());
  }
  return absl::StrCat(prefix, client_ip, lr_token);
}

// Maps gRPC status codes to load reporting status tags
const char* GetStatusTagForStatus(grpc_status_code status) {
  switch (status) {
    case GRPC_STATUS_OK:
      return grpc::load_reporter::kCallStatusOk;
    case GRPC_STATUS_UNKNOWN:
    case GRPC_STATUS_DEADLINE_EXCEEDED:
    case GRPC_STATUS_UNIMPLEMENTED:
    case GRPC_STATUS_INTERNAL:
    case GRPC_STATUS_UNAVAILABLE:
    case GRPC_STATUS_DATA_LOSS:
      return grpc::load_reporter::kCallStatusServerError;
    default:
      return grpc::load_reporter::kCallStatusClientError;
  }
}
}  // namespace

// Handles client initial metadata
void ServerLoadReportingFilter::Call::OnClientInitialMetadata(
    ClientMetadata& md, ServerLoadReportingFilter* filter) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ServerLoadReportingFilter::Call::OnClientInitialMetadata");

  // Extract service method from path metadata
  Slice service_method;
  if (const Slice* path = md.get_pointer(HttpPathMetadata())) {
    service_method = path->Ref();
  }
  
  // Extract target host from authority metadata
  if (const Slice* authority = md.get_pointer(HttpAuthorityMetadata())) {
    target_host_ = absl::AsciiStrToLower(authority->as_string_view());
  }
  
  // Take load balancing token from metadata
  auto lb_token = md.Take(LbTokenMetadata()).value_or(Slice());
  
  // Create combined client IP and load reporting token
  client_ip_and_lr_token_ =
      MakeClientIpAndLrToken(lb_token.as_string_view(), md);

  // Record start count metric with relevant tags
  opencensus::stats::Record(
      {{::grpc::load_reporter::MeasureStartCount(), 1}},
      {{::grpc::load_reporter::TagKeyToken(),
        {client_ip_and_lr_token_.data(), client_ip_and_lr_token_.length()}},
       {::grpc::load_reporter::TagKeyHost(),
        {target_host_.data(), target_host_.length()}},
       {::grpc::load_reporter::TagKeyUserId(),
        {filter->peer_identity_.data(), filter->peer_identity_.length()}}});
}

// Handles server trailing metadata
void ServerLoadReportingFilter::Call::OnServerTrailingMetadata(
    ServerMetadata& md, ServerLoadReportingFilter* filter) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "ServerLoadReportingFilter::Call::OnServerTrailingMetadata");
  
  // Process load balancing cost bins
  const auto& costs = md.Take(LbCostBinMetadata());
  for (const auto& cost : costs) {
    // Record cost metrics with relevant tags
    opencensus::stats::Record(
        {{::grpc::load_reporter::MeasureOtherCallMetric(), cost.cost}},
        {{::grpc::load_reporter::TagKeyToken(),
          {client_ip_and_lr_token_.data(), client_ip_and_lr_token_.length()}},
         {::grpc::load_reporter::TagKeyHost(),
          {target_host_.data(), target_host_.length()}},
         {::grpc::load_reporter::TagKeyUserId(),
          {filter->peer_identity_.data(), filter->peer_identity_.length()}},
         {::grpc::load_reporter::TagKeyMetricName(),
          {cost.name.data(), cost.name.length()}}});
  }
}

// Handles call finalization
void ServerLoadReportingFilter::Call::OnFinalize(
    const grpc_call_final_info* final_info, ServerLoadReportingFilter* filter) {
  GRPC_LATENT_SEE_INNER_SCOPE("ServerLoadReportingFilter::Call::OnFinalize");
  if (final_info == nullptr) return;

  // Record end metrics with call statistics
  opencensus::stats::Record(
      {{::grpc::load_reporter::MeasureEndCount(), 1},
       {::grpc::load_reporter::MeasureEndBytesSent(),
        final_info->stats.transport_stream_stats.outgoing.data_bytes},
       {::grpc::load_reporter::MeasureEndBytesReceived(),
        final_info->stats.transport_stream_stats.incoming.data_bytes},
       {::grpc::load_reporter::MeasureEndLatencyMs(),
        gpr_time_to_millis(final_info->stats.latency)}},
      {{::grpc::load_reporter::TagKeyToken(),
        {client_ip_and_lr_token_.data(), client_ip_and_lr_token_.length()}},
       {::grpc::load_reporter::TagKeyHost(),
        {target_host_.data(), target_host_.length()}},
       {::grpc::load_reporter::TagKeyUserId(),
        {filter->peer_identity_.data(), filter->peer_identity_.length()}},
       {::grpc::load_reporter::TagKeyStatus(),
        GetStatusTagForStatus(final_info->final_status)}});
}

// Static filter definition
const grpc_channel_filter ServerLoadReportingFilter::kFilter =
    MakePromiseBasedFilter<ServerLoadReportingFilter,
                           FilterEndpoint::kServer>();

// Static registrar for the filter
struct ServerLoadReportingFilterStaticRegistrar {
  ServerLoadReportingFilterStaticRegistrar() {
    CoreConfiguration::RegisterEphemeralBuilder(
        [](CoreConfiguration::Builder* builder) {
          // Register load reporting measures
          grpc::load_reporter::MeasureStartCount();
          grpc::load_reporter::MeasureEndCount();
          grpc::load_reporter::MeasureEndBytesSent();
          grpc::load_reporter::MeasureEndBytesReceived();
          grpc::load_reporter::MeasureEndLatencyMs();
          grpc::load_reporter::MeasureOtherCallMetric();
          
          // Register the filter if load reporting is enabled
          builder->channel_init()
              ->RegisterFilter<ServerLoadReportingFilter>(GRPC_SERVER_CHANNEL)
              .IfChannelArg(GRPC_ARG_ENABLE_LOAD_REPORTING, false);
        });
  }
} server_load_reporting_filter_static_registrar;

}  // namespace grpc_core
```