
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SECURITY_SERVER_CREDENTIALS_H
#define GRPCPP_SECURITY_SERVER_CREDENTIALS_H

#include <grpc/grpc_security_constants.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/security/auth_metadata_processor.h>
#include <grpcpp/security/tls_credentials_options.h>
#include <grpcpp/support/config.h>

#include <memory>
#include <vector>

struct grpc_server;

namespace grpc {

class Server;
class ServerCredentials;

struct SslServerCredentialsOptions {

  SslServerCredentialsOptions()
      : force_client_auth(false),
        client_certificate_request(GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE) {}
  explicit SslServerCredentialsOptions(
      grpc_ssl_client_certificate_request_type request_type)
      : force_client_auth(false), client_certificate_request(request_type) {}

  struct PemKeyCertPair {
    std::string private_key;
    std::string cert_chain;
  };
  std::string pem_root_certs;
  std::vector<PemKeyCertPair> pem_key_cert_pairs;

  bool force_client_auth;

  grpc_ssl_client_certificate_request_type client_certificate_request;
};

std::shared_ptr<ServerCredentials> XdsServerCredentials(
    const std::shared_ptr<ServerCredentials>& fallback_credentials);

class ServerCredentials : private grpc::internal::GrpcLibrary {
 public:
  ~ServerCredentials() override;

  virtual void SetAuthMetadataProcessor(
      const std::shared_ptr<grpc::AuthMetadataProcessor>& processor);

 protected:
  explicit ServerCredentials(grpc_server_credentials* creds);

  grpc_server_credentials* c_creds() const { return c_creds_; }

 private:

  friend class Server;

  friend class ServerBuilder;
  friend std::shared_ptr<ServerCredentials> grpc::XdsServerCredentials(
      const std::shared_ptr<ServerCredentials>& fallback_credentials);

  virtual int AddPortToServer(const std::string& addr, grpc_server* server);

  grpc_server_credentials* c_creds_;
};

std::shared_ptr<ServerCredentials> SslServerCredentials(
    const grpc::SslServerCredentialsOptions& options);

std::shared_ptr<ServerCredentials> InsecureServerCredentials();

namespace experimental {

struct AltsServerCredentialsOptions {

};

std::shared_ptr<ServerCredentials> AltsServerCredentials(
    const AltsServerCredentialsOptions& options);

std::shared_ptr<ServerCredentials> LocalServerCredentials(
    grpc_local_connect_type type);

std::shared_ptr<ServerCredentials> TlsServerCredentials(
    const experimental::TlsServerCredentialsOptions& options);

}
}

#endif
