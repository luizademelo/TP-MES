Here's the commented version of the code:

```c++
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

// Forward declarations of C-style structs used in the interface
typedef struct grpc_tls_custom_verification_check_request
    grpc_tls_custom_verification_check_request;
typedef struct grpc_tls_certificate_verifier grpc_tls_certificate_verifier;
typedef struct grpc_tls_certificate_verifier_external
    grpc_tls_certificate_verifier_external;

// Callback type for asynchronous verification completion
typedef void (*grpc_tls_on_custom_verification_check_done_cb)(
    grpc_tls_custom_verification_check_request* request, void* callback_arg,
    grpc_status_code status, const char* error_details);

// C function to create an external certificate verifier
extern "C" grpc_tls_certificate_verifier*
grpc_tls_certificate_verifier_external_create(
    grpc_tls_certificate_verifier_external* external_verifier);

namespace grpc {
namespace experimental {

// Wrapper class for TLS custom verification check requests
class TlsCustomVerificationCheckRequest {
 public:
  // Construct from a C-style request object
  explicit TlsCustomVerificationCheckRequest(
      grpc_tls_custom_verification_check_request* request);
  ~TlsCustomVerificationCheckRequest() {}

  // Accessors for various certificate properties
  grpc::string_ref target_name() const;
  grpc::string_ref peer_cert() const;
  grpc::string_ref peer_cert_full_chain() const;
  grpc::string_ref common_name() const;

  grpc::string_ref verified_root_cert_subject() const;
  std::vector<grpc::string_ref> uri_names() const;
  std::vector<grpc::string_ref> dns_names() const;
  std::vector<grpc::string_ref> email_names() const;
  std::vector<grpc::string_ref> ip_names() const;

  // Returns the underlying C request object
  grpc_tls_custom_verification_check_request* c_request() { return c_request_; }

 private:
  grpc_tls_custom_verification_check_request* c_request_ = nullptr;
};

// Base class for certificate verifiers
class CertificateVerifier {
 public:
  // Construct from a C-style verifier
  explicit CertificateVerifier(grpc_tls_certificate_verifier* v);
  ~CertificateVerifier();

  // Verify a certificate request asynchronously
  // Returns true if verification completed synchronously (sync_status contains result)
  // Returns false if verification is asynchronous (callback will be called later)
  bool Verify(TlsCustomVerificationCheckRequest* request,
              std::function<void(grpc::Status)> callback,
              grpc::Status* sync_status);

  // Cancel an ongoing verification request
  void Cancel(TlsCustomVerificationCheckRequest* request);

  // Returns the underlying C verifier object
  grpc_tls_certificate_verifier* c_verifier() { return verifier_; }

 private:
  // Callback for when async verification completes
  static void AsyncCheckDone(
      grpc_tls_custom_verification_check_request* request, void* callback_arg,
      grpc_status_code status, const char* error_details);

  grpc_tls_certificate_verifier* verifier_ = nullptr;
  grpc::internal::Mutex mu_;
  // Map of active verification requests to their callbacks
  std::map<grpc_tls_custom_verification_check_request*,
           std::function<void(grpc::Status)>>
      request_map_ ABSL_GUARDED_BY(mu_);
};

// Base class for external certificate verifiers
class ExternalCertificateVerifier {
 public:
  // Factory method to create a verifier of a specific subclass
  template <typename Subclass, typename... Args>
  static std::shared_ptr<CertificateVerifier> Create(Args&&... args) {
    auto* external_verifier = new Subclass(std::forward<Args>(args)...);
    return std::make_shared<CertificateVerifier>(
        grpc_tls_certificate_verifier_external_create(
            external_verifier->base_));
  }

  // Pure virtual methods to be implemented by subclasses
  virtual bool Verify(TlsCustomVerificationCheckRequest* request,
                      std::function<void(grpc::Status)> callback,
                      grpc::Status* sync_status) = 0;

  virtual void Cancel(TlsCustomVerificationCheckRequest* request) = 0;

 protected:
  ExternalCertificateVerifier();
  virtual ~ExternalCertificateVerifier();

 private:
  // State for an asynchronous verification request
  struct AsyncRequestState {
    AsyncRequestState(grpc_tls_on_custom_verification_check_done_cb cb,
                      void* arg,
                      grpc_tls_custom_verification_check_request* request)
        : callback(cb), callback_arg(arg), cpp_request(request) {}

    grpc_tls_on_custom_verification_check_done_cb callback;
    void* callback_arg;
    TlsCustomVerificationCheckRequest cpp_request;
  };

  // C-style callbacks that bridge to the C++ implementation
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
  // Map of active verification requests to their state
  std::map<grpc_tls_custom_verification_check_request*, AsyncRequestState>
      request_map_ ABSL_GUARDED_BY(mu_);
};

// A certificate verifier that always accepts certificates (no verification)
class NoOpCertificateVerifier : public CertificateVerifier {
 public:
  NoOpCertificateVerifier();
};

// A certificate verifier that verifies hostnames against certificate names
class HostNameCertificateVerifier : public CertificateVerifier {
 public:
  HostNameCertificateVerifier();
};

}  // namespace experimental
}  // namespace grpc

#endif  // GRPCPP_SECURITY_TLS_CERTIFICATE_VERIFIER_H
```

The comments added explain:
1. The purpose of each class and its main functionality
2. Important methods and their parameters/return values
3. The relationship between C and C++ interfaces
4. The asynchronous verification flow
5. Thread safety considerations (mutex usage)
6. The purpose of specific implementation classes
7. Key data structures and their roles

The comments are designed to help future developers understand:
- The overall architecture of the certificate verification system
- How to implement custom verifiers
- The flow of verification requests
- The interaction between C and C++ layers
- Threading considerations