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
"""An example of compression on the server side with gRPC."""

# Import future features for Python 2/3 compatibility
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

# Import required modules
import argparse  # For command-line argument parsing
from concurrent import futures  # For thread pool executor
import logging  # For logging functionality
import threading  # For thread-safe operations

import grpc  # gRPC core library
import helloworld_pb2  # Generated protocol buffer messages
import helloworld_pb2_grpc  # Generated gRPC stubs

# Server description constant
_DESCRIPTION = "A server capable of compression."

# Dictionary mapping compression algorithm names to gRPC compression options
_COMPRESSION_OPTIONS = {
    "none": grpc.Compression.NoCompression,
    "deflate": grpc.Compression.Deflate,
    "gzip": grpc.Compression.Gzip,
}

# Logger instance for this module
_LOGGER = logging.getLogger(__name__)

# Default server host address
_SERVER_HOST = "localhost"

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    """Implementation of the gRPC Greeter service with compression control."""
    
    def __init__(self, no_compress_every_n):
        """
        Initialize the Greeter service.
        
        Args:
            no_compress_every_n: If set, every nth response will be uncompressed.
                                 If 0, all responses will use server's default compression.
        """
        super(Greeter, self).__init__()
        self._no_compress_every_n = no_compress_every_n  # Compression suppression frequency
        self._request_counter = 0  # Counter for tracking requests
        self._counter_lock = threading.RLock()  # Lock for thread-safe counter access

    def _should_suppress_compression(self):
        """
        Determine if compression should be suppressed for the current request.
        
        Returns:
            bool: True if compression should be suppressed, False otherwise.
        """
        suppress_compression = False
        with self._counter_lock:
            if (
                self._no_compress_every_n
                and self._request_counter % self._no_compress_every_n == 0
            ):
                suppress_compression = True
            self._request_counter += 1
        return suppress_compression

    def SayHello(self, request, context):
        """
        Implementation of the SayHello RPC method.
        
        Args:
            request: The HelloRequest protocol buffer message.
            context: The gRPC context for the RPC call.
            
        Returns:
            HelloReply: The response protocol buffer message.
        """
        if self._should_suppress_compression():
            # Disable compression for this response if needed
            context.set_compression(grpc.Compression.NoCompression)
        return helloworld_pb2.HelloReply(message="Hello, %s!" % request.name)

def run_server(server_compression, no_compress_every_n, port):
    """
    Run the gRPC server with specified compression settings.
    
    Args:
        server_compression: Default compression algorithm for the server.
        no_compress_every_n: If set, every nth response will be uncompressed.
        port: The port number to listen on.
    """
    # Create a gRPC server with thread pool executor
    server = grpc.server(
        futures.ThreadPoolExecutor(),
        compression=server_compression,  # Set default server compression
        options=(("grpc.so_reuseport", 1),),  # Enable SO_REUSEPORT option
    )
    
    # Add the Greeter service implementation to the server
    helloworld_pb2_grpc.add_GreeterServicer_to_server(
        Greeter(no_compress_every_n), server
    )
    
    # Start the server on the specified address and port
    address = "{}:{}".format(_SERVER_HOST, port)
    server.add_insecure_port(address)
    server.start()
    print("Server listening at '{}'".format(address))
    server.wait_for_termination()

def main():
    """Main function to parse arguments and start the server."""
    # Set up argument parser with server description
    parser = argparse.ArgumentParser(description=_DESCRIPTION)
    
    # Add command line arguments:
    parser.add_argument(
        "--server_compression",
        default="none",
        nargs="?",
        choices=_COMPRESSION_OPTIONS.keys(),
        help="The default compression method for the server.",
    )
    parser.add_argument(
        "--no_compress_every_n",
        type=int,
        default=0,
        nargs="?",
        help="If set, every nth reply will be uncompressed.",
    )
    parser.add_argument(
        "--port",
        type=int,
        default=50051,
        nargs="?",
        help="The port on which the server will listen.",
    )
    
    # Parse command line arguments
    args = parser.parse_args()
    
    # Start the server with specified parameters
    run_server(
        _COMPRESSION_OPTIONS[args.server_compression],
        args.no_compress_every_n,
        args.port,
    )

if __name__ == "__main__":
    # Configure basic logging and start the server
    logging.basicConfig()
    main()
```