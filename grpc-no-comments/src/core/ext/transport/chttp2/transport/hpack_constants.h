// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HPACK_CONSTANTS_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_HPACK_CONSTANTS_H

#include <grpc/support/port_platform.h>

#include <cstddef>
#include <cstdint>

namespace grpc_core {
namespace hpack_constants {

static constexpr uint32_t kEntryOverhead = 32;

static constexpr uint32_t kInitialTableSize = 4096;

static constexpr uint32_t kLastStaticEntry = 61;

static constexpr uint32_t EntriesForBytes(uint32_t bytes) noexcept {
  return (bytes + kEntryOverhead - 1) / kEntryOverhead;
}

static constexpr size_t SizeForEntry(size_t key_length,
                                     size_t value_length) noexcept {
  return key_length + value_length + kEntryOverhead;
}

static constexpr uint32_t kInitialTableEntries =
    EntriesForBytes(kInitialTableSize);
}
}

#endif
