Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#ifndef OBSERVABILITY_MAIN_H
#define OBSERVABILITY_MAIN_H

// Include necessary headers for the observability functionality
#include <grpc/status.h>  // For gRPC status codes
#include <stdint.h>       // For fixed-width integer types

// Standard library includes
#include <algorithm>
#include <condition_variable>  // For thread synchronization
#include <mutex>              // For mutual exclusion
#include <queue>              // For queue data structure
#include <string>             // For string handling
#include <utility>            // For std::move
#include <vector>             // For dynamic arrays

// Third-party includes
#include "absl/strings/string_view.h"  // For string view functionality
#include "constants.h"                // For application constants
#include "python_observability_context.h"  // For observability context

namespace grpc_observability {

// Structure to hold census data which can be either metric data or span data
struct CensusData {
  DataType type;             // Type of census data (metric or span)
  std::vector<Label> labels; // Labels associated with the data
  std::string identifier;    // Unique identifier for the data

  SpanCensusData span_data;       // Data specific to spans
  Measurement measurement_data;    // Data specific to measurements

  // Default constructor
  CensusData() {}

  // Constructor for metric data
  CensusData(const Measurement& mm, const std::vector<Label>& labels,
             std::string id)
      : type(kMetricData),
        labels(std::move(labels)),
        identifier(id),
        measurement_data(mm) {}

  // Constructor for span data
  CensusData(const SpanCensusData& sd) : type(kSpanData), span_data(sd) {}
};

// Global variables for census data buffer and synchronization
extern std::queue<CensusData>* g_census_data_buffer;          // Queue for storing census data
extern std::mutex g_census_data_buffer_mutex;                 // Mutex for thread-safe access to the queue
extern std::condition_variable g_census_data_buffer_cv;       // Condition variable for queue notifications

// Creates a client call tracer for monitoring client-side RPC calls
void* CreateClientCallTracer(const char* method, const char* target,
                             const char* trace_id, const char* parent_span_id,
                             const char* identifier,
                             const std::vector<Label> exchange_labels,
                             bool add_csm_optional_labels,
                             bool registered_method);

// Creates a server call tracer factory for monitoring server-side RPC calls
void* CreateServerCallTracerFactory(const std::vector<Label> exchange_labels,
                                    const char* identifier);

// Initializes native observability functionality
void NativeObservabilityInit();

// Waits for the next batch of census data with a timeout
void AwaitNextBatchLocked(std::unique_lock<std::mutex>& lock, int timeout_ms);

// Adds census data to the global buffer
void AddCensusDataToBuffer(const CensusData& buffer);

// Records an integer metric with associated labels and identifier
void RecordIntMetric(MetricsName name, int64_t value,
                     const std::vector<Label>& labels, std::string identifier,
                     const bool registered_method,
                     const bool include_exchange_labels);

// Records a double metric with associated labels and identifier
void RecordDoubleMetric(MetricsName name, double value,
                        const std::vector<Label>& labels,
                        std::string identifier, const bool registered_method,
                        const bool include_exchange_labels);

// Records span data
void RecordSpan(const SpanCensusData& span_census_data);

// Converts gRPC status code to its string representation
absl::string_view StatusCodeToString(grpc_status_code code);

}  // namespace grpc_observability

#endif  // OBSERVABILITY_MAIN_H
```

The comments provide:
1. File header information
2. Explanation of included headers
3. Documentation for the CensusData struct and its constructors
4. Description of global variables and their purpose
5. Detailed explanations for each function's purpose and parameters
6. Namespace closure and header guard comments

The comments are concise yet informative, helping future developers understand the purpose and usage of each component without being overly verbose.