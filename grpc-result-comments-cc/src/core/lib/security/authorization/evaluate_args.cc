Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/lib/security/authorization/evaluate_args.h"

#include <grpc/grpc_security_constants.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/match.h"
#include "absl/strings/numbers.h"
#include "src/core/credentials/transport/tls/tls_utils.h"
#include "src/core/handshaker/endpoint_info/endpoint_info_handshaker.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/util/host_port.h"
#include "src/core/util/uri.h"

namespace grpc_core {

namespace {

// Parses a URI string into an Address structure containing host, port, and resolved address.
// Returns an empty Address structure if parsing fails at any step.
EvaluateArgs::PerChannelArgs::Address ParseEndpointUri(
    absl::string_view uri_text) {
  EvaluateArgs::PerChannelArgs::Address address;
  // Attempt to parse the URI text into a URI object
  absl::StatusOr<URI> uri = URI::Parse(uri_text);
  if (!uri.ok()) {
    VLOG(2) << "Failed to parse uri.";
    return address;
  }
  
  // Split the URI path into host and port components
  absl::string_view host_view;
  absl::string_view port_view;
  if (!SplitHostPort(uri->path(), &host_view, &port_view)) {
    VLOG(2) << "Failed to split " << uri->path() << " into host and port.";
    return address;
  }
  
  // Convert port string to integer
  if (!absl::SimpleAtoi(port_view, &address.port)) {
    VLOG(2) << "Port " << port_view << " is out of range or null.";
  }
  
  // Store host string and attempt to resolve the full address
  address.address_str = std::string(host_view);
  auto resolved_address = StringToSockaddr(uri->path());
  if (!resolved_address.ok()) {
    VLOG(2) << "Address \"" << uri->path()
            << "\" is not IPv4/IPv6. Error: " << resolved_address.status();
    memset(&address.address, 0, sizeof(address.address));
  } else {
    address.address = *resolved_address;
  }
  return address;
}

}  // namespace

// Constructor for PerChannelArgs that initializes security properties from auth_context
// and parses endpoint addresses from channel arguments.
EvaluateArgs::PerChannelArgs::PerChannelArgs(grpc_auth_context* auth_context,
                                             const ChannelArgs& args) {
  if (auth_context != nullptr) {
    // Extract various security properties from the authentication context
    transport_security_type = GetAuthPropertyValue(
        auth_context, GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME);
    spiffe_id =
        GetAuthPropertyValue(auth_context, GRPC_PEER_SPIFFE_ID_PROPERTY_NAME);
    uri_sans = GetAuthPropertyArray(auth_context, GRPC_PEER_URI_PROPERTY_NAME);
    dns_sans = GetAuthPropertyArray(auth_context, GRPC_PEER_DNS_PROPERTY_NAME);
    common_name =
        GetAuthPropertyValue(auth_context, GRPC_X509_CN_PROPERTY_NAME);
    subject =
        GetAuthPropertyValue(auth_context, GRPC_X509_SUBJECT_PROPERTY_NAME);
  }
  // Parse local and peer endpoint addresses from channel arguments
  local_address = ParseEndpointUri(
      args.GetString(GRPC_ARG_ENDPOINT_LOCAL_ADDRESS).value_or(""));
  peer_address = ParseEndpointUri(
      args.GetString(GRPC_ARG_ENDPOINT_PEER_ADDRESS).value_or(""));
}

// Returns the HTTP path from metadata if available, otherwise returns empty string view
absl::string_view EvaluateArgs::GetPath() const {
  if (metadata_ != nullptr) {
    const auto* path = metadata_->get_pointer(HttpPathMetadata());
    if (path != nullptr) {
      return path->as_string_view();
    }
  }
  return absl::string_view();
}

// Returns the HTTP authority (host) from metadata if available, otherwise returns empty string view
absl::string_view EvaluateArgs::GetAuthority() const {
  absl::string_view authority;
  if (metadata_ != nullptr) {
    if (auto* authority_md = metadata_->get_pointer(HttpAuthorityMetadata())) {
      authority = authority_md->as_string_view();
    }
  }
  return authority;
}

// Returns the HTTP method from metadata if available, otherwise returns empty string view
absl::string_view EvaluateArgs::GetMethod() const {
  if (metadata_ != nullptr) {
    auto method_md = metadata_->get(HttpMethodMetadata());
    if (method_md.has_value()) {
      return HttpMethodMetadata::Encode(*method_md).as_string_view();
    }
  }
  return absl::string_view();
}

// Returns the value of a specific header from metadata. Special handling for 'te' and 'host' headers.
// For 'host' header, returns the authority. For 'te' header, returns nullopt.
// concatenated_value is used to store concatenated values for headers with multiple entries.
std::optional<absl::string_view> EvaluateArgs::GetHeaderValue(
    absl::string_view key, std::string* concatenated_value) const {
  if (metadata_ == nullptr) {
    return std::nullopt;
  }
  if (absl::EqualsIgnoreCase(key, "te")) {
    return std::nullopt;
  }
  if (absl::EqualsIgnoreCase(key, "host")) {
    return GetAuthority();
  }
  return metadata_->GetStringValue(key, concatenated_value);
}

// Returns the local address as a grpc_resolved_address structure
grpc_resolved_address EvaluateArgs::GetLocalAddress() const {
  if (channel_args_ == nullptr) {
    return {};
  }
  return channel_args_->local_address.address;
}

// Returns the local address as a string
absl::string_view EvaluateArgs::GetLocalAddressString() const {
  if (channel_args_ == nullptr) {
    return "";
  }
  return channel_args_->local_address.address_str;
}

// Returns the local port number
int EvaluateArgs::GetLocalPort() const {
  if (channel_args_ == nullptr) {
    return 0;
  }
  return channel_args_->local_address.port;
}

// Returns the peer address as a grpc_resolved_address structure
grpc_resolved_address EvaluateArgs::GetPeerAddress() const {
  if (channel_args_ == nullptr) {
    return {};
  }
  return channel_args_->peer_address.address;
}

// Returns the peer address as a string
absl::string_view EvaluateArgs::GetPeerAddressString() const {
  if (channel_args_ == nullptr) {
    return "";
  }
  return channel_args_->peer_address.address_str;
}

// Returns the peer port number
int EvaluateArgs::GetPeerPort() const {
  if (channel_args_ == nullptr) {
    return 0;
  }
  return channel_args_->peer_address.port;
}

// Returns the transport security type (e.g., "ssl", "tls")
absl::string_view EvaluateArgs::GetTransportSecurityType() const {
  if (channel_args_ == nullptr) {
    return "";
  }
  return channel_args_->transport_security_type;
}

// Returns the SPIFFE ID of the peer if available
absl::string_view EvaluateArgs::GetSpiffeId() const {
  if (channel_args_ == nullptr) {
    return "";
  }
  return channel_args_->spiffe_id;
}

// Returns a list of URI SANs (Subject Alternative Names) from the peer's certificate
std::vector<absl::string_view> EvaluateArgs::GetUriSans() const {
  if (channel_args_ == nullptr) {
    return {};
  }
  return channel_args_->uri_sans;
}

// Returns a list of DNS SANs (Subject Alternative Names) from the peer's certificate
std::vector<absl::string_view> EvaluateArgs::GetDnsSans() const {
  if (channel_args_ == nullptr) {
    return {};
  }
  return channel_args_->dns_sans;
}

// Returns the common name from the peer's certificate
absl::string_view EvaluateArgs::GetCommonName() const {
  if (channel_args_ == nullptr) {
    return "";
  }
  return channel_args_->common_name;
}

// Returns the subject from the peer's certificate
absl::string_view EvaluateArgs::GetSubject() const {
  if (channel_args_ == nullptr) {
    return "";
  }
  return channel_args_->subject;
}

}  // namespace grpc_core
```