# Copyright 2019 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Server of the Python example of customizing authentication mechanism."""

import argparse
from concurrent import futures
import contextlib
import logging

import _credentials
import grpc

helloworld_pb2, helloworld_pb2_grpc = grpc.protos_and_services(
    "helloworld.proto"
)

_LOGGER = logging.getLogger(__name__)
_LOGGER.setLevel(logging.INFO)

_LISTEN_ADDRESS_TEMPLATE = "localhost:%d"
_SIGNATURE_HEADER_KEY = "x-signature"

class SignatureValidationInterceptor(grpc.ServerInterceptor):
    def __init__(self):
        def abort(ignored_request, context):
            context.abort(grpc.StatusCode.UNAUTHENTICATED, "Invalid signature")

        self._abortion = grpc.unary_unary_rpc_method_handler(abort)

    def intercept_service(self, continuation, handler_call_details):

        method_name = handler_call_details.method.split("/")[-1]
        expected_metadata = (_SIGNATURE_HEADER_KEY, method_name[::-1])
        if expected_metadata in handler_call_details.invocation_metadata:
            return continuation(handler_call_details)
        else:
            return self._abortion

class SimpleGreeter(helloworld_pb2_grpc.GreeterServicer):
    def SayHello(self, request, unused_context):
        return helloworld_pb2.HelloReply(message="Hello, %s!" % request.name)

@contextlib.contextmanager
def run_server(port):

    server = grpc.server(
        futures.ThreadPoolExecutor(),
        interceptors=(SignatureValidationInterceptor(),),
    )
    helloworld_pb2_grpc.add_GreeterServicer_to_server(SimpleGreeter(), server)

    server_credentials = grpc.ssl_server_credentials(
        (
            (
                _credentials.SERVER_CERTIFICATE_KEY,
                _credentials.SERVER_CERTIFICATE,
            ),
        )
    )

    port = server.add_secure_port(
        _LISTEN_ADDRESS_TEMPLATE % port, server_credentials
    )

    server.start()
    try:
        yield server, port
    finally:
        server.stop(0)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--port", nargs="?", type=int, default=50051, help="the listening port"
    )
    args = parser.parse_args()

    with run_server(args.port) as (server, port):
        logging.info("Server is listening at port :%d", port)
        server.wait_for_termination()

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    main()
