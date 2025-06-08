Here's the commented version of the code:

```python
# Copyright 2020 The gRPC Authors.
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

import logging
import unittest

import grpc
from grpc.experimental import aio

from src.proto.grpc.testing import messages_pb2
from src.proto.grpc.testing import test_pb2_grpc
from tests_aio.unit._common import CountingRequestIterator
from tests_aio.unit._common import CountingResponseIterator
from tests_aio.unit._test_base import AioTestBase
from tests_aio.unit._test_server import start_test_server

# Constants for test configuration
_NUM_STREAM_RESPONSES = 5  # Number of stream responses to test
_NUM_STREAM_REQUESTS = 5   # Number of stream requests to test
_RESPONSE_PAYLOAD_SIZE = 7 # Size of response payload in bytes

class _StreamStreamInterceptorEmpty(aio.StreamStreamClientInterceptor):
    """Empty interceptor that just passes through the call without modification."""
    
    async def intercept_stream_stream(
        self, continuation, client_call_details, request_iterator
    ):
        """Intercepts the stream-stream call and passes it through unchanged.
        
        Args:
            continuation: Function to continue the RPC call
            client_call_details: Details of the RPC call
            request_iterator: Iterator for the request stream
            
        Returns:
            The result of the continuation call
        """
        return await continuation(client_call_details, request_iterator)

    def assert_in_final_state(self, test: unittest.TestCase):
        """No-op assertion method for empty interceptor."""
        pass

class _StreamStreamInterceptorWithRequestAndResponseIterator(
    aio.StreamStreamClientInterceptor
):
    """Interceptor that counts requests and responses for validation."""
    
    async def intercept_stream_stream(
        self, continuation, client_call_details, request_iterator
    ):
        """Intercepts the stream-stream call and wraps request/response iterators.
        
        Args:
            continuation: Function to continue the RPC call
            client_call_details: Details of the RPC call
            request_iterator: Iterator for the request stream
            
        Returns:
            A wrapped response iterator that counts responses
        """
        # Wrap the request iterator to count requests
        self.request_iterator = CountingRequestIterator(request_iterator)
        # Continue the call with the wrapped request iterator
        call = await continuation(client_call_details, self.request_iterator)
        # Wrap the response iterator to count responses
        self.response_iterator = CountingResponseIterator(call)
        return self.response_iterator

    def assert_in_final_state(self, test: unittest.TestCase):
        """Verifies the expected number of requests and responses were processed.
        
        Args:
            test: The unittest.TestCase instance for assertions
        """
        test.assertEqual(
            _NUM_STREAM_REQUESTS, self.request_iterator.request_cnt
        )
        test.assertEqual(
            _NUM_STREAM_RESPONSES, self.response_iterator.response_cnt
        )

class TestStreamStreamClientInterceptor(AioTestBase):
    """Test case for stream-stream client interceptors."""
    
    async def setUp(self):
        """Set up test environment by starting a test server."""
        self._server_target, self._server = await start_test_server()

    async def tearDown(self):
        """Clean up test environment by stopping the test server."""
        await self._server.stop(None)

    async def test_intercepts(self):
        """Tests interceptors with async streaming calls."""
        for interceptor_class in (
            _StreamStreamInterceptorEmpty,
            _StreamStreamInterceptorWithRequestAndResponseIterator,
        ):
            with self.subTest(name=interceptor_class):
                # Create interceptor and channel
                interceptor = interceptor_class()
                channel = aio.insecure_channel(
                    self._server_target, interceptors=[interceptor]
                )
                stub = test_pb2_grpc.TestServiceStub(channel)

                # Prepare request with response parameters
                request = messages_pb2.StreamingOutputCallRequest()
                request.response_parameters.append(
                    messages_pb2.ResponseParameters(size=_RESPONSE_PAYLOAD_SIZE)
                )

                # Create request iterator that yields _NUM_STREAM_REQUESTS requests
                async def request_iterator():
                    for _ in range(_NUM_STREAM_REQUESTS):
                        yield request

                # Make the streaming call
                call = stub.FullDuplexCall(request_iterator())

                # Wait for connection to be established
                await call.wait_for_connection()

                # Process and validate responses
                response_cnt = 0
                async for response in call:
                    response_cnt += 1
                    self.assertIsInstance(
                        response, messages_pb2.StreamingOutputCallResponse
                    )
                    self.assertEqual(
                        _RESPONSE_PAYLOAD_SIZE, len(response.payload.body)
                    )

                # Validate response count and call status
                self.assertEqual(response_cnt, _NUM_STREAM_RESPONSES)
                self.assertEqual(await call.code(), grpc.StatusCode.OK)
                self.assertEqual(await call.initial_metadata(), aio.Metadata())
                self.assertEqual(await call.trailing_metadata(), aio.Metadata())
                self.assertEqual(await call.details(), "")
                self.assertEqual(await call.debug_error_string(), "")
                self.assertEqual(call.cancel(), False)
                self.assertEqual(call.cancelled(), False)
                self.assertEqual(call.done(), True)

                # Verify interceptor state
                interceptor.assert_in_final_state(self)

                # Clean up
                await channel.close()

    async def test_intercepts_using_write_and_read(self):
        """Tests interceptors with manual write/read streaming calls."""
        for interceptor_class in (
            _StreamStreamInterceptorEmpty,
            _StreamStreamInterceptorWithRequestAndResponseIterator,
        ):
            with self.subTest(name=interceptor_class):
                # Create interceptor and channel
                interceptor = interceptor_class()
                channel = aio.insecure_channel(
                    self._server_target, interceptors=[interceptor]
                )
                stub = test_pb2_grpc.TestServiceStub(channel)

                # Prepare request with response parameters
                request = messages_pb2.StreamingOutputCallRequest()
                request.response_parameters.append(
                    messages_pb2.ResponseParameters(size=_RESPONSE_PAYLOAD_SIZE)
                )

                # Create streaming call
                call = stub.FullDuplexCall()

                # Manually write requests and read responses
                for _ in range(_NUM_STREAM_RESPONSES):
                    await call.write(request)
                    response = await call.read()
                    self.assertIsInstance(
                        response, messages_pb2.StreamingOutputCallResponse
                    )
                    self.assertEqual(
                        _RESPONSE_PAYLOAD_SIZE, len(response.payload.body)
                    )

                # Signal end of writes
                await call.done_writing()

                # Validate call status
                self.assertEqual(await call.code(), grpc.StatusCode.OK)
                self.assertEqual(await call.initial_metadata(), aio.Metadata())
                self.assertEqual(await call.trailing_metadata(), aio.Metadata())
                self.assertEqual(await call.details(), "")
                self.assertEqual(await call.debug_error_string(), "")
                self.assertEqual(call.cancel(), False)
                self.assertEqual(call.cancelled(), False)
                self.assertEqual(call.done(), True)

                # Verify interceptor state
                interceptor.assert_in_final_state(self)

                # Clean up
                await channel.close()

    async def test_multiple_interceptors_request_iterator(self):
        """Tests multiple interceptors with manual write/read streaming calls."""
        for interceptor_class in (
            _StreamStreamInterceptorEmpty,
            _StreamStreamInterceptorWithRequestAndResponseIterator,
        ):
            with self.subTest(name=interceptor_class):
                # Create multiple interceptors
                interceptors = [interceptor_class(), interceptor_class()]
                channel = aio.insecure_channel(
                    self._server_target, interceptors=interceptors
                )
                stub = test_pb2_grpc.TestServiceStub(channel)

                # Prepare request with response parameters
                request = messages_pb2.StreamingOutputCallRequest()
                request.response_parameters.append(
                    messages_pb2.ResponseParameters(size=_RESPONSE_PAYLOAD_SIZE)
                )

                # Create streaming call
                call = stub.FullDuplexCall()

                # Manually write requests and read responses
                for _ in range(_NUM_STREAM_RESPONSES):
                    await call.write(request)
                    response = await call.read()
                    self.assertIsInstance(
                        response, messages_pb2.StreamingOutputCallResponse
                    )
                    self.assertEqual(
                        _RESPONSE_PAYLOAD_SIZE, len(response.payload.body)
                    )

                # Signal end of writes
                await call.done_writing()

                # Validate call status
                self.assertEqual(await call.code(), grpc.StatusCode.OK)
                self.assertEqual(await call.initial_metadata(), aio.Metadata())
                self.assertEqual(await call.trailing_metadata(), aio.Metadata())
                self.assertEqual(await call.details(), "")
                self.assertEqual(await call.debug_error_string(), "")
                self.assertEqual(call.cancel(), False)
                self.assertEqual(call.cancelled(), False)
                self.assertEqual(call.done(), True)

                # Verify all interceptors' states
                for interceptor in interceptors:
                    interceptor.assert_in_final_state(self)

                # Clean up
                await channel.close()

if __name__ == "__main__":
    # Configure logging and run tests
    logging.basicConfig(level=logging.DEBUG)
    unittest.main(verbosity=2)
```