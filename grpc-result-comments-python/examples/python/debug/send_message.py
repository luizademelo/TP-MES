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
"""Send multiple greeting messages to the backend."""

# Import future features to ensure compatibility with Python 3
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import logging

import grpc

# Load protocol buffer definitions and gRPC services from helloworld.proto
helloworld_pb2, helloworld_pb2_grpc = grpc.protos_and_services(
    "helloworld.proto"
)

def process(stub, request):
    """Process a single request to the gRPC server.
    
    Args:
        stub: The gRPC stub/client for making RPC calls
        request: The request message to send to the server
    """
    try:
        # Call the SayHello RPC method
        response = stub.SayHello(request)
    except grpc.RpcError as rpc_error:
        # Handle any RPC errors that occur
        print("Received error: %s" % rpc_error)
    else:
        # Print the successful response
        print("Received message: %s" % response)

def run(addr, n):
    """Run the gRPC client to send multiple requests.
    
    Args:
        addr: Server address to connect to
        n: Number of messages to send
    """
    # Create an insecure channel (no encryption) to the server
    with grpc.insecure_channel(addr) as channel:
        # Create the stub/client for the Greeter service
        stub = helloworld_pb2_grpc.GreeterStub(channel)
        # Create the request message
        request = helloworld_pb2.HelloRequest(name="you")
        # Send 'n' requests to the server
        for _ in range(n):
            process(stub, request)

def main():
    """Main function that parses arguments and starts the client."""
    # Set up command line argument parsing
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--addr",
        nargs=1,
        type=str,
        default="[::]:50051",
        help="the address to request",
    )
    parser.add_argument(
        "-n",
        nargs=1,
        type=int,
        default=10,
        help="an integer for number of messages to sent",
    )
    # Parse command line arguments
    args = parser.parse_args()
    # Start the client with the provided arguments
    run(addr=args.addr, n=args.n)

if __name__ == "__main__":
    # Configure basic logging
    logging.basicConfig()
    # Start the program
    main()
```