Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/cpp/ext/csm/metadata_exchange.h"

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <variant>

#include "absl/log/check.h"
#include "absl/status/statusor.h"
#include "absl/strings/escaping.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "opentelemetry/sdk/resource/semantic_conventions.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/util/env.h"
#include "src/cpp/ext/otel/key_value_iterable.h"
#include "upb/base/string_view.h"

namespace grpc {
namespace internal {

// Type alias for optional label keys in client call tracing
using OptionalLabelKey =
    grpc_core::ClientCallTracer::CallAttemptTracer::OptionalLabelKey;

namespace {

// Constants for metadata exchange keys
constexpr absl::string_view kMetadataExchangeTypeKey = "type";
constexpr absl::string_view kMetadataExchangeWorkloadNameKey = "workload_name";
constexpr absl::string_view kMetadataExchangeNamespaceNameKey =
    "namespace_name";
constexpr absl::string_view kMetadataExchangeClusterNameKey = "cluster_name";
constexpr absl::string_view kMetadataExchangeLocationKey = "location";
constexpr absl::string_view kMetadataExchangeProjectIdKey = "project_id";
constexpr absl::string_view kMetadataExchangeCanonicalServiceKey =
    "canonical_service";

// Constants for canonical service and mesh ID attributes
constexpr absl::string_view kCanonicalServiceAttribute =
    "csm.workload_canonical_service";
constexpr absl::string_view kMeshIdAttribute = "csm.mesh_id";

// Constants for peer attributes
constexpr absl::string_view kPeerTypeAttribute = "csm.remote_workload_type";
constexpr absl::string_view kPeerWorkloadNameAttribute =
    "csm.remote_workload_name";
constexpr absl::string_view kPeerNamespaceNameAttribute =
    "csm.remote_workload_namespace_name";
constexpr absl::string_view kPeerClusterNameAttribute =
    "csm.remote_workload_cluster_name";
constexpr absl::string_view kPeerLocationAttribute =
    "csm.remote_workload_location";
constexpr absl::string_view kPeerProjectIdAttribute =
    "csm.remote_workload_project_id";
constexpr absl::string_view kPeerCanonicalServiceAttribute =
    "csm.remote_workload_canonical_service";

// Constants for GCP resource types
constexpr absl::string_view kGkeType = "gcp_kubernetes_engine";
constexpr absl::string_view kGceType = "gcp_compute_engine";

// Decodes base64 encoded metadata into a protobuf Struct
google_protobuf_Struct* DecodeMetadata(grpc_core::Slice slice,
                                       upb_Arena* arena) {
  if (slice.empty()) {
    return nullptr;
  }

  std::string decoded_metadata;
  bool metadata_decoded =
      absl::Base64Unescape(slice.as_string_view(), &decoded_metadata);
  if (metadata_decoded) {
    return google_protobuf_Struct_parse(decoded_metadata.c_str(),
                                        decoded_metadata.size(), arena);
  }
  return nullptr;
}

// Converts a string representation to GcpResourceType enum
MeshLabelsIterable::GcpResourceType StringToGcpResourceType(
    absl::string_view type) {
  if (type == kGkeType) {
    return MeshLabelsIterable::GcpResourceType::kGke;
  } else if (type == kGceType) {
    return MeshLabelsIterable::GcpResourceType::kGce;
  }
  return MeshLabelsIterable::GcpResourceType::kUnknown;
}

// Converts absl::string_view to upb_StringView
upb_StringView AbslStrToUpbStr(absl::string_view str) {
  return upb_StringView_FromDataAndSize(str.data(), str.size());
}

// Converts upb_StringView to absl::string_view
absl::string_view UpbStrToAbslStr(upb_StringView str) {
  return absl::string_view(str.data, str.size);
}

// Adds a string key-value pair to a protobuf Struct
void AddStringKeyValueToStructProto(google_protobuf_Struct* struct_pb,
                                    absl::string_view key,
                                    absl::string_view value, upb_Arena* arena) {
  google_protobuf_Value* value_pb = google_protobuf_Value_new(arena);
  google_protobuf_Value_set_string_value(value_pb, AbslStrToUpbStr(value));
  google_protobuf_Struct_fields_set(struct_pb, AbslStrToUpbStr(key), value_pb,
                                    arena);
}

// Gets a string value from an AttributeMap by key
absl::string_view GetStringValueFromAttributeMap(
    const opentelemetry::sdk::common::AttributeMap& map,
    absl::string_view key) {
  const auto& attributes = map.GetAttributes();
  const auto it = attributes.find(std::string(key));
  if (it == attributes.end()) {
    return "unknown";
  }
  const auto* string_value = std::get_if<std::string>(&it->second);
  if (string_value == nullptr) {
    return "unknown";
  }
  return *string_value;
}

// Gets a string value from a protobuf Struct by key
absl::string_view GetStringValueFromUpbStruct(google_protobuf_Struct* struct_pb,
                                              absl::string_view key,
                                              upb_Arena* arena) {
  if (struct_pb == nullptr) {
    return "unknown";
  }
  google_protobuf_Value* value_pb = google_protobuf_Value_new(arena);
  bool present = google_protobuf_Struct_fields_get(
      struct_pb, AbslStrToUpbStr(key), &value_pb);
  if (present) {
    if (google_protobuf_Value_has_string_value(value_pb)) {
      return UpbStrToAbslStr(google_protobuf_Value_string_value(value_pb));
    }
  }
  return "unknown";
}

// Structure defining mapping between OTel attributes and metadata attributes
struct RemoteAttribute {
  absl::string_view otel_attribute;
  absl::string_view metadata_attribute;
};

// Fixed attributes that are always included
constexpr std::array<RemoteAttribute, 2> kFixedAttributes = {
    RemoteAttribute{kPeerTypeAttribute, kMetadataExchangeTypeKey},
    RemoteAttribute{kPeerCanonicalServiceAttribute,
                    kMetadataExchangeCanonicalServiceKey},
};

// Attributes specific to GKE resources
constexpr std::array<RemoteAttribute, 5> kGkeAttributeList = {
    RemoteAttribute{kPeerWorkloadNameAttribute,
                    kMetadataExchangeWorkloadNameKey},
    RemoteAttribute{kPeerNamespaceNameAttribute,
                    kMetadataExchangeNamespaceNameKey},
    RemoteAttribute{kPeerClusterNameAttribute, kMetadataExchangeClusterNameKey},
    RemoteAttribute{kPeerLocationAttribute, kMetadataExchangeLocationKey},
    RemoteAttribute{kPeerProjectIdAttribute, kMetadataExchangeProjectIdKey},
};

// Attributes specific to GCE resources
constexpr std::array<RemoteAttribute, 3> kGceAttributeList = {
    RemoteAttribute{kPeerWorkloadNameAttribute,
                    kMetadataExchangeWorkloadNameKey},
    RemoteAttribute{kPeerLocationAttribute, kMetadataExchangeLocationKey},
    RemoteAttribute{kPeerProjectIdAttribute, kMetadataExchangeProjectIdKey},
};

// Returns the appropriate attribute list based on resource type
absl::Span<const RemoteAttribute> GetAttributesForType(
    MeshLabelsIterable::GcpResourceType remote_type) {
  switch (remote_type) {
    case MeshLabelsIterable::GcpResourceType::kGke:
      return kGkeAttributeList;
    case MeshLabelsIterable::GcpResourceType::kGce:
      return kGceAttributeList;
    default:
      return {};
  }
}

// Gets the next attribute from the attribute list
std::optional<std::pair<absl::string_view, absl::string_view>>
NextFromAttributeList(absl::Span<const RemoteAttribute> attributes,
                      size_t start_index, size_t curr,
                      google_protobuf_Struct* decoded_metadata,
                      upb_Arena* arena) {
  DCHECK_GE(curr, start_index);
  const size_t index = curr - start_index;
  if (index >= attributes.size()) return std::nullopt;
  const auto& attribute = attributes[index];
  return std::pair(attribute.otel_attribute,
                   GetStringValueFromUpbStruct(
                       decoded_metadata, attribute.metadata_attribute, arena));
}

}  // namespace

// MeshLabelsIterable constructor
MeshLabelsIterable::MeshLabelsIterable(
    const std::vector<std::pair<absl::string_view, std::string>>& local_labels,
    grpc_core::Slice remote_metadata)
    : struct_pb_(DecodeMetadata(std::move(remote_metadata), arena_.ptr())),
      local_labels_(local_labels),
      remote_type_(StringToGcpResourceType(GetStringValueFromUpbStruct(
          struct_pb_, kMetadataExchangeTypeKey, arena_.ptr()))) {}

// Gets the next label in the iteration
std::optional<std::pair<absl::string_view, absl::string_view>>
MeshLabelsIterable::Next() {
  size_t local_labels_size = local_labels_.size();
  if (pos_ < local_labels_size) {
    return local_labels_[pos_++];
  }
  const size_t fixed_attribute_end =
      local_labels_size + kFixedAttributes.size();
  if (pos_ < fixed_attribute_end) {
    return NextFromAttributeList(kFixedAttributes, local_labels_size, pos_++,
                                 struct_pb_, arena_.ptr());
  }
  return NextFromAttributeList(GetAttributesForType(remote_type_),
                               fixed_attribute_end, pos_++, struct_pb_,
                               arena_.ptr());
}

// Returns the total number of labels
size_t MeshLabelsIterable::Size() const {
  return local_labels_.size() + kFixedAttributes.size() +
         GetAttributesForType(remote_type_).size();
}

// ServiceMeshLabelsInjector constructor
ServiceMeshLabelsInjector::ServiceMeshLabelsInjector(
    const opentelemetry::sdk::common::AttributeMap& map) {
  upb::Arena arena;
  auto* metadata = google_protobuf_Struct_new(arena.ptr());

  // Get values from environment and attribute map
  absl::string_view type_value = GetStringValueFromAttributeMap(
      map, opentelemetry::sdk::resource::SemanticConventions::kCloudPlatform);
  std::string workload_name_value =
      grpc_core::GetEnv("CSM_WORKLOAD_NAME").value_or("unknown");
  absl::string_view namespace_value = GetStringValueFromAttributeMap(
      map,
      opentelemetry::sdk::resource::SemanticConventions::kK8sNamespaceName);
  absl::string_view cluster_name_value = GetStringValueFromAttributeMap(
      map, opentelemetry::sdk::resource::SemanticConventions::kK8sClusterName);
  absl::string_view location_value = GetStringValueFromAttributeMap(
      map, opentelemetry::sdk::resource::SemanticConventions::
               kCloudAvailabilityZone);
  if (location_value == "unknown") {
    location_value = GetStringValueFromAttributeMap(
        map, opentelemetry::sdk::resource::SemanticConventions::
                 kCloudRegion);
  }
  absl::string_view project_id_value = GetStringValueFromAttributeMap(
      map, opentelemetry::sdk::resource::SemanticConventions::kCloudAccountId);
  std::string canonical_service_value =
      grpc_core::GetEnv("CSM_CANONICAL_SERVICE_NAME").value_or("unknown");

  // Add common attributes to metadata
  AddStringKeyValueToStructProto(metadata, kMetadataExchangeTypeKey, type_value,
                                 arena.ptr());
  AddStringKeyValueToStructProto(metadata, kMetadataExchangeCanonicalServiceKey,
                                 canonical_service_value, arena.ptr());
  
  // Add type-specific attributes
  if (type_value == kGkeType) {
    AddStringKeyValueToStructProto(metadata, kMetadataExchangeWorkloadNameKey,
                                   workload_name_value, arena.ptr());
    AddStringKeyValueToStructProto(metadata, kMetadataExchangeNamespaceNameKey,
                                   namespace_value, arena.ptr());
    AddStringKeyValueToStructProto(metadata, kMetadataExchangeClusterNameKey,
                                   cluster_name_value, arena.ptr());
    AddStringKeyValueToStructProto(metadata, kMetadataExchangeLocationKey,
                                   location_value, arena.ptr());
    AddStringKeyValueToStructProto(metadata, kMetadataExchangeProjectIdKey,
                                   project_id_value, arena.ptr());
  } else if (type_value == kGceType) {
    AddStringKeyValueToStructProto(metadata, kMetadataExchangeWorkloadNameKey,
                                   workload_name_value, arena.ptr());
    AddStringKeyValueToStructProto(metadata, kMetadataExchangeLocationKey,
                                   location_value, arena.ptr());
    AddStringKeyValueToStructProto(metadata, kMetadataExchangeProjectIdKey,
                                   project_id_value, arena.ptr());
  }

  // Serialize and base64 encode the metadata
  size_t output_length;
  char* output =
      google_protobuf_Struct_serialize(metadata, arena.ptr(), &output_length);
  serialized_labels_to_send_ = grpc_core::Slice::FromCopiedString(
      absl::Base64Escape(absl::string_view(output, output_length)));

  // Set local labels
  local_labels_.emplace_back(kCanonicalServiceAttribute,
                             canonical_service_value);
  local_labels_.emplace_back(
      kMeshIdAttribute, grpc_core::GetEnv("CSM_MESH_ID").value_or("unknown"));
}

// Gets labels for the current context
std::unique_ptr<LabelsIterable> ServiceMeshLabelsInjector::GetLabels(
    grpc_metadata_batch* incoming_initial_metadata) const {
  auto peer_metadata =
      incoming_initial_metadata->Take(grpc_core::XEnvoyPeerMetadata());
  return std::make_unique<MeshLabelsIterable>(
      local_labels_, peer_metadata.has_value() ? *std::move(peer_metadata)
                                               : grpc_core::Slice());
}

// Adds labels to outgoing metadata
void ServiceMeshLabelsInjector::AddLabels(
    grpc_metadata_batch* outgoing_initial_metadata,
    LabelsIterable* labels_from_incoming_metadata) const {
  if (labels_from_incoming_metadata != nullptr &&
      !static_cast<MeshLabelsIterable*>(labels_from_incoming_metadata)
           ->GotRemoteLabels()) {
    return;
  }
  outgoing_initial_metadata->Set(grpc_core::XEnvoyPeerMetadata(),
                                 serialized_labels_to_send_.Ref());
}

// Adds optional labels for telemetry
bool ServiceMeshLabelsInjector::AddOptionalLabels(
    bool is_client,
    absl::Span<const grpc_core::RefCountedStringValue> optional_labels,
    opentelemetry::nostd::function_ref<
        bool(opentelemetry::nostd::string_view,
             opentelemetry::common::AttributeValue)>
        callback) const {
  if (!is_client) {
    return true;
  }

  // Get service name and namespace from optional labels
  absl::string_view service_name =
      optional_labels[static_cast<size_t>(
                          grpc_core::ClientCallTracer::CallAttemptTracer::
                              OptionalLabelKey::kXdsServiceName)]
          .as_string_view();
  absl::string_view service_namespace =
      optional_labels[static_cast<size_t>(
                          grpc_core::ClientCallTracer::CallAttemptTracer::
                              OptionalLabelKey::kXdsServiceNamespace)]
          .as_string_view();
  
  // Add them via callback
  return callback("csm.service_name",
                  service_name.empty()
                      ? "unknown"
                      : AbslStrViewToOpenTelemetryStrView(service_name)) &&
         callback("csm.service_namespace_name",
                  service_namespace.empty()
                      ? "unknown"
                      : AbslStrViewToOpenTelemetryStrView(service_namespace));
}

}  // namespace internal
}  // namespace grpc
```