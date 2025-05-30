
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_GCP_ENVIRONMENT_AUTODETECT_H
#define GRPC_SRC_CPP_EXT_GCP_ENVIRONMENT_AUTODETECT_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "src/core/util/sync.h"

namespace grpc {

namespace internal {

absl::Status GcpObservabilityInit();

class EnvironmentAutoDetect {
 public:
  struct ResourceType {

    std::string resource_type;

    std::map<std::string, std::string> labels;
  };

  static EnvironmentAutoDetect& Get();

  explicit EnvironmentAutoDetect(std::string project_id);

  void NotifyOnDone(absl::AnyInvocable<void()> callback);

  const ResourceType* resource() {
    grpc_core::MutexLock lock(&mu_);
    return resource_.get();
  }

 private:
  friend absl::Status grpc::internal::GcpObservabilityInit();

  static void Create(std::string project_id);

  const std::string project_id_;
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_;
  grpc_core::Mutex mu_;
  std::unique_ptr<ResourceType> resource_ ABSL_GUARDED_BY(mu_);
  std::vector<absl::AnyInvocable<void()>> callbacks_ ABSL_GUARDED_BY(mu_);
};

}
}

#endif
