
// Copyright 2016 gRPC authors.

#include "test/core/handshake/server_ssl_common.h"

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <netinet/in.h>
#include <openssl/crypto.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/crash.h"
#include "src/core/util/sync.h"
#include "src/core/util/thd.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/core/test_util/tls_utils.h"

#define SSL_CERT_PATH "src/core/tsi/test_creds/server1.pem"
#define SSL_KEY_PATH "src/core/tsi/test_creds/server1.key"
#define SSL_CA_PATH "src/core/tsi/test_creds/ca.pem"

namespace {

gpr_event client_handshake_complete;

int create_socket(int port) {
  int s;
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(static_cast<uint16_t>(port));
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    perror("Unable to create socket");
    return -1;
  }

  if (connect(s, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
    perror("Unable to connect");
    return -1;
  }

  return s;
}

class ServerInfo {
 public:
  explicit ServerInfo(int p) : port_(p) {}

  int port() const { return port_; }

  void Activate() {
    grpc_core::MutexLock lock(&mu_);
    ready_ = true;
    cv_.Signal();
  }

  void Await() {
    grpc_core::MutexLock lock(&mu_);
    while (!ready_) {
      cv_.Wait(&mu_);
    }
  }

 private:
  const int port_;
  grpc_core::Mutex mu_;
  grpc_core::CondVar cv_;
  bool ready_ ABSL_GUARDED_BY(mu_) = false;
};

void server_thread(void* arg) {
  ServerInfo* s = static_cast<ServerInfo*>(arg);
  const int port = s->port();

  std::string ca_cert = grpc_core::testing::GetFileContents(SSL_CA_PATH);
  std::string cert = grpc_core::testing::GetFileContents(SSL_CERT_PATH);
  std::string key = grpc_core::testing::GetFileContents(SSL_KEY_PATH);

  grpc_ssl_pem_key_cert_pair pem_key_cert_pair;
  pem_key_cert_pair.private_key = key.c_str();
  pem_key_cert_pair.cert_chain = cert.c_str();
  grpc_server_credentials* ssl_creds = grpc_ssl_server_credentials_create(
      ca_cert.c_str(), &pem_key_cert_pair, 1, 0, nullptr);

  std::string addr = absl::StrCat("127.0.0.1:", port);
  grpc_server* server = grpc_server_create(nullptr, nullptr);
  CHECK(grpc_server_add_http2_port(server, addr.c_str(), ssl_creds));

  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);

  grpc_server_register_completion_queue(server, cq, nullptr);
  grpc_server_start(server);

  s->Activate();

  int retries = 10;
  while (!gpr_event_get(&client_handshake_complete) && retries-- > 0) {
    const gpr_timespec cq_deadline = grpc_timeout_seconds_to_deadline(1);
    grpc_event ev = grpc_completion_queue_next(cq, cq_deadline, nullptr);
    CHECK(ev.type == GRPC_QUEUE_TIMEOUT);
  }

  LOG(INFO) << "Shutting down server";
  grpc_server_shutdown_and_notify(server, cq, nullptr);
  grpc_completion_queue_shutdown(cq);

  const gpr_timespec cq_deadline = grpc_timeout_seconds_to_deadline(5);
  grpc_event ev = grpc_completion_queue_next(cq, cq_deadline, nullptr);
  CHECK(ev.type == GRPC_OP_COMPLETE);

  grpc_server_destroy(server);
  grpc_completion_queue_destroy(cq);
  grpc_server_credentials_release(ssl_creds);
}

}

bool server_ssl_test(const char* alpn_list[], unsigned int alpn_list_len,
                     const char* alpn_expected) {
  bool success = true;

  grpc_init();
  ServerInfo s(grpc_pick_unused_port_or_die());
  gpr_event_init(&client_handshake_complete);

  bool ok;
  grpc_core::Thread thd("grpc_ssl_test", server_thread, &s, &ok);
  CHECK(ok);
  thd.Start();

  s.Await();

  const SSL_METHOD* method = TLSv1_2_client_method();
  SSL_CTX* ctx = SSL_CTX_new(method);
  if (!ctx) {
    perror("Unable to create SSL context");
    ERR_print_errors_fp(stderr);
    abort();
  }

  if (SSL_CTX_use_certificate_file(ctx, SSL_CERT_PATH, SSL_FILETYPE_PEM) < 0) {
    ERR_print_errors_fp(stderr);
    abort();
  }
  if (SSL_CTX_use_PrivateKey_file(ctx, SSL_KEY_PATH, SSL_FILETYPE_PEM) < 0) {
    ERR_print_errors_fp(stderr);
    abort();
  }

  const char* cipher_list =
      "ECDHE-RSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-SHA256:ECDHE-RSA-AES256-"
      "SHA384:ECDHE-RSA-AES256-GCM-SHA384";
  if (!SSL_CTX_set_cipher_list(ctx, cipher_list)) {
    ERR_print_errors_fp(stderr);
    grpc_core::Crash("Couldn't set server cipher list.");
  }

  unsigned int alpn_protos_len = alpn_list_len;
  for (unsigned int i = 0; i < alpn_list_len; ++i) {
    alpn_protos_len += static_cast<unsigned int>(strlen(alpn_list[i]));
  }
  unsigned char* alpn_protos =
      static_cast<unsigned char*>(gpr_malloc(alpn_protos_len));
  unsigned char* p = alpn_protos;
  for (unsigned int i = 0; i < alpn_list_len; ++i) {
    const uint8_t len = static_cast<uint8_t>(strlen(alpn_list[i]));
    *p++ = len;
    memcpy(p, alpn_list[i], len);
    p += len;
  }
  CHECK_EQ(SSL_CTX_set_alpn_protos(ctx, alpn_protos, alpn_protos_len), 0);

  int retries = 10;
  int sock = -1;
  while (sock == -1 && retries-- > 0) {
    sock = create_socket(s.port());
    if (sock < 0) {
      sleep(1);
    }
  }
  CHECK_GT(sock, 0);
  LOG(INFO) << "Connected to server on port " << s.port();

  SSL* ssl = SSL_new(ctx);
  CHECK(ssl);
  SSL_set_fd(ssl, sock);
  if (SSL_connect(ssl) <= 0) {
    ERR_print_errors_fp(stderr);
    LOG(ERROR) << "Handshake failed.";
    success = false;
  } else {
    LOG(INFO) << "Handshake successful.";

    const unsigned char* alpn_selected;
    unsigned int alpn_selected_len;
    SSL_get0_alpn_selected(ssl, &alpn_selected, &alpn_selected_len);
    if (strlen(alpn_expected) != alpn_selected_len ||
        strncmp(reinterpret_cast<const char*>(alpn_selected), alpn_expected,
                alpn_selected_len) != 0) {
      LOG(ERROR) << "Unexpected ALPN protocol preference";
      success = false;
    }
  }
  gpr_event_set(&client_handshake_complete, &client_handshake_complete);

  SSL_free(ssl);
  gpr_free(alpn_protos);
  SSL_CTX_free(ctx);
  close(sock);

  thd.Join();

  grpc_shutdown();

  return success;
}

void CleanupSslLibrary() { EVP_cleanup(); }
