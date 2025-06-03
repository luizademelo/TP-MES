Here's the commented version of the code:

```c++
// Copyright 2025 gRPC authors.

#include "src/core/util/seq_bit_set.h"

#include <limits>

namespace grpc_core {

// Checks if a sequence number is marked as set in the bit set
// Args:
//   seq: The sequence number to check
// Returns:
//   true if the sequence number is set, false otherwise
bool SeqBitSet::IsSet(uint64_t seq) const {
  // Sequence numbers before the current epoch are always considered set
  if (seq < epoch_) return true;
  
  // For sequence numbers far in the future, check the far_future_bits_ set
  if (seq >= epoch_ + kNumFutureBitEntries * 64) {
    return far_future_bits_.count(seq) != 0;
  }
  
  // For sequence numbers in the near future, calculate which bit to check
  const std::size_t index = (seq - epoch_) / 64;  // Determine which 64-bit chunk
  const uint64_t offset = (seq - epoch_) % 64;    // Determine which bit in the chunk
  return (future_bits_[index] & (1ull << offset)) != 0;  // Check the specific bit
}

// Sets a sequence number in the bit set
// Args:
//   seq: The sequence number to set
// Returns:
//   true if the sequence number was already set, false otherwise
bool SeqBitSet::Set(uint64_t seq) {
  // Sequence numbers before current epoch are always considered already set
  if (seq < epoch_) return true;
  
  // For sequence numbers far in the future, add to far_future_bits_ set
  if (seq >= epoch_ + kNumFutureBitEntries * 64) {
    return !far_future_bits_.insert(seq).second;  // Returns true if already present
  }
  
  // For sequence numbers in the near future, calculate position and set bit
  const std::size_t index = (seq - epoch_) / 64;  // Determine which 64-bit chunk
  const uint64_t offset = (seq - epoch_) % 64;    // Determine which bit in the chunk
  const bool was_set = (future_bits_[index] & (1ull << offset)) != 0;  // Check if already set
  future_bits_[index] |= (1ull << offset);  // Set the bit
  
  // If we modified the first chunk, we might need to shift the epoch forward
  if (index != 0) return was_set;
  
  // While the first chunk is completely full (all bits set), shift epoch forward
  while (future_bits_[0] == std::numeric_limits<uint64_t>::max()) {
    epoch_ += 64;  // Move epoch forward by a chunk
    
    // Shift all chunks left by one position
    for (std::size_t i = 0; i < kNumFutureBitEntries - 1; ++i) {
      future_bits_[i] = future_bits_[i + 1];
    }
    future_bits_[kNumFutureBitEntries - 1] = 0;  // Clear the last chunk
    
    // Check if any far-future sequences now fall into our new range
    auto it = far_future_bits_.begin();
    const uint64_t new_last_future_bits_epoch =
        epoch_ + (kNumFutureBitEntries - 1) * 64;
    
    // Move sequences that are now in range from far_future_bits_ to future_bits_
    while (it != far_future_bits_.end() &&
           *it < new_last_future_bits_epoch + 64) {
      future_bits_[kNumFutureBitEntries - 1] |=
          1ull << (*it - new_last_future_bits_epoch);
      ++it;
    }
    far_future_bits_.erase(far_future_bits_.begin(), it);  // Remove moved sequences
  }
  
  return was_set;
}

}  // namespace grpc_core
```

The comments explain:
1. The overall purpose of each method
2. The logic for handling sequence numbers in different ranges (past, near future, far future)
3. The bit manipulation operations
4. The epoch shifting mechanism
5. The interaction between the near-future bits and far-future bits storage
6. The return value semantics

The comments are placed to help future developers understand both the high-level behavior and the implementation details of this sequence bit set implementation.