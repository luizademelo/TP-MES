Here's the commented version of the code snippet:

```c++
# Copyright 2020 The gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# distributed under the License is distributed on an "AS IS" BASIS,
#
# See the License for the specific language governing permissions and
# limitations under the License.
"""Hello World without using protoc.

This example parses message and service schemas directly from a
.proto file on the filesystem.

Several APIs used in this example are in an experimental state.
"""

# Import print function from Python 3 for Python 2 compatibility
from __future__ import print_function

import logging  # For logging functionality

# Import gRPC core functionality and experimental features
import grpc
import grpc.experimental

# NOTE: The path to the .proto file must be reachable from an entry

# Load protocol buffer definitions directly from .proto file without using protoc
# This is an experimental feature in gRPC
protos = grpc.protos("helloworld.proto")  # Load message definitions
services = grpc.services("helloworld.proto")  # Load service definitions

# Configure basic logging
logging.basicConfig()

# Make RPC call to Greeter service:
# 1. Create HelloRequest with name="you"
# 2. Connect to server at localhost:50051 with insecure channel (no encryption)
# 3. Call SayHello method with the request
response = services.Greeter.SayHello(
    protos.HelloRequest(name="you"),  # Create request message
    "localhost:50051",  # Server address
    insecure=True  # Use insecure channel (no TLS)
)

# Print the response received from the server
print("Greeter client received: " + response.message)
```

Key additions:
1. Added comments explaining each import statement
2. Documented the experimental nature of the proto loading functionality
3. Explained the RPC call parameters and what they represent
4. Added context about the insecure channel flag
5. Clarified the purpose of each code block while maintaining the original structure

The comments aim to help future developers understand:
- The experimental nature of some features
- The flow of the gRPC client code
- The purpose of each parameter in the RPC call
- The relationship between the proto definitions and the actual service call