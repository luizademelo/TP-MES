// Copyright 2023 gRPC authors.

#include <grpcpp/grpcpp.h>

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/match.h"
#include "absl/strings/str_format.h"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

using grpc::CallbackServerContext;
using grpc::Channel;
using grpc::ClientContext;

using grpc::Server;
using grpc::ServerBidiReactor;
using grpc::ServerBuilder;
using grpc::ServerUnaryReactor;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class GreeterServiceImpl final : public Greeter::CallbackService {
 public:
  GreeterServiceImpl(const std::string& self_address) {
    self_channel_ =
        grpc::CreateChannel(self_address, grpc::InsecureChannelCredentials());
  }

 private:
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    if (absl::StartsWith(request->name(), "[propagate me]")) {
      std::unique_ptr<Greeter::Stub> stub = Greeter::NewStub(self_channel_);
      std::this_thread::sleep_for(std::chrono::milliseconds(800));

      HelloRequest new_request;
      new_request.set_name(request->name().substr(14));
      std::unique_ptr<ClientContext> new_context =
          ClientContext::FromCallbackServerContext(*context);
      std::mutex mu;
      std::condition_variable cv;
      bool done = false;
      Status status;
      stub->async()->SayHello(new_context.get(), &new_request, reply,
                              [&mu, &cv, &done, &status](Status s) {
                                status = std::move(s);
                                std::lock_guard<std::mutex> lock(mu);
                                done = true;
                                cv.notify_one();
                              });
      std::unique_lock<std::mutex> lock(mu);
      while (!done) {
        cv.wait(lock);
      }
      ServerUnaryReactor* reactor = context->DefaultReactor();
      reactor->Finish(status);
      return reactor;
    }

    if (request->name() == "delay") {

      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }

    reply->set_message(request->name());

    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }

  std::shared_ptr<Channel> self_channel_;
};

void RunServer(uint16_t port) {
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service(server_address);

  ServerBuilder builder;

  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  builder.RegisterService(&service);

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
