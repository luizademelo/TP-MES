Here's the commented version of the code:

```python
# Copyright 2024 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Example gRPC server that applies back-pressure on client"""

from concurrent import futures
import logging
import time

import grpc
import helloworld_pb2
import helloworld_pb2_grpc
import helpers

# Define the port number the server will listen on
_PORT = "50051"

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of Greeter service with bidirectional streaming RPC."""
    
    def SayHelloBidiStream(self, request_iterator, unused_context):
        """
        Bidirectional streaming RPC handler for greeting messages.
        Implements back-pressure by delaying responses and tracking message sizes.
        
        Args:
            request_iterator: Iterator for incoming HelloRequest messages
            unused_context: gRPC context (unused in this implementation)
        
        Yields:
            HelloReply messages in response to received requests
        """
        
        # Initial delay to simulate processing time
        time.sleep(5)

        # Counter for total bytes received from client
        bytes_received = 0

        # Process incoming requests (enumerate starts counting at 1)
        for i, request in enumerate(request_iterator, start=1):
            # Accumulate total bytes received
            bytes_received += len(request.name)
            
            # Print progress every 10 requests
            if (i % 10) == 0:
                print(
                    f"{helpers.get_current_time()}   "
                    f"Request {i}:   Received {bytes_received} bytes in total"
                )

            # Artificial delay to simulate processing and create back-pressure
            time.sleep(1)

            # Create and yield response message
            msg = "Hello!"
            yield helloworld_pb2.HelloReply(message=msg)

            # Print status update every 10 requests
            if (i % 10) == 0:
                print(
                    f"{helpers.get_current_time()}   "
                    f"Request {i}:   Sent {bytes_received} bytes in total\n"
                )

def serve():
    """Starts the gRPC server with configured back-pressure settings."""
    
    # Create gRPC server with:
    # - Thread pool of 10 workers
    # - Specific HTTP/2 frame size limit
    # - BDP probing disabled
    # - Limited to 1 concurrent stream
    server = grpc.server(
        futures.ThreadPoolExecutor(max_workers=10),
        options=[
            ("grpc.http2.max_frame_size", 16384),  # Max frame size of 16KB
            ("grpc.http2.bdp_probe", 0),          # Disable bandwidth delay product probing
            ("grpc.max_concurrent_streams", 1),   # Limit to 1 active stream
        ],
    )
    
    # Add Greeter service implementation to the server
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)

    # Bind server to port and start
    server.add_insecure_port("[::]:" + _PORT)
    server.start()
    print("Server started, listening on " + _PORT)
    
    # Keep server running until terminated
    server.wait_for_termination()

if __name__ == "__main__":
    # Configure basic logging and start the server
    logging.basicConfig()
    serve()
```