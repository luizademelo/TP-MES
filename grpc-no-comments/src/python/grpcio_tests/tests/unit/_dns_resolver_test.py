# Copyright 2019 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Tests for an actual dns resolution."""

import logging
import unittest

import grpc

from tests.unit import test_common
from tests.unit.framework.common import test_constants

_SERVICE_NAME = "test"
_METHOD = "METHOD"
_REQUEST = b"\x00\x00\x00"
_RESPONSE = _REQUEST

_METHOD_HANDLERS = {
    _METHOD: grpc.unary_unary_rpc_method_handler(
        lambda request, unused_context: request,
    )
}

class DNSResolverTest(unittest.TestCase):
    def setUp(self):
        self._server = test_common.test_server()
        self._server.add_registered_method_handlers(
            _SERVICE_NAME, _METHOD_HANDLERS
        )
        self._port = self._server.add_insecure_port("[::]:0")
        self._server.start()

    def tearDown(self):
        self._server.stop(None)

    def test_connect_loopback(self):

        with grpc.insecure_channel(
            "loopback46.unittest.grpc.io:%d" % self._port
        ) as channel:
            self.assertEqual(
                channel.unary_unary(
                    grpc._common.fully_qualified_method(_SERVICE_NAME, _METHOD),
                    _registered_method=True,
                )(
                    _REQUEST,
                    timeout=10,
                ),
                _RESPONSE,
            )

if __name__ == "__main__":
    logging.basicConfig()
    unittest.main(verbosity=2)
