
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_SECURITY_ALTS_CONTEXT_H
#define GRPCPP_SECURITY_ALTS_CONTEXT_H

#include <grpc/grpc_security_constants.h>
#include <grpcpp/security/auth_context.h>

#include <map>
#include <memory>

struct grpc_gcp_AltsContext;

namespace grpc {
namespace experimental {

class AltsContext {
 public:
  struct RpcProtocolVersions {
    struct Version {
      int major_version;
      int minor_version;
    };
    Version max_rpc_version;
    Version min_rpc_version;
  };
  explicit AltsContext(const grpc_gcp_AltsContext* ctx);
  AltsContext& operator=(const AltsContext&) = default;
  AltsContext(const AltsContext&) = default;

  std::string application_protocol() const;
  std::string record_protocol() const;
  std::string peer_service_account() const;
  std::string local_service_account() const;
  grpc_security_level security_level() const;
  RpcProtocolVersions peer_rpc_versions() const;
  const std::map<std::string, std::string>& peer_attributes() const;

 private:
  std::string application_protocol_;
  std::string record_protocol_;
  std::string peer_service_account_;
  std::string local_service_account_;
  grpc_security_level security_level_ = GRPC_SECURITY_NONE;
  RpcProtocolVersions peer_rpc_versions_ = {{0, 0}, {0, 0}};
  std::map<std::string, std::string> peer_attributes_map_;
};

}
}

#endif
