Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

// Includes necessary headers for authorization policy provider implementation
#include "src/core/lib/security/authorization/grpc_authorization_policy_provider.h"

#include <grpc/grpc_security.h>
#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <grpc/support/time.h>
#include <stdint.h>

#include <optional>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/security/authorization/grpc_authorization_engine.h"
#include "src/core/lib/security/authorization/rbac_policy.h"
#include "src/core/lib/security/authorization/rbac_translator.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/util/load_file.h"
#include "src/core/util/status_helper.h"

namespace grpc_core {

// Creates a static data authorization policy provider from the given policy string
absl::StatusOr<RefCountedPtr<grpc_authorization_policy_provider>>
StaticDataAuthorizationPolicyProvider::Create(absl::string_view authz_policy) {
  // First generate RBAC policies from the input string
  auto policies_or = GenerateRbacPolicies(authz_policy);
  if (!policies_or.ok()) {
    return policies_or.status();
  }
  // Create and return a new provider with the generated policies
  return MakeRefCounted<StaticDataAuthorizationPolicyProvider>(
      std::move(*policies_or));
}

// Constructor for static policy provider that initializes allow/deny engines
StaticDataAuthorizationPolicyProvider::StaticDataAuthorizationPolicyProvider(
    RbacPolicies policies)
    : allow_engine_(MakeRefCounted<GrpcAuthorizationEngine>(
          std::move(policies.allow_policy))),
      deny_engine_(policies.deny_policy.has_value()
                       ? MakeRefCounted<GrpcAuthorizationEngine>(
                             std::move(*policies.deny_policy))
                       : nullptr) {}

namespace {

// Helper function to read policy from a file
absl::StatusOr<std::string> ReadPolicyFromFile(absl::string_view policy_path) {
  auto policy_slice =
      LoadFile(std::string(policy_path), false);
  if (!policy_slice.ok()) {
    return absl::InvalidArgumentError(policy_slice.status().ToString());
  }
  return std::string(policy_slice->as_string_view());
}

// Helper function to convert seconds to deadline timestamp
gpr_timespec TimeoutSecondsToDeadline(int64_t seconds) {
  return gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                      gpr_time_from_seconds(seconds, GPR_TIMESPAN));
}

}  // namespace

// Creates a file watcher authorization policy provider that watches for policy changes
absl::StatusOr<RefCountedPtr<grpc_authorization_policy_provider>>
FileWatcherAuthorizationPolicyProvider::Create(
    absl::string_view authz_policy_path, unsigned int refresh_interval_sec) {
  // Validate input parameters
  CHECK(!authz_policy_path.empty());
  CHECK_GT(refresh_interval_sec, 0u);
  absl::Status status;
  // Create provider instance
  auto provider = MakeRefCounted<FileWatcherAuthorizationPolicyProvider>(
      authz_policy_path, refresh_interval_sec, &status);
  if (!status.ok()) return status;
  return provider;
}

// Constructor for file watcher policy provider
FileWatcherAuthorizationPolicyProvider::FileWatcherAuthorizationPolicyProvider(
    absl::string_view authz_policy_path, unsigned int refresh_interval_sec,
    absl::Status* status)
    : authz_policy_path_(std::string(authz_policy_path)),
      refresh_interval_sec_(refresh_interval_sec) {
  // Initialize shutdown event
  gpr_event_init(&shutdown_event_);

  // Perform initial policy load
  *status = ForceUpdate();
  if (!status->ok()) {
    return;
  }
  // Lambda function for the background refresh thread
  auto thread_lambda = [](void* arg) {
    WeakRefCountedPtr<FileWatcherAuthorizationPolicyProvider> provider(
        static_cast<FileWatcherAuthorizationPolicyProvider*>(arg));
    CHECK(provider != nullptr);
    while (true) {
      // Wait for either shutdown event or refresh interval timeout
      void* value = gpr_event_wait(
          &provider->shutdown_event_,
          TimeoutSecondsToDeadline(provider->refresh_interval_sec_));
      if (value != nullptr) {
        return;  // Shutdown signaled
      }
      // Perform policy update
      absl::Status status = provider->ForceUpdate();
      if (GRPC_TRACE_FLAG_ENABLED(grpc_authz_api) && !status.ok()) {
        LOG(ERROR) << "authorization policy reload status. code="
                   << static_cast<int>(status.code())
                   << " error_details=" << status.message();
      }
    }
  };
  // Create and start the refresh thread
  refresh_thread_ = std::make_unique<Thread>(
      "FileWatcherAuthorizationPolicyProvider_refreshing_thread", thread_lambda,
      WeakRef().release());
  refresh_thread_->Start();
}

