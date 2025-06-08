Here's the commented version of the code:

```python
# Copyright 2016 gRPC authors.
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

"""Test of RPCs made against gRPC Python's application-layer API."""

from concurrent import futures
import itertools
import logging
import threading
import unittest

import grpc
from grpc.framework.foundation import logging_pool

# Import test helpers and constants
from tests.unit._rpc_test_helpers import (
    stream_stream_non_blocking_multi_callable,
)
from tests.unit._rpc_test_helpers import (
    unary_stream_non_blocking_multi_callable,
)
from tests.unit._rpc_test_helpers import BaseRPCTest
from tests.unit._rpc_test_helpers import Callback
from tests.unit._rpc_test_helpers import TIMEOUT_SHORT
from tests.unit._rpc_test_helpers import stream_stream_multi_callable
from tests.unit._rpc_test_helpers import stream_unary_multi_callable
from tests.unit._rpc_test_helpers import unary_stream_multi_callable
from tests.unit._rpc_test_helpers import unary_unary_multi_callable
from tests.unit.framework.common import test_constants

class RPCPart2Test(BaseRPCTest, unittest.TestCase):
    """Test suite for gRPC Python's application-layer API (part 2)."""

    def testDefaultThreadPoolIsUsed(self):
        """Test that the default thread pool is used for stream responses."""
        self._consume_one_stream_response_unary_request(
            unary_stream_multi_callable(self._channel)
        )
        self.assertFalse(self._thread_pool.was_used())

    def testExperimentalThreadPoolIsUsed(self):
        """Test that the experimental thread pool is used for non-blocking calls."""
        self._consume_one_stream_response_unary_request(
            unary_stream_non_blocking_multi_callable(self._channel)
        )
        self.assertTrue(self._thread_pool.was_used())

    def testUnrecognizedMethod(self):
        """Test that calling an unrecognized method raises UNIMPLEMENTED error."""
        request = b"abc"

        with self.assertRaises(grpc.RpcError) as exception_context:
            self._channel.unary_unary("NoSuchMethod")(request)

        self.assertEqual(
            grpc.StatusCode.UNIMPLEMENTED, exception_context.exception.code()
        )

    def testSuccessfulUnaryRequestBlockingUnaryResponse(self):
        """Test successful unary request with blocking unary response."""
        request = b"\x07\x08"
        expected_response = self._handler.handle_unary_unary(request, None)

        multi_callable = unary_unary_multi_callable(self._channel)
        response = multi_callable(
            request,
            metadata=(("test", "SuccessfulUnaryRequestBlockingUnaryResponse"),),
        )

        self.assertEqual(expected_response, response)

    def testSuccessfulUnaryRequestBlockingUnaryResponseWithCall(self):
        """Test successful unary request with blocking unary response using with_call."""
        request = b"\x07\x08"
        expected_response = self._handler.handle_unary_unary(request, None)

        multi_callable = unary_unary_multi_callable(self._channel)
        response, call = multi_callable.with_call(
            request,
            metadata=(
                ("test", "SuccessfulUnaryRequestBlockingUnaryResponseWithCall"),
            ),
        )

        self.assertEqual(expected_response, response)
        self.assertIs(grpc.StatusCode.OK, call.code())
        self.assertEqual("", call.debug_error_string())

    def testSuccessfulUnaryRequestFutureUnaryResponse(self):
        """Test successful unary request with future unary response."""
        request = b"\x07\x08"
        expected_response = self._handler.handle_unary_unary(request, None)

        multi_callable = unary_unary_multi_callable(self._channel)
        response_future = multi_callable.future(
            request,
            metadata=(("test", "SuccessfulUnaryRequestFutureUnaryResponse"),),
        )
        response = response_future.result()

        self.assertIsInstance(response_future, grpc.Future)
        self.assertIsInstance(response_future, grpc.Call)
        self.assertEqual(expected_response, response)
        self.assertIsNone(response_future.exception())
        self.assertIsNone(response_future.traceback())

    def testSuccessfulUnaryRequestStreamResponse(self):
        """Test successful unary request with stream response."""
        request = b"\x37\x58"
        expected_responses = tuple(
            self._handler.handle_unary_stream(request, None)
        )

        multi_callable = unary_stream_multi_callable(self._channel)
        response_iterator = multi_callable(
            request,
            metadata=(("test", "SuccessfulUnaryRequestStreamResponse"),),
        )
        responses = tuple(response_iterator)

        self.assertSequenceEqual(expected_responses, responses)

    def testSuccessfulStreamRequestBlockingUnaryResponse(self):
        """Test successful stream request with blocking unary response."""
        requests = tuple(
            b"\x07\x08" for _ in range(test_constants.STREAM_LENGTH)
        )
        expected_response = self._handler.handle_stream_unary(
            iter(requests), None
        )
        request_iterator = iter(requests)

        multi_callable = stream_unary_multi_callable(self._channel)
        response = multi_callable(
            request_iterator,
            metadata=(
                ("test", "SuccessfulStreamRequestBlockingUnaryResponse"),
            ),
        )

        self.assertEqual(expected_response, response)

    def testSuccessfulStreamRequestBlockingUnaryResponseWithCall(self):
        """Test successful stream request with blocking unary response using with_call."""
        requests = tuple(
            b"\x07\x08" for _ in range(test_constants.STREAM_LENGTH)
        )
        expected_response = self._handler.handle_stream_unary(
            iter(requests), None
        )
        request_iterator = iter(requests)

        multi_callable = stream_unary_multi_callable(self._channel)
        response, call = multi_callable.with_call(
            request_iterator,
            metadata=(
                (
                    "test",
                    "SuccessfulStreamRequestBlockingUnaryResponseWithCall",
                ),
            ),
        )

        self.assertEqual(expected_response, response)
        self.assertIs(grpc.StatusCode.OK, call.code())

    def testSuccessfulStreamRequestFutureUnaryResponse(self):
        """Test successful stream request with future unary response."""
        requests = tuple(
            b"\x07\x08" for _ in range(test_constants.STREAM_LENGTH)
        )
        expected_response = self._handler.handle_stream_unary(
            iter(requests), None
        )
        request_iterator = iter(requests)

        multi_callable = stream_unary_multi_callable(self._channel)
        response_future = multi_callable.future(
            request_iterator,
            metadata=(("test", "SuccessfulStreamRequestFutureUnaryResponse"),),
        )
        response = response_future.result()

        self.assertEqual(expected_response, response)
        self.assertIsNone(response_future.exception())
        self.assertIsNone(response_future.traceback())

    def testSuccessfulStreamRequestStreamResponse(self):
        """Test successful stream request with stream response."""
        requests = tuple(
            b"\x77\x58" for _ in range(test_constants.STREAM_LENGTH)
        )

        expected_responses = tuple(
            self._handler.handle_stream_stream(iter(requests), None)
        )
        request_iterator = iter(requests)

        multi_callable = stream_stream_multi_callable(self._channel)
        response_iterator = multi_callable(
            request_iterator,
            metadata=(("test", "SuccessfulStreamRequestStreamResponse"),),
        )
        responses = tuple(response_iterator)

        self.assertSequenceEqual(expected_responses, responses)

    def testSequentialInvocations(self):
        """Test sequential invocations of the same RPC method."""
        first_request = b"\x07\x08"
        second_request = b"\x0809"
        expected_first_response = self._handler.handle_unary_unary(
            first_request, None
        )
        expected_second_response = self._handler.handle_unary_unary(
            second_request, None
        )

        multi_callable = unary_unary_multi_callable(self._channel)
        first_response = multi_callable(
            first_request, metadata=(("test", "SequentialInvocations"),)
        second_response = multi_callable(
            second_request, metadata=(("test", "SequentialInvocations"),)

        self.assertEqual(expected_first_response, first_response)
        self.assertEqual(expected_second_response, second_response)

    def testConcurrentBlockingInvocations(self):
        """Test concurrent blocking invocations of the same RPC method."""
        pool = logging_pool.pool(test_constants.THREAD_CONCURRENCY)
        requests = tuple(
            b"\x07\x08" for _ in range(test_constants.STREAM_LENGTH)
        )
        expected_response = self._handler.handle_stream_unary(
            iter(requests), None
        )
        expected_responses = [
            expected_response
        ] * test_constants.THREAD_CONCURRENCY
        response_futures = [None] * test_constants.THREAD_CONCURRENCY

        multi_callable = stream_unary_multi_callable(self._channel)
        for index in range(test_constants.THREAD_CONCURRENCY):
            request_iterator = iter(requests)
            response_future = pool.submit(
                multi_callable,
                request_iterator,
                metadata=(("test", "ConcurrentBlockingInvocations"),),
            )
            response_futures[index] = response_future
        responses = tuple(
            response_future.result() for response_future in response_futures
        )

        pool.shutdown(wait=True)
        self.assertSequenceEqual(expected_responses, responses)

    def testConcurrentFutureInvocations(self):
        """Test concurrent future invocations of the same RPC method."""
        requests = tuple(
            b"\x07\x08" for _ in range(test_constants.STREAM_LENGTH)
        )
        expected_response = self._handler.handle_stream_unary(
            iter(requests), None
        )
        expected_responses = [
            expected_response
        ] * test_constants.THREAD_CONCURRENCY
        response_futures = [None] * test_constants.THREAD_CONCURRENCY

        multi_callable = stream_unary_multi_callable(self._channel)
        for index in range(test_constants.THREAD_CONCURRENCY):
            request_iterator = iter(requests)
            response_future = multi_callable.future(
                request_iterator,
                metadata=(("test", "ConcurrentFutureInvocations"),),
            )
            response_futures[index] = response_future
        responses = tuple(
            response_future.result() for response_future in response_futures
        )

        self.assertSequenceEqual(expected_responses, responses)

    def testWaitingForSomeButNotAllConcurrentFutureInvocations(self):
        """Test waiting for some but not all concurrent future invocations."""
        pool = logging_pool.pool(test_constants.THREAD_CONCURRENCY)
        request = b"\x67\x68"
        expected_response = self._handler.handle_unary_unary(request, None)
        response_futures = [None] * test_constants.THREAD_CONCURRENCY
        lock = threading.Lock()
        test_is_running_cell = [True]

        def wrap_future(future):
            def wrap():
                try:
                    return future.result()
                except grpc.RpcError:
                    with lock:
                        if test_is_running_cell[0]:
                            raise
                    return None

            return wrap

        multi_callable = unary_unary_multi_callable(self._channel)
        for index in range(test_constants.THREAD_CONCURRENCY):
            inner_response_future = multi_callable.future(
                request,
                metadata=(
                    (
                        "test",
                        "WaitingForSomeButNotAllConcurrentFutureInvocations",
                    ),
                ),
            )
            outer_response_future = pool.submit(
                wrap_future(inner_response_future)
            )
            response_futures[index] = outer_response_future

        some_completed_response_futures_iterator = itertools.islice(
            futures.as_completed(response_futures),
            test_constants.THREAD_CONCURRENCY // 2,
        )
        for response_future in some_completed_response_futures_iterator:
            self.assertEqual(expected_response, response_future.result())
        with lock:
            test_is_running_cell[0] = False

    def testConsumingOneStreamResponseUnaryRequest(self):
        """Test consuming one stream response from a unary request."""
        self._consume_one_stream_response_unary_request(
            unary_stream_multi_callable(self._channel)
        )

    def testConsumingOneStreamResponseUnaryRequestNonBlocking(self):
        """Test consuming one stream response from a non-blocking unary request."""
        self._consume_one_stream_response_unary_request(
            unary_stream_non_blocking_multi_callable(self._channel)
        )

    def testConsumingSomeButNotAllStreamResponsesUnaryRequest(self):
        """Test consuming some but not all stream responses from a unary request."""
        self._consume_some_but_not_all_stream_responses_unary_request(
            unary_stream_multi_callable(self._channel)
        )

    def testConsumingSomeButNotAllStreamResponsesUnaryRequestNonBlocking(self):
        """Test consuming some but not all stream responses from a non-blocking unary request."""
        self._consume_some_but_not_all_stream_responses_unary_request(
            unary_stream_non_blocking_multi_callable(self._channel)
        )

    def testConsumingSomeButNotAllStreamResponsesStreamRequest(self):
        """Test consuming some but not all stream responses from a stream request."""
        self._consume_some_but_not_all_stream_responses_stream_request(
            stream_stream_multi_callable(self._channel)
        )

    def testConsumingSomeButNotAllStreamResponsesStreamRequestNonBlocking(self):
        """Test consuming some but not all stream responses from a non-blocking stream request."""
        self._consume_some_but_not_all_stream_responses_stream_request(
            stream_stream_non_blocking_multi_callable(self._channel)
        )

    def testConsumingTooManyStreamResponsesStreamRequest(self):
        """Test consuming too many stream responses from a stream request."""
        self._consume_too_many_stream_responses_stream_request(
            stream_stream_multi_callable(self._channel)
        )

    def testConsumingTooManyStreamResponsesStreamRequestNonBlocking(self):
        """Test consuming too many stream responses from a non-blocking stream request."""
        self._consume_too_many_stream_responses_stream_request(
            stream_stream_non_blocking_multi_callable(self._channel)
        )

    def testCancelledUnaryRequestUnaryResponse(self):
        """Test cancellation of unary request with unary response."""
        request = b"\x07\x17"

        multi_callable = unary_unary_multi_callable(self._channel)
        with self._control.pause():
            response_future = multi_callable.future(
                request,
                metadata=(("test", "CancelledUnaryRequestUnaryResponse"),),
            )
            response_future.cancel()

        self.assertIs(grpc.StatusCode.CANCELLED, response_future.code())
        self.assertTrue(response_future.cancelled())
        with self.assertRaises(grpc.FutureCancelledError):
            response_future.result()
        with self.assertRaises(grpc.FutureCancelledError):
            response_future.exception()
        with self.assertRaises(grpc.FutureCancelledError):
            response_future.traceback()

    def testCancelledUnaryRequestStreamResponse(self):
        """Test cancellation of unary request with stream response."""
        self._cancelled_unary_request_stream_response(
            unary_stream_multi_callable(self._channel)
        )

    def testCancelledUnaryRequestStreamResponseNonBlocking(self):
        """Test cancellation of unary request with non-blocking stream response."""
        self._cancelled_unary_request_stream_response(
            unary_stream_non_blocking_multi_callable(self._channel)
        )

    def testCancelledStreamRequestUnaryResponse(self):
        """Test cancellation of stream request with unary response."""
        requests = tuple(
            b"\x07\x08" for _ in range(test_constants.STREAM_LENGTH)
        )
        request_iterator = iter(requests)

        multi_callable = stream_unary_multi_callable(self._channel)
        with self._control.pause():
            response_future = multi_callable.future(
                request_iterator,
                metadata=(("test", "CancelledStreamRequestUnaryResponse"),),
            )
            self._control.block_until_paused()
            response_future.cancel()

        self.assertIs(grpc.StatusCode.CANCELLED, response_future.code())
        self.assertTrue(response_future.cancelled())
        with self.assertRaises(grpc.FutureCancelledError):
            response_future.result()
        with self.assertRaises(grpc.FutureCancelledError):
            response_future.exception()
        with self.assertRaises(grpc.FutureCancelledError):
            response_future.traceback()
        self.assertIsNotNone(response_future.initial_metadata())
        self.assertIsNotNone(response_future.details())
        self.assertIsNotNone(response_future.trailing_metadata())

    def testCancelledStreamRequestStreamResponse(self):
        """Test cancellation of stream request with stream response."""
        self._cancelled_stream_request_stream_response(
            stream_stream_multi_callable(self._channel)
        )

    def testCancelledStreamRequestStreamResponseNonBlocking(self):
        """Test cancellation of stream request with non-blocking stream response."""
        self._cancelled_stream_request_stream_response(
            stream_stream_non_blocking_multi_callable(self._channel)
        )

    def testExpiredUnaryRequestBlockingUnaryResponse(self):
        """Test expired unary request with blocking unary response."""
        request = b"\x07\x17"

        multi_callable = unary_unary_multi_callable(self._channel)
        with self._control.pause():
            with self.assertRaises(grpc.RpcError) as exception_context: