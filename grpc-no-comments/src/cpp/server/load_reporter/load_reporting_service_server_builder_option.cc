
// Copyright 2018 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/ext/server_load_reporting.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/support/channel_arguments.h>

#include <algorithm>
#include <memory>
#include <vector>

#include "src/cpp/server/load_reporter/load_reporting_service_server_builder_plugin.h"

namespace grpc {
namespace load_reporter {
namespace experimental {

void LoadReportingServiceServerBuilderOption::UpdateArguments(
    grpc::ChannelArguments* args) {
  args->SetInt(GRPC_ARG_ENABLE_LOAD_REPORTING, true);
}

void LoadReportingServiceServerBuilderOption::UpdatePlugins(
    std::vector<std::unique_ptr<grpc::ServerBuilderPlugin>>* plugins) {
  plugins->emplace_back(
      new grpc::load_reporter::LoadReportingServiceServerBuilderPlugin());
}

}
}
}
