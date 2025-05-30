
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
template <typename T>
T ClampedAdd(std::atomic<T>& value, T delta, T min, T max) {
  T prev_value = value.load(std::memory_order_relaxed);
  T new_value;
  do {
    new_value = Clamp(SaturatingAdd(prev_value, delta), min, max);
  } while (!value.compare_exchange_weak(prev_value, new_value,
                                        std::memory_order_relaxed));
  return new_value;
}
}

ServerRetryThrottleData::ServerRetryThrottleData(uintptr_t max_milli_tokens,
                                                 uintptr_t milli_token_ratio,
                                                 uintptr_t milli_tokens)
    : max_milli_tokens_(max_milli_tokens),
      milli_token_ratio_(milli_token_ratio),
      milli_tokens_(milli_tokens) {}

ServerRetryThrottleData::~ServerRetryThrottleData() {
  ServerRetryThrottleData* replacement =
      replacement_.load(std::memory_order_acquire);
  if (replacement != nullptr) {
    replacement->Unref();
  }
}

void ServerRetryThrottleData::SetReplacement(
    RefCountedPtr<ServerRetryThrottleData> replacement) {
  replacement_.store(replacement.release(), std::memory_order_release);
}

void ServerRetryThrottleData::GetReplacementThrottleDataIfNeeded(
    ServerRetryThrottleData** throttle_data) {
  while (true) {
    ServerRetryThrottleData* new_throttle_data =
        (*throttle_data)->replacement_.load(std::memory_order_acquire);
    if (new_throttle_data == nullptr) return;
    *throttle_data = new_throttle_data;
  }
}

bool ServerRetryThrottleData::RecordFailure() {

  ServerRetryThrottleData* throttle_data = this;
  GetReplacementThrottleDataIfNeeded(&throttle_data);

  const uintptr_t new_value = ClampedAdd<intptr_t>(
      throttle_data->milli_tokens_, -1000, 0,
      std::min<uintptr_t>(throttle_data->max_milli_tokens_,
                          std::numeric_limits<intptr_t>::max()));

  return new_value > throttle_data->max_milli_tokens_ / 2;
}

void ServerRetryThrottleData::RecordSuccess() {

  ServerRetryThrottleData* throttle_data = this;
  GetReplacementThrottleDataIfNeeded(&throttle_data);

  ClampedAdd<intptr_t>(
      throttle_data->milli_tokens_, throttle_data->milli_token_ratio_, 0,
      std::max<intptr_t>(
          0, std::min<uintptr_t>(throttle_data->max_milli_tokens_,
                                 std::numeric_limits<intptr_t>::max())));
}

ServerRetryThrottleMap* ServerRetryThrottleMap::Get() {
  static ServerRetryThrottleMap* m = new ServerRetryThrottleMap();
  return m;
}

RefCountedPtr<ServerRetryThrottleData> ServerRetryThrottleMap::GetDataForServer(
    const std::string& server_name, uintptr_t max_milli_tokens,
    uintptr_t milli_token_ratio) {
  MutexLock lock(&mu_);
  auto& throttle_data = map_[server_name];
  if (throttle_data == nullptr ||
      throttle_data->max_milli_tokens() != max_milli_tokens ||
      throttle_data->milli_token_ratio() != milli_token_ratio) {

    auto old_throttle_data = std::move(throttle_data);
    uintptr_t initial_milli_tokens = max_milli_tokens;

    if (old_throttle_data != nullptr) {
      double token_fraction =
          static_cast<double>(old_throttle_data->milli_tokens()) /
          static_cast<double>(old_throttle_data->max_milli_tokens());
      initial_milli_tokens =
          static_cast<uintptr_t>(token_fraction * max_milli_tokens);
    }
    throttle_data = MakeRefCounted<ServerRetryThrottleData>(
        max_milli_tokens, milli_token_ratio, initial_milli_tokens);
    if (old_throttle_data != nullptr) {
      old_throttle_data->SetReplacement(throttle_data);
    }
  }
  return throttle_data;
}

}
}
