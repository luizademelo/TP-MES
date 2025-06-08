Here's the commented version of the code:

```c++
# Copyright 2019 the gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""The Python implementation of the GRPC helloworld.Greeter client."""

# Import necessary libraries
from concurrent import futures  # For thread pool execution
import contextlib  # For context manager utilities
import datetime  # For date/time operations
import logging  # For logging capabilities
import unittest  # For unit testing framework

# Protocol Buffer imports
from google.protobuf import duration_pb2  # For duration operations
from google.protobuf import timestamp_pb2  # For timestamp operations
import grpc  # gRPC core library
import helloworld_pb2  # Generated protocol buffer messages
import helloworld_pb2_grpc  # Generated gRPC services

# Constants
_HOST = "localhost"  # Host address for the server
_SERVER_ADDRESS = "{}:0".format(_HOST)  # Server address with dynamic port

# Greeter service implementation
class Greeter(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of Greeter service with SayHello method."""
    
    def SayHello(self, request, context):
        """Handles SayHello RPC call.
        
        Args:
            request: HelloRequest containing name and request_initiation timestamp
            context: RPC context
            
        Returns:
            HelloReply with greeting message and request duration
        """
        # Calculate time elapsed since request initiation
        request_in_flight = (
            datetime.datetime.now() - request.request_initiation.ToDatetime()
        )
        # Convert timedelta to Duration proto
        request_duration = duration_pb2.Duration()
        request_duration.FromTimedelta(request_in_flight)
        # Return response with greeting and duration
        return helloworld_pb2.HelloReply(
            message="Hello, %s!" % request.name,
            request_duration=request_duration,
        )

@contextlib.contextmanager
def _listening_server():
    """Context manager for creating and managing a gRPC server.
    
    Yields:
        The port number the server is listening on.
    """
    # Create server with thread pool executor
    server = grpc.server(futures.ThreadPoolExecutor())
    # Add Greeter service to the server
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    # Bind server to an available port
    port = server.add_insecure_port(_SERVER_ADDRESS)
    server.start()
    try:
        yield port  # Yield control to the caller with the port number
    finally:
        # Ensure server is stopped when context exits
        server.stop(0)

class ImportTest(unittest.TestCase):
    """Test case for verifying gRPC service functionality."""
    
    def test_import(self):
        """Tests the gRPC service by making a SayHello RPC call."""
        with _listening_server() as port:
            # Create insecure channel to the server
            with grpc.insecure_channel("{}:{}".format(_HOST, port)) as channel:
                # Create client stub
                stub = helloworld_pb2_grpc.GreeterStub(channel)
                # Create and set current timestamp
                request_timestamp = timestamp_pb2.Timestamp()
                request_timestamp.GetCurrentTime()
                # Make RPC call
                response = stub.SayHello(
                    helloworld_pb2.HelloRequest(
                        name="you",
                        request_initiation=request_timestamp,
                    ),
                    wait_for_ready=True,
                )
                # Verify response
                self.assertEqual(response.message, "Hello, you!")
                self.assertGreater(response.request_duration.nanos, 0)

if __name__ == "__main__":
    # Configure basic logging and run tests
    logging.basicConfig()
    unittest.main()
```

Key improvements made:
1. Added detailed docstrings for classes and methods
2. Added comments explaining the purpose of each import
3. Added comments for important code blocks and logic
4. Documented the context manager functionality
5. Explained the test case and its assertions
6. Maintained consistent comment style throughout
7. Added comments for protocol buffer operations
8. Documented the server creation and management process

The comments are designed to help future developers understand:
- The overall structure of the code
- The purpose of each component
- The flow of execution
- The key operations being performed
- The expected behavior of the system