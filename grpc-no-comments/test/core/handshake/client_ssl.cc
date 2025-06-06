
// Copyright 2016 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/slice.h>
#include <grpc/support/time.h>
#include <netinet/in.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <stdint.h>
#include <stdio.h>

#include "absl/base/thread_annotations.h"
#include "absl/strings/str_format.h"
#include "gtest/gtest.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/port.h"
#include "test/core/test_util/test_config.h"

#ifdef GRPC_POSIX_SOCKET_TCP

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>

#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/util/crash.h"
#include "src/core/util/sync.h"
#include "src/core/util/thd.h"
#include "test/core/test_util/tls_utils.h"

#define SSL_CERT_PATH "src/core/tsi/test_creds/server1.pem"
#define SSL_KEY_PATH "src/core/tsi/test_creds/server1.key"
#define SSL_CA_PATH "src/core/tsi/test_creds/ca.pem"

class SslLibraryInfo {
 public:
  SslLibraryInfo() {}

  void Notify() {
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
  grpc_core::Mutex mu_;
  grpc_core::CondVar cv_;
  bool ready_ ABSL_GUARDED_BY(mu_) = false;
};

typedef struct {
  int socket;
  char* alpn_preferred;
  SslLibraryInfo* ssl_library_info;
} server_args;

static int create_socket(int* out_port) {
  int s;
  struct sockaddr_in addr;
  socklen_t addr_len;
  *out_port = -1;

  addr.sin_family = AF_INET;
  addr.sin_port = 0;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    perror("Unable to create socket");
    return -1;
  }

