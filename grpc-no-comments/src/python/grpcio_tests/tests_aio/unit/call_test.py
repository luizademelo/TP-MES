# Copyright 2019 The gRPC Authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

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

_SHORT_TIMEOUT_S = datetime.timedelta(seconds=1).total_seconds()

_NUM_STREAM_RESPONSES = 5
_RESPONSE_PAYLOAD_SIZE = 42
_REQUEST_PAYLOAD_SIZE = 7
_LOCAL_CANCEL_DETAILS_EXPECTATION = "Locally cancelled by application!"
_RESPONSE_INTERVAL_US = int(_SHORT_TIMEOUT_S * 1000 * 1000)
_INFINITE_INTERVAL_US = 2**31 - 1

_NONDETERMINISTIC_ITERATIONS = 50
_NONDETERMINISTIC_SERVER_SLEEP_MAX_US = 1000

class _MulticallableTestMixin:
    async def setUp(self):
        address, self._server = await start_test_server()
        self._channel = aio.insecure_channel(address)
        self._stub = test_pb2_grpc.TestServiceStub(self._channel)

    async def tearDown(self):
        await self._channel.close()
        await self._server.stop(None)

class TestUnaryUnaryCall(_MulticallableTestMixin, AioTestBase):
    async def test_call_to_string(self):
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())

        self.assertTrue(str(call) is not None)
        self.assertTrue(repr(call) is not None)

        await call

        self.assertTrue(str(call) is not None)
        self.assertTrue(repr(call) is not None)

    async def test_call_ok(self):
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())

        self.assertFalse(call.done())

        response = await call

        self.assertTrue(call.done())
        self.assertIsInstance(response, messages_pb2.SimpleResponse)
        self.assertEqual(await call.code(), grpc.StatusCode.OK)

        response_retry = await call
        self.assertIs(response, response_retry)

    async def test_call_rpc_error(self):
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
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())
        self.assertEqual(await call.code(), grpc.StatusCode.OK)

    async def test_call_details_awaitable(self):
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())
        self.assertEqual("", await call.details())

    async def test_call_initial_metadata_awaitable(self):
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())
        self.assertEqual(aio.Metadata(), await call.initial_metadata())

    async def test_call_trailing_metadata_awaitable(self):
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())
        self.assertEqual(aio.Metadata(), await call.trailing_metadata())

    async def test_call_initial_metadata_cancelable(self):
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
        call = self._stub.UnaryCall(messages_pb2.SimpleRequest())

        async def coro():
            return await call.initial_metadata()

        task1 = self.loop.create_task(coro())
        task2 = self.loop.create_task(coro())

        await call
        expected = [aio.Metadata() for _ in range(2)]
        self.assertEqual(expected, await asyncio.gather(*[task1, task2]))

    async def test_call_code_cancelable(self):
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
    async def test_call_rpc_error(self):
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
        """Test cancellation after received all messages."""

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
        """Test calling read after received all messages fails."""

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
        """Sunny day test case for unary_stream."""

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
        """A cheap alternative to a structured fuzzer.

        Certain classes of error only appear for very specific interleavings of
        coroutines. Rather than inserting semi-private asyncio.Events throughout
        the implementation on which to coordinate and explicitly waiting on those
        in tests, we instead search for bugs over the space of interleavings by
        stochastically varying the durations of certain events within the test.
        """

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

        self.assertEqual(grpc.StatusCode.CANCELLED, await call.code())

        with self.assertRaises(asyncio.CancelledError):
            await task

    async def test_time_remaining(self):
        request = messages_pb2.StreamingOutputCallRequest()

        request.response_parameters.append(
            messages_pb2.ResponseParameters(
                size=_RESPONSE_PAYLOAD_SIZE,
            )
        )

        request.response_parameters.append(
            messages_pb2.ResponseParameters(
                size=_RESPONSE_PAYLOAD_SIZE,
                interval_us=_RESPONSE_INTERVAL_US,
            )
        )

        call = self._stub.StreamingOutputCall(
            request, timeout=_SHORT_TIMEOUT_S * 2
        )

        response = await call.read()
        self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))

        remained_time = call.time_remaining()
        self.assertGreater(remained_time, _SHORT_TIMEOUT_S * 3 / 2)
        self.assertLess(remained_time, _SHORT_TIMEOUT_S * 5 / 2)

        response = await call.read()
        self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))

        remained_time = call.time_remaining()
        self.assertGreater(remained_time, _SHORT_TIMEOUT_S / 2)
        self.assertLess(remained_time, _SHORT_TIMEOUT_S * 3 / 2)

        self.assertEqual(grpc.StatusCode.OK, await call.code())

    async def test_empty_responses(self):

        request = messages_pb2.StreamingOutputCallRequest()
        for _ in range(_NUM_STREAM_RESPONSES):
            request.response_parameters.append(
                messages_pb2.ResponseParameters()
            )

        call = self._stub.StreamingOutputCall(request)

        for _ in range(_NUM_STREAM_RESPONSES):
            response = await call.read()
            self.assertIs(
                type(response), messages_pb2.StreamingOutputCallResponse
            )
            self.assertEqual(b"", response.SerializeToString())

        self.assertEqual(grpc.StatusCode.OK, await call.code())

