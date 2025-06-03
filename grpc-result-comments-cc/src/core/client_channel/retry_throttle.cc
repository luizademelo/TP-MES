Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#include "src/core/client_channel/retry_throttle.h"

#include <grpc/support/port_platform.h>

#include <atomic>
#include <cstdint>
#include <limits>
#include <map>
#include <string>
#include <utility>

#include "src/core/util/useful.h"

namespace grpc_core {
namespace internal {

namespace {
// Helper function that performs a thread-safe clamped addition on an atomic value
// Parameters:
//   value: Atomic reference to the value to modify
//   delta: Amount to add/subtract
//   min: Minimum allowed value (clamp lower bound)
//   max: Maximum allowed value (clamp upper bound)
// Returns: The new value after the clamped addition
template <typename T>
T ClampedAdd(std::atomic<T>& value, T delta, T min, T max) {
  T prev_value = value.load(std::memory_order_relaxed);
  T new_value;
  do {
    // Calculate new value by adding delta and clamping between min/max
    new_value = Clamp(SaturatingAdd(prev_value, delta), min, max);
    // Attempt to update the value atomically
  } while (!value.compare_exchange_weak(prev_value, new_value,
                                        std::memory_order_relaxed));
  return new_value;
}
}

// Constructor for ServerRetryThrottleData
// Parameters:
//   max_milli_tokens: Maximum allowed tokens (in millitokens)
//   milli_token_ratio: Ratio for token replenishment (in millitokens)
//   milli_tokens: Initial token count (in millitokens)
ServerRetryThrottleData::ServerRetryThrottleData(uintptr_t max_milli_tokens,
                                                 uintptr_t milli_token_ratio,
                                                 uintptr_t milli_tokens)
    : max_milli_tokens_(max_milli_tokens),
      milli_token_ratio_(milli_token_ratio),
      milli_tokens_(milli_tokens) {}

// Destructor for ServerRetryThrottleData
// Handles cleanup of replacement throttle data if it exists
ServerRetryThrottleData::~ServerRetryThrottleData() {
  ServerRetryThrottleData* replacement =
      replacement_.load(std::memory_order_acquire);
  if (replacement != nullptr) {
    replacement->Unref();
  }
}

// Sets a replacement throttle data object
// Parameters:
//   replacement: The new throttle data to replace this one with
void ServerRetryThrottleData::SetReplacement(
    RefCountedPtr<ServerRetryThrottleData> replacement) {
  replacement_.store(replacement.release(), std::memory_order_release);
}

// Gets the most recent replacement throttle data if one exists
// Parameters:
//   throttle_data: Pointer to the current throttle data (will be updated if replacement exists)
void ServerRetryThrottleData::GetReplacementThrottleDataIfNeeded(
    ServerRetryThrottleData** throttle_data) {
  while (true) {
    ServerRetryThrottleData* new_throttle_data =
        (*throttle_data)->replacement_.load(std::memory_order_acquire);
    if (new_throttle_data == nullptr) return;
    *throttle_data = new_throttle_data;
  }
}

// Records a failure event by decrementing the token count
// Returns: true if retries should be throttled (token count below half of max)
bool ServerRetryThrottleData::RecordFailure() {
  // Get the most current throttle data
  ServerRetryThrottleData* throttle_data = this;
  GetReplacementThrottleDataIfNeeded(&throttle_data);

  // Decrement tokens by 1000 millitokens (1 token), clamped between 0 and max
  const uintptr_t new_value = ClampedAdd<intptr_t>(
      throttle_data->milli_tokens_, -1000, 0,
      std::min<uintptr_t>(throttle_data->max_milli_tokens_,
                          std::numeric_limits<intptr_t>::max()));

  // Throttle retries if tokens are below half of maximum
  return new_value > throttle_data->max_milli_tokens_ / 2;
}

// Records a success event by incrementing the token count
void ServerRetryThrottleData::RecordSuccess() {
  // Get the most current throttle data
  ServerRetryThrottleData* throttle_data = this;
  GetReplacementThrottleDataIfNeeded(&throttle_data);

  // Increment tokens by the configured ratio, clamped between 0 and max
  ClampedAdd<intptr_t>(
      throttle_data->milli_tokens_, throttle_data->milli_token_ratio_, 0,
      std::max<intptr_t>(
          0, std::min<uintptr_t>(throttle_data->max_milli_tokens_,
                                 std::numeric_limits<intptr_t>::max())));
}

// Returns the singleton instance of ServerRetryThrottleMap
ServerRetryThrottleMap* ServerRetryThrottleMap::Get() {
  static ServerRetryThrottleMap* m = new ServerRetryThrottleMap();
  return m;
}

// Gets or creates throttle data for a specific server
// Parameters:
//   server_name: Name of the server to get throttle data for
//   max_milli_tokens: Maximum allowed tokens for new throttle data
//   milli_token_ratio: Replenishment ratio for new throttle data
// Returns: RefCountedPtr to the throttle data for the server
RefCountedPtr<ServerRetryThrottleData> ServerRetryThrottleMap::GetDataForServer(
    const std::string& server_name, uintptr_t max_milli_tokens,
    uintptr_t milli_token_ratio) {
  MutexLock lock(&mu_);
  auto& throttle_data = map_[server_name];
  // Check if we need to create new throttle data (either doesn't exist or params changed)
  if (throttle_data == nullptr ||
      throttle_data->max_milli_tokens() != max_milli_tokens ||
      throttle_data->milli_token_ratio() != milli_token_ratio) {

    auto old_throttle_data = std::move(throttle_data);
    uintptr_t initial_milli_tokens = max_milli_tokens;

    // If there was existing throttle data, scale its token count proportionally
    if (old_throttle_data != nullptr) {
      double token_fraction =
          static_cast<double>(old_throttle_data->milli_tokens()) /
          static_cast<double>(old_throttle_data->max_milli_tokens());
      initial_milli_tokens =
          static_cast<uintptr_t>(token_fraction * max_milli_tokens);
    }
    // Create new throttle data
    throttle_data = MakeRefCounted<ServerRetryThrottleData>(
        max_milli_tokens, milli_token_ratio, initial_milli_tokens);
    // Set the new data as replacement for the old one
    if (old_throttle_data != nullptr) {
      old_throttle_data->SetReplacement(throttle_data);
    }
  }
  return throttle_data;
}

}
}
```