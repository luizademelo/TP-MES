
// Copyright 2018 gRPC authors.

#include "src/cpp/server/load_reporter/load_reporting_service_server_builder_plugin.h"

#include <grpc/support/port_platform.h>
#include <grpcpp/impl/server_initializer.h>
#include <grpcpp/server_builder.h>

#include <utility>

namespace grpc {
namespace load_reporter {

bool LoadReportingServiceServerBuilderPlugin::has_sync_methods() const {
  if (service_ != nullptr) {
    return service_->has_synchronous_methods();
  }
  return false;
}

bool LoadReportingServiceServerBuilderPlugin::has_async_methods() const {
  if (service_ != nullptr) {
    return service_->has_async_methods();
  }
  return false;
}

void LoadReportingServiceServerBuilderPlugin::UpdateServerBuilder(
    grpc::ServerBuilder* builder) {
  auto cq = builder->AddCompletionQueue();
  service_ = std::make_shared<LoadReporterAsyncServiceImpl>(std::move(cq));
}

void LoadReportingServiceServerBuilderPlugin::InitServer(
    grpc::ServerInitializer* si) {
  si->RegisterService(service_);
}

void LoadReportingServiceServerBuilderPlugin::Finish(
    grpc::ServerInitializer* ) {
  service_->StartThread();
  service_.reset();
}

}
}
