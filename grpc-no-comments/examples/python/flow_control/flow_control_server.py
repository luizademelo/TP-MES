# Copyright 2024 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Example gRPC server that applies back-pressure on client"""

from concurrent import futures
import logging
import time

import grpc
import helloworld_pb2
import helloworld_pb2_grpc
import helpers

_PORT = "50051"

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    def SayHelloBidiStream(self, request_iterator, unused_context):

        time.sleep(5)

        bytes_received = 0

        for i, request in enumerate(request_iterator, start=1):
            bytes_received += len(request.name)
            if (i % 10) == 0:
                print(
                    f"{helpers.get_current_time()}   "
                    f"Request {i}:   Received {bytes_received} bytes in total"
                )

            time.sleep(1)

            msg = "Hello!"
            yield helloworld_pb2.HelloReply(message=msg)

            if (i % 10) == 0:
                print(
                    f"{helpers.get_current_time()}   "
                    f"Request {i}:   Sent {bytes_received} bytes in total\n"
                )

def serve():
    server = grpc.server(
        futures.ThreadPoolExecutor(max_workers=10),

        options=[
            ("grpc.http2.max_frame_size", 16384),
            ("grpc.http2.bdp_probe", 0),
            ("grpc.max_concurrent_streams", 1),
        ],
    )
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)

    server.add_insecure_port("[::]:" + _PORT)
    server.start()
    print("Server started, listening on " + _PORT)
    server.wait_for_termination()

if __name__ == "__main__":
    logging.basicConfig()
    serve()
