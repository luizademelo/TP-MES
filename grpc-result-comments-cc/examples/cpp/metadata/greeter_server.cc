Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2015 gRPC authors.
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

#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

// Implementation of the Greeter service
class GreeterServiceImpl final : public Greeter::Service {
  // Handles SayHello RPC call
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override {
    std::string prefix("Hello ");

    // Print all client metadata headers
    std::cout << "Client metadata: " << std::endl;
    const std::multimap<grpc::string_ref, grpc::string_ref> metadata =
        context->client_metadata();
    for (auto iter = metadata.begin(); iter != metadata.end(); ++iter) {
      std::cout << "Header key: " << iter->first << ", value: ";

      // Check if the header is a binary header (ends with "-bin")
      size_t isbin = iter->first.find("-bin");
      if ((isbin != std::string::npos) && (isbin + 4 == iter->first.size())) {
        // Print binary data in hex format
        std::cout << std::hex;
        for (auto c : iter->second) {
          std::cout << static_cast<unsigned int>(c);
        }
        std::cout << std::dec;
      } else {
        // Print regular string value
        std::cout << iter->second;
      }
      std::cout << std::endl;
    }

    // Add custom metadata to response
    context->AddInitialMetadata("custom-server-metadata",
                                "initial metadata value");
    context->AddTrailingMetadata("custom-trailing-metadata",
                                 "trailing metadata value");
    
    // Set the reply message and return OK status
    reply->set_message(prefix + request->name());
    return Status::OK;
  }
};

// Starts the gRPC server
void RunServer() {
  std::string server_address("0.0.0.0:50051");  // Listen on all interfaces on port 50051
  GreeterServiceImpl service;  // Create service implementation instance

  ServerBuilder builder;  // Create server builder

  // Add listening port with insecure credentials (no encryption)
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  // Register our service implementation
  builder.RegisterService(&service);

  // Build and start the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown (blocking call)
  server->Wait();
}

int main(int argc, char** argv) {
  // Initialize command line parsing and logging
  absl::ParseCommandLine(argc, argv);
  absl::InitializeLog();
  
  // Start the server
  RunServer();

  return 0;
}
```

Key additions in the comments:
1. Added explanation of the Greeter service implementation class
2. Documented the SayHello RPC method including:
   - Client metadata handling
   - Binary header detection and special handling
   - Response metadata addition
   - Reply message construction
3. Documented the server startup process:
   - Address binding
   - Service registration
   - Server building and starting
4. Added comments for main() function initialization
5. Explained the insecure credentials usage
6. Added notes about blocking calls and server lifecycle

The comments provide a clear understanding of:
- The gRPC service implementation
- Request/response handling
- Metadata processing
- Server configuration and lifecycle
- Special cases like binary header handling