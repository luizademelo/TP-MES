Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Header file includes for XDS route configuration functionality
#include "src/core/xds/grpc/xds_route_config.h"

// Standard library includes
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

// Abseil string utilities
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
// RE2 regular expression library
#include "re2/re2.h"
// Core utility libraries
#include "src/core/util/match.h"
#include "src/core/util/matchers.h"

namespace grpc_core {

// Implementation of ToString() for RetryBackOff which formats the retry backoff configuration
std::string XdsRouteConfigResource::RetryPolicy::RetryBackOff::ToString()
    const {
  std::vector<std::string> contents;
  contents.push_back(
      absl::StrCat("RetryBackOff Base: ", base_interval.ToString()));
  contents.push_back(
      absl::StrCat("RetryBackOff max: ", max_interval.ToString()));
  return absl::StrJoin(contents, ",");
}

// Implementation of ToString() for RetryPolicy which formats the retry policy configuration
std::string XdsRouteConfigResource::RetryPolicy::ToString() const {
  std::vector<std::string> contents;
  contents.push_back(absl::StrFormat("num_retries=%d", num_retries));
  contents.push_back(retry_back_off.ToString());
  return absl::StrCat("{", absl::StrJoin(contents, ","), "}");
}

// Implementation of ToString() for Route Matchers which formats the route matching criteria
std::string XdsRouteConfigResource::Route::Matchers::ToString() const {
  std::vector<std::string> contents;
  contents.push_back(
      absl::StrFormat("PathMatcher{%s}", path_matcher.ToString()));
  // Add all header matchers to the output
  for (const HeaderMatcher& header_matcher : header_matchers) {
    contents.push_back(header_matcher.ToString());
  }
  // Add fraction per million if specified
  if (fraction_per_million.has_value()) {
    contents.push_back(absl::StrFormat("Fraction Per Million %d",
                                       fraction_per_million.value()));
  }
  return absl::StrJoin(contents, "\n");
}

// Copy constructor for HashPolicy::Header
XdsRouteConfigResource::Route::RouteAction::HashPolicy::Header::Header(
    const Header& other)
    : header_name(other.header_name),
      regex_substitution(other.regex_substitution) {
  // Deep copy of regex if it exists in the source
  if (other.regex != nullptr) {
    regex =
        std::make_unique<RE2>(other.regex->pattern(), other.regex->options());
  }
}

// Copy assignment operator for HashPolicy::Header
XdsRouteConfigResource::Route::RouteAction::HashPolicy::Header&
XdsRouteConfigResource::Route::RouteAction::HashPolicy::Header::operator=(
    const Header& other) {
  header_name = other.header_name;
  // Deep copy of regex if it exists in the source
  if (other.regex != nullptr) {
    regex =
        std::make_unique<RE2>(other.regex->pattern(), other.regex->options());
  }
  regex_substitution = other.regex_substitution;
  return *this;
}

// Move constructor for HashPolicy::Header
XdsRouteConfigResource::Route::RouteAction::HashPolicy::Header::Header(
    Header&& other) noexcept
    : header_name(std::move(other.header_name)),
      regex(std::move(other.regex)),
      regex_substitution(std::move(other.regex_substitution)) {}

// Move assignment operator for HashPolicy::Header
XdsRouteConfigResource::Route::RouteAction::HashPolicy::Header&
XdsRouteConfigResource::Route::RouteAction::HashPolicy::Header::operator=(
    Header&& other) noexcept {
  header_name = std::move(other.header_name);
  regex = std::move(other.regex);
  regex_substitution = std::move(other.regex_substitution);
  return *this;
}

// Equality comparison operator for HashPolicy::Header
bool XdsRouteConfigResource::Route::RouteAction::HashPolicy::Header::operator==(
    const Header& other) const {
  if (header_name != other.header_name) return false;
  // Compare regex patterns if both exist
  if (regex == nullptr) {
    if (other.regex != nullptr) return false;
  } else {
    if (other.regex == nullptr) return false;
    if (regex->pattern() != other.regex->pattern()) return false;
  }
  return regex_substitution == other.regex_substitution;
}

// Implementation of ToString() for HashPolicy::Header
std::string
XdsRouteConfigResource::Route::RouteAction::HashPolicy::Header::ToString()
    const {
  return absl::StrCat("Header ", header_name, "/",
                      (regex == nullptr) ? "" : regex->pattern(), "/",
                      regex_substitution);
}

// Implementation of ToString() for HashPolicy
std::string XdsRouteConfigResource::Route::RouteAction::HashPolicy::ToString()
    const {
  // Use pattern matching to format different policy types
  std::string type = Match(
      policy, [](const Header& header) { return header.ToString(); },
      [](const ChannelId&) -> std::string { return "ChannelId"; });
  return absl::StrCat("{", type, ", terminal=", terminal ? "true" : "false",
                      "}");
}

// Implementation of ToString() for ClusterWeight
std::string
XdsRouteConfigResource::Route::RouteAction::ClusterWeight::ToString() const {
  std::vector<std::string> contents;
  contents.push_back(absl::StrCat("cluster=", name));
  contents.push_back(absl::StrCat("weight=", weight));
  // Add typed per-filter configurations if they exist
  if (!typed_per_filter_config.empty()) {
    std::vector<std::string> parts;
    for (const auto& [key, config] : typed_per_filter_config) {
      parts.push_back(absl::StrCat(key, "=", config.ToString()));
    }
    contents.push_back(absl::StrCat("typed_per_filter_config={",
                                    absl::StrJoin(parts, ", "), "}"));
  }
  return absl::StrCat("{", absl::StrJoin(contents, ", "), "}");
}

// Implementation of ToString() for RouteAction
std::string XdsRouteConfigResource::Route::RouteAction::ToString() const {
  std::vector<std::string> contents;
  contents.reserve(hash_policies.size());
  // Add all hash policies to the output
  for (const HashPolicy& hash_policy : hash_policies) {
    contents.push_back(absl::StrCat("hash_policy=", hash_policy.ToString()));
  }
  // Add retry policy if specified
  if (retry_policy.has_value()) {
    contents.push_back(absl::StrCat("retry_policy=", retry_policy->ToString()));
  }
  // Use pattern matching to format different action types
  Match(
      action,
      [&contents](const ClusterName& cluster_name) {
        contents.push_back(
            absl::StrFormat("Cluster name: %s", cluster_name.cluster_name));
      },
      [&contents](const std::vector<ClusterWeight>& weighted_clusters) {
        for (const ClusterWeight& cluster_weight : weighted_clusters) {
          contents.push_back(cluster_weight.ToString());
        }
      },
      [&contents](
          const ClusterSpecifierPluginName& cluster_specifier_plugin_name) {
        contents.push_back(absl::StrFormat(
            "Cluster specifier plugin name: %s",
            cluster_specifier_plugin_name.cluster_specifier_plugin_name));
      });
  // Add max stream duration if specified
  if (max_stream_duration.has_value()) {
    contents.push_back(max_stream_duration->ToString());
  }
  // Add auto host rewrite flag if true
  if (auto_host_rewrite) contents.push_back("auto_host_rewrite=true");
  return absl::StrCat("{", absl::StrJoin(contents, ", "), "}");
}

// Implementation of ToString() for Route
std::string XdsRouteConfigResource::Route::ToString() const {
  std::vector<std::string> contents;
  contents.push_back(matchers.ToString());
  // Handle different route action types
  auto* route_action =
      std::get_if<XdsRouteConfigResource::Route::RouteAction>(&action);
  if (route_action != nullptr) {
    contents.push_back(absl::StrCat("route=", route_action->ToString()));
  } else if (std::holds_alternative<
                 XdsRouteConfigResource::Route::NonForwardingAction>(action)) {
    contents.push_back("non_forwarding_action={}");
  } else {
    contents.push_back("unknown_action={}");
  }
  // Add typed per-filter configurations if they exist
  if (!typed_per_filter_config.empty()) {
    contents.push_back("typed_per_filter_config={");
    for (const auto& [name, config] : typed_per_filter_config) {
      contents.push_back(absl::StrCat("  ", name, "=", config.ToString()));
    }
    contents.push_back("}");
  }
  return absl::StrJoin(contents, "\n");
}

// Implementation of ToString() for VirtualHost
std::string XdsRouteConfigResource::VirtualHost::ToString() const {
  std::vector<std::string> parts;
  parts.push_back(
      absl::StrCat("vhost={\n"
                   "  domains=[",
                   absl::StrJoin(domains, ", "),
                   "]\n"
                   "  routes=[\n"));
  // Add all routes to the output
  for (const XdsRouteConfigResource::Route& route : routes) {
    parts.push_back("    {\n");
    parts.push_back(route.ToString());
    parts.push_back("\n    }\n");
  }
  parts.push_back("  ]\n");
  parts.push_back("  typed_per_filter_config={\n");
  // Add all typed per-filter configurations
  for (const auto& [name, config] : typed_per_filter_config) {
    parts.push_back(absl::StrCat("    ", name, "=", config.ToString(), "\n"));
  }
  parts.push_back("  }\n");
  parts.push_back("}\n");
  return absl::StrJoin(parts, "");
}

// Implementation of ToString() for the entire XdsRouteConfigResource
std::string XdsRouteConfigResource::ToString() const {
  std::vector<std::string> parts;
  parts.reserve(virtual_hosts.size());
  // Add all virtual hosts to the output
  for (const VirtualHost& vhost : virtual_hosts) {
    parts.push_back(vhost.ToString());
  }
  parts.push_back("cluster_specifier_plugins={\n");
  // Add all cluster specifier plugins
  for (const auto& [name, plugin] : cluster_specifier_plugin_map) {
    parts.push_back(absl::StrFormat("%s={%s}\n", name, plugin));
  }
  parts.push_back("}");
  return absl::StrJoin(parts, "");
}

}  // namespace grpc_core
```