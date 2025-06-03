Here's the commented version of the code:

```c++
// Copyright 2025 gRPC authors.

#include "src/core/credentials/transport/tls/spiffe_utils.h"

#include <openssl/x509.h>

#include <string>

#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "src/core/tsi/ssl_transport_security_utils.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/load_file.h"
#include "src/core/util/status_helper.h"

namespace grpc_core {
namespace {
// Constants for SPIFFE validation
constexpr absl::string_view kAllowedUse = "x509-svid";  // Allowed use type
constexpr absl::string_view kAllowedKty = "RSA";        // Allowed key type
constexpr absl::string_view kCertificatePrefix = "-----BEGIN CERTIFICATE-----\n";
constexpr absl::string_view kCertificateSuffix = "\n-----END CERTIFICATE-----";
constexpr int kMaxTrustDomainLength = 255;  // Max length for trust domain
constexpr absl::string_view kSpiffePrefix = "spiffe://";  // SPIFFE URI prefix
constexpr int kX5cSize = 1;  // Expected size of x5c certificate chain array

// Validates basic URI requirements for SPIFFE IDs
absl::Status DoInitialUriValidation(absl::string_view uri) {
  if (uri.empty()) {
    return absl::InvalidArgumentError(
        "SPIFFE ID cannot be parsed from empty URI");
  }
  if (uri.length() > 2048) {
    return absl::InvalidArgumentError(absl::StrFormat(
        "URI length is %d, maximum allowed for SPIFFE ID is 2048",
        uri.length()));
  }
  if (absl::StrContains(uri, "#")) {
    return absl::InvalidArgumentError(
        "SPIFFE ID cannot contain query fragments");
  }
  if (absl::StrContains(uri, "?")) {
    return absl::InvalidArgumentError(
        "SPIFFE ID cannot contain query parameters");
  }
  // Check for non-ASCII characters
  for (char ch : uri) {
    if (!absl::ascii_isascii(ch)) {
      return absl::InvalidArgumentError(absl::StrFormat(
          "SPIFFE ID URI cannot contain non-ascii characters. Contains %#x",
          ch));
    }
  }
  return absl::OkStatus();
}

// Validates trust domain format according to SPIFFE specifications
absl::Status ValidateTrustDomain(absl::string_view trust_domain) {
  if (trust_domain.empty()) {
    return absl::InvalidArgumentError("Trust domain cannot be empty");
  }
  if (trust_domain.size() > kMaxTrustDomainLength) {
    return absl::InvalidArgumentError(absl::StrFormat(
        "Trust domain maximum length is %i characters", kMaxTrustDomainLength));
  }
  // Check each character in trust domain
  for (auto c : trust_domain) {
    if (c >= 'a' && c <= 'z') continue;
    if (c >= '0' && c <= '9') continue;
    if (c == '.') continue;
    if (c == '-') continue;
    if (c == '_') continue;
    return absl::InvalidArgumentError(absl::StrFormat(
        "Trust domain contains invalid character '%c'. MUST contain only "
        "lowercase letters, numbers, dots, dashes, and underscores",
        c));
  }
  return absl::OkStatus();
}

// Validates individual path segments in SPIFFE ID
absl::Status ValidatePathSegment(absl::string_view path_segment) {
  if (path_segment.empty()) {
    return absl::InvalidArgumentError("Path segment cannot be empty");
  }
  if (path_segment == "." || path_segment == "..") {
    return absl::InvalidArgumentError(
        "Path segment cannot be a relative modifier (. or ..)");
  }
  // Check each character in path segment
  for (auto c : path_segment) {
    if (c >= 'a' && c <= 'z') continue;
    if (c >= 'A' && c <= 'Z') continue;
    if (c >= '0' && c <= '9') continue;
    if (c == '.') continue;
    if (c == '-') continue;
    if (c == '_') continue;
    return absl::InvalidArgumentError(absl::StrFormat(
        "Path segment contains invalid character '%c'. MUST contain only "
        "letters, numbers, dots, dashes, and underscores",
        c));
  }
  return absl::OkStatus();
}

// Validates the entire path component of a SPIFFE ID
absl::Status ValidatePath(absl::string_view path) {
  if (path.empty()) {
    return absl::OkStatus();
  }
  // Validate each segment in the path
  for (absl::string_view segment : absl::StrSplit(path, '/')) {
    GRPC_RETURN_IF_ERROR(ValidatePathSegment(segment));
  }
  return absl::OkStatus();
}

}  // namespace

// Creates a SpiffeId from a string input with validation
absl::StatusOr<SpiffeId> SpiffeId::FromString(absl::string_view input) {
  GRPC_RETURN_IF_ERROR(DoInitialUriValidation(input));
  if (!absl::StartsWithIgnoreCase(input, kSpiffePrefix)) {
    return absl::InvalidArgumentError("SPIFFE ID must start with spiffe://");
  }
  if (absl::EndsWith(input, "/")) {
    return absl::InvalidArgumentError("SPIFFE ID cannot end with a /");
  }

  // Extract trust domain and path components
  absl::string_view trust_domain_and_path =
      input.substr(kSpiffePrefix.length());
  absl::string_view trust_domain;
  absl::string_view path;
  
  if (absl::StartsWith(trust_domain_and_path, "/")) {
    return absl::InvalidArgumentError("The trust domain cannot be empty");
  }

  // Split into trust domain and path
  if (absl::StrContains(trust_domain_and_path, "/")) {
    std::vector<absl::string_view> split =
        absl::StrSplit(trust_domain_and_path, absl::MaxSplits('/', 1));
    trust_domain = split[0];
    path = split[1];
  } else {
    trust_domain = trust_domain_and_path;
  }
  
  // Validate components
  GRPC_RETURN_IF_ERROR(ValidateTrustDomain(trust_domain));
  GRPC_RETURN_IF_ERROR(ValidatePath(path));

  // Return constructed SpiffeId
  if (path.empty()) {
    return SpiffeId(trust_domain, "");
  }
  return SpiffeId(trust_domain, absl::StrCat("/", path));
}

// JSON loader for SpiffeBundleKey
const JsonLoaderInterface* SpiffeBundleKey::JsonLoader(const JsonArgs&) {
  static const auto* kLoader = JsonObjectLoader<SpiffeBundleKey>().Finish();
  return kLoader;
}

// Post-load validation for SpiffeBundleKey JSON data
void SpiffeBundleKey::JsonPostLoad(const Json& json, const JsonArgs& args,
                                   ValidationErrors* errors) {
  // Validate 'use' field
  auto use =
      LoadJsonObjectField<std::string>(json.object(), args, "use", errors);
  {
    ValidationErrors::ScopedField field(errors, ".use");
    if (use.has_value() && *use != kAllowedUse) {
      errors->AddError(absl::StrFormat("value must be \"%s\", got \"%s\"",
                                       kAllowedUse, *use));
    }
  }
  
  // Validate 'kty' field
  auto kty =
      LoadJsonObjectField<std::string>(json.object(), args, "kty", errors);
  {
    ValidationErrors::ScopedField field(errors, ".kty");
    if (kty.has_value() && *kty != kAllowedKty) {
      errors->AddError(absl::StrFormat("value must be \"%s\", got \"%s\"",
                                       kAllowedKty, *kty));
    }
  }
  
  // Validate 'x5c' certificate chain
  auto x5c = LoadJsonObjectField<std::vector<std::string>>(json.object(), args,
                                                           "x5c", errors);
  if (x5c.has_value()) {
    ValidationErrors::ScopedField field(errors, ".x5c");
    if (x5c->size() != kX5cSize) {
      errors->AddError(
          absl::StrCat("array length must be 1, got ", x5c->size()));
    }
    if (!x5c->empty()) {
      ValidationErrors::ScopedField field(errors, "[0]");
      std::string pem_cert =
          absl::StrCat(kCertificatePrefix, (*x5c)[0], kCertificateSuffix);
      auto certs = ParsePemCertificateChain(pem_cert);
      if (!certs.ok()) {
        errors->AddError(certs.status().ToString());
      } else {
        root_ = std::move((*x5c)[0]);
        for (X509* cert : *certs) {
          X509_free(cert);
        }
      }
    }
  }
}

// Returns the root certificate
absl::string_view SpiffeBundleKey::GetRoot() { return root_; }

// Post-load processing for SpiffeBundle JSON data
void SpiffeBundle::JsonPostLoad(const Json& json, const JsonArgs& args,
                                ValidationErrors* errors) {
  auto keys = LoadJsonObjectField<std::vector<SpiffeBundleKey>>(
      json.object(), args, "keys", errors);
  if (!keys.has_value()) {
    return;
  }
  // Collect all root certificates
  for (size_t i = 0; i < keys->size(); ++i) {
    roots_.emplace_back((*keys)[i].GetRoot());
  }
}

// Returns all root certificates in the bundle
absl::Span<const std::string> SpiffeBundle::GetRoots() { return roots_; }

// Post-load validation for SpiffeBundleMap
void SpiffeBundleMap::JsonPostLoad(const Json&, const JsonArgs&,
                                   ValidationErrors* errors) {
  // Validate all trust domains in the map
  for (auto const& [k, _] : bundles_) {
    ValidationErrors::ScopedField field(
        errors, absl::StrCat(".trust_domains[\"", k, "\"]"));
    absl::Status status = ValidateTrustDomain(k);
    if (!status.ok()) {
      errors->AddError(
          absl::StrCat("invalid trust domain: ", status.ToString()));
    }
  }
}

// Creates a SpiffeBundleMap from a file
absl::StatusOr<SpiffeBundleMap> SpiffeBundleMap::FromFile(
    absl::string_view file_path) {
  auto slice = LoadFile(file_path.data(), false);
  GRPC_RETURN_IF_ERROR(slice.status());
  auto json = JsonParse(slice->as_string_view());
  GRPC_RETURN_IF_ERROR(json.status());
  return LoadFromJson<SpiffeBundleMap>(*json);
}

// Retrieves root certificates for a specific trust domain
absl::StatusOr<absl::Span<const std::string>> SpiffeBundleMap::GetRoots(
    const absl::string_view trust_domain) {
  if (auto it = bundles_.find(trust_domain); it != bundles_.end()) {
    return it->second.GetRoots();
  }
  return absl::NotFoundError(absl::StrFormat(
      "No spiffe bundle found for trust domain %s", trust_domain));
}

}  // namespace grpc_core
```