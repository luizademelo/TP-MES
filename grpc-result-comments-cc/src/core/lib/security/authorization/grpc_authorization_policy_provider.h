Here's the commented version of the code:

```c++
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

// Implementation of authorization policy provider that uses static policy data.
// This provider doesn't support policy updates after initialization.
class StaticDataAuthorizationPolicyProvider
    : public grpc_authorization_policy_provider {
 public:
  // Creates a new provider instance from the given authorization policy string.
  // Returns StatusOr with either the provider or an error status.
  static absl::StatusOr<RefCountedPtr<grpc_authorization_policy_provider>>
  Create(absl::string_view authz_policy);

  // Constructs provider with pre-parsed RBAC policies.
  explicit StaticDataAuthorizationPolicyProvider(RbacPolicies policies);

  // Returns the pair of authorization engines (allow and deny) used for
  // evaluating requests against the policy.
  AuthorizationEngines engines() override {
    return {allow_engine_, deny_engine_};
  }

  // Cleanup method called when provider is no longer needed.
  // No-op for static provider as it doesn't maintain any resources.
  void Orphaned() override {}

 private:
  // Authorization engines for allow and deny rules respectively
  RefCountedPtr<AuthorizationEngine> allow_engine_;
  RefCountedPtr<AuthorizationEngine> deny_engine_;
};

// Implementation of authorization policy provider that watches a policy file
// for changes and automatically reloads the policy when the file changes.
class FileWatcherAuthorizationPolicyProvider
    : public grpc_authorization_policy_provider {
 public:
  // Creates a new provider instance that watches the given policy file path
  // and refreshes at the specified interval (in seconds).
  // Returns StatusOr with either the provider or an error status.
  static absl::StatusOr<RefCountedPtr<grpc_authorization_policy_provider>>
  Create(absl::string_view authz_policy_path,
         unsigned int refresh_interval_sec);

  // Constructs provider with file path and refresh interval.
  // Initializes the policy from file and starts the watcher thread.
  // Populates status with any initialization errors.
  FileWatcherAuthorizationPolicyProvider(absl::string_view authz_policy_path,
                                       unsigned int refresh_interval_sec,
                                       absl::Status* status);

  // Sets a callback for testing purposes that gets notified when file
  // contents change or when errors occur during refresh.
  void SetCallbackForTesting(
      std::function<void(bool contents_changed, absl::Status Status)> cb);

  // Cleanup method called when provider is no longer needed.
  // Stops the watcher thread and releases resources.
  void Orphaned() override;

  // Returns the current pair of authorization engines (allow and deny).
  // Thread-safe as engines can be updated by the watcher thread.
  AuthorizationEngines engines() override {
    MutexLock lock(&mu_);
    return {allow_engine_, deny_engine_};
  }

 private:
  // Forces an immediate policy update from file, bypassing the refresh interval.
  // Used for initialization and testing.
  absl::Status ForceUpdate();

  // Path to the authorization policy file being watched
  std::string authz_policy_path_;
  // Last read contents of the policy file (used for change detection)
  std::string file_contents_;
  // Interval in seconds between file checks
  unsigned int refresh_interval_sec_;

  // Thread that periodically checks for file updates
  std::unique_ptr<Thread> refresh_thread_;
  // Event used to signal thread shutdown
  gpr_event shutdown_event_;

  // Mutex protecting access to engines and callback
  Mutex mu_;

  // Optional callback for testing notifications
  std::function<void(bool contents_changed, absl::Status status)> cb_
      ABSL_GUARDED_BY(mu_) = nullptr;

  // Authorization engines for allow and deny rules respectively
  // Protected by mu_ as they can be updated by the watcher thread
  RefCountedPtr<AuthorizationEngine> allow_engine_ ABSL_GUARDED_BY(mu_);
  RefCountedPtr<AuthorizationEngine> deny_engine_ ABSL_GUARDED_BY(mu_);
};

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_GRPC_AUTHORIZATION_POLICY_PROVIDER_H
```