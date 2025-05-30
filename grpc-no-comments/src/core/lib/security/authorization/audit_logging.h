
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_AUDIT_LOGGING_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_AUDIT_LOGGING_H

#include <grpc/grpc_audit_logging.h>
#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>

#include <map>
#include <memory>

#include "absl/base/thread_annotations.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/util/sync.h"

namespace grpc_core {
namespace experimental {

class AuditLoggerRegistry {
 public:
  static void RegisterFactory(std::unique_ptr<AuditLoggerFactory>);

  static bool FactoryExists(absl::string_view name);

  static absl::StatusOr<std::unique_ptr<AuditLoggerFactory::Config>>
  ParseConfig(absl::string_view name, const Json& json);

  static std::unique_ptr<AuditLogger> CreateAuditLogger(
      std::unique_ptr<AuditLoggerFactory::Config>);

  static void TestOnlyResetRegistry();

 private:
  AuditLoggerRegistry();

  static Mutex* mu;

  static AuditLoggerRegistry* registry ABSL_GUARDED_BY(mu);

  std::map<absl::string_view, std::unique_ptr<AuditLoggerFactory>>
      logger_factories_map_ ABSL_GUARDED_BY(mu);
};

}
}

#endif
