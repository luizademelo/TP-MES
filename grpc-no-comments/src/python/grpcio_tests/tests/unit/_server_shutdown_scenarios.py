# Copyright 2018 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Defines a number of module-scope gRPC scenarios to test server shutdown."""

import argparse
from concurrent import futures
import logging
import os
import queue
import threading
import time

import grpc

from tests.unit import test_common

WAIT_TIME = 1000

REQUEST = b"request"
RESPONSE = b"response"

SERVER_RAISES_EXCEPTION = "server_raises_exception"
SERVER_DEALLOCATED = "server_deallocated"
SERVER_FORK_CAN_EXIT = "server_fork_can_exit"

_SERVICE_NAME = "test"
FORK_EXIT = "ForkExit"

def fork_and_exit(request, servicer_context):
    pid = os.fork()
    if pid == 0:
        os._exit(0)
    return RESPONSE

class GenericHandler(grpc.GenericRpcHandler):
    def service(self, handler_call_details):
        if handler_call_details.method == FORK_EXIT:
            return grpc.unary_unary_rpc_method_handler(fork_and_exit)
        else:
            return None

_METHOD_HANDLERS = {
    FORK_EXIT: grpc.unary_unary_rpc_method_handler(fork_and_exit)
}

def run_server(port_queue):
    server = test_common.test_server()
    port = server.add_insecure_port("[::]:0")
    port_queue.put(port)
    server.add_registered_method_handlers(_SERVICE_NAME, _METHOD_HANDLERS)
    server.start()

    time.sleep(WAIT_TIME)

def run_test(args):
    if args.scenario == SERVER_RAISES_EXCEPTION:
        server = test_common.test_server()
        server.start()
        raise Exception()
    elif args.scenario == SERVER_DEALLOCATED:
        server = test_common.test_server()
        server.start()
        server.__del__()
        while server._state.stage != grpc._server._ServerStage.STOPPED:
            pass
    elif args.scenario == SERVER_FORK_CAN_EXIT:
        port_queue = queue.Queue()
        thread = threading.Thread(target=run_server, args=(port_queue,))
        thread.daemon = True
        thread.start()
        port = port_queue.get()
        channel = grpc.insecure_channel("localhost:%d" % port)
        multi_callable = channel.unary_unary(
            grpc._common.fully_qualified_method(_SERVICE_NAME, FORK_EXIT),
            _registered_method=True,
        )
        result, call = multi_callable.with_call(REQUEST, wait_for_ready=True)
        os.wait()
    else:
        raise ValueError("unknown test scenario")

if __name__ == "__main__":
    logging.basicConfig()
    parser = argparse.ArgumentParser()
    parser.add_argument("scenario", type=str)
    args = parser.parse_args()
    run_test(args)
