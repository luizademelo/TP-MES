Here's the commented version of the code:

```python
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

# List of test error messages containing various unicode characters
# First message is a right double quotation mark (utf-8)
# Second message is a mix of ASCII and invalid utf-8 (decoded as latin-1)
# Third message is a lowercase e with acute accent (utf-8)
_UNICODE_ERROR_MESSAGES = [
    b"\xe2\x80\x9d".decode("utf-8"),
    b"abc\x80\xd0\xaf".decode("latin-1"),
    b"\xc3\xa9".decode("utf-8"),
]

# Simple binary request and response payloads
_REQUEST = b"\x00\x00\x00"
_RESPONSE = b"\x00\x00\x00"

# Service and method names for testing
_SERVICE_NAME = "test"
_UNARY_UNARY = "UnaryUnary"

class _MethodHandler(grpc.RpcMethodHandler):
    """Custom RPC method handler for testing error message encoding."""
    def __init__(self, request_streaming=None, response_streaming=None):
        """Initialize method handler with streaming options."""
        self.request_streaming = request_streaming
        self.response_streaming = response_streaming
        self.request_deserializer = None
        self.response_serializer = None
        self.unary_stream = None
        self.stream_unary = None
        self.stream_stream = None

    def unary_unary(self, request, servicer_context):
        """
        Unary-unary RPC implementation that always returns an error.
        
        Args:
            request: The incoming request message
            servicer_context: Context object for the RPC
            
        Returns:
            Always returns the predefined _RESPONSE, but first sets error status
            with the request message as error details.
        """
        # Set error status and use decoded request as error message
        servicer_context.set_code(grpc.StatusCode.UNKNOWN)
        servicer_context.set_details(request.decode("utf-8"))
        return _RESPONSE

# Dictionary mapping method names to their handlers
_METHOD_HANDLERS = {_UNARY_UNARY: _MethodHandler()}

class ErrorMessageEncodingTest(unittest.TestCase):
    """Test case for verifying proper encoding of error messages in gRPC."""
    
    def setUp(self):
        """Set up test server and channel before each test."""
        # Create and configure test server
        self._server = test_common.test_server()
        self._server.add_registered_method_handlers(
            _SERVICE_NAME, _METHOD_HANDLERS
        )
        # Start server on an insecure port
        port = self._server.add_insecure_port("[::]:0")
        self._server.start()
        # Create client channel to connect to the server
        self._channel = grpc.insecure_channel("localhost:%d" % port)

    def tearDown(self):
        """Clean up server and channel after each test."""
        self._server.stop(0)
        self._channel.close()

    def testMessageEncoding(self):
        """Test that unicode error messages are properly encoded and preserved."""
        for message in _UNICODE_ERROR_MESSAGES:
            # Create a unary-unary RPC callable
            multi_callable = self._channel.unary_unary(
                grpc._common.fully_qualified_method(
                    _SERVICE_NAME, _UNARY_UNARY
                ),
                _registered_method=True,
            )
            
            # Verify that the RPC fails with expected error message
            with self.assertRaises(grpc.RpcError) as cm:
                multi_callable(message.encode("utf-8"))

            # Check that error code and message match what we set in the handler
            self.assertEqual(cm.exception.code(), grpc.StatusCode.UNKNOWN)
            self.assertEqual(cm.exception.details(), message)

if __name__ == "__main__":
    # Run tests with verbose output
    unittest.main(verbosity=2)
```