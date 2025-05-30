// Copyright 2025 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_IOMGR_COMPATIBLE_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_IOMGR_COMPATIBLE_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include "absl/functional/any_invocable.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace grpc_event_engine::experimental {

class IomgrCompatibleListener {
 public:
  virtual ~IomgrCompatibleListener() = default;
  static absl::string_view EndpointExtensionName() {
    return "io.grpc.event_engine.extension.iomgr_compatible_listener";
  }

  virtual void Shutdown() = 0;
};

}

#endif
