
// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_AUDIT_LOGGING_UTILS_H
#define GRPC_TEST_CORE_TEST_UTIL_AUDIT_LOGGING_UTILS_H

#include <grpc/grpc_audit_logging.h>
#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <string>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace grpc_core {
namespace testing {

class TestAuditLogger : public experimental::AuditLogger {
 public:
  explicit TestAuditLogger(std::vector<std::string>* audit_logs)
      : audit_logs_(audit_logs) {}

  absl::string_view name() const override;
  void Log(const experimental::AuditContext& context) override;

 private:
  std::vector<std::string>* audit_logs_;
};

class TestAuditLoggerFactory : public experimental::AuditLoggerFactory {
 public:
  class Config : public AuditLoggerFactory::Config {
    absl::string_view name() const override;
    std::string ToString() const override { return "{}"; }
  };

  explicit TestAuditLoggerFactory(std::vector<std::string>* audit_logs)
      : audit_logs_(audit_logs) {}

  absl::string_view name() const override;
  absl::StatusOr<std::unique_ptr<AuditLoggerFactory::Config>>
  ParseAuditLoggerConfig(const experimental::Json&) override;
  std::unique_ptr<experimental::AuditLogger> CreateAuditLogger(
      std::unique_ptr<AuditLoggerFactory::Config>) override;

 private:
  std::vector<std::string>* audit_logs_;
};

}
}

#endif
