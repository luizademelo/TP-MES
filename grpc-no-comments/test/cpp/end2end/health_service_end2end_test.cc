
// Copyright 2016 gRPC authors.

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/ext/health_check_service_server_builder_option.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "gtest/gtest.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/health/v1/health.grpc.pb.h"
#include "src/proto/grpc/testing/duplicate/echo_duplicate.grpc.pb.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/end2end/test_health_check_service_impl.h"
#include "test/cpp/end2end/test_service_impl.h"

using grpc::health::v1::Health;
using grpc::health::v1::HealthCheckRequest;
using grpc::health::v1::HealthCheckResponse;

namespace grpc {
namespace testing {
namespace {

class CustomHealthCheckService : public HealthCheckServiceInterface {
 public:
  explicit CustomHealthCheckService(HealthCheckServiceImpl* impl)
      : impl_(impl) {
    impl_->SetStatus("", HealthCheckResponse::SERVING);
  }
  void SetServingStatus(const std::string& service_name,
                        bool serving) override {
    impl_->SetStatus(service_name, serving ? HealthCheckResponse::SERVING
                                           : HealthCheckResponse::NOT_SERVING);
  }

  void SetServingStatus(bool serving) override {
    impl_->SetAll(serving ? HealthCheckResponse::SERVING
                          : HealthCheckResponse::NOT_SERVING);
  }

  void Shutdown() override { impl_->Shutdown(); }

 private:
  HealthCheckServiceImpl* impl_;
};

class HealthServiceEnd2endTest : public ::testing::Test {
 protected:
  HealthServiceEnd2endTest() {}

  void SetUpServer(bool register_sync_test_service, bool add_async_cq,
                   bool explicit_health_service,
                   std::unique_ptr<HealthCheckServiceInterface> service) {
    int port = grpc_pick_unused_port_or_die();
    server_address_ << "localhost:" << port;

    bool register_sync_health_service_impl =
        explicit_health_service && service != nullptr;

    ServerBuilder builder;
    if (explicit_health_service) {
      std::unique_ptr<ServerBuilderOption> option(
          new HealthCheckServiceServerBuilderOption(std::move(service)));
      builder.SetOption(std::move(option));
    }
    builder.AddListeningPort(server_address_.str(),
                             grpc::InsecureServerCredentials());
    if (register_sync_test_service) {

      builder.RegisterService(&echo_test_service_);
    }
    if (register_sync_health_service_impl) {
      builder.RegisterService(&health_check_service_impl_);
    }
    if (add_async_cq) {
      cq_ = builder.AddCompletionQueue();
    }
    server_ = builder.BuildAndStart();
  }

  void TearDown() override {
    if (server_) {
      server_->Shutdown();
      if (cq_ != nullptr) {
        cq_->Shutdown();
      }
      if (cq_thread_.joinable()) {
        cq_thread_.join();
      }
    }
  }

  void ResetStubs() {
    std::shared_ptr<Channel> channel = grpc::CreateChannel(
        server_address_.str(), InsecureChannelCredentials());
    hc_stub_ = grpc::health::v1::Health::NewStub(channel);
  }

  void SendHealthCheckRpc(const std::string& service_name,
                          const Status& expected_status) {
    EXPECT_FALSE(expected_status.ok());
    SendHealthCheckRpc(service_name, expected_status,
                       HealthCheckResponse::UNKNOWN);
  }

  void SendHealthCheckRpc(
      const std::string& service_name, const Status& expected_status,
      HealthCheckResponse::ServingStatus expected_serving_status) {
    HealthCheckRequest request;
    request.set_service(service_name);
    HealthCheckResponse response;
    ClientContext context;
    Status s = hc_stub_->Check(&context, request, &response);
    EXPECT_EQ(expected_status.error_code(), s.error_code());
    if (s.ok()) {
      EXPECT_EQ(expected_serving_status, response.status());
    }
  }

