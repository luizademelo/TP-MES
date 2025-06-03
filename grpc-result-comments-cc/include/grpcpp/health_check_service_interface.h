Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_HEALTH_CHECK_SERVICE_INTERFACE_H
#define GRPCPP_HEALTH_CHECK_SERVICE_INTERFACE_H

// Include configuration support for gRPC
#include <grpcpp/support/config.h>

namespace grpc {

// Constant string used as an argument to identify the health check service interface
const char kHealthCheckServiceInterfaceArg[] =
    "grpc.health_check_service_interface";

// Abstract base class defining the interface for health check services in gRPC
class HealthCheckServiceInterface {
 public:
  // Virtual destructor to ensure proper cleanup of derived classes
  virtual ~HealthCheckServiceInterface() {}

  // Pure virtual function to set serving status for a specific service
  // Parameters:
  //   service_name: the name of the service whose status is being set
  //   serving: boolean indicating whether the service is serving (true) or not (false)
  virtual void SetServingStatus(const std::string& service_name,
                                bool serving) = 0;

  // Pure virtual function to set serving status for all services
  // Parameters:
  //   serving: boolean indicating whether all services are serving (true) or not (false)
  virtual void SetServingStatus(bool serving) = 0;

  // Virtual function to shutdown the health check service
  // Default implementation does nothing, can be overridden by derived classes
  virtual void Shutdown() {}
};

// Function to enable/disable the default health check service implementation
// Parameters:
//   enable: boolean to turn the service on (true) or off (false)
void EnableDefaultHealthCheckService(bool enable);

// Function to check if the default health check service is enabled
// Returns:
//   boolean indicating whether the default health check service is enabled (true) or not (false)
bool DefaultHealthCheckServiceEnabled();

}  // namespace grpc

#endif  // GRPCPP_HEALTH_CHECK_SERVICE_INTERFACE_H
```