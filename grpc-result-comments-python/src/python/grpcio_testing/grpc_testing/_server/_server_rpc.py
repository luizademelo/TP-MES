Here's the commented version of the code:

```python
# Copyright 2017 gRPC authors.
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

import grpc_testing

# Implementation of a unary-unary RPC (single request, single response) server for testing purposes
class UnaryUnaryServerRpc(grpc_testing.UnaryUnaryServerRpc):
    def __init__(self, handler):
        # Initialize with a handler that will process the RPC
        self._handler = handler

    def initial_metadata(self):
        # Returns the initial metadata from the handler
        return self._handler.initial_metadata()

    def cancel(self):
        # Cancels the RPC by delegating to the handler
        self._handler.cancel()

    def termination(self):
        # Returns the termination status of the unary response
        return self._handler.unary_response_termination()


# Implementation of a unary-stream RPC (single request, multiple responses) server for testing purposes
class UnaryStreamServerRpc(grpc_testing.UnaryStreamServerRpc):
    def __init__(self, handler):
        # Initialize with a handler that will process the RPC
        self._handler = handler

    def initial_metadata(self):
        # Returns the initial metadata from the handler
        return self._handler.initial_metadata()

    def take_response(self):
        # Takes a single response from the stream
        return self._handler.take_response()

    def cancel(self):
        # Cancels the RPC by delegating to the handler
        self._handler.cancel()

    def termination(self):
        # Returns the termination status of the stream response
        return self._handler.stream_response_termination()


# Implementation of a stream-unary RPC (multiple requests, single response) server for testing purposes
class StreamUnaryServerRpc(grpc_testing.StreamUnaryServerRpc):
    def __init__(self, handler):
        # Initialize with a handler that will process the RPC
        self._handler = handler

    def initial_metadata(self):
        # Returns the initial metadata from the handler
        return self._handler.initial_metadata()

    def send_request(self, request):
        # Adds a request to the stream
        self._handler.add_request(request)

    def requests_closed(self):
        # Notifies the handler that no more requests will be sent
        self._handler.requests_closed()

    def cancel(self):
        # Cancels the RPC by delegating to the handler
        self._handler.cancel()

    def termination(self):
        # Returns the termination status of the unary response
        return self._handler.unary_response_termination()


# Implementation of a stream-stream RPC (multiple requests, multiple responses) server for testing purposes
class StreamStreamServerRpc(grpc_testing.StreamStreamServerRpc):
    def __init__(self, handler):
        # Initialize with a handler that will process the RPC
        self._handler = handler

    def initial_metadata(self):
        # Returns the initial metadata from the handler
        return self._handler.initial_metadata()

    def send_request(self, request):
        # Adds a request to the stream
        self._handler.add_request(request)

    def requests_closed(self):
        # Notifies the handler that no more requests will be sent
        self._handler.requests_closed()

    def take_response(self):
        # Takes a single response from the stream
        return self._handler.take_response()

    def cancel(self):
        # Cancels the RPC by delegating to the handler
        self._handler.cancel()

    def termination(self):
        # Returns the termination status of the stream response
        return self._handler.stream_response_termination()
```

The comments explain:
1. The purpose of each class (type of RPC pattern)
2. The initialization with a handler
3. Each method's responsibility and what it delegates to the handler
4. The flow of requests and responses for each RPC pattern
5. The termination conditions for each RPC type

The comments maintain a consistent style and provide enough information for future developers to understand the code's purpose and behavior without being overly verbose.