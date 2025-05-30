// Copyright 2023 gRPC authors.

#include <grpcpp/grpcpp.h>

#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_cat.h"

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::StatusCode;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

void unaryCall(std::shared_ptr<Channel> channel, std::string label,
               std::string message, grpc::StatusCode expected_code) {
  std::unique_ptr<Greeter::Stub> stub = Greeter::NewStub(channel);

  HelloRequest request;
  request.set_name(message);

  HelloReply reply;

  ClientContext context;

  context.set_deadline(std::chrono::system_clock::now() +
                       std::chrono::seconds(1));

  std::mutex mu;
  std::condition_variable cv;
  bool done = false;
  Status status;
  stub->async()->SayHello(&context, &request, &reply,
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

  std::cout << "[" << label << "] wanted = " << expected_code
            << ", got = " << status.error_code() << std::endl;
}

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  std::string target_str = absl::GetFlag(FLAGS_target);

  std::shared_ptr<Channel> channel =
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials());

  unaryCall(channel, "Successful request", "world", grpc::StatusCode::OK);
  unaryCall(channel, "Exceeds deadline", "delay",
            grpc::StatusCode::DEADLINE_EXCEEDED);
  unaryCall(channel, "Successful request with propagated deadline",
            "[propagate me]world", grpc::StatusCode::OK);
  unaryCall(channel, "Exceeds propagated deadline",
            "[propagate me][propagate me]world",
            grpc::StatusCode::DEADLINE_EXCEEDED);
  return 0;
}
