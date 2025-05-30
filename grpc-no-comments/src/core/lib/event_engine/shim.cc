// Copyright 2022 gRPC authors.

#include "src/core/lib/event_engine/shim.h"

#include <grpc/support/port_platform.h>

#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/port.h"

namespace grpc_event_engine::experimental {

bool UseEventEngineClient() {
#if defined(GRPC_DO_NOT_INSTANTIATE_POSIX_POLLER)
  return false;
#endif
  return grpc_core::IsEventEngineClientEnabled();
}

bool UseEventEngineListener() {
#if defined(GRPC_DO_NOT_INSTANTIATE_POSIX_POLLER)
  return false;
#endif
  return grpc_core::IsEventEngineListenerEnabled();
}

bool UsePollsetAlternative() {
  return UseEventEngineClient() && UseEventEngineListener() &&
         grpc_core::IsPollsetAlternativeEnabled();
}

bool EventEngineExperimentDisabledForPython() {
#ifdef GRPC_DO_NOT_INSTANTIATE_POSIX_POLLER
  return true;
#else
  return false;
#endif
}

}
