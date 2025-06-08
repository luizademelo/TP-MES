Here's the commented version of the code:

```python
# Copyright 2019 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""This example sends out rich error status from server-side."""

from concurrent import futures
import logging
import threading

from google.protobuf import any_pb2
from google.rpc import code_pb2
from google.rpc import error_details_pb2
from google.rpc import status_pb2
import grpc
from grpc_status import rpc_status

from examples.protos import helloworld_pb2
from examples.protos import helloworld_pb2_grpc

def create_greet_limit_exceed_error_status(name):
    """Creates a rich error status for when greeting limit is exceeded.
    
    Args:
        name: The name of the person who has exceeded the greeting limit.
        
    Returns:
        A Status object containing:
        - RESOURCE_EXHAUSTED error code
        - Descriptive message
        - Details about the quota violation
    """
    # Create an Any message to hold the error details
    detail = any_pb2.Any()
    # Pack the QuotaFailure details into the Any message
    detail.Pack(
        error_details_pb2.QuotaFailure(
            violations=[
                error_details_pb2.QuotaFailure.Violation(
                    subject="name: %s" % name,
                    description="Limit one greeting per person",
                )
            ],
        )
    )
    # Return a Status object with error details
    return status_pb2.Status(
        code=code_pb2.RESOURCE_EXHAUSTED,
        message="Request limit exceeded.",
        details=[detail],
    )

class LimitedGreeter(helloworld_pb2_grpc.GreeterServicer):
    """Greeter service implementation that limits greetings to once per name."""
    
    def __init__(self):
        """Initializes the greeter with:
        - A reentrant lock for thread safety
        - A set to track already greeted names
        """
        self._lock = threading.RLock()  # Thread-safe lock
        self._greeted = set()  # Set of names that have been greeted

    def SayHello(self, request, context):
        """Handles SayHello RPC requests.
        
        Args:
            request: The HelloRequest containing the name to greet.
            context: The RPC context.
            
        Returns:
            HelloReply with greeting message if name hasn't been greeted before.
            
        Raises:
            Aborts with rich error status if name has already been greeted.
        """
        with self._lock:  # Ensure thread-safe access to greeted set
            if request.name in self._greeted:
                # Create and return rich error status if name was already greeted
                rich_status = create_greet_limit_exceed_error_status(
                    request.name
                )
                context.abort_with_status(rpc_status.to_status(rich_status))
            else:
                # Add new name to greeted set
                self._greeted.add(request.name)
        # Return normal greeting response
        return helloworld_pb2.HelloReply(message="Hello, %s!" % request.name)

def create_server(server_address):
    """Creates and configures a gRPC server.
    
    Args:
        server_address: The address to bind the server to.
        
    Returns:
        A tuple containing:
        - The configured gRPC server
        - The port number the server is bound to
    """
    # Create server with thread pool executor
    server = grpc.server(futures.ThreadPoolExecutor())
    # Add LimitedGreeter service to the server
    helloworld_pb2_grpc.add_GreeterServicer_to_server(LimitedGreeter(), server)
    # Bind server to the specified address
    port = server.add_insecure_port(server_address)
    return server, port

def serve(server):
    """Starts and runs the gRPC server until terminated.
    
    Args:
        server: The gRPC server to run.
    """
    server.start()
    server.wait_for_termination()

def main():
    """Main function that creates and runs the gRPC server."""
    # Create server bound to port 50051
    server, unused_port = create_server("[::]:50051")
    # Start serving
    serve(server)

if __name__ == "__main__":
    # Configure basic logging and start the server
    logging.basicConfig()
    main()
```