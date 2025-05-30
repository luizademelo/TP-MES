
// Copyright 2017 gRPC authors.

#include <grpcpp/impl/channel_argument_option.h>
#include <grpcpp/impl/server_builder_option.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/support/channel_arguments.h>

#include <memory>
#include <string>
#include <vector>

namespace grpc {

std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const std::string& name, const std::string& value) {
  class StringOption final : public ServerBuilderOption {
   public:
    StringOption(const std::string& name, const std::string& value)
        : name_(name), value_(value) {}

    void UpdateArguments(ChannelArguments* args) override {
      args->SetString(name_, value_);
    }
    void UpdatePlugins(
        std::vector<std::unique_ptr<ServerBuilderPlugin>>* )
        override {}

   private:
    const std::string name_;
    const std::string value_;
  };
  return std::unique_ptr<ServerBuilderOption>(new StringOption(name, value));
}

std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const std::string& name, int value) {
  class IntOption final : public ServerBuilderOption {
   public:
    IntOption(const std::string& name, int value)
        : name_(name), value_(value) {}

    void UpdateArguments(ChannelArguments* args) override {
      args->SetInt(name_, value_);
    }
    void UpdatePlugins(
        std::vector<std::unique_ptr<ServerBuilderPlugin>>* )
        override {}

   private:
    const std::string name_;
    const int value_;
  };
  return std::unique_ptr<ServerBuilderOption>(new IntOption(name, value));
}

std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const std::string& name, void* value) {
  class PointerOption final : public ServerBuilderOption {
   public:
    PointerOption(const std::string& name, void* value)
        : name_(name), value_(value) {}

    void UpdateArguments(ChannelArguments* args) override {
      args->SetPointer(name_, value_);
    }
    void UpdatePlugins(
        std::vector<std::unique_ptr<ServerBuilderPlugin>>* )
        override {}

   private:
    const std::string name_;
    void* value_;
  };
  return std::unique_ptr<ServerBuilderOption>(new PointerOption(name, value));
}

}
