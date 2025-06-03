Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_GCP_OBSERVABILITY_CONFIG_H
#define GRPC_SRC_CPP_EXT_GCP_OBSERVABILITY_CONFIG_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <map>
#include <optional>
#include <string>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/validation_errors.h"

namespace grpc {
namespace internal {

// Configuration structure for GCP Observability features
struct GcpObservabilityConfig {
  // Configuration for Cloud Logging feature
  struct CloudLogging {
    // Configuration for RPC event logging
    struct RpcEventConfiguration {
      // Represents a parsed method name with service and method components
      struct ParsedMethod {
        absl::string_view service;  // Service name
        absl::string_view method;   // Method name
      };

      std::vector<std::string> qualified_methods;  // Fully qualified method names
      std::vector<ParsedMethod> parsed_methods;    // Parsed method components
      bool exclude = false;                        // Whether to exclude these methods from logging
      uint32_t max_metadata_bytes = 0;             // Max metadata size to log (bytes)
      uint32_t max_message_bytes = 0;              // Max message size to log (bytes)

      // JSON loader for RpcEventConfiguration
      static const grpc_core::JsonLoaderInterface* JsonLoader(
          const grpc_core::JsonArgs&);

      // Post-processing after JSON load to validate and parse data
      void JsonPostLoad(const grpc_core::Json& json,
                        const grpc_core::JsonArgs& args,
                        grpc_core::ValidationErrors* errors);
    };

    std::vector<RpcEventConfiguration> client_rpc_events;  // Client-side RPC event configs
    std::vector<RpcEventConfiguration> server_rpc_events;  // Server-side RPC event configs

    // JSON loader for CloudLogging configuration
    static const grpc_core::JsonLoaderInterface* JsonLoader(
        const grpc_core::JsonArgs&) {
      static const auto* loader =
          grpc_core::JsonObjectLoader<CloudLogging>()
              .OptionalField("client_rpc_events",
                             &CloudLogging::client_rpc_events)
              .OptionalField("server_rpc_events",
                             &CloudLogging::server_rpc_events)
              .Finish();
      return loader;
    }
  };

  // Configuration for Cloud Monitoring feature
  struct CloudMonitoring {
    // JSON loader for CloudMonitoring configuration
    static const grpc_core::JsonLoaderInterface* JsonLoader(
        const grpc_core::JsonArgs&) {
      static const auto* loader =
          grpc_core::JsonObjectLoader<CloudMonitoring>().Finish();
      return loader;
    }
  };

  // Configuration for Cloud Trace feature
  struct CloudTrace {
    CloudTrace() : sampling_rate(0) {}
    float sampling_rate;  // Sampling rate for traces (0-1)

    // JSON loader for CloudTrace configuration
    static const grpc_core::JsonLoaderInterface* JsonLoader(
        const grpc_core::JsonArgs&) {
      static const auto* loader =
          grpc_core::JsonObjectLoader<CloudTrace>()
              .OptionalField("sampling_rate", &CloudTrace::sampling_rate)
              .Finish();
      return loader;
    }
  };

  std::optional<CloudLogging> cloud_logging;      // Optional Cloud Logging config
  std::optional<CloudMonitoring> cloud_monitoring; // Optional Cloud Monitoring config
  std::optional<CloudTrace> cloud_trace;         // Optional Cloud Trace config
  std::string project_id;                        // GCP project ID
  std::map<std::string, std::string> labels;     // Additional resource labels

  // JSON loader for the main GcpObservabilityConfig
  static const grpc_core::JsonLoaderInterface* JsonLoader(
      const grpc_core::JsonArgs&) {
    static const auto* loader =
        grpc_core::JsonObjectLoader<GcpObservabilityConfig>()
            .OptionalField("cloud_logging",
                           &GcpObservabilityConfig::cloud_logging)
            .OptionalField("cloud_monitoring",
                           &GcpObservabilityConfig::cloud_monitoring)
            .OptionalField("cloud_trace", &GcpObservabilityConfig::cloud_trace)
            .OptionalField("project_id", &GcpObservabilityConfig::project_id)
            .OptionalField("labels", &GcpObservabilityConfig::labels)
            .Finish();
    return loader;
  }

  // Reads and parses the configuration from environment variables
  static absl::StatusOr<GcpObservabilityConfig> ReadFromEnv();
};

}
}

#endif
```