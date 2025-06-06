# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Tests experimental TLS Session Resumption API"""

import logging
import pickle
import unittest

import grpc
from grpc import _channel
from grpc.experimental import session_cache

from tests.unit import resources
from tests.unit import test_common

_REQUEST = b"\x00\x00\x00"
_RESPONSE = b"\x00\x00\x00"

_SERVICE_NAME = "test"
_UNARY_UNARY = "UnaryUnary"

_SERVER_HOST_OVERRIDE = "foo.test.google.fr"
_ID = "id"
_ID_KEY = "id_key"
_AUTH_CTX = "auth_ctx"

_PRIVATE_KEY = resources.private_key()
_CERTIFICATE_CHAIN = resources.certificate_chain()
_TEST_ROOT_CERTIFICATES = resources.test_root_certificates()
_SERVER_CERTS = ((_PRIVATE_KEY, _CERTIFICATE_CHAIN),)
_PROPERTY_OPTIONS = (
    (
        "grpc.ssl_target_name_override",
        _SERVER_HOST_OVERRIDE,
    ),
)

def handle_unary_unary(request, servicer_context):
    return pickle.dumps(
        {
            _ID: servicer_context.peer_identities(),
            _ID_KEY: servicer_context.peer_identity_key(),
            _AUTH_CTX: servicer_context.auth_context(),
        }
    )

_METHOD_HANDLERS = {
    _UNARY_UNARY: grpc.unary_unary_rpc_method_handler(handle_unary_unary)
}

def start_secure_server():
    server = test_common.test_server()
    server.add_registered_method_handlers(_SERVICE_NAME, _METHOD_HANDLERS)
    server_cred = grpc.ssl_server_credentials(_SERVER_CERTS)
    port = server.add_secure_port("[::]:0", server_cred)
    server.start()

    return server, port

class SSLSessionCacheTest(unittest.TestCase):
    def _do_one_shot_client_rpc(
        self, channel_creds, channel_options, port, expect_ssl_session_reused
    ):
        channel = grpc.secure_channel(
            "localhost:{}".format(port), channel_creds, options=channel_options
        )
        response = channel.unary_unary(
            grpc._common.fully_qualified_method(_SERVICE_NAME, _UNARY_UNARY),
            _registered_method=True,
        )(_REQUEST)
        auth_data = pickle.loads(response)
        self.assertEqual(
            expect_ssl_session_reused,
            auth_data[_AUTH_CTX]["ssl_session_reused"],
        )
        channel.close()

    def testSSLSessionCacheLRU(self):
        server_1, port_1 = start_secure_server()

        cache = session_cache.ssl_session_cache_lru(1)
        channel_creds = grpc.ssl_channel_credentials(
            root_certificates=_TEST_ROOT_CERTIFICATES
        )
        channel_options = _PROPERTY_OPTIONS + (
            ("grpc.ssl_session_cache", cache),
        )

        self._do_one_shot_client_rpc(
            channel_creds,
            channel_options,
            port_1,
            expect_ssl_session_reused=[b"false"],
        )

        self._do_one_shot_client_rpc(
            channel_creds,
            channel_options,
            port_1,
            expect_ssl_session_reused=[b"true"],
        )

        server_2, port_2 = start_secure_server()
        self._do_one_shot_client_rpc(
            channel_creds,
            channel_options,
            port_2,
            expect_ssl_session_reused=[b"false"],
        )
        self._do_one_shot_client_rpc(
            channel_creds,
            channel_options,
            port_2,
            expect_ssl_session_reused=[b"true"],
        )
        server_2.stop(None)

        self._do_one_shot_client_rpc(
            channel_creds,
            channel_options,
            port_1,
            expect_ssl_session_reused=[b"false"],
        )

        server_1.stop(None)
        server_1, port_1 = start_secure_server()

        self._do_one_shot_client_rpc(
            channel_creds,
            channel_options,
            port_1,
            expect_ssl_session_reused=[b"false"],
        )

        self._do_one_shot_client_rpc(
            channel_creds,
            channel_options,
            port_1,
            expect_ssl_session_reused=[b"true"],
        )
        server_1.stop(None)

if __name__ == "__main__":
    logging.basicConfig()
    unittest.main(verbosity=2)
