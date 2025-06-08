Here's the commented version of the code:

```python
# Copyright 2018 gRPC authors.
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
"""Tests server context abort mechanism"""

import collections
import gc
import logging
import unittest
import weakref

import grpc

from tests.unit import test_common
from tests.unit.framework.common import test_constants

# Constants for service and method names
_SERVICE_NAME = "test"
_ABORT = "abort"
_ABORT_WITH_STATUS = "AbortWithStatus"
_INVALID_CODE = "InvalidCode"

# Test request and response messages
_REQUEST = b"\x00\x00\x00"
_RESPONSE = b"\x00\x00\x00"

# Constants for abort details and metadata
_ABORT_DETAILS = "Abandon ship!"
_ABORT_METADATA = (("a-trailing-metadata", "42"),)

# Custom Status class that inherits from both namedtuple and grpc.Status
class _Status(
    collections.namedtuple("_Status", ("code", "details", "trailing_metadata")),
    grpc.Status,
):
    pass

# Simple object class for leak testing
class _Object(object):
    pass

# Global object for leak testing
do_not_leak_me = _Object()

# Handler for abort unary-unary RPC
def abort_unary_unary(request, servicer_context):
    # Local variable to test for memory leaks
    this_should_not_be_leaked = do_not_leak_me
    # Abort the RPC with INTERNAL status code and details
    servicer_context.abort(
        grpc.StatusCode.INTERNAL,
        _ABORT_DETAILS,
    )
    # This line should never be reached as abort terminates the RPC
    raise Exception("This line should not be executed!")

# Handler for abort_with_status unary-unary RPC
def abort_with_status_unary_unary(request, servicer_context):
    # Abort the RPC with custom status object containing code, details and metadata
    servicer_context.abort_with_status(
        _Status(
            code=grpc.StatusCode.INTERNAL,
            details=_ABORT_DETAILS,
            trailing_metadata=_ABORT_METADATA,
        )
    )
    # This line should never be reached as abort terminates the RPC
    raise Exception("This line should not be executed!")

# Handler for invalid code unary-unary RPC
def invalid_code_unary_unary(request, servicer_context):
    # Attempt to abort with invalid status code (42)
    servicer_context.abort(
        42,
        _ABORT_DETAILS,
    )

# Dictionary mapping method names to their respective handlers
RPC_METHOD_HANDLERS = {
    _ABORT: grpc.unary_unary_rpc_method_handler(abort_unary_unary),
    _ABORT_WITH_STATUS: grpc.unary_unary_rpc_method_handler(
        abort_with_status_unary_unary
    ),
    _INVALID_CODE: grpc.stream_stream_rpc_method_handler(
        invalid_code_unary_unary
    ),
}

# Main test class for abort functionality
class AbortTest(unittest.TestCase):
    def setUp(self):
        """Set up test server and channel before each test"""
        # Create test server
        self._server = test_common.test_server()
        # Add insecure port and start server
        port = self._server.add_insecure_port("[::]:0")
        # Register method handlers
        self._server.add_registered_method_handlers(
            _SERVICE_NAME, RPC_METHOD_HANDLERS
        )
        self._server.start()

        # Create insecure channel to the server
        self._channel = grpc.insecure_channel("localhost:%d" % port)

    def tearDown(self):
        """Clean up after each test"""
        self._channel.close()
        self._server.stop(0)

    def test_abort(self):
        """Test basic abort functionality"""
        with self.assertRaises(grpc.RpcError) as exception_context:
            # Make unary-unary RPC that will abort
            self._channel.unary_unary(
                grpc._common.fully_qualified_method(_SERVICE_NAME, _ABORT),
                _registered_method=True,
            )(_REQUEST)
        rpc_error = exception_context.exception

        # Verify error code and details match expected values
        self.assertEqual(rpc_error.code(), grpc.StatusCode.INTERNAL)
        self.assertEqual(rpc_error.details(), _ABORT_DETAILS)

    @unittest.skip("https://github.com/grpc/grpc/issues/17927")
    def test_abort_does_not_leak_local_vars(self):
        """Test that local variables are properly cleaned up after abort"""
        global do_not_leak_me
        # Create weak reference to test object
        weak_ref = weakref.ref(do_not_leak_me)

        with self.assertRaises(grpc.RpcError):
            # Make RPC that will abort
            self._channel.unary_unary(
                grpc._common.fully_qualified_method(_SERVICE_NAME, _ABORT),
                _registered_method=True,
            )(_REQUEST)

        # Stop server and clean up
        self._server.stop(None)
        do_not_leak_me = None
        # Verify object was properly garbage collected
        self.assertIsNone(weak_ref())

    def test_abort_with_status(self):
        """Test abort_with_status functionality with metadata"""
        with self.assertRaises(grpc.RpcError) as exception_context:
            # Make unary-unary RPC that will abort with status
            self._channel.unary_unary(
                grpc._common.fully_qualified_method(
                    _SERVICE_NAME, _ABORT_WITH_STATUS
                ),
                _registered_method=True,
            )(_REQUEST)
        rpc_error = exception_context.exception

        # Verify error code, details and metadata match expected values
        self.assertEqual(rpc_error.code(), grpc.StatusCode.INTERNAL)
        self.assertEqual(rpc_error.details(), _ABORT_DETAILS)
        self.assertEqual(rpc_error.trailing_metadata(), _ABORT_METADATA)

    def test_invalid_code(self):
        """Test behavior with invalid status code"""
        with self.assertRaises(grpc.RpcError) as exception_context:
            # Make unary-unary RPC that will abort with invalid code
            self._channel.unary_unary(
                grpc._common.fully_qualified_method(
                    _SERVICE_NAME, _INVALID_CODE
                ),
                _registered_method=True,
            )(_REQUEST)
        rpc_error = exception_context.exception

        # Verify invalid code is converted to UNKNOWN status
        self.assertEqual(rpc_error.code(), grpc.StatusCode.UNKNOWN)
        self.assertEqual(rpc_error.details(), _ABORT_DETAILS)

if __name__ == "__main__":
    # Configure logging and run tests with verbose output
    logging.basicConfig()
    unittest.main(verbosity=2)
```