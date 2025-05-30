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

class KeyValueStoreClient
    : public grpc::ClientBidiReactor<HelloRequest, HelloReply> {
 public:
  KeyValueStoreClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {
    stub_->async()->SayHelloBidiStream(&context_, this);
    request_.set_name("Begin");
    StartWrite(&request_);
    StartCall();
  }

  void OnReadDone(bool ok) override {
    if (ok) {
      std::cout << request_.name() << " : " << response_.message() << std::endl;
      if (++counter_ < 10) {
        request_.set_name(absl::StrCat("Count ", counter_));
        StartWrite(&request_);
      } else {

        context_.TryCancel();
      }
    }
  }

  void OnWriteDone(bool ok) override {
    if (ok) {
      StartRead(&response_);
    }
  }

  void OnDone(const grpc::Status& status) override {
    if (!status.ok()) {
      if (status.error_code() == StatusCode::CANCELLED) {

        std::cout << "RPC Cancelled!" << std::endl;
      } else {
        std::cout << "RPC Failed: " << status.error_code() << ": "
                  << status.error_message() << std::endl;
      }
    }
    std::unique_lock<std::mutex> l(mu_);
    done_ = true;
    cv_.notify_all();
  }

  void Await() {
    std::unique_lock<std::mutex> l(mu_);
    while (!done_) {
      cv_.wait(l);
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
  size_t counter_ = 0;
  ClientContext context_;
  bool done_ = false;
  HelloRequest request_;
  HelloReply response_;
  std::mutex mu_;
  std::condition_variable cv_;
};

int main(int argc, char** argv) {
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  std::string target_str = absl::GetFlag(FLAGS_target);
  KeyValueStoreClient client(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  client.Await();
  return 0;
}
