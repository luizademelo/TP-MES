Here's the commented version of the code:

```c++
# Copyright 2017 gRPC authors.
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
"""Tests server certificate rotation.

Here we test various aspects of gRPC Python, and in some cases gRPC
Core by extension, support for server certificate rotation.

* ServerSSLCertReloadTestWithClientAuth: test ability to rotate
  server's SSL cert for use in future channels with clients while not
  affecting any existing channel. The server requires client
  authentication.

* ServerSSLCertReloadTestWithoutClientAuth: like
  ServerSSLCertReloadTestWithClientAuth except that the server does
  not authenticate the client.

* ServerSSLCertReloadTestCertConfigReuse: tests gRPC Python's ability
  to deal with user's reuse of ServerCertificateConfiguration instances.
"""

import abc
import collections
from concurrent import futures
import logging
import os
import threading
import unittest

import grpc

from tests.testing import _application_common
from tests.testing import _server_application
from tests.testing.proto import services_pb2_grpc
from tests.unit import resources
from tests.unit import test_common

# Certificate resources for test hierarchy 1
CA_1_PEM = resources.cert_hier_1_root_ca_cert()
CLIENT_KEY_1_PEM = resources.cert_hier_1_client_1_key()
CLIENT_CERT_CHAIN_1_PEM = (
    resources.cert_hier_1_client_1_cert()
    + resources.cert_hier_1_intermediate_ca_cert()
)
SERVER_KEY_1_PEM = resources.cert_hier_1_server_1_key()
SERVER_CERT_CHAIN_1_PEM = (
    resources.cert_hier_1_server_1_cert()
    + resources.cert_hier_1_intermediate_ca_cert()
)

# Certificate resources for test hierarchy 2
CA_2_PEM = resources.cert_hier_2_root_ca_cert()
CLIENT_KEY_2_PEM = resources.cert_hier_2_client_1_key()
CLIENT_CERT_CHAIN_2_PEM = (
    resources.cert_hier_2_client_1_cert()
    + resources.cert_hier_2_intermediate_ca_cert()
)
SERVER_KEY_2_PEM = resources.cert_hier_2_server_1_key()
SERVER_CERT_CHAIN_2_PEM = (
    resources.cert_hier_2_server_1_cert()
    + resources.cert_hier_2_intermediate_ca_cert()
)

# Named tuple to track certificate configuration calls
Call = collections.namedtuple("Call", ["did_raise", "returned_cert_config"])

def _create_channel(port, credentials):
    """Helper function to create a secure channel."""
    return grpc.secure_channel("localhost:{}".format(port), credentials)

def _create_client_stub(channel, expect_success):
    """Helper function to create a client stub and verify channel readiness."""
    if expect_success:
        grpc.channel_ready_future(channel).result(timeout=10)
    return services_pb2_grpc.FirstServiceStub(channel)

class CertConfigFetcher(object):
    """Callback class for dynamic SSL certificate configuration.
    
    Tracks calls and allows configuration of return values/errors.
    """
    def __init__(self):
        self._lock = threading.Lock()
        self._calls = []
        self._should_raise = False
        self._cert_config = None

    def reset(self):
        """Reset the fetcher's state."""
        with self._lock:
            self._calls = []
            self._should_raise = False
            self._cert_config = None

    def configure(self, should_raise, cert_config):
        """Configure the fetcher's behavior.
        
        Args:
            should_raise: Whether to raise an error when called
            cert_config: Certificate configuration to return
        """
        assert not (should_raise and cert_config), (
            "should not specify both should_raise and a cert_config at the same"
            " time"
        )
        with self._lock:
            self._should_raise = should_raise
            self._cert_config = cert_config

    def getCalls(self):
        """Get all recorded calls."""
        with self._lock:
            return self._calls

    def __call__(self):
        """Callback implementation that returns configured cert config or error."""
        with self._lock:
            if self._should_raise:
                self._calls.append(Call(True, None))
                raise ValueError("just for fun, should not affect the test")
            else:
                self._calls.append(Call(False, self._cert_config))
                return self._cert_config

class _ServerSSLCertReloadTest(unittest.TestCase, metaclass=abc.ABCMeta):
    """Base class for server SSL certificate reload tests."""
    def __init__(self, *args, **kwargs):
        super(_ServerSSLCertReloadTest, self).__init__(*args, **kwargs)
        self.server = None
        self.port = None

    @abc.abstractmethod
    def require_client_auth(self):
        """Abstract method to determine if client auth is required."""
        raise NotImplementedError()

    def setUp(self):
        """Set up test server with initial certificate configuration."""
        self.server = test_common.test_server()
        services_pb2_grpc.add_FirstServiceServicer_to_server(
            _server_application.FirstServiceServicer(), self.server
        )
        # Initial certificate configuration uses hierarchy 1
        initial_cert_config = grpc.ssl_server_certificate_configuration(
            [(SERVER_KEY_1_PEM, SERVER_CERT_CHAIN_1_PEM)],
            root_certificates=CA_2_PEM,
        )
        self.cert_config_fetcher = CertConfigFetcher()
        server_credentials = grpc.dynamic_ssl_server_credentials(
            initial_cert_config,
            self.cert_config_fetcher,
            require_client_authentication=self.require_client_auth(),
        )
        self.port = self.server.add_secure_port("[::]:0", server_credentials)
        self.server.start()

    def tearDown(self):
        """Clean up test server."""
        if self.server:
            self.server.stop(None)

    def _perform_rpc(self, client_stub, expect_success):
        """Perform a unary RPC and verify expected outcome.
        
        Args:
            client_stub: The client stub to use
            expect_success: Whether the RPC should succeed
        """
        request = _application_common.UNARY_UNARY_REQUEST
        if expect_success:
            response = client_stub.UnUn(request)
            self.assertEqual(response, _application_common.UNARY_UNARY_RESPONSE)
        else:
            with self.assertRaises(grpc.RpcError) as exception_context:
                client_stub.UnUn(request)

            self.assertTrue(
                exception_context.exception.code()
                in [grpc.StatusCode.UNAVAILABLE, grpc.StatusCode.UNKNOWN]
            )

    def _do_one_shot_client_rpc(
        self,
        expect_success,
        root_certificates=None,
        private_key=None,
        certificate_chain=None,
    ):
        """Create a client and perform a single RPC.
        
        Args:
            expect_success: Whether the RPC should succeed
            root_certificates: Client root certificates
            private_key: Client private key
            certificate_chain: Client certificate chain
        """
        credentials = grpc.ssl_channel_credentials(
            root_certificates=root_certificates,
            private_key=private_key,
            certificate_chain=certificate_chain,
        )
        with _create_channel(self.port, credentials) as client_channel:
            client_stub = _create_client_stub(client_channel, expect_success)
            self._perform_rpc(client_stub, expect_success)

    def _test(self):
        """Main test logic for certificate rotation scenarios."""
        # Test 1: Initial configuration with hierarchy 1 certs
        self.cert_config_fetcher.configure(False, None)
        self._do_one_shot_client_rpc(
            True,
            root_certificates=CA_1_PEM,
            private_key=CLIENT_KEY_2_PEM,
            certificate_chain=CLIENT_CERT_CHAIN_2_PEM,
        )
        
        # Verify fetcher was called once with no error and no config change
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertEqual(len(actual_calls), 1)
        self.assertFalse(actual_calls[0].did_raise)
        self.assertIsNone(actual_calls[0].returned_cert_config)

        # Test 2: Attempt connection with mismatched CA (should fail)
        self.cert_config_fetcher.reset()
        self.cert_config_fetcher.configure(False, None)
        self._do_one_shot_client_rpc(
            False,
            root_certificates=CA_2_PEM,
            private_key=CLIENT_KEY_2_PEM,
            certificate_chain=CLIENT_CERT_CHAIN_2_PEM,
        )
        
        # Verify fetcher was called (multiple times due to retries)
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertGreaterEqual(len(actual_calls), 1)
        for i, call in enumerate(actual_calls):
            self.assertFalse(call.did_raise, "i= {}".format(i))
            self.assertIsNone(call.returned_cert_config, "i= {}".format(i))

        # Test 3: Simulate fetcher error
        self.cert_config_fetcher.reset()
        self.cert_config_fetcher.configure(True, None)
        self._do_one_shot_client_rpc(
            True,
            root_certificates=CA_1_PEM,
            private_key=CLIENT_KEY_2_PEM,
            certificate_chain=CLIENT_CERT_CHAIN_2_PEM,
        )
        
        # Verify error was recorded
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertEqual(len(actual_calls), 1)
        self.assertTrue(actual_calls[0].did_raise)
        self.assertIsNone(actual_calls[0].returned_cert_config)

        # Test 4: Attempt connection with different client certs
        self.cert_config_fetcher.reset()
        self.cert_config_fetcher.configure(False, None)
        self._do_one_shot_client_rpc(
            not self.require_client_auth(),
            root_certificates=CA_1_PEM,
            private_key=CLIENT_KEY_1_PEM,
            certificate_chain=CLIENT_CERT_CHAIN_1_PEM,
        )
        
        # Verify fetcher was called
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertGreaterEqual(len(actual_calls), 1)
        for i, call in enumerate(actual_calls):
            self.assertFalse(call.did_raise, "i= {}".format(i))
            self.assertIsNone(call.returned_cert_config, "i= {}".format(i))

        # Test 5: Re-test initial successful configuration
        self.cert_config_fetcher.reset()
        self.cert_config_fetcher.configure(False, None)
        self._do_one_shot_client_rpc(
            True,
            root_certificates=CA_1_PEM,
            private_key=CLIENT_KEY_2_PEM,
            certificate_chain=CLIENT_CERT_CHAIN_2_PEM,
        )
        
        # Verify single successful call
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertEqual(len(actual_calls), 1)
        self.assertFalse(actual_calls[0].did_raise)
        self.assertIsNone(actual_calls[0].returned_cert_config)

        # Test 6: Create persistent client A
        self.cert_config_fetcher.reset()
        self.cert_config_fetcher.configure(False, None)
        channel_A = _create_channel(
            self.port,
            grpc.ssl_channel_credentials(
                root_certificates=CA_1_PEM,
                private_key=CLIENT_KEY_2_PEM,
                certificate_chain=CLIENT_CERT_CHAIN_2_PEM,
            ),
        )
        persistent_client_stub_A = _create_client_stub(channel_A, True)
        self._perform_rpc(persistent_client_stub_A, True)
        
        # Verify single successful call
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertEqual(len(actual_calls), 1)
        self.assertFalse(actual_calls[0].did_raise)
        self.assertIsNone(actual_calls[0].returned_cert_config)

        # Test 7: Create persistent client B
        self.cert_config_fetcher.reset()
        self.cert_config_fetcher.configure(False, None)
        channel_B = _create_channel(
            self.port,
            grpc.ssl_channel_credentials(
                root_certificates=CA_1_PEM,
                private_key=CLIENT_KEY_2_PEM,
                certificate_chain=CLIENT_CERT_CHAIN_2_PEM,
            ),
        )
        persistent_client_stub_B = _create_client_stub(channel_B, True)
        self._perform_rpc(persistent_client_stub_B, True)
        
        # Verify single successful call
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertEqual(len(actual_calls), 1)
        self.assertFalse(actual_calls[0].did_raise)
        self.assertIsNone(actual_calls[0].returned_cert_config)

        # Test 8: Rotate to hierarchy 2 certificates
        cert_config = grpc.ssl_server_certificate_configuration(
            [(SERVER_KEY_2_PEM, SERVER_CERT_CHAIN_2_PEM)],
            root_certificates=CA_1_PEM,
        )
        self.cert_config_fetcher.reset()
        self.cert_config_fetcher.configure(False, cert_config)
        self._do_one_shot_client_rpc(
            False,
            root_certificates=CA_1_PEM,
            private_key=CLIENT_KEY_2_PEM,
            certificate_chain=CLIENT_CERT_CHAIN_2_PEM,
        )
        
        # Verify fetcher was called with new config
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertGreaterEqual(len(actual_calls), 1)
        for i, call in enumerate(actual_calls):
            self.assertFalse(call.did_raise, "i= {}".format(i))
            self.assertEqual(
                call.returned_cert_config, cert_config, "i= {}".format(i)
            )

        # Test 9: New configuration should work with hierarchy 2 CA
        self.cert_config_fetcher.reset()
        self.cert_config_fetcher.configure(False, None)
        self._do_one_shot_client_rpc(
            True,
            root_certificates=CA_2_PEM,
            private_key=CLIENT_KEY_1_PEM,
            certificate_chain=CLIENT_CERT_CHAIN_1_PEM,
        )
        
        # Verify single successful call
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertEqual(len(actual_calls), 1)
        self.assertFalse(actual_calls[0].did_raise)
        self.assertIsNone(actual_calls[0].returned_cert_config)

        # Test 10: Verify behavior with different client certs on new config
        self.cert_config_fetcher.reset()
        self.cert_config_fetcher.configure(False, None)
        self._do_one_shot_client_rpc(
            not self.require_client_auth(),
            root_certificates=CA_2_PEM,
            private_key=CLIENT_KEY_2_PEM,
            certificate_chain=CLIENT_CERT_CHAIN_2_PEM,
        )
        
        # Verify fetcher was called
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertGreaterEqual(len(actual_calls), 1)
        for i, call in enumerate(actual_calls):
            self.assertFalse(call.did_raise, "i= {}".format(i))
            self.assertIsNone(call.returned_cert_config, "i= {}".format(i))

        # Test 11: Verify old configuration no longer works
        self.cert_config_fetcher.reset()
        self.cert_config_fetcher.configure(False, None)
        self._do_one_shot_client_rpc(
            False,
            root_certificates=CA_1_PEM,
            private_key=CLIENT_KEY_2_PEM,
            certificate_chain=CLIENT_CERT_CHAIN_2_PEM,
        )
        
        # Verify fetcher was called
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertGreaterEqual(len(actual_calls), 1)
        for i, call in enumerate(actual_calls):
            self.assertFalse(call.did_raise, "i= {}".format(i))
            self.assertIsNone(call.returned_cert_config, "i= {}".format(i))

        # Test 12: Verify persistent clients still work
        self.cert_config_fetcher.reset()
        self.cert_config_fetcher.configure(False, None)
        self._perform_rpc(persistent_client_stub_A, True)
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertEqual(len(actual_calls), 0)

        self.cert_config_fetcher.reset()
        self.cert_config_fetcher.configure(False, None)
        self._perform_rpc(persistent_client_stub_B, True)
        actual_calls = self.cert_config_fetcher.getCalls()
        self.assertEqual(len(actual_calls), 0)

        # Clean up
        channel_A.close()
        channel_B.close()

class ServerSSLC