// Copyright 2023 gRPC authors.

#include <grpcpp/grpcpp.h>

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  void SayHello(const std::string& user) {

    HelloRequest request;
    request.set_name(user);

    HelloReply reply;

    ClientContext context;

    std::mutex mu;
    std::condition_variable cv;
    bool done = false;
    Status status;
    std::cout << absl::StrFormat("### Send: SayHello(name=%s)", user)
              << std::endl;
    stub_->async()->SayHello(&context, &request, &reply, [&](Status s) {
      status = std::move(s);
      std::lock_guard<std::mutex> lock(mu);
      done = true;
      cv.notify_one();
    });
    std::unique_lock<std::mutex> lock(mu);
    while (!done) {
      cv.wait(lock);
    }

    if (status.ok()) {
      std::cout << absl::StrFormat("Ok. ReplyMessage=%s", reply.message())
                << std::endl;
    } else {
      std::cout << absl::StrFormat("Failed. Code=%d Message=%s",
                                   status.error_code(), status.error_message())
                << std::endl;
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  std::string target_str = absl::GetFlag(FLAGS_target);

  GreeterClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

  greeter.SayHello("");

  greeter.SayHello("ItsTooLongName");

  greeter.SayHello("World");
  return 0;
}
