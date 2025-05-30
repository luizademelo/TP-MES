
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_WORK_SERIALIZER_H
#define GRPC_SRC_CORE_UTIL_WORK_SERIALIZER_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <functional>
#include <memory>

#include "absl/base/thread_annotations.h"
#include "absl/functional/any_invocable.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/orphanable.h"

namespace grpc_core {

class ABSL_LOCKABLE WorkSerializer {
 public:
  explicit WorkSerializer(
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>
          event_engine);
  ~WorkSerializer();

  WorkSerializer(const WorkSerializer&) = delete;
  WorkSerializer& operator=(const WorkSerializer&) = delete;
  WorkSerializer(WorkSerializer&&) noexcept = default;
  WorkSerializer& operator=(WorkSerializer&&) noexcept = default;

  void Run(absl::AnyInvocable<void()> callback, DebugLocation location = {});

#ifndef NDEBUG

  bool RunningInWorkSerializer() const;
#endif

 private:
  class WorkSerializerImpl;

  OrphanablePtr<WorkSerializerImpl> impl_;
};

}

#endif
