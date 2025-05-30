
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_RESOLVER_RESOLVER_H
#define GRPC_SRC_CORE_RESOLVER_RESOLVER_H

#include <grpc/support/port_platform.h>

#include <functional>
#include <string>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/server_address.h"
#include "src/core/service_config/service_config.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

/// Note: All methods with a "Locked" suffix must be called from the

class Resolver : public InternallyRefCounted<Resolver> {
 public:

  struct Result {

    absl::StatusOr<EndpointAddressesList> addresses;

    absl::StatusOr<RefCountedPtr<ServiceConfig>> service_config = nullptr;

    std::string resolution_note;

    ChannelArgs args;

    std::function<void(absl::Status)> result_health_callback;
  };

  class ResultHandler {
   public:
    virtual ~ResultHandler() {}

    virtual void ReportResult(Result result) = 0;
  };

  Resolver(const Resolver&) = delete;
  Resolver& operator=(const Resolver&) = delete;
  ~Resolver() override = default;

  virtual void StartLocked() = 0;

  /// Note: Implementations must not invoke any method on the

  virtual void RequestReresolutionLocked() {}

  virtual void ResetBackoffLocked() {}

  // Note: This must be invoked while holding the work_serializer.
  void Orphan() override {
    ShutdownLocked();
    Unref();
  }

 protected:
  Resolver();

  virtual void ShutdownLocked() = 0;
};

}

#endif
