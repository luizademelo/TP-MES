// Copyright 2023 The gRPC Authors

#include "src/core/lib/event_engine/thread_local.h"

#include <grpc/support/port_platform.h>

namespace grpc_event_engine::experimental {

namespace {
thread_local bool g_thread_local{false};
}

void ThreadLocal::SetIsEventEngineThread(bool is) { g_thread_local = is; }
bool ThreadLocal::IsEventEngineThread() { return g_thread_local; }

}
