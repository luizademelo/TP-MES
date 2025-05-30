
// Copyright 2024 gRPC authors.

#ifndef GRPC_PYTHON_OBSERVABILITY_METADATA_EXCHANGE_H
#define GRPC_PYTHON_OBSERVABILITY_METADATA_EXCHANGE_H

#include <stddef.h>
#include <stdint.h>

#include <bitset>
#include <memory>
#include <string>
#include <utility>

#include "absl/strings/string_view.h"
#include "constants.h"
#include "python_observability_context.h"
#include "src/core/call/metadata_batch.h"

namespace grpc_observability {

class PythonLabelsInjector {
 public:
  explicit PythonLabelsInjector(const std::vector<Label>& exchange_labels);

  std::vector<Label> GetExchangeLabels(
      grpc_metadata_batch* incoming_initial_metadata) const;

  void AddExchangeLabelsToMetadata(
      grpc_metadata_batch* outgoing_initial_metadata) const;

  void AddXdsOptionalLabels(
      bool is_client,
      absl::Span<const grpc_core::RefCountedStringValue> optional_labels_span,
      std::vector<Label>& labels);

 private:
  std::vector<std::pair<std::string, std::string>> metadata_to_exchange_;
};

}

#endif
