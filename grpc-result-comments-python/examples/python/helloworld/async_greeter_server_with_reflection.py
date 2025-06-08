Here's the commented version of the code:

```c++
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The reflection-enabled version of gRPC AsyncIO helloworld.Greeter server."""

import asyncio
import logging

import grpc
from grpc_reflection.v1alpha import reflection
import helloworld_pb2
import helloworld_pb2_grpc

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of the gRPC Greeter service with reflection enabled."""
    
    async def SayHello(
        self,
        request: helloworld_pb2.HelloRequest,
        context: grpc.aio.ServicerContext,
    ) -> helloworld_pb2.HelloReply:
        """Implementation of the SayHello RPC method.
        
        Args:
            request: HelloRequest containing the 'name' field
            context: gRPC servicer context
            
        Returns:
            HelloReply with a greeting message containing the request's name
        """
        return helloworld_pb2.HelloReply(message="Hello, %s!" % request.name)

async def serve() -> None:
    """Configures and starts the gRPC server with reflection service enabled."""
    # Create an asynchronous gRPC server
    server = grpc.aio.server()
    
    # Add Greeter service implementation to the server
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    
    # Define service names for reflection (both our service and reflection service)
    SERVICE_NAMES = (
        helloworld_pb2.DESCRIPTOR.services_by_name["Greeter"].full_name,
        reflection.SERVICE_NAME,
    )
    
    # Enable server reflection
    reflection.enable_server_reflection(SERVICE_NAMES, server)
    
    # Listen on port 50051 on all interfaces (IPv6 '::' means all IPv4 and IPv6)
    server.add_insecure_port("[::]:50051")
    
    # Start the server
    await server.start()
    
    # Keep server running until terminated
    await server.wait_for_termination()

if __name__ == "__main__":
    # Configure basic logging
    logging.basicConfig()
    
    # Run the async server using asyncio event loop
    asyncio.run(serve())
```

Key improvements in the comments:
1. Added class-level docstring for the Greeter service
2. Detailed the SayHello method parameters and return value
3. Explained the serve() function's purpose and its steps
4. Clarified the purpose of SERVICE_NAMES and reflection
5. Explained the port binding syntax ("[::]:50051")
6. Added comments for the main execution block
7. Maintained all existing license and header information

The comments now provide a clear understanding of:
- The service implementation
- The server setup process
- The reflection configuration
- The execution flow
- Important configuration details