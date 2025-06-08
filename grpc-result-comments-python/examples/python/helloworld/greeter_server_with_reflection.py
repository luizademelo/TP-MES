Here's the commented version of the code:

```c++
# Copyright 2018 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The reflection-enabled version of gRPC helloworld.Greeter server."""

from concurrent import futures
import logging

import grpc
from grpc_reflection.v1alpha import reflection
import helloworld_pb2
import helloworld_pb2_grpc

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of the gRPC Greeter service."""
    
    def SayHello(self, request, context):
        """Implementation of the SayHello RPC method.
        
        Args:
            request: The HelloRequest message containing the 'name' field.
            context: The RPC context.
            
        Returns:
            A HelloReply message with a greeting containing the request's name.
        """
        return helloworld_pb2.HelloReply(message="Hello, %s!" % request.name)

def serve():
    """Starts the gRPC server with reflection enabled.
    
    The server:
    1. Creates a thread pool for handling RPCs
    2. Adds the Greeter service implementation
    3. Enables server reflection for service discovery
    4. Binds to port 50051
    5. Starts the server and waits for termination
    """
    # Create a gRPC server with a thread pool of 10 workers
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    
    # Add the Greeter service implementation to the server
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    
    # Prepare the list of service names for reflection
    SERVICE_NAMES = (
        helloworld_pb2.DESCRIPTOR.services_by_name["Greeter"].full_name,
        reflection.SERVICE_NAME,  # Standard reflection service name
    )
    
    # Enable server reflection
    reflection.enable_server_reflection(SERVICE_NAMES, server)
    
    # Bind the server to port 50051 on all interfaces
    server.add_insecure_port("[::]:50051")
    
    # Start the server
    server.start()
    
    # Keep the server running until terminated
    server.wait_for_termination()

if __name__ == "__main__":
    # Configure basic logging
    logging.basicConfig()
    
    # Start the server
    serve()
```