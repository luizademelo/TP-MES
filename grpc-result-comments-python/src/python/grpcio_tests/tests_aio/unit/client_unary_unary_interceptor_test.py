Here's the commented version of the code:

```python
# Copyright 2019 The gRPC Authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Import required modules
import asyncio
import logging
import unittest

import grpc
from grpc.experimental import aio

from src.proto.grpc.testing import messages_pb2
from src.proto.grpc.testing import test_pb2_grpc
from tests_aio.unit import _common
from tests_aio.unit import _constants
from tests_aio.unit._test_base import AioTestBase
from tests_aio.unit._test_server import _INITIAL_METADATA_KEY
from tests_aio.unit._test_server import _TRAILING_METADATA_KEY
from tests_aio.unit._test_server import start_test_server

# Constants for testing
_LOCAL_CANCEL_DETAILS_EXPECTATION = "Locally cancelled by application!"
_INITIAL_METADATA_TO_INJECT = aio.Metadata(
    (_INITIAL_METADATA_KEY, "extra info"),
    (_TRAILING_METADATA_KEY, b"\x13\x37"),
)
_TIMEOUT_CHECK_IF_CALLBACK_WAS_CALLED = 1.0

class TestUnaryUnaryClientInterceptor(AioTestBase):
    """Test class for UnaryUnaryClientInterceptor functionality."""

    async def setUp(self):
        """Set up test server before each test."""
        self._server_target, self._server = await start_test_server()

    async def tearDown(self):
        """Clean up test server after each test."""
        await self._server.stop(None)

    def test_invalid_interceptor(self):
        """Test that invalid interceptor raises ValueError."""
        class InvalidInterceptor:
            """Just an invalid Interceptor"""

        with self.assertRaises(ValueError):
            aio.insecure_channel("", interceptors=[InvalidInterceptor()])

    async def test_executed_right_order(self):
        """Test interceptors are executed in the correct order."""
        interceptors_executed = []

        class Interceptor(aio.UnaryUnaryClientInterceptor):
            """Interceptor used for testing if the interceptor is being called"""

            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                interceptors_executed.append(self)
                call = await continuation(client_call_details, request)
                return call

        interceptors = [Interceptor() for i in range(2)]

        async with aio.insecure_channel(
            self._server_target, interceptors=interceptors
        ) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCall",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )
            call = multicallable(messages_pb2.SimpleRequest())
            response = await call

            self.assertSequenceEqual(interceptors_executed, interceptors)
            self.assertIsInstance(response, messages_pb2.SimpleResponse)

    @unittest.expectedFailure
    def test_modify_metadata(self):
        """Test metadata modification (expected to fail)."""
        raise NotImplementedError()

    @unittest.expectedFailure
    def test_modify_credentials(self):
        """Test credentials modification (expected to fail)."""
        raise NotImplementedError()

    async def test_status_code_Ok(self):
        """Test interceptor observing status code OK."""
        class StatusCodeOkInterceptor(aio.UnaryUnaryClientInterceptor):
            """Interceptor used for observing status code Ok returned by the RPC"""

            def __init__(self):
                self.status_code_Ok_observed = False

            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                call = await continuation(client_call_details, request)
                code = await call.code()
                if code == grpc.StatusCode.OK:
                    self.status_code_Ok_observed = True
                return call

        interceptor = StatusCodeOkInterceptor()

        async with aio.insecure_channel(
            self._server_target, interceptors=[interceptor]
        ) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCall",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )

            await multicallable(messages_pb2.SimpleRequest())
            self.assertTrue(interceptor.status_code_Ok_observed)

    async def test_add_timeout(self):
        """Test interceptor adding timeout to RPC."""
        class TimeoutInterceptor(aio.UnaryUnaryClientInterceptor):
            """Interceptor used for adding a timeout to the RPC"""

            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                new_client_call_details = aio.ClientCallDetails(
                    method=client_call_details.method,
                    timeout=_constants.UNARY_CALL_WITH_SLEEP_VALUE / 2,
                    metadata=client_call_details.metadata,
                    credentials=client_call_details.credentials,
                    wait_for_ready=client_call_details.wait_for_ready,
                )
                return await continuation(new_client_call_details, request)

        interceptor = TimeoutInterceptor()

        async with aio.insecure_channel(
            self._server_target, interceptors=[interceptor]
        ) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCallWithSleep",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )

            call = multicallable(messages_pb2.SimpleRequest())

            with self.assertRaises(aio.AioRpcError) as exception_context:
                await call

            self.assertEqual(
                exception_context.exception.code(),
                grpc.StatusCode.DEADLINE_EXCEEDED,
            )
            self.assertTrue(call.done())
            self.assertEqual(
                grpc.StatusCode.DEADLINE_EXCEEDED, await call.code()
            )

    async def test_retry(self):
        """Test retry interceptor functionality."""
        class RetryInterceptor(aio.UnaryUnaryClientInterceptor):
            """Simulates a Retry Interceptor which ends up by making two RPC calls."""

            def __init__(self):
                self.calls = []

            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                new_client_call_details = aio.ClientCallDetails(
                    method=client_call_details.method,
                    timeout=_constants.UNARY_CALL_WITH_SLEEP_VALUE / 2,
                    metadata=client_call_details.metadata,
                    credentials=client_call_details.credentials,
                    wait_for_ready=client_call_details.wait_for_ready,
                )

                try:
                    call = await continuation(new_client_call_details, request)
                    await call
                except grpc.RpcError:
                    pass

                self.calls.append(call)

                new_client_call_details = aio.ClientCallDetails(
                    method=client_call_details.method,
                    timeout=None,
                    metadata=client_call_details.metadata,
                    credentials=client_call_details.credentials,
                    wait_for_ready=client_call_details.wait_for_ready,
                )

                call = await continuation(new_client_call_details, request)
                self.calls.append(call)
                return call

        interceptor = RetryInterceptor()

        async with aio.insecure_channel(
            self._server_target, interceptors=[interceptor]
        ) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCallWithSleep",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )

            call = multicallable(messages_pb2.SimpleRequest())
            await call

            self.assertEqual(grpc.StatusCode.OK, await call.code())
            self.assertEqual(len(interceptor.calls), 2)
            self.assertEqual(
                await interceptor.calls[0].code(),
                grpc.StatusCode.DEADLINE_EXCEEDED,
            )
            self.assertEqual(
                await interceptor.calls[1].code(), grpc.StatusCode.OK
            )

    async def test_retry_with_multiple_interceptors(self):
        """Test retry interceptor working with multiple interceptors."""
        class RetryInterceptor(aio.UnaryUnaryClientInterceptor):
            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                for _ in range(2):
                    call = await continuation(client_call_details, request)
                    result = await call
                return result

        class AnotherInterceptor(aio.UnaryUnaryClientInterceptor):
            def __init__(self):
                self.called_times = 0

            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                self.called_times += 1
                call = await continuation(client_call_details, request)
                result = await call
                return result

        retry_interceptor = RetryInterceptor()
        another_interceptor = AnotherInterceptor()
        async with aio.insecure_channel(
            self._server_target,
            interceptors=[retry_interceptor, another_interceptor],
        ) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCallWithSleep",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )

            call = multicallable(messages_pb2.SimpleRequest())
            await call

            self.assertEqual(grpc.StatusCode.OK, await call.code())
            self.assertEqual(another_interceptor.called_times, 2)

    async def test_rpcresponse(self):
        """Test raw response handling in interceptors."""
        class Interceptor(aio.UnaryUnaryClientInterceptor):
            """Raw responses are seen as regular calls"""

            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                call = await continuation(client_call_details, request)
                response = await call
                return call

        class ResponseInterceptor(aio.UnaryUnaryClientInterceptor):
            """Return a raw response"""

            response = messages_pb2.SimpleResponse()

            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                return ResponseInterceptor.response

        interceptor, interceptor_response = Interceptor(), ResponseInterceptor()

        async with aio.insecure_channel(
            self._server_target,
            interceptors=[interceptor, interceptor_response],
        ) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCall",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )

            call = multicallable(messages_pb2.SimpleRequest())
            response = await call

            self.assertEqual(id(response), id(ResponseInterceptor.response))
            self.assertTrue(call.done())
            self.assertFalse(call.cancel())
            self.assertFalse(call.cancelled())
            self.assertEqual(await call.code(), grpc.StatusCode.OK)
            self.assertEqual(await call.details(), "")
            self.assertEqual(await call.initial_metadata(), None)
            self.assertEqual(await call.trailing_metadata(), None)
            self.assertEqual(await call.debug_error_string(), None)

class TestInterceptedUnaryUnaryCall(AioTestBase):
    """Test class for intercepted UnaryUnary calls."""

    async def setUp(self):
        """Set up test server before each test."""
        self._server_target, self._server = await start_test_server()

    async def tearDown(self):
        """Clean up test server after each test."""
        await self._server.stop(None)

    async def test_call_ok(self):
        """Test successful intercepted call."""
        class Interceptor(aio.UnaryUnaryClientInterceptor):
            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                call = await continuation(client_call_details, request)
                return call

        async with aio.insecure_channel(
            self._server_target, interceptors=[Interceptor()]
        ) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCall",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )
            call = multicallable(messages_pb2.SimpleRequest())
            response = await call

            self.assertTrue(call.done())
            self.assertFalse(call.cancelled())
            self.assertEqual(type(response), messages_pb2.SimpleResponse)
            self.assertEqual(await call.code(), grpc.StatusCode.OK)
            self.assertEqual(await call.details(), "")
            self.assertEqual(await call.initial_metadata(), aio.Metadata())
            self.assertEqual(await call.trailing_metadata(), aio.Metadata())

    async def test_call_ok_awaited(self):
        """Test successful intercepted call with await."""
        class Interceptor(aio.UnaryUnaryClientInterceptor):
            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                call = await continuation(client_call_details, request)
                await call
                return call

        async with aio.insecure_channel(
            self._server_target, interceptors=[Interceptor()]
        ) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCall",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )
            call = multicallable(messages_pb2.SimpleRequest())
            response = await call

            self.assertTrue(call.done())
            self.assertFalse(call.cancelled())
            self.assertEqual(type(response), messages_pb2.SimpleResponse)
            self.assertEqual(await call.code(), grpc.StatusCode.OK)
            self.assertEqual(await call.details(), "")
            self.assertEqual(await call.initial_metadata(), aio.Metadata())
            self.assertEqual(await call.trailing_metadata(), aio.Metadata())

    async def test_call_rpc_error(self):
        """Test RPC error in intercepted call."""
        class Interceptor(aio.UnaryUnaryClientInterceptor):
            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                call = await continuation(client_call_details, request)
                return call

        async with aio.insecure_channel(
            self._server_target, interceptors=[Interceptor()]
        ) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCallWithSleep",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )

            call = multicallable(
                messages_pb2.SimpleRequest(),
                timeout=_constants.UNARY_CALL_WITH_SLEEP_VALUE / 2,
            )

            with self.assertRaises(aio.AioRpcError) as exception_context:
                await call

            self.assertTrue(call.done())
            self.assertFalse(call.cancelled())
            self.assertEqual(
                await call.code(), grpc.StatusCode.DEADLINE_EXCEEDED
            )
            self.assertEqual(await call.details(), "Deadline Exceeded")
            self.assertEqual(await call.initial_metadata(), aio.Metadata())
            self.assertEqual(await call.trailing_metadata(), aio.Metadata())

    async def test_call_rpc_error_awaited(self):
        """Test RPC error in intercepted call with await."""
        class Interceptor(aio.UnaryUnaryClientInterceptor):
            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                call = await continuation(client_call_details, request)
                await call
                return call

        async with aio.insecure_channel(
            self._server_target, interceptors=[Interceptor()]
        ) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCallWithSleep",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )

            call = multicallable(
                messages_pb2.SimpleRequest(),
                timeout=_constants.UNARY_CALL_WITH_SLEEP_VALUE / 2,
            )

            with self.assertRaises(aio.AioRpcError) as exception_context:
                await call

            self.assertTrue(call.done())
            self.assertFalse(call.cancelled())
            self.assertEqual(
                await call.code(), grpc.StatusCode.DEADLINE_EXCEEDED
            )
            self.assertEqual(await call.details(), "Deadline Exceeded")
            self.assertEqual(await call.initial_metadata(), aio.Metadata())
            self.assertEqual(await call.trailing_metadata(), aio.Metadata())

    async def test_cancel_before_rpc(self):
        """Test canceling call before RPC starts."""
        interceptor_reached = asyncio.Event()
        wait_for_ever = self.loop.create_future()

        class Interceptor(aio.UnaryUnaryClientInterceptor):
            async def intercept_unary_unary(
                self, continuation, client_call_details, request
            ):
                interceptor_reached.set()
                await wait_for_ever

        async with aio.insecure_channel(
            self._server_target, interceptors=[Interceptor()]
        ) as channel:
            multicallable = channel.unary_unary(
                "/grpc.testing.TestService/UnaryCall",
                request_serializer=messages_pb2.SimpleRequest.SerializeToString,
                response_deserializer=messages_pb2.SimpleResponse.FromString,
            )
            call = multicallable(messages_pb2.SimpleRequest())

            self.assertFalse(call.cancelled())
            self.assertFalse(call.done())

            await interceptor_reached.wait()
            self.assertTrue(call.cancel())

            with self.assertRaises(asyncio.CancelledError):