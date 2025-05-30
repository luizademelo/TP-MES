
// Copyright 2017 gRPC authors.

#ifndef GRPC_TEST_CPP_END2END_COUNTED_SERVICE_H
#define GRPC_TEST_CPP_END2END_COUNTED_SERVICE_H

#include "src/core/util/sync.h"

namespace grpc {
namespace testing {

template <typename ServiceType>
class CountedService : public ServiceType {
 public:
  size_t request_count() {
    grpc_core::MutexLock lock(&mu_);
    return request_count_;
  }

  size_t response_count() {
    grpc_core::MutexLock lock(&mu_);
    return response_count_;
  }

  void IncreaseResponseCount() {
    grpc_core::MutexLock lock(&mu_);
    ++response_count_;
  }
  void IncreaseRequestCount() {
    grpc_core::MutexLock lock(&mu_);
    ++request_count_;
  }

  void ResetCounters() {
    grpc_core::MutexLock lock(&mu_);
    request_count_ = 0;
    response_count_ = 0;
  }

 private:
  grpc_core::Mutex mu_;
  size_t request_count_ ABSL_GUARDED_BY(mu_) = 0;
  size_t response_count_ ABSL_GUARDED_BY(mu_) = 0;
};

}
}

#endif
