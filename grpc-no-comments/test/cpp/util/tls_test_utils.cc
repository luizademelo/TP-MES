
// Copyright 2021 gRPC authors.

#include "test/cpp/util/tls_test_utils.h"

#include <memory>

#include "src/core/util/thd.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"

using ::grpc::experimental::TlsCustomVerificationCheckRequest;

namespace grpc {
namespace testing {

bool SyncCertificateVerifier::Verify(TlsCustomVerificationCheckRequest*,
                                     std::function<void(grpc::Status)>,
                                     grpc::Status* sync_status) {
  if (!success_) {
    *sync_status = grpc::Status(grpc::StatusCode::UNAUTHENTICATED,
                                "SyncCertificateVerifier failed");
  } else {
    *sync_status = grpc::Status(grpc::StatusCode::OK, "");
  }
  return true;
}

AsyncCertificateVerifier::AsyncCertificateVerifier(bool success)
    : success_(success),
      thread_("AsyncCertificateVerifierWorkerThread", WorkerThread, this) {
  thread_.Start();
}

AsyncCertificateVerifier::~AsyncCertificateVerifier() {

  {
    internal::MutexLock lock(&mu_);
    queue_.push_back(Request{nullptr, nullptr, true});
  }

  thread_.Join();
}

bool AsyncCertificateVerifier::Verify(
    TlsCustomVerificationCheckRequest* request,
    std::function<void(grpc::Status)> callback, grpc::Status*) {
  internal::MutexLock lock(&mu_);
  queue_.push_back(Request{request, std::move(callback), false});
  return false;
}

void AsyncCertificateVerifier::WorkerThread(void* arg) {
  auto* self = static_cast<AsyncCertificateVerifier*>(arg);
  while (true) {

    bool got_request = false;
    Request request;
    {
      internal::MutexLock lock(&self->mu_);
      if (!self->queue_.empty()) {
        got_request = true;
        request = self->queue_.front();
        self->queue_.pop_front();
      }
    }

    if (!got_request) {
      gpr_sleep_until(grpc_timeout_milliseconds_to_deadline(100));
      continue;
    }

    if (request.shutdown) return;
    auto return_status = grpc::Status(grpc::StatusCode::OK, "");

    if (!self->success_) {
      return_status = grpc::Status(grpc::StatusCode::UNAUTHENTICATED,
                                   "AsyncCertificateVerifier failed");
    }
    request.callback(return_status);
  }
}

bool VerifiedRootCertSubjectVerifier::Verify(
    TlsCustomVerificationCheckRequest* request,
    std::function<void(grpc::Status)>, grpc::Status* sync_status) {
  if (request->verified_root_cert_subject() != expected_subject_) {
    *sync_status = grpc::Status(grpc::StatusCode::UNAUTHENTICATED,
                                "VerifiedRootCertSubjectVerifier failed");
  } else {
    *sync_status = grpc::Status::OK;
  }
  return true;
}

}
}
