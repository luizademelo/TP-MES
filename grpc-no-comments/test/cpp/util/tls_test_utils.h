
// Copyright 2021 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_TLS_TEST_UTILS_H
#define GRPC_TEST_CPP_UTIL_TLS_TEST_UTILS_H

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/server_credentials.h>

#include <deque>

#include "src/core/util/thd.h"

namespace grpc {
namespace testing {

class SyncCertificateVerifier
    : public grpc::experimental::ExternalCertificateVerifier {
 public:
  explicit SyncCertificateVerifier(bool success) : success_(success) {}

  ~SyncCertificateVerifier() override {}

  bool Verify(grpc::experimental::TlsCustomVerificationCheckRequest* request,
              std::function<void(grpc::Status)> callback,
              grpc::Status* sync_status) override;

  void Cancel(grpc::experimental::TlsCustomVerificationCheckRequest*) override {
  }

 private:
  bool success_ = false;
};

class AsyncCertificateVerifier
    : public grpc::experimental::ExternalCertificateVerifier {
 public:
  explicit AsyncCertificateVerifier(bool success);

  ~AsyncCertificateVerifier() override;

  bool Verify(grpc::experimental::TlsCustomVerificationCheckRequest* request,
              std::function<void(grpc::Status)> callback,
              grpc::Status* sync_status) override;

  void Cancel(grpc::experimental::TlsCustomVerificationCheckRequest*) override {
  }

 private:

  struct Request {
    grpc::experimental::TlsCustomVerificationCheckRequest* request;
    std::function<void(grpc::Status)> callback;
    bool shutdown;
  };

  static void WorkerThread(void* arg);

  bool success_ = false;
  grpc_core::Thread thread_;
  grpc::internal::Mutex mu_;
  std::deque<Request> queue_ ABSL_GUARDED_BY(mu_);
};

class VerifiedRootCertSubjectVerifier
    : public grpc::experimental::ExternalCertificateVerifier {
 public:
  explicit VerifiedRootCertSubjectVerifier(absl::string_view expected_subject)
      : expected_subject_(expected_subject) {}

  ~VerifiedRootCertSubjectVerifier() override {}

  bool Verify(grpc::experimental::TlsCustomVerificationCheckRequest* request,
              std::function<void(grpc::Status)> callback,
              grpc::Status* sync_status) override;

  void Cancel(grpc::experimental::TlsCustomVerificationCheckRequest*) override {
  }

 private:
  std::string expected_subject_;
};

}
}

#endif
