Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_CERTIFICATE_PROVIDER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_CERTIFICATE_PROVIDER_H

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_distributor.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_provider.h"
#include "src/core/util/matchers.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"

namespace grpc_core {

// XdsCertificateProvider is an implementation of grpc_tls_certificate_provider
// that provides certificate management for xDS. It can provide both root and
// identity certificates, with optional SAN (Subject Alternative Name) matching
// and client certificate requirements.
class XdsCertificateProvider final : public grpc_tls_certificate_provider {
 public:
  // Constructor for server-side usage.
  // Args:
  //   root_cert_provider: Provider for root certificates
  //   root_cert_name: Name of the root certificate to use
  //   use_system_root_certs: Whether to fall back to system root certificates
  //   identity_cert_provider: Provider for identity certificates
  //   identity_cert_name: Name of the identity certificate to use
  //   san_matchers: List of SAN matchers for certificate validation
  XdsCertificateProvider(
      RefCountedPtr<grpc_tls_certificate_provider> root_cert_provider,
      absl::string_view root_cert_name, bool use_system_root_certs,
      RefCountedPtr<grpc_tls_certificate_provider> identity_cert_provider,
      absl::string_view identity_cert_name,
      std::vector<StringMatcher> san_matchers);

  // Constructor for client-side usage.
  // Args:
  //   root_cert_provider: Provider for root certificates
  //   root_cert_name: Name of the root certificate to use
  //   identity_cert_provider: Provider for identity certificates
  //   identity_cert_name: Name of the identity certificate to use
  //   require_client_certificate: Whether client cert is required
  XdsCertificateProvider(
      RefCountedPtr<grpc_tls_certificate_provider> root_cert_provider,
      absl::string_view root_cert_name,
      RefCountedPtr<grpc_tls_certificate_provider> identity_cert_provider,
      absl::string_view identity_cert_name, bool require_client_certificate);

  ~XdsCertificateProvider() override;

  // Returns the certificate distributor instance
  RefCountedPtr<grpc_tls_certificate_distributor> distributor() const override {
    return distributor_;
  }

  // Returns the unique type name of this certificate provider
  UniqueTypeName type() const override;

  // Returns true if root certificates are provided
  bool ProvidesRootCerts() const { return root_cert_provider_ != nullptr; }
  // Returns true if system root certificates should be used as fallback
  bool UseSystemRootCerts() const { return use_system_root_certs_; }
  // Returns true if identity certificates are provided
  bool ProvidesIdentityCerts() const {
    return identity_cert_provider_ != nullptr;
  }
  // Returns true if client certificate is required
  bool require_client_certificate() const {
    return require_client_certificate_;
  }
  // Returns the list of SAN matchers for certificate validation
  const std::vector<StringMatcher>& san_matchers() const {
    return san_matchers_;
  }

  // Returns the channel argument name for this certificate provider
  static absl::string_view ChannelArgName() {
    return "grpc.internal.xds_certificate_provider";
  }
  // Compares two XdsCertificateProvider instances for channel args
  static int ChannelArgsCompare(const XdsCertificateProvider* a,
                                const XdsCertificateProvider* b) {
    if (a == nullptr || b == nullptr) return QsortCompare(a, b);
    return a->Compare(b);
  }

 private:
  // Implementation of comparison between certificate providers
  int CompareImpl(const grpc_tls_certificate_provider* other) const override {
    return QsortCompare(static_cast<const grpc_tls_certificate_provider*>(this),
                        other);
  }

  // Callback for watching certificate status changes
  void WatchStatusCallback(std::string cert_name, bool root_being_watched,
                           bool identity_being_watched);

  // Certificate distributor instance
  RefCountedPtr<grpc_tls_certificate_distributor> distributor_;
  // Provider for root certificates
  RefCountedPtr<grpc_tls_certificate_provider> root_cert_provider_;
  // Name of the root certificate to use
  std::string root_cert_name_;
  // Whether to use system root certificates as fallback
  bool use_system_root_certs_ = false;
  // Provider for identity certificates
  RefCountedPtr<grpc_tls_certificate_provider> identity_cert_provider_;
  // Name of the identity certificate to use
  std::string identity_cert_name_;
  // List of SAN matchers for certificate validation
  std::vector<StringMatcher> san_matchers_;
  // Whether client certificate is required
  bool require_client_certificate_ = false;

  // Watcher for root certificate updates
  grpc_tls_certificate_distributor::TlsCertificatesWatcherInterface*
      root_cert_watcher_ = nullptr;
  // Watcher for identity certificate updates
  grpc_tls_certificate_distributor::TlsCertificatesWatcherInterface*
      identity_cert_watcher_ = nullptr;
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_XDS_GRPC_XDS_CERTIFICATE_PROVIDER_H
```

The comments explain:
1. The overall purpose of the XdsCertificateProvider class
2. The difference between the two constructors (server-side vs client-side usage)
3. The purpose of each public method
4. The meaning of each private member variable
5. Key implementation details like the certificate watching mechanism

The comments are concise but provide enough information for a developer to understand how to use and maintain this class. They follow the style of existing comments in the codebase and use consistent terminology.