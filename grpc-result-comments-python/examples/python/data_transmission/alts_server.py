Here's the commented version of the code:

```c++
# Copyright 2020 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The example of using ALTS credentials to setup gRPC server in python.

The example would only successfully run in GCP environment."""

# Import required modules
from concurrent import futures  # For thread pool execution
import grpc  # gRPC core library
import demo_pb2_grpc  # Auto-generated gRPC service stubs
from server import DemoServer  # Custom server implementation

# Define server address and port
SERVER_ADDRESS = "localhost:23333"

def main():
    """Main function to setup and run the gRPC server with ALTS credentials."""
    
    # Create a gRPC server with thread pool executor
    svr = grpc.server(futures.ThreadPoolExecutor())
    
    # Add the DemoServer service implementation to the gRPC server
    demo_pb2_grpc.add_GRPCDemoServicer_to_server(DemoServer(), svr)
    
    # Add secure port to the server using ALTS credentials
    # ALTS (Application Layer Transport Security) is GCP's mutual TLS authentication
    svr.add_secure_port(
        SERVER_ADDRESS, server_credentials=grpc.alts_server_credentials()
    )
    
    # Start the server
    print("------------------start Python GRPC server with ALTS encryption")
    svr.start()
    
    # Keep the server running until terminated
    svr.wait_for_termination()

if __name__ == "__main__":
    # Entry point of the script
    main()
```

Key additions:
1. Added comments explaining each major section of the code
2. Documented the purpose of the main function
3. Explained what ALTS credentials are
4. Added comments for the server setup and execution flow
5. Noted the entry point of the script
6. Explained the purpose of each import

The comments maintain a professional tone while being clear and helpful for future developers who might need to maintain or modify this code.