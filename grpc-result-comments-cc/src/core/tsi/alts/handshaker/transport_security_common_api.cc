Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/handshaker/transport_security_common_api.h"

#include <grpc/support/port_platform.h>

#include "absl/log/log.h"
#include "upb/mem/arena.hpp"

// Sets the maximum RPC protocol version for a given versions structure.
// Returns true on success, false if versions is nullptr.
bool grpc_gcp_rpc_protocol_versions_set_max(
    grpc_gcp_rpc_protocol_versions* versions, uint32_t max_major,
    uint32_t max_minor) {
  if (versions == nullptr) {
    LOG(ERROR)
        << "versions is nullptr in grpc_gcp_rpc_protocol_versions_set_max().";
    return false;
  }
  versions->max_rpc_version.major = max_major;
  versions->max_rpc_version.minor = max_minor;
  return true;
}

// Sets the minimum RPC protocol version for a given versions structure.
// Returns true on success, false if versions is nullptr.
bool grpc_gcp_rpc_protocol_versions_set_min(
    grpc_gcp_rpc_protocol_versions* versions, uint32_t min_major,
    uint32_t min_minor) {
  if (versions == nullptr) {
    LOG(ERROR)
        << "versions is nullptr in grpc_gcp_rpc_protocol_versions_set_min().";
    return false;
  }
  versions->min_rpc_version.major = min_major;
  versions->min_rpc_version.minor = min_minor;
  return true;
}

// Encodes RPC protocol versions into a grpc_slice.
// Returns true on success, false if versions or slice is nullptr.
bool grpc_gcp_rpc_protocol_versions_encode(
    const grpc_gcp_rpc_protocol_versions* versions, grpc_slice* slice) {
  if (versions == nullptr || slice == nullptr) {
    LOG(ERROR) << "Invalid nullptr arguments to "
                  "grpc_gcp_rpc_protocol_versions_encode().";
    return false;
  }
  upb::Arena arena;
  grpc_gcp_RpcProtocolVersions* versions_msg =
      grpc_gcp_RpcProtocolVersions_new(arena.ptr());
  grpc_gcp_RpcProtocolVersions_assign_from_struct(versions_msg, arena.ptr(),
                                                  versions);
  return grpc_gcp_rpc_protocol_versions_encode(versions_msg, arena.ptr(),
                                               slice);
}

// Encodes RPC protocol versions (upb format) into a grpc_slice.
// Returns true on success, false if any argument is nullptr or serialization fails.
bool grpc_gcp_rpc_protocol_versions_encode(
    const grpc_gcp_RpcProtocolVersions* versions, upb_Arena* arena,
    grpc_slice* slice) {
  if (versions == nullptr || arena == nullptr || slice == nullptr) {
    LOG(ERROR) << "Invalid nullptr arguments to "
                  "grpc_gcp_rpc_protocol_versions_encode().";
    return false;
  }
  size_t buf_length;
  char* buf =
      grpc_gcp_RpcProtocolVersions_serialize(versions, arena, &buf_length);
  if (buf == nullptr) {
    return false;
  }
  *slice = grpc_slice_from_copied_buffer(buf, buf_length);
  return true;
}

// Decodes RPC protocol versions from a grpc_slice.
// Returns true on success, false if versions is nullptr or parsing fails.
bool grpc_gcp_rpc_protocol_versions_decode(
    const grpc_slice& slice, grpc_gcp_rpc_protocol_versions* versions) {
  if (versions == nullptr) {
    LOG(ERROR)
        << "version is nullptr in grpc_gcp_rpc_protocol_versions_decode().";
    return false;
  }
  upb::Arena arena;
  grpc_gcp_RpcProtocolVersions* versions_msg =
      grpc_gcp_RpcProtocolVersions_parse(
          reinterpret_cast<const char*>(GRPC_SLICE_START_PTR(slice)),
          GRPC_SLICE_LENGTH(slice), arena.ptr());
  if (versions_msg == nullptr) {
    LOG(ERROR) << "cannot deserialize RpcProtocolVersions message";
    return false;
  }
  grpc_gcp_rpc_protocol_versions_assign_from_upb(versions, versions_msg);
  return true;
}

// Assigns protocol versions from upb message to C struct.
// If max or min versions are null in the upb message, they are set to 0.
void grpc_gcp_rpc_protocol_versions_assign_from_upb(
    grpc_gcp_rpc_protocol_versions* versions,
    const grpc_gcp_RpcProtocolVersions* value) {
  const grpc_gcp_RpcProtocolVersions_Version* max_version_msg =
      grpc_gcp_RpcProtocolVersions_max_rpc_version(value);
  if (max_version_msg != nullptr) {
    versions->max_rpc_version.major =
        grpc_gcp_RpcProtocolVersions_Version_major(max_version_msg);
    versions->max_rpc_version.minor =
        grpc_gcp_RpcProtocolVersions_Version_minor(max_version_msg);
  } else {
    versions->max_rpc_version.major = 0;
    versions->max_rpc_version.minor = 0;
  }
  const grpc_gcp_RpcProtocolVersions_Version* min_version_msg =
      grpc_gcp_RpcProtocolVersions_min_rpc_version(value);
  if (min_version_msg != nullptr) {
    versions->min_rpc_version.major =
        grpc_gcp_RpcProtocolVersions_Version_major(min_version_msg);
    versions->min_rpc_version.minor =
        grpc_gcp_RpcProtocolVersions_Version_minor(min_version_msg);
  } else {
    versions->min_rpc_version.major = 0;
    versions->min_rpc_version.minor = 0;
  }
}

