
// Copyright 2023 gRPC authors.

#include "src/core/lib/security/authorization/audit_logging.h"

#include <grpc/grpc_audit_logging.h>
#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <utility>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/security/authorization/stdout_logger.h"
#include "src/core/util/sync.h"

namespace grpc_core {
namespace experimental {

Mutex* AuditLoggerRegistry::mu = new Mutex();

AuditLoggerRegistry* AuditLoggerRegistry::registry = new AuditLoggerRegistry();

AuditLoggerRegistry::AuditLoggerRegistry() {
  auto factory = std::make_unique<StdoutAuditLoggerFactory>();
  absl::string_view name = factory->name();
  CHECK(logger_factories_map_.emplace(name, std::move(factory)).second);
}

void AuditLoggerRegistry::RegisterFactory(
    std::unique_ptr<AuditLoggerFactory> factory) {
  CHECK(factory != nullptr);
  MutexLock lock(mu);
  absl::string_view name = factory->name();
  CHECK(
      registry->logger_factories_map_.emplace(name, std::move(factory)).second);
}

bool AuditLoggerRegistry::FactoryExists(absl::string_view name) {
  MutexLock lock(mu);
  return registry->logger_factories_map_.find(name) !=
         registry->logger_factories_map_.end();
}

absl::StatusOr<std::unique_ptr<AuditLoggerFactory::Config>>
AuditLoggerRegistry::ParseConfig(absl::string_view name, const Json& json) {
  MutexLock lock(mu);
  auto it = registry->logger_factories_map_.find(name);
  if (it == registry->logger_factories_map_.end()) {
    return absl::NotFoundError(
        absl::StrFormat("audit logger factory for %s does not exist", name));
  }
  return it->second->ParseAuditLoggerConfig(json);
}

std::unique_ptr<AuditLogger> AuditLoggerRegistry::CreateAuditLogger(
    std::unique_ptr<AuditLoggerFactory::Config> config) {
  MutexLock lock(mu);
  auto it = registry->logger_factories_map_.find(config->name());
  CHECK(it != registry->logger_factories_map_.end());
  return it->second->CreateAuditLogger(std::move(config));
}

void AuditLoggerRegistry::TestOnlyResetRegistry() {
  MutexLock lock(mu);
  delete registry;
  registry = new AuditLoggerRegistry();
}

void RegisterAuditLoggerFactory(std::unique_ptr<AuditLoggerFactory> factory) {
  AuditLoggerRegistry::RegisterFactory(std::move(factory));
}

}
}
