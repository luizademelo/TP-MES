
// Copyright 2020 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_TLS_UTILS_H
#define GRPC_TEST_CORE_TEST_UTIL_TLS_UTILS_H

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/status.h>

#include <deque>
#include <string>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/tls/ssl_utils.h"
#include "src/core/util/sync.h"
#include "src/core/util/thd.h"

namespace grpc_core {

namespace testing {

class TmpFile {
 public:

  explicit TmpFile(absl::string_view data);

  ~TmpFile();

  const std::string& name() { return name_; }

  void RewriteFile(absl::string_view data);

 private:
  std::string CreateTmpFileAndWriteData(absl::string_view data);

  std::string name_;
};

PemKeyCertPairList MakeCertKeyPairs(absl::string_view private_key,
                                    absl::string_view certs);

std::string GetFileContents(const std::string& path);

class SyncExternalVerifier {
 public:
  explicit SyncExternalVerifier(bool success)
      : success_(success), base_{this, Verify, Cancel, Destruct} {}

  grpc_tls_certificate_verifier_external* base() { return &base_; }

 private:
  static int Verify(void* user_data,
                    grpc_tls_custom_verification_check_request* request,
                    grpc_tls_on_custom_verification_check_done_cb callback,
                    void* callback_arg, grpc_status_code* sync_status,
                    char** sync_error_details);

  static void Cancel(void*, grpc_tls_custom_verification_check_request*) {}

  static void Destruct(void* user_data);

  bool success_ = false;
  grpc_tls_certificate_verifier_external base_;
};

class AsyncExternalVerifier {
 public:
  explicit AsyncExternalVerifier(bool success)
      : success_(success),
        thread_("AsyncExternalVerifierWorkerThread", WorkerThread, this),
        base_{this, Verify, Cancel, Destruct} {
    grpc_init();
    thread_.Start();
  }

  ~AsyncExternalVerifier();

  grpc_tls_certificate_verifier_external* base() { return &base_; }

 private:

  struct Request {
    grpc_tls_custom_verification_check_request* request;
    grpc_tls_on_custom_verification_check_done_cb callback;
    void* callback_arg;
    bool shutdown;
  };

  static int Verify(void* user_data,
                    grpc_tls_custom_verification_check_request* request,
                    grpc_tls_on_custom_verification_check_done_cb callback,
                    void* callback_arg, grpc_status_code* sync_status,
                    char** sync_error_details);

  static void Cancel(void*, grpc_tls_custom_verification_check_request*) {}

  static void Destruct(void* user_data);

  static void WorkerThread(void* arg);

  bool success_ = false;
  Thread thread_;
  grpc_tls_certificate_verifier_external base_;
  Mutex mu_;
  std::deque<Request> queue_ ABSL_GUARDED_BY(mu_);
};

class PeerPropertyExternalVerifier {
 public:
  explicit PeerPropertyExternalVerifier(
      std::string expected_verified_root_cert_subject)
      : expected_verified_root_cert_subject_(
            std::move(expected_verified_root_cert_subject)),
        base_{this, Verify, Cancel, Destruct} {}

  grpc_tls_certificate_verifier_external* base() { return &base_; }

 private:
  static int Verify(void* user_data,
                    grpc_tls_custom_verification_check_request* request,
                    grpc_tls_on_custom_verification_check_done_cb callback,
                    void* callback_arg, grpc_status_code* sync_status,
                    char** sync_error_details);

  static void Cancel(void*, grpc_tls_custom_verification_check_request*) {}

  static void Destruct(void* user_data);

  std::string expected_verified_root_cert_subject_;
  grpc_tls_certificate_verifier_external base_;
};

}

}

#endif
