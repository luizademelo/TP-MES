# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""gRPC Python helloworld.Greeter client with channel options and call timeout parameters."""

from __future__ import print_function

import logging

import grpc
import helloworld_pb2
import helloworld_pb2_grpc

def run():

    with grpc.insecure_channel(
        target="localhost:50051",
        options=[
            ("grpc.lb_policy_name", "pick_first"),
            ("grpc.enable_retries", 0),
            ("grpc.keepalive_timeout_ms", 10000),
        ],
    ) as channel:
        stub = helloworld_pb2_grpc.GreeterStub(channel)

        response = stub.SayHello(
            helloworld_pb2.HelloRequest(name="you"), timeout=10
        )
    print("Greeter client received: " + response.message)

if __name__ == "__main__":
    logging.basicConfig()
    run()
