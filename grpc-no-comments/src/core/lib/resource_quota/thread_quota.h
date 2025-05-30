// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_THREAD_QUOTA_H
#define GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_THREAD_QUOTA_H

#include <grpc/support/port_platform.h>

#include <cstddef>
#include <limits>

#include "absl/base/thread_annotations.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class ThreadQuota : public RefCounted<ThreadQuota> {
 public:
  ThreadQuota();
  ~ThreadQuota() override;

  ThreadQuota(const ThreadQuota&) = delete;
  ThreadQuota& operator=(const ThreadQuota&) = delete;

  void SetMax(size_t new_max);

  bool Reserve(size_t num_threads);

  void Release(size_t num_threads);

 private:
  Mutex mu_;
  size_t allocated_ ABSL_GUARDED_BY(mu_) = 0;
  size_t max_ ABSL_GUARDED_BY(mu_) = std::numeric_limits<size_t>::max();
};

using ThreadQuotaPtr = RefCountedPtr<ThreadQuota>;

}

#endif
