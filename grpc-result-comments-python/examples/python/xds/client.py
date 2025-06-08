Here's the commented version of the code:

```c++
# Copyright 2020 The gRPC authors.
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
"""The Python implementation of the GRPC helloworld.Greeter client."""

# Import print_function from future to ensure Python 2/3 compatibility
from __future__ import print_function

# Import required modules
import argparse  # For parsing command line arguments
import logging   # For logging configuration

import grpc                      # gRPC core library
import grpc.experimental         # Experimental gRPC features
import helloworld_pb2            # Generated protocol buffer messages
import helloworld_pb2_grpc       # Generated gRPC stubs

# Constant for the command line description
_DESCRIPTION = "Get a greeting from a server."

def run(server_address, secure):
    """Main function to establish connection with server and get greeting.
    
    Args:
        server_address: String containing server address to connect to
        secure: Boolean indicating whether to use secure channel (xDS credentials)
    """
    if secure:
        # Create fallback credentials for insecure channel
        fallback_creds = grpc.experimental.insecure_channel_credentials()
        # Create xDS credentials with fallback
        channel_creds = grpc.xds_channel_credentials(fallback_creds)
        # Create secure channel with xDS credentials
        channel = grpc.secure_channel(server_address, channel_creds)
    else:
        # Create insecure channel (plaintext)
        channel = grpc.insecure_channel(server_address)
    
    # Channel is automatically closed when exiting the 'with' block
    with channel:
        # Create client stub for Greeter service
        stub = helloworld_pb2_grpc.GreeterStub(channel)
        # Call SayHello RPC with a request containing name "you"
        response = stub.SayHello(helloworld_pb2.HelloRequest(name="you"))
        # Print the response from server
        print("Greeter client received: " + response.message)

if __name__ == "__main__":
    # Set up command line argument parser
    parser = argparse.ArgumentParser(description=_DESCRIPTION)
    parser.add_argument(
        "server", default=None, help="The address of the server."
    )
    parser.add_argument(
        "--xds-creds",
        action="store_true",
        help="If specified, uses xDS credentials to connect to the server.",
    )
    # Parse command line arguments
    args = parser.parse_args()
    # Configure basic logging
    logging.basicConfig()
    # Run the client with parsed arguments
    run(args.server, args.xds_creds)
```