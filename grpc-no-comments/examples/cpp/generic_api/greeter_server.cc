// Copyright 2023 gRPC authors.

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"
#include "absl/synchronization/mutex.h"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

using grpc::ByteBuffer;
using grpc::CallbackGenericService;
using grpc::CallbackServerContext;
using grpc::GenericCallbackServerContext;
using grpc::ProtoBufferReader;
using grpc::ProtoBufferWriter;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerGenericBidiReactor;
using grpc::Status;
using grpc::StatusCode;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class GreeterServiceImpl final : public CallbackGenericService {
  ServerGenericBidiReactor* CreateReactor(
      GenericCallbackServerContext* context) override {
    if (context->method() == "/helloworld.Greeter/SayHello") {

      return new SayHelloReactor();
    } else {

      return CallbackGenericService::CreateReactor(context);
    }
  }

  class SayHelloReactor : public ServerGenericBidiReactor {
   public:
    SayHelloReactor() { StartRead(&request_); }

   private:
    Status OnSayHello(const HelloRequest& request, HelloReply* reply) {
      if (request.name() == "") {
        return Status(StatusCode::INVALID_ARGUMENT, "name is not specified");
      }
      reply->set_message(absl::StrFormat("Hello %s", request.name()));
      return Status::OK;
    }

    void OnDone() override { delete this; }
    void OnReadDone(bool ok) override {
      if (!ok) {
        return;
      }
      Status result;

      HelloRequest request;
      result = grpc::GenericDeserialize<ProtoBufferReader, HelloRequest>(
          &request_, &request);
      if (!result.ok()) {
        Finish(result);
        return;
      }

      HelloReply reply;
      result = OnSayHello(request, &reply);
      if (!result.ok()) {
        Finish(result);
        return;
      }

      bool own_buffer;
      result = grpc::GenericSerialize<ProtoBufferWriter, HelloReply>(
          reply, &response_, &own_buffer);
      if (!result.ok()) {
        Finish(result);
        return;
      }
      StartWrite(&response_);
    }
    void OnWriteDone(bool ok) override {
      Finish(ok ? Status::OK
                : Status(StatusCode::UNKNOWN, "Unexpected failure"));
    }
    ByteBuffer request_;
    ByteBuffer response_;
  };

 private:
  absl::Mutex mu_;
};

void RunServer(uint16_t port) {
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;
  grpc::EnableDefaultHealthCheckService(true);
  ServerBuilder builder;

  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  builder.RegisterCallbackGenericService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
