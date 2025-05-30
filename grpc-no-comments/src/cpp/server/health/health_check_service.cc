
// Copyright 2016 gRPC authors.

#include <grpcpp/health_check_service_interface.h>

namespace grpc {
namespace {
bool g_grpc_default_health_check_service_enabled = false;
}

bool DefaultHealthCheckServiceEnabled() {
  return g_grpc_default_health_check_service_enabled;
}

void EnableDefaultHealthCheckService(bool enable) {
  g_grpc_default_health_check_service_enabled = enable;
}

}
