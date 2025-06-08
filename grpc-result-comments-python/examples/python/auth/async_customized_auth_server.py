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
"""Server of the Python AsyncIO example of customizing authentication mechanism."""

import argparse
import asyncio
import logging
from typing import Awaitable, Callable, Tuple

import _credentials
import grpc

# Load protobuf definitions and gRPC services from helloworld.proto
helloworld_pb2, helloworld_pb2_grpc = grpc.protos_and_services(
    "helloworld.proto"
)

# Set up logger for the module
_LOGGER = logging.getLogger(__name__)
_LOGGER.setLevel(logging.INFO)

# Template for server listening address and header key for signature validation
_LISTEN_ADDRESS_TEMPLATE = "localhost:%d"
_SIGNATURE_HEADER_KEY = "x-signature"

class SignatureValidationInterceptor(grpc.aio.ServerInterceptor):
    """gRPC interceptor for validating request signatures."""
    
    def __init__(self):
        """Initialize the interceptor with an abort handler for invalid signatures."""
        def abort(ignored_request, context: grpc.aio.ServicerContext) -> None:
            """Abort the RPC with UNAUTHENTICATED status if signature is invalid."""
            context.abort(grpc.StatusCode.UNAUTHENTICATED, "Invalid signature")

        # Create a unary-unary RPC method handler for aborting requests
        self._abort_handler = grpc.unary_unary_rpc_method_handler(abort)

    async def intercept_service(
        self,
        continuation: Callable[
            [grpc.HandlerCallDetails], Awaitable[grpc.RpcMethodHandler]
        ],
        handler_call_details: grpc.HandlerCallDetails,
    ) -> grpc.RpcMethodHandler:
        """
        Intercept incoming RPCs to validate the request signature.
        
        Args:
            continuation: Function to continue processing if validation succeeds
            handler_call_details: Contains metadata about the incoming call
            
        Returns:
            Either continues processing with the original handler or returns abort handler
        """
        # Extract method name from the call details
        method_name = handler_call_details.method.split("/")[-1]
        # Expected metadata is the reversed method name as signature
        expected_metadata = (_SIGNATURE_HEADER_KEY, method_name[::-1])
        
        # Check if expected signature exists in invocation metadata
        if expected_metadata in handler_call_details.invocation_metadata:
            return await continuation(handler_call_details)
        else:
            return self._abort_handler

class SimpleGreeter(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of Greeter service."""
    
    async def SayHello(
        self, request: helloworld_pb2.HelloRequest, unused_context
    ) -> helloworld_pb2.HelloReply:
        """Implementation of SayHello RPC method.
        
        Args:
            request: Contains the name to greet
            unused_context: gRPC context (unused in this simple implementation)
            
        Returns:
            HelloReply with a greeting message
        """
        return helloworld_pb2.HelloReply(message="Hello, %s!" % request.name)

async def run_server(port: int) -> Tuple[grpc.aio.Server, int]:
    """Start and run the gRPC server with authentication.
    
    Args:
        port: The port number to listen on
        
    Returns:
        Tuple of (server instance, actual listening port)
    """
    # Create async gRPC server with signature validation interceptor
    server = grpc.aio.server(interceptors=(SignatureValidationInterceptor(),))
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

    # Bind the server to the specified port with SSL security
    port = server.add_secure_port(
        _LISTEN_ADDRESS_TEMPLATE % port, server_credentials
    )

    # Start the server and return it with the bound port
    await server.start()
    return server, port

async def main() -> None:
    """Main entry point for running the server."""
    # Set up command line argument parser
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--port", nargs="?", type=int, default=50051, help="the listening port"
    )
    args = parser.parse_args()

    # Run the server with specified or default port
    server, port = await run_server(args.port)
    logging.info("Server is listening at port :%d", port)
    # Keep server running until terminated
    await server.wait_for_termination()

if __name__ == "__main__":
    # Configure basic logging and start the async server
    logging.basicConfig(level=logging.INFO)
    asyncio.run(main())
```