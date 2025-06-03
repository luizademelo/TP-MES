Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

// Header includes for stateful session filter implementation
#include "src/core/ext/filters/stateful_session/stateful_session_filter.h"

// Platform support and standard library includes
#include <grpc/support/port_platform.h>
#include <string.h>

#include <algorithm>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

// Abseil library includes for logging, string manipulation, etc.
#include "absl/log/check.h"
#include "absl/strings/escaping.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"

// gRPC core includes
#include "src/core/call/metadata_batch.h"
#include "src/core/config/core_configuration.h"
#include "src/core/ext/filters/stateful_session/stateful_session_service_config_parser.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/pipe.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/transport.h"

// XDS resolver related includes
#include "src/core/resolver/xds/xds_resolver_attributes.h"
#include "src/core/service_config/service_config_call_data.h"

// Utility includes
#include "src/core/util/crash.h"
#include "src/core/util/latent_see.h"
#include "src/core/util/time.h"

namespace grpc_core {

// Returns the unique type name for XdsOverrideHostAttribute
UniqueTypeName XdsOverrideHostAttribute::TypeName() {
  static UniqueTypeName::Factory kFactory("xds_override_host");
  return kFactory.Create();
}

// Static definition of the stateful session filter
const grpc_channel_filter StatefulSessionFilter::kFilter =
    MakePromiseBasedFilter<StatefulSessionFilter, FilterEndpoint::kClient,
                           kFilterExaminesServerInitialMetadata>();

// Creates a new StatefulSessionFilter instance
absl::StatusOr<std::unique_ptr<StatefulSessionFilter>>
StatefulSessionFilter::Create(const ChannelArgs&,
                              ChannelFilter::Args filter_args) {
  return std::make_unique<StatefulSessionFilter>(filter_args);
}

// StatefulSessionFilter constructor
StatefulSessionFilter::StatefulSessionFilter(ChannelFilter::Args filter_args)
    : index_(filter_args.instance_id()),  // Store the instance ID
      service_config_parser_index_(
          StatefulSessionServiceConfigParser::ParserIndex()) {}  // Store parser index

namespace {

// Allocates and concatenates two string views on the arena
absl::string_view AllocateStringOnArena(
    absl::string_view src1, absl::string_view src2 = absl::string_view()) {
  if (src1.empty() && src2.empty()) {
    return absl::string_view();
  }
  char* arena_allocated_value =
      static_cast<char*>(GetContext<Arena>()->Alloc(src1.size() + src2.size()));
  memcpy(arena_allocated_value, src1.data(), src1.size());
  if (!src2.empty()) {
    memcpy(arena_allocated_value + src1.size(), src2.data(), src2.size());
  }
  return absl::string_view(arena_allocated_value, src1.size() + src2.size());
}

// Updates server initial metadata with cookie information if needed
void MaybeUpdateServerInitialMetadata(
    const StatefulSessionMethodParsedConfig::CookieConfig* cookie_config,
    bool cluster_changed, absl::string_view actual_cluster,
    absl::string_view cookie_address_list,
    XdsOverrideHostAttribute* override_host_attribute,
    ServerMetadata& server_initial_metadata) {

  // Return early if no changes are needed
  if (cookie_address_list == override_host_attribute->actual_address_list() &&
      !cluster_changed) {
    return;
  }

  // Construct new cookie value
  std::string new_value = absl::StrCat(
      override_host_attribute->actual_address_list(), ";", actual_cluster);
  std::vector<std::string> parts = {absl::StrCat(
      *cookie_config->name, "=", absl::Base64Escape(new_value), "; HttpOnly")};
  
  // Add path if configured
  if (!cookie_config->path.empty()) {
    parts.emplace_back(absl::StrCat("Path=", cookie_config->path));
  }
  
  // Add TTL if configured
  if (cookie_config->ttl > Duration::Zero()) {
    parts.emplace_back(
        absl::StrCat("Max-Age=", cookie_config->ttl.as_timespec().tv_sec));
  }
  
  // Append the new cookie to metadata
  server_initial_metadata.Append(
      "set-cookie", Slice::FromCopiedString(absl::StrJoin(parts, "; ")),
      [](absl::string_view error, const Slice&) {
        Crash(absl::StrCat("ERROR ADDING set-cookie METADATA: ", error));
      });
}

// Determines which cluster to use based on cookie and service config
absl::string_view GetClusterToUse(
    absl::string_view cluster_from_cookie,
    ServiceConfigCallData* service_config_call_data) {

  // Get cluster attribute from service config
  auto cluster_attribute =
      service_config_call_data->GetCallAttribute<XdsClusterAttribute>();
  CHECK_NE(cluster_attribute, nullptr);
  auto current_cluster = cluster_attribute->cluster();
  static constexpr absl::string_view kClusterPrefix = "cluster:";

  // Remove cluster prefix if present
  if (!absl::ConsumePrefix(&current_cluster, kClusterPrefix)) {
    return absl::string_view();
  }

  // If no cookie cluster, use current cluster
  if (cluster_from_cookie.empty()) {
    return AllocateStringOnArena(current_cluster);
  }

  // Check if cookie cluster is valid for current route
  auto route_data =
      service_config_call_data->GetCallAttribute<XdsRouteStateAttribute>();
  CHECK_NE(route_data, nullptr);

  if (!route_data->HasClusterForRoute(cluster_from_cookie)) {
    return AllocateStringOnArena(current_cluster);
  }
  
  // Update cluster attribute with cookie cluster
  auto arena_allocated_cluster =
      AllocateStringOnArena(kClusterPrefix, cluster_from_cookie);
  cluster_attribute->set_cluster(arena_allocated_cluster);
  return absl::StripPrefix(arena_allocated_cluster, kClusterPrefix);
}

// Extracts cookie value from client metadata
std::string GetCookieValue(const ClientMetadata& client_initial_metadata,
                           absl::string_view cookie_name) {
  std::string buffer;
  // Get cookie header value
  auto header_value = client_initial_metadata.GetStringValue("cookie", &buffer);
  if (!header_value.has_value()) return "";

  // Find all cookies with matching name
  std::vector<absl::string_view> values;
  for (absl::string_view cookie : absl::StrSplit(*header_value, "; ")) {
    std::pair<absl::string_view, absl::string_view> kv =
        absl::StrSplit(cookie, absl::MaxSplits('=', 1));
    if (kv.first == cookie_name) values.push_back(kv.second);
  }
  if (values.empty()) return "";

  // Decode base64 encoded cookie value
  std::string decoded;
  if (absl::Base64Unescape(values.front(), &decoded)) {
    return decoded;
  }
  return "";
}

// Checks if request path matches configured path for cookie
bool IsConfiguredPath(absl::string_view configured_path,
                      const ClientMetadata& client_initial_metadata) {
  // If no path configured, always return true
  if (configured_path.empty()) {
    return true;
  }

  // Get request path from metadata
  const Slice* path_slice =
      client_initial_metadata.get_pointer(HttpPathMetadata());
  CHECK_NE(path_slice, nullptr);
  absl::string_view path = path_slice->as_string_view();

  // Check path prefix match
  if (!absl::StartsWith(path, configured_path)) {
    return false;
  }

  // Check for exact match or directory boundary
  return path.length() == configured_path.length() ||
         configured_path.back() == '/' || path[configured_path.length()] == '/';
}
}

// Handles client initial metadata processing
void StatefulSessionFilter::Call::OnClientInitialMetadata(
    ClientMetadata& md, StatefulSessionFilter* filter) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "StatefulSessionFilter::Call::OnClientInitialMetadata");

  // Get service config and method parameters
  auto* service_config_call_data = GetContext<ServiceConfigCallData>();
  CHECK_NE(service_config_call_data, nullptr);
  auto* method_params = static_cast<StatefulSessionMethodParsedConfig*>(
      service_config_call_data->GetMethodParsedConfig(
          filter->service_config_parser_index_));
  CHECK_NE(method_params, nullptr);
  
  // Get cookie configuration
  cookie_config_ = method_params->GetConfig(filter->index_);
  CHECK_NE(cookie_config_, nullptr);
  
  // Return early if no cookie name or path mismatch
  if (!cookie_config_->name.has_value() ||
      !IsConfiguredPath(cookie_config_->path, md)) {
    return;
  }

  // Process cookie value
  std::string cookie_value = GetCookieValue(md, *cookie_config_->name);
  std::pair<absl::string_view, absl::string_view> host_cluster =
      absl::StrSplit(cookie_value, absl::MaxSplits(';', 1));

  // Store address list from cookie
  if (!host_cluster.first.empty()) {
    cookie_address_list_ = AllocateStringOnArena(host_cluster.first);
  }

  // Create and set override host attribute
  override_host_attribute_ =
      GetContext<Arena>()->ManagedNew<XdsOverrideHostAttribute>(
          cookie_address_list_);
  service_config_call_data->SetCallAttribute(override_host_attribute_);

  // Determine cluster to use
  cluster_name_ =
      GetClusterToUse(host_cluster.second, service_config_call_data);
  cluster_changed_ = cluster_name_ != host_cluster.second;
  perform_filtering_ = true;
}

// Handles server initial metadata processing
void StatefulSessionFilter::Call::OnServerInitialMetadata(ServerMetadata& md) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "StatefulSessionFilter::Call::OnServerInitialMetadata");
  if (!perform_filtering_) return;

  // Update metadata with cookie if needed
  MaybeUpdateServerInitialMetadata(cookie_config_, cluster_changed_,
                                   cluster_name_, cookie_address_list_,
                                   override_host_attribute_, md);
}

// Handles server trailing metadata processing
void StatefulSessionFilter::Call::OnServerTrailingMetadata(ServerMetadata& md) {
  GRPC_LATENT_SEE_INNER_SCOPE(
      "StatefulSessionFilter::Call::OnServerTrailingMetadata");
  if (!perform_filtering_) return;

  // For trailers-only responses, update metadata with cookie
  if (md.get(GrpcTrailersOnly()).value_or(false)) {
    MaybeUpdateServerInitialMetadata(cookie_config_, cluster_changed_,
                                     cluster_name_, cookie_address_list_,
                                     override_host_attribute_, md);
  }
}

// Registers the stateful session filter with core configuration
void StatefulSessionFilterRegister(CoreConfiguration::Builder* builder) {
  StatefulSessionServiceConfigParser::Register(builder);
}

}
```