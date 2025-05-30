
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_EXT_SERVER_LOAD_REPORTING_H
#define GRPCPP_EXT_SERVER_LOAD_REPORTING_H

#include <grpc/load_reporting.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/impl/server_builder_option.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/config.h>

namespace grpc {
namespace load_reporter {
namespace experimental {

class LoadReportingServiceServerBuilderOption
    : public grpc::ServerBuilderOption {
 public:
  void UpdateArguments(grpc::ChannelArguments* args) override;
  void UpdatePlugins(std::vector<std::unique_ptr<grpc::ServerBuilderPlugin>>*
                         plugins) override;
};

void AddLoadReportingCost(grpc::ServerContext* ctx,
                          const std::string& cost_name, double cost_value);

}
}
}

#endif
