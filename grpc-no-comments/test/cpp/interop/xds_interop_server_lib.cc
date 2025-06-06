
// Copyright 2023 gRPC authors.

#include "test/cpp/interop/xds_interop_server_lib.h"

#include <grpc/grpc.h>
#include <grpc/support/time.h>
#include <grpcpp/ext/admin_services.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/xds_server_builder.h>

#include <memory>

#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "src/proto/grpc/testing/empty.pb.h"
#include "src/proto/grpc/testing/messages.pb.h"
#include "src/proto/grpc/testing/test.grpc.pb.h"
#include "test/cpp/end2end/test_health_check_service_impl.h"
#include "test/cpp/interop/pre_stop_hook_server.h"

namespace grpc {
namespace testing {
namespace {

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::XdsServerBuilder;
using grpc::testing::Empty;
using grpc::testing::HealthCheckServiceImpl;
using grpc::testing::SimpleRequest;
using grpc::testing::SimpleResponse;
using grpc::testing::TestService;
using grpc::testing::XdsUpdateHealthService;

constexpr absl::string_view kRpcBehaviorMetadataKey = "rpc-behavior";
constexpr absl::string_view kErrorCodeRpcBehavior = "error-code-";
constexpr absl::string_view kHostnameRpcBehaviorFilter = "hostname=";

std::vector<std::string> GetRpcBehaviorMetadata(ServerContext* context) {
  std::vector<std::string> rpc_behaviors;
  auto rpc_behavior_metadata =
      context->client_metadata().equal_range(grpc::string_ref(
          kRpcBehaviorMetadataKey.data(), kRpcBehaviorMetadataKey.length()));
  for (auto metadata = rpc_behavior_metadata.first;
       metadata != rpc_behavior_metadata.second; ++metadata) {
    auto value = metadata->second;
    for (auto behavior :
         absl::StrSplit(absl::string_view(value.data(), value.length()), ',')) {
      rpc_behaviors.emplace_back(behavior);
    }
  }
  return rpc_behaviors;
}

class TestServiceImpl : public TestService::Service {
 public:
  explicit TestServiceImpl(absl::string_view hostname,
                           absl::string_view server_id)
      : hostname_(hostname), server_id_(server_id) {}

  Status UnaryCall(ServerContext* context, const SimpleRequest* request,
                   SimpleResponse* response) override {
    response->set_server_id(server_id_);
    for (const auto& rpc_behavior : GetRpcBehaviorMetadata(context)) {
      auto maybe_status =
          GetStatusForRpcBehaviorMetadata(rpc_behavior, hostname_);
      if (maybe_status.has_value()) {
        return *maybe_status;
      }
    }
    if (request->response_size() > 0) {
      std::string payload(request->response_size(), '0');
      response->mutable_payload()->set_body(payload.c_str(),
                                            request->response_size());
    }
    response->set_hostname(hostname_);
    context->AddInitialMetadata("hostname", hostname_);
    return Status::OK;
  }

  Status EmptyCall(ServerContext* context, const Empty* ,
                   Empty* ) override {
    context->AddInitialMetadata("hostname", hostname_);
    return Status::OK;
  }

 private:
  std::string hostname_;
  std::string server_id_;
};

class XdsUpdateHealthServiceImpl : public XdsUpdateHealthService::Service {
 public:
  explicit XdsUpdateHealthServiceImpl(
      HealthCheckServiceImpl* health_check_service,
      std::unique_ptr<PreStopHookServerManager> pre_stop_hook_server)
      : health_check_service_(health_check_service),
        pre_stop_hook_server_(std::move(pre_stop_hook_server)) {}

  Status SetServing(ServerContext* , const Empty* ,
                    Empty* ) override {
    health_check_service_->SetAll(
        grpc::health::v1::HealthCheckResponse::SERVING);
    return Status::OK;
  }

  Status SetNotServing(ServerContext* , const Empty* ,
                       Empty* ) override {
    health_check_service_->SetAll(
        grpc::health::v1::HealthCheckResponse::NOT_SERVING);
    return Status::OK;
  }

  Status SendHookRequest(ServerContext* ,
                         const HookRequest* request,
                         HookResponse* ) override {
    switch (request->command()) {
      case HookRequest::START:
        return pre_stop_hook_server_->Start(request->server_port(), 30 );
      case HookRequest::STOP:
        return pre_stop_hook_server_->Stop();
      case HookRequest::RETURN:
        pre_stop_hook_server_->Return(
            static_cast<StatusCode>(request->grpc_code_to_return()),
            request->grpc_status_description());
        return Status::OK;
      default:
        return Status(
            StatusCode::INVALID_ARGUMENT,
            absl::StrFormat("Invalid command %d", request->command()));
    }
  }

