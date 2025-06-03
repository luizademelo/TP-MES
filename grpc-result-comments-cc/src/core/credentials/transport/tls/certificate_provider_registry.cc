Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

// Include necessary headers for the implementation
#include "src/core/credentials/transport/tls/certificate_provider_registry.h"
#include <grpc/support/port_platform.h>

// Standard library includes
#include <string>
#include <utility>

// Abseil logging and checking utilities
#include "absl/log/check.h"
#include "absl/log/log.h"

namespace grpc_core {

// Registers a certificate provider factory with the registry builder
// Args:
//   factory - unique_ptr to the factory to be registered
// Notes:
//   - Logs the registration attempt at VLOG level 2
//   - Uses CHECK to ensure the factory name wasn't already registered
//   - Takes ownership of the factory via std::move
void CertificateProviderRegistry::Builder::RegisterCertificateProviderFactory(
    std::unique_ptr<CertificateProviderFactory> factory) {
  absl::string_view name = factory->name();
  VLOG(2) << "registering certificate provider factory for \"" << name << "\"";
  CHECK(factories_.emplace(name, std::move(factory)).second);
}

// Constructs and returns a CertificateProviderRegistry from the registered factories
// Returns:
//   A new CertificateProviderRegistry instance containing all registered factories
// Notes:
//   - Moves the factories map into the new registry instance
CertificateProviderRegistry CertificateProviderRegistry::Builder::Build() {
  return CertificateProviderRegistry(std::move(factories_));
}

// Looks up a certificate provider factory by name in the registry
// Args:
//   name - The name of the factory to look up (as string_view)
// Returns:
//   - Pointer to the factory if found
//   - nullptr if no factory with that name exists
CertificateProviderFactory*
CertificateProviderRegistry::LookupCertificateProviderFactory(
    absl::string_view name) const {
  auto it = factories_.find(name);
  if (it == factories_.end()) return nullptr;
  return it->second.get();
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose and behavior of each method
2. Important implementation details (like ownership transfer)
3. Parameters and return values
4. Error handling (CHECK for duplicate registration)
5. Logging behavior
6. The overall flow of factory registration and lookup

The comments are kept concise while providing all the essential information a maintainer would need to understand and work with this code.