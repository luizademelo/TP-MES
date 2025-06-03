Here's the commented version of the code:

```c++
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

// Static mutex for thread-safe access to the registry
Mutex* AuditLoggerRegistry::mu = new Mutex();

// Singleton instance of the audit logger registry
AuditLoggerRegistry* AuditLoggerRegistry::registry = new AuditLoggerRegistry();

// Constructor for AuditLoggerRegistry
// Initializes the registry with a default stdout logger factory
AuditLoggerRegistry::AuditLoggerRegistry() {
  auto factory = std::make_unique<StdoutAuditLoggerFactory>();
  absl::string_view name = factory->name();
  CHECK(logger_factories_map_.emplace(name, std::move(factory)).second);
}

// Registers a new audit logger factory in the registry
// Args:
//   factory: Unique pointer to the factory to be registered
void AuditLoggerRegistry::RegisterFactory(
    std::unique_ptr<AuditLoggerFactory> factory) {
  CHECK(factory != nullptr);
  MutexLock lock(mu);
  absl::string_view name = factory->name();
  CHECK(
      registry->logger_factories_map_.emplace(name, std::move(factory)).second);
}

// Checks if a factory with the given name exists in the registry
// Args:
//   name: Name of the factory to check
// Returns:
//   true if factory exists, false otherwise
bool AuditLoggerRegistry::FactoryExists(absl::string_view name) {
  MutexLock lock(mu);
  return registry->logger_factories_map_.find(name) !=
         registry->logger_factories_map_.end();
}

// Parses JSON configuration for a specific audit logger factory
// Args:
//   name: Name of the factory to use for parsing
//   json: JSON configuration to parse
// Returns:
//   StatusOr containing parsed config on success, error status if factory not found
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

// Creates an audit logger instance using the provided configuration
// Args:
//   config: Configuration for the logger to be created
// Returns:
//   Unique pointer to the created audit logger
std::unique_ptr<AuditLogger> AuditLoggerRegistry::CreateAuditLogger(
    std::unique_ptr<AuditLoggerFactory::Config> config) {
  MutexLock lock(mu);
  auto it = registry->logger_factories_map_.find(config->name());
  CHECK(it != registry->logger_factories_map_.end());
  return it->second->CreateAuditLogger(std::move(config));
}

// Resets the registry (for testing purposes only)
void AuditLoggerRegistry::TestOnlyResetRegistry() {
  MutexLock lock(mu);
  delete registry;
  registry = new AuditLoggerRegistry();
}

// Convenience function to register an audit logger factory
// Args:
//   factory: Unique pointer to the factory to be registered
void RegisterAuditLoggerFactory(std::unique_ptr<AuditLoggerFactory> factory) {
  AuditLoggerRegistry::RegisterFactory(std::move(factory));
}

}
}
```