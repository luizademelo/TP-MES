// Copyright 2023 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_MEMORY_ALLOCATOR_FACTORY_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_MEMORY_ALLOCATOR_FACTORY_H
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <utility>

#include "absl/strings/string_view.h"
#include "src/core/lib/resource_quota/memory_quota.h"

namespace grpc_event_engine::experimental {

class MemoryQuotaBasedMemoryAllocatorFactory : public MemoryAllocatorFactory {
 public:
  explicit MemoryQuotaBasedMemoryAllocatorFactory(
      grpc_core::MemoryQuotaRefPtr memory_quota)
      : memory_quota_(std::move(memory_quota)) {}

  MemoryAllocator CreateMemoryAllocator(absl::string_view name) override {
    return memory_quota_->CreateMemoryAllocator(name);
  }

 private:
  grpc_core::MemoryQuotaRefPtr memory_quota_;
};

}

#endif