class TestStreamUnaryCall(_MulticallableTestMixin, AioTestBase):
    async def test_cancel_stream_unary(self):
        call = self._stub.StreamingInputCall()

        payload = messages_pb2.Payload(body=b"\0" * _REQUEST_PAYLOAD_SIZE)
        request = messages_pb2.StreamingInputCallRequest(payload=payload)

        for _ in range(_NUM_STREAM_RESPONSES):
            await call.write(request)

        self.assertFalse(call.done())
        self.assertFalse(call.cancelled())
        self.assertTrue(call.cancel())
        self.assertTrue(call.cancelled())

        await call.done_writing()

        with self.assertRaises(asyncio.CancelledError):
            await call

    async def test_early_cancel_stream_unary(self):
        call = self._stub.StreamingInputCall()

        self.assertFalse(call.done())
        self.assertFalse(call.cancelled())
        self.assertTrue(call.cancel())
        self.assertTrue(call.cancelled())

        with self.assertRaises(asyncio.InvalidStateError):
            await call.write(messages_pb2.StreamingInputCallRequest())

        await call.done_writing()

        with self.assertRaises(asyncio.CancelledError):
            await call

    async def test_write_after_done_writing(self):
        call = self._stub.StreamingInputCall()

        payload = messages_pb2.Payload(body=b"\0" * _REQUEST_PAYLOAD_SIZE)
        request = messages_pb2.StreamingInputCallRequest(payload=payload)

        for _ in range(_NUM_STREAM_RESPONSES):
            await call.write(request)

        await call.done_writing()

        with self.assertRaises(asyncio.InvalidStateError):
            await call.write(messages_pb2.StreamingInputCallRequest())

        response = await call
        self.assertIsInstance(response, messages_pb2.StreamingInputCallResponse)
        self.assertEqual(
            _NUM_STREAM_RESPONSES * _REQUEST_PAYLOAD_SIZE,
            response.aggregated_payload_size,
        )

        self.assertEqual(await call.code(), grpc.StatusCode.OK)

    async def test_error_in_async_generator(self):

        request = messages_pb2.StreamingOutputCallRequest()
        request.response_parameters.append(
            messages_pb2.ResponseParameters(
                size=_RESPONSE_PAYLOAD_SIZE,
                interval_us=_RESPONSE_INTERVAL_US,
            )
        )

        request_iterator_received_the_exception = asyncio.Event()

        async def request_iterator():
            with self.assertRaises(asyncio.CancelledError):
                for _ in range(_NUM_STREAM_RESPONSES):
                    yield request
                    await asyncio.sleep(_SHORT_TIMEOUT_S)
            request_iterator_received_the_exception.set()

        call = self._stub.StreamingInputCall(request_iterator())

        async def cancel_later():
            await asyncio.sleep(_SHORT_TIMEOUT_S * 2)
            call.cancel()

        cancel_later_task = self.loop.create_task(cancel_later())

        with self.assertRaises(asyncio.CancelledError):
            await call

        await request_iterator_received_the_exception.wait()

        await cancel_later_task

    async def test_normal_iterable_requests(self):

        payload = messages_pb2.Payload(body=b"\0" * _REQUEST_PAYLOAD_SIZE)
        request = messages_pb2.StreamingInputCallRequest(payload=payload)
        requests = [request] * _NUM_STREAM_RESPONSES

        call = self._stub.StreamingInputCall(requests)

        response = await call
        self.assertIsInstance(response, messages_pb2.StreamingInputCallResponse)
        self.assertEqual(
            _NUM_STREAM_RESPONSES * _REQUEST_PAYLOAD_SIZE,
            response.aggregated_payload_size,
        )

        self.assertEqual(await call.code(), grpc.StatusCode.OK)

    async def test_call_rpc_error(self):
        async with aio.insecure_channel(UNREACHABLE_TARGET) as channel:
            stub = test_pb2_grpc.TestServiceStub(channel)

            call = stub.StreamingInputCall()
            with self.assertRaises(aio.AioRpcError) as exception_context:
                await call

            self.assertEqual(
                grpc.StatusCode.UNAVAILABLE, exception_context.exception.code()
            )

            self.assertTrue(call.done())
            self.assertEqual(grpc.StatusCode.UNAVAILABLE, await call.code())

    async def test_timeout(self):
        call = self._stub.StreamingInputCall(timeout=_SHORT_TIMEOUT_S)

        with self.assertRaises(aio.AioRpcError) as exception_context:
            await call

        rpc_error = exception_context.exception
        self.assertEqual(grpc.StatusCode.DEADLINE_EXCEEDED, rpc_error.code())
        self.assertTrue(call.done())
        self.assertEqual(grpc.StatusCode.DEADLINE_EXCEEDED, await call.code())

