Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_PYTHON_OBSERVABILITY_CONSTANTS_H
#define GRPC_PYTHON_OBSERVABILITY_CONSTANTS_H

#include <set>
#include <string>

// Namespace for gRPC observability-related constants and types
namespace grpc_observability {

// String constants for client-side attributes
const std::string kClientMethod = "grpc.method";       // gRPC method name for client
const std::string kClientTarget = "grpc.target";       // Target server for client calls
const std::string kClientStatus = "grpc.status";       // Status of client call

// String constants for server-side attributes
const std::string kServerMethod = "grpc.method";       // gRPC method name for server
const std::string kServerStatus = "grpc.status";       // Status of server call

// Other string constants
const std::string kRegisteredMethod = "registerMethod"; // Key for registered methods
const std::string kXEnvoyPeerMetadata = "XEnvoyPeerMetadata"; // Envoy-specific metadata key

// Enum defining types of measurements
typedef enum { 
    kMeasurementDouble = 0,  // Measurement with double/float value
    kMeasurementInt          // Measurement with integer value
} MeasurementType;

// Enum defining types of observability data
typedef enum { 
    kSpanData = 0,   // Data represents tracing span information
    kMetricData      // Data represents metric information
} DataType;

// Enum defining all supported gRPC metrics names
typedef enum {
  // Client-side metrics
  kRpcClientApiLatencyMeasureName = 0,                // API call latency
  kRpcClientSentMessagesPerRpcMeasureName,            // Messages sent per RPC
  kRpcClientSentBytesPerRpcMeasureName,               // Bytes sent per RPC
  kRpcClientReceivedMessagesPerRpcMeasureName,        // Messages received per RPC
  kRpcClientReceivedBytesPerRpcMeasureName,           // Bytes received per RPC
  kRpcClientRoundtripLatencyMeasureName,              // Roundtrip latency
  kRpcClientCompletedRpcMeasureName,                  // Completed RPC count
  kRpcClientServerLatencyMeasureName,                 // Server processing latency
  kRpcClientStartedRpcsMeasureName,                   // Started RPC count
  kRpcClientRetriesPerCallMeasureName,                // Retries per call
  kRpcClientTransparentRetriesPerCallMeasureName,     // Transparent retries per call
  kRpcClientRetryDelayPerCallMeasureName,             // Retry delay per call
  kRpcClientTransportLatencyMeasureName,              // Transport layer latency
  
  // Server-side metrics
  kRpcServerSentMessagesPerRpcMeasureName,            // Messages sent per RPC
  kRpcServerSentBytesPerRpcMeasureName,               // Bytes sent per RPC
  kRpcServerReceivedMessagesPerRpcMeasureName,        // Messages received per RPC
  kRpcServerReceivedBytesPerRpcMeasureName,           // Bytes received per RPC
  kRpcServerServerLatencyMeasureName,                 // Server processing latency
  kRpcServerCompletedRpcMeasureName,                  // Completed RPC count
  kRpcServerStartedRpcsMeasureName                    // Started RPC count
} MetricsName;

// Set of metadata keys used for metadata exchange between services
const std::set<std::string> MetadataExchangeKeyNames = {kXEnvoyPeerMetadata};

}  // namespace grpc_observability

#endif  // GRPC_PYTHON_OBSERVABILITY_CONSTANTS_H
```

The comments provide:
1. Explanation of the header guard purpose
2. Namespace description
3. Documentation for each string constant indicating its purpose
4. Clear descriptions of each enum type and its values
5. Explanation of the metrics name enum values, grouped by client/server side
6. Description of the metadata exchange keys set
7. Proper closing comments for namespace and header guard