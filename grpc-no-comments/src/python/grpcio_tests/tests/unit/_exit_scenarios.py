# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Defines a number of module-scope gRPC scenarios to test clean exit."""

import argparse
import logging
import threading
import time

import grpc

from tests.unit.framework.common import test_constants

WAIT_TIME = 1000

REQUEST = b"request"

UNSTARTED_SERVER = "unstarted_server"
RUNNING_SERVER = "running_server"
POLL_CONNECTIVITY_NO_SERVER = "poll_connectivity_no_server"
POLL_CONNECTIVITY = "poll_connectivity"
IN_FLIGHT_UNARY_UNARY_CALL = "in_flight_unary_unary_call"
IN_FLIGHT_UNARY_STREAM_CALL = "in_flight_unary_stream_call"
IN_FLIGHT_STREAM_UNARY_CALL = "in_flight_stream_unary_call"
IN_FLIGHT_STREAM_STREAM_CALL = "in_flight_stream_stream_call"
IN_FLIGHT_PARTIAL_UNARY_STREAM_CALL = "in_flight_partial_unary_stream_call"
IN_FLIGHT_PARTIAL_STREAM_UNARY_CALL = "in_flight_partial_stream_unary_call"
IN_FLIGHT_PARTIAL_STREAM_STREAM_CALL = "in_flight_partial_stream_stream_call"

_SERVICE_NAME = "test"
UNARY_UNARY = b"UnaryUnary"
UNARY_STREAM = b"UnaryStream"
STREAM_UNARY = b"StreamUnary"
STREAM_STREAM = b"StreamStream"
PARTIAL_UNARY_STREAM = b"PartialUnaryStream"
PARTIAL_STREAM_UNARY = b"PartialStreamUnary"
PARTIAL_STREAM_STREAM = b"PartialStreamStream"

TEST_TO_METHOD = {
    IN_FLIGHT_UNARY_UNARY_CALL: UNARY_UNARY,
    IN_FLIGHT_UNARY_STREAM_CALL: UNARY_STREAM,
    IN_FLIGHT_STREAM_UNARY_CALL: STREAM_UNARY,
    IN_FLIGHT_STREAM_STREAM_CALL: STREAM_STREAM,
    IN_FLIGHT_PARTIAL_UNARY_STREAM_CALL: PARTIAL_UNARY_STREAM,
    IN_FLIGHT_PARTIAL_STREAM_UNARY_CALL: PARTIAL_STREAM_UNARY,
    IN_FLIGHT_PARTIAL_STREAM_STREAM_CALL: PARTIAL_STREAM_STREAM,
}

def hang_unary_unary(request, servicer_context):
    time.sleep(WAIT_TIME)

def hang_unary_stream(request, servicer_context):
    time.sleep(WAIT_TIME)

