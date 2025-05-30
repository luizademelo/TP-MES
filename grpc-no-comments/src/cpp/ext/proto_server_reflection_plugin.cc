
// Copyright 2015 gRPC authors.

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/impl/server_initializer.h>
#include <grpcpp/server_builder.h>

#include <memory>
#include <string>

#include "src/core/config/config_vars.h"
#include "src/cpp/ext/proto_server_reflection.h"

namespace grpc {
namespace reflection {

ProtoServerReflectionPlugin::ProtoServerReflectionPlugin()
    : backend_(std::make_shared<ProtoServerReflectionBackend>()),
      reflection_service_v1alpha_(
          std::make_shared<ProtoServerReflection>(backend_)),
      reflection_service_v1_(
          std::make_shared<ProtoServerReflectionV1>(backend_)) {}

std::string ProtoServerReflectionPlugin::name() {
  return "proto_server_reflection";
}

void ProtoServerReflectionPlugin::InitServer(grpc::ServerInitializer* si) {

  if (!grpc_core::ConfigVars::Get().CppExperimentalDisableReflection()) {
    si->RegisterService(reflection_service_v1_);
    si->RegisterService(reflection_service_v1alpha_);
  }
}

void ProtoServerReflectionPlugin::Finish(grpc::ServerInitializer* si) {
  backend_->SetServiceList(si->GetServiceList());
}

void ProtoServerReflectionPlugin::ChangeArguments(const std::string& ,
                                                  void* ) {}

bool ProtoServerReflectionPlugin::has_sync_methods() const {
  if (!grpc_core::ConfigVars::Get().CppExperimentalDisableReflection()) {
    return (reflection_service_v1_ &&
            reflection_service_v1_->has_synchronous_methods()) ||
           (reflection_service_v1alpha_ &&
            reflection_service_v1alpha_->has_synchronous_methods());
  }
  return false;
}

bool ProtoServerReflectionPlugin::has_async_methods() const {
  if (!grpc_core::ConfigVars::Get().CppExperimentalDisableReflection()) {
    return (reflection_service_v1_ &&
            reflection_service_v1_->has_async_methods()) ||
           (reflection_service_v1alpha_ &&
            reflection_service_v1alpha_->has_async_methods());
  }
  return false;
}

static std::unique_ptr<grpc::ServerBuilderPlugin> CreateProtoReflection() {
  return std::unique_ptr<grpc::ServerBuilderPlugin>(
      new ProtoServerReflectionPlugin());
}

void InitProtoReflectionServerBuilderPlugin() {
  static struct Initialize {
    Initialize() {
      grpc::ServerBuilder::InternalAddPluginFactory(&CreateProtoReflection);
    }
  } initializer;
}

struct StaticProtoReflectionPluginInitializer {
  StaticProtoReflectionPluginInitializer() {
    InitProtoReflectionServerBuilderPlugin();
  }
} static_proto_reflection_plugin_initializer;

}
}
