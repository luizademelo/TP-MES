Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SECURITY_SERVER_CREDENTIALS_H
#define GRPCPP_SECURITY_SERVER_CREDENTIALS_H

// Include necessary headers for security constants, library implementation,
// authentication, TLS, and configuration
#include <grpc/grpc_security_constants.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/security/auth_metadata_processor.h>
#include <grpcpp/security/tls_credentials_options.h>
#include <grpcpp/support/config.h>

#include <memory>
#include <vector>

// Forward declaration of grpc_server structure
struct grpc_server;

namespace grpc {

// Forward declarations
class Server;
class ServerCredentials;

// Options for configuring SSL server credentials
struct SslServerCredentialsOptions {
  // Default constructor - no client auth by default
  SslServerCredentialsOptions()
      : force_client_auth(false),
        client_certificate_request(GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE) {}
  
  // Constructor with explicit client certificate request type
  explicit SslServerCredentialsOptions(
      grpc_ssl_client_certificate_request_type request_type)
      : force_client_auth(false), client_certificate_request(request_type) {}

  // Structure for holding private key and certificate chain pairs
  struct PemKeyCertPair {
    std::string private_key;  // PEM-encoded private key
    std::string cert_chain;   // PEM-encoded certificate chain
  };
  
  std::string pem_root_certs;  // PEM-encoded root certificates
  std::vector<PemKeyCertPair> pem_key_cert_pairs;  // Key-cert pairs for server

  bool force_client_auth;  // Whether to enforce client authentication

  // Type of client certificate request
  grpc_ssl_client_certificate_request_type client_certificate_request;
};

// Creates XDS server credentials using fallback credentials
std::shared_ptr<ServerCredentials> XdsServerCredentials(
    const std::shared_ptr<ServerCredentials>& fallback_credentials);

// Base class for server credentials
class ServerCredentials : private grpc::internal::GrpcLibrary {
 public:
  ~ServerCredentials() override;

  // Sets the auth metadata processor for these credentials
  virtual void SetAuthMetadataProcessor(
      const std::shared_ptr<grpc::AuthMetadataProcessor>& processor);

 protected:
  // Constructor taking raw grpc_server_credentials
  explicit ServerCredentials(grpc_server_credentials* creds);

  // Returns the underlying C credentials object
  grpc_server_credentials* c_creds() const { return c_creds_; }

 private:
  // Grant access to Server, ServerBuilder, and XdsServerCredentials
  friend class Server;
  friend class ServerBuilder;
  friend std::shared_ptr<ServerCredentials> grpc::XdsServerCredentials(
      const std::shared_ptr<ServerCredentials>& fallback_credentials);

  // Internal method to add port to server using these credentials
  virtual int AddPortToServer(const std::string& addr, grpc_server* server);

  grpc_server_credentials* c_creds_;  // Underlying C credentials object
};

// Creates SSL server credentials with the specified options
std::shared_ptr<ServerCredentials> SslServerCredentials(
    const grpc::SslServerCredentialsOptions& options);

// Creates insecure server credentials (no encryption)
std::shared_ptr<ServerCredentials> InsecureServerCredentials();

namespace experimental {

// Options for ALTS (Application Layer Transport Security) server credentials
struct AltsServerCredentialsOptions {
  // Currently empty, can be extended with ALTS-specific options
};

// Creates ALTS server credentials with the specified options
std::shared_ptr<ServerCredentials> AltsServerCredentials(
    const AltsServerCredentialsOptions& options);

// Creates local server credentials for inter-process communication
std::shared_ptr<ServerCredentials> LocalServerCredentials(
    grpc_local_connect_type type);

// Creates TLS server credentials with the specified options
std::shared_ptr<ServerCredentials> TlsServerCredentials(
    const experimental::TlsServerCredentialsOptions& options);

}  // namespace experimental
}  // namespace grpc

#endif  // GRPCPP_SECURITY_SERVER_CREDENTIALS_H
```

The comments explain:
1. The purpose of each include directive
2. The structure and purpose of SslServerCredentialsOptions
3. The role of each class and method
4. The relationships between classes (friend declarations)
5. The purpose of each credential creation function
6. The separation between standard and experimental features
7. The underlying C objects being wrapped

The comments are concise but provide enough information for a developer to understand the purpose and usage of each component without needing to dive into implementation details.