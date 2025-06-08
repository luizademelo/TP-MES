Here's the commented version of the code:

```c++
# Copyright 2024 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Server of the Python example of token based authentication mechanism."""

# Import required modules
import argparse
from concurrent import futures
import contextlib
import logging

# Import local credentials and gRPC module
import _credentials
import grpc

# Generate gRPC service stubs from protobuf definition
helloworld_pb2, helloworld_pb2_grpc = grpc.protos_and_services(
    "helloworld.proto"
)

# Set up logger for the module
_LOGGER = logging.getLogger(__name__)
_LOGGER.setLevel(logging.INFO)

# Template for server listen address and authentication constants
_LISTEN_ADDRESS_TEMPLATE = "localhost:%d"
_AUTH_HEADER_KEY = "authorization"
_AUTH_HEADER_VALUE = "Bearer example_oauth2_token"

class SignatureValidationInterceptor(grpc.ServerInterceptor):
    """gRPC interceptor for validating authentication tokens."""
    def __init__(self):
        # Define abort handler for unauthenticated requests
        def abort(ignored_request, context):
            context.abort(grpc.StatusCode.UNAUTHENTICATED, "Invalid signature")

        self._abort_handler = grpc.unary_unary_rpc_method_handler(abort)

    def intercept_service(self, continuation, handler_call_details):
        """
        Intercepts incoming RPCs to validate authentication header.
        
        Args:
            continuation: Function to continue processing if auth is valid
            handler_call_details: Contains metadata about the RPC call
            
        Returns:
            Either continues processing or returns abort handler
        """
        # Check if expected auth metadata exists in the call
        expected_metadata = (_AUTH_HEADER_KEY, _AUTH_HEADER_VALUE)
        if expected_metadata in handler_call_details.invocation_metadata:
            return continuation(handler_call_details)
        else:
            return self._abort_handler

class SimpleGreeter(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of the Greeter service."""
    def SayHello(self, request, unused_context):
        """
        Implementation of the SayHello RPC method.
        
        Args:
            request: Contains the name parameter from client
            unused_context: gRPC context (not used in this simple example)
            
        Returns:
            HelloReply with a greeting message containing the request name
        """
        return helloworld_pb2.HelloReply(message="Hello, %s!" % request.name)

@contextlib.contextmanager
def run_server(port):
    """
    Context manager for running the gRPC server.
    
    Args:
        port: The port number to listen on
        
    Yields:
        A tuple containing the server instance and actual listening port
    """
    # Create gRPC server with thread pool and authentication interceptor
    server = grpc.server(
        futures.ThreadPoolExecutor(),
        interceptors=(SignatureValidationInterceptor(),),
    )
    # Register the Greeter service implementation
    helloworld_pb2_grpc.add_GreeterServicer_to_server(SimpleGreeter(), server)

    # Set up SSL server credentials using certificate from credentials module
    server_credentials = grpc.ssl_server_credentials(
        (
            (
                _credentials.SERVER_CERTIFICATE_KEY,
                _credentials.SERVER_CERTIFICATE,
            ),
        )
    )

    # Bind server to the specified port with secure connection
    port = server.add_secure_port(
        _LISTEN_ADDRESS_TEMPLATE % port, server_credentials
    )

    # Start the server
    server.start()
    try:
        yield server, port
    finally:
        # Ensure server is stopped when context exits
        server.stop(0)

def main():
    """Main function to parse arguments and run the server."""
    # Set up argument parser
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--port", nargs="?", type=int, default=50051, help="the listening port"
    )
    args = parser.parse_args()

    # Run server within context manager
    with run_server(args.port) as (server, port):
        logging.info("Server is listening at port :%d", port)
        server.wait_for_termination()

if __name__ == "__main__":
    # Configure basic logging and start the application
    logging.basicConfig(level=logging.INFO)
    main()
```