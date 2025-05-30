# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The example of four ways of data transmission using gRPC in Python."""

import time

import grpc

import demo_pb2
import demo_pb2_grpc

__all__ = [
    "simple_method",
    "client_streaming_method",
    "server_streaming_method",
    "bidirectional_streaming_method",
]

SERVER_ADDRESS = "localhost:23333"
CLIENT_ID = 1

def simple_method(stub):
    print("--------------Call SimpleMethod Begin--------------")
    request = demo_pb2.Request(
        client_id=CLIENT_ID, request_data="called by Python client"
    )
    response = stub.SimpleMethod(request)
    print(
        "resp from server(%d), the message=%s"
        % (response.server_id, response.response_data)
    )
    print("--------------Call SimpleMethod Over---------------")

def client_streaming_method(stub):
    print("--------------Call ClientStreamingMethod Begin--------------")

    def request_messages():
        for i in range(5):
            request = demo_pb2.Request(
                client_id=CLIENT_ID,
                request_data="called by Python client, message:%d" % i,
            )
            yield request

    response = stub.ClientStreamingMethod(request_messages())
    print(
        "resp from server(%d), the message=%s"
        % (response.server_id, response.response_data)
    )
    print("--------------Call ClientStreamingMethod Over---------------")

def server_streaming_method(stub):
    print("--------------Call ServerStreamingMethod Begin--------------")
    request = demo_pb2.Request(
        client_id=CLIENT_ID, request_data="called by Python client"
    )
    response_iterator = stub.ServerStreamingMethod(request)
    for response in response_iterator:
        print(
            "recv from server(%d), message=%s"
            % (response.server_id, response.response_data)
        )

    print("--------------Call ServerStreamingMethod Over---------------")

def bidirectional_streaming_method(stub):
    print(
        "--------------Call BidirectionalStreamingMethod Begin---------------"
    )

    def request_messages():
        for i in range(5):
            request = demo_pb2.Request(
                client_id=CLIENT_ID,
                request_data="called by Python client, message: %d" % i,
            )
            yield request
            time.sleep(1)

    response_iterator = stub.BidirectionalStreamingMethod(request_messages())
    for response in response_iterator:
        print(
            "recv from server(%d), message=%s"
            % (response.server_id, response.response_data)
        )

    print("--------------Call BidirectionalStreamingMethod Over---------------")

def main():
    with grpc.insecure_channel(SERVER_ADDRESS) as channel:
        stub = demo_pb2_grpc.GRPCDemoStub(channel)

        simple_method(stub)

        client_streaming_method(stub)

        server_streaming_method(stub)

        bidirectional_streaming_method(stub)

if __name__ == "__main__":
    main()
