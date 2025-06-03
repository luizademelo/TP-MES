Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

#include "src/core/lib/security/authorization/cel_authorization_engine.h"

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <algorithm>
#include <optional>
#include <utility>

#include "absl/log/log.h"
#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "upb/base/string_view.h"
#include "upb/message/map.h"

namespace grpc_core {

namespace {
// Constants defining the attribute names used in CEL expressions
constexpr char kUrlPath[] = "url_path";               // Request URL path
constexpr char kHost[] = "host";                      // Request host/authority
constexpr char kMethod[] = "method";                  // HTTP method
constexpr char kHeaders[] = "headers";                // Request headers
constexpr char kSourceAddress[] = "source_address";   // Peer IP address
constexpr char kSourcePort[] = "source_port";         // Peer port number
constexpr char kDestinationAddress[] = "destination_address";  // Local IP address
constexpr char kDestinationPort[] = "destination_port";        // Local port number
constexpr char kSpiffeId[] = "spiffe_id";             // SPIFFE ID of peer
constexpr char kCertServerName[] = "cert_server_name"; // Certificate server name
}  // namespace

// Creates a CEL authorization engine instance from RBAC policies
// Returns nullptr if the input policies are invalid
std::unique_ptr<CelAuthorizationEngine>
CelAuthorizationEngine::CreateCelAuthorizationEngine(
    const std::vector<envoy_config_rbac_v3_RBAC*>& rbac_policies) {
  // Validate policy count and order
  if (rbac_policies.empty() || rbac_policies.size() > 2) {
    LOG(ERROR) << "Invalid rbac policies vector. Must contain either one or "
                  "two rbac policies.";
    return nullptr;
  } else if (rbac_policies.size() == 2 &&
             (envoy_config_rbac_v3_RBAC_action(rbac_policies[0]) != kDeny ||
              envoy_config_rbac_v3_RBAC_action(rbac_policies[1]) != kAllow)) {
    LOG(ERROR) << "Invalid rbac policies vector. Must contain one deny policy "
                  "and one allow policy, in that order.";
    return nullptr;
  } else {
    // Create engine with valid policies
    return std::make_unique<CelAuthorizationEngine>(rbac_policies);
  }
}

// Constructor that processes RBAC policies and extracts CEL conditions
CelAuthorizationEngine::CelAuthorizationEngine(
    const std::vector<envoy_config_rbac_v3_RBAC*>& rbac_policies) {
  // Process each RBAC policy in the input vector
  for (const auto& rbac_policy : rbac_policies) {
    upb::Arena temp_arena;
    size_t iter = kUpb_Map_Begin;
    upb_StringView name;
    const envoy_config_rbac_v3_Policy* policy;
    
    // Iterate through all policies in the RBAC configuration
    while (envoy_config_rbac_v3_RBAC_policies_next(rbac_policy, &name, &policy,
                                                   &iter)) {
      // Extract policy name and condition
      const std::string policy_name(name.data, name.size);
      const google_api_expr_v1alpha1_Expr* condition =
          envoy_config_rbac_v3_Policy_condition(policy);

      // Serialize and parse the condition expression for storage
      size_t serial_len;
      const char* serialized = google_api_expr_v1alpha1_Expr_serialize(
          condition, temp_arena.ptr(), &serial_len);
      const google_api_expr_v1alpha1_Expr* parsed_condition =
          google_api_expr_v1alpha1_Expr_parse(serialized, serial_len,
                                              arena_.ptr());
      
      // Store condition based on policy action (allow/deny)
      if (envoy_config_rbac_v3_RBAC_action(rbac_policy) == kAllow) {
        allow_if_matched_.insert(std::pair(policy_name, parsed_condition));
      } else {
        deny_if_matched_.insert(std::pair(policy_name, parsed_condition));
      }
    }
  }
}

// Creates a CEL activation context populated with request attributes
std::unique_ptr<mock_cel::Activation> CelAuthorizationEngine::CreateActivation(
    const EvaluateArgs& args) {
  std::unique_ptr<mock_cel::Activation> activation;
  
  // Process each supported attribute
  for (const auto& elem : envoy_attributes_) {
    if (elem == kUrlPath) {
      // Add URL path to activation if present
      absl::string_view url_path(args.GetPath());
      if (!url_path.empty()) {
        activation->InsertValue(kUrlPath,
                                mock_cel::CelValue::CreateStringView(url_path));
      }
    } else if (elem == kHost) {
      // Add host/authority to activation if present
      absl::string_view host(args.GetAuthority());
      if (!host.empty()) {
        activation->InsertValue(kHost,
                                mock_cel::CelValue::CreateStringView(host));
      }
    } else if (elem == kMethod) {
      // Add HTTP method to activation if present
      absl::string_view method(args.GetMethod());
      if (!method.empty()) {
        activation->InsertValue(kMethod,
                                mock_cel::CelValue::CreateStringView(method));
      }
    } else if (elem == kHeaders) {
      // Process headers and create a CEL map
      std::vector<std::pair<mock_cel::CelValue, mock_cel::CelValue>>
          header_items;
      for (const auto& header_key : header_keys_) {
        std::string temp_value;
        std::optional<absl::string_view> header_value =
            args.GetHeaderValue(header_key, &temp_value);
        if (header_value.has_value()) {
          header_items.push_back(
              std::pair<mock_cel::CelValue, mock_cel::CelValue>(
                  mock_cel::CelValue::CreateStringView(header_key),
                  mock_cel::CelValue::CreateStringView(*header_value)));
        }
      }
      headers_ = mock_cel::ContainerBackedMapImpl::Create(
          absl::Span<std::pair<mock_cel::CelValue, mock_cel::CelValue>>(
              header_items));
      activation->InsertValue(kHeaders,
                              mock_cel::CelValue::CreateMap(headers_.get()));
    } else if (elem == kSourceAddress) {
      // Add peer address to activation if present
      absl::string_view source_address(args.GetPeerAddressString());
      if (!source_address.empty()) {
        activation->InsertValue(
            kSourceAddress,
            mock_cel::CelValue::CreateStringView(source_address));
      }
    } else if (elem == kSourcePort) {
      // Add peer port to activation
      activation->InsertValue(
          kSourcePort, mock_cel::CelValue::CreateInt64(args.GetPeerPort()));
    } else if (elem == kDestinationAddress) {
      // Add local address to activation if present
      absl::string_view destination_address(args.GetLocalAddressString());
      if (!destination_address.empty()) {
        activation->InsertValue(
            kDestinationAddress,
            mock_cel::CelValue::CreateStringView(destination_address));
      }
    } else if (elem == kDestinationPort) {
      // Add local port to activation
      activation->InsertValue(kDestinationPort, mock_cel::CelValue::CreateInt64(
                                                    args.GetLocalPort()));
    } else if (elem == kSpiffeId) {
      // Add SPIFFE ID to activation if present
      absl::string_view spiffe_id(args.GetSpiffeId());
      if (!spiffe_id.empty()) {
        activation->InsertValue(
            kSpiffeId, mock_cel::CelValue::CreateStringView(spiffe_id));
      }
    } else if (elem == kCertServerName) {
      // Add certificate server name to activation if present
      absl::string_view cert_server_name(args.GetCommonName());
      if (!cert_server_name.empty()) {
        activation->InsertValue(
            kCertServerName,
            mock_cel::CelValue::CreateStringView(cert_server_name));
      }
    } else {
      LOG(ERROR) << "Error: Authorization engine does not support evaluating "
                    "attribute "
                 << elem;
    }
  }
  return activation;
}

}  // namespace grpc_core
```