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

import grpc
from grpc_testing import _common
from grpc_testing._channel import _invocation

class UnaryUnary(grpc.UnaryUnaryMultiCallable):
    """Implements a unary-unary RPC callable for testing purposes."""
    
    def __init__(self, method_full_rpc_name, channel_handler):
        """Initializes the unary-unary callable.
        
        Args:
            method_full_rpc_name: Full name of the RPC method.
            channel_handler: Handler for managing RPC invocations.
        """
        self._method_full_rpc_name = method_full_rpc_name
        self._channel_handler = channel_handler

    def __call__(self, request, timeout=None, metadata=None, credentials=None):
        """Executes a blocking unary RPC call.
        
        Args:
            request: The request message for the RPC.
            timeout: Optional timeout for the RPC.
            metadata: Optional metadata to send with the RPC.
            credentials: Optional credentials for the RPC.
            
        Returns:
            The response from the RPC.
        """
        rpc_handler = self._channel_handler.invoke_rpc(
            self._method_full_rpc_name,
            _common.fuss_with_metadata(metadata),
            [request],
            True,
            timeout,
        )
        return _invocation.blocking_unary_response(rpc_handler)

    def with_call(self, request, timeout=None, metadata=None, credentials=None):
        """Executes a blocking unary RPC call and returns response with call details.
        
        Args:
            request: The request message for the RPC.
            timeout: Optional timeout for the RPC.
            metadata: Optional metadata to send with the RPC.
            credentials: Optional credentials for the RPC.
            
        Returns:
            A tuple of (response, call) objects.
        """
        rpc_handler = self._channel_handler.invoke_rpc(
            self._method_full_rpc_name,
            _common.fuss_with_metadata(metadata),
            [request],
            True,
            timeout,
        )
        return _invocation.blocking_unary_response_with_call(rpc_handler)

    def future(self, request, timeout=None, metadata=None, credentials=None):
        """Executes a unary RPC call and returns a Future object.
        
        Args:
            request: The request message for the RPC.
            timeout: Optional timeout for the RPC.
            metadata: Optional metadata to send with the RPC.
            credentials: Optional credentials for the RPC.
            
        Returns:
            A Future object representing the asynchronous RPC call.
        """
        rpc_handler = self._channel_handler.invoke_rpc(
            self._method_full_rpc_name,
            _common.fuss_with_metadata(metadata),
            [request],
            True,
            timeout,
        )
        return _invocation.future_call(rpc_handler)

class UnaryStream(grpc.StreamStreamMultiCallable):
    """Implements a unary-stream RPC callable for testing purposes."""
    
    def __init__(self, method_full_rpc_name, channel_handler):
        """Initializes the unary-stream callable.
        
        Args:
            method_full_rpc_name: Full name of the RPC method.
            channel_handler: Handler for managing RPC invocations.
        """
        self._method_full_rpc_name = method_full_rpc_name
        self._channel_handler = channel_handler

    def __call__(self, request, timeout=None, metadata=None, credentials=None):
        """Executes a unary-stream RPC call and returns a response iterator.
        
        Args:
            request: The request message for the RPC.
            timeout: Optional timeout for the RPC.
            metadata: Optional metadata to send with the RPC.
            credentials: Optional credentials for the RPC.
            
        Returns:
            An iterator for streaming responses.
        """
        rpc_handler = self._channel_handler.invoke_rpc(
            self._method_full_rpc_name,
            _common.fuss_with_metadata(metadata),
            [request],
            True,
            timeout,
        )
        return _invocation.ResponseIteratorCall(rpc_handler)

class StreamUnary(grpc.StreamUnaryMultiCallable):
    """Implements a stream-unary RPC callable for testing purposes."""
    
    def __init__(self, method_full_rpc_name, channel_handler):
        """Initializes the stream-unary callable.
        
        Args:
            method_full_rpc_name: Full name of the RPC method.
            channel_handler: Handler for managing RPC invocations.
        """
        self._method_full_rpc_name = method_full_rpc_name
        self._channel_handler = channel_handler

    def __call__(
        self, request_iterator, timeout=None, metadata=None, credentials=None
    ):
        """Executes a blocking stream-unary RPC call.
        
        Args:
            request_iterator: Iterator of request messages.
            timeout: Optional timeout for the RPC.
            metadata: Optional metadata to send with the RPC.
            credentials: Optional credentials for the RPC.
            
        Returns:
            The response from the RPC.
        """
        rpc_handler = self._channel_handler.invoke_rpc(
            self._method_full_rpc_name,
            _common.fuss_with_metadata(metadata),
            [],
            False,
            timeout,
        )
        _invocation.consume_requests(request_iterator, rpc_handler)
        return _invocation.blocking_unary_response(rpc_handler)

    def with_call(
        self, request_iterator, timeout=None, metadata=None, credentials=None
    ):
        """Executes a blocking stream-unary RPC call and returns response with call details.
        
        Args:
            request_iterator: Iterator of request messages.
            timeout: Optional timeout for the RPC.
            metadata: Optional metadata to send with the RPC.
            credentials: Optional credentials for the RPC.
            
        Returns:
            A tuple of (response, call) objects.
        """
        rpc_handler = self._channel_handler.invoke_rpc(
            self._method_full_rpc_name,
            _common.fuss_with_metadata(metadata),
            [],
            False,
            timeout,
        )
        _invocation.consume_requests(request_iterator, rpc_handler)
        return _invocation.blocking_unary_response_with_call(rpc_handler)

    def future(
        self, request_iterator, timeout=None, metadata=None, credentials=None
    ):
        """Executes a stream-unary RPC call and returns a Future object.
        
        Args:
            request_iterator: Iterator of request messages.
            timeout: Optional timeout for the RPC.
            metadata: Optional metadata to send with the RPC.
            credentials: Optional credentials for the RPC.
            
        Returns:
            A Future object representing the asynchronous RPC call.
        """
        rpc_handler = self._channel_handler.invoke_rpc(
            self._method_full_rpc_name,
            _common.fuss_with_metadata(metadata),
            [],
            False,
            timeout,
        )
        _invocation.consume_requests(request_iterator, rpc_handler)
        return _invocation.future_call(rpc_handler)

class StreamStream(grpc.StreamStreamMultiCallable):
    """Implements a stream-stream RPC callable for testing purposes."""
    
    def __init__(self, method_full_rpc_name, channel_handler):
        """Initializes the stream-stream callable.
        
        Args:
            method_full_rpc_name: Full name of the RPC method.
            channel_handler: Handler for managing RPC invocations.
        """
        self._method_full_rpc_name = method_full_rpc_name
        self._channel_handler = channel_handler

    def __call__(
        self, request_iterator, timeout=None, metadata=None, credentials=None
    ):
        """Executes a stream-stream RPC call and returns a response iterator.
        
        Args:
            request_iterator: Iterator of request messages.
            timeout: Optional timeout for the RPC.
            metadata: Optional metadata to send with the RPC.
            credentials: Optional credentials for the RPC.
            
        Returns:
            An iterator for streaming responses.
        """
        rpc_handler = self._channel_handler.invoke_rpc(
            self._method_full_rpc_name,
            _common.fuss_with_metadata(metadata),
            [],
            False,
            timeout,
        )
        _invocation.consume_requests(request_iterator, rpc_handler)
        return _invocation.ResponseIteratorCall(rpc_handler)
```