Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/credentials/transport/tls/grpc_tls_certificate_verifier.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <string.h>

#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/tls/tls_utils.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/host_port.h"

namespace grpc_core {

// Verifies a certificate using an external verifier implementation
bool ExternalCertificateVerifier::Verify(
    grpc_tls_custom_verification_check_request* request,
    std::function<void(absl::Status)> callback, absl::Status* sync_status) {
  {
    // Store the callback in the request map for later use
    MutexLock lock(&mu_);
    request_map_.emplace(request, std::move(callback));
  }

  // Call the external verifier's verify function
  grpc_status_code status_code = GRPC_STATUS_OK;
  char* error_details = nullptr;
  bool is_done = external_verifier_->verify(external_verifier_->user_data,
                                            request, &OnVerifyDone, this,
                                            &status_code, &error_details);
  if (is_done) {
    // If verification is done synchronously, handle the result
    if (status_code != GRPC_STATUS_OK) {
      *sync_status = absl::Status(static_cast<absl::StatusCode>(status_code),
                                  error_details);
    }
    MutexLock lock(&mu_);
    request_map_.erase(request);
  }
  gpr_free(error_details);
  return is_done;
}

// Returns the type name for this verifier
UniqueTypeName ExternalCertificateVerifier::type() const {
  static UniqueTypeName::Factory kFactory("External");
  return kFactory.Create();
}

// Callback invoked when external verification is complete
void ExternalCertificateVerifier::OnVerifyDone(
    grpc_tls_custom_verification_check_request* request, void* callback_arg,
    grpc_status_code status, const char* error_details) {
  ExecCtx exec_ctx;
  auto* self = static_cast<ExternalCertificateVerifier*>(callback_arg);
  std::function<void(absl::Status)> callback;
  {
    // Retrieve and remove the callback from the request map
    MutexLock lock(&self->mu_);
    auto it = self->request_map_.find(request);
    if (it != self->request_map_.end()) {
      callback = std::move(it->second);
      self->request_map_.erase(it);
    }
  }
  // Invoke the callback with the verification result
  if (callback != nullptr) {
    absl::Status return_status;
    if (status != GRPC_STATUS_OK) {
      return_status =
          absl::Status(static_cast<absl::StatusCode>(status), error_details);
    }
    callback(return_status);
  }
}

// Returns the type name for the no-op verifier
UniqueTypeName NoOpCertificateVerifier::type() const {
  static UniqueTypeName::Factory kFactory("NoOp");
  return kFactory.Create();
}

// Verifies a certificate by checking hostname against SANs (Subject Alternative Names)
bool HostNameCertificateVerifier::Verify(
    grpc_tls_custom_verification_check_request* request,
    std::function<void(absl::Status)>, absl::Status* sync_status) {
  CHECK_NE(request, nullptr);

  // Check if target name is provided
  const char* target_name = request->target_name;
  if (target_name == nullptr) {
    *sync_status = absl::Status(absl::StatusCode::kUnauthenticated,
                                "Target name is not specified.");
    return true;
  }
  
  // Split host and port from target name
  absl::string_view target_host;
  absl::string_view ignored_port;
  SplitHostPort(target_name, &target_host, &ignored_port);
  if (target_host.empty()) {
    *sync_status = absl::Status(absl::StatusCode::kUnauthenticated,
                                "Failed to split hostname and port.");
    return true;
  }

  // Remove zone identifier if present (for IPv6 addresses)
  const size_t zone_id = target_host.find('%');
  if (zone_id != absl::string_view::npos) {
    target_host.remove_suffix(target_host.size() - zone_id);
  }

  // Check DNS SANs
  char** dns_names = request->peer_info.san_names.dns_names;
  size_t dns_names_size = request->peer_info.san_names.dns_names_size;
  if (dns_names != nullptr && dns_names_size > 0) {
    for (size_t i = 0; i < dns_names_size; ++i) {
      const char* dns_name = dns_names[i];
      if (VerifySubjectAlternativeName(dns_name, std::string(target_host))) {
        return true;
      }
    }
  }

  // Check IP SANs
  char** ip_names = request->peer_info.san_names.ip_names;
  size_t ip_names_size = request->peer_info.san_names.ip_names_size;
  if (ip_names != nullptr && ip_names_size > 0) {
    for (size_t i = 0; i < ip_names_size; ++i) {
      const char* ip_name = ip_names[i];
      if (target_host == ip_name) {
        return true;
      }
    }
  }

  // If no DNS SANs, check common name as fallback
  if (dns_names_size == 0) {
    const char* common_name = request->peer_info.common_name;
    if (common_name != nullptr &&
        VerifySubjectAlternativeName(common_name, std::string(target_host))) {
      return true;
    }
  }
  
  // Verification failed if none of the checks passed
  *sync_status = absl::Status(absl::StatusCode::kUnauthenticated,
                              "Hostname Verification Check failed.");
  return true;
}

// Returns the type name for the hostname verifier
UniqueTypeName HostNameCertificateVerifier::type() const {
  static UniqueTypeName::Factory kFactory("Hostname");
  return kFactory.Create();
}

}  // namespace grpc_core

// C API function to verify a certificate
int grpc_tls_certificate_verifier_verify(
    grpc_tls_certificate_verifier* verifier,
    grpc_tls_custom_verification_check_request* request,
    grpc_tls_on_custom_verification_check_done_cb callback, void* callback_arg,
    grpc_status_code* sync_status, char** sync_error_details) {
  grpc_core::ExecCtx exec_ctx;
  // Create a C++ callback that wraps the C callback
  std::function<void(absl::Status)> async_cb =
      [callback, request, callback_arg](absl::Status async_status) {
        callback(request, callback_arg,
                 static_cast<grpc_status_code>(async_status.code()),
                 std::string(async_status.message()).c_str());
      };
  absl::Status sync_status_cpp;
  bool is_done = verifier->Verify(request, async_cb, &sync_status_cpp);
  if (is_done) {
    // If verification completed synchronously, convert the result
    if (!sync_status_cpp.ok()) {
      *sync_status = static_cast<grpc_status_code>(sync_status_cpp.code());
      *sync_error_details =
          gpr_strdup(std::string(sync_status_cpp.message()).c_str());
    }
  }
  return is_done;
}

// C API function to cancel a verification request
void grpc_tls_certificate_verifier_cancel(
    grpc_tls_certificate_verifier* verifier,
    grpc_tls_custom_verification_check_request* request) {
  grpc_core::ExecCtx exec_ctx;
  verifier->Cancel(request);
}

// Creates an external certificate verifier
grpc_tls_certificate_verifier* grpc_tls_certificate_verifier_external_create(
    grpc_tls_certificate_verifier_external* external_verifier) {
  grpc_core::ExecCtx exec_ctx;
  return new grpc_core::ExternalCertificateVerifier(external_verifier);
}

// Creates a no-op certificate verifier (always succeeds)
grpc_tls_certificate_verifier* grpc_tls_certificate_verifier_no_op_create() {
  grpc_core::ExecCtx exec_ctx;
  return new grpc_core::NoOpCertificateVerifier();
}

// Creates a hostname certificate verifier
grpc_tls_certificate_verifier*
grpc_tls_certificate_verifier_host_name_create() {
  grpc_core::ExecCtx exec_ctx;
  return new grpc_core::HostNameCertificateVerifier();
}

// Releases a certificate verifier
void grpc_tls_certificate_verifier_release(
    grpc_tls_certificate_verifier* verifier) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_tls_certificate_verifier_release(verifier=" << verifier << ")";
  grpc_core::ExecCtx exec_ctx;
  if (verifier != nullptr) verifier->Unref();
}
```