
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_GRPC_TLS_CERTIFICATE_VERIFIER_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_GRPC_TLS_CERTIFICATE_VERIFIER_H

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>

#include <functional>
#include <map>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/sync.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"

struct grpc_tls_certificate_verifier
    : public grpc_core::RefCounted<grpc_tls_certificate_verifier> {
 public:
  ~grpc_tls_certificate_verifier() override = default;

  virtual bool Verify(grpc_tls_custom_verification_check_request* request,
                      std::function<void(absl::Status)> callback,
                      absl::Status* sync_status) = 0;

  virtual void Cancel(grpc_tls_custom_verification_check_request* request) = 0;

  int Compare(const grpc_tls_certificate_verifier* other) const {
    CHECK_NE(other, nullptr);
    int r = type().Compare(other->type());
    if (r != 0) return r;
    return CompareImpl(other);
  }

  virtual grpc_core::UniqueTypeName type() const = 0;

 private:

  virtual int CompareImpl(const grpc_tls_certificate_verifier* other) const = 0;
};

namespace grpc_core {

class ExternalCertificateVerifier : public grpc_tls_certificate_verifier {
 public:
  explicit ExternalCertificateVerifier(
      grpc_tls_certificate_verifier_external* external_verifier)
      : external_verifier_(external_verifier) {}

  ~ExternalCertificateVerifier() override {
    if (external_verifier_->destruct != nullptr) {
      external_verifier_->destruct(external_verifier_->user_data);
    }
  }

  bool Verify(grpc_tls_custom_verification_check_request* request,
              std::function<void(absl::Status)> callback,
              absl::Status* sync_status) override;

  void Cancel(grpc_tls_custom_verification_check_request* request) override {
    external_verifier_->cancel(external_verifier_->user_data, request);
  }

  UniqueTypeName type() const override;

 private:
  int CompareImpl(const grpc_tls_certificate_verifier* other) const override {
    const auto* o = static_cast<const ExternalCertificateVerifier*>(other);
    return QsortCompare(external_verifier_, o->external_verifier_);
  }

  static void OnVerifyDone(grpc_tls_custom_verification_check_request* request,
                           void* callback_arg, grpc_status_code status,
                           const char* error_details);

  grpc_tls_certificate_verifier_external* external_verifier_;

  Mutex mu_;

  std::map<grpc_tls_custom_verification_check_request*,
           std::function<void(absl::Status)>>
      request_map_ ABSL_GUARDED_BY(mu_);
};

// Note: using this solely without any other authentication mechanisms on the

class NoOpCertificateVerifier : public grpc_tls_certificate_verifier {
 public:
  bool Verify(grpc_tls_custom_verification_check_request*,
              std::function<void(absl::Status)>, absl::Status*) override {
    return true;
  };
  void Cancel(grpc_tls_custom_verification_check_request*) override {}

  UniqueTypeName type() const override;

 private:
  int CompareImpl(
      const grpc_tls_certificate_verifier* ) const override {

    return 0;
  }
};

class HostNameCertificateVerifier : public grpc_tls_certificate_verifier {
 public:
  bool Verify(grpc_tls_custom_verification_check_request* request,
              std::function<void(absl::Status)> callback,
              absl::Status* sync_status) override;
  void Cancel(grpc_tls_custom_verification_check_request*) override {}

  UniqueTypeName type() const override;

 private:
  int CompareImpl(
      const grpc_tls_certificate_verifier* ) const override {

    return 0;
  }
};

}

#endif
