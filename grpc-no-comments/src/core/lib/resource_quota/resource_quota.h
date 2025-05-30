// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_RESOURCE_QUOTA_H
#define GRPC_SRC_CORE_LIB_RESOURCE_QUOTA_RESOURCE_QUOTA_H

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/port_platform.h>

#include <string>
#include <utility>

#include "absl/strings/string_view.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/thread_quota.h"
#include "src/core/util/cpp_impl_of.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/useful.h"

namespace grpc_core {

class ResourceQuota;

using ResourceQuotaRefPtr = RefCountedPtr<ResourceQuota>;

class ResourceQuota : public RefCounted<ResourceQuota>,
                      public CppImplOf<ResourceQuota, grpc_resource_quota> {
 public:
  explicit ResourceQuota(std::string name);
  ~ResourceQuota() override;

  ResourceQuota(const ResourceQuota&) = delete;
  ResourceQuota& operator=(const ResourceQuota&) = delete;

  static absl::string_view ChannelArgName() { return GRPC_ARG_RESOURCE_QUOTA; }

  MemoryQuotaRefPtr memory_quota() { return memory_quota_; }

  const RefCountedPtr<ThreadQuota>& thread_quota() { return thread_quota_; }

  static ResourceQuotaRefPtr Default();

  static int ChannelArgsCompare(const ResourceQuota* a,
                                const ResourceQuota* b) {
    return QsortCompare(a, b);
  }

 private:
  MemoryQuotaRefPtr memory_quota_;
  RefCountedPtr<ThreadQuota> thread_quota_;
};

inline ResourceQuotaRefPtr MakeResourceQuota(std::string name) {
  return MakeRefCounted<ResourceQuota>(std::move(name));
}

}

#endif
