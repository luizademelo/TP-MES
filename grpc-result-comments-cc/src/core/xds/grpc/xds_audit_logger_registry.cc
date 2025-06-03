Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/core/xds/grpc/xds_audit_logger_registry.h"

#include <grpc/support/port_platform.h>

#include <optional>
#include <string>
#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "envoy/config/core/v3/extension.upb.h"
#include "envoy/config/rbac/v3/rbac.upb.h"
#include "src/core/lib/security/authorization/audit_logging.h"
#include "src/core/util/match.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/grpc/xds_common_types_parser.h"

namespace grpc_core {

namespace {

using experimental::AuditLoggerRegistry;

// Implementation of ConfigFactory for stdout audit logger
class StdoutLoggerConfigFactory final
    : public XdsAuditLoggerRegistry::ConfigFactory {
 public:
  // Converts XDS audit logger configuration to JSON format
  // Currently returns empty object as stdout logger doesn't need configuration
  Json::Object ConvertXdsAuditLoggerConfig(
      const XdsResourceType::DecodeContext& ,
      absl::string_view ,
      ValidationErrors* ) override {
    return {};
  }

  // Returns the type identifier for this logger
  absl::string_view type() override { return Type(); }
  
  // Returns the name identifier for this logger
  absl::string_view name() override { return "stdout_logger"; }

  // Static method to get the type identifier for stdout logger
  static absl::string_view Type() {
    return "envoy.extensions.rbac.audit_loggers.stream.v3.StdoutAuditLog";
  }
};

}  // namespace

// Constructor for XdsAuditLoggerRegistry that registers the stdout logger factory
XdsAuditLoggerRegistry::XdsAuditLoggerRegistry() {
  audit_logger_config_factories_.emplace(
      StdoutLoggerConfigFactory::Type(),
      std::make_unique<StdoutLoggerConfigFactory>());
}

// Converts XDS audit logger configuration to JSON format
// Handles both typed extension config and direct JSON configurations
Json XdsAuditLoggerRegistry::ConvertXdsAuditLoggerConfig(
    const XdsResourceType::DecodeContext& context,
    const envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig*
        logger_config,
    ValidationErrors* errors) const {
  // Extract the typed extension configuration from the logger config
  const auto* typed_extension_config =
      envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_audit_logger(
          logger_config);
  ValidationErrors::ScopedField field(errors, ".audit_logger");
  if (typed_extension_config == nullptr) {
    errors->AddError("field not present");
    return Json();
  }
  
  // Extract the typed config from the extension configuration
  ValidationErrors::ScopedField field2(errors, ".typed_config");
  const auto* typed_config =
      envoy_config_core_v3_TypedExtensionConfig_typed_config(
          typed_extension_config);
  auto extension = ExtractXdsExtension(context, typed_config, errors);
  if (!extension.has_value()) return Json();
  
  absl::string_view name;
  Json config;
  
  // Match the extension value type to either string (serialized config) or JSON
  Match(
      extension->value,

      // Handler for serialized string configuration
      [&](absl::string_view serialized_value) {
        auto it = audit_logger_config_factories_.find(extension->type);
        if (it == audit_logger_config_factories_.end()) return;
        name = it->second->name();
        config = Json::FromObject(it->second->ConvertXdsAuditLoggerConfig(
            context, serialized_value, errors));
      },

      // Handler for direct JSON configuration
      [&](Json json) {
        if (!AuditLoggerRegistry::FactoryExists(extension->type)) return;
        name = extension->type;
        config = json;
      });

  // If no valid logger was found, handle error unless logger is optional
  if (name.empty()) {
    if (!envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig_is_optional(
            logger_config)) {
      errors->AddError("unsupported audit logger type");
    }
    return Json();
  }

  // Validate the parsed configuration
  auto result = AuditLoggerRegistry::ParseConfig(name, config);
  if (!result.ok()) {
    errors->AddError(result.status().message());
    return Json();
  }
  
  // Return the configuration as a JSON object with the logger name as key
  return Json::FromObject({{std::string(name), std::move(config)}});
}
}  // namespace grpc_core
```