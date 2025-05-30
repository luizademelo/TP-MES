
// Copyright 2018 gRPC authors.

#ifndef GRPC_TEST_CPP_END2END_TEST_HEALTH_CHECK_SERVICE_IMPL_H
#define GRPC_TEST_CPP_END2END_TEST_HEALTH_CHECK_SERVICE_IMPL_H

#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>

#include <map>
#include <mutex>

#include "src/proto/grpc/health/v1/health.grpc.pb.h"

namespace grpc {
namespace testing {

class HealthCheckServiceImpl : public health::v1::Health::Service {
 public:
  Status Check(ServerContext* context,
               const health::v1::HealthCheckRequest* request,
               health::v1::HealthCheckResponse* response) override;
  Status Watch(ServerContext* context,
               const health::v1::HealthCheckRequest* request,
               ServerWriter<health::v1::HealthCheckResponse>* writer) override;
  void SetStatus(const std::string& service_name,
                 health::v1::HealthCheckResponse::ServingStatus status);
  void SetAll(health::v1::HealthCheckResponse::ServingStatus status);

  void Shutdown();

 private:
  std::mutex mu_;
  bool shutdown_ = false;
  std::map<const std::string, health::v1::HealthCheckResponse::ServingStatus>
      status_map_;
};

}
}

#endif
