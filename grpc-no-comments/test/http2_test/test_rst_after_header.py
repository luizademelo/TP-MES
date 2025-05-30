# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import http2_base_server

class TestcaseRstStreamAfterHeader(object):
    """
    In response to an incoming request, this test sends headers, followed by
    a reset stream frame. Client asserts that the RPC failed.
    """

    def __init__(self):
        self._base_server = http2_base_server.H2ProtocolBaseServer()
        self._base_server._handlers[
            "RequestReceived"
        ] = self.on_request_received

    def get_base_server(self):
        return self._base_server

    def on_request_received(self, event):

        self._base_server.on_request_received_default(event)

        self._base_server.send_reset_stream()
