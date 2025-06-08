Here's the commented version of the code:

```python
# Copyright 2021 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The graceful shutdown example for the asyncio Greeter server."""

import asyncio
import logging

import grpc
import helloworld_pb2
import helloworld_pb2_grpc

# Global list to store cleanup coroutines for graceful shutdown
_cleanup_coroutines = []

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of the Greeter service."""
    
    async def SayHello(
        self,
        request: helloworld_pb2.HelloRequest,
        context: grpc.aio.ServicerContext,
    ) -> helloworld_pb2.HelloReply:
        """Handles SayHello RPC call.
        
        Args:
            request: HelloRequest containing the name parameter
            context: Servicer context for RPC
            
        Returns:
            HelloReply with a greeting message
        """
        # Simulate processing time with sleep
        logging.info("Received request, sleeping for 4 seconds...")
        await asyncio.sleep(4)
        logging.info("Sleep completed, responding")
        # Return greeting response with the provided name
        return helloworld_pb2.HelloReply(message="Hello, %s!" % request.name)

async def serve() -> None:
    """Starts the gRPC server and handles graceful shutdown."""
    # Create an async gRPC server
    server = grpc.aio.server()
    
    # Add Greeter service implementation to the server
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    
    # Configure server to listen on all interfaces at port 50051
    listen_addr = "[::]:50051"
    server.add_insecure_port(listen_addr)
    logging.info("Starting server on %s", listen_addr)
    
    # Start the server
    await server.start()

    async def server_graceful_shutdown():
        """Handles the server shutdown gracefully with a 5 second timeout."""
        logging.info("Starting graceful shutdown...")
        # Stop the server with a 5 second grace period
        await server.stop(5)

    # Add the shutdown coroutine to the cleanup list
    _cleanup_coroutines.append(server_graceful_shutdown())
    
    # Wait for server termination
    await server.wait_for_termination()

if __name__ == "__main__":
    # Configure basic logging
    logging.basicConfig(level=logging.INFO)
    
    # Get the event loop
    loop = asyncio.get_event_loop()
    try:
        # Run the server until completion
        loop.run_until_complete(serve())
    finally:
        # Ensure cleanup coroutines are executed before exit
        loop.run_until_complete(*_cleanup_coroutines)
        # Close the event loop
        loop.close()
```