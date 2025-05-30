# Copyright 2019 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The Python example of utilizing wait-for-ready flag."""

from concurrent import futures
from contextlib import contextmanager
import logging
import socket
import threading

import grpc

helloworld_pb2, helloworld_pb2_grpc = grpc.protos_and_services(
    "helloworld.proto"
)

_LOGGER = logging.getLogger(__name__)
_LOGGER.setLevel(logging.INFO)

@contextmanager
def get_free_loopback_tcp_port():
    if socket.has_ipv6:
        tcp_socket = socket.socket(socket.AF_INET6)
    else:
        tcp_socket = socket.socket(socket.AF_INET)
    tcp_socket.bind(("", 0))
    address_tuple = tcp_socket.getsockname()
    yield "localhost:%s" % (address_tuple[1])
    tcp_socket.close()

class Greeter(helloworld_pb2_grpc.GreeterServicer):
    def SayHello(self, request, unused_context):
        return helloworld_pb2.HelloReply(message="Hello, %s!" % request.name)

def create_server(server_address):
    server = grpc.server(futures.ThreadPoolExecutor())
    helloworld_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)
    bound_port = server.add_insecure_port(server_address)
    assert bound_port == int(server_address.split(":")[-1])
    return server

def process(stub, wait_for_ready=None):
    try:
        response = stub.SayHello(
            helloworld_pb2.HelloRequest(name="you"),
            wait_for_ready=wait_for_ready,
        )
        message = response.message
    except grpc.RpcError as rpc_error:
        assert rpc_error.code() == grpc.StatusCode.UNAVAILABLE
        assert not wait_for_ready
        message = rpc_error
    else:
        assert wait_for_ready
    _LOGGER.info(
        "Wait-for-ready %s, client received: %s",
        "enabled" if wait_for_ready else "disabled",
        message,
    )

def main():

    with get_free_loopback_tcp_port() as server_address:

        transient_failure_event = threading.Event()

        def wait_for_transient_failure(channel_connectivity):
            if (
                channel_connectivity
                == grpc.ChannelConnectivity.TRANSIENT_FAILURE
            ):
                transient_failure_event.set()

        channel = grpc.insecure_channel(server_address)
        channel.subscribe(wait_for_transient_failure)
        stub = helloworld_pb2_grpc.GreeterStub(channel)

        thread_disabled_wait_for_ready = threading.Thread(
            target=process, args=(stub, False)
        )
        thread_disabled_wait_for_ready.start()

        thread_enabled_wait_for_ready = threading.Thread(
            target=process, args=(stub, True)
        )
        thread_enabled_wait_for_ready.start()

    transient_failure_event.wait()
    server = create_server(server_address)
    server.start()

    thread_disabled_wait_for_ready.join()

    thread_enabled_wait_for_ready.join()

    server.stop(None)
    channel.close()

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    main()
