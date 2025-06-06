
/*
 *
 * Copyright 2023 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <grpcpp/ext/admin_services.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/xds_server_builder.h>

#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

ABSL_FLAG(int32_t, port, 50051, "Server port for service.");
ABSL_FLAG(int32_t, maintenance_port, 50052,
          "Server port for maintenance if --secure is used.");
ABSL_FLAG(bool, secure, true, "Secure mode");

using grpc::CallbackServerContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerUnaryReactor;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class GreeterServiceImpl final : public Greeter::CallbackService {
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());

    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }
};

void RunServer() {
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  int port = absl::GetFlag(FLAGS_port);
  int maintenance_port = absl::GetFlag(FLAGS_maintenance_port);
  grpc::XdsServerBuilder xds_builder;
  ServerBuilder builder;
  std::unique_ptr<Server> xds_enabled_server;
  std::unique_ptr<Server> server;
  GreeterServiceImpl service;

  xds_builder.RegisterService(&service);
  if (absl::GetFlag(FLAGS_secure)) {

    xds_builder.AddListeningPort(
        absl::StrCat("0.0.0.0:", port),
        grpc::XdsServerCredentials(grpc::InsecureServerCredentials()));
    xds_enabled_server = xds_builder.BuildAndStart();
    LOG(INFO) << "Server starting on 0.0.0.0:" << port;
    grpc::AddAdminServices(&builder);

    builder.AddListeningPort(absl::StrCat("0.0.0.0:", maintenance_port),
                             grpc::InsecureServerCredentials());
    server = builder.BuildAndStart();
    LOG(INFO) << "Maintenance server listening on 0.0.0.0:" << maintenance_port;
  } else {
    grpc::AddAdminServices(&xds_builder);

    builder.AddListeningPort(absl::StrCat("0.0.0.0:", port),
                             grpc::InsecureServerCredentials());
    server = xds_builder.BuildAndStart();
    LOG(INFO) << "Server listening on 0.0.0.0:" << port;
  }

  server->Wait();
}

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  RunServer();
  return 0;
}
