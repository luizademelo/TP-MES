Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary headers for gRPC server reflection functionality
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

// Constructor for ProtoServerReflectionPlugin
// Initializes backend and creates reflection services for both v1 and v1alpha versions
ProtoServerReflectionPlugin::ProtoServerReflectionPlugin()
    : backend_(std::make_shared<ProtoServerReflectionBackend>()),
      reflection_service_v1alpha_(
          std::make_shared<ProtoServerReflection>(backend_)),
      reflection_service_v1_(
          std::make_shared<ProtoServerReflectionV1>(backend_)) {}

// Returns the name of this plugin
std::string ProtoServerReflectionPlugin::name() {
  return "proto_server_reflection";
}

// Initializes the server by registering reflection services if reflection is enabled
void ProtoServerReflectionPlugin::InitServer(grpc::ServerInitializer* si) {
  // Check if reflection is disabled via configuration
  if (!grpc_core::ConfigVars::Get().CppExperimentalDisableReflection()) {
    // Register both v1 and v1alpha reflection services
    si->RegisterService(reflection_service_v1_);
    si->RegisterService(reflection_service_v1alpha_);
  }
}

// Finalizes plugin initialization by setting the service list in the backend
void ProtoServerReflectionPlugin::Finish(grpc::ServerInitializer* si) {
  backend_->SetServiceList(si->GetServiceList());
}

// Placeholder for changing arguments - currently does nothing
void ProtoServerReflectionPlugin::ChangeArguments(const std::string&, void*) {}

// Checks if any of the reflection services have synchronous methods
bool ProtoServerReflectionPlugin::has_sync_methods() const {
  if (!grpc_core::ConfigVars::Get().CppExperimentalDisableReflection()) {
    return (reflection_service_v1_ &&
            reflection_service_v1_->has_synchronous_methods()) ||
           (reflection_service_v1alpha_ &&
            reflection_service_v1alpha_->has_synchronous_methods());
  }
  return false;
}

// Checks if any of the reflection services have asynchronous methods
bool ProtoServerReflectionPlugin::has_async_methods() const {
  if (!grpc_core::ConfigVars::Get().CppExperimentalDisableReflection()) {
    return (reflection_service_v1_ &&
            reflection_service_v1_->has_async_methods()) ||
           (reflection_service_v1alpha_ &&
            reflection_service_v1alpha_->has_async_methods());
  }
  return false;
}

// Factory function to create a ProtoServerReflectionPlugin instance
static std::unique_ptr<grpc::ServerBuilderPlugin> CreateProtoReflection() {
  return std::unique_ptr<grpc::ServerBuilderPlugin>(
      new ProtoServerReflectionPlugin());
}

// Initializes the proto reflection server builder plugin
void InitProtoReflectionServerBuilderPlugin() {
  // Static initializer that registers the plugin factory with ServerBuilder
  static struct Initialize {
    Initialize() {
      grpc::ServerBuilder::InternalAddPluginFactory(&CreateProtoReflection);
    }
  } initializer;
}

// Static instance that ensures plugin registration at startup
struct StaticProtoReflectionPluginInitializer {
  StaticProtoReflectionPluginInitializer() {
    InitProtoReflectionServerBuilderPlugin();
  }
} static_proto_reflection_plugin_initializer;

}  // namespace reflection
}  // namespace grpc
```

The comments explain:
1. The purpose of each include directive
2. The functionality of each class method
3. The control flow and conditions
4. The purpose of static initialization
5. The overall architecture of the reflection plugin system
6. The version handling (v1 vs v1alpha)
7. The configuration checking for reflection enablement

The comments are concise yet informative, providing enough context for future maintainers to understand the code's purpose and behavior without being overly verbose.