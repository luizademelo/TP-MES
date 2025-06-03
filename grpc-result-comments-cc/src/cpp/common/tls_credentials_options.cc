Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

// Include necessary gRPC security and TLS-related headers
#include <grpc/credentials.h>
#include <grpc/grpc_crl_provider.h>
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpcpp/security/tls_certificate_provider.h>
#include <grpcpp/security/tls_certificate_verifier.h>
#include <grpcpp/security/tls_credentials_options.h>
#include <grpcpp/security/tls_crl_provider.h>

#include <memory>
#include <string>

#include "absl/log/check.h"

namespace grpc {
namespace experimental {

// Constructor: Creates a new TlsCredentialsOptions object with default settings
TlsCredentialsOptions::TlsCredentialsOptions() {
  c_credentials_options_ = grpc_tls_credentials_options_create();
}

// Destructor: Cleans up the underlying C credentials options
TlsCredentialsOptions::~TlsCredentialsOptions() {
  grpc_tls_credentials_options_destroy(c_credentials_options_);
}

// Copy constructor: Creates a deep copy of another TlsCredentialsOptions object
TlsCredentialsOptions::TlsCredentialsOptions(
    const TlsCredentialsOptions& other) {
  c_credentials_options_ =
      grpc_tls_credentials_options_copy(other.c_credentials_options_);
}

// Sets the certificate provider for these credentials
void TlsCredentialsOptions::set_certificate_provider(
    std::shared_ptr<CertificateProviderInterface> certificate_provider) {
  certificate_provider_ = certificate_provider;
  if (certificate_provider_ != nullptr) {
    grpc_tls_credentials_options_set_certificate_provider(
        c_credentials_options_, certificate_provider_->c_provider());
  }
}

// Sets the CRL (Certificate Revocation List) provider for these credentials
void TlsCredentialsOptions::set_crl_provider(
    std::shared_ptr<CrlProvider> crl_provider) {
  grpc_tls_credentials_options_set_crl_provider(c_credentials_options_,
                                                crl_provider);
}

// Enables watching for root certificate updates
void TlsCredentialsOptions::watch_root_certs() {
  grpc_tls_credentials_options_watch_root_certs(c_credentials_options_);
}

// Sets the name for the root certificate
void TlsCredentialsOptions::set_root_cert_name(
    const std::string& root_cert_name) {
  grpc_tls_credentials_options_set_root_cert_name(c_credentials_options_,
                                                  root_cert_name.c_str());
}

// Enables watching for identity key-certificate pair updates
void TlsCredentialsOptions::watch_identity_key_cert_pairs() {
  grpc_tls_credentials_options_watch_identity_key_cert_pairs(
      c_credentials_options_);
}

// Sets the name for the identity certificate
void TlsCredentialsOptions::set_identity_cert_name(
    const std::string& identity_cert_name) {
  grpc_tls_credentials_options_set_identity_cert_name(
      c_credentials_options_, identity_cert_name.c_str());
}

// Sets the directory path for CRL files
void TlsCredentialsOptions::set_crl_directory(const std::string& path) {
  grpc_tls_credentials_options_set_crl_directory(c_credentials_options_,
                                                 path.c_str());
}

// Sets the file path for TLS session key logging
void TlsCredentialsOptions::set_tls_session_key_log_file_path(
    const std::string& tls_session_key_log_file_path) {
  grpc_tls_credentials_options_set_tls_session_key_log_file_path(
      c_credentials_options_, tls_session_key_log_file_path.c_str());
}

// Sets the certificate verifier for these credentials
void TlsCredentialsOptions::set_certificate_verifier(
    std::shared_ptr<CertificateVerifier> certificate_verifier) {
  certificate_verifier_ = certificate_verifier;
  if (certificate_verifier_ != nullptr) {
    grpc_tls_credentials_options_set_certificate_verifier(
        c_credentials_options_, certificate_verifier_->c_verifier());
  }
}

// Sets the minimum TLS version allowed for connections
void TlsCredentialsOptions::set_min_tls_version(grpc_tls_version tls_version) {
  grpc_tls_credentials_options* options = mutable_c_credentials_options();
  CHECK_NE(options, nullptr);
  grpc_tls_credentials_options_set_min_tls_version(options, tls_version);
}

// Sets the maximum TLS version allowed for connections
void TlsCredentialsOptions::set_max_tls_version(grpc_tls_version tls_version) {
  grpc_tls_credentials_options* options = mutable_c_credentials_options();
  CHECK_NE(options, nullptr);
  grpc_tls_credentials_options_set_max_tls_version(options, tls_version);
}

// Returns a copy of the underlying C credentials options
grpc_tls_credentials_options* TlsCredentialsOptions::c_credentials_options()
    const {
  return grpc_tls_credentials_options_copy(c_credentials_options_);
}

// Enables or disables hostname verification for calls
void TlsCredentialsOptions::set_check_call_host(bool check_call_host) {
  grpc_tls_credentials_options* options = mutable_c_credentials_options();
  CHECK_NE(options, nullptr);
  grpc_tls_credentials_options_set_check_call_host(options, check_call_host);
}

// Channel-specific options: enables or disables server certificate verification
void TlsChannelCredentialsOptions::set_verify_server_certs(
    bool verify_server_certs) {
  grpc_tls_credentials_options* options = mutable_c_credentials_options();
  CHECK_NE(options, nullptr);
  grpc_tls_credentials_options_set_verify_server_cert(options,
                                                      verify_server_certs);
}

// Server-specific options: sets the client certificate request type
void TlsServerCredentialsOptions::set_cert_request_type(
    grpc_ssl_client_certificate_request_type cert_request_type) {
  grpc_tls_credentials_options* options = mutable_c_credentials_options();
  CHECK_NE(options, nullptr);
  grpc_tls_credentials_options_set_cert_request_type(options,
                                                     cert_request_type);
}

// Server-specific options: enables or disables sending client CA list
void TlsServerCredentialsOptions::set_send_client_ca_list(
    bool send_client_ca_list) {
  grpc_tls_credentials_options* options = mutable_c_credentials_options();
  CHECK_NE(options, nullptr);
  grpc_tls_credentials_options_set_send_client_ca_list(options,
                                                       send_client_ca_list);
}

}  // namespace experimental
}  // namespace grpc
```