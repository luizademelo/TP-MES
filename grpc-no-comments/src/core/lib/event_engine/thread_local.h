// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_THREAD_LOCAL_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_THREAD_LOCAL_H
#include <grpc/support/port_platform.h>

namespace grpc_event_engine::experimental {

class ThreadLocal {
 public:
  static void SetIsEventEngineThread(bool is_local);
  static bool IsEventEngineThread();
};

}

#endif
