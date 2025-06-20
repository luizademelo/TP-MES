Here's the commented version of the code:

```c++
# Copyright 2023 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""gRPC Python helloworld.Greeter client with keepAlive channel options."""

import logging
from time import sleep

import grpc
import helloworld_pb2
import helloworld_pb2_grpc

def unary_call(
    stub: helloworld_pb2_grpc.GreeterStub, request_id: int, message: str
):
    """Make a unary RPC call to the Greeter service.
    
    Args:
        stub: The gRPC stub for the Greeter service.
        request_id: Identifier for the request (for logging purposes).
        message: The message to send to the server.
    """
    print("call:", request_id)
    try:
        # Make the RPC call and print the response
        response = stub.SayHello(helloworld_pb2.HelloRequest(name=message))
        print(f"Greeter client received: {response.message}")
    except grpc.RpcError as rpc_error:
        # Handle any RPC errors that occur during the call
        print("Call failed with code: ", rpc_error.code())

def run():
    """Main function to run the gRPC client with keepalive options.
    
    Configures keepalive parameters for the gRPC channel to maintain connection
    health and detect disconnections. Then makes a sample RPC call and keeps
    the connection alive for 30 seconds to demonstrate keepalive functionality.
    
    Keepalive parameters explained:
    grpc.keepalive_time_ms: The period (in milliseconds) after which a keepalive ping is
        sent on the transport.
    grpc.keepalive_timeout_ms: The amount of time (in milliseconds) the sender of the keepalive
        ping waits for an acknowledgement. If it does not receive an acknowledgement within this
        time, it will close the connection.
    grpc.keepalive_permit_without_calls: If set to 1 (0 : false; 1 : true), allows keepalive
        pings to be sent even if there are no calls in flight.
    grpc.http2.max_pings_without_data: How many pings can the client send before needing to
        send a data/header frame.
    For more details, check: https://github.com/grpc/grpc/blob/master/doc/keepalive.md
    """
    # Configure keepalive channel options
    channel_options = [
        ("grpc.keepalive_time_ms", 8000),  # Send keepalive ping every 8 seconds
        ("grpc.keepalive_timeout_ms", 5000),  # Wait 5 seconds for ping ack
        ("grpc.http2.max_pings_without_data", 5),  # Max 5 pings without data
        ("grpc.keepalive_permit_without_calls", 1),  # Allow pings without active calls
    ]

    # Create an insecure channel (no TLS) with the specified keepalive options
    with grpc.insecure_channel(
        target="localhost:50051", options=channel_options
    ) as channel:
        # Create the Greeter service stub
        stub = helloworld_pb2_grpc.GreeterStub(channel)

        # Make an initial RPC call
        unary_call(stub, 1, "you")

        # Keep the connection alive for 30 seconds to demonstrate keepalive
        for i in range(30):
            print(f"{i} seconds passed.")
            sleep(1)

if __name__ == "__main__":
    # Configure basic logging and run the client
    logging.basicConfig()
    run()
```