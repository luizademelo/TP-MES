
// Copyright 2021 gRPC authors.

#include <grpcpp/ext/admin_services.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>

#include "absl/strings/str_cat.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/proto/grpc/reflection/v1alpha/reflection.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"

namespace grpc {
namespace testing {

class AdminServicesTest : public ::testing::Test {
 public:
  void SetUp() override {
    std::string address =
        absl::StrCat("localhost:", grpc_pick_unused_port_or_die());

    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    builder.AddListeningPort(address, InsecureServerCredentials());
    grpc::AddAdminServices(&builder);
    server_ = builder.BuildAndStart();

    auto reflection_stub = reflection::v1alpha::ServerReflection::NewStub(
        CreateChannel(address, InsecureChannelCredentials()));
    stream_ = reflection_stub->ServerReflectionInfo(&reflection_ctx_);
  }

  std::vector<std::string> GetServiceList() {
    std::vector<std::string> services;
    reflection::v1alpha::ServerReflectionRequest request;
    reflection::v1alpha::ServerReflectionResponse response;
    request.set_list_services("");
    stream_->Write(request);
    stream_->Read(&response);
    for (auto& service : response.list_services_response().service()) {
      services.push_back(service.name());
    }
    return services;
  }

 private:
  std::unique_ptr<Server> server_;
  ClientContext reflection_ctx_;
  std::shared_ptr<
      ClientReaderWriter<reflection::v1alpha::ServerReflectionRequest,
                         reflection::v1alpha::ServerReflectionResponse>>
      stream_;
};

TEST_F(AdminServicesTest, ValidateRegisteredServices) {

  EXPECT_THAT(
      GetServiceList(),
      ::testing::AllOf(
          ::testing::Contains("grpc.channelz.v1.Channelz"),
          ::testing::Contains("grpc.reflection.v1alpha.ServerReflection")));
#if defined(GRPC_NO_XDS) || defined(DISABLED_XDS_PROTO_IN_CC)
  EXPECT_THAT(GetServiceList(),
              ::testing::Not(::testing::Contains(
                  "envoy.service.status.v3.ClientStatusDiscoveryService")));
#else
  EXPECT_THAT(GetServiceList(),
              ::testing::Contains(
                  "envoy.service.status.v3.ClientStatusDiscoveryService"));
#endif
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
