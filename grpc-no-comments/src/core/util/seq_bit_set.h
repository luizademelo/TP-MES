// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_SEQ_BIT_SET_H
#define GRPC_SRC_CORE_UTIL_SEQ_BIT_SET_H

#include <cstdint>
#include <set>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"

namespace grpc_core {

class SeqBitSet {
 public:

  bool Set(uint64_t seq);
  bool IsSet(uint64_t seq) const;

  template <typename Sink>
  friend void AbslStringify(Sink& out, SeqBitSet sbs) {
    std::set<uint64_t> rest = sbs.far_future_bits_;
    for (size_t i = 0; i < kNumFutureBitEntries; i++) {
      for (int j = 0; j < 64; j++) {
        if (sbs.future_bits_[i] & (1ull << j)) {
          rest.insert(sbs.epoch_ + i * 64 + j);
        }
      }
    }
    out.Append(absl::StrCat("epoch:", sbs.epoch_, " set:{",
                            absl::StrJoin(rest, ","), "}"));
  }

 private:
  static constexpr std::size_t kNumFutureBitEntries = 3;

  uint64_t epoch_ = 0;
  uint64_t future_bits_[kNumFutureBitEntries] = {0, 0, 0};
  std::set<uint64_t> far_future_bits_;
};

}

#endif
