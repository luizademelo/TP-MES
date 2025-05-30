
// Copyright 2016 gRPC authors.

#include <grpcpp/ext/health_check_service_server_builder_option.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/support/channel_arguments.h>

#include <memory>
#include <utility>
#include <vector>

namespace grpc {

HealthCheckServiceServerBuilderOption::HealthCheckServiceServerBuilderOption(
    std::unique_ptr<HealthCheckServiceInterface> hc)
    : hc_(std::move(hc)) {}

void HealthCheckServiceServerBuilderOption::UpdateArguments(
    ChannelArguments* args) {
  args->SetPointer(kHealthCheckServiceInterfaceArg, hc_.release());
}

void HealthCheckServiceServerBuilderOption::UpdatePlugins(
    std::vector<std::unique_ptr<ServerBuilderPlugin>>* ) {}

}
