// Copyright 2021 gRPC authors.

#include "src/core/lib/resource_quota/thread_quota.h"

#include <grpc/support/port_platform.h>

#include "absl/log/check.h"

namespace grpc_core {

ThreadQuota::ThreadQuota() = default;

ThreadQuota::~ThreadQuota() = default;

void ThreadQuota::SetMax(size_t new_max) {
  MutexLock lock(&mu_);
  max_ = new_max;
}

bool ThreadQuota::Reserve(size_t num_threads) {
  MutexLock lock(&mu_);
  if (allocated_ + num_threads > max_) return false;
  allocated_ += num_threads;
  return true;
}

void ThreadQuota::Release(size_t num_threads) {
  MutexLock lock(&mu_);
  CHECK(num_threads <= allocated_);
  allocated_ -= num_threads;
}

}
