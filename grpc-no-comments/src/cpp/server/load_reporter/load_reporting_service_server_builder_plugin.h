
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_LOAD_REPORTER_LOAD_REPORTING_SERVICE_SERVER_BUILDER_PLUGIN_H
#define GRPC_SRC_CPP_SERVER_LOAD_REPORTER_LOAD_REPORTING_SERVICE_SERVER_BUILDER_PLUGIN_H

#include <grpc/support/port_platform.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/support/channel_arguments.h>

#include <memory>
#include <string>

#include "src/cpp/server/load_reporter/load_reporter_async_service_impl.h"

namespace grpc {
namespace load_reporter {

class LoadReportingServiceServerBuilderPlugin : public ServerBuilderPlugin {
 public:
  ~LoadReportingServiceServerBuilderPlugin() override = default;
  std::string name() override { return "load_reporting_service"; }

  void UpdateServerBuilder(ServerBuilder* builder) override;

  void InitServer(ServerInitializer* si) override;

  void Finish(ServerInitializer* si) override;

  void ChangeArguments(const std::string& , void* ) override {}
  void UpdateChannelArguments(grpc::ChannelArguments* ) override {}
  bool has_sync_methods() const override;
  bool has_async_methods() const override;

 private:
  std::shared_ptr<LoadReporterAsyncServiceImpl> service_;
};

std::unique_ptr<grpc::ServerBuilderPlugin>
CreateLoadReportingServiceServerBuilderPlugin();

}
}

#endif
