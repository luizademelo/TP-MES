
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_GRPCLB_GRPCLB_CLIENT_STATS_H
#define GRPC_SRC_CORE_LOAD_BALANCING_GRPCLB_GRPCLB_CLIENT_STATS_H

#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <memory>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/container/inlined_vector.h"
#include "src/core/util/memory.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class GrpcLbClientStats final : public RefCounted<GrpcLbClientStats> {
 public:
  struct DropTokenCount {
    UniquePtr<char> token;
    int64_t count;

    DropTokenCount(UniquePtr<char> token, int64_t count)
        : token(std::move(token)), count(count) {}
  };

  typedef absl::InlinedVector<DropTokenCount, 10> DroppedCallCounts;

  void AddCallStarted();
  void AddCallFinished(bool finished_with_client_failed_to_send,
                       bool finished_known_received);

  void AddCallDropped(const char* token);

  void Get(int64_t* num_calls_started, int64_t* num_calls_finished,
           int64_t* num_calls_finished_with_client_failed_to_send,
           int64_t* num_calls_finished_known_received,
           std::unique_ptr<DroppedCallCounts>* drop_token_counts);

  static void Destroy(void* arg) {
    static_cast<GrpcLbClientStats*>(arg)->Unref();
  }

 private:
  gpr_atm num_calls_started_ = 0;
  gpr_atm num_calls_finished_ = 0;
  gpr_atm num_calls_finished_with_client_failed_to_send_ = 0;
  gpr_atm num_calls_finished_known_received_ = 0;
  Mutex drop_count_mu_;
  std::unique_ptr<DroppedCallCounts> drop_token_counts_
      ABSL_GUARDED_BY(drop_count_mu_);
};

}

#endif
