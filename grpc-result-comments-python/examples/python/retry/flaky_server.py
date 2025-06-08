Here's the commented version of the code:

```c++
# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""A flaky backend for the gRPC Python retry example."""

import asyncio
import collections
import logging
import random

import grpc

# Load protocol buffer definitions and gRPC services from helloworld.proto
helloworld_pb2, helloworld_pb2_grpc = grpc.protos_and_services(
    "helloworld.proto"
)

class ErrorInjectingGreeter(helloworld_pb2_grpc.GreeterServicer):
    """A gRPC servicer that intentionally fails requests to test retry logic."""
    
    def __init__(self):
        # Track request counts per client (peer)
        self._counter = collections.defaultdict(int)

    async def SayHello(
        self,
        request: helloworld_pb2.HelloRequest,
        context: grpc.aio.ServicerContext,
    ) -> helloworld_pb2.HelloReply:
        """
        Implementation of the SayHello RPC method with intentional failures.
        
        Args:
            request: The HelloRequest containing the client's name.
            context: The gRPC context for the RPC call.
            
        Returns:
            HelloReply with a greeting message if successful.
            
        Behavior:
            - Fails with 75% probability for the first 4 requests from each client
            - After 4 requests or on 25% chance, responds successfully
            - Uses UNAVAILABLE status code for injected errors
        """
        # Increment request counter for this client
        self._counter[context.peer()] += 1
        
        # Only inject errors for the first 4 requests from a client
        if self._counter[context.peer()] < 5:
            # 75% chance to inject an error
            if random.random() < 0.75:
                logging.info("Injecting error to RPC from %s", context.peer())
                await context.abort(
                    grpc.StatusCode.UNAVAILABLE, "injected error"
                )
        
        # If we get here, return a successful response
        logging.info("Successfully responding to RPC from %s", context.peer())
        return helloworld_pb2.HelloReply(message="Hello, %s!" % request.name)

async def serve() -> None:
    """Start and run the gRPC server with the ErrorInjectingGreeter service."""
    # Create async gRPC server
    server = grpc.aio.server()
    
    # Add our error-injecting service to the server
    helloworld_pb2_grpc.add_GreeterServicer_to_server(
        ErrorInjectingGreeter(), server
    )
    
    # Configure server to listen on all interfaces, port 50051
    listen_addr = "[::]:50051"
    server.add_insecure_port(listen_addr)
    
    # Start the server
    logging.info("Starting flaky server on %s", listen_addr)
    await server.start()
    await server.wait_for_termination()

if __name__ == "__main__":
    # Configure basic logging and start the server
    logging.basicConfig(level=logging.INFO)
    asyncio.run(serve())
```