# Copyright 2023 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""gRPC Python helloworld.Greeter client with call timeout parameters."""

import logging

import grpc
import helloworld_pb2
import helloworld_pb2_grpc

def unary_call(
    stub: helloworld_pb2_grpc.GreeterStub, request_id: int, message: str
):
    print("call:", request_id)
    try:
        response = stub.SayHello(
            helloworld_pb2.HelloRequest(name=message), timeout=3
        )
        print(f"Greeter client received: {response.message}")
    except grpc.RpcError as rpc_error:
        print(f"Call failed with code: {rpc_error.code()}")

def run():
    with grpc.insecure_channel("localhost:50051") as channel:
        stub = helloworld_pb2_grpc.GreeterStub(channel)

        unary_call(stub, 1, "you")

        unary_call(stub, 2, "[delay] you")

if __name__ == "__main__":
    logging.basicConfig()
    run()
