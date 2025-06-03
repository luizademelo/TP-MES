Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/xds/xds_client/xds_api.h"

#include "google/protobuf/struct.upb.h"
#include "src/core/util/json/json.h"
#include "src/core/util/upb_utils.h"
#include "upb/base/string_view.h"
#include "upb/mem/arena.hpp"

namespace grpc_core {

namespace {

// Populates a protobuf Value message from a JSON value
// Args:
//   value_pb: The protobuf Value message to populate
//   value: The JSON value to convert
//   arena: Memory arena for allocation
void PopulateMetadataValue(google_protobuf_Value* value_pb, const Json& value,
                           upb_Arena* arena);

// Populates a protobuf ListValue message from a JSON array
// Args:
//   list_value: The protobuf ListValue message to populate
//   values: The JSON array to convert
//   arena: Memory arena for allocation
void PopulateListValue(google_protobuf_ListValue* list_value,
                       const Json::Array& values, upb_Arena* arena) {
  for (const auto& value : values) {
    auto* value_pb = google_protobuf_ListValue_add_values(list_value, arena);
    PopulateMetadataValue(value_pb, value, arena);
  }
}

// Populates a protobuf Struct message from a JSON object
// Args:
//   metadata_pb: The protobuf Struct message to populate
//   metadata: The JSON object to convert
//   arena: Memory arena for allocation
void PopulateMetadata(google_protobuf_Struct* metadata_pb,
                      const Json::Object& metadata, upb_Arena* arena) {
  for (const auto& [key, value] : metadata) {
    google_protobuf_Value* value_proto = google_protobuf_Value_new(arena);
    PopulateMetadataValue(value_proto, value, arena);
    google_protobuf_Struct_fields_set(metadata_pb, StdStringToUpbString(key),
                                      value_proto, arena);
  }
}

// Converts a JSON value to a protobuf Value message
// Handles all JSON types (null, number, string, boolean, object, array)
// Args:
//   value_pb: The protobuf Value message to populate
//   value: The JSON value to convert
//   arena: Memory arena for allocation
void PopulateMetadataValue(google_protobuf_Value* value_pb, const Json& value,
                           upb_Arena* arena) {
  switch (value.type()) {
    case Json::Type::kNull:
      google_protobuf_Value_set_null_value(value_pb, 0);
      break;
    case Json::Type::kNumber:
      google_protobuf_Value_set_number_value(
          value_pb, strtod(value.string().c_str(), nullptr));
      break;
    case Json::Type::kString:
      google_protobuf_Value_set_string_value(
          value_pb, StdStringToUpbString(value.string()));
      break;
    case Json::Type::kBoolean:
      google_protobuf_Value_set_bool_value(value_pb, value.boolean());
      break;
    case Json::Type::kObject: {
      google_protobuf_Struct* struct_value =
          google_protobuf_Value_mutable_struct_value(value_pb, arena);
      PopulateMetadata(struct_value, value.object(), arena);
      break;
    }
    case Json::Type::kArray: {
      google_protobuf_ListValue* list_value =
          google_protobuf_Value_mutable_list_value(value_pb, arena);
      PopulateListValue(list_value, value.array(), arena);
      break;
    }
  }
}

}  // namespace

// Populates an xDS Node message with node information and user agent details
// Args:
//   node: The bootstrap node information (may be null)
//   user_agent_name: The name of the user agent
//   user_agent_version: The version of the user agent
//   node_msg: The protobuf Node message to populate
//   arena: Memory arena for allocation
void PopulateXdsNode(const XdsBootstrap::Node* node,
                     absl::string_view user_agent_name,
                     absl::string_view user_agent_version,
                     envoy_config_core_v3_Node* node_msg, upb_Arena* arena) {
  // Populate node information if provided
  if (node != nullptr) {
    if (!node->id().empty()) {
      envoy_config_core_v3_Node_set_id(node_msg,
                                       StdStringToUpbString(node->id()));
    }
    if (!node->cluster().empty()) {
      envoy_config_core_v3_Node_set_cluster(
          node_msg, StdStringToUpbString(node->cluster()));
    }
    // Convert and set node metadata if present
    if (!node->metadata().empty()) {
      google_protobuf_Struct* metadata =
          envoy_config_core_v3_Node_mutable_metadata(node_msg, arena);
      PopulateMetadata(metadata, node->metadata(), arena);
    }
    // Set locality information if any locality field is present
    if (!node->locality_region().empty() || !node->locality_zone().empty() ||
        !node->locality_sub_zone().empty()) {
      envoy_config_core_v3_Locality* locality =
          envoy_config_core_v3_Node_mutable_locality(node_msg, arena);
      if (!node->locality_region().empty()) {
        envoy_config_core_v3_Locality_set_region(
            locality, StdStringToUpbString(node->locality_region()));
      }
      if (!node->locality_zone().empty()) {
        envoy_config_core_v3_Locality_set_zone(
            locality, StdStringToUpbString(node->locality_zone()));
      }
      if (!node->locality_sub_zone().empty()) {
        envoy_config_core_v3_Locality_set_sub_zone(
            locality, StdStringToUpbString(node->locality_sub_zone()));
      }
    }
  }
  // Set user agent information
  envoy_config_core_v3_Node_set_user_agent_name(
      node_msg, StdStringToUpbString(user_agent_name));
  envoy_config_core_v3_Node_set_user_agent_version(
      node_msg, StdStringToUpbString(user_agent_version));
  // Add default client feature
  envoy_config_core_v3_Node_add_client_features(
      node_msg,
      upb_StringView_FromString("envoy.lb.does_not_support_overprovisioning"),
      arena);
}

}  // namespace grpc_core
```

The comments provide:
1. File-level copyright notice
2. Function-level documentation explaining purpose and parameters
3. Inline comments explaining key logic blocks
4. Clear separation between different logical sections
5. Consistent formatting and style
6. Explanation of conditional blocks and their significance
7. Note about default values being set

The comments are designed to help future maintainers understand:
- What each function does
- The purpose of each parameter
- The flow of data conversion between JSON and protobuf formats
- The structure of the xDS Node message population
- Important conditional logic