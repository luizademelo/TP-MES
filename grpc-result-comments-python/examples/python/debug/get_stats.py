Here's the commented version of the code snippet:

```python
# Copyright 2019 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Poll statistics from the server."""

# Ensure Python 2 compatibility for absolute imports, division, and print function
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse  # For parsing command-line arguments
import logging   # For logging functionality

import grpc  # gRPC library for Python
from grpc_channelz.v1 import channelz_pb2  # Protocol buffers for Channelz service
from grpc_channelz.v1 import channelz_pb2_grpc  # gRPC stubs for Channelz service

def run(addr):
    """
    Establishes an insecure gRPC channel and queries server statistics using Channelz.
    
    Args:
        addr (str): The server address to connect to in format 'host:port'
    """
    # Create an insecure gRPC channel (no encryption/authentication)
    with grpc.insecure_channel(addr) as channel:
        # Create a stub for the Channelz service
        channelz_stub = channelz_pb2_grpc.ChannelzStub(channel)
        
        # Make GetServers RPC call to fetch server statistics
        response = channelz_stub.GetServers(channelz_pb2.GetServersRequest())
        # Print the server statistics response
        print(f"Info for all servers: {response}")

def main():
    """
    Main function that parses command-line arguments and initiates the server polling.
    """
    # Set up argument parser with default values and help messages
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--addr",
        nargs=1,
        type=str,
        default="[::]:50051",  # Default server address (IPv6 any address, port 50051)
        help="the address to request",
    )
    args = parser.parse_args()
    
    # Start the polling process with the provided or default address
    run(addr=args.addr)

if __name__ == "__main__":
    # Configure basic logging when script is run directly
    logging.basicConfig()
    main()
```

Key improvements in the comments:
1. Added module-level comments explaining the purpose of imports
2. Added detailed docstrings for both functions
3. Explained the default value in the argument parser
4. Clarified the purpose of the insecure channel
5. Added context about the Channelz service
6. Explained the basic logging configuration
7. Maintained all original functionality while making it more understandable

The comments now provide a clear understanding of:
- What the code does (poll server statistics via Channelz)
- How it does it (using gRPC with insecure channel)
- How to use it (command-line arguments)
- Key components and their purposes