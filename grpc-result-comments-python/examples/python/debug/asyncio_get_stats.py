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
"""Poll statistics from the server."""

import argparse
import asyncio
import logging

import grpc
from grpc_channelz.v1 import channelz_pb2
from grpc_channelz.v1 import channelz_pb2_grpc

async def run(addr: str) -> None:
    """Connect to a gRPC server and fetch server statistics using Channelz.
    
    Args:
        addr: The address of the gRPC server to connect to.
    """
    # Create an insecure asynchronous gRPC channel (no SSL/TLS)
    async with grpc.aio.insecure_channel(addr) as channel:
        # Create a Channelz stub for making Channelz API calls
        channelz_stub = channelz_pb2_grpc.ChannelzStub(channel)
        
        # Request server statistics starting from server ID 0
        response = await channelz_stub.GetServers(
            channelz_pb2.GetServersRequest(start_server_id=0)
        
        # Print the server statistics response
        print("Info for all servers: %s" % response)

async def main() -> None:
    """Main function to parse command-line arguments and execute the run function."""
    # Set up argument parser with default values
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--addr",
        nargs=1,
        type=str,
        default="[::]:50051",  # Default server address (IPv6 any address on port 50051)
        help="the address to request",
    )
    
    # Parse command-line arguments
    args = parser.parse_args()
    
    # Execute the run function with the provided or default address
    await run(addr=args.addr)

if __name__ == "__main__":
    # Configure basic logging
    logging.basicConfig()
    
    # Run the main coroutine in the asyncio event loop
    asyncio.get_event_loop().run_until_complete(main())
```

Key improvements made:
1. Added docstring for the `run` function explaining its purpose and parameters
2. Added inline comments explaining key operations (channel creation, stub creation, RPC call)
3. Added docstring for the `main` function
4. Added comments for argument parsing and default value explanation
5. Added comments for the main execution block
6. Maintained all existing functionality while making the code more understandable

The comments now provide clear explanations of:
- What the code does at each major step
- The purpose of each function
- The meaning of important parameters
- The flow of execution
- Key gRPC operations being performed