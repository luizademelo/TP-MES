
// Copyright 2016 gRPC authors.

#ifndef GRPCPP_EXT_HEALTH_CHECK_SERVICE_SERVER_BUILDER_OPTION_H
#define GRPCPP_EXT_HEALTH_CHECK_SERVICE_SERVER_BUILDER_OPTION_H

#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/impl/server_builder_option.h>
#include <grpcpp/support/config.h>

#include <memory>

namespace grpc {

class HealthCheckServiceServerBuilderOption : public ServerBuilderOption {
 public:

  explicit HealthCheckServiceServerBuilderOption(
      std::unique_ptr<HealthCheckServiceInterface> hc);
  ~HealthCheckServiceServerBuilderOption() override {}
  void UpdateArguments(ChannelArguments* args) override;
  void UpdatePlugins(
      std::vector<std::unique_ptr<ServerBuilderPlugin>>* plugins) override;

 private:
  std::unique_ptr<HealthCheckServiceInterface> hc_;
};

}

#endif
