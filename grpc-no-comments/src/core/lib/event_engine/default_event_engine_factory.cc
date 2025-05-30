// Copyright 2022 The gRPC Authors

#include "src/core/lib/event_engine/default_event_engine_factory.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <memory>

#if defined(GPR_WINDOWS)
#include "src/core/lib/event_engine/windows/windows_engine.h"

namespace grpc_event_engine::experimental {

std::shared_ptr<EventEngine> DefaultEventEngineFactory() {
  return std::make_shared<WindowsEventEngine>();
}

}
#elif defined(GRPC_CFSTREAM)
#include "src/core/lib/event_engine/cf_engine/cf_engine.h"

namespace grpc_event_engine::experimental {

std::shared_ptr<EventEngine> DefaultEventEngineFactory() {
  return std::make_shared<CFEventEngine>();
}

}
#else
#include "src/core/lib/event_engine/posix_engine/posix_engine.h"

namespace grpc_event_engine::experimental {

std::shared_ptr<EventEngine> DefaultEventEngineFactory() {
  return PosixEventEngine::MakePosixEventEngine();
}

}

#endif
