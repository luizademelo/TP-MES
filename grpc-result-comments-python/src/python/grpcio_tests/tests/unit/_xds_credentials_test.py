Here's the commented version of the code:

```python
# Copyright 2021 The gRPC authors.
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
"""Tests xDS server and channel credentials."""

from concurrent import futures
import contextlib
import logging
import unittest

import grpc
import grpc.experimental

from tests.unit import resources
from tests.unit import test_common

# Constants for service configuration
_SERVICE_NAME = "test"  # Name of the test service
_METHOD = "method"      # Name of the test method

# Method handler that simply echoes back the request
_METHOD_HANDLERS = {
    _METHOD: grpc.unary_unary_rpc_method_handler(
        lambda request, unused_context: request
    )
}

@contextlib.contextmanager
def xds_channel_server_without_xds(server_fallback_creds):
    """Context manager that creates and manages an xDS server without xDS configuration.
    
    Args:
        server_fallback_creds: Fallback credentials to use when xDS is not available.
    
    Yields:
        str: The server address (host:port) where the server is listening.
    """
    # Create a gRPC server with thread pool executor
    server = grpc.server(futures.ThreadPoolExecutor())
    # Register method handlers for our test service
    server.add_registered_method_handlers(_SERVICE_NAME, _METHOD_HANDLERS)
    # Create SSL server credentials for fallback scenario
    server_server_fallback_creds = grpc.ssl_server_credentials(
        ((resources.private_key(), resources.certificate_chain()),)
    )
    # Create xDS server credentials with the provided fallback
    server_creds = grpc.xds_server_credentials(server_fallback_creds)
    # Add secure port to the server and get the assigned port
    port = server.add_secure_port("localhost:0", server_creds)
    server.start()
    try:
        # Yield the server address to the caller
        yield "localhost:{}".format(port)
    finally:
        # Ensure server is stopped when context exits
        server.stop(None)

class XdsCredentialsTest(unittest.TestCase):
    """Test case for xDS server and channel credentials functionality."""

    def test_xds_creds_fallback_ssl(self):
        """Test xDS credentials with SSL fallback credentials."""
        # Create SSL server credentials for fallback
        server_fallback_creds = grpc.ssl_server_credentials(
            ((resources.private_key(), resources.certificate_chain()),)
        )
        # Create server with SSL fallback
        with xds_channel_server_without_xds(
            server_fallback_creds
        ) as server_address:
            # Configure channel options for SSL
            override_options = (
                ("grpc.ssl_target_name_override", "foo.test.google.fr"),
            )
            # Create SSL channel credentials for fallback
            channel_fallback_creds = grpc.ssl_channel_credentials(
                root_certificates=resources.test_root_certificates(),
                private_key=resources.private_key(),
                certificate_chain=resources.certificate_chain(),
            )
            # Create xDS channel credentials with SSL fallback
            channel_creds = grpc.xds_channel_credentials(channel_fallback_creds)
            # Create secure channel and test communication
            with grpc.secure_channel(
                server_address, channel_creds, options=override_options
            ) as channel:
                request = b"abc"
                # Make unary RPC call and verify response matches request
                response = channel.unary_unary(
                    grpc._common.fully_qualified_method(_SERVICE_NAME, _METHOD),
                    _registered_method=True,
                )(request, wait_for_ready=True)
                self.assertEqual(response, request)

    def test_xds_creds_fallback_insecure(self):
        """Test xDS credentials with insecure fallback credentials."""
        # Create insecure server credentials for fallback
        server_fallback_creds = grpc.insecure_server_credentials()
        # Create server with insecure fallback
        with xds_channel_server_without_xds(
            server_fallback_creds
        ) as server_address:
            # Create insecure channel credentials for fallback
            channel_fallback_creds = (
                grpc.experimental.insecure_channel_credentials()
            )
            # Create xDS channel credentials with insecure fallback
            channel_creds = grpc.xds_channel_credentials(channel_fallback_creds)
            # Create secure channel and test communication
            with grpc.secure_channel(server_address, channel_creds) as channel:
                request = b"abc"
                # Make unary RPC call and verify response matches request
                response = channel.unary_unary(
                    "/test/method",
                    _registered_method=True,
                )(request, wait_for_ready=True)
                self.assertEqual(response, request)

    def test_start_xds_server(self):
        """Test basic xDS server startup and shutdown."""
        # Create gRPC server with xDS enabled
        server = grpc.server(futures.ThreadPoolExecutor(), xds=True)
        # Register method handlers for our test service
        server.add_registered_method_handlers(_SERVICE_NAME, _METHOD_HANDLERS)
        # Create insecure server credentials for fallback
        server_fallback_creds = grpc.insecure_server_credentials()
        # Create xDS server credentials with insecure fallback
        server_creds = grpc.xds_server_credentials(server_fallback_creds)
        # Add secure port and start server
        port = server.add_secure_port("localhost:0", server_creds)
        server.start()
        # Immediately stop server (just testing startup)
        server.stop(None)

if __name__ == "__main__":
    # Configure basic logging and run tests
    logging.basicConfig()
    unittest.main()
```