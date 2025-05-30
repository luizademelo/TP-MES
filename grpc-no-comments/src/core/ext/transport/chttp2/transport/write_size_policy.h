// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_WRITE_SIZE_POLICY_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_WRITE_SIZE_POLICY_H

#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include "src/core/util/time.h"

namespace grpc_core {

class Chttp2WriteSizePolicy {
 public:

  static constexpr size_t MinTarget() { return 32 * 1024; }

  static constexpr size_t MaxTarget() { return 16 * 1024 * 1024; }

  static constexpr Duration FastWrite() { return Duration::Milliseconds(100); }

  static constexpr Duration SlowWrite() { return Duration::Seconds(1); }

  static constexpr Duration TargetWriteTime() {
    return Duration::Milliseconds(300);
  }

  size_t WriteTargetSize();

  void BeginWrite(size_t size);

  void EndWrite(bool success);

 private:
  size_t current_target_ = 128 * 1024;
  Timestamp experiment_start_time_ = Timestamp::InfFuture();

  int8_t state_ = 0;
};

}

#endif
