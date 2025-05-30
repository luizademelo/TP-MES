
// Copyright 2016 gRPC authors.

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/impl/server_builder_option.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/impl/server_initializer.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <thread>

#include "absl/memory/memory.h"
#include "gtest/gtest.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/test_service_impl.h"

#define PLUGIN_NAME "TestServerBuilderPlugin"

namespace grpc {
namespace testing {

class TestServerBuilderPlugin : public ServerBuilderPlugin {
 public:
  TestServerBuilderPlugin() : service_(new TestServiceImpl()) {
    init_server_is_called_ = false;
    finish_is_called_ = false;
    change_arguments_is_called_ = false;
    register_service_ = false;
  }

  std::string name() override { return PLUGIN_NAME; }

  void InitServer(ServerInitializer* si) override {
    init_server_is_called_ = true;
    if (register_service_) {
      si->RegisterService(service_);
    }
  }

  void Finish(ServerInitializer* ) override { finish_is_called_ = true; }

  void ChangeArguments(const std::string& , void* ) override {
    change_arguments_is_called_ = true;
  }

  bool has_async_methods() const override {
    if (register_service_) {
      return service_->has_async_methods();
    }
    return false;
  }

  bool has_sync_methods() const override {
    if (register_service_) {
      return service_->has_synchronous_methods();
    }
    return false;
  }

  void SetRegisterService() { register_service_ = true; }

  bool init_server_is_called() { return init_server_is_called_; }
  bool finish_is_called() { return finish_is_called_; }
  bool change_arguments_is_called() { return change_arguments_is_called_; }

 private:
  bool init_server_is_called_;
  bool finish_is_called_;
  bool change_arguments_is_called_;
  bool register_service_;
  std::shared_ptr<TestServiceImpl> service_;
};

class InsertPluginServerBuilderOption : public ServerBuilderOption {
 public:
  InsertPluginServerBuilderOption() { register_service_ = false; }

  void UpdateArguments(ChannelArguments* ) override {}

  void UpdatePlugins(
      std::vector<std::unique_ptr<ServerBuilderPlugin>>* plugins) override {
    plugins->clear();

    std::unique_ptr<TestServerBuilderPlugin> plugin(
        new TestServerBuilderPlugin());
    if (register_service_) plugin->SetRegisterService();
    plugins->emplace_back(std::move(plugin));
  }

  void SetRegisterService() { register_service_ = true; }

 private:
  bool register_service_;
};

std::unique_ptr<ServerBuilderPlugin> CreateTestServerBuilderPlugin() {
  return std::unique_ptr<ServerBuilderPlugin>(new TestServerBuilderPlugin());
}

struct StaticTestPluginInitializer {
  StaticTestPluginInitializer() {
    grpc::ServerBuilder::InternalAddPluginFactory(
        &CreateTestServerBuilderPlugin);
  }
} static_plugin_initializer_test_;

class ServerBuilderPluginTest : public ::testing::TestWithParam<bool> {
 public:
  ServerBuilderPluginTest() {}

  void SetUp() override {
    port_ = grpc_pick_unused_port_or_die();
    builder_ = std::make_unique<ServerBuilder>();
  }

  void InsertPlugin() {
    if (GetParam()) {

      CheckPresent();
    } else {

      builder_->SetOption(std::unique_ptr<ServerBuilderOption>(
          new InsertPluginServerBuilderOption()));
    }
  }

  void InsertPluginWithTestService() {
    if (GetParam()) {

      auto plugin = CheckPresent();
      EXPECT_TRUE(plugin);
      plugin->SetRegisterService();
    } else {

      std::unique_ptr<InsertPluginServerBuilderOption> option(
          new InsertPluginServerBuilderOption());
      option->SetRegisterService();
      builder_->SetOption(std::move(option));
    }
  }

  void StartServer() {
    std::string server_address = "localhost:" + to_string(port_);
    builder_->AddListeningPort(server_address, InsecureServerCredentials());

    cq_ = builder_->AddCompletionQueue();
    cq_thread_ = new std::thread(&ServerBuilderPluginTest::RunCQ, this);
    server_ = builder_->BuildAndStart();
    EXPECT_TRUE(CheckPresent());
  }

  void ResetStub() {
    string target = "dns:localhost:" + to_string(port_);
    channel_ = grpc::CreateChannel(target, InsecureChannelCredentials());
    stub_ = grpc::testing::EchoTestService::NewStub(channel_);
  }

  void TearDown() override {
    auto plugin = CheckPresent();
    EXPECT_TRUE(plugin);
    EXPECT_TRUE(plugin->init_server_is_called());
    EXPECT_TRUE(plugin->finish_is_called());
    server_->Shutdown();
    cq_->Shutdown();
    cq_thread_->join();
    delete cq_thread_;
  }

  string to_string(const int number) {
    std::stringstream strs;
    strs << number;
    return strs.str();
  }

 protected:
  std::shared_ptr<Channel> channel_;
  std::unique_ptr<ServerBuilder> builder_;
  std::unique_ptr<grpc::testing::EchoTestService::Stub> stub_;
  std::unique_ptr<ServerCompletionQueue> cq_;
  std::unique_ptr<Server> server_;
  std::thread* cq_thread_;
  TestServiceImpl service_;
  int port_;

 private:
  TestServerBuilderPlugin* CheckPresent() {
    auto it = builder_->plugins_.begin();
    for (; it != builder_->plugins_.end(); it++) {
      if ((*it)->name() == PLUGIN_NAME) break;
    }
    if (it != builder_->plugins_.end()) {
      return static_cast<TestServerBuilderPlugin*>(it->get());
    } else {
      return nullptr;
    }
  }

  void RunCQ() {
    void* tag;
    bool ok;
    while (cq_->Next(&tag, &ok)) {
    }
  }
};

TEST_P(ServerBuilderPluginTest, PluginWithoutServiceTest) {
  InsertPlugin();
  StartServer();
}

TEST_P(ServerBuilderPluginTest, PluginWithServiceTest) {
  InsertPluginWithTestService();
  StartServer();
  ResetStub();

  EchoRequest request;
  EchoResponse response;
  request.set_message("Hello hello hello hello");
  ClientContext context;
  context.set_compression_algorithm(GRPC_COMPRESS_GZIP);
  Status s = stub_->Echo(&context, request, &response);
  EXPECT_EQ(response.message(), request.message());
  EXPECT_TRUE(s.ok());
}

INSTANTIATE_TEST_SUITE_P(ServerBuilderPluginTest, ServerBuilderPluginTest,
                         ::testing::Values(false, true));

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
