// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_SHARED_BIT_GEN_H
#define GRPC_SRC_CORE_UTIL_SHARED_BIT_GEN_H

#include "absl/random/random.h"

namespace grpc_core {

class SharedBitGen {
 public:
  SharedBitGen() = default;
  SharedBitGen(const SharedBitGen&) = delete;
  SharedBitGen& operator=(const SharedBitGen&) = delete;
  SharedBitGen(SharedBitGen&&) = default;
  SharedBitGen& operator=(SharedBitGen&&) = default;

  using result_type = absl::BitGen::result_type;
  result_type operator()() { return bit_gen_(); }

  static constexpr auto min() { return absl::BitGen::min(); }
  static constexpr auto max() { return absl::BitGen::max(); }

 private:

  static thread_local absl::BitGen bit_gen_;
};

}

#endif