// Assigns protocol versions from C struct to upb message.
void grpc_gcp_RpcProtocolVersions_assign_from_struct(
    grpc_gcp_RpcProtocolVersions* versions, upb_Arena* arena,
    const grpc_gcp_rpc_protocol_versions* value) {
  grpc_gcp_RpcProtocolVersions_Version* max_version_msg =
      grpc_gcp_RpcProtocolVersions_mutable_max_rpc_version(versions, arena);
  grpc_gcp_RpcProtocolVersions_Version_set_major(max_version_msg,
                                                 value->max_rpc_version.major);
  grpc_gcp_RpcProtocolVersions_Version_set_minor(max_version_msg,
                                                 value->max_rpc_version.minor);
  grpc_gcp_RpcProtocolVersions_Version* min_version_msg =
      grpc_gcp_RpcProtocolVersions_mutable_min_rpc_version(versions, arena);
  grpc_gcp_RpcProtocolVersions_Version_set_major(min_version_msg,
                                                 value->min_rpc_version.major);
  grpc_gcp_RpcProtocolVersions_Version_set_minor(min_version_msg,
                                                 value->min_rpc_version.minor);
}

// Copies RPC protocol versions from src to dst.
// Returns true on success, false if only one of src or dst is nullptr.
bool grpc_gcp_rpc_protocol_versions_copy(
    const grpc_gcp_rpc_protocol_versions* src,
    grpc_gcp_rpc_protocol_versions* dst) {
  if ((src == nullptr && dst != nullptr) ||
      (src != nullptr && dst == nullptr)) {
    LOG(ERROR) << "Invalid arguments to grpc_gcp_rpc_protocol_versions_copy().";
    return false;
  }
  if (src == nullptr) {
    return true;
  }
  grpc_gcp_rpc_protocol_versions_set_max(dst, src->max_rpc_version.major,
                                         src->max_rpc_version.minor);
  grpc_gcp_rpc_protocol_versions_set_min(dst, src->min_rpc_version.major,
                                         src->min_rpc_version.minor);
  return true;
}

namespace grpc_core {
namespace internal {

// Compares two RPC protocol versions.
// Returns 1 if v1 > v2, -1 if v1 < v2, and 0 if they are equal.
int grpc_gcp_rpc_protocol_version_compare(
    const grpc_gcp_rpc_protocol_versions_version* v1,
    const grpc_gcp_rpc_protocol_versions_version* v2) {
  if ((v1->major > v2->major) ||
      (v1->major == v2->major && v1->minor > v2->minor)) {
    return 1;
  }
  if ((v1->major < v2->major) ||
      (v1->major == v2->major && v1->minor < v2->minor)) {
    return -1;
  }
  return 0;
}

}
}

// Checks compatibility between local and peer RPC protocol versions.
// If compatible, sets highest_common_version if not nullptr.
// Returns true if versions are compatible, false otherwise.
bool grpc_gcp_rpc_protocol_versions_check(
    const grpc_gcp_rpc_protocol_versions* local_versions,
    const grpc_gcp_rpc_protocol_versions* peer_versions,
    grpc_gcp_rpc_protocol_versions_version* highest_common_version) {
  if (local_versions == nullptr || peer_versions == nullptr) {
    LOG(ERROR)
        << "Invalid arguments to grpc_gcp_rpc_protocol_versions_check().";
    return false;
  }

  // Find the minimum of the two maximum versions
  const grpc_gcp_rpc_protocol_versions_version* max_common_version =
      grpc_core::internal::grpc_gcp_rpc_protocol_version_compare(
          &local_versions->max_rpc_version, &peer_versions->max_rpc_version) > 0
          ? &peer_versions->max_rpc_version
          : &local_versions->max_rpc_version;

  // Find the maximum of the two minimum versions
  const grpc_gcp_rpc_protocol_versions_version* min_common_version =
      grpc_core::internal::grpc_gcp_rpc_protocol_version_compare(
          &local_versions->min_rpc_version, &peer_versions->min_rpc_version) > 0
          ? &local_versions->min_rpc_version
          : &peer_versions->min_rpc_version;
  
  // Check if there's an overlap between version ranges
  bool result = grpc_core::internal::grpc_gcp_rpc_protocol_version_compare(
                    max_common_version, min_common_version) >= 0;
  if (result && highest_common_version != nullptr) {
    memcpy(highest_common_version, max_common_version,
           sizeof(grpc_gcp_rpc_protocol_versions_version));
  }
  return result;
}
```