// Sets a callback for testing purposes to be notified of policy changes
void FileWatcherAuthorizationPolicyProvider::SetCallbackForTesting(
    std::function<void(bool contents_changed, absl::Status status)> cb) {
  MutexLock lock(&mu_);
  cb_ = std::move(cb);
}

// Forces an update of the policy by reloading from file
absl::Status FileWatcherAuthorizationPolicyProvider::ForceUpdate() {
  bool contents_changed = false;
  // Helper lambda to handle early return with callback notification
  auto done_early = [&](absl::Status status) {
    MutexLock lock(&mu_);
    if (cb_ != nullptr) {
      cb_(contents_changed, status);
    }
    return status;
  };
  // Read policy file contents
  absl::StatusOr<std::string> file_contents =
      ReadPolicyFromFile(authz_policy_path_);
  if (!file_contents.ok()) {
    return done_early(file_contents.status());
  }
  // Check if contents actually changed
  if (file_contents_ == *file_contents) {
    return done_early(absl::OkStatus());
  }
  // Update stored contents
  file_contents_ = std::move(*file_contents);
  contents_changed = true;
  // Generate new RBAC policies
  auto rbac_policies_or = GenerateRbacPolicies(file_contents_);
  if (!rbac_policies_or.ok()) {
    return done_early(rbac_policies_or.status());
  }
  // Update authorization engines with new policies
  MutexLock lock(&mu_);
  allow_engine_ = MakeRefCounted<GrpcAuthorizationEngine>(
      std::move(rbac_policies_or->allow_policy));
  if (rbac_policies_or->deny_policy.has_value()) {
    deny_engine_ = MakeRefCounted<GrpcAuthorizationEngine>(
        std::move(*rbac_policies_or->deny_policy));
  } else {
    deny_engine_.reset();
  }
  // Notify callback if set
  if (cb_ != nullptr) {
    cb_(contents_changed, absl::OkStatus());
  }
  // Log successful update
  GRPC_TRACE_LOG(grpc_authz_api, INFO)
      << "authorization policy reload status: successfully loaded new "
         "policy\n"
      << file_contents_;
  return absl::OkStatus();
}

// Handles cleanup when provider is orphaned
void FileWatcherAuthorizationPolicyProvider::Orphaned() {
  // Signal shutdown to refresh thread
  gpr_event_set(&shutdown_event_, reinterpret_cast<void*>(1));
  if (refresh_thread_ != nullptr) {
    refresh_thread_->Join();
  }
}

}  // namespace grpc_core

// C API function to create static policy provider
grpc_authorization_policy_provider*
grpc_authorization_policy_provider_static_data_create(
    const char* authz_policy, grpc_status_code* code,
    const char** error_details) {
  CHECK_NE(authz_policy, nullptr);
  auto provider_or =
      grpc_core::StaticDataAuthorizationPolicyProvider::Create(authz_policy);
  if (!provider_or.ok()) {
    *code = static_cast<grpc_status_code>(provider_or.status().code());
    *error_details =
        gpr_strdup(std::string(provider_or.status().message()).c_str());
    return nullptr;
  }
  return provider_or->release();
}

// C API function to create file watcher policy provider
grpc_authorization_policy_provider*
grpc_authorization_policy_provider_file_watcher_create(
    const char* authz_policy_path, unsigned int refresh_interval_sec,
    grpc_status_code* code, const char** error_details) {
  CHECK_NE(authz_policy_path, nullptr);
  auto provider_or = grpc_core::FileWatcherAuthorizationPolicyProvider::Create(
      authz_policy_path, refresh_interval_sec);
  if (!provider_or.ok()) {
    *code = static_cast<grpc_status_code>(provider_or.status().code());
    *error_details =
        gpr_strdup(std::string(provider_or.status().message()).c_str());
    return nullptr;
  }
  return provider_or->release();
}

// C API function to release a policy provider
void grpc_authorization_policy_provider_release(
    grpc_authorization_policy_provider* provider) {
  if (provider != nullptr) provider->Unref();
}
```

The comments explain:
1. The overall purpose of each class and function
2. Key implementation details
3. The flow of operations
4. Important edge cases and error handling
5. The purpose of helper functions
6. Threading behavior in the file watcher implementation
7. The C API boundary functions

The comments are concise yet informative, providing enough context for future maintainers to understand the code without being overly verbose. They highlight the key aspects of the authorization policy provider implementation, including both the static and file-watching variants.