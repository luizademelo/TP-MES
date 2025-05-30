
// Copyright 2016 gRPC authors.

#ifndef GRPCPP_RESOURCE_QUOTA_H
#define GRPCPP_RESOURCE_QUOTA_H

struct grpc_resource_quota;

#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/support/config.h>

namespace grpc {

class ResourceQuota final : private grpc::internal::GrpcLibrary {
 public:

  explicit ResourceQuota(const std::string& name);
  ResourceQuota();
  ~ResourceQuota() override;

  ResourceQuota& Resize(size_t new_size);

  ResourceQuota& SetMaxThreads(int new_max_threads);

  grpc_resource_quota* c_resource_quota() const { return impl_; }

 private:
  ResourceQuota(const ResourceQuota& rhs);
  ResourceQuota& operator=(const ResourceQuota& rhs);

  grpc_resource_quota* const impl_;
};

}

#endif
