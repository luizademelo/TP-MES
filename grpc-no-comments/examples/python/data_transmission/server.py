# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The example of four ways of data transmission using gRPC in Python."""

from concurrent import futures
from threading import Thread

import grpc

import demo_pb2
import demo_pb2_grpc

__all__ = "DemoServer"
SERVER_ADDRESS = "localhost:23333"
SERVER_ID = 1

class DemoServer(demo_pb2_grpc.GRPCDemoServicer):

    def SimpleMethod(self, request, context):
        print(
            "SimpleMethod called by client(%d) the message: %s"
            % (request.client_id, request.request_data)
        )
        response = demo_pb2.Response(
            server_id=SERVER_ID,
            response_data="Python server SimpleMethod Ok!!!!",
        )
        return response

    def ClientStreamingMethod(self, request_iterator, context):
        print("ClientStreamingMethod called by client...")
        for request in request_iterator:
            print(
                "recv from client(%d), message= %s"
                % (request.client_id, request.request_data)
            )
        response = demo_pb2.Response(
            server_id=SERVER_ID,
            response_data="Python server ClientStreamingMethod ok",
        )
        return response

    def ServerStreamingMethod(self, request, context):
        print(
            "ServerStreamingMethod called by client(%d), message= %s"
            % (request.client_id, request.request_data)
        )

        def response_messages():
            for i in range(5):
                response = demo_pb2.Response(
                    server_id=SERVER_ID,
                    response_data="send by Python server, message=%d" % i,
                )
                yield response

        return response_messages()

    def BidirectionalStreamingMethod(self, request_iterator, context):
        print("BidirectionalStreamingMethod called by client...")

        def parse_request():
            for request in request_iterator:
                print(
                    "recv from client(%d), message= %s"
                    % (request.client_id, request.request_data)
                )

        t = Thread(target=parse_request)
        t.start()

        for i in range(5):
            yield demo_pb2.Response(
                server_id=SERVER_ID,
                response_data="send by Python server, message= %d" % i,
            )

        t.join()

def main():
    server = grpc.server(futures.ThreadPoolExecutor())

    demo_pb2_grpc.add_GRPCDemoServicer_to_server(DemoServer(), server)

    server.add_insecure_port(SERVER_ADDRESS)
    print("------------------start Python GRPC server")
    server.start()
    server.wait_for_termination()

if __name__ == "__main__":
    main()
