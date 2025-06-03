Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

#include "metadata_exchange.h"

#include <grpc/slice.h>
#include <stddef.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <unordered_map>

#include "absl/strings/string_view.h"
#include "constants.h"
#include "src/core/telemetry/call_tracer.h"

namespace grpc_observability {

// Constructor for PythonLabelsInjector that initializes metadata to be exchanged
// based on the provided labels. Only labels with keys found in MetadataExchangeKeyNames
// are stored for later exchange.
PythonLabelsInjector::PythonLabelsInjector(
    const std::vector<Label>& exchange_labels) {
  for (const auto& label : exchange_labels) {
    auto it = MetadataExchangeKeyNames.find(label.key);
    if (it != MetadataExchangeKeyNames.end()) {
      metadata_to_exchange_.emplace_back(label.key, label.value);
    }
  }
}

// Retrieves labels from incoming metadata that should be exchanged.
// Currently only processes kXEnvoyPeerMetadata by:
// 1. Extracting the metadata from incoming_initial_metadata
// 2. Base64 decoding the value if present
// 3. Adding the decoded value to the returned labels
std::vector<Label> PythonLabelsInjector::GetExchangeLabels(
    grpc_metadata_batch* incoming_initial_metadata) const {
  std::vector<Label> labels;
  for (const auto& key : MetadataExchangeKeyNames) {
    if (key == kXEnvoyPeerMetadata) {
      auto xds_peer_metadata =
          incoming_initial_metadata->Take(grpc_core::XEnvoyPeerMetadata());
      grpc_core::Slice xds_remote_metadata = xds_peer_metadata.has_value()
                                                 ? *std::move(xds_peer_metadata)
                                                 : grpc_core::Slice();
      if (!xds_remote_metadata.empty()) {
        std::string xds_decoded_metadata;
        bool metadata_decoded = absl::Base64Unescape(
            xds_remote_metadata.as_string_view(), &xds_decoded_metadata);
        if (metadata_decoded) {
          labels.emplace_back(kXEnvoyPeerMetadata, xds_decoded_metadata);
        }
      }
    }
  }
  return labels;
}

// Adds exchange labels to outgoing metadata by:
// 1. Base64 encoding the values
// 2. Creating metadata slices
// 3. Setting them in the outgoing metadata batch
// Currently only processes kXEnvoyPeerMetadata
void PythonLabelsInjector::AddExchangeLabelsToMetadata(
    grpc_metadata_batch* outgoing_initial_metadata) const {
  for (const auto& metadata : metadata_to_exchange_) {
    if (metadata.first == kXEnvoyPeerMetadata) {
      grpc_core::Slice metadata_slice = grpc_core::Slice::FromCopiedString(
          absl::Base64Escape(absl::string_view(metadata.second)));
      outgoing_initial_metadata->Set(grpc_core::XEnvoyPeerMetadata(),
                                     metadata_slice.Ref());
    }
  }
}

// Adds optional XDS labels for CSM (Cloud Service Monitoring) if:
// 1. This is a client call (is_client is true)
// 2. The service name and namespace are available from optional_labels_span
// Defaults to "unknown" if service name or namespace are empty
void PythonLabelsInjector::AddXdsOptionalLabels(
    bool is_client,
    absl::Span<const grpc_core::RefCountedStringValue> optional_labels_span,
    std::vector<Label>& labels) {
  if (!is_client) {
    // Only add these labels for client calls
    return;
  }

  // Extract service name and namespace from optional labels
  absl::string_view service_name =
      optional_labels_span[static_cast<size_t>(
                               grpc_core::ClientCallTracer::CallAttemptTracer::
                                   OptionalLabelKey::kXdsServiceName)]
          .as_string_view();
  absl::string_view service_namespace =
      optional_labels_span[static_cast<size_t>(
                               grpc_core::ClientCallTracer::CallAttemptTracer::
                                   OptionalLabelKey::kXdsServiceNamespace)]
          .as_string_view();

  // Default to "unknown" if values are empty
  if (service_name.empty()) {
    service_name = "unknown";
  }
  if (service_namespace.empty()) {
    service_namespace = "unknown";
  }

  // Add the labels with "csm." prefix
  labels.emplace_back("csm.service_name", std::string(service_name));
  labels.emplace_back("csm.service_namespace_name",
                      std::string(service_namespace));
}

}  // namespace grpc_observability
```