Here's the commented version of the code:

```c++
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import logging

import http2_base_server

class TestcasePing(object):
    """
    This test injects PING frames before and after header and data. Keeps count
    of outstanding ping response and asserts when the count is non-zero at the
    end of the test.
    """

    def __init__(self):
        """Initialize the test case with base HTTP/2 server and set up event handlers."""
        # Initialize base HTTP/2 server
        self._base_server = http2_base_server.H2ProtocolBaseServer()
        # Set up event handlers for different HTTP/2 events
        self._base_server._handlers[
            "RequestReceived"
        ] = self.on_request_received
        self._base_server._handlers["DataReceived"] = self.on_data_received
        self._base_server._handlers["ConnectionLost"] = self.on_connection_lost

    def get_base_server(self):
        """Get the base HTTP/2 server instance.
        
        Returns:
            The base HTTP/2 server instance being used for testing.
        """
        return self._base_server

    def on_request_received(self, event):
        """Handler for when a request is received.
        
        Args:
            event: The HTTP/2 request received event.
        """
        # Send PING frame before processing request
        self._base_server.default_ping()
        # Process request using default handler
        self._base_server.on_request_received_default(event)
        # Send PING frame after processing request
        self._base_server.default_ping()

    def on_data_received(self, event):
        """Handler for when data is received.
        
        Args:
            event: The HTTP/2 data received event.
        """
        # Process data using default handler
        self._base_server.on_data_received_default(event)
        # Parse received data and get server response details
        sr = self._base_server.parse_received_data(event.stream_id)
        if sr:
            logging.info("Creating response size = %s" % sr.response_size)
            # Generate default response data
            response_data = self._base_server.default_response_data(
                sr.response_size
            )
            # Send PING frame before sending response
            self._base_server.default_ping()
            # Setup and send the response
            self._base_server.setup_send(response_data, event.stream_id)
            # Send PING frame after sending response
            self._base_server.default_ping()

    def on_connection_lost(self, reason):
        """Handler for when connection is lost.
        
        Args:
            reason: The reason for connection loss.
        
        Raises:
            AssertionError: If there are outstanding PING responses when connection is lost.
        """
        logging.info(
            "Disconnect received. Ping Count %d"
            % self._base_server._outstanding_pings
        )
        # Verify all PINGs have been acknowledged
        assert self._base_server._outstanding_pings == 0
        # Process connection loss using default handler
        self._base_server.on_connection_lost(reason)
```