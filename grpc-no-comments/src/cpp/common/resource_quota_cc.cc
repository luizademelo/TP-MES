
// Copyright 2016 gRPC authors.

#include <grpc/grpc.h>
#include <grpcpp/resource_quota.h>
#include <stddef.h>

#include <string>

namespace grpc {

ResourceQuota::ResourceQuota() : impl_(grpc_resource_quota_create(nullptr)) {}

ResourceQuota::ResourceQuota(const std::string& name)
    : impl_(grpc_resource_quota_create(name.c_str())) {}

ResourceQuota::~ResourceQuota() { grpc_resource_quota_unref(impl_); }

ResourceQuota& ResourceQuota::Resize(size_t new_size) {
  grpc_resource_quota_resize(impl_, new_size);
  return *this;
}

ResourceQuota& ResourceQuota::SetMaxThreads(int new_max_threads) {
  grpc_resource_quota_set_max_threads(impl_, new_max_threads);
  return *this;
}
}
