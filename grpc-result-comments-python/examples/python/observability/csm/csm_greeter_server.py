Here's the commented version of the code:

```python
# Copyright 2024 The gRPC authors.
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

import argparse
from concurrent import futures
import logging
from typing import Sequence

import grpc
from grpc_csm_observability import CsmOpenTelemetryPlugin
from opentelemetry.exporter.prometheus import PrometheusMetricReader
from opentelemetry.sdk.metrics import Histogram
from opentelemetry.sdk.metrics import MeterProvider
from opentelemetry.sdk.metrics import view
from prometheus_client import start_http_server

from examples.python.observability.csm import helloworld_pb2
from examples.python.observability.csm import helloworld_pb2_grpc

# Network configuration constants
_LISTEN_HOST = "0.0.0.0"  # Listen on all available network interfaces
_THREAD_POOL_SIZE = 256   # Size of thread pool for handling concurrent requests

# Configure logging
logger = logging.getLogger()
console_handler = logging.StreamHandler()
formatter = logging.Formatter(fmt="%(asctime)s: %(levelname)-8s %(message)s")
console_handler.setFormatter(formatter)
logger.addHandler(console_handler)

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of Greeter service that responds to SayHello RPCs."""
    def SayHello(self, request, context):
        """Responds to SayHello RPC with a greeting message.
        
        Args:
            request: The HelloRequest containing the name to greet
            context: RPC context
            
        Returns:
            HelloReply containing the greeting message
        """
        message = request.name
        return helloworld_pb2.HelloReply(message=f"Hello {message}")

def _run(
    port: int,
    secure_mode: bool,
    server_id: str,
    prometheus_endpoint: int,
) -> None:
    """Main function to run the gRPC server with CSM observability.
    
    Args:
        port: Port number for the gRPC server
        secure_mode: Whether to run in secure (xDS) mode
        server_id: Identifier for this server
        prometheus_endpoint: Port for Prometheus metrics endpoint
    """
    # Set up CSM observability
    csm_plugin = _prepare_csm_observability_plugin(prometheus_endpoint)
    csm_plugin.register_global()
    
    # Create and configure gRPC server
    server = grpc.server(
        futures.ThreadPoolExecutor(max_workers=_THREAD_POOL_SIZE),
        xds=secure_mode,
    )
    _configure_test_server(server, port, secure_mode, server_id)
    
    # Start server and wait for termination
    server.start()
    logger.info("Test server listening on port %d", port)
    server.wait_for_termination()
    
    # Clean up observability when server terminates
    csm_plugin.deregister_global()

def _prepare_csm_observability_plugin(
    prometheus_endpoint: int,
) -> CsmOpenTelemetryPlugin:
    """Prepares and configures the CSM OpenTelemetry plugin.
    
    Args:
        prometheus_endpoint: Port for Prometheus metrics endpoint
        
    Returns:
        Configured CsmOpenTelemetryPlugin instance
    """
    # Start Prometheus metrics endpoint
    start_http_server(port=prometheus_endpoint, addr="0.0.0.0")
    
    # Configure OpenTelemetry metrics
    reader = PrometheusMetricReader()
    meter_provider = MeterProvider(
        metric_readers=[reader], views=_create_views()
    )
    
    # Create and return CSM plugin
    csm_plugin = CsmOpenTelemetryPlugin(
        meter_provider=meter_provider,
    )
    return csm_plugin

def _create_views() -> Sequence[view.View]:
    """Create a list of views with config for specific metrics.
    
    Returns:
        Sequence of View objects configured with appropriate bucket boundaries
        for latency and size metrics.
    """
    # Bucket boundaries for latency metrics (in seconds)
    latency_boundaries = [
        0,
        0.00001,  # 10us
        0.00005,  # 50us
        0.0001,   # 100us
        0.0003,   # 300us
        0.0006,   # 600us
        0.0008,   # 800us
        0.001,    # 1ms
        0.002,    # 2ms
        0.003,    # 3ms
        0.004,    # 4ms
        0.005,    # 5ms
        0.006,    # 6ms
        0.008,    # 8ms
        0.01,     # 10ms
        0.013,    # 13ms
        0.016,    # 16ms
        0.02,     # 20ms
        0.025,    # 25ms
        0.03,     # 30ms
        0.04,     # 40ms
        0.05,     # 50ms
        0.065,    # 65ms
        0.08,     # 80ms
        0.1,      # 100ms
        0.13,     # 130ms
        0.16,     # 160ms
        0.2,      # 200ms
        0.25,     # 250ms
        0.3,      # 300ms
        0.4,      # 400ms
        0.5,      # 500ms
        0.65,     # 650ms
        0.8,      # 800ms
        1,        # 1s
        2,        # 2s
        5,        # 5s
        10,       # 10s
        20,       # 20s
        50,       # 50s
        100,      # 100s
    ]
    
    # Bucket boundaries for size metrics (in bytes)
    size_boundaries = [
        0,
        1024,      # 1KB
        2048,      # 2KB
        4096,      # 4KB
        16384,     # 16KB
        65536,     # 64KB
        262144,    # 256KB
        1048576,   # 1MB
        4194304,   # 4MB
        16777216,  # 16MB
        67108864,  # 64MB
        268435456, # 256MB
        1073741824, # 1GB
        4294967296, # 4GB
    ]
    
    # Return views for both latency and size metrics
    return [
        view.View(
            instrument_type=Histogram,
            instrument_unit="s",
            aggregation=view.ExplicitBucketHistogramAggregation(
                boundaries=latency_boundaries
            ),
        ),
        view.View(
            instrument_type=Histogram,
            instrument_unit="By",
            aggregation=view.ExplicitBucketHistogramAggregation(
                boundaries=size_boundaries
            ),
        ),
    ]

def _configure_test_server(
    server: grpc.Server, port: int, secure_mode: bool, server_id: str
) -> None:
    """Configures the gRPC server with appropriate settings.
    
    Args:
        server: The gRPC server instance
        port: Port number to listen on
        secure_mode: Whether to use secure (xDS) credentials
        server_id: Identifier for this server
    """
    # Register the Greeter service implementation
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    
    # Configure listening address
    listen_address = f"{_LISTEN_HOST}:{port}"
    
    # Configure security based on mode
    if not secure_mode:
        server.add_insecure_port(listen_address)
    else:
        logger.info("Running with xDS Server credentials")
        server_fallback_creds = grpc.insecure_server_credentials()
        server_creds = grpc.xds_server_credentials(server_fallback_creds)
        server.add_secure_port(listen_address, server_creds)

def bool_arg(arg: str) -> bool:
    """Converts string argument to boolean.
    
    Args:
        arg: String input to parse
        
    Returns:
        Boolean value
        
    Raises:
        ArgumentTypeError: If input cannot be parsed as boolean
    """
    if arg.lower() in ("true", "yes", "y"):
        return True
    elif arg.lower() in ("false", "no", "n"):
        return False
    else:
        raise argparse.ArgumentTypeError(f"Could not parse '{arg}' as a bool.")

if __name__ == "__main__":
    # Configure basic logging
    logging.basicConfig()
    logger.setLevel(logging.INFO)
    
    # Set up command line argument parsing
    parser = argparse.ArgumentParser(
        description="Run Python CSM Observability Test server."
    )
    parser.add_argument(
        "--port", type=int, default=50051, help="Port for test server."
    )
    parser.add_argument(
        "--secure_mode",
        type=bool_arg,
        default="False",
        help="If specified, uses xDS to retrieve server credentials.",
    )
    parser.add_argument(
        "--server_id",
        type=str,
        default="python_server",
        help="The server ID to return in responses.",
    )
    parser.add_argument(
        "--prometheus_endpoint",
        type=int,
        default=9464,
        help="Port for servers besides test server.",
    )
    
    # Parse arguments and run server
    args = parser.parse_args()
    _run(
        args.port,
        args.secure_mode,
        args.server_id,
        args.prometheus_endpoint,
    )
```