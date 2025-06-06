# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Tests metadata flags feature by testing wait-for-ready semantics"""

import logging
import queue
import socket
import threading
import time
import unittest
import weakref

import grpc

from tests.unit import test_common
import tests.unit.framework.common
from tests.unit.framework.common import get_socket
from tests.unit.framework.common import test_constants

_SERVICE_NAME = "test"
_UNARY_UNARY = "UnaryUnary"
_UNARY_STREAM = "UnaryStream"
_STREAM_UNARY = "StreamUnary"
_STREAM_STREAM = "StreamStream"

_REQUEST = b"\x00\x00\x00"
_RESPONSE = b"\x00\x00\x00"

def handle_unary_unary(test, request, servicer_context):
    return _RESPONSE

def handle_unary_stream(test, request, servicer_context):
    for _ in range(test_constants.STREAM_LENGTH):
        yield _RESPONSE

def handle_stream_unary(test, request_iterator, servicer_context):
    for _ in request_iterator:
        pass
    return _RESPONSE

def handle_stream_stream(test, request_iterator, servicer_context):
    for _ in request_iterator:
        yield _RESPONSE

class _MethodHandler(grpc.RpcMethodHandler):
    def __init__(self, test, request_streaming, response_streaming):
        self.request_streaming = request_streaming
        self.response_streaming = response_streaming
        self.request_deserializer = None
        self.response_serializer = None
        self.unary_unary = None
        self.unary_stream = None
        self.stream_unary = None
        self.stream_stream = None
        if self.request_streaming and self.response_streaming:
            self.stream_stream = lambda req, ctx: handle_stream_stream(
                test, req, ctx
            )
        elif self.request_streaming:
            self.stream_unary = lambda req, ctx: handle_stream_unary(
                test, req, ctx
            )
        elif self.response_streaming:
            self.unary_stream = lambda req, ctx: handle_unary_stream(
                test, req, ctx
            )
        else:
            self.unary_unary = lambda req, ctx: handle_unary_unary(
                test, req, ctx
            )

def get_method_handlers(test):
    return {
        _UNARY_UNARY: _MethodHandler(test, False, False),
        _UNARY_STREAM: _MethodHandler(test, False, True),
        _STREAM_UNARY: _MethodHandler(test, True, False),
        _STREAM_STREAM: _MethodHandler(test, True, True),
    }

def create_phony_channel():
    """Creating phony channels is a workaround for retries"""
    host, port, sock = get_socket(sock_options=(socket.SO_REUSEADDR,))
    sock.close()
    return grpc.insecure_channel("{}:{}".format(host, port))

def perform_unary_unary_call(channel, wait_for_ready=None):
    channel.unary_unary(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _UNARY_UNARY),
        _registered_method=True,
    ).__call__(
        _REQUEST,
        timeout=test_constants.LONG_TIMEOUT,
        wait_for_ready=wait_for_ready,
    )

def perform_unary_unary_with_call(channel, wait_for_ready=None):
    channel.unary_unary(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _UNARY_UNARY),
        _registered_method=True,
    ).with_call(
        _REQUEST,
        timeout=test_constants.LONG_TIMEOUT,
        wait_for_ready=wait_for_ready,
    )

def perform_unary_unary_future(channel, wait_for_ready=None):
    channel.unary_unary(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _UNARY_UNARY),
        _registered_method=True,
    ).future(
        _REQUEST,
        timeout=test_constants.LONG_TIMEOUT,
        wait_for_ready=wait_for_ready,
    ).result(
        timeout=test_constants.LONG_TIMEOUT
    )

def perform_unary_stream_call(channel, wait_for_ready=None):
    response_iterator = channel.unary_stream(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _UNARY_STREAM),
        _registered_method=True,
    ).__call__(
        _REQUEST,
        timeout=test_constants.LONG_TIMEOUT,
        wait_for_ready=wait_for_ready,
    )
    for _ in response_iterator:
        pass

def perform_stream_unary_call(channel, wait_for_ready=None):
    channel.stream_unary(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _STREAM_UNARY),
        _registered_method=True,
    ).__call__(
        iter([_REQUEST] * test_constants.STREAM_LENGTH),
        timeout=test_constants.LONG_TIMEOUT,
        wait_for_ready=wait_for_ready,
    )

