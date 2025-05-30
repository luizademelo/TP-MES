// Copyright 2024 gRPC authors.

#include "src/core/call/call_arena_allocator.h"

#include <grpc/support/port_platform.h>

#include <algorithm>

namespace grpc_core {

void CallArenaAllocator::FinalizeArena(Arena* arena) {
  call_size_estimator_.UpdateCallSizeEstimate(arena->TotalUsedBytes());
}

}
