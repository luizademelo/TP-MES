# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Test of RPCs made against gRPC Python's application-layer API."""

import logging
import unittest

import grpc

from tests.unit.framework.common import test_constants

_SERIALIZE_REQUEST = lambda bytestring: bytestring * 2
_DESERIALIZE_REQUEST = lambda bytestring: bytestring[len(bytestring) // 2 :]
_SERIALIZE_RESPONSE = lambda bytestring: bytestring * 3
_DESERIALIZE_RESPONSE = lambda bytestring: bytestring[: len(bytestring) // 3]

_SERVICE_NAME = "test"
_UNARY_UNARY = "UnaryUnary"
_UNARY_STREAM = "UnaryStream"
_STREAM_UNARY = "StreamUnary"
_STREAM_STREAM = "StreamStream"

def _unary_unary_multi_callable(channel):
    return channel.unary_unary(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _UNARY_UNARY),
        _registered_method=True,
    )

def _unary_stream_multi_callable(channel):
    return channel.unary_stream(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _UNARY_STREAM),
        request_serializer=_SERIALIZE_REQUEST,
        response_deserializer=_DESERIALIZE_RESPONSE,
        _registered_method=True,
    )

def _stream_unary_multi_callable(channel):
    return channel.stream_unary(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _STREAM_UNARY),
        request_serializer=_SERIALIZE_REQUEST,
        response_deserializer=_DESERIALIZE_RESPONSE,
        _registered_method=True,
    )

def _stream_stream_multi_callable(channel):
    return channel.stream_stream(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _STREAM_STREAM),
        _registered_method=True,
    )

class InvalidMetadataTest(unittest.TestCase):
    def setUp(self):
        self._channel = grpc.insecure_channel("localhost:8080")
        self._unary_unary = _unary_unary_multi_callable(self._channel)
        self._unary_stream = _unary_stream_multi_callable(self._channel)
        self._stream_unary = _stream_unary_multi_callable(self._channel)
        self._stream_stream = _stream_stream_multi_callable(self._channel)

    def tearDown(self):
        self._channel.close()

    def testUnaryRequestBlockingUnaryResponse(self):
        request = b"\x07\x08"
        metadata = (("InVaLiD", "UnaryRequestBlockingUnaryResponse"),)
        expected_error_details = "metadata was invalid: %s" % metadata
        with self.assertRaises(ValueError) as exception_context:
            self._unary_unary(request, metadata=metadata)
        self.assertIn(expected_error_details, str(exception_context.exception))

    def testUnaryRequestBlockingUnaryResponseWithCall(self):
        request = b"\x07\x08"
        metadata = (("InVaLiD", "UnaryRequestBlockingUnaryResponseWithCall"),)
        expected_error_details = "metadata was invalid: %s" % metadata
        with self.assertRaises(ValueError) as exception_context:
            self._unary_unary.with_call(request, metadata=metadata)
        self.assertIn(expected_error_details, str(exception_context.exception))

    def testUnaryRequestFutureUnaryResponse(self):
        request = b"\x07\x08"
        metadata = (("InVaLiD", "UnaryRequestFutureUnaryResponse"),)
        expected_error_details = "metadata was invalid: %s" % metadata
        with self.assertRaises(ValueError) as exception_context:
            self._unary_unary.future(request, metadata=metadata)

    def testUnaryRequestStreamResponse(self):
        request = b"\x37\x58"
        metadata = (("InVaLiD", "UnaryRequestStreamResponse"),)
        expected_error_details = "metadata was invalid: %s" % metadata
        with self.assertRaises(ValueError) as exception_context:
            self._unary_stream(request, metadata=metadata)
        self.assertIn(expected_error_details, str(exception_context.exception))

    def testStreamRequestBlockingUnaryResponse(self):
        request_iterator = (
            b"\x07\x08" for _ in range(test_constants.STREAM_LENGTH)
        )
        metadata = (("InVaLiD", "StreamRequestBlockingUnaryResponse"),)
        expected_error_details = "metadata was invalid: %s" % metadata
        with self.assertRaises(ValueError) as exception_context:
            self._stream_unary(request_iterator, metadata=metadata)
        self.assertIn(expected_error_details, str(exception_context.exception))

    def testStreamRequestBlockingUnaryResponseWithCall(self):
        request_iterator = (
            b"\x07\x08" for _ in range(test_constants.STREAM_LENGTH)
        )
        metadata = (("InVaLiD", "StreamRequestBlockingUnaryResponseWithCall"),)
        expected_error_details = "metadata was invalid: %s" % metadata
        multi_callable = _stream_unary_multi_callable(self._channel)
        with self.assertRaises(ValueError) as exception_context:
            multi_callable.with_call(request_iterator, metadata=metadata)
        self.assertIn(expected_error_details, str(exception_context.exception))

    def testStreamRequestFutureUnaryResponse(self):
        request_iterator = (
            b"\x07\x08" for _ in range(test_constants.STREAM_LENGTH)
        )
        metadata = (("InVaLiD", "StreamRequestFutureUnaryResponse"),)
        expected_error_details = "metadata was invalid: %s" % metadata
        with self.assertRaises(ValueError) as exception_context:
            self._stream_unary.future(request_iterator, metadata=metadata)
        self.assertIn(expected_error_details, str(exception_context.exception))

    def testStreamRequestStreamResponse(self):
        request_iterator = (
            b"\x07\x08" for _ in range(test_constants.STREAM_LENGTH)
        )
        metadata = (("InVaLiD", "StreamRequestStreamResponse"),)
        expected_error_details = "metadata was invalid: %s" % metadata
        with self.assertRaises(ValueError) as exception_context:
            self._stream_stream(request_iterator, metadata=metadata)
        self.assertIn(expected_error_details, str(exception_context.exception))

    def testInvalidMetadata(self):
        self.assertRaises(TypeError, self._unary_unary, b"", metadata=42)

if __name__ == "__main__":
    logging.basicConfig()
    unittest.main(verbosity=2)