  if (bind(s, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
    perror("Unable to bind");
    LOG(ERROR) << "Unable to bind to any port";
    close(s);
    return -1;
  }

  if (listen(s, 1) < 0) {
    perror("Unable to listen");
    close(s);
    return -1;
  }

  addr_len = sizeof(addr);
  if (getsockname(s, reinterpret_cast<struct sockaddr*>(&addr), &addr_len) !=
          0 ||
      addr_len > sizeof(addr)) {
    perror("getsockname");
    LOG(ERROR) << "Unable to get socket local address";
    close(s);
    return -1;
  }

  *out_port = ntohs(addr.sin_port);
  return s;
}

static int alpn_select_cb(SSL* , const uint8_t** out, uint8_t* out_len,
                          const uint8_t* in, unsigned in_len, void* arg) {
  const uint8_t* alpn_preferred = static_cast<const uint8_t*>(arg);

  *out = alpn_preferred;
  *out_len = static_cast<uint8_t>(
      strlen(reinterpret_cast<const char*>(alpn_preferred)));

  bool h2_seen = false;
  const char* inp = reinterpret_cast<const char*>(in);
  const char* in_end = inp + in_len;
  while (inp < in_end) {
    const size_t length = static_cast<size_t>(*inp++);
    if (length == strlen("h2") && strncmp(inp, "h2", length) == 0) {
      h2_seen = true;
    }
    inp += length;
  }

  EXPECT_EQ(inp, in_end);
  EXPECT_TRUE(h2_seen);

  return SSL_TLSEXT_ERR_OK;
}

static void ssl_log_where_info(const SSL* ssl, int where, int flag,
                               const char* msg) {
  if ((where & flag) != 0) {
    GRPC_TRACE_LOG(tsi, INFO)
        << absl::StrFormat("%20.20s - %30.30s  - %5.10s", msg,
                           SSL_state_string_long(ssl), SSL_state_string(ssl));
  }
}

static void ssl_server_info_callback(const SSL* ssl, int where, int ret) {
  if (ret == 0) {
    LOG(ERROR) << "ssl_server_info_callback: error occurred.\n";
    return;
  }

  ssl_log_where_info(ssl, where, SSL_CB_LOOP, "Server: LOOP");
  ssl_log_where_info(ssl, where, SSL_CB_HANDSHAKE_START,
                     "Server: HANDSHAKE START");
  ssl_log_where_info(ssl, where, SSL_CB_HANDSHAKE_DONE,
                     "Server: HANDSHAKE DONE");
}

static void server_thread(void* arg) {
  const server_args* args = static_cast<server_args*>(arg);

  SSL_load_error_strings();
  OpenSSL_add_ssl_algorithms();
  args->ssl_library_info->Notify();

  const SSL_METHOD* method = TLSv1_2_server_method();
  SSL_CTX* ctx = SSL_CTX_new(method);
  if (!ctx) {
    perror("Unable to create SSL context");
    ERR_print_errors_fp(stderr);
    abort();
  }

  if (SSL_CTX_use_certificate_file(ctx, SSL_CERT_PATH, SSL_FILETYPE_PEM) < 0) {
    perror("Unable to use certificate file.");
    ERR_print_errors_fp(stderr);
    abort();
  }
  if (SSL_CTX_use_PrivateKey_file(ctx, SSL_KEY_PATH, SSL_FILETYPE_PEM) < 0) {
    perror("Unable to use private key file.");
    ERR_print_errors_fp(stderr);
    abort();
  }
  if (SSL_CTX_check_private_key(ctx) != 1) {
    perror("Check private key failed.");
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

  if (!SSL_CTX_set_ecdh_auto(ctx, 1)) {
    ERR_print_errors_fp(stderr);
    grpc_core::Crash("Couldn't set automatic curve selection.");
  }

  SSL_CTX_set_alpn_select_cb(ctx, alpn_select_cb, args->alpn_preferred);

  const int sock = args->socket;
  LOG(INFO) << "Server listening";
  struct sockaddr_in addr;
  socklen_t len = sizeof(addr);
  const int client =
      accept(sock, reinterpret_cast<struct sockaddr*>(&addr), &len);
  if (client < 0) {
    perror("Unable to accept");
    abort();
  }

  SSL* ssl = SSL_new(ctx);
  SSL_set_info_callback(ssl, ssl_server_info_callback);
  ASSERT_TRUE(ssl);
  SSL_set_fd(ssl, client);
  if (SSL_accept(ssl) <= 0) {
    ERR_print_errors_fp(stderr);
    LOG(ERROR) << "Handshake failed.";
  } else {
    LOG(INFO) << "Handshake successful.";
  }

  const char settings_frame[] = "\x00\x00\x00\x04\x00\x00\x00\x00\x00";
  SSL_write(ssl, settings_frame, sizeof(settings_frame) - 1);

  char buf;
  while (SSL_read(ssl, &buf, sizeof(buf)) > 0) {
  }

  SSL_free(ssl);
  close(client);
  close(sock);
  SSL_CTX_free(ctx);
}

static bool client_ssl_test(char* server_alpn_preferred) {
  bool success = true;

  grpc_init();

  int port = -1;
  int server_socket = -1;
  int socket_retries = 30;
  while (server_socket == -1 && socket_retries-- > 0) {
    server_socket = create_socket(&port);
    if (server_socket == -1) {
      sleep(1);
    }
  }
  EXPECT_GT(server_socket, 0);
  EXPECT_GT(port, 0);

  SslLibraryInfo ssl_library_info;
  server_args args = {server_socket, server_alpn_preferred, &ssl_library_info};
  bool ok;
  grpc_core::Thread thd("grpc_client_ssl_test", server_thread, &args, &ok);
  EXPECT_TRUE(ok);
  thd.Start();
  ssl_library_info.Await();

  std::string ca_cert = grpc_core::testing::GetFileContents(SSL_CA_PATH);
  std::string cert = grpc_core::testing::GetFileContents(SSL_CERT_PATH);
  std::string key = grpc_core::testing::GetFileContents(SSL_KEY_PATH);

  grpc_ssl_pem_key_cert_pair pem_key_cert_pair;
  pem_key_cert_pair.private_key = key.c_str();
  pem_key_cert_pair.cert_chain = cert.c_str();
  grpc_channel_credentials* ssl_creds = grpc_ssl_credentials_create(
      ca_cert.c_str(), &pem_key_cert_pair, nullptr, nullptr);

  std::string target = absl::StrCat("127.0.0.1:", port);
  grpc_arg ssl_name_override = {
      GRPC_ARG_STRING,
      const_cast<char*>(GRPC_SSL_TARGET_NAME_OVERRIDE_ARG),
      {const_cast<char*>("foo.test.google.fr")}};
  grpc_channel_args grpc_args;
  grpc_args.num_args = 1;
  grpc_args.args = &ssl_name_override;
  grpc_channel* channel =
      grpc_channel_create(target.c_str(), ssl_creds, &grpc_args);
  EXPECT_TRUE(channel);

  EXPECT_EQ(
      grpc_channel_check_connectivity_state(channel, 1 ),
      GRPC_CHANNEL_IDLE);

  int retries = 10;
  grpc_connectivity_state state = GRPC_CHANNEL_IDLE;
  grpc_completion_queue* cq = grpc_completion_queue_create_for_next(nullptr);

  while (state != GRPC_CHANNEL_READY && retries-- > 0) {
    grpc_channel_watch_connectivity_state(
        channel, state, grpc_timeout_seconds_to_deadline(3), cq, nullptr);
    gpr_timespec cq_deadline = grpc_timeout_seconds_to_deadline(5);
    grpc_event ev = grpc_completion_queue_next(cq, cq_deadline, nullptr);
    EXPECT_EQ(ev.type, GRPC_OP_COMPLETE);
    state =
        grpc_channel_check_connectivity_state(channel, 0 );
  }
  grpc_completion_queue_destroy(cq);
  if (retries < 0) {
    success = false;
  }

  grpc_channel_destroy(channel);
  grpc_channel_credentials_release(ssl_creds);

  thd.Join();

  grpc_shutdown();

  return success;
}

TEST(ClientSslTest, MainTest) {

  ASSERT_TRUE(client_ssl_test(const_cast<char*>("h2")));

#ifdef OPENSSL_IS_BORING_SSL

  ASSERT_FALSE(client_ssl_test(const_cast<char*>("foo")));
#endif

  EVP_cleanup();
}

#endif

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
