Here's the commented version of the code:

```python
# Copyright 2019 The gRPC Authors.
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
"""Tests behavior of the Call classes."""

import asyncio
import datetime
import logging
import random
import unittest

import grpc
from grpc.experimental import aio

from src.proto.grpc.testing import messages_pb2
from src.proto.grpc.testing import test_pb2_grpc
from tests_aio.unit._constants import UNREACHABLE_TARGET
from tests_aio.unit._test_base import AioTestBase
from tests_aio.unit._test_server import start_test_server

# Constants for test configuration
_SHORT_TIMEOUT_S = datetime.timedelta(seconds=1).total_seconds()

_NUM_STREAM_RESPONSES = 5
_RESPONSE_PAYLOAD_SIZE = 42
_REQUEST_PAYLOAD_SIZE = 7
_LOCAL_CANCEL_DETAILS_EXPECTATION = "Locally cancelled by application!"
_RESPONSE_INTERVAL_US = int(_SHORT_TIMEOUT_S * 1000 * 1000)
_INFINITE_INTERVAL_US = 2**31 - 1

# Configuration for non-deterministic tests
_NONDETERMINISTIC_ITERATIONS = 50
_NONDETERMINISTIC_SERVER_SLEEP_MAX_US = 1000

class _MulticallableTestMixin:
    """Mixin class providing common setup/teardown for test classes."""
    
    async def setUp(self):
        """Set up test server and channel before each test."""
        address, self._server = await start_test_server()
        self._channel = aio.insecure_channel(address)
        self._stub = test_pb2_grpc.TestServiceStub(self._channel)

    async def tearDown(self):
        """Clean up channel and server after each test."""
        await self._channel.close()
        await self._server.stop(None)

class TestUnaryUnaryCall(_MulticallableTestMixin, AioTestBase):
    """Tests for unary-unary RPC calls."""
    
    async def test_call_to_string(self):
        """Test string representation of call objects."""
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())

        self.assertTrue(str(call) is not None)
        self.assertTrue(repr(call) is not None)

        await call

        self.assertTrue(str(call) is not None)
        self.assertTrue(repr(call) is not None)

    async def test_call_ok(self):
        """Test successful unary call."""
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())

        self.assertFalse(call.done())

        response = await call

        self.assertTrue(call.done())
        self.assertIsInstance(response, messages_pb2.SimpleResponse)
        self.assertEqual(await call.code(), grpc.StatusCode.OK)

        response_retry = await call
        self.assertIs(response, response_retry)

    async def test_call_rpc_error(self):
        """Test RPC error handling for unary calls."""
        async with aio.insecure_channel(UNREACHABLE_TARGET) as channel:
            stub = test_pb2_grpc.TestServiceStub(channel)

            call = stub.UnaryCall(messages_pb2.SimpleRequest())

            with self.assertRaises(aio.AioRpcError) as exception_context:
                await call

            self.assertEqual(
                grpc.StatusCode.UNAVAILABLE, exception_context.exception.code()
            )

            self.assertTrue(call.done())
            self.assertEqual(grpc.StatusCode.UNAVAILABLE, await call.code())

    async def test_call_code_awaitable(self):
        """Test awaitable status code."""
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())
        self.assertEqual(await call.code(), grpc.StatusCode.OK)

    async def test_call_details_awaitable(self):
        """Test awaitable call details."""
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())
        self.assertEqual("", await call.details())

    async def test_call_initial_metadata_awaitable(self):
        """Test awaitable initial metadata."""
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())
        self.assertEqual(aio.Metadata(), await call.initial_metadata())

    async def test_call_trailing_metadata_awaitable(self):
        """Test awaitable trailing metadata."""
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())
        self.assertEqual(aio.Metadata(), await call.trailing_metadata())

    async def test_call_initial_metadata_cancelable(self):
        """Test cancellation while waiting for initial metadata."""
        coro_started = asyncio.Event()
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())

        async def coro():
            coro_started.set()
            await call.initial_metadata()

        task = self.loop.create_task(coro())
        await coro_started.wait()
        task.cancel()

        self.assertEqual(aio.Metadata(), await call.initial_metadata())

    async def test_call_initial_metadata_multiple_waiters(self):
        """Test multiple coroutines waiting for initial metadata."""
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())

        async def coro():
            return await call.initial_metadata()

        task1 = self.loop.create_task(coro())
        task2 = self.loop.create_task(coro())

        await call
        expected = [aio.Metadata() for _ in range(2)]
        self.assertEqual(expected, await asyncio.gather(*[task1, task2]))

    async def test_call_code_cancelable(self):
        """Test cancellation while waiting for status code."""
        coro_started = asyncio.Event()
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())

        async def coro():
            coro_started.set()
            await call.code()

        task = self.loop.create_task(coro())
        await coro_started.wait()
        task.cancel()

        self.assertEqual(grpc.StatusCode.OK, await call.code())

    async def test_call_code_multiple_waiters(self):
        """Test multiple coroutines waiting for status code."""
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())

        async def coro():
            return await call.code()

        task1 = self.loop.create_task(coro())
        task2 = self.loop.create_task(coro())

        await call

        self.assertEqual(
            [grpc.StatusCode.OK, grpc.StatusCode.OK],
            await asyncio.gather(task1, task2),
        )

    async def test_cancel_unary_unary(self):
        """Test cancellation of unary call."""
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())

        self.assertFalse(call.cancelled())

        self.assertTrue(call.cancel())
        self.assertFalse(call.cancel())

        with self.assertRaises(asyncio.CancelledError):
            await call

        self.assertTrue(call.cancelled())
        self.assertEqual(await call.code(), grpc.StatusCode.CANCELLED)
        self.assertEqual(
            await call.details(), "Locally cancelled by application!"
        )

    async def test_cancel_unary_unary_in_task(self):
        """Test cancellation of unary call when called from another task."""
        coro_started = asyncio.Event()
        call = self._stub.EmptyCall(messages_pb2.SimpleRequest())

        async def another_coro():
            coro_started.set()
            await call

        task = self.loop.create_task(another_coro())
        await coro_started.wait()

        self.assertFalse(task.done())
        task.cancel()

        self.assertEqual(grpc.StatusCode.CANCELLED, await call.code())

        with self.assertRaises(asyncio.CancelledError):
            await task

    async def test_passing_credentials_fails_over_insecure_channel(self):
        """Test that call credentials fail on insecure channel."""
        call_credentials = grpc.composite_call_credentials(
            grpc.access_token_call_credentials("abc"),
            grpc.access_token_call_credentials("def"),
        )
        with self.assertRaisesRegex(
            aio.UsageError, "Call credentials are only valid on secure channels"
        ):
            self._stub.UnaryCall(
                messages_pb2.SimpleRequest(), credentials=call_credentials
            )

class TestUnaryStreamCall(_MulticallableTestMixin, AioTestBase):
    """Tests for unary-stream RPC calls."""
    
    async def test_call_rpc_error(self):
        """Test RPC error handling for unary-stream calls."""
        channel = aio.insecure_channel(UNREACHABLE_TARGET)
        request = messages_pb2.StreamingOutputCallRequest()
        stub = test_pb2_grpc.TestServiceStub(channel)
        call = stub.StreamingOutputCall(request)

        with self.assertRaises(aio.AioRpcError) as exception_context:
            async for response in call:
                pass

        self.assertEqual(
            grpc.StatusCode.UNAVAILABLE, exception_context.exception.code()
        )

        self.assertTrue(call.done())
        self.assertEqual(grpc.StatusCode.UNAVAILABLE, await call.code())
        await channel.close()

    async def test_cancel_unary_stream(self):
        """Test cancellation of unary-stream call."""
        request = messages_pb2.StreamingOutputCallRequest()
        for _ in range(_NUM_STREAM_RESPONSES):
            request.response_parameters.append(
                messages_pb2.ResponseParameters(
                    size=_RESPONSE_PAYLOAD_SIZE,
                    interval_us=_RESPONSE_INTERVAL_US,
                )
            )

        call = self._stub.StreamingOutputCall(request)
        self.assertFalse(call.cancelled())

        response = await call.read()
        self.assertIs(type(response), messages_pb2.StreamingOutputCallResponse)
        self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))

        self.assertTrue(call.cancel())
        self.assertEqual(grpc.StatusCode.CANCELLED, await call.code())
        self.assertEqual(
            _LOCAL_CANCEL_DETAILS_EXPECTATION, await call.details()
        )
        self.assertFalse(call.cancel())

        with self.assertRaises(asyncio.CancelledError):
            await call.read()
        self.assertTrue(call.cancelled())

    async def test_multiple_cancel_unary_stream(self):
        """Test multiple cancellation attempts on unary-stream call."""
        request = messages_pb2.StreamingOutputCallRequest()
        for _ in range(_NUM_STREAM_RESPONSES):
            request.response_parameters.append(
                messages_pb2.ResponseParameters(
                    size=_RESPONSE_PAYLOAD_SIZE,
                    interval_us=_RESPONSE_INTERVAL_US,
                )
            )

        call = self._stub.StreamingOutputCall(request)
        self.assertFalse(call.cancelled())

        response = await call.read()
        self.assertIs(type(response), messages_pb2.StreamingOutputCallResponse)
        self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))

        self.assertTrue(call.cancel())
        self.assertFalse(call.cancel())
        self.assertFalse(call.cancel())
        self.assertFalse(call.cancel())

        with self.assertRaises(asyncio.CancelledError):
            await call.read()

    async def test_early_cancel_unary_stream(self):
        """Test cancellation before receiving messages."""
        request = messages_pb2.StreamingOutputCallRequest()
        for _ in range(_NUM_STREAM_RESPONSES):
            request.response_parameters.append(
                messages_pb2.ResponseParameters(
                    size=_RESPONSE_PAYLOAD_SIZE,
                    interval_us=_RESPONSE_INTERVAL_US,
                )
            )

        call = self._stub.StreamingOutputCall(request)

        self.assertFalse(call.cancelled())
        self.assertTrue(call.cancel())
        self.assertFalse(call.cancel())

        with self.assertRaises(asyncio.CancelledError):
            await call.read()

        self.assertTrue(call.cancelled())

        self.assertEqual(grpc.StatusCode.CANCELLED, await call.code())
        self.assertEqual(
            _LOCAL_CANCEL_DETAILS_EXPECTATION, await call.details()
        )

    async def test_late_cancel_unary_stream(self):
        """Test cancellation after receiving all messages."""
        request = messages_pb2.StreamingOutputCallRequest()
        for _ in range(_NUM_STREAM_RESPONSES):
            request.response_parameters.append(
                messages_pb2.ResponseParameters(
                    size=_RESPONSE_PAYLOAD_SIZE,
                )
            )

        call = self._stub.StreamingOutputCall(request)

        for _ in range(_NUM_STREAM_RESPONSES):
            response = await call.read()
            self.assertIs(
                type(response), messages_pb2.StreamingOutputCallResponse
            )
            self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))

        call.cancel()
        self.assertIn(
            await call.code(), [grpc.StatusCode.OK, grpc.StatusCode.CANCELLED]
        )

    async def test_too_many_reads_unary_stream(self):
        """Test calling read after receiving all messages."""
        request = messages_pb2.StreamingOutputCallRequest()
        for _ in range(_NUM_STREAM_RESPONSES):
            request.response_parameters.append(
                messages_pb2.ResponseParameters(
                    size=_RESPONSE_PAYLOAD_SIZE,
                )
            )

        call = self._stub.StreamingOutputCall(request)

        for _ in range(_NUM_STREAM_RESPONSES):
            response = await call.read()
            self.assertIs(
                type(response), messages_pb2.StreamingOutputCallResponse
            )
            self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))
        self.assertIs(await call.read(), aio.EOF)

        self.assertEqual(await call.code(), grpc.StatusCode.OK)
        self.assertIs(await call.read(), aio.EOF)

    async def test_unary_stream_async_generator(self):
        """Test basic async generator usage with unary-stream call."""
        request = messages_pb2.StreamingOutputCallRequest()
        for _ in range(_NUM_STREAM_RESPONSES):
            request.response_parameters.append(
                messages_pb2.ResponseParameters(
                    size=_RESPONSE_PAYLOAD_SIZE,
                )
            )

        call = self._stub.StreamingOutputCall(request)
        self.assertFalse(call.cancelled())

        async for response in call:
            self.assertIs(
                type(response), messages_pb2.StreamingOutputCallResponse
            )
            self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))

        self.assertEqual(await call.code(), grpc.StatusCode.OK)

    async def test_cancel_unary_stream_with_many_interleavings(self):
        """Test cancellation with various interleavings to find race conditions."""
        sleep_ranges = (10.0**-i for i in range(1, 4))
        for sleep_range in sleep_ranges:
            for _ in range(_NONDETERMINISTIC_ITERATIONS):
                interval_us = random.randrange(
                    _NONDETERMINISTIC_SERVER_SLEEP_MAX_US
                )
                sleep_secs = sleep_range * random.random()

                coro_started = asyncio.Event()

                request = messages_pb2.StreamingOutputCallRequest()
                request.response_parameters.append(
                    messages_pb2.ResponseParameters(
                        size=1,
                        interval_us=interval_us,
                    )
                )

                call = self._stub.StreamingOutputCall(request)

                unhandled_error = False

                async def another_coro():
                    nonlocal unhandled_error
                    coro_started.set()
                    try:
                        await call.read()
                    except asyncio.CancelledError:
                        pass
                    except Exception as e:
                        unhandled_error = True
                        raise

                task = self.loop.create_task(another_coro())
                await coro_started.wait()
                await asyncio.sleep(sleep_secs)

                task.cancel()

                try:
                    await task
                except asyncio.CancelledError:
                    pass

                self.assertFalse(unhandled_error)

    async def test_cancel_unary_stream_in_task_using_read(self):
        """Test cancellation of unary-stream call in separate task using read()."""
        coro_started = asyncio.Event()

        request = messages_pb2.StreamingOutputCallRequest()
        request.response_parameters.append(
            messages_pb2.ResponseParameters(
                size=_RESPONSE_PAYLOAD_SIZE,
                interval_us=_INFINITE_INTERVAL_US,
            )
        )

        call = self._stub.StreamingOutputCall(request)

        async def another_coro():
            coro_started.set()
            await call.read()

        task = self.loop.create_task(another_coro())
        await coro_started.wait()

        self.assertFalse(task.done())
        task.cancel()

        self.assertEqual(grpc.StatusCode.CANCELLED, await call.code())

        with self.assertRaises(asyncio.CancelledError):
            await task

    async def test_cancel_unary_stream_in_task_using_async_for(self):
        """Test cancellation of unary-stream call in separate task using async for."""
        coro_started = asyncio.Event()

        request = messages_pb2.StreamingOutputCallRequest()
        request.response_parameters.append(
            messages_pb2.ResponseParameters(
                size=_RESPONSE_PAYLOAD_SIZE,
                interval_us=_INFINITE_INTERVAL_US,
            )
        )

        call = self._stub.StreamingOutputCall(request)

        async def another_coro():
            coro_started.set()
            async for _ in call:
                pass

        task = self.loop.create_task(another_coro())
        await coro_started.wait()

        self.assertFalse(task.done())
        task.cancel()

        self.assertEqual(grpc.Status