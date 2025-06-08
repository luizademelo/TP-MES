Here's the commented version of the code:

```c++
# Copyright 2019 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The Python example of utilizing wait-for-ready flag."""

from concurrent import futures
from contextlib import contextmanager
import logging
import socket
import threading

import grpc

# Load protobuf definitions and gRPC services from helloworld.proto
helloworld_pb2, helloworld_pb2_grpc = grpc.protos_and_services(
    "helloworld.proto"
)

# Initialize logger
_LOGGER = logging.getLogger(__name__)
_LOGGER.setLevel(logging.INFO)

@contextmanager
def get_free_loopback_tcp_port():
    """Context manager that finds and yields a free TCP port on localhost.
    
    Creates a temporary socket to find an available port, yields it in
    'localhost:port' format, and ensures the socket is closed afterward.
    Supports both IPv4 and IPv6 sockets.
    """
    if socket.has_ipv6:
        tcp_socket = socket.socket(socket.AF_INET6)
    else:
        tcp_socket = socket.socket(socket.AF_INET)
    tcp_socket.bind(("", 0))
    address_tuple = tcp_socket.getsockname()
    yield "localhost:%s" % (address_tuple[1])
    tcp_socket.close()

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of the Greeter service defined in helloworld.proto."""
    
    def SayHello(self, request, unused_context):
        """Implementation of the SayHello RPC method.
        
        Args:
            request: HelloRequest containing the name to greet
            unused_context: RPC context (unused in this simple example)
            
        Returns:
            HelloReply containing the greeting message
        """
        return helloworld_pb2.HelloReply(message="Hello, %s!" % request.name)

def create_server(server_address):
    """Creates and configures a gRPC server with the Greeter service.
    
    Args:
        server_address: Address string in 'host:port' format
        
    Returns:
        Configured gRPC server instance
    """
    server = grpc.server(futures.ThreadPoolExecutor())
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    bound_port = server.add_insecure_port(server_address)
    assert bound_port == int(server_address.split(":")[-1])
    return server

def process(stub, wait_for_ready=None):
    """Makes an RPC call and handles the response or error.
    
    Args:
        stub: Greeter service stub
        wait_for_ready: Boolean flag to enable/disable wait-for-ready behavior
        
    Logs the result of the RPC call and verifies expected behavior based on
    the wait_for_ready setting.
    """
    try:
        response = stub.SayHello(
            helloworld_pb2.HelloRequest(name="you"),
            wait_for_ready=wait_for_ready,
        )
        message = response.message
    except grpc.RpcError as rpc_error:
        assert rpc_error.code() == grpc.StatusCode.UNAVAILABLE
        assert not wait_for_ready
        message = rpc_error
    else:
        assert wait_for_ready
    _LOGGER.info(
        "Wait-for-ready %s, client received: %s",
        "enabled" if wait_for_ready else "disabled",
        message,
    )

def main():
    """Main function demonstrating wait-for-ready behavior.
    
    1. Gets a free port and creates a channel to it (server not running yet)
    2. Starts two threads making RPC calls with different wait-for-ready settings
    3. Waits for channel to reach TRANSIENT_FAILURE state
    4. Starts the server
    5. Joins the threads and cleans up resources
    """
    with get_free_loopback_tcp_port() as server_address:
        # Event to track when channel reaches TRANSIENT_FAILURE state
        transient_failure_event = threading.Event()

        def wait_for_transient_failure(channel_connectivity):
            """Callback for channel state changes.
            
            Sets the event when channel reaches TRANSIENT_FAILURE state.
            """
            if (
                channel_connectivity
                == grpc.ChannelConnectivity.TRANSIENT_FAILURE
            ):
                transient_failure_event.set()

        # Create channel and stub before server is running
        channel = grpc.insecure_channel(server_address)
        channel.subscribe(wait_for_transient_failure)
        stub = helloworld_pb2_grpc.GreeterStub(channel)

        # Start threads with different wait-for-ready settings
        thread_disabled_wait_for_ready = threading.Thread(
            target=process, args=(stub, False)
        )
        thread_disabled_wait_for_ready.start()

        thread_enabled_wait_for_ready = threading.Thread(
            target=process, args=(stub, True)
        )
        thread_enabled_wait_for_ready.start()

    # Wait for channel to fail before starting server
    transient_failure_event.wait()
    server = create_server(server_address)
    server.start()

    # Wait for threads to complete
    thread_disabled_wait_for_ready.join()
    thread_enabled_wait_for_ready.join()

    # Clean up
    server.stop(None)
    channel.close()

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    main()
```