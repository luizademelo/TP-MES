
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

struct GcpObservabilityConfig {
  struct CloudLogging {
    struct RpcEventConfiguration {
      struct ParsedMethod {
        absl::string_view service;
        absl::string_view method;
      };
      std::vector<std::string> qualified_methods;
      std::vector<ParsedMethod> parsed_methods;
      bool exclude = false;
      uint32_t max_metadata_bytes = 0;
      uint32_t max_message_bytes = 0;

      static const grpc_core::JsonLoaderInterface* JsonLoader(
          const grpc_core::JsonArgs&);

      void JsonPostLoad(const grpc_core::Json& json,
                        const grpc_core::JsonArgs& args,
                        grpc_core::ValidationErrors* errors);
    };

    std::vector<RpcEventConfiguration> client_rpc_events;
    std::vector<RpcEventConfiguration> server_rpc_events;

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

  struct CloudMonitoring {
    static const grpc_core::JsonLoaderInterface* JsonLoader(
        const grpc_core::JsonArgs&) {
      static const auto* loader =
          grpc_core::JsonObjectLoader<CloudMonitoring>().Finish();
      return loader;
    }
  };

  struct CloudTrace {
    CloudTrace() : sampling_rate(0) {}
    float sampling_rate;

    static const grpc_core::JsonLoaderInterface* JsonLoader(
        const grpc_core::JsonArgs&) {
      static const auto* loader =
          grpc_core::JsonObjectLoader<CloudTrace>()
              .OptionalField("sampling_rate", &CloudTrace::sampling_rate)
              .Finish();
      return loader;
    }
  };

  std::optional<CloudLogging> cloud_logging;
  std::optional<CloudMonitoring> cloud_monitoring;
  std::optional<CloudTrace> cloud_trace;
  std::string project_id;
  std::map<std::string, std::string> labels;

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

  static absl::StatusOr<GcpObservabilityConfig> ReadFromEnv();
};

}
}

#endif
