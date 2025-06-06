# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The Python implementation of the GRPC helloworld.Greeter client."""

from __future__ import print_function

import logging

import grpc
import header_manipulator_client_interceptor
import helloworld_pb2
import helloworld_pb2_grpc

def run():
    header_adder_interceptor = (
        header_manipulator_client_interceptor.header_adder_interceptor(
            "one-time-password", "42"
        )
    )

    with grpc.insecure_channel("localhost:50051") as channel:
        intercept_channel = grpc.intercept_channel(
            channel, header_adder_interceptor
        )
        stub = helloworld_pb2_grpc.GreeterStub(intercept_channel)
        response = stub.SayHello(helloworld_pb2.HelloRequest(name="you"))
    print("Greeter client received: " + response.message)

if __name__ == "__main__":
    logging.basicConfig()
    run()
