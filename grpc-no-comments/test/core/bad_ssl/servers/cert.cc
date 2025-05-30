
// Copyright 2015 gRPC authors.

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/slice.h>

#include "absl/log/check.h"
#include "src/core/lib/iomgr/error.h"
#include "test/core/bad_ssl/server_common.h"
#include "test/core/test_util/tls_utils.h"

int main(int argc, char** argv) {
  const char* addr = bad_ssl_addr(argc, argv);
  grpc_ssl_pem_key_cert_pair pem_key_cert_pair;
  grpc_server_credentials* ssl_creds;
  grpc_server* server;

  grpc_init();

  std::string cert = grpc_core::testing::GetFileContents(
      "src/core/tsi/test_creds/badserver.pem");
  std::string key = grpc_core::testing::GetFileContents(
      "src/core/tsi/test_creds/badserver.key");
  pem_key_cert_pair.private_key = key.c_str();
  pem_key_cert_pair.cert_chain = cert.c_str();

  ssl_creds = grpc_ssl_server_credentials_create(nullptr, &pem_key_cert_pair, 1,
                                                 0, nullptr);
  server = grpc_server_create(nullptr, nullptr);
  CHECK(grpc_server_add_http2_port(server, addr, ssl_creds));
  grpc_server_credentials_release(ssl_creds);

  bad_ssl_run(server);
  grpc_shutdown();

  return 0;
}
