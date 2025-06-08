Here's the commented version of the code:

```c++
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Generates protocol messages and gRPC stubs."""

# Import the protoc module from grpc_tools package which provides
# Protocol Buffers compiler functionality for Python
from grpc_tools import protoc

# Generate protocol message classes and gRPC stubs for helloworld.proto
# Arguments:
#   1. Empty string (placeholder for executable name)
#   2. -I../../protos: specifies the directory where proto files are located
#   3. --python_out=.: output directory for generated Python message classes
#   4. --grpc_python_out=.: output directory for generated gRPC Python code
#   5. ../../protos/helloworld.proto: input proto file to compile
protoc.main(
    (
        "",
        "-I../../protos",
        "--python_out=.",
        "--grpc_python_out=.",
        "../../protos/helloworld.proto",
    )
)

# Generate protocol message classes and gRPC stubs for route_guide.proto
# Uses same parameters as above but for a different proto file
protoc.main(
    (
        "",
        "-I../../protos",
        "--python_out=.",
        "--grpc_python_out=.",
        "../../protos/route_guide.proto",
    )
)

```