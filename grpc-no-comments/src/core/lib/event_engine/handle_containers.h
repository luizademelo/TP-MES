// Copyright 2022 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_HANDLE_CONTAINERS_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_HANDLE_CONTAINERS_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <cstdint>
#include <utility>

#include "absl/container/flat_hash_set.h"
#include "absl/hash/hash.h"

namespace grpc_event_engine::experimental {

template <typename TaskHandle>
struct TaskHandleComparator {
  struct Hash {
    using HashType = std::pair<const intptr_t, const intptr_t>;
    using is_transparent = void;
    size_t operator()(const TaskHandle& handle) const {
      return absl::Hash<HashType>()({handle.keys[0], handle.keys[1]});
    }
  };
};

using TaskHandleSet =
    absl::flat_hash_set<EventEngine::TaskHandle,
                        TaskHandleComparator<EventEngine::TaskHandle>::Hash>;

using ConnectionHandleSet = absl::flat_hash_set<
    EventEngine::ConnectionHandle,
    TaskHandleComparator<EventEngine::ConnectionHandle>::Hash>;

}

#endif
