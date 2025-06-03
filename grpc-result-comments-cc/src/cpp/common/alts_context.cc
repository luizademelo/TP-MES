Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

#include <grpc/grpc_security_constants.h>
#include <grpcpp/security/alts_context.h>
#include <stddef.h>

#include <map>
#include <string>

#include "src/proto/grpc/gcp/altscontext.upb.h"
#include "src/proto/grpc/gcp/transport_security_common.upb.h"
#include "upb/base/string_view.h"
#include "upb/message/map.h"

namespace grpc {
namespace experimental {

// Constructor for AltsContext that initializes the object from a grpc_gcp_AltsContext
AltsContext::AltsContext(const grpc_gcp_AltsContext* ctx) {
  // Extract and store application protocol if present
  upb_StringView application_protocol =
      grpc_gcp_AltsContext_application_protocol(ctx);
  if (application_protocol.data != nullptr && application_protocol.size > 0) {
    application_protocol_ =
        std::string(application_protocol.data, application_protocol.size);
  }

  // Extract and store record protocol if present
  upb_StringView record_protocol = grpc_gcp_AltsContext_record_protocol(ctx);
  if (record_protocol.data != nullptr && record_protocol.size > 0) {
    record_protocol_ = std::string(record_protocol.data, record_protocol.size);
  }

  // Extract and store peer service account if present
  upb_StringView peer_service_account =
      grpc_gcp_AltsContext_peer_service_account(ctx);
  if (peer_service_account.data != nullptr && peer_service_account.size > 0) {
    peer_service_account_ =
        std::string(peer_service_account.data, peer_service_account.size);
  }

  // Extract and store local service account if present
  upb_StringView local_service_account =
      grpc_gcp_AltsContext_local_service_account(ctx);
  if (local_service_account.data != nullptr && local_service_account.size > 0) {
    local_service_account_ =
        std::string(local_service_account.data, local_service_account.size);
  }

  // Extract and store RPC protocol versions if present
  const grpc_gcp_RpcProtocolVersions* versions =
      grpc_gcp_AltsContext_peer_rpc_versions(ctx);
  if (versions != nullptr) {
    // Store max RPC version if available
    const grpc_gcp_RpcProtocolVersions_Version* max_version =
        grpc_gcp_RpcProtocolVersions_max_rpc_version(versions);
    if (max_version != nullptr) {
      int max_version_major =
          grpc_gcp_RpcProtocolVersions_Version_major(max_version);
      int max_version_minor =
          grpc_gcp_RpcProtocolVersions_Version_minor(max_version);
      peer_rpc_versions_.max_rpc_version.major_version = max_version_major;
      peer_rpc_versions_.max_rpc_version.minor_version = max_version_minor;
    }

    // Store min RPC version if available
    const grpc_gcp_RpcProtocolVersions_Version* min_version =
        grpc_gcp_RpcProtocolVersions_min_rpc_version(versions);
    if (min_version != nullptr) {
      int min_version_major =
          grpc_gcp_RpcProtocolVersions_Version_major(min_version);
      int min_version_minor =
          grpc_gcp_RpcProtocolVersions_Version_minor(min_version);
      peer_rpc_versions_.min_rpc_version.major_version = min_version_major;
      peer_rpc_versions_.min_rpc_version.minor_version = min_version_minor;
    }
  }

  // Store security level if it's within valid bounds
  if (grpc_gcp_AltsContext_security_level(ctx) >= GRPC_SECURITY_MIN ||
      grpc_gcp_AltsContext_security_level(ctx) <= GRPC_SECURITY_MAX) {
    security_level_ = static_cast<grpc_security_level>(
        grpc_gcp_AltsContext_security_level(ctx));
  }

  // Extract and store peer attributes if present
  if (grpc_gcp_AltsContext_peer_attributes_size(ctx) != 0) {
    grpc_gcp_AltsContext* ctx_upb = (grpc_gcp_AltsContext*)ctx;
    size_t iter = kUpb_Map_Begin;
    upb_StringView key;
    upb_StringView val;
    // Iterate through all peer attributes and store them in a map
    while (
        grpc_gcp_AltsContext_peer_attributes_next(ctx_upb, &key, &val, &iter)) {
      peer_attributes_map_[std::string(key.data, key.size)] =
          std::string(val.data, val.size);
    }
  }
}

// Getter for application protocol
std::string AltsContext::application_protocol() const {
  return application_protocol_;
}

// Getter for record protocol
std::string AltsContext::record_protocol() const { return record_protocol_; }

// Getter for peer service account
std::string AltsContext::peer_service_account() const {
  return peer_service_account_;
}

// Getter for local service account
std::string AltsContext::local_service_account() const {
  return local_service_account_;
}

// Getter for security level
grpc_security_level AltsContext::security_level() const {
  return security_level_;
}

// Getter for peer RPC versions
AltsContext::RpcProtocolVersions AltsContext::peer_rpc_versions() const {
  return peer_rpc_versions_;
}

// Getter for peer attributes map
const std::map<std::string, std::string>& AltsContext::peer_attributes() const {
  return peer_attributes_map_;
}

}  // namespace experimental
}  // namespace grpc
```