  void VerifyHealthCheckService() {
    HealthCheckServiceInterface* service = server_->GetHealthCheckService();
    EXPECT_TRUE(service != nullptr);
    const std::string kHealthyService("healthy_service");
    const std::string kUnhealthyService("unhealthy_service");
    const std::string kNotRegisteredService("not_registered");
    service->SetServingStatus(kHealthyService, true);
    service->SetServingStatus(kUnhealthyService, false);

    ResetStubs();

    SendHealthCheckRpc("", Status::OK, HealthCheckResponse::SERVING);
    SendHealthCheckRpc(kHealthyService, Status::OK,
                       HealthCheckResponse::SERVING);
    SendHealthCheckRpc(kUnhealthyService, Status::OK,
                       HealthCheckResponse::NOT_SERVING);
    SendHealthCheckRpc(kNotRegisteredService,
                       Status(StatusCode::NOT_FOUND, ""));

    service->SetServingStatus(false);
    SendHealthCheckRpc("", Status::OK, HealthCheckResponse::NOT_SERVING);
    SendHealthCheckRpc(kHealthyService, Status::OK,
                       HealthCheckResponse::NOT_SERVING);
    SendHealthCheckRpc(kUnhealthyService, Status::OK,
                       HealthCheckResponse::NOT_SERVING);
    SendHealthCheckRpc(kNotRegisteredService,
                       Status(StatusCode::NOT_FOUND, ""));
  }

  void VerifyHealthCheckServiceStreaming() {
    const std::string kServiceName("service_name");
    HealthCheckServiceInterface* service = server_->GetHealthCheckService();

    ClientContext context;
    HealthCheckRequest request;
    request.set_service(kServiceName);
    std::unique_ptr<grpc::ClientReaderInterface<HealthCheckResponse>> reader =
        hc_stub_->Watch(&context, request);

    HealthCheckResponse response;
    EXPECT_TRUE(reader->Read(&response));
    EXPECT_EQ(response.SERVICE_UNKNOWN, response.status());
    response.Clear();

    service->SetServingStatus(kServiceName, false);
    EXPECT_TRUE(reader->Read(&response));
    EXPECT_EQ(response.NOT_SERVING, response.status());
    response.Clear();

    service->SetServingStatus(kServiceName, true);
    EXPECT_TRUE(reader->Read(&response));
    EXPECT_EQ(response.SERVING, response.status());

    context.TryCancel();
  }

  void VerifyHealthCheckServiceShutdown() {
    HealthCheckServiceInterface* service = server_->GetHealthCheckService();
    EXPECT_TRUE(service != nullptr);
    const std::string kHealthyService("healthy_service");
    const std::string kUnhealthyService("unhealthy_service");
    const std::string kNotRegisteredService("not_registered");
    const std::string kNewService("add_after_shutdown");
    service->SetServingStatus(kHealthyService, true);
    service->SetServingStatus(kUnhealthyService, false);

    ResetStubs();

    ClientContext context;
    HealthCheckRequest request;
    request.set_service(kHealthyService);
    std::unique_ptr<grpc::ClientReaderInterface<HealthCheckResponse>> reader =
        hc_stub_->Watch(&context, request);

    HealthCheckResponse response;
    EXPECT_TRUE(reader->Read(&response));
    EXPECT_EQ(response.SERVING, response.status());

    SendHealthCheckRpc("", Status::OK, HealthCheckResponse::SERVING);
    SendHealthCheckRpc(kHealthyService, Status::OK,
                       HealthCheckResponse::SERVING);
    SendHealthCheckRpc(kUnhealthyService, Status::OK,
                       HealthCheckResponse::NOT_SERVING);
    SendHealthCheckRpc(kNotRegisteredService,
                       Status(StatusCode::NOT_FOUND, ""));
    SendHealthCheckRpc(kNewService, Status(StatusCode::NOT_FOUND, ""));

    service->Shutdown();

    EXPECT_TRUE(reader->Read(&response));
    EXPECT_EQ(response.NOT_SERVING, response.status());

    context.TryCancel();

    SendHealthCheckRpc("", Status::OK, HealthCheckResponse::NOT_SERVING);
    SendHealthCheckRpc(kHealthyService, Status::OK,
                       HealthCheckResponse::NOT_SERVING);
    SendHealthCheckRpc(kUnhealthyService, Status::OK,
                       HealthCheckResponse::NOT_SERVING);
    SendHealthCheckRpc(kNotRegisteredService,
                       Status(StatusCode::NOT_FOUND, ""));

    service->SetServingStatus(kHealthyService, true);
    SendHealthCheckRpc(kHealthyService, Status::OK,
                       HealthCheckResponse::NOT_SERVING);

    service->SetServingStatus(kNewService, true);
    SendHealthCheckRpc(kNewService, Status::OK,
                       HealthCheckResponse::NOT_SERVING);
  }

