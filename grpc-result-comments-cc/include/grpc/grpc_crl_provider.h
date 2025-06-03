Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#ifndef GRPC_GRPC_CRL_PROVIDER_H
#define GRPC_GRPC_CRL_PROVIDER_H

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace grpc_core {
namespace experimental {

// Represents a Certificate Revocation List (CRL) in X.509 format
class Crl {
 public:
  // Parses a CRL from its string representation
  // Returns a unique_ptr to Crl on success, or an error status on failure
  static absl::StatusOr<std::unique_ptr<Crl>> Parse(
      absl::string_view crl_string);
  
  // Virtual destructor for proper cleanup of derived classes
  virtual ~Crl() = default;
  
  // Returns the issuer name of the CRL
  virtual absl::string_view Issuer() = 0;
};

// Contains information about a certificate needed for CRL lookup
class CertificateInfo {
 public:
  // Virtual destructor for proper cleanup of derived classes
  virtual ~CertificateInfo() = default;
  
  // Returns the issuer name of the certificate
  virtual absl::string_view Issuer() const = 0;
  
  // Returns the authority key identifier of the certificate
  virtual absl::string_view AuthorityKeyIdentifier() const = 0;
};

// Interface for providers that can supply CRLs
class CrlProvider {
 public:
  // Virtual destructor for proper cleanup of derived classes
  virtual ~CrlProvider() = default;

  // Retrieves a CRL for the given certificate information
  // Returns a shared_ptr to the CRL if found, nullptr otherwise
  virtual std::shared_ptr<Crl> GetCrl(
      const CertificateInfo& certificate_info) = 0;
};

// Creates a static CRL provider that uses a fixed set of CRLs
// Takes a span of CRL strings as input
// Returns a shared_ptr to the provider or an error status
absl::StatusOr<std::shared_ptr<CrlProvider>> CreateStaticCrlProvider(
    absl::Span<const std::string> crls);

// Creates a CRL provider that reloads CRLs from a directory periodically
// Parameters:
//   directory - path to directory containing CRL files
//   refresh_duration - interval between directory refreshes
//   reload_error_callback - function called when reload fails
// Returns a shared_ptr to the provider or an error status
absl::StatusOr<std::shared_ptr<CrlProvider>> CreateDirectoryReloaderCrlProvider(
    absl::string_view directory, std::chrono::seconds refresh_duration,
    std::function<void(absl::Status)> reload_error_callback);

}  // namespace experimental
}  // namespace grpc_core

// Sets the CRL provider for TLS credentials options
// Parameters:
//   options - TLS credentials options to configure
//   provider - CRL provider to set
void grpc_tls_credentials_options_set_crl_provider(
    grpc_tls_credentials_options* options,
    std::shared_ptr<grpc_core::experimental::CrlProvider> provider);

#endif  // GRPC_GRPC_CRL_PROVIDER_H
```

The comments explain:
1. The purpose of each class and its role in the CRL system
2. The functionality of each method
3. The parameters and return values of functions
4. The behavior of the different CRL provider implementations
5. The overall structure and relationships between components

The comments are designed to help future developers understand:
- How to use these classes
- What each component is responsible for
- The expected behavior of each function
- How the different pieces fit together in the CRL verification system