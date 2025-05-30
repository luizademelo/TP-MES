// Copyright 2021 gRPC authors.

#include <grpc/grpc_security.h>
#include <grpc/status.h>
#include <grpc/support/alloc.h>
#include <grpcpp/security/authorization_policy_provider.h>
#include <grpcpp/support/status.h>

#include <memory>
#include <string>

namespace grpc {
namespace experimental {

std::shared_ptr<StaticDataAuthorizationPolicyProvider>
StaticDataAuthorizationPolicyProvider::Create(const std::string& authz_policy,
                                              grpc::Status* status) {
  grpc_status_code code = GRPC_STATUS_OK;
  const char* error_details;
  grpc_authorization_policy_provider* provider =
      grpc_authorization_policy_provider_static_data_create(
          authz_policy.c_str(), &code, &error_details);
  if (code != GRPC_STATUS_OK) {
    *status = grpc::Status(static_cast<grpc::StatusCode>(code), error_details);
    gpr_free(const_cast<char*>(error_details));
    return nullptr;
  }
  *status = grpc::Status();
  return std::make_shared<StaticDataAuthorizationPolicyProvider>(provider);
}

StaticDataAuthorizationPolicyProvider::
    ~StaticDataAuthorizationPolicyProvider() {
  grpc_authorization_policy_provider_release(c_provider_);
}

std::shared_ptr<FileWatcherAuthorizationPolicyProvider>
FileWatcherAuthorizationPolicyProvider::Create(
    const std::string& authz_policy_path, unsigned int refresh_interval_sec,
    grpc::Status* status) {
  grpc_status_code code = GRPC_STATUS_OK;
  const char* error_details;
  grpc_authorization_policy_provider* provider =
      grpc_authorization_policy_provider_file_watcher_create(
          authz_policy_path.c_str(), refresh_interval_sec, &code,
          &error_details);
  if (code != GRPC_STATUS_OK) {
    *status = grpc::Status(static_cast<grpc::StatusCode>(code), error_details);
    gpr_free(const_cast<char*>(error_details));
    return nullptr;
  }
  return std::make_shared<FileWatcherAuthorizationPolicyProvider>(provider);
}

FileWatcherAuthorizationPolicyProvider::
    ~FileWatcherAuthorizationPolicyProvider() {
  grpc_authorization_policy_provider_release(c_provider_);
}

}
}
