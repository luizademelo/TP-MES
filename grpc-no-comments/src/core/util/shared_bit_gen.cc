// Copyright 2025 gRPC authors.

#include "src/core/util/shared_bit_gen.h"

namespace grpc_core {

thread_local absl::BitGen SharedBitGen::bit_gen_;

}
