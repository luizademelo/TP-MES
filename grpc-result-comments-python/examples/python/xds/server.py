Here's the commented version of the code:

```python
# Copyright 2020 The gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The Python implementation of the GRPC helloworld.Greeter server."""

# Import required modules
import argparse
from concurrent import futures  # For thread pool execution
import logging  # For logging server activities
import socket  # For hostname resolution

import grpc  # Core gRPC library
from grpc_health.v1 import health  # Health checking service
from grpc_health.v1 import health_pb2  # Health check protocol buffers
from grpc_health.v1 import health_pb2_grpc  # Health check gRPC services
from grpc_reflection.v1alpha import reflection  # Server reflection
import helloworld_pb2  # Generated protocol buffer messages
import helloworld_pb2_grpc  # Generated gRPC services

# Server description constant
_DESCRIPTION = "A general purpose phony server."

# Default host to listen on (all interfaces)
_LISTEN_HOST = "0.0.0.0"

# Size of the thread pool for handling requests
_THREAD_POOL_SIZE = 256

# Configure logging
logger = logging.getLogger()
console_handler = logging.StreamHandler()
formatter = logging.Formatter(fmt="%(asctime)s: %(levelname)-8s %(message)s")
console_handler.setFormatter(formatter)
logger.addHandler(console_handler)

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of the Greeter service."""
    
    def __init__(self, hostname: str):
        """Initialize the Greeter with a hostname.
        
        Args:
            hostname: The hostname to use in responses. If None, uses system hostname.
        """
        self._hostname = hostname if hostname else socket.gethostname()

    def SayHello(
        self,
        request: helloworld_pb2.HelloRequest,
        context: grpc.ServicerContext,
    ) -> helloworld_pb2.HelloReply:
        """Implementation of the SayHello RPC method.
        
        Args:
            request: The HelloRequest containing the name to greet.
            context: The RPC context.
            
        Returns:
            A HelloReply with a greeting message containing the request name and hostname.
        """
        return helloworld_pb2.HelloReply(
            message=f"Hello {request.name} from {self._hostname}!"
        )

def _configure_maintenance_server(
    server: grpc.Server, maintenance_port: int
) -> None:
    """Configure and add maintenance services to the gRPC server.
    
    This includes health checking and server reflection services.
    
    Args:
        server: The gRPC server to configure.
        maintenance_port: The port to listen on for maintenance services.
    """
    listen_address = f"{_LISTEN_HOST}:{maintenance_port}"
    server.add_insecure_port(listen_address)

    # Configure health checking service
    health_servicer = health.HealthServicer(
        experimental_non_blocking=True,
        experimental_thread_pool=futures.ThreadPoolExecutor(
            max_workers=_THREAD_POOL_SIZE
        ),
    )

    # Get list of all services to enable reflection for
    services = tuple(
        service.full_name
        for service in helloworld_pb2.DESCRIPTOR.services_by_name.values()
    ) + (reflection.SERVICE_NAME, health.SERVICE_NAME)

    # Add health service to server
    health_pb2_grpc.add_HealthServicer_to_server(health_servicer, server)
    
    # Set all services as healthy
    for service in services:
        health_servicer.set(service, health_pb2.HealthCheckResponse.SERVING)
    
    # Enable server reflection
    reflection.enable_server_reflection(services, server)

def _configure_greeter_server(
    server: grpc.Server, port: int, secure_mode: bool, hostname
) -> None:
    """Configure the main Greeter service on the gRPC server.
    
    Args:
        server: The gRPC server to configure.
        port: The port to listen on.
        secure_mode: Whether to use secure (xDS) credentials.
        hostname: The hostname to use in responses.
    """
    # Add Greeter service implementation to server
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(hostname), server)
    
    listen_address = f"{_LISTEN_HOST}:{port}"
    if not secure_mode:
        # Run in insecure mode (plaintext)
        server.add_insecure_port(listen_address)
    else:
        # Run with xDS security credentials
        logger.info("Running with xDS Server credentials")

        server_fallback_creds = grpc.insecure_server_credentials()
        server_creds = grpc.xds_server_credentials(server_fallback_creds)
        server.add_secure_port(listen_address, server_creds)

def serve(
    port: int, hostname: str, maintenance_port: int, secure_mode: bool
) -> None:
    """Start and run the gRPC servers.
    
    Args:
        port: The main port for Greeter service.
        hostname: The hostname to use in responses.
        maintenance_port: The port for maintenance services.
        secure_mode: Whether to use secure (xDS) credentials.
    """
    if port == maintenance_port:
        # Combined mode - single server for both services
        server = grpc.server(
            futures.ThreadPoolExecutor(max_workers=_THREAD_POOL_SIZE)
        )
        _configure_greeter_server(server, port, secure_mode, hostname)
        _configure_maintenance_server(server, maintenance_port)
        server.start()
        logger.info("Greeter server listening on port %d", port)
        logger.info("Maintenance server listening on port %d", maintenance_port)
        server.wait_for_termination()
    else:
        # Separate mode - different servers for Greeter and maintenance services
        greeter_server = grpc.server(
            futures.ThreadPoolExecutor(max_workers=_THREAD_POOL_SIZE),
            xds=secure_mode,
        )
        _configure_greeter_server(greeter_server, port, secure_mode, hostname)
        greeter_server.start()
        logger.info("Greeter server listening on port %d", port)
        
        maintenance_server = grpc.server(
            futures.ThreadPoolExecutor(max_workers=_THREAD_POOL_SIZE)
        )
        _configure_maintenance_server(maintenance_server, maintenance_port)
        maintenance_server.start()
        logger.info("Maintenance server listening on port %d", maintenance_port)
        
        greeter_server.wait_for_termination()
        maintenance_server.wait_for_termination()

if __name__ == "__main__":
    # Parse command line arguments
    parser = argparse.ArgumentParser(description=_DESCRIPTION)
    parser.add_argument(
        "port",
        default=50051,
        type=int,
        nargs="?",
        help="The port on which to listen.",
    )
    parser.add_argument(
        "hostname",
        type=str,
        default=None,
        nargs="?",
        help="The name clients will see in responses.",
    )
    parser.add_argument(
        "--xds-creds",
        action="store_true",
        help="If specified, uses xDS credentials to connect to the server.",
    )
    
    # Configure logging and start server
    args = parser.parse_args()
    logging.basicConfig()
    logger.setLevel(logging.INFO)
    serve(args.port, args.hostname, args.port + 1, args.xds_creds)
```