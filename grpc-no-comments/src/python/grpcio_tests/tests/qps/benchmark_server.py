# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

from src.proto.grpc.testing import benchmark_service_pb2_grpc
from src.proto.grpc.testing import messages_pb2

class BenchmarkServer(benchmark_service_pb2_grpc.BenchmarkServiceServicer):
    """Synchronous Server implementation for the Benchmark service."""

    def UnaryCall(self, request, context):
        payload = messages_pb2.Payload(body=b"\0" * request.response_size)
        return messages_pb2.SimpleResponse(payload=payload)

    def StreamingCall(self, request_iterator, context):
        for request in request_iterator:
            payload = messages_pb2.Payload(body=b"\0" * request.response_size)
            yield messages_pb2.SimpleResponse(payload=payload)

class GenericBenchmarkServer(
    benchmark_service_pb2_grpc.BenchmarkServiceServicer
):
    """Generic Server implementation for the Benchmark service."""

    def __init__(self, resp_size):
        self._response = b"\0" * resp_size

    def UnaryCall(self, request, context):
        return self._response

    def StreamingCall(self, request_iterator, context):
        for request in request_iterator:
            yield self._response