  TestServiceImpl echo_test_service_;
  HealthCheckServiceImpl health_check_service_impl_;
  std::unique_ptr<Health::Stub> hc_stub_;
  std::unique_ptr<ServerCompletionQueue> cq_;
  std::unique_ptr<Server> server_;
  std::ostringstream server_address_;
  std::thread cq_thread_;
};

TEST_F(HealthServiceEnd2endTest, DefaultHealthServiceDisabled) {
  EnableDefaultHealthCheckService(false);
  EXPECT_FALSE(DefaultHealthCheckServiceEnabled());
  SetUpServer(true, false, false, nullptr);
  HealthCheckServiceInterface* default_service =
      server_->GetHealthCheckService();
  EXPECT_TRUE(default_service == nullptr);

  ResetStubs();

  SendHealthCheckRpc("", Status(StatusCode::UNIMPLEMENTED, ""));
}

TEST_F(HealthServiceEnd2endTest, DefaultHealthService) {
  EnableDefaultHealthCheckService(true);
  EXPECT_TRUE(DefaultHealthCheckServiceEnabled());
  SetUpServer(true, false, false, nullptr);
  VerifyHealthCheckService();
  VerifyHealthCheckServiceStreaming();

  const std::string kTooLongServiceName(201, 'x');
  SendHealthCheckRpc(kTooLongServiceName,
                     Status(StatusCode::INVALID_ARGUMENT, ""));
}

TEST_F(HealthServiceEnd2endTest, DefaultHealthServiceShutdown) {
  EnableDefaultHealthCheckService(true);
  EXPECT_TRUE(DefaultHealthCheckServiceEnabled());
  SetUpServer(true, false, false, nullptr);
  VerifyHealthCheckServiceShutdown();
}

TEST_F(HealthServiceEnd2endTest, ExplicitlyDisableViaOverride) {
  EnableDefaultHealthCheckService(true);
  EXPECT_TRUE(DefaultHealthCheckServiceEnabled());
  std::unique_ptr<HealthCheckServiceInterface> empty_service;
  SetUpServer(true, false, true, std::move(empty_service));
  HealthCheckServiceInterface* service = server_->GetHealthCheckService();
  EXPECT_TRUE(service == nullptr);

  ResetStubs();

  SendHealthCheckRpc("", Status(StatusCode::UNIMPLEMENTED, ""));
}

TEST_F(HealthServiceEnd2endTest, ExplicitlyOverride) {
  EnableDefaultHealthCheckService(true);
  EXPECT_TRUE(DefaultHealthCheckServiceEnabled());
  std::unique_ptr<HealthCheckServiceInterface> override_service(
      new CustomHealthCheckService(&health_check_service_impl_));
  HealthCheckServiceInterface* underlying_service = override_service.get();
  SetUpServer(false, false, true, std::move(override_service));
  HealthCheckServiceInterface* service = server_->GetHealthCheckService();
  EXPECT_TRUE(service == underlying_service);

  ResetStubs();

  VerifyHealthCheckService();
  VerifyHealthCheckServiceStreaming();
}

TEST_F(HealthServiceEnd2endTest, ExplicitlyHealthServiceShutdown) {
  EnableDefaultHealthCheckService(true);
  EXPECT_TRUE(DefaultHealthCheckServiceEnabled());
  std::unique_ptr<HealthCheckServiceInterface> override_service(
      new CustomHealthCheckService(&health_check_service_impl_));
  HealthCheckServiceInterface* underlying_service = override_service.get();
  SetUpServer(false, false, true, std::move(override_service));
  HealthCheckServiceInterface* service = server_->GetHealthCheckService();
  EXPECT_TRUE(service == underlying_service);

  ResetStubs();

  VerifyHealthCheckServiceShutdown();
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
