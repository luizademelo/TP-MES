Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_BOOTSTRAP_GRPC_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_BOOTSTRAP_GRPC_H

#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/certificate_provider_store.h"
#include "src/core/xds/grpc/xds_audit_logger_registry.h"
#include "src/core/xds/grpc/xds_cluster_specifier_plugin.h"
#include "src/core/xds/grpc/xds_http_filter_registry.h"
#include "src/core/xds/grpc/xds_lb_policy_registry.h"
#include "src/core/xds/grpc/xds_server_grpc.h"
#include "src/core/xds/xds_client/xds_bootstrap.h"

namespace grpc_core {

// GrpcXdsBootstrap is the gRPC implementation of the XdsBootstrap interface,
// containing configuration needed to initialize an XdsClient.
class GrpcXdsBootstrap final : public XdsBootstrap {
 public:
  // GrpcNode represents the node identifier information in the bootstrap config
  class GrpcNode final : public Node {
   public:
    // Returns the node identifier
    const std::string& id() const override { return id_; }
    // Returns the node cluster name
    const std::string& cluster() const override { return cluster_; }
    // Returns the node's locality region
    const std::string& locality_region() const override {
      return locality_.region;
    }
    // Returns the node's locality zone
    const std::string& locality_zone() const override { return locality_.zone; }
    // Returns the node's locality sub-zone
    const std::string& locality_sub_zone() const override {
      return locality_.sub_zone;
    }
    // Returns the node's metadata
    const Json::Object& metadata() const override { return metadata_; }

    // Returns the JSON loader interface for parsing node configuration
    static const JsonLoaderInterface* JsonLoader(const JsonArgs&);

   private:
    // Locality information containing region, zone, and sub-zone
    struct Locality {
      std::string region;
      std::string zone;
      std::string sub_zone;

      // Returns the JSON loader interface for parsing locality configuration
      static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
    };

    std::string id_;          // Unique identifier for the node
    std::string cluster_;     // Cluster the node belongs to
    Locality locality_;       // Geographical location information
    Json::Object metadata_;   // Additional metadata about the node
  };

  // GrpcAuthority represents an authority in the xDS configuration
  class GrpcAuthority final : public Authority {
   public:
    // Returns a list of xDS servers for this authority
    std::vector<const XdsServer*> servers() const override {
      std::vector<const XdsServer*> servers;
      servers.reserve(servers_.size());
      for (const auto& server : servers_) {
        servers.emplace_back(&server);
      }
      return servers;
    }

    // Returns the client listener resource name template for this authority
    const std::string& client_listener_resource_name_template() const {
      return client_listener_resource_name_template_;
    }

    // Returns the JSON loader interface for parsing authority configuration
    static const JsonLoaderInterface* JsonLoader(const JsonArgs&);

   private:
    std::vector<GrpcXdsServer> servers_;  // List of xDS servers
    std::string client_listener_resource_name_template_;  // Resource name template
  };

  // Creates a GrpcXdsBootstrap instance from a JSON string
  static absl::StatusOr<std::unique_ptr<GrpcXdsBootstrap>> Create(
      absl::string_view json_string);

  // Returns the JSON loader interface for parsing bootstrap configuration
  static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
  
  // Performs post-loading validation and processing of JSON configuration
  void JsonPostLoad(const Json& json, const JsonArgs& args,
                    ValidationErrors* errors);

  // Returns a string representation of the bootstrap configuration
  std::string ToString() const override;

  // Returns a list of xDS servers from the bootstrap configuration
  std::vector<const XdsServer*> servers() const override {
    std::vector<const XdsServer*> servers;
    servers.reserve(servers_.size());
    for (const auto& server : servers_) {
      servers.emplace_back(&server);
    }
    return servers;
  }

  // Returns the node configuration if present
  const Node* node() const override {
    return node_.has_value() ? &*node_ : nullptr;
  }
  
  // Looks up an authority by name
  const Authority* LookupAuthority(const std::string& name) const override;

  // Returns the default client listener resource name template
  const std::string& client_default_listener_resource_name_template() const {
    return client_default_listener_resource_name_template_;
  }
  
  // Returns the server listener resource name template
  const std::string& server_listener_resource_name_template() const {
    return server_listener_resource_name_template_;
  }
  
  // Returns the certificate providers configuration
  const CertificateProviderStore::PluginDefinitionMap& certificate_providers()
      const {
    return certificate_providers_;
  }
  
  // Returns the HTTP filter registry
  const XdsHttpFilterRegistry& http_filter_registry() const {
    return http_filter_registry_;
  }
  
  // Returns the cluster specifier plugin registry
  const XdsClusterSpecifierPluginRegistry& cluster_specifier_plugin_registry()
      const {
    return cluster_specifier_plugin_registry_;
  }
  
  // Returns the load balancing policy registry
  const XdsLbPolicyRegistry& lb_policy_registry() const {
    return lb_policy_registry_;
  }
  
  // Returns the audit logger registry
  const XdsAuditLoggerRegistry& audit_logger_registry() const {
    return audit_logger_registry_;
  }

  // Returns the map of configured authorities
  const std::map<std::string, GrpcAuthority>& authorities() const {
    return authorities_;
  }

 private:
  std::vector<GrpcXdsServer> servers_;  // List of xDS servers
  std::optional<GrpcNode> node_;        // Node configuration (optional)
  std::string client_default_listener_resource_name_template_;  // Default client listener template
  std::string server_listener_resource_name_template_;  // Server listener template
  std::map<std::string, GrpcAuthority> authorities_;    // Map of authorities by name
  CertificateProviderStore::PluginDefinitionMap certificate_providers_;  // Certificate providers
  XdsHttpFilterRegistry http_filter_registry_;          // HTTP filter registry
  XdsClusterSpecifierPluginRegistry cluster_specifier_plugin_registry_;  // Cluster specifier plugins
  XdsLbPolicyRegistry lb_policy_registry_;              // LB policy registry
  XdsAuditLoggerRegistry audit_logger_registry_;        // Audit logger registry
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_XDS_GRPC_XDS_BOOTSTRAP_GRPC_H
```

The comments provide:
1. Class-level documentation explaining the purpose of each class
2. Method-level documentation explaining what each method does
3. Field-level documentation explaining the purpose of each member variable
4. Clear separation between public interface and private implementation
5. Explanation of key concepts like authorities, listeners, and registries

The comments maintain a consistent style and provide enough detail to understand the code's functionality without being overly verbose.