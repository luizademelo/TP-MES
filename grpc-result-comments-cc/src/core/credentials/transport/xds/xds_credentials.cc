Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

#include "src/core/credentials/transport/xds/xds_credentials.h"

#include <grpc/grpc_security_constants.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/port_platform.h>

#include <optional>

#include "absl/log/check.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_provider.h"
#include "src/core/credentials/transport/tls/grpc_tls_credentials_options.h"
#include "src/core/credentials/transport/tls/tls_credentials.h"
#include "src/core/credentials/transport/tls/tls_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/load_balancing/xds/xds_channel_args.h"
#include "src/core/util/useful.h"
#include "src/core/xds/grpc/xds_certificate_provider.h"

namespace grpc_core {

namespace {

// Verifies if any of the subject alternative names (SANs) match any of the provided matchers
// Args:
//   subject_alternative_names: Array of SAN strings to check
//   subject_alternative_names_size: Number of SANs in the array
//   matchers: List of StringMatcher objects to compare against
// Returns:
//   true if at least one SAN matches any matcher, false otherwise
bool XdsVerifySubjectAlternativeNames(
    const char* const* subject_alternative_names,
    size_t subject_alternative_names_size,
    const std::vector<StringMatcher>& matchers) {
  if (matchers.empty()) return true;  // No matchers means automatic success
  for (size_t i = 0; i < subject_alternative_names_size; ++i) {
    for (const auto& matcher : matchers) {
      if (matcher.type() == StringMatcher::Type::kExact) {
        // For exact matches, use specialized verification
        if (VerifySubjectAlternativeName(subject_alternative_names[i],
                                         matcher.string_matcher())) {
          return true;
        }
      } else {
        // For other match types, use the matcher directly
        if (matcher.Match(subject_alternative_names[i])) {
          return true;
        }
      }
    }
  }
  return false;  // No matches found
}

}  // namespace

// Constructor for XdsCertificateVerifier
// Args:
//   xds_certificate_provider: Reference-counted pointer to XdsCertificateProvider
XdsCertificateVerifier::XdsCertificateVerifier(
    RefCountedPtr<XdsCertificateProvider> xds_certificate_provider)
    : xds_certificate_provider_(std::move(xds_certificate_provider)) {}

// Performs certificate verification by checking SANs against xDS provided matchers
// Args:
//   request: TLS verification request containing peer info
//   sync_status: Output parameter for verification status
// Returns:
//   Always returns true (verification is synchronous)
bool XdsCertificateVerifier::Verify(
    grpc_tls_custom_verification_check_request* request,
    std::function<void(absl::Status)>, absl::Status* sync_status) {
  CHECK_NE(request, nullptr);
  // Check all types of SANs (URI, IP, DNS) against the matchers
  if (!XdsVerifySubjectAlternativeNames(
          request->peer_info.san_names.uri_names,
          request->peer_info.san_names.uri_names_size,
          xds_certificate_provider_->san_matchers()) &&
      !XdsVerifySubjectAlternativeNames(
          request->peer_info.san_names.ip_names,
          request->peer_info.san_names.ip_names_size,
          xds_certificate_provider_->san_matchers()) &&
      !XdsVerifySubjectAlternativeNames(
          request->peer_info.san_names.dns_names,
          request->peer_info.san_names.dns_names_size,
          xds_certificate_provider_->san_matchers())) {
    // If no SANs match, set verification failure status
    *sync_status = absl::Status(
        absl::StatusCode::kUnauthenticated,
        "SANs from certificate did not match SANs from xDS control plane");
  }
  return true;
}

// Cancels an ongoing verification (no-op in this implementation)
void XdsCertificateVerifier::Cancel(
    grpc_tls_custom_verification_check_request*) {}

// Compares two XdsCertificateVerifier instances
// Args:
//   other: Other verifier to compare with
// Returns:
//   Comparison result based on the underlying certificate providers
int XdsCertificateVerifier::CompareImpl(
    const grpc_tls_certificate_verifier* other) const {
  auto* o = static_cast<const XdsCertificateVerifier*>(other);
  if (xds_certificate_provider_ == nullptr ||
      o->xds_certificate_provider_ == nullptr) {
    return QsortCompare(xds_certificate_provider_,
                        o->xds_certificate_provider_);
  }
  return xds_certificate_provider_->Compare(o->xds_certificate_provider_.get());
}

// Returns the type name of this verifier
UniqueTypeName XdsCertificateVerifier::type() const {
  static UniqueTypeName::Factory kFactory("Xds");
  return kFactory.Create();
}

// Test-only version of SAN verification function
bool TestOnlyXdsVerifySubjectAlternativeNames(
    const char* const* subject_alternative_names,
    size_t subject_alternative_names_size,
    const std::vector<StringMatcher>& matchers) {
  return XdsVerifySubjectAlternativeNames(
      subject_alternative_names, subject_alternative_names_size, matchers);
}

// Creates a security connector for XdsCredentials
// Args:
//   call_creds: Call credentials to use
//   target_name: Target name for the connection
//   args: Channel arguments (modified in-place)
// Returns:
//   Ref-counted pointer to created security connector
RefCountedPtr<grpc_channel_security_connector>
XdsCredentials::create_security_connector(
    RefCountedPtr<grpc_call_credentials> call_creds, const char* target_name,
    ChannelArgs* args) {
  // Set target name override if not already set
  *args = args->SetIfUnset(GRPC_SSL_TARGET_NAME_OVERRIDE_ARG, target_name);
  RefCountedPtr<grpc_channel_security_connector> security_connector;
  
  // Get xDS certificate provider from channel args if available
  auto xds_certificate_provider = args->GetObjectRef<XdsCertificateProvider>();
  if (xds_certificate_provider != nullptr) {
    const bool watch_root = xds_certificate_provider->ProvidesRootCerts();
    const bool use_system_root_certs =
        xds_certificate_provider->UseSystemRootCerts();
    const bool watch_identity =
        xds_certificate_provider->ProvidesIdentityCerts();
    
    // If any certificate watching is needed, create TLS credentials
    if (watch_root || use_system_root_certs || watch_identity) {
      auto tls_credentials_options =
          MakeRefCounted<grpc_tls_credentials_options>();
      
      // Configure certificate watching if needed
      if (watch_root || watch_identity) {
        tls_credentials_options->set_certificate_provider(
            xds_certificate_provider);
        if (watch_root) {
          tls_credentials_options->set_watch_root_cert(true);
        }
        if (watch_identity) {
          tls_credentials_options->set_watch_identity_pair(true);
        }
      }
      
      // Configure verification options
      tls_credentials_options->set_verify_server_cert(true);
      tls_credentials_options->set_certificate_verifier(
          MakeRefCounted<XdsCertificateVerifier>(
              std::move(xds_certificate_provider)));
      tls_credentials_options->set_check_call_host(false);
      
      // Create and return TLS security connector
      auto tls_credentials =
          MakeRefCounted<TlsCredentials>(std::move(tls_credentials_options));
      return tls_credentials->create_security_connector(std::move(call_creds),
                                                        target_name, args);
    }
  }
  
  // Fallback to using the fallback credentials if no xDS provider or no watching needed
  CHECK(fallback_credentials_ != nullptr);
  return fallback_credentials_->create_security_connector(std::move(call_creds),
                                                          target_name, args);
}

// Returns the type name of XdsCredentials
UniqueTypeName XdsCredentials::Type() {
  static UniqueTypeName::Factory kFactory("Xds");
  return kFactory.Create();
}

// Creates a security connector for XdsServerCredentials
// Args:
//   args: Channel arguments
// Returns:
//   Ref-counted pointer to created security connector
RefCountedPtr<grpc_server_security_connector>
XdsServerCredentials::create_security_connector(const ChannelArgs& args) {
  auto xds_certificate_provider = args.GetObjectRef<XdsCertificateProvider>();

  // If identity certificates are provided, create TLS credentials
  if (xds_certificate_provider != nullptr &&
      xds_certificate_provider->ProvidesIdentityCerts()) {
    auto tls_credentials_options =
        MakeRefCounted<grpc_tls_credentials_options>();
    tls_credentials_options->set_watch_identity_pair(true);
    tls_credentials_options->set_certificate_provider(xds_certificate_provider);
    
    // Configure root certificate watching if available
    if (xds_certificate_provider->ProvidesRootCerts()) {
      tls_credentials_options->set_watch_root_cert(true);
      tls_credentials_options->set_cert_request_type(
          xds_certificate_provider->require_client_certificate()
              ? GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY
              : GRPC_SSL_REQUEST_CLIENT_CERTIFICATE_AND_VERIFY);
    } else {
      tls_credentials_options->set_cert_request_type(
          GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE);
    }
    
    // Create and return TLS security connector
    auto tls_credentials = MakeRefCounted<TlsServerCredentials>(
        std::move(tls_credentials_options));
    return tls_credentials->create_security_connector(args);
  }
  
  // Fallback to using the fallback credentials if no xDS provider or no identity certs
  return fallback_credentials_->create_security_connector(args);
}

// Returns the type name of XdsServerCredentials
UniqueTypeName XdsServerCredentials::Type() {
  static UniqueTypeName::Factory kFactory("Xds");
  return kFactory.Create();
}

}  // namespace grpc_core

// Creates new XdsCredentials using the provided fallback credentials
grpc_channel_credentials* grpc_xds_credentials_create(
    grpc_channel_credentials* fallback_credentials) {
  CHECK_NE(fallback_credentials, nullptr);
  return new grpc_core::XdsCredentials(fallback_credentials->Ref());
}

// Creates new XdsServerCredentials using the provided fallback credentials
grpc_server_credentials* grpc_xds_server_credentials_create(
    grpc_server_credentials* fallback_credentials) {
  CHECK_NE(fallback_credentials, nullptr);
  return new grpc_core::XdsServerCredentials(fallback_credentials->Ref());
}
```