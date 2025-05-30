// Copyright 2025 gRPC authors.

#include "src/core/util/seq_bit_set.h"

#include <limits>

namespace grpc_core {

bool SeqBitSet::IsSet(uint64_t seq) const {
  if (seq < epoch_) return true;
  if (seq >= epoch_ + kNumFutureBitEntries * 64) {
    return far_future_bits_.count(seq) != 0;
  }
  const std::size_t index = (seq - epoch_) / 64;
  const uint64_t offset = (seq - epoch_) % 64;
  return (future_bits_[index] & (1ull << offset)) != 0;
}

bool SeqBitSet::Set(uint64_t seq) {
  if (seq < epoch_) return true;
  if (seq >= epoch_ + kNumFutureBitEntries * 64) {
    return !far_future_bits_.insert(seq).second;
  }
  const std::size_t index = (seq - epoch_) / 64;
  const uint64_t offset = (seq - epoch_) % 64;
  const bool was_set = (future_bits_[index] & (1ull << offset)) != 0;
  future_bits_[index] |= (1ull << offset);
  if (index != 0) return was_set;
  while (future_bits_[0] == std::numeric_limits<uint64_t>::max()) {
    epoch_ += 64;
    for (std::size_t i = 0; i < kNumFutureBitEntries - 1; ++i) {
      future_bits_[i] = future_bits_[i + 1];
    }
    future_bits_[kNumFutureBitEntries - 1] = 0;
    auto it = far_future_bits_.begin();
    const uint64_t new_last_future_bits_epoch =
        epoch_ + (kNumFutureBitEntries - 1) * 64;
    while (it != far_future_bits_.end() &&
           *it < new_last_future_bits_epoch + 64) {
      future_bits_[kNumFutureBitEntries - 1] |=
          1ull << (*it - new_last_future_bits_epoch);
      ++it;
    }
    far_future_bits_.erase(far_future_bits_.begin(), it);
  }
  return was_set;
}

}
