Here's the commented version of the code snippet:

```c++
// Copyright 2024 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_EXAMPLES_CPP_OTEL_UTIL_H
#define GRPCPP_EXAMPLES_CPP_OTEL_UTIL_H

#include <string>

// Include OpenTelemetry metrics SDK for MeterProvider functionality
#include "opentelemetry/sdk/metrics/meter_provider.h"

// Function to add a latency view to the provided MeterProvider
// Parameters:
//   provider - Pointer to the MeterProvider where the view will be added
//   name     - Name identifier for the latency metric
//   unit     - Unit of measurement for the latency (e.g., "ms", "s")
void AddLatencyView(opentelemetry::sdk::metrics::MeterProvider* provider,
                    const std::string& name, const std::string& unit);

// Function to run a gRPC server on the specified port
// Parameter:
//   port - The port number on which the server will listen
void RunServer(uint16_t port);

// Function to run a gRPC server with xDS (Traffic Director) enabled
// Parameter:
//   port - The port number on which the xDS-enabled server will listen
void RunXdsEnabledServer(uint16_t port);

// Function to run a gRPC client that connects to the specified target
// Parameter:
//   target_str - The target server address in URI format (e.g., "localhost:50051")
void RunClient(const std::string& target_str);

#endif  // End of header guard
```

The comments provide:
1. Explanation of the header guard
2. Purpose of included headers
3. Detailed documentation for each function including:
   - What the function does
   - Description of each parameter
   - Expected parameter values where relevant
4. Clear indication of the end of the header guard

The comments are concise yet informative, helping future developers understand the purpose and usage of each component without being overly verbose.