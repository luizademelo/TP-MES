Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_LISTENER_PARSER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_LISTENER_PARSER_H

// Include necessary headers
#include "absl/strings/string_view.h"  // For string_view
#include "envoy/config/listener/v3/listener.upbdefs.h"  // For Listener proto definitions
#include "envoy/extensions/filters/network/http_connection_manager/v3/http_connection_manager.upbdefs.h"  // For HCM proto definitions
#include "src/core/util/down_cast.h"  // For DownCast utility
#include "src/core/xds/grpc/xds_bootstrap_grpc.h"  // For XDS bootstrap configuration
#include "src/core/xds/grpc/xds_http_filter_registry.h"  // For HTTP filter registry
#include "src/core/xds/grpc/xds_listener.h"  // For XDS Listener resource
#include "src/core/xds/xds_client/xds_client.h"  // For XDS client
#include "src/core/xds/xds_client/xds_resource_type.h"  // For XDS resource type base class
#include "src/core/xds/xds_client/xds_resource_type_impl.h"  // For XDS resource type implementation
#include "upb/reflection/def.h"  // For upb definitions

namespace grpc_core {

// XdsListenerResourceType implements the XdsResourceType interface for
// processing Listener resources from xDS.
// It handles parsing and validation of Listener configuration.
class XdsListenerResourceType final
    : public XdsResourceTypeImpl<XdsListenerResourceType, XdsListenerResource> {
 public:
  // Returns the type URL for the Listener resource as defined in the xDS API
  absl::string_view type_url() const override {
    return "envoy.config.listener.v3.Listener";
  }

  // Decodes a serialized Listener resource from xDS
  // context: Contains decoding context including xDS client and upb symtab
  // serialized_resource: The serialized protobuf data to decode
  // Returns: A DecodeResult containing either the parsed resource or an error
  DecodeResult Decode(const XdsResourceType::DecodeContext& context,
                      absl::string_view serialized_resource) const override;

  // Indicates whether all resources of this type are required in State of the World (SotW)
  // implementations. For Listener resources, this is true.
  bool AllResourcesRequiredInSotW() const override { return true; }

  // Initializes the upb symbol table with necessary protobuf definitions
  // xds_client: The XDS client instance
  // symtab: The upb symbol table to populate
  void InitUpbSymtab(XdsClient* xds_client,
                     upb_DefPool* symtab) const override {
    // Add Listener message definition to symbol table
    envoy_config_listener_v3_Listener_getmsgdef(symtab);
    // Add HTTP Connection Manager message definition to symbol table
    envoy_extensions_filters_network_http_connection_manager_v3_HttpConnectionManager_getmsgdef(
        symtab);
    // Get HTTP filter registry from bootstrap config and populate its types
    const auto& http_filter_registry =
        DownCast<const GrpcXdsBootstrap&>(xds_client->bootstrap())
            .http_filter_registry();
    http_filter_registry.PopulateSymtab(symtab);
  }
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_XDS_GRPC_XDS_LISTENER_PARSER_H
```

Key aspects covered in the comments:
1. Header guard explanation
2. Purpose of each included header
3. Class overview explaining its role in xDS
4. Documentation for each method including:
   - Purpose
   - Parameters
   - Return values
5. Special notes about implementation details
6. Namespace closure comment

The comments follow a consistent style and provide both high-level context and specific details about implementation choices.