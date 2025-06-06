
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/alpn/alpn.h"

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/slice.h>
#include <string.h>

#include "absl/log/check.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/useful.h"
#include "test/core/bad_ssl/server_common.h"
#include "test/core/test_util/tls_utils.h"

#define CA_CERT_PATH "src/core/tsi/test_creds/ca.pem"
#define SERVER_CERT_PATH "src/core/tsi/test_creds/server1.pem"
#define SERVER_KEY_PATH "src/core/tsi/test_creds/server1.key"

static const char* const fake_versions[] = {"not-h2"};

int grpc_chttp2_is_alpn_version_supported(const char* version, size_t size) {
  size_t i;
  for (i = 0; i < GPR_ARRAY_SIZE(fake_versions); i++) {
    if (!strncmp(version, fake_versions[i], size)) return 1;
  }
  return 0;
}

size_t grpc_chttp2_num_alpn_versions(void) {
  return GPR_ARRAY_SIZE(fake_versions);
}

const char* grpc_chttp2_get_alpn_version_index(size_t i) {
  CHECK(i < GPR_ARRAY_SIZE(fake_versions));
  return fake_versions[i];
}

int main(int argc, char** argv) {
  const char* addr = bad_ssl_addr(argc, argv);
  std::string server_cert =
      grpc_core::testing::GetFileContents(SERVER_CERT_PATH);
  std::string server_key = grpc_core::testing::GetFileContents(SERVER_KEY_PATH);
  grpc_ssl_pem_key_cert_pair pem_key_cert_pair = {server_key.c_str(),
                                                  server_cert.c_str()};
  grpc_server_credentials* ssl_creds;
  grpc_server* server;

  grpc_init();
  ssl_creds = grpc_ssl_server_credentials_create(nullptr, &pem_key_cert_pair, 1,
                                                 0, nullptr);
  server = grpc_server_create(nullptr, nullptr);
  CHECK(grpc_server_add_http2_port(server, addr, ssl_creds));
  grpc_server_credentials_release(ssl_creds);

  bad_ssl_run(server);
  grpc_shutdown();

  return 0;
}
