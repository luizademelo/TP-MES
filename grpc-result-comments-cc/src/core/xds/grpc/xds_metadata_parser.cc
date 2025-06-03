Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Includes necessary headers for xDS metadata parsing functionality
#include "src/core/xds/grpc/xds_metadata_parser.h"

#include <memory>
#include <utility>
#include <variant>

// Include various utility and protobuf-related headers
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "envoy/config/core/v3/address.upb.h"
#include "envoy/config/core/v3/address.upbdefs.h"
#include "envoy/extensions/filters/http/gcp_authn/v3/gcp_authn.upb.h"
#include "envoy/extensions/filters/http/gcp_authn/v3/gcp_authn.upbdefs.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/util/env.h"
#include "src/core/util/string.h"
#include "src/core/util/upb_utils.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_cluster_parser.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/grpc/xds_common_types_parser.h"
#include "upb/base/string_view.h"
#include "upb/message/array.h"
#include "upb/message/map.h"
#include "upb/message/message.h"
#include "upb/text/encode.h"

namespace grpc_core {

namespace {

// Parses GCP authentication audience metadata from the given extension
// Returns nullptr if parsing fails or validation errors occur
std::unique_ptr<XdsMetadataValue> ParseGcpAuthnAudience(
    const XdsResourceType::DecodeContext& context, XdsExtension extension,
    ValidationErrors* errors) {
  // Try to get the serialized proto data from the extension
  absl::string_view* serialized_proto =
      std::get_if<absl::string_view>(&extension.value);
  if (serialized_proto == nullptr) {
    errors->AddError("could not parse audience metadata");
    return nullptr;
  }
  
  // Parse the proto message from the serialized data
  auto* proto = envoy_extensions_filters_http_gcp_authn_v3_Audience_parse(
      serialized_proto->data(), serialized_proto->size(), context.arena);
  if (proto == nullptr) {
    errors->AddError("could not parse audience metadata");
    return nullptr;
  }
  
  // Log detailed proto information if tracing is enabled
  if (GRPC_TRACE_FLAG_ENABLED(xds_client) && ABSL_VLOG_IS_ON(2)) {
    const upb_MessageDef* msg_type =
        envoy_extensions_filters_http_gcp_authn_v3_Audience_getmsgdef(
            context.symtab);
    char buf[10240];
    upb_TextEncode(reinterpret_cast<const upb_Message*>(proto), msg_type,
                   nullptr, 0, buf, sizeof(buf));
    VLOG(2) << "[xds_client " << context.client
            << "] cluster metadata Audience: " << buf;
  }
  
  // Extract and validate the URL field from the proto
  absl::string_view url = UpbStringToAbsl(
      envoy_extensions_filters_http_gcp_authn_v3_Audience_url(proto));
  if (url.empty()) {
    ValidationErrors::ScopedField field(errors, ".url");
    errors->AddError("must be non-empty");
    return nullptr;
  }
  
  // Return a new metadata value containing the audience URL
  return std::make_unique<XdsGcpAuthnAudienceMetadataValue>(url);
}

// Parses address metadata from the given extension
// Returns nullptr if parsing fails or validation errors occur
std::unique_ptr<XdsMetadataValue> ParseAddress(
    const XdsResourceType::DecodeContext& context, XdsExtension extension,
    ValidationErrors* errors) {
  // Try to get the serialized proto data from the extension
  absl::string_view* serialized_proto =
      std::get_if<absl::string_view>(&extension.value);
  if (serialized_proto == nullptr) {
    errors->AddError("could not parse address metadata");
    return nullptr;
  }
  
  // Parse the proto message from the serialized data
  auto* proto = envoy_config_core_v3_Address_parse(
      serialized_proto->data(), serialized_proto->size(), context.arena);
  if (proto == nullptr) {
    errors->AddError("could not parse address metadata");
    return nullptr;
  }
  
  // Log detailed proto information if tracing is enabled
  if (GRPC_TRACE_FLAG_ENABLED(xds_client) && ABSL_VLOG_IS_ON(2)) {
    const upb_MessageDef* msg_type =
        envoy_config_core_v3_Address_getmsgdef(context.symtab);
    char buf[10240];
    upb_TextEncode(reinterpret_cast<const upb_Message*>(proto), msg_type,
                   nullptr, 0, buf, sizeof(buf));
    VLOG(2) << "[xds_client " << context.client
            << "] cluster metadata Address: " << buf;
  }
  
  // Parse the address from the proto
  auto addr = ParseXdsAddress(proto, errors);
  if (!addr.has_value()) return nullptr;
  
  // Convert the address to a string representation
  auto addr_uri = grpc_sockaddr_to_string(&*addr, false);
  if (!addr_uri.ok()) {
    errors->AddError(addr_uri.status().message());
    return nullptr;
  }
  
  // Return a new metadata value containing the address URI
  return std::make_unique<XdsAddressMetadataValue>(std::move(*addr_uri));
}

}  // namespace

// Parses xDS metadata map from the given protobuf metadata message
// Returns an empty map if metadata is null or parsing fails
XdsMetadataMap ParseXdsMetadataMap(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_core_v3_Metadata* metadata, ValidationErrors* errors) {
  XdsMetadataMap metadata_map;
  if (metadata == nullptr) return metadata_map;

  // Process typed filter metadata (protocol buffer Any messages)
  envoy_config_core_v3_Metadata* metadata_upb =
      (envoy_config_core_v3_Metadata*)metadata;
  size_t iter = kUpb_Map_Begin;
  upb_StringView typed_filter_metadata_key_view;
  const google_protobuf_Any* typed_filter_metadata_val;
  while (envoy_config_core_v3_Metadata_typed_filter_metadata_next(
      metadata_upb, &typed_filter_metadata_key_view, &typed_filter_metadata_val,
      &iter)) {
    absl::string_view key = UpbStringToAbsl(typed_filter_metadata_key_view);
    ValidationErrors::ScopedField field(
        errors, absl::StrCat(".typed_filter_metadata[", key, "]"));
    
    // Extract and parse the extension
    auto extension =
        ExtractXdsExtension(context, typed_filter_metadata_val, errors);
    if (!extension.has_value()) continue;

    // Handle different types of metadata
    std::unique_ptr<XdsMetadataValue> metadata_value;
    if (extension->type == XdsGcpAuthnAudienceMetadataValue::Type()) {
      metadata_value =
          ParseGcpAuthnAudience(context, std::move(*extension), errors);
    } else if (XdsHttpConnectEnabled() &&
               extension->type == XdsAddressMetadataValue::Type()) {
      metadata_value = ParseAddress(context, std::move(*extension), errors);
    }
    
    // Add valid metadata to the map
    if (metadata_value != nullptr) {
      metadata_map.Insert(key, std::move(metadata_value));
    }
  }

  // Process filter metadata (JSON-like struct messages)
  size_t iter2 = kUpb_Map_Begin;
  upb_StringView filter_metadata_key_view;
  const google_protobuf_Struct* filter_metadata_val;
  while (envoy_config_core_v3_Metadata_filter_metadata_next(
      metadata_upb, &filter_metadata_key_view, &filter_metadata_val, &iter2)) {
    absl::string_view key = UpbStringToAbsl(filter_metadata_key_view);
    
    // Convert protobuf struct to JSON
    auto json = ParseProtobufStructToJson(context, filter_metadata_val);
    if (!json.ok()) {
      ValidationErrors::ScopedField field(
          errors, absl::StrCat(".filter_metadata[", key, "]"));
      errors->AddError(json.status().message());
    }
    // Add to map only if key doesn't already exist and JSON is valid
    else if (metadata_map.Find(key) == nullptr) {
      metadata_map.Insert(
          key, std::make_unique<XdsStructMetadataValue>(std::move(*json)));
    }
  }
  return metadata_map;
}

}  // namespace grpc_core
```