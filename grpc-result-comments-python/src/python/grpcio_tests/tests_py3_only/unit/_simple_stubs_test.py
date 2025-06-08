Here's the commented version of the code:

```python
# Copyright 2020 The gRPC authors.
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
"""Tests for Simple Stubs."""

import os

# Maximum number of channels allowed in the channel cache
_MAXIMUM_CHANNELS = 10

# Default timeout value for RPC calls (in seconds)
_DEFAULT_TIMEOUT = 1.0

# Set environment variables for gRPC configuration
os.environ["GRPC_PYTHON_MANAGED_CHANNEL_EVICTION_SECONDS"] = "2"  # Channel eviction time
os.environ["GRPC_PYTHON_MANAGED_CHANNEL_MAXIMUM"] = str(_MAXIMUM_CHANNELS)  # Max channels
os.environ["GRPC_PYTHON_DEFAULT_TIMEOUT_SECONDS"] = str(_DEFAULT_TIMEOUT)  # Default timeout

import contextlib
import datetime
import inspect
import logging
import sys
import threading
import time
from typing import Callable, Optional
import unittest

import grpc
import grpc.experimental

from tests.unit import resources
from tests.unit import test_common
from tests.unit.framework.common import get_socket

# Constants for test requests/responses
_REQUEST = b"0000"  # Test request payload

# Constants for cache testing
_CACHE_EPOCHS = 8    # Number of cache test iterations
_CACHE_TRIALS = 6    # Number of trials per cache test

# Constants for request/response counts
_SERVER_RESPONSE_COUNT = 10  # Number of responses for streaming tests
_CLIENT_REQUEST_COUNT = _SERVER_RESPONSE_COUNT  # Matching request count

# Stress test iterations
_STRESS_EPOCHS = _MAXIMUM_CHANNELS * 10

# RPC method names for testing
_UNARY_UNARY = "/test/UnaryUnary"     # Unary request, unary response
_UNARY_STREAM = "/test/UnaryStream"   # Unary request, stream response
_STREAM_UNARY = "/test/StreamUnary"   # Stream request, unary response
_STREAM_STREAM = "/test/StreamStream" # Stream request, stream response
_BLACK_HOLE = "/test/BlackHole"       # Method that never completes

@contextlib.contextmanager
def _env(key: str, value: str):
    """Context manager for temporarily setting environment variables.
    
    Args:
        key: Environment variable name
        value: Value to set
    """
    os.environ[key] = value
    grpc._cython.cygrpc.reset_grpc_config_vars()  # Reset gRPC config
    yield
    del os.environ[key]  # Clean up

# Handler functions for different RPC types
def _unary_unary_handler(request, context):
    """Simple unary-unary handler that echoes the request."""
    return request

def _unary_stream_handler(request, context):
    """Unary-stream handler that streams the request multiple times."""
    for _ in range(_SERVER_RESPONSE_COUNT):
        yield request

def _stream_unary_handler(request_iterator, context):
    """Stream-unary handler that returns the last received request."""
    request = None
    for single_request in request_iterator:
        request = single_request
    return request

def _stream_stream_handler(request_iterator, context):
    """Stream-stream handler that echoes each request."""
    for request in request_iterator:
        yield request

def _black_hole_handler(request, context):
    """Handler that never completes until the RPC is cancelled."""
    event = threading.Event()

    def _on_done():
        """Callback when RPC is done."""
        event.set()

    context.add_callback(_on_done)
    while not event.is_set():
        time.sleep(0.1)

class _GenericHandler(grpc.GenericRpcHandler):
    """Generic handler that routes requests to appropriate handlers."""
    def service(self, handler_call_details):
        """Routes incoming RPCs to the appropriate handler."""
        if handler_call_details.method == _UNARY_UNARY:
            return grpc.unary_unary_rpc_method_handler(_unary_unary_handler)
        elif handler_call_details.method == _UNARY_STREAM:
            return grpc.unary_stream_rpc_method_handler(_unary_stream_handler)
        elif handler_call_details.method == _STREAM_UNARY:
            return grpc.stream_unary_rpc_method_handler(_stream_unary_handler)
        elif handler_call_details.method == _STREAM_STREAM:
            return grpc.stream_stream_rpc_method_handler(_stream_stream_handler)
        elif handler_call_details.method == _BLACK_HOLE:
            return grpc.unary_unary_rpc_method_handler(_black_hole_handler)
        else:
            raise NotImplementedError()

def _time_invocation(to_time: Callable[[], None]) -> datetime.timedelta:
    """Times the execution of a function.
    
    Args:
        to_time: Function to time
        
    Returns:
        Time taken to execute the function
    """
    start = datetime.datetime.now()
    to_time()
    return datetime.datetime.now() - start

@contextlib.contextmanager
def _server(credentials: Optional[grpc.ServerCredentials]):
    """Context manager for creating and managing a test server.
    
    Args:
        credentials: Optional server credentials for secure connections
        
    Yields:
        The port number the server is listening on
    """
    try:
        server = test_common.test_server()
        target = "[::]:0"  # Bind to any available port
        if credentials is None:
            port = server.add_insecure_port(target)
        else:
            port = server.add_secure_port(target, credentials)
        server.add_generic_rpc_handlers((_GenericHandler(),))
        server.start()
        yield port
    finally:
        server.stop(None)  # Ensure server is stopped

class SimpleStubsTest(unittest.TestCase):
    """Test case for simple gRPC stubs functionality."""

    def assert_cached(self, to_check: Callable[[str], None]) -> None:
        """Asserts that a function caches intermediate data/state.

        Args:
            to_check: A function that caches values based on a string input.
        """
        initial_runs = []
        cached_runs = []
        for epoch in range(_CACHE_EPOCHS):
            runs = []
            text = str(epoch)
            for trial in range(_CACHE_TRIALS):
                runs.append(_time_invocation(lambda: to_check(text)))
            initial_runs.append(runs[0])
            cached_runs.extend(runs[1:])
        average_cold = sum(
            (run for run in initial_runs), datetime.timedelta()
        ) / len(initial_runs)
        average_warm = sum(
            (run for run in cached_runs), datetime.timedelta()
        ) / len(cached_runs)
        self.assertLess(average_warm, average_cold)

    def assert_eventually(
        self,
        predicate: Callable[[], bool],
        *,
        timeout: Optional[datetime.timedelta] = None,
        message: Optional[Callable[[], str]] = None,
    ) -> None:
        """Asserts that a condition eventually becomes true.
        
        Args:
            predicate: Condition to check
            timeout: Maximum time to wait
            message: Optional failure message generator
        """
        message = message or (lambda: "Proposition did not evaluate to true")
        timeout = timeout or datetime.timedelta(seconds=10)
        end = datetime.datetime.now() + timeout
        while datetime.datetime.now() < end:
            if predicate():
                break
            time.sleep(0.5)
        else:
            self.fail(message() + " after " + str(timeout))

    def test_unary_unary_insecure(self):
        """Tests basic unary-unary RPC with insecure channel."""
        with _server(None) as port:
            target = f"localhost:{port}"
            response = grpc.experimental.unary_unary(
                _REQUEST,
                target,
                _UNARY_UNARY,
                channel_credentials=grpc.experimental.insecure_channel_credentials(),
                timeout=None,
                _registered_method=0,
            )
            self.assertEqual(_REQUEST, response)

    def test_unary_unary_secure(self):
        """Tests basic unary-unary RPC with secure channel."""
        with _server(grpc.local_server_credentials()) as port:
            target = f"localhost:{port}"
            response = grpc.experimental.unary_unary(
                _REQUEST,
                target,
                _UNARY_UNARY,
                channel_credentials=grpc.local_channel_credentials(),
                timeout=None,
                _registered_method=0,
            )
            self.assertEqual(_REQUEST, response)

    def test_channels_cached(self):
        """Tests that channels are properly cached."""
        with _server(grpc.local_server_credentials()) as port:
            target = f"localhost:{port}"
            test_name = inspect.stack()[0][3]
            args = (_REQUEST, target, _UNARY_UNARY)
            kwargs = {
                "channel_credentials": grpc.local_channel_credentials(),
                "_registered_method": True,
            }

            def _invoke(seed: str):
                """Invokes RPC with test-specific options."""
                run_kwargs = dict(kwargs)
                run_kwargs["options"] = ((test_name + seed, ""),)
                grpc.experimental.unary_unary(*args, **run_kwargs)

            self.assert_cached(_invoke)

    def test_channels_evicted(self):
        """Tests that unused channels are eventually evicted."""
        with _server(grpc.local_server_credentials()) as port:
            target = f"localhost:{port}"
            response = grpc.experimental.unary_unary(
                _REQUEST,
                target,
                _UNARY_UNARY,
                channel_credentials=grpc.local_channel_credentials(),
                _registered_method=0,
            )
            self.assert_eventually(
                lambda: grpc._simple_stubs.ChannelCache.get()._test_only_channel_count()
                == 0,
                message=lambda: f"{grpc._simple_stubs.ChannelCache.get()._test_only_channel_count()} remain",
            )

    def test_total_channels_enforced(self):
        """Tests that the maximum channel limit is enforced."""
        with _server(grpc.local_server_credentials()) as port:
            target = f"localhost:{port}"
            for i in range(_STRESS_EPOCHS):
                options = (("foo", str(i)),)

                grpc.experimental.unary_unary(
                    _REQUEST,
                    target,
                    _UNARY_UNARY,
                    options=options,
                    channel_credentials=grpc.local_channel_credentials(),
                    _registered_method=0,
                )
                self.assert_eventually(
                    lambda: grpc._simple_stubs.ChannelCache.get()._test_only_channel_count()
                    <= _MAXIMUM_CHANNELS + 1,
                    message=lambda: f"{grpc._simple_stubs.ChannelCache.get()._test_only_channel_count()} channels remain",
                )

    def test_unary_stream(self):
        """Tests unary-stream RPC."""
        with _server(grpc.local_server_credentials()) as port:
            target = f"localhost:{port}"
            for response in grpc.experimental.unary_stream(
                _REQUEST,
                target,
                _UNARY_STREAM,
                channel_credentials=grpc.local_channel_credentials(),
                _registered_method=0,
            ):
                self.assertEqual(_REQUEST, response)

    def test_stream_unary(self):
        """Tests stream-unary RPC."""
        def request_iter():
            """Generates test requests."""
            for _ in range(_CLIENT_REQUEST_COUNT):
                yield _REQUEST

        with _server(grpc.local_server_credentials()) as port:
            target = f"localhost:{port}"
            response = grpc.experimental.stream_unary(
                request_iter(),
                target,
                _STREAM_UNARY,
                channel_credentials=grpc.local_channel_credentials(),
                _registered_method=0,
            )
            self.assertEqual(_REQUEST, response)

    def test_stream_stream(self):
        """Tests stream-stream RPC."""
        def request_iter():
            """Generates test requests."""
            for _ in range(_CLIENT_REQUEST_COUNT):
                yield _REQUEST

        with _server(grpc.local_server_credentials()) as port:
            target = f"localhost:{port}"
            for response in grpc.experimental.stream_stream(
                request_iter(),
                target,
                _STREAM_STREAM,
                channel_credentials=grpc.local_channel_credentials(),
                _registered_method=0,
            ):
                self.assertEqual(_REQUEST, response)

    def test_default_ssl(self):
        """Tests SSL/TLS configuration with default roots."""
        _private_key = resources.private_key()
        _certificate_chain = resources.certificate_chain()
        _server_certs = ((_private_key, _certificate_chain),)
        _server_host_override = "foo.test.google.fr"
        _test_root_certificates = resources.test_root_certificates()
        _property_options = (
            (
                "grpc.ssl_target_name_override",
                _server_host_override,
            ),
        )
        cert_dir = os.path.join(
            os.path.dirname(resources.__file__), "credentials"
        )
        cert_file = os.path.join(cert_dir, "ca.pem")
        with _env("GRPC_DEFAULT_SSL_ROOTS_FILE_PATH", cert_file):
            server_creds = grpc.ssl_server_credentials(_server_certs)
            with _server(server_creds) as port:
                target = f"localhost:{port}"
                response = grpc.experimental.unary_unary(
                    _REQUEST,
                    target,
                    _UNARY_UNARY,
                    options=_property_options,
                    _registered_method=0,
                )

    def test_insecure_sugar(self):
        """Tests the insecure=True shorthand for insecure channels."""
        with _server(None) as port:
            target = f"localhost:{port}"
            response = grpc.experimental.unary_unary(
                _REQUEST,
                target,
                _UNARY_UNARY,
                insecure=True,
                _registered_method=0,
            )
            self.assertEqual(_REQUEST, response)

    def test_insecure_sugar_mutually_exclusive(self):
        """Tests that insecure and channel_credentials are mutually exclusive."""
        with _server(None) as port:
            target = f"localhost:{port}"
            with self.assertRaises(ValueError):
                response = grpc.experimental.unary_unary(
                    _REQUEST,
                    target,
                    _UNARY_UNARY,
                    insecure=True,
                    channel_credentials=grpc.local_channel_credentials(),
                    _registered_method=0,
                )

    def test_default_wait_for_ready(self):
        """Tests that RPCs wait for the server to become available."""
        addr, port, sock = get_socket()
        sock.close()
        target = f"{addr}:{port}"
        (
            channel,
            unused_method_handle,
        ) = grpc._simple_stubs.ChannelCache.get().get_channel(
            target=target,
            options=(),
            channel_credentials=None,
            insecure=True,
            compression=None,
            method=_UNARY_UNARY,
            _registered_method=True,
        )
        rpc_finished_event = threading.Event()
        rpc_failed_event = threading.Event()
        server = None

        def _on_connectivity_changed(connectivity):
            """Handles channel connectivity changes."""
            nonlocal server
            if connectivity is grpc.ChannelConnectivity.TRANSIENT_FAILURE:
                self.assertFalse(rpc_finished_event.is_set())
                self.assertFalse(rpc_failed_event.is_set())
                server = test_common.test_server()
                server.add_insecure_port(target)
                server.add_generic_rpc_handlers((_GenericHandler(),))
                server.start()
                channel.unsubscribe(_on_connectivity_changed)
            elif connectivity in (
                grpc.ChannelConnectivity.IDLE,
                grpc.ChannelConnectivity.CONNECTING,
            ):
                pass
            else:
                self.fail("Encountered unknown state.")

        channel.subscribe(_on_connectivity_changed)

        def _send_rpc():
            """Sends test RPC and sets completion flags."""
            try:
                response = grpc.experimental.unary_unary(
                    _REQUEST,
                    target,
                    _UNARY_UNARY,
                    timeout=None,
                    insecure=True,
                    _registered_method=0,
                )
                rpc_finished_event.set()
            except Exception as e:
                rpc_failed_event.set()

        t = threading.Thread(target=_send_rpc)
        t.start()
        t.join()
        self.assertFalse(rpc_failed_event.is_set())
        self.assertTrue(rpc_finished_event.is_set())
        if server is not None:
            server.stop(None)

    def assert_times_out(self, invocation_args):
        """Helper to assert an RPC times out with given arguments."""
        with _server(None) as port:
            target = f"localhost:{port}"
            with self.assertRaises(grpc.RpcError) as cm:
                response = grpc.experimental.unary_unary(
                    _REQUEST,
                    target,
                    _BLACK_HOLE,
                    insecure=True,
                    _registered_method=0,
                    **invocation_args,
                )
            self.assertEqual(
                grpc.StatusCode.DEADLINE_EXCEEDED, cm.exception.code()
            )

    def test_default_timeout(self):
        """Tests that default timeout values are properly applied."""
        not_present = object()
        wait_for_ready_values = [True, not_present]
        timeout_values = [0.5, not_present]
        cases = []
        for wait_for_ready in wait_for_ready_values:
            for timeout in timeout_values:
                case = {}
                if timeout is not not_present:
                    case["timeout"] = timeout
                if wait_for_ready is not not_present:
                    case["wait_for_ready"] = wait_for_ready
                cases.append(case)

        for case in cases:
            with self.subTest(**case):
                self.assert_times_out(case)

if __name__ ==