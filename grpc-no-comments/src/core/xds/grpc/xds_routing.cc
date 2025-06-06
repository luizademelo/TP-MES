
// Copyright 2021 gRPC authors.

#include "src/core/xds/grpc/xds_routing.h"

#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <stdlib.h>

#include <algorithm>
#include <cctype>
#include <utility>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/matchers.h"
#include "src/core/xds/grpc/xds_http_filter.h"

namespace grpc_core {

namespace {
enum MatchType {
  EXACT_MATCH,
  SUFFIX_MATCH,
  PREFIX_MATCH,
  UNIVERSE_MATCH,
  INVALID_MATCH,
};

bool DomainMatch(MatchType match_type, absl::string_view domain_pattern_in,
                 absl::string_view expected_host_name_in) {

  std::string domain_pattern = std::string(domain_pattern_in);
  std::string expected_host_name = std::string(expected_host_name_in);
  std::transform(domain_pattern.begin(), domain_pattern.end(),
                 domain_pattern.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  std::transform(expected_host_name.begin(), expected_host_name.end(),
                 expected_host_name.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  if (match_type == EXACT_MATCH) {
    return domain_pattern == expected_host_name;
  } else if (match_type == SUFFIX_MATCH) {

    if (expected_host_name.size() < domain_pattern.size()) return false;
    absl::string_view pattern_suffix(domain_pattern.c_str() + 1);
    absl::string_view host_suffix(expected_host_name.c_str() +
                                  expected_host_name.size() -
                                  pattern_suffix.size());
    return pattern_suffix == host_suffix;
  } else if (match_type == PREFIX_MATCH) {

    if (expected_host_name.size() < domain_pattern.size()) return false;
    absl::string_view pattern_prefix(domain_pattern.c_str(),
                                     domain_pattern.size() - 1);
    absl::string_view host_prefix(expected_host_name.c_str(),
                                  pattern_prefix.size());
    return pattern_prefix == host_prefix;
  } else {
    return match_type == UNIVERSE_MATCH;
  }
}

MatchType DomainPatternMatchType(absl::string_view domain_pattern) {
  if (domain_pattern.empty()) return INVALID_MATCH;
  if (!absl::StrContains(domain_pattern, '*')) return EXACT_MATCH;
  if (domain_pattern == "*") return UNIVERSE_MATCH;
  if (domain_pattern[0] == '*') return SUFFIX_MATCH;
  if (domain_pattern[domain_pattern.size() - 1] == '*') return PREFIX_MATCH;
  return INVALID_MATCH;
}

}

std::optional<size_t> XdsRouting::FindVirtualHostForDomain(
    const VirtualHostListIterator& vhost_iterator, absl::string_view domain) {

  std::optional<size_t> target_index;
  MatchType best_match_type = INVALID_MATCH;
  size_t longest_match = 0;

  for (size_t i = 0; i < vhost_iterator.Size(); ++i) {
    const auto& domains = vhost_iterator.GetDomainsForVirtualHost(i);
    for (const std::string& domain_pattern : domains) {

      const MatchType match_type = DomainPatternMatchType(domain_pattern);

      CHECK(match_type != INVALID_MATCH);
      if (match_type > best_match_type) continue;
      if (match_type == best_match_type &&
          domain_pattern.size() <= longest_match) {
        continue;
      }

      if (!DomainMatch(match_type, domain_pattern, domain)) continue;

      target_index = i;
      best_match_type = match_type;
      longest_match = domain_pattern.size();
      if (best_match_type == EXACT_MATCH) break;
    }
    if (best_match_type == EXACT_MATCH) break;
  }
  return target_index;
}

namespace {

bool HeadersMatch(const std::vector<HeaderMatcher>& header_matchers,
                  grpc_metadata_batch* initial_metadata) {
  for (const auto& header_matcher : header_matchers) {
    std::string concatenated_value;
    if (!header_matcher.Match(XdsRouting::GetHeaderValue(
            initial_metadata, header_matcher.name(), &concatenated_value))) {
      return false;
    }
  }
  return true;
}

bool UnderFraction(const uint32_t fraction_per_million) {

  const uint32_t random_number = rand() % 1000000;
  return random_number < fraction_per_million;
}

}

std::optional<size_t> XdsRouting::GetRouteForRequest(
    const RouteListIterator& route_list_iterator, absl::string_view path,
    grpc_metadata_batch* initial_metadata) {
  for (size_t i = 0; i < route_list_iterator.Size(); ++i) {
    const XdsRouteConfigResource::Route::Matchers& matchers =
        route_list_iterator.GetMatchersForRoute(i);
    if (matchers.path_matcher.Match(path) &&
        HeadersMatch(matchers.header_matchers, initial_metadata) &&
        (!matchers.fraction_per_million.has_value() ||
         UnderFraction(*matchers.fraction_per_million))) {
      return i;
    }
  }
  return std::nullopt;
}

bool XdsRouting::IsValidDomainPattern(absl::string_view domain_pattern) {
  return DomainPatternMatchType(domain_pattern) != INVALID_MATCH;
}

std::optional<absl::string_view> XdsRouting::GetHeaderValue(
    grpc_metadata_batch* initial_metadata, absl::string_view header_name,
    std::string* concatenated_value) {
  // Note: If we ever allow binary headers here, we still need to

  if (absl::EndsWith(header_name, "-bin")) {
    return std::nullopt;
  } else if (header_name == "content-type") {
    return "application/grpc";
  }
  return initial_metadata->GetStringValue(header_name, concatenated_value);
}

namespace {

const XdsHttpFilterImpl::FilterConfig* FindFilterConfigOverride(
    const std::string& instance_name,
    const XdsRouteConfigResource::VirtualHost& vhost,
    const XdsRouteConfigResource::Route& route,
    const XdsRouteConfigResource::Route::RouteAction::ClusterWeight*
        cluster_weight) {

  if (cluster_weight != nullptr) {
    auto it = cluster_weight->typed_per_filter_config.find(instance_name);
    if (it != cluster_weight->typed_per_filter_config.end()) return &it->second;
  }

  auto it = route.typed_per_filter_config.find(instance_name);
  if (it != route.typed_per_filter_config.end()) return &it->second;

  it = vhost.typed_per_filter_config.find(instance_name);
  if (it != vhost.typed_per_filter_config.end()) return &it->second;

  return nullptr;
}

absl::StatusOr<XdsRouting::GeneratePerHttpFilterConfigsResult>
GeneratePerHTTPFilterConfigs(
    const XdsHttpFilterRegistry& http_filter_registry,
    const std::vector<XdsListenerResource::HttpConnectionManager::HttpFilter>&
        http_filters,
    const ChannelArgs& args,
    absl::FunctionRef<absl::StatusOr<XdsHttpFilterImpl::ServiceConfigJsonEntry>(
        const XdsHttpFilterImpl&,
        const XdsListenerResource::HttpConnectionManager::HttpFilter&)>
        generate_service_config) {
  XdsRouting::GeneratePerHttpFilterConfigsResult result;
  result.args = args;
  for (const auto& http_filter : http_filters) {

    const XdsHttpFilterImpl* filter_impl =
        http_filter_registry.GetFilterForType(
            http_filter.config.config_proto_type_name);
    CHECK_NE(filter_impl, nullptr);

    if (filter_impl->channel_filter() == nullptr) continue;

    result.args = filter_impl->ModifyChannelArgs(result.args);

    auto service_config_field =
        generate_service_config(*filter_impl, http_filter);
    if (!service_config_field.ok()) {
      return absl::FailedPreconditionError(absl::StrCat(
          "failed to generate service config for HTTP filter ",
          http_filter.name, ": ", service_config_field.status().ToString()));
    }
    if (service_config_field->service_config_field_name.empty()) continue;
    result.per_filter_configs[service_config_field->service_config_field_name]
        .push_back(service_config_field->element);
  }
  return result;
}

}

absl::StatusOr<XdsRouting::GeneratePerHttpFilterConfigsResult>
XdsRouting::GeneratePerHTTPFilterConfigsForMethodConfig(
    const XdsHttpFilterRegistry& http_filter_registry,
    const std::vector<XdsListenerResource::HttpConnectionManager::HttpFilter>&
        http_filters,
    const XdsRouteConfigResource::VirtualHost& vhost,
    const XdsRouteConfigResource::Route& route,
    const XdsRouteConfigResource::Route::RouteAction::ClusterWeight*
        cluster_weight,
    const ChannelArgs& args) {
  return GeneratePerHTTPFilterConfigs(
      http_filter_registry, http_filters, args,
      [&](const XdsHttpFilterImpl& filter_impl,
          const XdsListenerResource::HttpConnectionManager::HttpFilter&
              http_filter) {
        const XdsHttpFilterImpl::FilterConfig* config_override =
            FindFilterConfigOverride(http_filter.name, vhost, route,
                                     cluster_weight);

        return filter_impl.GenerateMethodConfig(http_filter.config,
                                                config_override);
      });
}

absl::StatusOr<XdsRouting::GeneratePerHttpFilterConfigsResult>
XdsRouting::GeneratePerHTTPFilterConfigsForServiceConfig(
    const XdsHttpFilterRegistry& http_filter_registry,
    const std::vector<XdsListenerResource::HttpConnectionManager::HttpFilter>&
        http_filters,
    const ChannelArgs& args) {
  return GeneratePerHTTPFilterConfigs(
      http_filter_registry, http_filters, args,
      [&](const XdsHttpFilterImpl& filter_impl,
          const XdsListenerResource::HttpConnectionManager::HttpFilter&
              http_filter) {
        return filter_impl.GenerateServiceConfig(http_filter.config);
      });
}

}
