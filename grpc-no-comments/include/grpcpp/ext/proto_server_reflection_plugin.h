
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_EXT_PROTO_SERVER_REFLECTION_PLUGIN_H
#define GRPCPP_EXT_PROTO_SERVER_REFLECTION_PLUGIN_H

#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/support/config.h>

#include <memory>

namespace grpc {
class ProtoServerReflection;
class ProtoServerReflectionBackend;
class ProtoServerReflectionV1;
class ServerInitializer;

namespace reflection {

class ProtoServerReflectionPlugin : public grpc::ServerBuilderPlugin {
 public:
  ProtoServerReflectionPlugin();
  ::std::string name() override;
  void InitServer(ServerInitializer* si) override;
  void Finish(ServerInitializer* si) override;
  void ChangeArguments(const ::std::string& name, void* value) override;
  bool has_async_methods() const override;
  bool has_sync_methods() const override;

 private:
  std::shared_ptr<grpc::ProtoServerReflectionBackend> backend_;
  std::shared_ptr<grpc::ProtoServerReflection> reflection_service_v1alpha_;
  std::shared_ptr<grpc::ProtoServerReflectionV1> reflection_service_v1_;
};

void InitProtoReflectionServerBuilderPlugin();

}
}

#endif
