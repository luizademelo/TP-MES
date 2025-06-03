Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_CSM_METADATA_EXCHANGE_H
#define GRPC_SRC_CPP_EXT_CSM_METADATA_EXCHANGE_H

#include <grpc/support/port_platform.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "absl/strings/string_view.h"
#include "google/protobuf/struct.upb.h"
#include "opentelemetry/sdk/common/attribute_utils.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/slice/slice.h"
#include "src/cpp/ext/otel/otel_plugin.h"
#include "upb/mem/arena.hpp"

namespace grpc {
namespace internal {

// ServiceMeshLabelsInjector is a LabelsInjector implementation for CSM (Cloud Service Mesh)
// that handles injection and extraction of labels/metadata for observability purposes.
class ServiceMeshLabelsInjector : public LabelsInjector {
 public:
  // Constructs a ServiceMeshLabelsInjector with the given attribute map.
  explicit ServiceMeshLabelsInjector(
      const opentelemetry::sdk::common::AttributeMap& map);

  // Gets labels from incoming metadata. Returns an iterable collection of labels.
  std::unique_ptr<LabelsIterable> GetLabels(
      grpc_metadata_batch* incoming_initial_metadata) const override;

  // Adds labels to outgoing metadata using labels from incoming metadata.
  void AddLabels(grpc_metadata_batch* outgoing_initial_metadata,
                 LabelsIterable* labels_from_incoming_metadata) const override;

  // Adds optional labels based on whether this is a client or server.
  // Returns true if all labels were successfully added.
  bool AddOptionalLabels(
      bool is_client,
      absl::Span<const grpc_core::RefCountedStringValue> optional_labels,
      opentelemetry::nostd::function_ref<
          bool(opentelemetry::nostd::string_view,
               opentelemetry::common::AttributeValue)>
          callback) const override;

  // Returns the number of optional labels for client/server.
  // Clients have 2 optional labels, servers have none.
  size_t GetOptionalLabelsSize(
      bool is_client,
      absl::Span<const grpc_core::RefCountedStringValue> )
      const override {
    return is_client ? 2 : 0;
  }

  // Test-only method to access local labels.
  const std::vector<std::pair<absl::string_view, std::string>>&
  TestOnlyLocalLabels() const {
    return local_labels_;
  }

  // Test-only method to access serialized labels.
  const grpc_core::Slice& TestOnlySerializedLabels() const {
    return serialized_labels_to_send_;
  }

 private:
  // Local labels to be injected into outgoing metadata
  std::vector<std::pair<absl::string_view, std::string>> local_labels_;
  // Serialized form of labels to be sent over the wire
  grpc_core::Slice serialized_labels_to_send_;
};

// MeshLabelsIterable provides iteration over mesh labels from both local and remote sources.
class MeshLabelsIterable : public LabelsIterable {
 public:
  // Enum representing different types of GCP resources
  enum class GcpResourceType : std::uint8_t { kGke, kGce, kUnknown };

  // Constructs a MeshLabelsIterable with local labels and remote metadata.
  MeshLabelsIterable(
      const std::vector<std::pair<absl::string_view, std::string>>&
          local_labels,
      grpc_core::Slice remote_metadata);

  // Gets the next label pair (key and value) if available.
  std::optional<std::pair<absl::string_view, absl::string_view>> Next()
      override;

  // Returns the total number of labels (local + remote).
  size_t Size() const override;

  // Resets the iterator position to start.
  void ResetIteratorPosition() override { pos_ = 0; }

  // Returns true if remote labels were successfully parsed.
  bool GotRemoteLabels() const { return struct_pb_ != nullptr; }

 private:
  // Arena for protobuf memory allocation
  upb::Arena arena_;
  // Parsed protobuf structure from remote metadata
  google_protobuf_Struct* struct_pb_ = nullptr;
  // Reference to local labels
  const std::vector<std::pair<absl::string_view, std::string>>& local_labels_;
  // Type of remote GCP resource
  GcpResourceType remote_type_ = GcpResourceType::kUnknown;
  // Current position in the iteration
  uint32_t pos_ = 0;
};

}
}

#endif
```