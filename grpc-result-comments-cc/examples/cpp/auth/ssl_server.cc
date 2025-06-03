Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

// Include necessary headers
#include <grpcpp/grpcpp.h>  // Main gRPC C++ library
#include <iostream>         // For console I/O
#include <memory>           // For smart pointers
#include <string>           // For string operations

// Include Abseil libraries for flags, logging, and string formatting
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/strings/str_format.h"
#include "helper.h"  // For helper functions like LoadStringFromFile

// Include generated protobuf headers with different paths for Bazel vs non-Bazel builds
#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

// Define a command line flag for server port with default value 50051
ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

// Using declarations to simplify code
using grpc::CallbackServerContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerUnaryReactor;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Implementation of the Greeter service
class GreeterServiceImpl final : public Greeter::CallbackService {
  // Override the SayHello method to handle incoming requests
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    // Create response message by combining prefix with client's name
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());

    // Get the default reactor and finish the call with OK status
    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }
};

// Define paths to SSL certificate and key files with different paths for Bazel vs non-Bazel builds
#ifdef BAZEL_BUILD
constexpr char kServerCertPath[] =
    "examples/cpp/auth/credentials/localhost.crt";
constexpr char kServerKeyPath[] = "examples/cpp/auth/credentials/localhost.key";
#else
constexpr char kServerCertPath[] = "credentials/localhost.crt";
constexpr char kServerKeyPath[] = "credentials/localhost.key";
#endif

// Function to start and run the gRPC server
void RunServer(uint16_t port) {
  // Create server address string using the specified port
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;
  ServerBuilder builder;

  // Load SSL key and certificate files and configure SSL options
  grpc::SslServerCredentialsOptions::PemKeyCertPair key_cert_pair = {
      LoadStringFromFile(kServerKeyPath), LoadStringFromFile(kServerCertPath)};
  grpc::SslServerCredentialsOptions ssl_options;
  ssl_options.pem_key_cert_pairs.emplace_back(key_cert_pair);

  // Configure server to listen on the specified address with SSL credentials
  builder.AddListeningPort(server_address,
                           grpc::SslServerCredentials(ssl_options));

  // Register our service implementation with the server
  builder.RegisterService(&service);

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown (blocking call)
  server->Wait();
}

// Main entry point
int main(int argc, char** argv) {
  // Parse command line flags and initialize logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  
  // Run the server with the specified port (from command line or default)
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}
```

The comments explain:
1. The purpose of each include statement
2. The command line flag definition
3. The service implementation and its methods
4. The SSL certificate configuration
5. The server setup and startup process
6. The main program flow

The comments are designed to help future developers understand:
- What each part of the code does
- Why certain design decisions were made
- How the different components work together
- Where to find related configuration files
- The overall program flow