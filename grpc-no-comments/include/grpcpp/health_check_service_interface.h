
// Copyright 2016 gRPC authors.

#ifndef GRPCPP_HEALTH_CHECK_SERVICE_INTERFACE_H
#define GRPCPP_HEALTH_CHECK_SERVICE_INTERFACE_H

#include <grpcpp/support/config.h>

namespace grpc {

const char kHealthCheckServiceInterfaceArg[] =
    "grpc.health_check_service_interface";

class HealthCheckServiceInterface {
 public:
  virtual ~HealthCheckServiceInterface() {}

  virtual void SetServingStatus(const std::string& service_name,
                                bool serving) = 0;

  virtual void SetServingStatus(bool serving) = 0;

  virtual void Shutdown() {}
};

void EnableDefaultHealthCheckService(bool enable);

bool DefaultHealthCheckServiceEnabled();

}

#endif
