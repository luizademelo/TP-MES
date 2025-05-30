
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_RESOLVER_DNS_C_ARES_GRPC_ARES_EV_DRIVER_H
#define GRPC_SRC_CORE_RESOLVER_DNS_C_ARES_GRPC_ARES_EV_DRIVER_H

#include <ares.h>
#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/base/thread_annotations.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/resolver/dns/c_ares/grpc_ares_wrapper.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class GrpcPolledFd {
 public:
  virtual ~GrpcPolledFd() {}

  virtual void RegisterForOnReadableLocked(grpc_closure* read_closure)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&grpc_ares_request::mu) = 0;

  virtual void RegisterForOnWriteableLocked(grpc_closure* write_closure)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&grpc_ares_request::mu) = 0;

  virtual bool IsFdStillReadableLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&grpc_ares_request::mu) = 0;

  virtual void ShutdownLocked(grpc_error_handle error)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&grpc_ares_request::mu) = 0;

  virtual ares_socket_t GetWrappedAresSocketLocked()
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&grpc_ares_request::mu) = 0;

  virtual const char* GetName() const = 0;
};

class GrpcPolledFdFactory {
 public:
  virtual ~GrpcPolledFdFactory() {}

  virtual GrpcPolledFd* NewGrpcPolledFdLocked(
      ares_socket_t as, grpc_pollset_set* driver_pollset_set)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&grpc_ares_request::mu) = 0;

  virtual void ConfigureAresChannelLocked(ares_channel channel)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(&grpc_ares_request::mu) = 0;
};

std::unique_ptr<GrpcPolledFdFactory> NewGrpcPolledFdFactory(Mutex* mu);

}

#endif
