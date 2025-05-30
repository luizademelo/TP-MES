
// Copyright 2021 gRPC authors.

#ifndef GRPCPP_SECURITY_TLS_CERTIFICATE_VERIFIER_H
#define GRPCPP_SECURITY_TLS_CERTIFICATE_VERIFIER_H

#include <grpc/grpc_security_constants.h>
#include <grpc/status.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/string_ref.h>

#include <functional>
#include <map>
#include <memory>
#include <utility>
#include <vector>

typedef struct grpc_tls_custom_verification_check_request
    grpc_tls_custom_verification_check_request;
typedef struct grpc_tls_certificate_verifier grpc_tls_certificate_verifier;
typedef struct grpc_tls_certificate_verifier_external
    grpc_tls_certificate_verifier_external;
typedef void (*grpc_tls_on_custom_verification_check_done_cb)(
    grpc_tls_custom_verification_check_request* request, void* callback_arg,
    grpc_status_code status, const char* error_details);
extern "C" grpc_tls_certificate_verifier*
grpc_tls_certificate_verifier_external_create(
    grpc_tls_certificate_verifier_external* external_verifier);

namespace grpc {
namespace experimental {

class TlsCustomVerificationCheckRequest {
 public:
  explicit TlsCustomVerificationCheckRequest(
      grpc_tls_custom_verification_check_request* request);
  ~TlsCustomVerificationCheckRequest() {}

  grpc::string_ref target_name() const;
  grpc::string_ref peer_cert() const;
  grpc::string_ref peer_cert_full_chain() const;
  grpc::string_ref common_name() const;

  grpc::string_ref verified_root_cert_subject() const;
  std::vector<grpc::string_ref> uri_names() const;
  std::vector<grpc::string_ref> dns_names() const;
  std::vector<grpc::string_ref> email_names() const;
  std::vector<grpc::string_ref> ip_names() const;

  grpc_tls_custom_verification_check_request* c_request() { return c_request_; }

 private:
  grpc_tls_custom_verification_check_request* c_request_ = nullptr;
};

class CertificateVerifier {
 public:
  explicit CertificateVerifier(grpc_tls_certificate_verifier* v);

  ~CertificateVerifier();

  bool Verify(TlsCustomVerificationCheckRequest* request,
              std::function<void(grpc::Status)> callback,
              grpc::Status* sync_status);

  void Cancel(TlsCustomVerificationCheckRequest* request);

  grpc_tls_certificate_verifier* c_verifier() { return verifier_; }

 private:
  static void AsyncCheckDone(
      grpc_tls_custom_verification_check_request* request, void* callback_arg,
      grpc_status_code status, const char* error_details);

  grpc_tls_certificate_verifier* verifier_ = nullptr;
  grpc::internal::Mutex mu_;
  std::map<grpc_tls_custom_verification_check_request*,
           std::function<void(grpc::Status)>>
      request_map_ ABSL_GUARDED_BY(mu_);
};

class ExternalCertificateVerifier {
 public:

  template <typename Subclass, typename... Args>
  static std::shared_ptr<CertificateVerifier> Create(Args&&... args) {
    auto* external_verifier = new Subclass(std::forward<Args>(args)...);
    return std::make_shared<CertificateVerifier>(
        grpc_tls_certificate_verifier_external_create(
            external_verifier->base_));
  }

  virtual bool Verify(TlsCustomVerificationCheckRequest* request,
                      std::function<void(grpc::Status)> callback,
                      grpc::Status* sync_status) = 0;

  virtual void Cancel(TlsCustomVerificationCheckRequest* request) = 0;

 protected:
  ExternalCertificateVerifier();

  virtual ~ExternalCertificateVerifier();

 private:
  struct AsyncRequestState {
    AsyncRequestState(grpc_tls_on_custom_verification_check_done_cb cb,
                      void* arg,
                      grpc_tls_custom_verification_check_request* request)
        : callback(cb), callback_arg(arg), cpp_request(request) {}

    grpc_tls_on_custom_verification_check_done_cb callback;
    void* callback_arg;
    TlsCustomVerificationCheckRequest cpp_request;
  };

  static int VerifyInCoreExternalVerifier(
      void* user_data, grpc_tls_custom_verification_check_request* request,
      grpc_tls_on_custom_verification_check_done_cb callback,
      void* callback_arg, grpc_status_code* sync_status,
      char** sync_error_details);

  static void CancelInCoreExternalVerifier(
      void* user_data, grpc_tls_custom_verification_check_request* request);

  static void DestructInCoreExternalVerifier(void* user_data);

  grpc_tls_certificate_verifier_external* base_ = nullptr;
  grpc::internal::Mutex mu_;
  std::map<grpc_tls_custom_verification_check_request*, AsyncRequestState>
      request_map_ ABSL_GUARDED_BY(mu_);
};

// Note: using this solely without any other authentication mechanisms on the

class NoOpCertificateVerifier : public CertificateVerifier {
 public:
  NoOpCertificateVerifier();
};

class HostNameCertificateVerifier : public CertificateVerifier {
 public:
  HostNameCertificateVerifier();
};

}
}

#endif
