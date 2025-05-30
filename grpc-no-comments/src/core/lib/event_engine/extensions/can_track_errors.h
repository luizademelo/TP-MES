// Copyright 2024 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_CAN_TRACK_ERRORS_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_CAN_TRACK_ERRORS_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"

namespace grpc_event_engine::experimental {

class EndpointCanTrackErrorsExtension {
 public:
  virtual ~EndpointCanTrackErrorsExtension() = default;
  static absl::string_view EndpointExtensionName() {
    return "io.grpc.event_engine.extension.can_track_errors";
  }

  virtual bool CanTrackErrors() = 0;
};

}

#endif
