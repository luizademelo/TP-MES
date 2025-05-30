// Copyright 2021 The gRPC Authors

#ifndef GRPC_EVENT_ENGINE_INTERNAL_MEMORY_ALLOCATOR_IMPL_H
#define GRPC_EVENT_ENGINE_INTERNAL_MEMORY_ALLOCATOR_IMPL_H

#include <grpc/event_engine/memory_request.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>

#include <algorithm>
#include <memory>
#include <type_traits>
#include <vector>

namespace grpc_event_engine {
namespace experimental {

namespace internal {

class MemoryAllocatorImpl
    : public std::enable_shared_from_this<MemoryAllocatorImpl> {
 public:
  MemoryAllocatorImpl() {}
  virtual ~MemoryAllocatorImpl() {}

  MemoryAllocatorImpl(const MemoryAllocatorImpl&) = delete;
  MemoryAllocatorImpl& operator=(const MemoryAllocatorImpl&) = delete;

  virtual size_t Reserve(MemoryRequest request) = 0;

  virtual grpc_slice MakeSlice(MemoryRequest request) = 0;

  virtual void Release(size_t n) = 0;

  virtual void Shutdown() = 0;
};

}

}
}

#endif
