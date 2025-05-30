
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_SUPPORT_VALIDATE_SERVICE_CONFIG_H
#define GRPCPP_SUPPORT_VALIDATE_SERVICE_CONFIG_H

#include <grpcpp/support/config.h>

namespace grpc {

namespace experimental {

std::string ValidateServiceConfigJSON(const std::string& service_config_json);
}

}

#endif
