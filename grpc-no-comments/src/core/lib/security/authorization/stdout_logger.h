// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_STDOUT_LOGGER_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_STDOUT_LOGGER_H

#include <grpc/grpc_audit_logging.h>
#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace grpc_core {
namespace experimental {

class StdoutAuditLogger : public AuditLogger {
 public:
  StdoutAuditLogger() = default;
  absl::string_view name() const override { return "stdout_logger"; }
  void Log(const AuditContext&) override;
};

class StdoutAuditLoggerFactory : public AuditLoggerFactory {
 public:
  class Config : public AuditLoggerFactory::Config {
   public:
    Config() = default;
    absl::string_view name() const override;
    std::string ToString() const override;
  };
  StdoutAuditLoggerFactory() = default;

  absl::string_view name() const override;

  absl::StatusOr<std::unique_ptr<AuditLoggerFactory::Config>>
  ParseAuditLoggerConfig(const Json& json) override;

  std::unique_ptr<AuditLogger> CreateAuditLogger(
      std::unique_ptr<AuditLoggerFactory::Config>) override;
};

}
}

#endif