def perform_stream_unary_with_call(channel, wait_for_ready=None):
    channel.stream_unary(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _STREAM_UNARY),
        _registered_method=True,
    ).with_call(
        iter([_REQUEST] * test_constants.STREAM_LENGTH),
        timeout=test_constants.LONG_TIMEOUT,
        wait_for_ready=wait_for_ready,
    )

def perform_stream_unary_future(channel, wait_for_ready=None):
    channel.stream_unary(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _STREAM_UNARY),
        _registered_method=True,
    ).future(
        iter([_REQUEST] * test_constants.STREAM_LENGTH),
        timeout=test_constants.LONG_TIMEOUT,
        wait_for_ready=wait_for_ready,
    ).result(
        timeout=test_constants.LONG_TIMEOUT
    )

def perform_stream_stream_call(channel, wait_for_ready=None):
    response_iterator = channel.stream_stream(
        grpc._common.fully_qualified_method(_SERVICE_NAME, _STREAM_STREAM),
        _registered_method=True,
    ).__call__(
        iter([_REQUEST] * test_constants.STREAM_LENGTH),
        timeout=test_constants.LONG_TIMEOUT,
        wait_for_ready=wait_for_ready,
    )
    for _ in response_iterator:
        pass

_ALL_CALL_CASES = [
    perform_unary_unary_call,
    perform_unary_unary_with_call,
    perform_unary_unary_future,
    perform_unary_stream_call,
    perform_stream_unary_call,
    perform_stream_unary_with_call,
    perform_stream_unary_future,
    perform_stream_stream_call,
]

class MetadataFlagsTest(unittest.TestCase):
    def check_connection_does_failfast(self, fn, channel, wait_for_ready=None):
        try:
            fn(channel, wait_for_ready)
            self.fail("The Call should fail")
        except BaseException as e:
            self.assertIs(grpc.StatusCode.UNAVAILABLE, e.code())

    def test_call_wait_for_ready_default(self):
        for perform_call in _ALL_CALL_CASES:
            with create_phony_channel() as channel:
                self.check_connection_does_failfast(perform_call, channel)

    def test_call_wait_for_ready_disabled(self):
        for perform_call in _ALL_CALL_CASES:
            with create_phony_channel() as channel:
                self.check_connection_does_failfast(
                    perform_call, channel, wait_for_ready=False
                )

    def test_call_wait_for_ready_enabled(self):

        unhandled_exceptions = queue.Queue()

        host, port, sock = get_socket(sock_options=(socket.SO_REUSEADDR,))
        sock.close()

        addr = "{}:{}".format(host, port)
        wg = test_common.WaitGroup(len(_ALL_CALL_CASES))

        def wait_for_transient_failure(channel_connectivity):
            if (
                channel_connectivity
                == grpc.ChannelConnectivity.TRANSIENT_FAILURE
            ):
                wg.done()

        def test_call(perform_call):
            with grpc.insecure_channel(addr) as channel:
                try:
                    channel.subscribe(wait_for_transient_failure)
                    perform_call(channel, wait_for_ready=True)
                except BaseException as e:

                    wg.done()
                    unhandled_exceptions.put(e, True)

        test_threads = []
        for perform_call in _ALL_CALL_CASES:
            test_thread = threading.Thread(
                target=test_call, args=(perform_call,)
            )
            test_thread.daemon = True
            test_thread.exception = None
            test_thread.start()
            test_threads.append(test_thread)

        wg.wait()
        server = test_common.test_server(reuse_port=True)
        server.add_registered_method_handlers(
            _SERVICE_NAME, get_method_handlers(weakref.proxy(self))
        )
        server.add_insecure_port(addr)
        server.start()

        for test_thread in test_threads:
            test_thread.join()

        server.stop(0)

        if not unhandled_exceptions.empty():
            raise unhandled_exceptions.get(True)

if __name__ == "__main__":
    logging.basicConfig(level=logging.DEBUG)
    unittest.main(verbosity=2)
