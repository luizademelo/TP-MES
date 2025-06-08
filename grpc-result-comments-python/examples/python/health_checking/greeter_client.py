Here's the commented version of the code:

```python
# Copyright 2023 gRPC authors.
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
"""gRPC Python helloworld.Greeter client with health checking."""

import logging
from time import sleep

import grpc
from grpc_health.v1 import health_pb2
from grpc_health.v1 import health_pb2_grpc
import helloworld_pb2
import helloworld_pb2_grpc


def unary_call(stub: helloworld_pb2_grpc.GreeterStub, message: str):
    """
    Makes a unary RPC call to the Greeter service to say hello.
    
    Args:
        stub: The Greeter service stub used to make RPC calls.
        message: The name to be included in the hello request.
    """
    response = stub.SayHello(
        helloworld_pb2.HelloRequest(name=message), timeout=3
    )
    print(f"Greeter client received: {response.message}")


def health_check_call(stub: health_pb2_grpc.HealthStub):
    """
    Checks the health status of the Greeter service.
    
    Args:
        stub: The Health service stub used to check service health.
    """
    request = health_pb2.HealthCheckRequest(service="helloworld.Greeter")
    resp = stub.Check(request)
    if resp.status == health_pb2.HealthCheckResponse.SERVING:
        print("server is serving")
    elif resp.status == health_pb2.HealthCheckResponse.NOT_SERVING:
        print("server stopped serving")


def run():
    """
    Main function that runs the gRPC client:
    1. Creates an insecure channel to the server
    2. Initializes service stubs
    3. Makes a sample RPC call
    4. Periodically checks service health for 30 seconds
    """
    with grpc.insecure_channel("localhost:50051") as channel:
        # Initialize stubs for Greeter and Health services
        stub = helloworld_pb2_grpc.GreeterStub(channel)
        health_stub = health_pb2_grpc.HealthStub(channel)

        # Make initial greeting call
        unary_call(stub, "you")

        # Check health status every second for 30 seconds
        for _ in range(30):
            health_check_call(health_stub)
            sleep(1)


if __name__ == "__main__":
    # Configure basic logging and run the client
    logging.basicConfig()
    run()
```

Key improvements made:
1. Added complete docstrings for all functions explaining their purpose and parameters
2. Added comments explaining the main blocks of code in the `run()` function
3. Fixed the license header formatting (was missing some comment markers)
4. Added comments explaining the main execution block
5. Made sure all comments follow consistent style and provide meaningful context

The comments now provide clear explanations of:
- What each function does
- The purpose of key operations
- The overall flow of the program
- The expected behavior of the client