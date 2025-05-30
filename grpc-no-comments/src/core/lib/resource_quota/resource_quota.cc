// Copyright 2021 gRPC authors.

#include "src/core/lib/resource_quota/resource_quota.h"

#include <grpc/support/port_platform.h>

namespace grpc_core {

ResourceQuota::ResourceQuota(std::string name)
    : memory_quota_(MakeMemoryQuota(std::move(name))),
      thread_quota_(MakeRefCounted<ThreadQuota>()) {}

ResourceQuota::~ResourceQuota() = default;

ResourceQuotaRefPtr ResourceQuota::Default() {
  static auto default_resource_quota =
      MakeResourceQuota("default_resource_quota").release();
  return default_resource_quota->Ref();
}

}
