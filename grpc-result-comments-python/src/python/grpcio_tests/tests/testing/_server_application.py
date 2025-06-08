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
"""An example gRPC Python-using server-side application."""

import threading

import grpc

from tests.testing import _application_common
from tests.testing.proto import requests_pb2
from tests.testing.proto import services_pb2
from tests.testing.proto import services_pb2_grpc

class FirstServiceServicer(services_pb2_grpc.FirstServiceServicer):
    """Implementation of gRPC FirstService service methods."""

    def __init__(self):
        # Thread-safe lock for abort operations
        self._abort_lock = threading.RLock()
        # Default abort response state
        self._abort_response = _application_common.ABORT_NO_STATUS_RESPONSE

    def UnUn(self, request, context):
        """Handles Unary-Unary RPC calls.
        
        Args:
            request: The incoming request message
            context: gRPC context object for RPC
            
        Returns:
            Appropriate response message or None for abort cases
        """
        if request == _application_common.UNARY_UNARY_REQUEST:
            # Return standard response for standard request
            return _application_common.UNARY_UNARY_RESPONSE
        elif request == _application_common.ABORT_REQUEST:
            # Handle abort request with thread-safe operation
            with self._abort_lock:
                try:
                    # Attempt to abort the RPC with permission denied status
                    context.abort(
                        grpc.StatusCode.PERMISSION_DENIED,
                        "Denying permission to test abort.",
                    )
                except Exception as e:
                    # If abort succeeds, set success response
                    self._abort_response = (
                        _application_common.ABORT_SUCCESS_RESPONSE
                    )
                else:
                    # If abort fails, set failure response
                    self._abort_status = (
                        _application_common.ABORT_FAILURE_RESPONSE
                    )
            return None  # NOTE: For the linter.
        elif request == _application_common.ABORT_SUCCESS_QUERY:
            # Return current abort status
            with self._abort_lock:
                return self._abort_response
        else:
            # Handle invalid requests
            context.set_code(grpc.StatusCode.INVALID_ARGUMENT)
            context.set_details("Something is wrong with your request!")
            return services_pb2.Down()

    def UnStre(self, request, context):
        """Handles Unary-Stream RPC calls.
        
        Args:
            request: The incoming request message
            context: gRPC context object for RPC
            
        Yields:
            Response messages in stream
        """
        if _application_common.UNARY_STREAM_REQUEST != request:
            # Validate request
            context.set_code(grpc.StatusCode.INVALID_ARGUMENT)
            context.set_details("Something is wrong with your request!")
        return
        yield services_pb2.Strange()

    def StreUn(self, request_iterator, context):
        """Handles Stream-Unary RPC calls.
        
        Args:
            request_iterator: Iterator of incoming request messages
            context: gRPC context object for RPC
            
        Returns:
            Single response message after processing stream
        """
        # Send initial metadata to client
        context.send_initial_metadata(
            (
                (
                    "server_application_metadata_key",
                    "Hi there!",
                ),
            )
        )
        # Process each request in the stream
        for request in request_iterator:
            if request != _application_common.STREAM_UNARY_REQUEST:
                # Validate each request
                context.set_code(grpc.StatusCode.INVALID_ARGUMENT)
                context.set_details("Something is wrong with your request!")
                return services_pb2.Strange()
            elif not context.is_active():
                # Check if RPC is still active
                return services_pb2.Strange()
        else:
            # Return standard response after processing all requests
            return _application_common.STREAM_UNARY_RESPONSE

    def StreStre(self, request_iterator, context):
        """Handles Stream-Stream RPC calls.
        
        Args:
            request_iterator: Iterator of incoming request messages
            context: gRPC context object for RPC
            
        Yields:
            Response messages in stream
        """
        # Define valid request types
        valid_requests = (
            _application_common.STREAM_STREAM_REQUEST,
            _application_common.STREAM_STREAM_MUTATING_REQUEST,
        )
        # Process each request in the stream
        for request in request_iterator:
            if request not in valid_requests:
                # Validate request
                context.set_code(grpc.StatusCode.INVALID_ARGUMENT)
                context.set_details("Something is wrong with your request!")
                return
            elif not context.is_active():
                # Check if RPC is still active
                return
            elif request == _application_common.STREAM_STREAM_REQUEST:
                # Yield standard responses for standard request
                yield _application_common.STREAM_STREAM_RESPONSE
                yield _application_common.STREAM_STREAM_RESPONSE
            elif request == _application_common.STREAM_STREAM_MUTATING_REQUEST:
                # Handle mutating request with incremental responses
                response = services_pb2.Bottom()
                for i in range(
                    _application_common.STREAM_STREAM_MUTATING_COUNT
                ):
                    response.first_bottom_field = i
                    yield response
```