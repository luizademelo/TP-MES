// Copyright 2022 gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_SHIM_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_SHIM_H

#include <grpc/support/port_platform.h>

namespace grpc_event_engine::experimental {

bool UseEventEngineClient();

bool UseEventEngineListener();

bool UsePollsetAlternative();

bool EventEngineExperimentDisabledForPython();

}

#endif
