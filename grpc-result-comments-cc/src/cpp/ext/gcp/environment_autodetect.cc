Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/cpp/ext/gcp/environment_autodetect.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <grpcpp/impl/grpc_library.h>

#include <memory>
#include <optional>
#include <utility>

#include "absl/container/flat_hash_map.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/util/crash.h"
#include "src/core/util/env.h"
#include "src/core/util/gcp_metadata_query.h"
#include "src/core/util/load_file.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/time.h"

namespace grpc {
namespace internal {

namespace {

// Gets the namespace name from Kubernetes service account file or environment variable
std::string GetNamespaceName() {
  // Default Kubernetes namespace file location
  const char* filename =
      "/var/run/secrets/kubernetes.io/serviceaccount/namespace";
  auto namespace_name = grpc_core::LoadFile(filename, false);
  if (!namespace_name.ok()) {
    GRPC_TRACE_VLOG(environment_autodetect, 2)
        << "Reading file " << filename
        << " failed: " << grpc_core::StatusToString(namespace_name.status());

    // Fallback to environment variable if file read fails
    return grpc_core::GetEnv("NAMESPACE_NAME").value_or("");
  }
  return std::string(reinterpret_cast<const char*>((*namespace_name).begin()),
                     (*namespace_name).length());
}

// Gets the pod name from environment variables (POD_NAME or HOSTNAME)
std::string GetPodName() {
  auto pod_name = grpc_core::GetEnv("POD_NAME");
  if (pod_name.has_value()) {
    return pod_name.value();
  }
  // Fallback to HOSTNAME if POD_NAME is not set
  return grpc_core::GetEnv("HOSTNAME").value_or("");
}

// Gets the container name from HOSTNAME environment variable
std::string GetContainerName() {
  return grpc_core::GetEnv("HOSTNAME").value_or("");
}

// Gets the function name from environment variables (K_SERVICE or FUNCTION_NAME)
std::string GetFunctionName() {
  auto k_service = grpc_core::GetEnv("K_SERVICE");
  if (k_service.has_value()) {
    return k_service.value();
  }
  return grpc_core::GetEnv("FUNCTION_NAME").value_or("");
}

// Gets the revision name from K_REVISION environment variable
std::string GetRevisionName() {
  return grpc_core::GetEnv("K_REVISION").value_or("");
}

// Gets the service name from K_SERVICE environment variable
std::string GetServiceName() {
  return grpc_core::GetEnv("K_SERVICE").value_or("");
}

// Gets the configuration name from K_CONFIGURATION environment variable
std::string GetConfiguratioName() {
  return grpc_core::GetEnv("K_CONFIGURATION").value_or("");
}

// Gets the module ID from GAE_SERVICE environment variable
std::string GetModuleId() {
  return grpc_core::GetEnv("GAE_SERVICE").value_or("");
}

// Gets the version ID from GAE_VERSION environment variable
std::string GetVersionId() {
  return grpc_core::GetEnv("GAE_VERSION").value_or("");
}

// Helper class for auto-detecting GCP environment attributes
class EnvironmentAutoDetectHelper
    : public grpc_core::InternallyRefCounted<EnvironmentAutoDetectHelper>,
      private internal::GrpcLibrary {
 public:
  // Constructor initializes polling infrastructure and starts auto-detection
  EnvironmentAutoDetectHelper(
      std::string project_id,
      absl::AnyInvocable<void(EnvironmentAutoDetect::ResourceType)> on_done,
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>
          event_engine)
      : InternallyRefCounted(nullptr, 2),
        project_id_(std::move(project_id)),
        on_done_(std::move(on_done)),
        event_engine_(std::move(event_engine)) {
    grpc_core::ExecCtx exec_ctx;

    // Initialize pollset for async operations
    pollset_ = static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
    grpc_pollset_init(pollset_, &mu_poll_);
    pollent_ = grpc_polling_entity_create_from_pollset(pollset_);

    // Start polling loop and auto-detection
    event_engine_->Run([this] { PollLoop(); });
    AutoDetect();
  }

  // Destructor cleans up polling infrastructure
  ~EnvironmentAutoDetectHelper() override {
    grpc_core::ExecCtx exec_ctx;
    grpc_pollset_shutdown(
        pollset_, GRPC_CLOSURE_CREATE(
                      [](void* arg, absl::Status ) {
                        grpc_pollset_destroy(static_cast<grpc_pollset*>(arg));
                        gpr_free(arg);
                      },
                      pollset_, nullptr));
  }

  // Orphan is not allowed for this class
  void Orphan() override {
    grpc_core::Crash("Illegal Orphan() call on EnvironmentAutoDetectHelper.");
  }

 private:
  // Structure for mapping resource attributes to metadata server attributes
  struct Attribute {
    std::string resource_attribute;
    std::string metadata_server_atttribute;
  };

  // Polling loop for async operations
  void PollLoop() {
    grpc_core::ExecCtx exec_ctx;
    bool done = false;
    gpr_mu_lock(mu_poll_);
    grpc_pollset_worker* worker = nullptr;
    if (!GRPC_LOG_IF_ERROR(
            "pollset_work",
            grpc_pollset_work(grpc_polling_entity_pollset(&pollent_), &worker,
                              grpc_core::Timestamp::InfPast()))) {
      notify_poller_ = true;
    }
    done = notify_poller_;
    gpr_mu_unlock(mu_poll_);
    if (!done) {
      // Schedule next poll if not done
      event_engine_->RunAfter(grpc_core::Duration::Milliseconds(100),
                              [this] { PollLoop(); });
    } else {
      Unref();
    }
  }

  // Main auto-detection logic
  void AutoDetect() {
    grpc_core::MutexLock lock(&mu_);

    // Always include project ID
    resource_.labels.emplace("project_id", project_id_);
    
    // Detect Kubernetes environment
    if (grpc_core::GetEnv("KUBERNETES_SERVICE_HOST").has_value()) {
      resource_.resource_type = "k8s_container";
      resource_.labels.emplace("namespace_name", GetNamespaceName());
      resource_.labels.emplace("pod_name", GetPodName());
      resource_.labels.emplace("container_name", GetContainerName());
      attributes_to_fetch_.emplace(grpc_core::GcpMetadataQuery::kZoneAttribute,
                                   "location");
      attributes_to_fetch_.emplace(
          grpc_core::GcpMetadataQuery::kClusterNameAttribute, "cluster_name");
    }
    // Detect Cloud Function environment
    else if (grpc_core::GetEnv("FUNCTION_NAME").has_value() ||
             grpc_core::GetEnv("FUNCTION_TARGET").has_value()) {
      resource_.resource_type = "cloud_function";
      resource_.labels.emplace("function_name", GetFunctionName());
      attributes_to_fetch_.emplace(
          grpc_core::GcpMetadataQuery::kRegionAttribute, "region");
    }
    // Detect Cloud Run environment
    else if (grpc_core::GetEnv("K_CONFIGURATION").has_value()) {
      resource_.resource_type = "cloud_run_revision";
      resource_.labels.emplace("revision_name", GetRevisionName());
      resource_.labels.emplace("service_name", GetServiceName());
      resource_.labels.emplace("configuration_name", GetConfiguratioName());
      attributes_to_fetch_.emplace(
          grpc_core::GcpMetadataQuery::kRegionAttribute, "location");
    }
    // Detect App Engine environment
    else if (grpc_core::GetEnv("GAE_SERVICE").has_value()) {
      resource_.resource_type = "gae_app";
      resource_.labels.emplace("module_id", GetModuleId());
      resource_.labels.emplace("version_id", GetVersionId());
      attributes_to_fetch_.emplace(grpc_core::GcpMetadataQuery::kZoneAttribute,
                                   "zone");
    }
    // Default to GCE instance if no other environment detected
    else {
      assuming_gce_ = true;
      resource_.resource_type = "gce_instance";
      attributes_to_fetch_.emplace(
          grpc_core::GcpMetadataQuery::kInstanceIdAttribute, "instance_id");
      attributes_to_fetch_.emplace(grpc_core::GcpMetadataQuery::kZoneAttribute,
                                   "zone");
    }
    FetchMetadataServerAttributesAsynchronouslyLocked();
  }

  // Fetches additional attributes from GCP metadata server
  void FetchMetadataServerAttributesAsynchronouslyLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    CHECK(!attributes_to_fetch_.empty());
    for (auto& element : attributes_to_fetch_) {
      queries_.push_back(grpc_core::MakeOrphanable<grpc_core::GcpMetadataQuery>(
          element.first, &pollent_,
          [this](std::string attribute, absl::StatusOr<std::string> result) {
            GRPC_TRACE_LOG(environment_autodetect, INFO)
                << "Environment AutoDetect: Attribute: \"" << attribute
                << "\" Result: \""
                << (result.ok() ? result.value()
                                : grpc_core::StatusToString(result.status()))
                << "\"";
            std::optional<EnvironmentAutoDetect::ResourceType> resource;
            {
              grpc_core::MutexLock lock(&mu_);
              auto it = attributes_to_fetch_.find(attribute);
              if (it != attributes_to_fetch_.end()) {
                if (result.ok()) {
                  // Add successful result to resource labels
                  resource_.labels.emplace(std::move(it->second),
                                           std::move(result).value());
                }
                // Fallback to global resource if GCE detection fails
                else if (assuming_gce_) {
                  GRPC_TRACE_LOG(environment_autodetect, INFO)
                      << "Environment Autodetect: Falling back to "
                      << "global resource type";
                  assuming_gce_ = false;
                  resource_.resource_type = "global";
                }
                attributes_to_fetch_.erase(it);
              } else {
                // Log unexpected attributes
                LOG(ERROR) << "An unexpected attribute was seen from the "
                              "MetadataServer: "
                           << attribute;
              }
              // If all attributes fetched, prepare to return resource
              if (attributes_to_fetch_.empty()) {
                resource = std::move(resource_);
              }
            }
            if (resource.has_value()) {
              // Notify poller and call completion callback
              gpr_mu_lock(mu_poll_);
              notify_poller_ = true;
              gpr_mu_unlock(mu_poll_);
              auto on_done = std::move(on_done_);
              Unref();
              on_done(std::move(resource).value());
            }
          },
          grpc_core::Duration::Seconds(10)));
    }
  }

