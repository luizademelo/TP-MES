Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The Python implementation of the GRPC helloworld.Greeter server."""

# Import required modules
from concurrent import futures  # For thread pool execution
import logging  # For basic logging

import grpc  # gRPC core library
import helloworld_pb2  # Generated protocol buffer messages
import helloworld_pb2_grpc  # Generated gRPC service stubs

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of the Greeter service defined in the proto file."""
    
    def SayHello(self, request, context):
        """Implementation of the SayHello RPC method.
        
        Args:
            request: The HelloRequest message containing the 'name' field.
            context: gRPC context for RPC metadata, cancellation, etc.
            
        Returns:
            A HelloReply message with a personalized greeting.
        """
        return helloworld_pb2.HelloReply(message="Hello, %s!" % request.name)

def serve():
    """Starts the gRPC server and listens for incoming connections."""
    # Define the port to listen on
    port = "50051"
    
    # Create a gRPC server with a thread pool of 10 workers
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    
    # Add the Greeter service implementation to the server
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    
    # Bind the server to the port (without TLS/SSL)
    server.add_insecure_port("[::]:" + port)
    
    # Start the server
    server.start()
    print("Server started, listening on " + port)
    
    # Keep the server running until terminated
    server.wait_for_termination()

if __name__ == "__main__":
    # Configure basic logging and start the server
    logging.basicConfig()
    serve()
```