_STREAM_OUTPUT_REQUEST_ONE_RESPONSE = messages_pb2.StreamingOutputCallRequest()
_STREAM_OUTPUT_REQUEST_ONE_RESPONSE.response_parameters.append(
    messages_pb2.ResponseParameters(size=_RESPONSE_PAYLOAD_SIZE)
)
_STREAM_OUTPUT_REQUEST_ONE_EMPTY_RESPONSE = (
    messages_pb2.StreamingOutputCallRequest()
)
_STREAM_OUTPUT_REQUEST_ONE_EMPTY_RESPONSE.response_parameters.append(
    messages_pb2.ResponseParameters()
)

class TestStreamStreamCall(_MulticallableTestMixin, AioTestBase):
    async def test_cancel(self):

        call = self._stub.FullDuplexCall()

        for _ in range(_NUM_STREAM_RESPONSES):
            await call.write(_STREAM_OUTPUT_REQUEST_ONE_RESPONSE)
            response = await call.read()
            self.assertIsInstance(
                response, messages_pb2.StreamingOutputCallResponse
            )
            self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))

        self.assertFalse(call.done())
        self.assertFalse(call.cancelled())
        self.assertTrue(call.cancel())
        self.assertTrue(call.cancelled())
        self.assertEqual(grpc.StatusCode.CANCELLED, await call.code())

    async def test_cancel_with_pending_read(self):
        call = self._stub.FullDuplexCall()

        await call.write(_STREAM_OUTPUT_REQUEST_ONE_RESPONSE)

        self.assertFalse(call.done())
        self.assertFalse(call.cancelled())
        self.assertTrue(call.cancel())
        self.assertTrue(call.cancelled())
        self.assertEqual(grpc.StatusCode.CANCELLED, await call.code())

    async def test_cancel_with_ongoing_read(self):
        call = self._stub.FullDuplexCall()
        coro_started = asyncio.Event()

        async def read_coro():
            coro_started.set()
            await call.read()

        read_task = self.loop.create_task(read_coro())
        await coro_started.wait()
        self.assertFalse(read_task.done())

        self.assertFalse(call.done())
        self.assertFalse(call.cancelled())
        self.assertTrue(call.cancel())
        self.assertTrue(call.cancelled())
        self.assertEqual(grpc.StatusCode.CANCELLED, await call.code())

    async def test_early_cancel(self):
        call = self._stub.FullDuplexCall()

        self.assertFalse(call.done())
        self.assertFalse(call.cancelled())
        self.assertTrue(call.cancel())
        self.assertTrue(call.cancelled())
        self.assertEqual(grpc.StatusCode.CANCELLED, await call.code())

    async def test_cancel_after_done_writing(self):
        call = self._stub.FullDuplexCall()
        request_with_delay = messages_pb2.StreamingOutputCallRequest()
        request_with_delay.response_parameters.append(
            messages_pb2.ResponseParameters(interval_us=10000)
        )
        await call.write(request_with_delay)
        await call.write(request_with_delay)
        await call.done_writing()

        self.assertFalse(call.cancelled())
        self.assertTrue(call.cancel())
        self.assertTrue(call.cancelled())
        self.assertEqual(grpc.StatusCode.CANCELLED, await call.code())

    async def test_late_cancel(self):
        call = self._stub.FullDuplexCall()
        await call.done_writing()
        self.assertEqual(grpc.StatusCode.OK, await call.code())

        self.assertTrue(call.done())
        self.assertFalse(call.cancelled())
        self.assertFalse(call.cancel())
        self.assertFalse(call.cancelled())

        self.assertEqual(grpc.StatusCode.OK, await call.code())

    async def test_async_generator(self):
        async def request_generator():
            yield _STREAM_OUTPUT_REQUEST_ONE_RESPONSE
            yield _STREAM_OUTPUT_REQUEST_ONE_RESPONSE

        call = self._stub.FullDuplexCall(request_generator())
        async for response in call:
            self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))

        self.assertEqual(await call.code(), grpc.StatusCode.OK)

    async def test_too_many_reads(self):
        async def request_generator():
            for _ in range(_NUM_STREAM_RESPONSES):
                yield _STREAM_OUTPUT_REQUEST_ONE_RESPONSE

        call = self._stub.FullDuplexCall(request_generator())
        for _ in range(_NUM_STREAM_RESPONSES):
            response = await call.read()
            self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))
        self.assertIs(await call.read(), aio.EOF)

        self.assertEqual(await call.code(), grpc.StatusCode.OK)

        self.assertIs(await call.read(), aio.EOF)

    async def test_read_write_after_done_writing(self):
        call = self._stub.FullDuplexCall()

        await call.write(_STREAM_OUTPUT_REQUEST_ONE_RESPONSE)
        await call.write(_STREAM_OUTPUT_REQUEST_ONE_RESPONSE)
        await call.done_writing()

        with self.assertRaises(asyncio.InvalidStateError):
            await call.write(_STREAM_OUTPUT_REQUEST_ONE_RESPONSE)

        response = await call.read()
        self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))
        response = await call.read()
        self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))

        self.assertEqual(await call.code(), grpc.StatusCode.OK)

    async def test_error_in_async_generator(self):

        request = messages_pb2.StreamingOutputCallRequest()
        request.response_parameters.append(
            messages_pb2.ResponseParameters(
                size=_RESPONSE_PAYLOAD_SIZE,
                interval_us=_RESPONSE_INTERVAL_US,
            )
        )

        request_iterator_received_the_exception = asyncio.Event()

        async def request_iterator():
            with self.assertRaises(asyncio.CancelledError):
                for _ in range(_NUM_STREAM_RESPONSES):
                    yield request
                    await asyncio.sleep(_SHORT_TIMEOUT_S)
            request_iterator_received_the_exception.set()

        call = self._stub.FullDuplexCall(request_iterator())

        async def cancel_later():
            await asyncio.sleep(_SHORT_TIMEOUT_S * 2)
            call.cancel()

        cancel_later_task = self.loop.create_task(cancel_later())

        with self.assertRaises(asyncio.CancelledError):
            async for response in call:
                self.assertEqual(
                    _RESPONSE_PAYLOAD_SIZE, len(response.payload.body)
                )

        await request_iterator_received_the_exception.wait()

        self.assertEqual(grpc.StatusCode.CANCELLED, await call.code())

        await cancel_later_task

    async def test_normal_iterable_requests(self):
        requests = [_STREAM_OUTPUT_REQUEST_ONE_RESPONSE] * _NUM_STREAM_RESPONSES

        call = self._stub.FullDuplexCall(iter(requests))
        async for response in call:
            self.assertEqual(_RESPONSE_PAYLOAD_SIZE, len(response.payload.body))

        self.assertEqual(await call.code(), grpc.StatusCode.OK)

    async def test_empty_ping_pong(self):
        call = self._stub.FullDuplexCall()
        for _ in range(_NUM_STREAM_RESPONSES):
            await call.write(_STREAM_OUTPUT_REQUEST_ONE_EMPTY_RESPONSE)
            response = await call.read()
            self.assertEqual(b"", response.SerializeToString())
        await call.done_writing()
        self.assertEqual(await call.code(), grpc.StatusCode.OK)

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    unittest.main(verbosity=2)
