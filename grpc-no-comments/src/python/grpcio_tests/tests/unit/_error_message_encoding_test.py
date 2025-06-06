# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Tests 'utf-8' encoded error message."""

import unittest
import weakref

import grpc

from tests.unit import test_common
from tests.unit.framework.common import test_constants

_UNICODE_ERROR_MESSAGES = [
    b"\xe2\x80\x9d".decode("utf-8"),
    b"abc\x80\xd0\xaf".decode("latin-1"),
    b"\xc3\xa9".decode("utf-8"),
]

_REQUEST = b"\x00\x00\x00"
_RESPONSE = b"\x00\x00\x00"

_SERVICE_NAME = "test"
_UNARY_UNARY = "UnaryUnary"

class _MethodHandler(grpc.RpcMethodHandler):
    def __init__(self, request_streaming=None, response_streaming=None):
        self.request_streaming = request_streaming
        self.response_streaming = response_streaming
        self.request_deserializer = None
        self.response_serializer = None
        self.unary_stream = None
        self.stream_unary = None
        self.stream_stream = None

    def unary_unary(self, request, servicer_context):
        servicer_context.set_code(grpc.StatusCode.UNKNOWN)
        servicer_context.set_details(request.decode("utf-8"))
        return _RESPONSE

_METHOD_HANDLERS = {_UNARY_UNARY: _MethodHandler()}

class ErrorMessageEncodingTest(unittest.TestCase):
    def setUp(self):
        self._server = test_common.test_server()
        self._server.add_registered_method_handlers(
            _SERVICE_NAME, _METHOD_HANDLERS
        )
        port = self._server.add_insecure_port("[::]:0")
        self._server.start()
        self._channel = grpc.insecure_channel("localhost:%d" % port)

    def tearDown(self):
        self._server.stop(0)
        self._channel.close()

    def testMessageEncoding(self):
        for message in _UNICODE_ERROR_MESSAGES:
            multi_callable = self._channel.unary_unary(
                grpc._common.fully_qualified_method(
                    _SERVICE_NAME, _UNARY_UNARY
                ),
                _registered_method=True,
            )
            with self.assertRaises(grpc.RpcError) as cm:
                multi_callable(message.encode("utf-8"))

            self.assertEqual(cm.exception.code(), grpc.StatusCode.UNKNOWN)
            self.assertEqual(cm.exception.details(), message)

if __name__ == "__main__":
    unittest.main(verbosity=2)
