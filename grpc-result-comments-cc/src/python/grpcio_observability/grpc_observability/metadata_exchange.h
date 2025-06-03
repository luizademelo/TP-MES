Here's the commented version of the code:

```c++
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

// Class responsible for injecting and extracting observability labels
// to/from gRPC metadata for Python observability purposes.
// This facilitates the exchange of observability data between client and server.
class PythonLabelsInjector {
 public:
  // Constructor that initializes the injector with labels to be exchanged.
  // Parameters:
  //   exchange_labels: Vector of labels that should be exchanged via metadata
  explicit PythonLabelsInjector(const std::vector<Label>& exchange_labels);

  // Retrieves exchange labels from incoming metadata.
  // Parameters:
  //   incoming_initial_metadata: Pointer to the incoming metadata batch
  // Returns:
  //   Vector of labels extracted from the metadata
  std::vector<Label> GetExchangeLabels(
      grpc_metadata_batch* incoming_initial_metadata) const;

  // Adds exchange labels to outgoing metadata.
  // Parameters:
  //   outgoing_initial_metadata: Pointer to the outgoing metadata batch
  //                             where labels will be added
  void AddExchangeLabelsToMetadata(
      grpc_metadata_batch* outgoing_initial_metadata) const;

  // Adds optional xDS labels to the provided labels vector.
  // Parameters:
  //   is_client: Boolean indicating if this is a client-side call
  //   optional_labels_span: Span of optional labels to potentially add
  //   labels: Reference to vector where labels will be added
  void AddXdsOptionalLabels(
      bool is_client,
      absl::Span<const grpc_core::RefCountedStringValue> optional_labels_span,
      std::vector<Label>& labels);

 private:
  // Internal storage for metadata key-value pairs to be exchanged
  std::vector<std::pair<std::string, std::string>> metadata_to_exchange_;
};

}

#endif
```

The comments explain:
1. The overall purpose of the PythonLabelsInjector class
2. Each public method's functionality, parameters, and return values
3. The private member variable's purpose
4. Maintained all existing copyright and include guard information

The comments are designed to help future developers understand:
- Why this class exists (for observability metadata exchange)
- How to use each method
- What each parameter represents
- The expected behavior of each function
- The internal data structure used for storing metadata