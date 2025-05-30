
// Copyright 2023 gRPC authors.

#include "src/core/util/uuid_v4.h"

#include <grpc/support/port_platform.h>

#include "absl/strings/str_format.h"

namespace grpc_core {

std::string GenerateUUIDv4(uint64_t hi, uint64_t lo) {
  uint32_t time_low = hi >> 32;
  uint16_t time_mid = hi >> 16;
  uint16_t time_hi_and_version = (hi & 0x0fff) | 0x4000;
  uint16_t clock_seq_hi_low = ((lo >> 48) & 0x3fff) | 0x8000;
  uint64_t node = lo & 0xffffffffffff;
  return absl::StrFormat("%08x-%04x-%04x-%04x-%012x", time_low, time_mid,
                         time_hi_and_version, clock_seq_hi_low, node);
}

}
