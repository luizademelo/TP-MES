Here's the commented version of the code:

```c++
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Test the functionality of server interceptors."""

import asyncio
import functools
import logging
from typing import Any, Awaitable, Callable, Tuple
import unittest

import grpc
from grpc.experimental import aio
from grpc.experimental import wrap_server_method_handler

from src.proto.grpc.testing import messages_pb2
from src.proto.grpc.testing import test_pb2_grpc
from tests_aio.unit._test_base import AioTestBase
from tests_aio.unit._test_server import TEST_CONTEXT_VAR
from tests_aio.unit._test_server import start_test_server

# Constants for test configuration
_NUM_STREAM_RESPONSES = 5  # Number of responses in streaming tests
_REQUEST_PAYLOAD_SIZE = 7  # Size of request payload in bytes
_RESPONSE_PAYLOAD_SIZE = 42  # Size of response payload in bytes

class _LoggingInterceptor(aio.ServerInterceptor):
    """Interceptor that logs its execution with a given tag."""
    def __init__(self, tag: str, record: list) -> None:
        """Initialize with a tag and record list to store logs."""
        self.tag = tag
        self.record = record

    async def intercept_service(
        self,
        continuation: Callable[
            [grpc.HandlerCallDetails], Awaitable[grpc.RpcMethodHandler]
        ],
        handler_call_details: grpc.HandlerCallDetails,
    ) -> grpc.RpcMethodHandler:
        """Log the interception and continue with the request."""
        self.record.append(
            self.tag + ":" + TEST_CONTEXT_VAR.get("intercept_service")
        )
        return await continuation(handler_call_details)

class _ContextVarSettingInterceptor(aio.ServerInterceptor):
    """Interceptor that sets context variables."""
    def __init__(self, value: str) -> None:
        """Initialize with the value to set in context."""
        self.value = value

    async def intercept_service(
        self,
        continuation: Callable[
            [grpc.HandlerCallDetails], Awaitable[grpc.RpcMethodHandler]
        ],
        handler_call_details: grpc.HandlerCallDetails,
    ) -> grpc.RpcMethodHandler:
        """Set context variable and continue with the request."""
        new_value = self.value
        old_value = TEST_CONTEXT_VAR.get("")
        if old_value:
            new_value = old_value + ":" + new_value
        TEST_CONTEXT_VAR.set(new_value)
        return await continuation(handler_call_details)

class _GenericInterceptor(aio.ServerInterceptor):
    """Generic interceptor that wraps a given function."""
    def __init__(
        self,
        fn: Callable[
            [
                Callable[
                    [grpc.HandlerCallDetails], Awaitable[grpc.RpcMethodHandler]
                ],
                grpc.HandlerCallDetails,
            ],
            Any,
        ],
    ) -> None:
        """Initialize with the function to wrap."""
        self._fn = fn

    async def intercept_service(
        self,
        continuation: Callable[
            [grpc.HandlerCallDetails], Awaitable[grpc.RpcMethodHandler]
        ],
        handler_call_details: grpc.HandlerCallDetails,
    ) -> grpc.RpcMethodHandler:
        """Execute the wrapped function."""
        return await self._fn(continuation, handler_call_details)

def _filter_server_interceptor(
    condition: Callable, interceptor: aio.ServerInterceptor
) -> aio.ServerInterceptor:
    """Create an interceptor that applies another interceptor conditionally."""
    async def intercept_service(
        continuation: Callable[
            [grpc.HandlerCallDetails], Awaitable[grpc.RpcMethodHandler]
        ],
        handler_call_details: grpc.HandlerCallDetails,
    ) -> grpc.RpcMethodHandler:
        """Apply interceptor only if condition is met."""
        if condition(handler_call_details):
            return await interceptor.intercept_service(
                continuation, handler_call_details
            )
        return await continuation(handler_call_details)

    return _GenericInterceptor(intercept_service)

class _CacheInterceptor(aio.ServerInterceptor):
    """An interceptor that caches response based on request message."""

    def __init__(self, cache_store=None):
        """Initialize with optional cache store dictionary."""
        self.cache_store = cache_store or {}

    async def intercept_service(
        self,
        continuation: Callable[
            [grpc.HandlerCallDetails], Awaitable[grpc.RpcMethodHandler]
        ],
        handler_call_details: grpc.HandlerCallDetails,
    ) -> grpc.RpcMethodHandler:
        """Cache responses for non-streaming methods."""
        handler = await continuation(handler_call_details)

        # Skip caching for streaming methods
        if handler and (
            handler.request_streaming
            or handler.response_streaming
        ):
            return handler

        def wrapper(
            behavior: Callable[
                [messages_pb2.SimpleRequest, aio.ServicerContext],
                messages_pb2.SimpleResponse,
            ]
        ):
            """Wrapper function to implement caching logic."""
            @functools.wraps(behavior)
            async def wrapper(
                request: messages_pb2.SimpleRequest,
                context: aio.ServicerContext,
            ) -> messages_pb2.SimpleResponse:
                """Check cache before executing behavior."""
                if request.response_size not in self.cache_store:
                    self.cache_store[request.response_size] = await behavior(
                        request, context
                    )
                return self.cache_store[request.response_size]

            return wrapper

        return wrap_server_method_handler(wrapper, handler)

async def _create_server_stub_pair(
    record: list, *interceptors: aio.ServerInterceptor
) -> Tuple[aio.Server, test_pb2_grpc.TestServiceStub]:
    """Creates a server-stub pair with given record and interceptors.

    Args:
        record: List to record interceptor execution
        interceptors: Interceptors to apply to the server

    Returns:
        Tuple of (server, stub) where server is kept to prevent garbage collection
    """
    server_target, server = await start_test_server(
        interceptors=interceptors, record=record
    )
    channel = aio.insecure_channel(server_target)
    return server, test_pb2_grpc.TestServiceStub(channel)

class TestServerInterceptor(AioTestBase):
    """Test suite for server interceptors."""

    async def test_invalid_interceptor(self):
        """Test that invalid interceptors are rejected."""
        class InvalidInterceptor:
            """Just an invalid Interceptor"""

        with self.assertRaises(ValueError):
            server_target, _ = await start_test_server(
                interceptors=(InvalidInterceptor(),)
            )

    async def test_executed_right_order(self):
        """Test interceptors execute in correct order."""
        record = []
        server_target, _ = await start_test_server(
            record=record,
            interceptors=(
                _LoggingInterceptor("log1", record),
                _ContextVarSettingInterceptor("context_var_value"),
                _LoggingInterceptor("log2", record),
            ),
        )

        async with aio.insecure_channel(server_target) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCall",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )
            call = multicallable(messages_pb2.SimpleRequest())
            response = await call

            self.assertSequenceEqual(
                [
                    "log1:intercept_service",
                    "log2:context_var_value",
                    "servicer:context_var_value",
                ],
                record,
            )
            self.assertIsInstance(response, messages_pb2.SimpleResponse)

    async def test_unique_context_per_call(self):
        """Test context is properly reset between calls."""
        record = []
        server, stub = await _create_server_stub_pair(
            record,
            _LoggingInterceptor("log1", record),
            _ContextVarSettingInterceptor("context_var_value"),
            _LoggingInterceptor("log2", record),
        )

        response = await stub.UnaryCall(
            messages_pb2.SimpleRequest(response_size=42)
        )

        self.assertSequenceEqual(
            [
                "log1:intercept_service",
                "log2:context_var_value",
                "servicer:context_var_value",
            ],
            record,
        )
        record.clear()

        response = await stub.UnaryCall(
            messages_pb2.SimpleRequest(response_size=42)
        )

        self.assertSequenceEqual(
            [
                "log1:intercept_service",
                "log2:context_var_value",
                "servicer:context_var_value",
            ],
            record,
        )

    async def test_response_ok(self):
        """Test successful response with interceptor."""
        record = []
        server_target, _ = await start_test_server(
            interceptors=(_LoggingInterceptor("log1", record),)
        )

        async with aio.insecure_channel(server_target) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCall",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )
            call = multicallable(messages_pb2.SimpleRequest())
            response = await call
            code = await call.code()

            self.assertSequenceEqual(["log1:intercept_service"], record)
            self.assertIsInstance(response, messages_pb2.SimpleResponse)
            self.assertEqual(code, grpc.StatusCode.OK)

    async def test_apply_different_interceptors_by_metadata(self):
        """Test conditional interceptor application based on metadata."""
        record = []
        conditional_interceptor = _filter_server_interceptor(
            lambda x: ("secret", "42") in x.invocation_metadata,
            _LoggingInterceptor("log3", record),
        )
        server_target, _ = await start_test_server(
            interceptors=(
                _LoggingInterceptor("log1", record),
                conditional_interceptor,
                _LoggingInterceptor("log2", record),
            )
        )

        async with aio.insecure_channel(server_target) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCall",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )

            metadata = aio.Metadata(
                ("key", "value"),
            )
            call = multicallable(
                messages_pb2.SimpleRequest(), metadata=metadata
            )
            await call
            self.assertSequenceEqual(
                [
                    "log1:intercept_service",
                    "log2:intercept_service",
                ],
                record,
            )

            record.clear()
            metadata = aio.Metadata(("key", "value"), ("secret", "42"))
            call = multicallable(
                messages_pb2.SimpleRequest(), metadata=metadata
            )
            await call
            self.assertSequenceEqual(
                [
                    "log1:intercept_service",
                    "log3:intercept_service",
                    "log2:intercept_service",
                ],
                record,
            )

    async def test_response_caching(self):
        """Test response caching functionality."""
        interceptor = _CacheInterceptor(
            {
                42: messages_pb2.SimpleResponse(
                    payload=messages_pb2.Payload(body=b"\x42")
                )
            }
        )

        server, stub = await _create_server_stub_pair([], interceptor)

        # Test cached response
        response = await stub.UnaryCall(
            messages_pb2.SimpleRequest(response_size=42)
        )
        self.assertEqual(1, len(interceptor.cache_store[42].payload.body))
        self.assertEqual(interceptor.cache_store[42], response)

        # Test new response
        response = await stub.UnaryCall(
            messages_pb2.SimpleRequest(response_size=1337)
        )
        self.assertEqual(1337, len(interceptor.cache_store[1337].payload.body))
        self.assertEqual(interceptor.cache_store[1337], response)
        
        # Test cached response again
        response = await stub.UnaryCall(
            messages_pb2.SimpleRequest(response_size=1337)
        )
        self.assertEqual(interceptor.cache_store[1337], response)

    async def test_interceptor_unary_stream(self):
        """Test interceptors with unary-stream RPC."""
        record = []
        server, stub = await _create_server_stub_pair(
            record,
            _ContextVarSettingInterceptor("context_var_value"),
            _LoggingInterceptor("log_unary_stream", record),
        )

        request = messages_pb2.StreamingOutputCallRequest()
        for _ in range(_NUM_STREAM_RESPONSES):
            request.response_parameters.append(
                messages_pb2.ResponseParameters(
                    size=_RESPONSE_PAYLOAD_SIZE,
                )
            )

        call = stub.StreamingOutputCall(request)

        async for response in call:
            self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))
        self.assertEqual(await call.code(), grpc.StatusCode.OK)

        self.assertSequenceEqual(
            [
                "log_unary_stream:context_var_value",
                "servicer:context_var_value",
            ],
            record,
        )

    async def test_interceptor_stream_unary(self):
        """Test interceptors with stream-unary RPC."""
        record = []
        server, stub = await _create_server_stub_pair(
            record,
            _ContextVarSettingInterceptor("context_var_value"),
            _LoggingInterceptor("log_stream_unary", record),
        )

        call = stub.StreamingInputCall()

        payload = messages_pb2.Payload(body=b"\0" * _REQUEST_PAYLOAD_SIZE)
        request = messages_pb2.StreamingInputCallRequest(payload=payload)

        for _ in range(_NUM_STREAM_RESPONSES):
            await call.write(request)
        await call.done_writing()

        response = await call
        self.assertIsInstance(response, messages_pb2.StreamingInputCallResponse)
        self.assertEqual(
            _NUM_STREAM_RESPONSES * _REQUEST_PAYLOAD_SIZE,
            response.aggregated_payload_size,
        )

        self.assertEqual(await call.code(), grpc.StatusCode.OK)

        self.assertSequenceEqual(
            [
                "log_stream_unary:context_var_value",
                "servicer:context_var_value",
            ],
            record,
        )

    async def test_interceptor_stream_stream(self):
        """Test interceptors with stream-stream RPC."""
        record = []
        server, stub = await _create_server_stub_pair(
            record,
            _ContextVarSettingInterceptor("context_var_value"),
            _LoggingInterceptor("log_stream_stream", record),
        )

        payload = messages_pb2.Payload(body=b"\0" * _REQUEST_PAYLOAD_SIZE)
        request = messages_pb2.StreamingInputCallRequest(payload=payload)

        async def gen():
            """Request generator for streaming call."""
            for _ in range(_NUM_STREAM_RESPONSES):
                yield request

        call = stub.StreamingInputCall(gen())

        response = await call
        self.assertIsInstance(response, messages_pb2.StreamingInputCallResponse)
        self.assertEqual(
            _NUM_STREAM_RESPONSES * _REQUEST_PAYLOAD_SIZE,
            response.aggregated_payload_size,
        )

        self.assertEqual(await call.code(), grpc.StatusCode.OK)

        self.assertSequenceEqual(
            [
                "log_stream_stream:context_var_value",
                "servicer:context_var_value",
            ],
            record,
        )

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    unittest.main(verbosity=2)
```