
// Copyright 2023 gRPC authors.

#include "test/core/test_util/audit_logging_utils.h"

#include <grpc/grpc_audit_logging.h>
#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/util/json/json_writer.h"

namespace grpc_core {
namespace testing {

namespace {

constexpr absl::string_view kLoggerName = "test_logger";

using experimental::AuditContext;
using experimental::AuditLogger;
using experimental::AuditLoggerFactory;
using experimental::Json;

}

absl::string_view TestAuditLogger::name() const { return kLoggerName; }
void TestAuditLogger::Log(const AuditContext& context) {
  audit_logs_->push_back(JsonDump(Json::FromObject({
      {"rpc_method", Json::FromString(std::string(context.rpc_method()))},
      {"principal", Json::FromString(std::string(context.principal()))},
      {"policy_name", Json::FromString(std::string(context.policy_name()))},
      {"matched_rule", Json::FromString(std::string(context.matched_rule()))},
      {"authorized", Json::FromBool(context.authorized())},
  })));
}

absl::string_view TestAuditLoggerFactory::Config::name() const {
  return kLoggerName;
}

absl::string_view TestAuditLoggerFactory::name() const { return kLoggerName; }

absl::StatusOr<std::unique_ptr<AuditLoggerFactory::Config>>
TestAuditLoggerFactory::ParseAuditLoggerConfig(const Json&) {
  return std::make_unique<Config>();
}

std::unique_ptr<AuditLogger> TestAuditLoggerFactory::CreateAuditLogger(
    std::unique_ptr<AuditLoggerFactory::Config>) {
  return std::make_unique<TestAuditLogger>(audit_logs_);
}

}
}
