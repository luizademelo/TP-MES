Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/xds/grpc/xds_common_types.h"

#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "src/core/util/match.h"

namespace grpc_core {

// Returns a string representation of the CertificateProviderPluginInstance object
// Format: "{instance_name=value, certificate_name=value}" (only includes non-empty fields)
std::string CommonTlsContext::CertificateProviderPluginInstance::ToString()
    const {
  std::vector<std::string> contents;
  if (!instance_name.empty()) {
    contents.push_back(absl::StrFormat("instance_name=%s", instance_name));
  }
  if (!certificate_name.empty()) {
    contents.push_back(
        absl::StrFormat("certificate_name=%s", certificate_name));
  }
  return absl::StrCat("{", absl::StrJoin(contents, ", "), "}");
}

// Returns true if both instance_name and certificate_name are empty
bool CommonTlsContext::CertificateProviderPluginInstance::Empty() const {
  return instance_name.empty() && certificate_name.empty();
}

// Returns a string representation of the CertificateValidationContext object
// Format includes:
// - CA certificate source (either provider or system root)
// - Subject Alternative Name matchers (if any)
std::string CommonTlsContext::CertificateValidationContext::ToString() const {
  std::vector<std::string> contents;
  Match(
      ca_certs, [](const std::monostate&) {},  // No action if no CA certs specified
      [&](const CertificateProviderPluginInstance& cert_provider) {
        contents.push_back(
            absl::StrCat("ca_certs=cert_provider", cert_provider.ToString()));
      },
      [&](const SystemRootCerts&) {
        contents.push_back("ca_certs=system_root_certs{}");
      });
  if (!match_subject_alt_names.empty()) {
    std::vector<std::string> san_matchers;
    san_matchers.reserve(match_subject_alt_names.size());
    for (const auto& match : match_subject_alt_names) {
      san_matchers.push_back(match.ToString());
    }
    contents.push_back(absl::StrCat("match_subject_alt_names=[",
                                    absl::StrJoin(san_matchers, ", "), "]"));
  }
  return absl::StrCat("{", absl::StrJoin(contents, ", "), "}");
}

// Returns true if no CA certificates are specified and no subject alternative names
// are configured for matching
bool CommonTlsContext::CertificateValidationContext::Empty() const {
  return std::holds_alternative<std::monostate>(ca_certs) &&
         match_subject_alt_names.empty();
}

// Returns a string representation of the CommonTlsContext object
// Format includes:
// - TLS certificate provider instance (if configured)
// - Certificate validation context (if configured)
std::string CommonTlsContext::ToString() const {
  std::vector<std::string> contents;
  if (!tls_certificate_provider_instance.Empty()) {
    contents.push_back(
        absl::StrFormat("tls_certificate_provider_instance=%s",
                        tls_certificate_provider_instance.ToString()));
  }
  if (!certificate_validation_context.Empty()) {
    contents.push_back(
        absl::StrFormat("certificate_validation_context=%s",
                        certificate_validation_context.ToString()));
  }
  return absl::StrCat("{", absl::StrJoin(contents, ", "), "}");
}

// Returns true if neither TLS certificate provider instance nor certificate
// validation context are configured
bool CommonTlsContext::Empty() const {
  return tls_certificate_provider_instance.Empty() &&
         certificate_validation_context.Empty();
}

}  // namespace grpc_core
```

The comments added explain:
1. The purpose of each method
2. The string format returned by ToString() methods
3. The conditions checked by Empty() methods
4. The logical flow of each method
5. The variant handling in CertificateValidationContext

The comments are concise but provide enough information for a developer to understand what each method does without having to analyze the implementation details.