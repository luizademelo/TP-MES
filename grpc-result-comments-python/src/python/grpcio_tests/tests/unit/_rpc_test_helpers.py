Here's the commented version of the code:

```python
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Test helpers for RPC invocation tests."""

import datetime
import threading

import grpc
from grpc.framework.foundation import logging_pool

from tests.unit import test_common
from tests.unit import thread_pool
from tests.unit.framework.common import test_constants
from tests.unit.framework.common import test_control

# Serialization/deserialization functions for testing
_SERIALIZE_REQUEST = lambda bytestring: bytestring * 2  # Duplicates the input bytes
_DESERIALIZE_REQUEST = lambda bytestring: bytestring[len(bytestring) // 2 :]  # Takes second half
_SERIALIZE_RESPONSE = lambda bytestring: bytestring * 3  # Triplicates the input bytes
_DESERIALIZE_RESPONSE = lambda bytestring: bytestring[: len(bytestring) // 3]  # Takes first third

# Constants for service and method names
_SERVICE_NAME = "test"
_UNARY_UNARY = "UnaryUnary"  # Single request, single response
_UNARY_STREAM = "UnaryStream"  # Single request, stream response
_UNARY_STREAM_NON_BLOCKING = "UnaryStreamNonBlocking"  # Non-blocking version
_STREAM_UNARY = "StreamUnary"  # Stream request, single response
_STREAM_STREAM = "StreamStream"  # Stream request, stream response
_STREAM_STREAM_NON_BLOCKING = "StreamStreamNonBlocking"  # Non-blocking version

# Short timeout for tests (4 seconds)
TIMEOUT_SHORT = datetime.timedelta(seconds=4).total_seconds()

class Callback(object):
    """Callback helper class for asynchronous operations with thread synchronization."""
    def __init__(self):
        self._condition = threading.Condition()  # Thread synchronization
        self._value = None  # Stores callback result
        self._called = False  # Flag indicating if callback was invoked

    def __call__(self, value):
        """Callback function that stores the value and notifies waiting threads."""
        with self._condition:
            self._value = value
            self._called = True
            self._condition.notify_all()

    def value(self):
        """Blocks until callback is called and returns the stored value."""
        with self._condition:
            while not self._called:
                self._condition.wait()
            return self._value

class _Handler(object):
    """Handles RPC methods for testing different gRPC call types."""
    def __init__(self, control, thread_pool):
        self._control = control  # Test control object
        self._thread_pool = thread_pool  # Thread pool for non-blocking operations
        
        # Mark non-blocking functions and assign thread pool
        non_blocking_functions = (
            self.handle_unary_stream_non_blocking,
            self.handle_stream_stream_non_blocking,
        )
        for non_blocking_function in non_blocking_functions:
            non_blocking_function.__func__.experimental_non_blocking = True
            non_blocking_function.__func__.experimental_thread_pool = (
                self._thread_pool
            )

    def handle_unary_unary(self, request, servicer_context):
        """Handles unary-unary RPC calls."""
        self._control.control()
        if servicer_context is not None:
            # Set test metadata and check context properties
            servicer_context.set_trailing_metadata((("testkey", "testvalue"),))
            servicer_context.is_active()
            servicer_context.time_remaining()
        return request  # Echo back the request

    def handle_unary_stream(self, request, servicer_context):
        """Handles unary-stream RPC calls."""
        for _ in range(test_constants.STREAM_LENGTH):
            self._control.control()
            yield request  # Stream multiple responses
        self._control.control()
        if servicer_context is not None:
            servicer_context.set_trailing_metadata((("testkey", "testvalue"),))

    def handle_unary_stream_non_blocking(self, request, servicer_context, on_next):
        """Non-blocking version of unary-stream handler."""
        for _ in range(test_constants.STREAM_LENGTH):
            self._control.control()
            on_next(request)  # Call callback for each response
        self._control.control()
        if servicer_context is not None:
            servicer_context.set_trailing_metadata((("testkey", "testvalue"),))
        on_next(None)  # Signal completion

    def handle_stream_unary(self, request_iterator, servicer_context):
        """Handles stream-unary RPC calls."""
        if servicer_context is not None:
            servicer_context.invocation_metadata()
        self._control.control()
        response_elements = []
        for request in request_iterator:
            self._control.control()
            response_elements.append(request)  # Collect all requests
        self._control.control()
        if servicer_context is not None:
            servicer_context.set_trailing_metadata((("testkey", "testvalue"),))
        return b"".join(response_elements)  # Concatenate all requests as response

    def handle_stream_stream(self, request_iterator, servicer_context):
        """Handles stream-stream RPC calls."""
        self._control.control()
        if servicer_context is not None:
            servicer_context.set_trailing_metadata((("testkey", "testvalue"),))
        for request in request_iterator:
            self._control.control()
            yield request  # Echo each request as response
        self._control.control()

    def handle_stream_stream_non_blocking(self, request_iterator, servicer_context, on_next):
        """Non-blocking version of stream-stream handler."""
        self._control.control()
        if servicer_context is not None:
            servicer_context.set_trailing_metadata((("testkey", "testvalue"),))
        for request in request_iterator:
            self._control.control()
            on_next(request)  # Call callback for each response
        self._control.control()
        on_next(None)  # Signal completion

class _MethodHandler(grpc.RpcMethodHandler):
    """Wrapper for gRPC method handlers with serialization support."""
    def __init__(
        self,
        request_streaming,
        response_streaming,
        request_deserializer,
        response_serializer,
        unary_unary,
        unary_stream,
        stream_unary,
        stream_stream,
    ):
        self.request_streaming = request_streaming  # True if request is stream
        self.response_streaming = response_streaming  # True if response is stream
        self.request_deserializer = request_deserializer  # Request deserializer
        self.response_serializer = response_serializer  # Response serializer
        self.unary_unary = unary_unary  # Unary-unary handler
        self.unary_stream = unary_stream  # Unary-stream handler
        self.stream_unary = stream_unary  # Stream-unary handler
        self.stream_stream = stream_stream  # Stream-stream handler

class _GenericHandler(grpc.GenericRpcHandler):
    """Routes RPC calls to appropriate method handlers based on method name."""
    def __init__(self, handler):
        self._handler = handler  # Underlying handler implementation

    def service(self, handler_call_details):
        """Returns appropriate method handler based on the called method."""
        if handler_call_details.method == _UNARY_UNARY:
            return _MethodHandler(
                False, False, None, None,
                self._handler.handle_unary_unary, None, None, None)
        elif handler_call_details.method == _UNARY_STREAM:
            return _MethodHandler(
                False, True, _DESERIALIZE_REQUEST, _SERIALIZE_RESPONSE,
                None, self._handler.handle_unary_stream, None, None)
        elif handler_call_details.method == _UNARY_STREAM_NON_BLOCKING:
            return _MethodHandler(
                False, True, _DESERIALIZE_REQUEST, _SERIALIZE_RESPONSE,
                None, self._handler.handle_unary_stream_non_blocking, None, None)
        elif handler_call_details.method == _STREAM_UNARY:
            return _MethodHandler(
                True, False, _DESERIALIZE_REQUEST, _SERIALIZE_RESPONSE,
                None, None, self._handler.handle_stream_unary, None)
        elif handler_call_details.method == _STREAM_STREAM:
            return _MethodHandler(
                True, True, None, None,
                None, None, None, self._handler.handle_stream_stream)
        elif handler_call_details.method == _STREAM_STREAM_NON_BLOCKING:
            return _MethodHandler(
                True, True, None, None,
                None, None, None, self._handler.handle_stream_stream_non_blocking)
        else:
            return None

def get_method_handlers(handler):
    """Returns a dictionary mapping method names to their handlers."""
    return {
        _UNARY_UNARY: _MethodHandler(
            False, False, None, None,
            handler.handle_unary_unary, None, None, None),
        _UNARY_STREAM: _MethodHandler(
            False, True, _DESERIALIZE_REQUEST, _SERIALIZE_RESPONSE,
            None, handler.handle_unary_stream, None, None),
        _UNARY_STREAM_NON_BLOCKING: _MethodHandler(
            False, True, _DESERIALIZE_REQUEST, _SERIALIZE_RESPONSE,
            None, handler.handle_unary_stream_non_blocking, None, None),
        _STREAM_UNARY: _MethodHandler(
            True, False, _DESERIALIZE_REQUEST, _SERIALIZE_RESPONSE,
            None, None, handler.handle_stream_unary, None),
        _STREAM_STREAM: _MethodHandler(
            True, True, None, None,
            None, None, None, handler.handle_stream_stream),
        _STREAM_STREAM_NON_BLOCKING: _MethodHandler(
            True, True, None, None,
            None, None, None, handler.handle_stream_stream_non_blocking),
    }

# Factory functions for creating multi-callable RPC stubs
def unary_unary_multi_callable(channel):
    return channel.unary_unary(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _UNARY_UNARY),
        _registered_method=True,
    )

def unary_stream_multi_callable(channel):
    return channel.unary_stream(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _UNARY_STREAM),
        request_serializer=_SERIALIZE_REQUEST,
        response_deserializer=_DESERIALIZE_RESPONSE,
        _registered_method=True,
    )

def unary_stream_non_blocking_multi_callable(channel):
    return channel.unary_stream(
        grpc._common.fully_qualified_method(
            _SERVICE_NAME, _UNARY_STREAM_NON_BLOCKING),
        request_serializer=_SERIALIZE_REQUEST,
        response_deserializer=_DESERIALIZE_RESPONSE,
        _registered_method=True,
    )

def stream_unary_multi_callable(channel):
    return channel.stream_unary(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _STREAM_UNARY),
        request_serializer=_SERIALIZE_REQUEST,
        response_deserializer=_DESERIALIZE_RESPONSE,
        _registered_method=True,
    )

def stream_stream_multi_callable(channel):
    return channel.stream_stream(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _STREAM_STREAM),
        _registered_method=True,
    )

def stream_stream_non_blocking_multi_callable(channel):
    return channel.stream_stream(
        grpc._common.fully_qualified_method(
            _SERVICE_NAME, _STREAM_STREAM_NON_BLOCKING),
        _registered_method=True,
    )

class BaseRPCTest(object):
    """Base class for RPC test cases with common setup/teardown and test methods."""
    def setUp(self):
        """Test setup: creates server and channel with all method handlers."""
        self._control = test_control.PauseFailControl()
        self._thread_pool = thread_pool.RecordingThreadPool(max_workers=None)
        self._handler = _Handler(self._control, self._thread_pool)

        self._server = test_common.test_server()
        port = self._server.add_insecure_port("[::]:0")
        self._server.add_registered_method_handlers(
            _SERVICE_NAME, get_method_handlers(self._handler))
        self._server.start()

        self._channel = grpc.insecure_channel("localhost:%d" % port)

    def tearDown(self):
        """Test teardown: stops server and closes channel."""
        self._server.stop(None)
        self._channel.close()

    # Test helper methods for various RPC scenarios
    def _consume_one_stream_response_unary_request(self, multi_callable):
        """Tests consuming one response from a unary request stream response."""
        request = b"\x57\x38"
        response_iterator = multi_callable(
            request,
            metadata=(("test", "ConsumingOneStreamResponseUnaryRequest"),),
        )
        next(response_iterator)

    def _consume_some_but_not_all_stream_responses_unary_request(self, multi_callable):
        """Tests partial consumption of stream responses from unary request."""
        request = b"\x57\x38"
        response_iterator = multi_callable(
            request,
            metadata=(("test", "ConsumingSomeButNotAllStreamResponsesUnaryRequest"),),
        )
        for _ in range(test_constants.STREAM_LENGTH // 2):
            next(response_iterator)

    def _consume_some_but_not_all_stream_responses_stream_request(self, multi_callable):
        """Tests partial consumption of stream responses from stream request."""
        requests = tuple(b"\x67\x88" for _ in range(test_constants.STREAM_LENGTH))
        request_iterator = iter(requests)
        response_iterator = multi_callable(
            request_iterator,
            metadata=(("test", "ConsumingSomeButNotAllStreamResponsesStreamRequest"),),
        )
        for _ in range(test_constants.STREAM_LENGTH // 2):
            next(response_iterator)

    def _consume_too_many_stream_responses_stream_request(self, multi_callable):
        """Tests over-consumption of stream responses from stream request."""
        requests = tuple(b"\x67\x88" for _ in range(test_constants.STREAM_LENGTH))
        request_iterator = iter(requests)
        response_iterator = multi_callable(
            request_iterator,
            metadata=(("test", "ConsumingTooManyStreamResponsesStreamRequest"),),
        )
        for _ in range(test_constants.STREAM_LENGTH):
            next(response_iterator)
        for _ in range(test_constants.STREAM_LENGTH):
            with self.assertRaises(StopIteration):
                next(response_iterator)

        # Verify response metadata and status
        self.assertIsNotNone(response_iterator.initial_metadata())
        self.assertIs(grpc.StatusCode.OK, response_iterator.code())
        self.assertIsNotNone(response_iterator.details())
        self.assertIsNotNone(response_iterator.trailing_metadata())

    def _cancelled_unary_request_stream_response(self, multi_callable):
        """Tests cancellation of unary request with stream response."""
        request = b"\x07\x19"
        with self._control.pause():
            response_iterator = multi_callable(
                request,
                metadata=(("test", "CancelledUnaryRequestStreamResponse"),),
            )
            self._control.block_until_paused()
            response_iterator.cancel()

        with self.assertRaises(grpc.RpcError) as exception_context:
            next(response_iterator)
        self.assertIs(grpc.StatusCode.CANCELLED, exception_context.exception.code())
        # Verify response metadata even after cancellation
        self.assertIsNotNone(response_iterator.initial_metadata())
        self.assertIs(grpc.StatusCode.CANCELLED, response_iterator.code())
        self.assertIsNotNone(response_iterator.details())
        self.assertIsNotNone(response_iterator.trailing_metadata())

    def _cancelled_stream_request_stream_response(self, multi_callable):
        """Tests cancellation of stream request with stream response."""
        requests = tuple(b"\x07\x08" for _ in range(test_constants.STREAM_LENGTH))
        request_iterator = iter(requests)
        with self._control.pause():
            response_iterator = multi_callable(
                request_iterator,
                metadata=(("test", "CancelledStreamRequestStreamResponse"),),
            )
            response_iterator.cancel()

        with self.assertRaises(grpc.RpcError):
            next(response_iterator)
        # Verify response metadata even after cancellation
        self.assertIsNotNone(response_iterator.initial_metadata())
        self.assertIs(grpc.StatusCode.CANCELLED, response_iterator.code())
        self.assertIsNotNone(response_iterator.details())
        self.assertIsNotNone(response_iterator.trailing_metadata())

    def _expired_unary_request_stream_response(self, multi_callable):
        """Tests timeout expiration for unary request with stream response."""
        request = b"\x07\x19"
        with self._control.pause():
            with self.assertRaises(grpc.RpcError) as exception_context:
                response_iterator = multi_callable(
                    request,
                    timeout=test_constants.SHORT_TIMEOUT,
                    metadata=(("test", "ExpiredUnaryRequestStreamResponse"),),
                )
                next(response_iterator)

        self.assertIs(grpc.StatusCode.DEADLINE_EXCEEDED, exception_context.exception.code())
        self.assertIs(grpc.StatusCode.DEADLINE_EXCEEDED, response_iterator.code())

    def _expired_stream_request_stream_response(self, multi_callable):
        """Tests timeout expiration for stream request with stream response."""
        requests = tuple(b"\x67\x18" for _ in range(test_constants.STREAM_LENGTH))
        request_iterator = iter(requests)
        with self._control.pause():
            with self.assertRaises(grpc.RpcError) as exception_context:
                response_iterator = multi_callable(
                    request_iterator,
                    timeout=test_constants.SHORT_TIMEOUT,
                    metadata=(("test", "ExpiredStreamRequestStreamResponse"),),
                )
                next(response_iterator)

        self.assertIs(gr