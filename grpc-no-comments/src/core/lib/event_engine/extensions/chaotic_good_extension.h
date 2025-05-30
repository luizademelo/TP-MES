// Copyright 2024 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_CHAOTIC_GOOD_EXTENSION_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_EXTENSIONS_CHAOTIC_GOOD_EXTENSION_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"
#include "src/core/lib/resource_quota/memory_quota.h"

namespace grpc_event_engine::experimental {

class ChaoticGoodExtension {
 public:
  virtual ~ChaoticGoodExtension() = default;
  static absl::string_view EndpointExtensionName() {
    return "io.grpc.event_engine.extension.chaotic_good_extension";
  }

  virtual void EnableStatsCollection(bool is_control_channel) = 0;

  virtual void UseMemoryQuota(grpc_core::MemoryQuotaRefPtr mem_quota) = 0;

  virtual void EnableRpcReceiveCoalescing() = 0;

  virtual void DisableRpcReceiveCoalescing() = 0;

  virtual void EnforceRxMemoryAlignment() = 0;
};

}

#endif
