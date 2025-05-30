// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_GRPC_AUTHORIZATION_POLICY_PROVIDER_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_GRPC_AUTHORIZATION_POLICY_PROVIDER_H

#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>

#include <functional>
#include <memory>
#include <string>

#include "absl/base/thread_annotations.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/security/authorization/authorization_engine.h"
#include "src/core/lib/security/authorization/authorization_policy_provider.h"
#include "src/core/lib/security/authorization/rbac_translator.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/thd.h"

namespace grpc_core {

class StaticDataAuthorizationPolicyProvider
    : public grpc_authorization_policy_provider {
 public:
  static absl::StatusOr<RefCountedPtr<grpc_authorization_policy_provider>>
  Create(absl::string_view authz_policy);

  explicit StaticDataAuthorizationPolicyProvider(RbacPolicies policies);

  AuthorizationEngines engines() override {
    return {allow_engine_, deny_engine_};
  }

  void Orphaned() override {}

 private:
  RefCountedPtr<AuthorizationEngine> allow_engine_;
  RefCountedPtr<AuthorizationEngine> deny_engine_;
};

class FileWatcherAuthorizationPolicyProvider
    : public grpc_authorization_policy_provider {
 public:
  static absl::StatusOr<RefCountedPtr<grpc_authorization_policy_provider>>
  Create(absl::string_view authz_policy_path,
         unsigned int refresh_interval_sec);

  FileWatcherAuthorizationPolicyProvider(absl::string_view authz_policy_path,
                                         unsigned int refresh_interval_sec,
                                         absl::Status* status);

  void SetCallbackForTesting(
      std::function<void(bool contents_changed, absl::Status Status)> cb);

  void Orphaned() override;

  AuthorizationEngines engines() override {
    MutexLock lock(&mu_);
    return {allow_engine_, deny_engine_};
  }

 private:

  absl::Status ForceUpdate();

  std::string authz_policy_path_;
  std::string file_contents_;
  unsigned int refresh_interval_sec_;

  std::unique_ptr<Thread> refresh_thread_;
  gpr_event shutdown_event_;

  Mutex mu_;

  std::function<void(bool contents_changed, absl::Status status)> cb_
      ABSL_GUARDED_BY(mu_) = nullptr;

  RefCountedPtr<AuthorizationEngine> allow_engine_ ABSL_GUARDED_BY(mu_);
  RefCountedPtr<AuthorizationEngine> deny_engine_ ABSL_GUARDED_BY(mu_);
};

}

#endif
