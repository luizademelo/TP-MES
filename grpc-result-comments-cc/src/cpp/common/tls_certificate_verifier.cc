Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/status.h>
#include <grpc/support/alloc.h>
#include <grpc/support/string_util.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/security/tls_certificate_verifier.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/string_ref.h>
#include <stddef.h>

#include <algorithm>
#include <functional>
#include <map>
#include <utility>
#include <vector>

#include "absl/log/check.h"

namespace grpc {
namespace experimental {

// Wrapper class for grpc_tls_custom_verification_check_request
TlsCustomVerificationCheckRequest::TlsCustomVerificationCheckRequest(
    grpc_tls_custom_verification_check_request* request)
    : c_request_(request) {
  CHECK_NE(c_request_, nullptr);
}

// Returns the target name from the verification request
grpc::string_ref TlsCustomVerificationCheckRequest::target_name() const {
  return c_request_->target_name != nullptr ? c_request_->target_name : "";
}

// Returns the peer certificate from the verification request
grpc::string_ref TlsCustomVerificationCheckRequest::peer_cert() const {
  return c_request_->peer_info.peer_cert != nullptr
             ? c_request_->peer_info.peer_cert
             : "";
}

// Returns the full certificate chain from the verification request
grpc::string_ref TlsCustomVerificationCheckRequest::peer_cert_full_chain()
    const {
  return c_request_->peer_info.peer_cert_full_chain != nullptr
             ? c_request_->peer_info.peer_cert_full_chain
             : "";
}

// Returns the common name from the verification request
grpc::string_ref TlsCustomVerificationCheckRequest::common_name() const {
  return c_request_->peer_info.common_name != nullptr
             ? c_request_->peer_info.common_name
             : "";
}

// Returns the verified root certificate subject from the verification request
grpc::string_ref TlsCustomVerificationCheckRequest::verified_root_cert_subject()
    const {
  return c_request_->peer_info.verified_root_cert_subject != nullptr
             ? c_request_->peer_info.verified_root_cert_subject
             : "";
}

// Returns the URI SANs (Subject Alternative Names) from the verification request
std::vector<grpc::string_ref> TlsCustomVerificationCheckRequest::uri_names()
    const {
  std::vector<grpc::string_ref> uri_names;
  for (size_t i = 0; i < c_request_->peer_info.san_names.uri_names_size; ++i) {
    uri_names.emplace_back(c_request_->peer_info.san_names.uri_names[i]);
  }
  return uri_names;
}

// Returns the DNS SANs (Subject Alternative Names) from the verification request
std::vector<grpc::string_ref> TlsCustomVerificationCheckRequest::dns_names()
    const {
  std::vector<grpc::string_ref> dns_names;
  for (size_t i = 0; i < c_request_->peer_info.san_names.dns_names_size; ++i) {
    dns_names.emplace_back(c_request_->peer_info.san_names.dns_names[i]);
  }
  return dns_names;
}

// Returns the email SANs (Subject Alternative Names) from the verification request
std::vector<grpc::string_ref> TlsCustomVerificationCheckRequest::email_names()
    const {
  std::vector<grpc::string_ref> email_names;
  for (size_t i = 0; i < c_request_->peer_info.san_names.email_names_size;
       ++i) {
    email_names.emplace_back(c_request_->peer_info.san_names.email_names[i]);
  }
  return email_names;
}

// Returns the IP SANs (Subject Alternative Names) from the verification request
std::vector<grpc::string_ref> TlsCustomVerificationCheckRequest::ip_names()
    const {
  std::vector<grpc::string_ref> ip_names;
  for (size_t i = 0; i < c_request_->peer_info.san_names.ip_names_size; ++i) {
    ip_names.emplace_back(c_request_->peer_info.san_names.ip_names[i]);
  }
  return ip_names;
}

// Constructor for CertificateVerifier that takes a grpc_tls_certificate_verifier
CertificateVerifier::CertificateVerifier(grpc_tls_certificate_verifier* v)
    : verifier_(v) {}

// Destructor for CertificateVerifier that releases the underlying verifier
CertificateVerifier::~CertificateVerifier() {
  grpc_tls_certificate_verifier_release(verifier_);
}

// Performs certificate verification either synchronously or asynchronously
bool CertificateVerifier::Verify(TlsCustomVerificationCheckRequest* request,
                                 std::function<void(grpc::Status)> callback,
                                 grpc::Status* sync_status) {
  CHECK_NE(request, nullptr);
  CHECK_NE(request->c_request(), nullptr);
  {
    internal::MutexLock lock(&mu_);
    request_map_.emplace(request->c_request(), std::move(callback));
  }
  grpc_status_code status_code = GRPC_STATUS_OK;
  char* error_details = nullptr;
  bool is_done = grpc_tls_certificate_verifier_verify(
      verifier_, request->c_request(), &AsyncCheckDone, this, &status_code,
      &error_details);
  if (is_done) {
    if (status_code != GRPC_STATUS_OK) {
      *sync_status = grpc::Status(static_cast<grpc::StatusCode>(status_code),
                                  error_details);
    }
    internal::MutexLock lock(&mu_);
    request_map_.erase(request->c_request());
  }
  gpr_free(error_details);
  return is_done;
}

// Cancels an ongoing verification request
void CertificateVerifier::Cancel(TlsCustomVerificationCheckRequest* request) {
  CHECK_NE(request, nullptr);
  CHECK_NE(request->c_request(), nullptr);
  grpc_tls_certificate_verifier_cancel(verifier_, request->c_request());
}

// Callback function invoked when async verification is complete
void CertificateVerifier::AsyncCheckDone(
    grpc_tls_custom_verification_check_request* request, void* callback_arg,
    grpc_status_code status, const char* error_details) {
  auto* self = static_cast<CertificateVerifier*>(callback_arg);
  std::function<void(grpc::Status)> callback;
  {
    internal::MutexLock lock(&self->mu_);
    auto it = self->request_map_.find(request);
    if (it != self->request_map_.end()) {
      callback = std::move(it->second);
      self->request_map_.erase(it);
    }
  }
  if (callback != nullptr) {
    grpc::Status return_status;
    if (status != GRPC_STATUS_OK) {
      return_status =
          grpc::Status(static_cast<grpc::StatusCode>(status), error_details);
    }
    callback(return_status);
  }
}

// Constructor for ExternalCertificateVerifier that sets up callbacks
ExternalCertificateVerifier::ExternalCertificateVerifier() {
  base_ = new grpc_tls_certificate_verifier_external();
  base_->user_data = this;
  base_->verify = VerifyInCoreExternalVerifier;
  base_->cancel = CancelInCoreExternalVerifier;
  base_->destruct = DestructInCoreExternalVerifier;
}

// Destructor for ExternalCertificateVerifier
ExternalCertificateVerifier::~ExternalCertificateVerifier() { delete base_; }

// Core verification function for external verifier
int ExternalCertificateVerifier::VerifyInCoreExternalVerifier(
    void* user_data, grpc_tls_custom_verification_check_request* request,
    grpc_tls_on_custom_verification_check_done_cb callback, void* callback_arg,
    grpc_status_code* sync_status, char** sync_error_details) {
  auto* self = static_cast<ExternalCertificateVerifier*>(user_data);
  TlsCustomVerificationCheckRequest* cpp_request = nullptr;
  {
    internal::MutexLock lock(&self->mu_);
    auto pair = self->request_map_.emplace(
        request, AsyncRequestState(callback, callback_arg, request));
    CHECK(pair.second);
    cpp_request = &pair.first->second.cpp_request;
  }
  grpc::Status sync_current_verifier_status;
  bool is_done = self->Verify(
      cpp_request,
      [self, request](grpc::Status status) {
        grpc_tls_on_custom_verification_check_done_cb callback = nullptr;
        void* callback_arg = nullptr;
        {
          internal::MutexLock lock(&self->mu_);
          auto it = self->request_map_.find(request);
          if (it != self->request_map_.end()) {
            callback = it->second.callback;
            callback_arg = it->second.callback_arg;
            self->request_map_.erase(it);
          }
        }
        if (callback != nullptr) {
          callback(request, callback_arg,
                   static_cast<grpc_status_code>(status.error_code()),
                   status.error_message().c_str());
        }
      },
      &sync_current_verifier_status);
  if (is_done) {
    if (!sync_current_verifier_status.ok()) {
      *sync_status = static_cast<grpc_status_code>(
          sync_current_verifier_status.error_code());
      *sync_error_details =
          gpr_strdup(sync_current_verifier_status.error_message().c_str());
    }
    internal::MutexLock lock(&self->mu_);
    self->request_map_.erase(request);
  }
  return is_done;
}

// Core cancellation function for external verifier
void ExternalCertificateVerifier::CancelInCoreExternalVerifier(
    void* user_data, grpc_tls_custom_verification_check_request* request) {
  auto* self = static_cast<ExternalCertificateVerifier*>(user_data);
  TlsCustomVerificationCheckRequest* cpp_request = nullptr;
  {
    internal::MutexLock lock(&self->mu_);
    auto it = self->request_map_.find(request);
    if (it != self->request_map_.end()) {
      cpp_request = &it->second.cpp_request;
    }
  }
  if (cpp_request != nullptr) {
    self->Cancel(cpp_request);
  }
}

// Core destructor function for external verifier
void ExternalCertificateVerifier::DestructInCoreExternalVerifier(
    void* user_data) {
  auto* self = static_cast<ExternalCertificateVerifier*>(user_data);
  delete self;
}

// Creates a no-op certificate verifier that always succeeds
NoOpCertificateVerifier::NoOpCertificateVerifier()
    : CertificateVerifier(grpc_tls_certificate_verifier_no_op_create()) {}

// Creates a hostname certificate verifier that verifies hostnames
HostNameCertificateVerifier::HostNameCertificateVerifier()
    : CertificateVerifier(grpc_tls_certificate_verifier_host_name_create()) {}

}
}
```