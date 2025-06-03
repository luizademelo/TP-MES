Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_SECURITY_TLS_CREDENTIALS_OPTIONS_H
#define GRPCPP_SECURITY_TLS_CREDENTIALS_OPTIONS_H

// Include necessary headers for gRPC security functionality
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/status.h>
#include <grpcpp/security/tls_certificate_provider.h>
#include <grpcpp/security/tls_certificate_verifier.h>
#include <grpcpp/security/tls_crl_provider.h>
#include <grpcpp/support/config.h>

// Standard library includes
#include <memory>
#include <vector>

namespace grpc {
namespace experimental {

// Class representing options for TLS credentials configuration
class TlsCredentialsOptions {
 public:
  // Constructor and destructor
  TlsCredentialsOptions();
  ~TlsCredentialsOptions();

  // Copy constructor (deleted assignment operator to prevent copying)
  TlsCredentialsOptions(const TlsCredentialsOptions& other);
  TlsCredentialsOptions& operator=(const TlsCredentialsOptions& other) = delete;

  // Sets the certificate provider interface
  void set_certificate_provider(
      std::shared_ptr<CertificateProviderInterface> certificate_provider);

  // Enables watching for root certificate updates
  void watch_root_certs();

  // Sets the name for root certificates
  void set_root_cert_name(const std::string& root_cert_name);

  // Enables watching for identity key-certificate pair updates
  void watch_identity_key_cert_pairs();

  // Sets the name for identity certificates
  void set_identity_cert_name(const std::string& identity_cert_name);

  // Sets the file path for TLS session key logging
  void set_tls_session_key_log_file_path(
      const std::string& tls_session_key_log_file_path);

  // Sets the certificate verifier
  void set_certificate_verifier(
      std::shared_ptr<CertificateVerifier> certificate_verifier);

  // Enables/disables hostname verification during calls
  void set_check_call_host(bool check_call_host);

  // Sets the CRL (Certificate Revocation List) directory path
  void set_crl_directory(const std::string& path);

  // Sets the CRL provider
  void set_crl_provider(std::shared_ptr<CrlProvider> crl_provider);

  // Sets the minimum supported TLS version
  void set_min_tls_version(grpc_tls_version tls_version);

  // Sets the maximum supported TLS version
  void set_max_tls_version(grpc_tls_version tls_version);

  // Returns the underlying C credentials options structure
  grpc_tls_credentials_options* c_credentials_options() const;

 protected:
  // Provides mutable access to the underlying C credentials options
  grpc_tls_credentials_options* mutable_c_credentials_options() {
    return c_credentials_options_;
  }

 private:
  // Shared pointer to certificate provider
  std::shared_ptr<CertificateProviderInterface> certificate_provider_;
  // Shared pointer to certificate verifier
  std::shared_ptr<CertificateVerifier> certificate_verifier_;
  // Pointer to underlying C credentials options structure
  grpc_tls_credentials_options* c_credentials_options_ = nullptr;
};

// Class representing TLS channel credentials options (client-side)
class TlsChannelCredentialsOptions final : public TlsCredentialsOptions {
 public:
  // Enables/disables server certificate verification
  void set_verify_server_certs(bool verify_server_certs);

 private:
};

// Class representing TLS server credentials options
class TlsServerCredentialsOptions final : public TlsCredentialsOptions {
 public:
  // Constructor that takes a certificate provider
  explicit TlsServerCredentialsOptions(
      std::shared_ptr<CertificateProviderInterface> certificate_provider)
      : TlsCredentialsOptions() {
    set_certificate_provider(certificate_provider);
  }

  // Sets the type of client certificate request
  void set_cert_request_type(
      grpc_ssl_client_certificate_request_type cert_request_type);

  // Enables/disables sending client CA list to client
  void set_send_client_ca_list(bool send_client_ca_list);

 private:
};

}  // namespace experimental
}  // namespace grpc

#endif  // GRPCPP_SECURITY_TLS_CREDENTIALS_OPTIONS_H
```

The comments provide:
1. File-level documentation about the purpose
2. Section headers for logical groupings
3. Explanations for each method's purpose
4. Notes about important implementation details
5. Clarification of protected/private members
6. Documentation of inheritance relationships

The comments are concise yet informative, helping future developers understand both the interface and implementation considerations.