def hang_partial_unary_stream(request, servicer_context):
    for _ in range(test_constants.STREAM_LENGTH // 2):
        yield request
    time.sleep(WAIT_TIME)

def hang_stream_unary(request_iterator, servicer_context):
    time.sleep(WAIT_TIME)

def hang_partial_stream_unary(request_iterator, servicer_context):
    for _ in range(test_constants.STREAM_LENGTH // 2):
        next(request_iterator)
    time.sleep(WAIT_TIME)

def hang_stream_stream(request_iterator, servicer_context):
    time.sleep(WAIT_TIME)

def hang_partial_stream_stream(request_iterator, servicer_context):
    for _ in range(test_constants.STREAM_LENGTH // 2):
        yield next(request_iterator)
    time.sleep(WAIT_TIME)

class MethodHandler(grpc.RpcMethodHandler):
    def __init__(self, request_streaming, response_streaming, partial_hang):
        self.request_streaming = request_streaming
        self.response_streaming = response_streaming
        self.request_deserializer = None
        self.response_serializer = None
        self.unary_unary = None
        self.unary_stream = None
        self.stream_unary = None
        self.stream_stream = None
        if self.request_streaming and self.response_streaming:
            if partial_hang:
                self.stream_stream = hang_partial_stream_stream
            else:
                self.stream_stream = hang_stream_stream
        elif self.request_streaming:
            if partial_hang:
                self.stream_unary = hang_partial_stream_unary
            else:
                self.stream_unary = hang_stream_unary
        elif self.response_streaming:
            if partial_hang:
                self.unary_stream = hang_partial_unary_stream
            else:
                self.unary_stream = hang_unary_stream
        else:
            self.unary_unary = hang_unary_unary

class GenericHandler(grpc.GenericRpcHandler):
    def service(self, handler_call_details):
        if handler_call_details.method == UNARY_UNARY:
            return MethodHandler(False, False, False)
        elif handler_call_details.method == UNARY_STREAM:
            return MethodHandler(False, True, False)
        elif handler_call_details.method == STREAM_UNARY:
            return MethodHandler(True, False, False)
        elif handler_call_details.method == STREAM_STREAM:
            return MethodHandler(True, True, False)
        elif handler_call_details.method == PARTIAL_UNARY_STREAM:
            return MethodHandler(False, True, True)
        elif handler_call_details.method == PARTIAL_STREAM_UNARY:
            return MethodHandler(True, False, True)
        elif handler_call_details.method == PARTIAL_STREAM_STREAM:
            return MethodHandler(True, True, True)
        else:
            return None

_METHOD_HANDLERS = {
    UNARY_UNARY: MethodHandler(False, False, False),
    UNARY_STREAM: MethodHandler(False, True, False),
    STREAM_UNARY: MethodHandler(True, False, False),
    STREAM_STREAM: MethodHandler(True, True, False),
    PARTIAL_UNARY_STREAM: MethodHandler(False, True, True),
    PARTIAL_STREAM_UNARY: MethodHandler(True, False, True),
    PARTIAL_STREAM_STREAM: MethodHandler(True, True, True),
}

class DaemonPool(object):
    def submit(self, fn, *args, **kwargs):
        thread = threading.Thread(target=fn, args=args, kwargs=kwargs)
        thread.daemon = True
        thread.start()

    def shutdown(self, wait=True):
        pass

def infinite_request_iterator():
    while True:
        yield REQUEST

if __name__ == "__main__":
    logging.basicConfig()
    parser = argparse.ArgumentParser()
    parser.add_argument("scenario", type=str)
    parser.add_argument(
        "--wait_for_interrupt", dest="wait_for_interrupt", action="store_true"
    )
    args = parser.parse_args()

    if args.scenario == UNSTARTED_SERVER:
        server = grpc.server(DaemonPool(), options=(("grpc.so_reuseport", 0),))
        if args.wait_for_interrupt:
            time.sleep(WAIT_TIME)
    elif args.scenario == RUNNING_SERVER:
        server = grpc.server(DaemonPool(), options=(("grpc.so_reuseport", 0),))
        port = server.add_insecure_port("[::]:0")
        server.start()
        if args.wait_for_interrupt:
            time.sleep(WAIT_TIME)
    elif args.scenario == POLL_CONNECTIVITY_NO_SERVER:
        channel = grpc.insecure_channel("localhost:12345")

        def connectivity_callback(connectivity):
            pass

        channel.subscribe(connectivity_callback, try_to_connect=True)
        if args.wait_for_interrupt:
            time.sleep(WAIT_TIME)
    elif args.scenario == POLL_CONNECTIVITY:
        server = grpc.server(DaemonPool(), options=(("grpc.so_reuseport", 0),))
        port = server.add_insecure_port("[::]:0")
        server.start()
        channel = grpc.insecure_channel("localhost:%d" % port)

        def connectivity_callback(connectivity):
            pass

        channel.subscribe(connectivity_callback, try_to_connect=True)
        if args.wait_for_interrupt:
            time.sleep(WAIT_TIME)

    else:
        server = grpc.server(DaemonPool(), options=(("grpc.so_reuseport", 0),))
        port = server.add_insecure_port("[::]:0")
        server.add_registered_method_handlers(_SERVICE_NAME, _METHOD_HANDLERS)
        server.start()
        channel = grpc.insecure_channel("localhost:%d" % port)

        method = (
            grpc._common.fully_qualified_method(
                _SERVICE_NAME, TEST_TO_METHOD[args.scenario]
            ),
        )

        if args.scenario == IN_FLIGHT_UNARY_UNARY_CALL:
            multi_callable = channel.unary_unary(
                method,
                _registered_method=True,
            )
            future = multi_callable.future(REQUEST)
            result, call = multi_callable.with_call(REQUEST)
        elif (
            args.scenario == IN_FLIGHT_UNARY_STREAM_CALL
            or args.scenario == IN_FLIGHT_PARTIAL_UNARY_STREAM_CALL
        ):
            multi_callable = channel.unary_stream(
                method,
                _registered_method=True,
            )
            response_iterator = multi_callable(REQUEST)
            for response in response_iterator:
                pass
        elif (
            args.scenario == IN_FLIGHT_STREAM_UNARY_CALL
            or args.scenario == IN_FLIGHT_PARTIAL_STREAM_UNARY_CALL
        ):
            multi_callable = channel.stream_unary(
                method,
                _registered_method=True,
            )
            future = multi_callable.future(infinite_request_iterator())
            result, call = multi_callable.with_call(
                iter([REQUEST] * test_constants.STREAM_LENGTH)
            )
        elif (
            args.scenario == IN_FLIGHT_STREAM_STREAM_CALL
            or args.scenario == IN_FLIGHT_PARTIAL_STREAM_STREAM_CALL
        ):
            multi_callable = channel.stream_stream(
                method,
                _registered_method=True,
            )
            response_iterator = multi_callable(infinite_request_iterator())
            for response in response_iterator:
                pass