  // Member variables
  const std::string project_id_;
  grpc_pollset* pollset_ = nullptr;
  grpc_polling_entity pollent_;
  gpr_mu* mu_poll_ = nullptr;
  absl::AnyInvocable<void(EnvironmentAutoDetect::ResourceType)> on_done_;
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_;
  grpc_core::Mutex mu_;
  bool notify_poller_ = false;
  absl::flat_hash_map<std::string ,
                      std::string >
      attributes_to_fetch_ ABSL_GUARDED_BY(mu_);
  std::vector<grpc_core::OrphanablePtr<grpc_core::GcpMetadataQuery>> queries_
      ABSL_GUARDED_BY(mu_);
  EnvironmentAutoDetect::ResourceType resource_ ABSL_GUARDED_BY(mu_);
  bool assuming_gce_ ABSL_GUARDED_BY(mu_) = false;
};

// Global instance of auto-detector
EnvironmentAutoDetect* g_autodetect = nullptr;

}

// Creates the global environment auto-detector instance
void EnvironmentAutoDetect::Create(std::string project_id) {
  CHECK_EQ(g_autodetect, nullptr);
  CHECK(!project_id.empty());

  g_autodetect = new EnvironmentAutoDetect(project_id);
}

// Returns the global environment auto-detector instance
EnvironmentAutoDetect& EnvironmentAutoDetect::Get() { return *g_autodetect; }

// Constructor for EnvironmentAutoDetect
EnvironmentAutoDetect::EnvironmentAutoDetect(std::string project_id)
    : project_id_(std::move(project_id)) {
  CHECK(!project_id_.empty());
}

// Registers a callback to be notified when auto-detection is complete
void EnvironmentAutoDetect::NotifyOnDone(absl::AnyInvocable<void()> callback) {
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine;
  {
    grpc_core::MutexLock lock(&mu_);

    // If detection already complete, execute callback immediately
    if (resource_ != nullptr) {
      return event_engine_->Run(std::move(callback));
    }
    callbacks_.push_back(std::move(callback));

    // Initialize event engine if not already done
    if (event_engine_ == nullptr) {
      event_engine_ = grpc_event_engine::experimental::GetDefaultEventEngine();
      event_engine = event_engine_;
    }
  }
  if (event_engine) {
    // Start auto-detection process
    new EnvironmentAutoDetectHelper(
        project_id_,
        [this](EnvironmentAutoDetect::ResourceType resource) {
          std::vector<absl::AnyInvocable<void()>> callbacks;
          {
            grpc_core::MutexLock lock(&mu_);
            resource_ = std::make_unique<EnvironmentAutoDetect::ResourceType>(
                std::move(resource));
            callbacks = std::move(callbacks_);
          }
          // Execute all registered callbacks
          for (auto& callback : callbacks) {
            callback();
          }
        },
        std::move(event_engine));
  }
}

}
}
```

The comments explain:
1. The purpose of each function and class
2. The logic flow of environment detection
3. The different environment types detected (Kubernetes, Cloud Functions, Cloud Run, App Engine, GCE)
4. The async polling mechanism
5. The metadata query process
6. The callback notification system
7. Important implementation details

The comments are designed to help future developers understand:
- How the auto-detection works
- The different environment types supported
- The async nature of the implementation
- The resource attribute collection process
- The error handling and fallback behavior