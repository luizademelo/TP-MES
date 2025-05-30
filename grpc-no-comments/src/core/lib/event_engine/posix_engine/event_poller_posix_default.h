// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_EVENT_POLLER_POSIX_DEFAULT_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_EVENT_POLLER_POSIX_DEFAULT_H

#include <grpc/support/port_platform.h>

#include <memory>

namespace grpc_event_engine::experimental {

class PosixEventPoller;
class Scheduler;

std::shared_ptr<PosixEventPoller> MakeDefaultPoller(Scheduler* scheduler);

}

#endif
