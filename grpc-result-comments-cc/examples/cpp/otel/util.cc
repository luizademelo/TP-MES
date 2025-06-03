Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

// Define HAVE_ABSEIL if not already defined to enable Abseil library features
#ifndef HAVE_ABSEIL
#define HAVE_ABSEIL
#endif

// gRPC core headers
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/xds_server_builder.h>

// Standard library headers for threading
#include <condition_variable>
#include <mutex>

// OpenTelemetry metrics headers
#include "opentelemetry/sdk/metrics/view/instrument_selector_factory.h"
#include "opentelemetry/sdk/metrics/view/meter_selector_factory.h"
#include "opentelemetry/sdk/metrics/view/view_factory.h"

// Conditional includes based on build system
#ifdef BAZEL_BUILD
#include "examples/cpp/otel/util.h"
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#include "util.h"
#endif

// Using declarations for gRPC and protobuf types
using grpc::CallbackServerContext;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerUnaryReactor;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

/**
 * Adds a latency view configuration to the OpenTelemetry meter provider.
 * 
 * @param provider The meter provider to configure
 * @param name The name of the metric instrument
 * @param unit The unit of measurement for the metric
 * 
 * Configures histogram aggregation with specific bucket boundaries for latency measurements.
 */
void AddLatencyView(opentelemetry::sdk::metrics::MeterProvider* provider,
                    const std::string& name, const std::string& unit) {
  auto histogram_config = std::make_shared<
      opentelemetry::sdk::metrics::HistogramAggregationConfig>();
  histogram_config->boundaries_ = {
      0,     0.00001, 0.00005, 0.0001, 0.0003, 0.0006, 0.0008, 0.001, 0.002,
      0.003, 0.004,   0.005,   0.006,  0.008,  0.01,   0.013,  0.016, 0.02,
      0.025, 0.03,    0.04,    0.05,   0.065,  0.08,   0.1,    0.13,  0.16,
      0.2,   0.25,    0.3,     0.4,    0.5,    0.65,   0.8,    1,     2,
      5,     10,      20,      50,     100};
  provider->AddView(
      opentelemetry::sdk::metrics::InstrumentSelectorFactory::Create(
          opentelemetry::sdk::metrics::InstrumentType::kHistogram, name, unit),
      opentelemetry::sdk::metrics::MeterSelectorFactory::Create(
          "grpc-c++", grpc::Version(), ""),
      opentelemetry::sdk::metrics::ViewFactory::Create(
          name, "", unit,
          opentelemetry::sdk::metrics::AggregationType::kHistogram,
          std::move(histogram_config)));
}

namespace {

/**
 * Client implementation for the Greeter service.
 */
class GreeterClient {
 public:
  /**
   * Constructs a GreeterClient connected to the specified channel.
   * @param channel The gRPC channel to use for communication
   */
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  /**
   * Sends a SayHello RPC to the server.
   * @param user The name to include in the greeting
   * @return The server's response message or an error message if RPC fails
   */
  std::string SayHello(const std::string& user) {
    // Prepare the request
    HelloRequest request;
    request.set_name(user);

    HelloReply reply;
    ClientContext context;

    // Synchronization primitives for async call
    std::mutex mu;
    std::condition_variable cv;
    bool done = false;
    Status status;

    // Make asynchronous call
    stub_->async()->SayHello(&context, &request, &reply,
                             [&mu, &cv, &done, &status](Status s) {
                               status = std::move(s);
                               std::lock_guard<std::mutex> lock(mu);
                               done = true;
                               cv.notify_one();
                             });

    // Wait for the async call to complete
    std::unique_lock<std::mutex> lock(mu);
    while (!done) {
      cv.wait(lock);
    }

    // Handle response
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;  // gRPC stub for making RPC calls
};

/**
 * Server implementation of the Greeter service.
 */
class GreeterServiceImpl final : public Greeter::CallbackService {
  /**
   * Implementation of the SayHello RPC method.
   * @param context Server context
   * @param request The incoming request
   * @param reply The response to send back
   * @return A reactor to handle the RPC completion
   */
  ServerUnaryReactor* SayHello(CallbackServerContext* context,
                               const HelloRequest* request,
                               HelloReply* reply) override {
    // Prepare response
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());

    // Complete the RPC
    ServerUnaryReactor* reactor = context->DefaultReactor();
    reactor->Finish(Status::OK);
    return reactor;
  }
};

}  // namespace

/**
 * Runs a standard gRPC server on the specified port.
 * @param port The port number to listen on
 */
void RunServer(uint16_t port) {
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;

  // Enable standard gRPC services
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  
  // Build and start server
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for server shutdown
  server->Wait();
}

/**
 * Runs an xDS-enabled gRPC server on the specified port.
 * @param port The port number to listen on
 */
void RunXdsEnabledServer(uint16_t port) {
  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GreeterServiceImpl service;

  // Enable standard gRPC services
  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  
  // Build and start xDS-enabled server
  grpc::XdsServerBuilder builder;
  builder.AddListeningPort(
      server_address,
      grpc::XdsServerCredentials(grpc::InsecureServerCredentials()));
  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for server shutdown
  server->Wait();
}

/**
 * Runs a client that connects to the specified target and makes periodic RPCs.
 * @param target_str The server address to connect to
 */
void RunClient(const std::string& target_str) {
  // Create channel with xDS credentials
  grpc::ChannelArguments args;
  GreeterClient greeter(grpc::CreateCustomChannel(
      target_str, grpc::XdsCredentials(grpc::InsecureChannelCredentials()),
      args));

  // Continuously make RPC calls every second
  while (true) {
    std::string user("world");
    std::string reply = greeter.SayHello(user);
    std::cout << "Greeter received: " << reply << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
```