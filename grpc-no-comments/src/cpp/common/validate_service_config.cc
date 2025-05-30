
// Copyright 2019 gRPC authors.

#include <grpc/grpc.h>
#include <grpcpp/support/validate_service_config.h>

#include <string>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/service_config/service_config.h"
#include "src/core/service_config/service_config_impl.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc {
namespace experimental {
std::string ValidateServiceConfigJSON(const std::string& service_config_json) {
  grpc_init();
  auto service_config = grpc_core::ServiceConfigImpl::Create(
      grpc_core::ChannelArgs(), service_config_json.c_str());
  std::string return_value;
  if (!service_config.ok()) return_value = service_config.status().ToString();
  grpc_shutdown();
  return return_value;
}
}
}
