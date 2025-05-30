
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

class ServiceMeshLabelsInjector : public LabelsInjector {
 public:
  explicit ServiceMeshLabelsInjector(
      const opentelemetry::sdk::common::AttributeMap& map);

  std::unique_ptr<LabelsIterable> GetLabels(
      grpc_metadata_batch* incoming_initial_metadata) const override;

  void AddLabels(grpc_metadata_batch* outgoing_initial_metadata,
                 LabelsIterable* labels_from_incoming_metadata) const override;

  bool AddOptionalLabels(
      bool is_client,
      absl::Span<const grpc_core::RefCountedStringValue> optional_labels,
      opentelemetry::nostd::function_ref<
          bool(opentelemetry::nostd::string_view,
               opentelemetry::common::AttributeValue)>
          callback) const override;

  size_t GetOptionalLabelsSize(
      bool is_client,
      absl::Span<const grpc_core::RefCountedStringValue> )
      const override {
    return is_client ? 2 : 0;
  }

  const std::vector<std::pair<absl::string_view, std::string>>&
  TestOnlyLocalLabels() const {
    return local_labels_;
  }

  const grpc_core::Slice& TestOnlySerializedLabels() const {
    return serialized_labels_to_send_;
  }

 private:
  std::vector<std::pair<absl::string_view, std::string>> local_labels_;
  grpc_core::Slice serialized_labels_to_send_;
};

class MeshLabelsIterable : public LabelsIterable {
 public:
  enum class GcpResourceType : std::uint8_t { kGke, kGce, kUnknown };

  MeshLabelsIterable(
      const std::vector<std::pair<absl::string_view, std::string>>&
          local_labels,
      grpc_core::Slice remote_metadata);

  std::optional<std::pair<absl::string_view, absl::string_view>> Next()
      override;

  size_t Size() const override;

  void ResetIteratorPosition() override { pos_ = 0; }

  bool GotRemoteLabels() const { return struct_pb_ != nullptr; }

 private:
  upb::Arena arena_;
  google_protobuf_Struct* struct_pb_ = nullptr;
  const std::vector<std::pair<absl::string_view, std::string>>& local_labels_;
  GcpResourceType remote_type_ = GcpResourceType::kUnknown;
  uint32_t pos_ = 0;
};

}
}

#endif
