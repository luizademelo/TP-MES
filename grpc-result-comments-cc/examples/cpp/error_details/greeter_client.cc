Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

// Include necessary headers for gRPC, mutexes, I/O operations, and string handling
#include <grpcpp/grpcpp.h>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>

// Include Abseil libraries for command line flags, logging, and string formatting
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"

// Include protocol buffer headers with different paths for Bazel and non-Bazel builds
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#include "google/rpc/error_details.pb.h"
#include "src/proto/grpc/status/status.pb.h"
#else
#include "error_details.pb.h"
#include "helloworld.grpc.pb.h"
#include "status.pb.h"
#endif

// Define a command line flag for the server address with default value "localhost:50051"
ABSL_FLAG(std::string, target, "localhost:50051", "Server address");

// Use declarations for gRPC and protocol buffer classes
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Client class for the Greeter service
class GreeterClient {
 public:
  // Constructor that takes a gRPC channel and creates a stub for the Greeter service
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Method to send a greeting request to the server
  void SayHello(const std::string& user) {
    // Create request and set the name field
    HelloRequest request;
    request.set_name(user);

    // Response object and client context
    HelloReply reply;
    ClientContext context;

    // Synchronization primitives for async call
    std::mutex mu;
    std::condition_variable cv;
    bool done = false;
    Status status;

    // Log the outgoing request
    std::cout << absl::StrFormat("### Send: SayHello(name=%s)", user)
              << std::endl;

    // Make asynchronous call to SayHello
    stub_->async()->SayHello(&context, &request, &reply, [&](Status s) {
      // Callback function that runs when the RPC completes
      status = std::move(s);
      std::lock_guard<std::mutex> lock(mu);
      done = true;
      cv.notify_one();  // Notify waiting thread
    });

    // Wait for the async call to complete
    std::unique_lock<std::mutex> lock(mu);
    while (!done) {
      cv.wait(lock);
    }

    // Handle the response
    if (status.ok()) {
      std::cout << absl::StrFormat("Ok. ReplyMessage=%s", reply.message())
                << std::endl;
    } else {
      // Log error details if the call failed
      std::cout << absl::StrFormat("Failed. Code=%d Message=%s",
                                   status.error_code(), status.error_message())
                << std::endl;
      PrintErrorDetails(status);
    }
  }

  // Helper method to print detailed error information from the server
  void PrintErrorDetails(grpc::Status status) {
    auto error_details = status.error_details();
    if (error_details.empty()) {
      return;
    }

    // Parse the error details protobuf
    google::rpc::Status s;
    if (!s.ParseFromString(error_details)) {
      std::cout << "Failed to deserialize `error_details`" << std::endl;
      return;
    }

    // Print each error detail
    std::cout << absl::StrFormat("Details:") << std::endl;
    for (auto& detail : s.details()) {
      google::rpc::QuotaFailure quota_failure;
      if (detail.UnpackTo(&quota_failure)) {
        // Handle quota failure details specifically
        for (auto& violation : quota_failure.violations()) {
          std::cout << absl::StrFormat("- Quota: subject=%s description=%s",
                                       violation.subject(),
                                       violation.description())
                    << std::endl;
        }
      } else {
        // Handle unknown error types
        std::cout << "Unknown error_detail: " + detail.type_url() << std::endl;
      }
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;  // gRPC stub for making RPC calls
};

int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();

  // Get server address from command line flags
  std::string target_str = absl::GetFlag(FLAGS_target);

  // Create client with insecure channel credentials
  GreeterClient greeter(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

  // Make two greeting requests
  greeter.SayHello("World");
  greeter.SayHello("World");
  
  return 0;
}
```