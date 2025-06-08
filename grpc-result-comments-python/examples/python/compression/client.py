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
"""An example of compression on the client side with gRPC."""

# Import future features to ensure compatibility with Python 2 and 3
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

# Import required modules
import argparse  # For parsing command line arguments
import logging  # For logging functionality

# Import gRPC related modules
import grpc
import helloworld_pb2  # Generated protocol buffer messages
import helloworld_pb2_grpc  # Generated gRPC services

# Client description constant
_DESCRIPTION = "A client capable of compression."

# Dictionary mapping compression option strings to gRPC compression options
_COMPRESSION_OPTIONS = {
    "none": grpc.Compression.NoCompression,
    "deflate": grpc.Compression.Deflate,
    "gzip": grpc.Compression.Gzip,
}

# Logger instance for this module
_LOGGER = logging.getLogger(__name__)

# Number of RPC calls to make
_RPC_COUNT = 10

def run_client(channel_compression, call_compression, target):
    """Run the gRPC client with specified compression settings.
    
    Args:
        channel_compression: Compression setting for the channel
        call_compression: Compression setting for individual calls
        target: Server address in host:port format
    """
    # Create an insecure channel with specified compression
    with grpc.insecure_channel(
        target, compression=channel_compression
    ) as channel:
        # Create client stub
        stub = helloworld_pb2_grpc.GreeterStub(channel)
        
        # Make multiple RPC calls
        for _ in range(_RPC_COUNT):
            # Call SayHello RPC with specified compression
            response = stub.SayHello(
                helloworld_pb2.HelloRequest(name="you"),
                compression=call_compression,
                wait_for_ready=True,  # Wait if channel is not ready
            )
            print("Response: {}".format(response))

def main():
    """Main function that parses arguments and runs the client."""
    # Set up argument parser with description
    parser = argparse.ArgumentParser(description=_DESCRIPTION)
    
    # Add command line arguments:
    
    # Channel compression argument
    parser.add_argument(
        "--channel_compression",
        default="none",
        nargs="?",
        choices=_COMPRESSION_OPTIONS.keys(),
        help="The compression method to use for the channel.",
    )
    
    # Call compression argument
    parser.add_argument(
        "--call_compression",
        default="none",
        nargs="?",
        choices=_COMPRESSION_OPTIONS.keys(),
        help="The compression method to use for an individual call.",
    )
    
    # Server address argument
    parser.add_argument(
        "--server",
        default="localhost:50051",
        type=str,
        nargs="?",
        help="The host-port pair at which to reach the server.",
    )
    
    # Parse command line arguments
    args = parser.parse_args()
    
    # Map string arguments to gRPC compression options
    channel_compression = _COMPRESSION_OPTIONS[args.channel_compression]
    call_compression = _COMPRESSION_OPTIONS[args.call_compression]
    
    # Run client with parsed arguments
    run_client(channel_compression, call_compression, args.server)

if __name__ == "__main__":
    # Configure basic logging
    logging.basicConfig()
    # Start the program
    main()
```