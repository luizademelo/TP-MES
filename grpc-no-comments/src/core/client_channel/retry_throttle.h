
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_RETRY_THROTTLE_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_RETRY_THROTTLE_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <atomic>
#include <map>
#include <string>

#include "absl/base/thread_annotations.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {
namespace internal {

class ServerRetryThrottleMap;

class ServerRetryThrottleData final
    : public RefCounted<ServerRetryThrottleData> {
 public:
  ServerRetryThrottleData(uintptr_t max_milli_tokens,
                          uintptr_t milli_token_ratio, uintptr_t milli_tokens);
  ~ServerRetryThrottleData() override;

  bool RecordFailure();

  void RecordSuccess();

  uintptr_t max_milli_tokens() const { return max_milli_tokens_; }
  uintptr_t milli_token_ratio() const { return milli_token_ratio_; }
  intptr_t milli_tokens() const {
    return milli_tokens_.load(std::memory_order_relaxed);
  }

 private:
  friend ServerRetryThrottleMap;

  void SetReplacement(RefCountedPtr<ServerRetryThrottleData> replacement);

  void GetReplacementThrottleDataIfNeeded(
      ServerRetryThrottleData** throttle_data);

  const uintptr_t max_milli_tokens_;
  const uintptr_t milli_token_ratio_;
  std::atomic<intptr_t> milli_tokens_;

  std::atomic<ServerRetryThrottleData*> replacement_{nullptr};
};

class ServerRetryThrottleMap final {
 public:
  static ServerRetryThrottleMap* Get();

  RefCountedPtr<ServerRetryThrottleData> GetDataForServer(
      const std::string& server_name, uintptr_t max_milli_tokens,
      uintptr_t milli_token_ratio);

 private:
  using StringToDataMap =
      std::map<std::string, RefCountedPtr<ServerRetryThrottleData>>;

  Mutex mu_;
  StringToDataMap map_ ABSL_GUARDED_BY(mu_);
};

}
}

#endif
