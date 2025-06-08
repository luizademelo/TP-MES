Here's the commented version of the code:

```c++
# Copyright 2019 the gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
""" Proxies a TCP connection between a single client-server pair.

This proxy is not suitable for production, but should work well for cases in
which a test needs to spy on the bytes put on the wire between a server and
a client.
"""

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import datetime
import select
import socket
import threading

from tests.unit.framework.common import get_socket

# Constants for proxy configuration
_TCP_PROXY_BUFFER_SIZE = 1024  # Size of buffer for socket reads
_TCP_PROXY_TIMEOUT = datetime.timedelta(milliseconds=500)  # Timeout for select operations

def _init_proxy_socket(gateway_address, gateway_port):
    """Initialize and return a socket connected to the gateway server."""
    proxy_socket = socket.create_connection((gateway_address, gateway_port))
    return proxy_socket

class TcpProxy(object):
    """Proxies a TCP connection between one client and one server."""

    def __init__(self, bind_address, gateway_address, gateway_port):
        """Initialize the TCP proxy with binding and gateway addresses.
        
        Args:
            bind_address: Address to bind the proxy listener to
            gateway_address: Address of the server to proxy to
            gateway_port: Port of the server to proxy to
        """
        self._bind_address = bind_address
        self._gateway_address = gateway_address
        self._gateway_port = gateway_port

        # Thread-safe counters for tracking bytes transferred
        self._byte_count_lock = threading.RLock()
        self._sent_byte_count = 0      # Bytes sent to server (client -> proxy -> server)
        self._received_byte_count = 0  # Bytes received from server (server -> proxy -> client)

        # Event to signal when proxy should stop
        self._stop_event = threading.Event()

        # Network components
        self._port = None              # Port the proxy is listening on
        self._listen_socket = None     # Socket listening for client connections
        self._proxy_socket = None      # Socket connected to gateway server

        # Data buffers
        self._northbound_data = b""   # Data from server to client(s)
        self._southbound_data = b""    # Data from client(s) to server
        self._client_sockets = []      # List of connected client sockets

        # Main proxy thread
        self._thread = threading.Thread(target=self._run_proxy)

    def start(self):
        """Start the proxy by:
        1. Creating a listening socket
        2. Connecting to the gateway server
        3. Starting the proxy thread
        """
        _, self._port, self._listen_socket = get_socket(
            bind_address=self._bind_address
        )
        self._proxy_socket = _init_proxy_socket(
            self._gateway_address, self._gateway_port
        )
        self._thread.start()

    def get_port(self):
        """Return the port number the proxy is listening on."""
        return self._port

    def _handle_reads(self, sockets_to_read):
        """Handle incoming data from readable sockets.
        
        Args:
            sockets_to_read: List of sockets with data available to read
        """
        for socket_to_read in sockets_to_read:
            if socket_to_read is self._listen_socket:
                # Accept new client connection
                client_socket, client_address = socket_to_read.accept()
                self._client_sockets.append(client_socket)
            elif socket_to_read is self._proxy_socket:
                # Read data from server (northbound)
                data = socket_to_read.recv(_TCP_PROXY_BUFFER_SIZE)
                with self._byte_count_lock:
                    self._received_byte_count += len(data)
                self._northbound_data += data
            elif socket_to_read in self._client_sockets:
                # Read data from client (southbound)
                data = socket_to_read.recv(_TCP_PROXY_BUFFER_SIZE)
                if data:
                    with self._byte_count_lock:
                        self._sent_byte_count += len(data)
                    self._southbound_data += data
                else:
                    # Client disconnected
                    self._client_sockets.remove(socket_to_read)
            else:
                raise RuntimeError("Unidentified socket appeared in read set.")

    def _handle_writes(self, sockets_to_write):
        """Handle outgoing data to writable sockets.
        
        Args:
            sockets_to_write: List of sockets ready to receive data
        """
        for socket_to_write in sockets_to_write:
            if socket_to_write is self._proxy_socket:
                # Send southbound data to server
                if self._southbound_data:
                    self._proxy_socket.sendall(self._southbound_data)
                    self._southbound_data = b""
            elif socket_to_write in self._client_sockets:
                # Send northbound data to client
                if self._northbound_data:
                    socket_to_write.sendall(self._northbound_data)
                    self._northbound_data = b""

    def _run_proxy(self):
        """Main proxy loop that handles all socket I/O."""
        while not self._stop_event.is_set():
            # Set up lists of sockets to monitor
            expected_reads = (self._listen_socket, self._proxy_socket) + tuple(
                self._client_sockets
            )
            expected_writes = expected_reads
            
            # Wait for socket activity
            sockets_to_read, sockets_to_write, _ = select.select(
                expected_reads,
                expected_writes,
                (),
                _TCP_PROXY_TIMEOUT.total_seconds(),
            )
            
            # Process active sockets
            self._handle_reads(sockets_to_read)
            self._handle_writes(sockets_to_write)
        
        # Clean up client connections when stopping
        for client_socket in self._client_sockets:
            client_socket.close()

    def stop(self):
        """Stop the proxy and clean up resources."""
        self._stop_event.set()      # Signal thread to stop
        self._thread.join()        # Wait for thread to finish
        self._listen_socket.close() # Close listening socket
        self._proxy_socket.close()  # Close server connection

    def get_byte_count(self):
        """Get tuple of (sent_byte_count, received_byte_count)."""
        with self._byte_count_lock:
            return self._sent_byte_count, self._received_byte_count

    def reset_byte_count(self):
        """Reset both byte counters to zero."""
        with self._byte_count_lock:
            self._byte_count = 0
            self._received_byte_count = 0

    def __enter__(self):
        """Context manager entry point - starts the proxy."""
        self.start()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        """Context manager exit point - stops the proxy."""
        self.stop()
```