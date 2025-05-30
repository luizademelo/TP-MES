
// Copyright 2017 gRPC authors.

#include "src/core/load_balancing/grpclb/grpclb_client_stats.h"

#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <string.h>

#include "src/core/util/sync.h"

namespace grpc_core {

void GrpcLbClientStats::AddCallStarted() {
  gpr_atm_full_fetch_add(&num_calls_started_, (gpr_atm)1);
}

void GrpcLbClientStats::AddCallFinished(
    bool finished_with_client_failed_to_send, bool finished_known_received) {
  gpr_atm_full_fetch_add(&num_calls_finished_, (gpr_atm)1);
  if (finished_with_client_failed_to_send) {
    gpr_atm_full_fetch_add(&num_calls_finished_with_client_failed_to_send_,
                           (gpr_atm)1);
  }
  if (finished_known_received) {
    gpr_atm_full_fetch_add(&num_calls_finished_known_received_, (gpr_atm)1);
  }
}

void GrpcLbClientStats::AddCallDropped(const char* token) {

  gpr_atm_full_fetch_add(&num_calls_started_, (gpr_atm)1);
  gpr_atm_full_fetch_add(&num_calls_finished_, (gpr_atm)1);

  MutexLock lock(&drop_count_mu_);
  if (drop_token_counts_ == nullptr) {
    drop_token_counts_ = std::make_unique<DroppedCallCounts>();
  }
  for (size_t i = 0; i < drop_token_counts_->size(); ++i) {
    if (strcmp((*drop_token_counts_)[i].token.get(), token) == 0) {
      ++(*drop_token_counts_)[i].count;
      return;
    }
  }

  drop_token_counts_->emplace_back(UniquePtr<char>(gpr_strdup(token)), 1);
}

namespace {

void AtomicGetAndResetCounter(int64_t* value, gpr_atm* counter) {
  *value = static_cast<int64_t>(gpr_atm_full_xchg(counter, (gpr_atm)0));
}

}

void GrpcLbClientStats::Get(
    int64_t* num_calls_started, int64_t* num_calls_finished,
    int64_t* num_calls_finished_with_client_failed_to_send,
    int64_t* num_calls_finished_known_received,
    std::unique_ptr<DroppedCallCounts>* drop_token_counts) {
  AtomicGetAndResetCounter(num_calls_started, &num_calls_started_);
  AtomicGetAndResetCounter(num_calls_finished, &num_calls_finished_);
  AtomicGetAndResetCounter(num_calls_finished_with_client_failed_to_send,
                           &num_calls_finished_with_client_failed_to_send_);
  AtomicGetAndResetCounter(num_calls_finished_known_received,
                           &num_calls_finished_known_received_);
  MutexLock lock(&drop_count_mu_);
  *drop_token_counts = std::move(drop_token_counts_);
}

}
