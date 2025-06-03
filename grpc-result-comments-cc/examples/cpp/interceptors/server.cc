Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2018 gRPC authors.
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

// Include necessary headers
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/server_interceptor.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "absl/flags/parse.h"
#include "absl/log/initialize.h"

// Handle different include paths for Bazel vs non-Bazel builds
#ifdef BAZEL_BUILD
#include "examples/protos/keyvaluestore.grpc.pb.h"
#else
#include "keyvaluestore.grpc.pb.h"
#endif

// Using declarations for gRPC and protobuf namespaces
using grpc::CallbackServerContext;
using grpc::Server;
using grpc::ServerBidiReactor;
using grpc::ServerBuilder;
using grpc::Status;
using grpc::experimental::InterceptionHookPoints;
using grpc::experimental::Interceptor;
using grpc::experimental::InterceptorBatchMethods;
using grpc::experimental::ServerInterceptorFactoryInterface;
using grpc::experimental::ServerRpcInfo;
using keyvaluestore::KeyValueStore;
using keyvaluestore::Request;
using keyvaluestore::Response;

// Custom interceptor for logging RPC events
class LoggingInterceptor : public Interceptor {
 public:
  void Intercept(InterceptorBatchMethods* methods) override {
    // Check if this is the post-receive initial metadata hook point
    if (methods->QueryInterceptionHookPoint(
            InterceptionHookPoints::POST_RECV_INITIAL_METADATA)) {
      std::cout << "Got a new streaming RPC" << std::endl;
    }
    // Continue processing the RPC
    methods->Proceed();
  }
};

// Factory for creating LoggingInterceptor instances
class LoggingInterceptorFactory : public ServerInterceptorFactoryInterface {
 public:
  Interceptor* CreateServerInterceptor(ServerRpcInfo* info) override {
    return new LoggingInterceptor();
  }
};

// Structure representing a key-value pair
struct kv_pair {
  const char* key;
  const char* value;
};

// Static key-value store data
static const kv_pair kvs_map[] = {
    {"key1", "value1"}, {"key2", "value2"}, {"key3", "value3"},
    {"key4", "value4"}, {"key5", "value5"},
};

// Helper function to lookup a value by key in the static map
const char* get_value_from_map(const char* key) {
  for (size_t i = 0; i < sizeof(kvs_map) / sizeof(kv_pair); ++i) {
    if (strcmp(key, kvs_map[i].key) == 0) {
      return kvs_map[i].value;
    }
  }
  return "";  // Return empty string if key not found
}

// Implementation of the KeyValueStore service
class KeyValueStoreServiceImpl final : public KeyValueStore::CallbackService {
  // Handle GetValues RPC with bidirectional streaming
  ServerBidiReactor<Request, Response>* GetValues(
      CallbackServerContext* context) override {
    // Inner Reactor class to handle the streaming RPC
    class Reactor : public ServerBidiReactor<Request, Response> {
     public:
      explicit Reactor() { StartRead(&request_); }  // Start first read immediately

      // Called when a read operation completes
      void OnReadDone(bool ok) override {
        if (!ok) {
          return Finish(grpc::Status::CANCELLED);  // Client closed connection
        }
        // Set response value from our static map
        response_.set_value(get_value_from_map(request_.key().c_str()));
        StartWrite(&response_);  // Send response back to client
      }

      // Called when a write operation completes
      void OnWriteDone(bool ok) override {
        if (!ok) {
          return Finish(grpc::Status::CANCELLED);  // Client closed connection
        }
        StartRead(&request_);  // Read next request from client
      }

      // Called when RPC is done
      void OnDone() override { delete this; }  // Clean up reactor

     private:
      Request request_;   // Current request from client
      Response response_; // Current response to send to client
    };

    return new Reactor();  // Create new reactor for this RPC
  }
};

// Function to start and run the gRPC server
void RunServer() {
  std::string server_address("0.0.0.0:50051");  // Listen on all interfaces
  KeyValueStoreServiceImpl service;  // Create service instance

  ServerBuilder builder;  // Server configuration builder

  // Add listening port with insecure credentials (for demo purposes)
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Register service and interceptors
  builder.RegisterService(&service);
  std::vector<std::unique_ptr<ServerInterceptorFactoryInterface>> creators;
  creators.push_back(std::unique_ptr<ServerInterceptorFactoryInterface>(
      new LoggingInterceptorFactory()));
  builder.experimental().SetInterceptorCreators(std::move(creators));

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();  // Block until server shuts down
}

// Main entry point
int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  
  // Start the server
  RunServer();

  return 0;
}
```

Key aspects covered in the comments:
1. File header and license information
2. Include statements and their purposes
3. Namespace usage declarations
4. Interceptor implementation details
5. Key-value store data structure and lookup function
6. Service implementation and reactor pattern explanation
7. Server setup and configuration
8. Main function flow

The comments aim to explain both the high-level architecture and specific implementation details while maintaining readability. They cover the gRPC-specific patterns as well as the custom business logic for the key-value store service.