 private:
  HealthCheckServiceImpl* const health_check_service_;
  std::unique_ptr<PreStopHookServerManager> pre_stop_hook_server_;
};

class MaintenanceServices {
 public:
  MaintenanceServices()
      : update_health_service_(&health_check_service_,
                               std::make_unique<PreStopHookServerManager>()) {
    health_check_service_.SetStatus(
        "", grpc::health::v1::HealthCheckResponse::SERVING);
    health_check_service_.SetStatus(
        "grpc.testing.TestService",
        grpc::health::v1::HealthCheckResponse::SERVING);
    health_check_service_.SetStatus(
        "grpc.testing.XdsUpdateHealthService",
        grpc::health::v1::HealthCheckResponse::SERVING);
  }

  void AddToServerBuilder(ServerBuilder* builder) {
    builder->RegisterService(&health_check_service_);
    builder->RegisterService(&update_health_service_);
    builder->RegisterService(&hook_service_);
    grpc::AddAdminServices(builder);
  }

 private:
  HealthCheckServiceImpl health_check_service_;
  XdsUpdateHealthServiceImpl update_health_service_;
  HookServiceImpl hook_service_;
};
}

std::optional<grpc::Status> GetStatusForRpcBehaviorMetadata(
    absl::string_view header_value, absl::string_view hostname) {
  for (auto part : absl::StrSplit(header_value, ' ')) {
    if (absl::ConsumePrefix(&part, kHostnameRpcBehaviorFilter)) {
      LOG(INFO) << part;
      if (part.empty()) {
        return Status(
            grpc::StatusCode::INVALID_ARGUMENT,
            absl::StrCat("Empty host name in the RPC behavior header: ",
                         header_value));
      }
      if (part != hostname) {
        VLOG(2) << "RPC behavior for a different host: \"" << std::string(part)
                << "\", this one is: \"" << hostname << "\"";
        return std::nullopt;
      }
    } else if (absl::ConsumePrefix(&part, kErrorCodeRpcBehavior)) {
      grpc::StatusCode code;
      if (absl::SimpleAtoi(part, &code)) {
        return Status(
            code,
            absl::StrCat("Rpc failed as per the rpc-behavior header value: ",
                         header_value));
      } else {
        return Status(grpc::StatusCode::INVALID_ARGUMENT,
                      absl::StrCat("Invalid format for rpc-behavior header: ",
                                   header_value));
      }
    } else {

      return Status(
          grpc::StatusCode::INVALID_ARGUMENT,
          absl::StrCat("Unsupported rpc behavior header: ", header_value));
    }
  }
  return std::nullopt;
}

void RunServer(bool secure_mode, int port, const int maintenance_port,
               absl::string_view hostname, absl::string_view server_id,
               const std::function<void(Server*)>& server_callback) {
  std::unique_ptr<Server> xds_enabled_server;
  std::unique_ptr<Server> server;
  TestServiceImpl service(hostname, server_id);

  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  MaintenanceServices maintenance_services;
  if (secure_mode) {
    XdsServerBuilder xds_builder;
    xds_builder.RegisterService(&service);
    xds_builder.AddListeningPort(
        absl::StrCat("0.0.0.0:", port),
        grpc::XdsServerCredentials(grpc::InsecureServerCredentials()));
    xds_enabled_server = xds_builder.BuildAndStart();
    LOG(INFO) << "Server starting on 0.0.0.0:" << port;
    ServerBuilder builder;
    maintenance_services.AddToServerBuilder(&builder);
    server = builder
                 .AddListeningPort(absl::StrCat("0.0.0.0:", maintenance_port),
                                   grpc::InsecureServerCredentials())
                 .BuildAndStart();
    LOG(INFO) << "Maintenance server listening on 0.0.0.0:" << maintenance_port;
  } else {
    ServerBuilder builder;
    maintenance_services.AddToServerBuilder(&builder);
    server = builder
                 .AddListeningPort(absl::StrCat("0.0.0.0:", port),
                                   grpc::InsecureServerCredentials())
                 .RegisterService(&service)
                 .BuildAndStart();
    LOG(INFO) << "Server listening on 0.0.0.0:" << port;
  }
  server_callback(server.get());
  server->Wait();
}

}
}
