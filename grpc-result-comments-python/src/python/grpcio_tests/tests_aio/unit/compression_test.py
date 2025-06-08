Here's the commented version of the code:

```python
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Tests behavior around the compression mechanism."""

import asyncio
import logging
import platform
import random
import unittest

import grpc
from grpc.experimental import aio

from tests_aio.unit import _common
from tests_aio.unit._test_base import AioTestBase

# Channel arguments for compression configuration:
# - GZIP compression algorithm (value 2 corresponds to GZIP)
_GZIP_CHANNEL_ARGUMENT = ("grpc.default_compression_algorithm", 2)
# - Disable GZIP compression (bitset value 3 means GZIP is disabled)
_GZIP_DISABLED_CHANNEL_ARGUMENT = (
    "grpc.compression_enabled_algorithms_bitset",
    3,
)
# - Disable DEFLATE compression (bitset value 5 means DEFLATE is disabled)
_DEFLATE_DISABLED_CHANNEL_ARGUMENT = (
    "grpc.compression_enabled_algorithms_bitset",
    5,
)

# Test RPC method names
_TEST_UNARY_UNARY = "/test/TestUnaryUnary"
_TEST_SET_COMPRESSION = "/test/TestSetCompression"
_TEST_DISABLE_COMPRESSION_UNARY = "/test/TestDisableCompressionUnary"
_TEST_DISABLE_COMPRESSION_STREAM = "/test/TestDisableCompressionStream"

# Test request and response data (100 bytes each)
_REQUEST = b"\x01" * 100
_RESPONSE = b"\x02" * 100

async def _test_unary_unary(unused_request, unused_context):
    """Simple unary-unary RPC handler that returns a fixed response."""
    return _RESPONSE

async def _test_set_compression(unused_request_iterator, context):
    """Stream-stream RPC handler that tests compression setting functionality.
    
    Verifies that:
    1. The received request matches expected data
    2. Compression can be set for the response
    3. Attempting to set compression again raises RuntimeError
    """
    assert _REQUEST == await context.read()
    context.set_compression(grpc.Compression.Deflate)
    await context.write(_RESPONSE)
    try:
        context.set_compression(grpc.Compression.Deflate)
    except RuntimeError:
        # Expected behavior - compression can't be set multiple times
        pass
    else:
        raise ValueError(
            "Expecting exceptions if set_compression is not effective"
        )

async def _test_disable_compression_unary(request, context):
    """Unary-unary RPC handler that tests disabling compression for next message.
    
    Sets compression but then disables it for the response.
    """
    assert _REQUEST == request
    context.set_compression(grpc.Compression.Deflate)
    context.disable_next_message_compression()
    return _RESPONSE

async def _test_disable_compression_stream(unused_request_iterator, context):
    """Stream-stream RPC handler that tests compression disabling during streaming.
    
    Tests:
    1. Setting compression for first message
    2. Disabling compression for next message
    3. Subsequent messages maintain their compression state
    """
    assert _REQUEST == await context.read()
    context.set_compression(grpc.Compression.Deflate)
    await context.write(_RESPONSE)
    context.disable_next_message_compression()
    await context.write(_RESPONSE)
    await context.write(_RESPONSE)

# Routing table mapping RPC methods to their handlers
_ROUTING_TABLE = {
    _TEST_UNARY_UNARY: grpc.unary_unary_rpc_method_handler(_test_unary_unary),
    _TEST_SET_COMPRESSION: grpc.stream_stream_rpc_method_handler(
        _test_set_compression
    ),
    _TEST_DISABLE_COMPRESSION_UNARY: grpc.unary_unary_rpc_method_handler(
        _test_disable_compression_unary
    ),
    _TEST_DISABLE_COMPRESSION_STREAM: grpc.stream_stream_rpc_method_handler(
        _test_disable_compression_stream
    ),
}

class _GenericHandler(grpc.GenericRpcHandler):
    """Generic RPC handler that routes requests based on method name."""
    def service(self, handler_call_details):
        return _ROUTING_TABLE.get(handler_call_details.method)

async def _start_test_server(options=None):
    """Starts a test server with the given options.
    
    Returns:
        Tuple of (server address, server instance)
    """
    server = aio.server(options=options)
    port = server.add_insecure_port("[::]:0")
    server.add_generic_rpc_handlers((_GenericHandler(),))
    await server.start()
    return f"localhost:{port}", server

class TestCompression(AioTestBase):
    """Test case for gRPC compression functionality."""
    
    async def setUp(self):
        """Set up test environment with server and channel."""
        # Start server with GZIP compression disabled
        server_options = (_GZIP_DISABLED_CHANNEL_ARGUMENT,)
        self._address, self._server = await _start_test_server(server_options)
        self._channel = aio.insecure_channel(self._address)

    async def tearDown(self):
        """Clean up test environment."""
        await self._channel.close()
        await self._server.stop(None)

    async def test_channel_level_compression_baned_compression(self):
        """Test that banned compression (GZIP) at channel level raises error."""
        async with aio.insecure_channel(
            self._address, compression=grpc.Compression.Gzip
        ) as channel:
            multicallable = channel.unary_unary(_TEST_UNARY_UNARY)
            call = multicallable(_REQUEST)
            with self.assertRaises(aio.AioRpcError) as exception_context:
                await call
            rpc_error = exception_context.exception
            self.assertEqual(grpc.StatusCode.UNIMPLEMENTED, rpc_error.code())

    async def test_channel_level_compression_allowed_compression(self):
        """Test that allowed compression (DEFLATE) at channel level works."""
        async with aio.insecure_channel(
            self._address, compression=grpc.Compression.Deflate
        ) as channel:
            multicallable = channel.unary_unary(_TEST_UNARY_UNARY)
            call = multicallable(_REQUEST)
            self.assertEqual(grpc.StatusCode.OK, await call.code())

    async def test_client_call_level_compression_baned_compression(self):
        """Test that banned compression (GZIP) at call level raises error."""
        multicallable = self._channel.unary_unary(_TEST_UNARY_UNARY)

        call = multicallable(_REQUEST, compression=grpc.Compression.Gzip)
        with self.assertRaises(aio.AioRpcError) as exception_context:
            await call
        rpc_error = exception_context.exception
        self.assertEqual(grpc.StatusCode.UNIMPLEMENTED, rpc_error.code())

    async def test_client_call_level_compression_allowed_compression(self):
        """Test that allowed compression (DEFLATE) at call level works."""
        multicallable = self._channel.unary_unary(_TEST_UNARY_UNARY)

        call = multicallable(_REQUEST, compression=grpc.Compression.Deflate)
        self.assertEqual(grpc.StatusCode.OK, await call.code())

    async def test_server_call_level_compression(self):
        """Test server-side compression setting during streaming RPC."""
        multicallable = self._channel.stream_stream(_TEST_SET_COMPRESSION)
        call = multicallable()
        await call.write(_REQUEST)
        await call.done_writing()
        self.assertEqual(_RESPONSE, await call.read())
        self.assertEqual(grpc.StatusCode.OK, await call.code())

    async def test_server_disable_compression_unary(self):
        """Test disabling compression for unary response."""
        multicallable = self._channel.unary_unary(
            _TEST_DISABLE_COMPRESSION_UNARY
        )
        call = multicallable(_REQUEST)
        self.assertEqual(_RESPONSE, await call)
        self.assertEqual(grpc.StatusCode.OK, await call.code())

    async def test_server_disable_compression_stream(self):
        """Test disabling compression during streaming response."""
        multicallable = self._channel.stream_stream(
            _TEST_DISABLE_COMPRESSION_STREAM
        )
        call = multicallable()
        await call.write(_REQUEST)
        await call.done_writing()
        self.assertEqual(_RESPONSE, await call.read())
        self.assertEqual(_RESPONSE, await call.read())
        self.assertEqual(_RESPONSE, await call.read())
        self.assertEqual(grpc.StatusCode.OK, await call.code())

    async def test_server_default_compression_algorithm(self):
        """Test server with default compression algorithm (DEFLATE)."""
        server = aio.server(compression=grpc.Compression.Deflate)
        port = server.add_insecure_port("[::]:0")
        server.add_generic_rpc_handlers((_GenericHandler(),))
        await server.start()

        async with aio.insecure_channel(f"localhost:{port}") as channel:
            multicallable = channel.unary_unary(_TEST_UNARY_UNARY)
            call = multicallable(_REQUEST)
            self.assertEqual(_RESPONSE, await call)
            self.assertEqual(grpc.StatusCode.OK, await call.code())

        await server.stop(None)

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    unittest.main(verbosity=2)
```

Key improvements made:
1. Added detailed docstrings for all functions and classes
2. Added comments explaining the purpose of constants and configuration values
3. Explained the test cases and what they verify
4. Added comments about expected behavior in error cases
5. Documented the routing mechanism and server setup
6. Explained the compression configuration options
7. Added comments about the test data and its purpose

The comments are focused on explaining the why behind the code rather than just what it does, which is more helpful for maintenance and future development.