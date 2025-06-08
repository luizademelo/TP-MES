Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.
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

"""Runs protoc with the gRPC plugin to generate messages and gRPC stubs."""

# Import the protoc module from grpc_tools package which provides
# the Protocol Buffers compiler functionality with gRPC extensions
from grpc_tools import protoc

# Execute the protoc compiler with specified arguments to generate:
# 1. Regular Protocol Buffers message classes (--python_out)
# 2. gRPC service stub classes (--grpc_python_out)
protoc.main(
    (
        "",  # Empty string typically represents the program name (argv[0])
        "-I../../protos",  # Add directory to the proto import path
        "--python_out=.",  # Generate Python messages in current directory
        "--grpc_python_out=.",  # Generate gRPC Python code in current directory
        "../../protos/route_guide.proto",  # Input proto file to compile
    )
)

# Note: This script is typically used as part of a build process to
# generate Python gRPC client/server code from .proto definitions.
# The generated files include:
# - route_guide_pb2.py: Contains the generated message classes
# - route_guide_pb2_grpc.py: Contains the generated client and server classes
```