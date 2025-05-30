
// Copyright 2022 gRPC authors.

#include "src/cpp/ext/gcp/observability_config.h"

#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <algorithm>
#include <optional>
#include <utility>

#include "absl/status/status.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/transport/error_utils.h"
#include "src/core/util/env.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/load_file.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/validation_errors.h"

namespace grpc {
namespace internal {

namespace {

absl::StatusOr<std::string> GetGcpObservabilityConfigContents() {

  std::string contents_str;
  auto path = grpc_core::GetEnv("GRPC_GCP_OBSERVABILITY_CONFIG_FILE");
  if (path.has_value() && !path.value().empty()) {
    auto contents = grpc_core::LoadFile(*path, true);
    if (!contents.ok()) {
      return absl::FailedPreconditionError(absl::StrCat(
          "error loading file ", *path, ": ", contents.status().ToString()));
    }
    return std::string(contents->as_string_view());
  }

  auto env_config = grpc_core::GetEnv("GRPC_GCP_OBSERVABILITY_CONFIG");
  if (env_config.has_value() && !env_config.value().empty()) {
    return std::move(*env_config);
  }

  return absl::FailedPreconditionError(
      "Environment variables GRPC_GCP_OBSERVABILITY_CONFIG_FILE or "
      "GRPC_GCP_OBSERVABILITY_CONFIG "
      "not defined");
}

std::string GetProjectIdFromGcpEnvVar() {

  std::optional<std::string> project_id = grpc_core::GetEnv("GCP_PROJECT");
  if (project_id.has_value() && !project_id->empty()) {
    return project_id.value();
  }

  project_id = grpc_core::GetEnv("GCLOUD_PROJECT");
  if (project_id.has_value() && !project_id->empty()) {
    return project_id.value();
  }

  project_id = grpc_core::GetEnv("GOOGLE_CLOUD_PROJECT");
  if (project_id.has_value() && !project_id->empty()) {
    return project_id.value();
  }
  return "";
}

}

const grpc_core::JsonLoaderInterface*
GcpObservabilityConfig::CloudLogging::RpcEventConfiguration::JsonLoader(
    const grpc_core::JsonArgs&) {
  static const auto* loader =
      grpc_core::JsonObjectLoader<RpcEventConfiguration>()
          .OptionalField("methods", &RpcEventConfiguration::qualified_methods)
          .OptionalField("exclude", &RpcEventConfiguration::exclude)
          .OptionalField("max_metadata_bytes",
                         &RpcEventConfiguration::max_metadata_bytes)
          .OptionalField("max_message_bytes",
                         &RpcEventConfiguration::max_message_bytes)
          .Finish();
  return loader;
}

void GcpObservabilityConfig::CloudLogging::RpcEventConfiguration::JsonPostLoad(
    const grpc_core::Json& , const grpc_core::JsonArgs& ,
    grpc_core::ValidationErrors* errors) {
  grpc_core::ValidationErrors::ScopedField methods_field(errors, ".methods");
  parsed_methods.reserve(qualified_methods.size());
  for (size_t i = 0; i < qualified_methods.size(); ++i) {
    grpc_core::ValidationErrors::ScopedField methods_index(
        errors, absl::StrCat("[", i, "]"));
    std::vector<absl::string_view> parts =
        absl::StrSplit(qualified_methods[i], '/', absl::SkipEmpty());
    if (parts.size() > 2) {
      errors->AddError("methods[] can have at most a single '/'");
      continue;
    } else if (parts.empty()) {
      errors->AddError("Empty configuration");
      continue;
    } else if (parts.size() == 1) {
      if (parts[0] != "*") {
        errors->AddError("Illegal methods[] configuration");
        continue;
      }
      if (exclude) {
        errors->AddError(
            "Wildcard match '*' not allowed when 'exclude' is set");
        continue;
      }
      parsed_methods.push_back(ParsedMethod{parts[0], ""});
    } else {

      if (absl::StrContains(parts[0], '*')) {
        errors->AddError("Configuration of type '*/method' not allowed");
        continue;
      }
      if (absl::StrContains(parts[1], '*') && parts[1].size() != 1) {
        errors->AddError("Wildcard specified for method in incorrect manner");
        continue;
      }
      parsed_methods.push_back(ParsedMethod{parts[0], parts[1]});
    }
  }
}

absl::StatusOr<GcpObservabilityConfig> GcpObservabilityConfig::ReadFromEnv() {
  auto config_contents = GetGcpObservabilityConfigContents();
  if (!config_contents.ok()) {
    return config_contents.status();
  }
  auto config_json = grpc_core::JsonParse(*config_contents);
  if (!config_json.ok()) {
    return config_json.status();
  }
  auto config = grpc_core::LoadFromJson<GcpObservabilityConfig>(*config_json);
  if (!config.ok()) {
    return config.status();
  }
  if (config->project_id.empty()) {

    config->project_id = GetProjectIdFromGcpEnvVar();
    if (config->project_id.empty()) {

      return absl::FailedPreconditionError("GCP Project ID not found.");
    }
  }
  return config;
}

}
}
