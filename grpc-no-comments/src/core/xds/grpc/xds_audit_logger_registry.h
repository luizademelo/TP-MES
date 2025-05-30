
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_AUDIT_LOGGER_REGISTRY_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_AUDIT_LOGGER_REGISTRY_H

#include <grpc/support/port_platform.h>

#include <map>
#include <memory>

#include "absl/strings/string_view.h"
#include "envoy/config/rbac/v3/rbac.upb.h"
#include "src/core/util/json/json.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/xds_client/xds_resource_type.h"

namespace grpc_core {

class XdsAuditLoggerRegistry final {
 public:
  class ConfigFactory {
   public:
    virtual ~ConfigFactory() = default;
    virtual Json::Object ConvertXdsAuditLoggerConfig(
        const XdsResourceType::DecodeContext& context,
        absl::string_view configuration, ValidationErrors* errors) = 0;

    virtual absl::string_view type() = 0;

    virtual absl::string_view name() = 0;
  };

  XdsAuditLoggerRegistry();

  Json ConvertXdsAuditLoggerConfig(
      const XdsResourceType::DecodeContext& context,
      const envoy_config_rbac_v3_RBAC_AuditLoggingOptions_AuditLoggerConfig*
          logger_config,
      ValidationErrors* errors) const;

 private:

  std::map<absl::string_view ,
           std::unique_ptr<ConfigFactory>>
      audit_logger_config_factories_;
};

}

#endif
