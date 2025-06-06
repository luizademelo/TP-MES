# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The Python implementation of the GRPC interoperability test server."""

from concurrent import futures
import logging

from absl import app
from absl.flags import argparse_flags
import grpc

from src.proto.grpc.testing import test_pb2_grpc
from tests.interop import resources
from tests.interop import service
from tests.unit import test_common

logging.basicConfig()
_LOGGER = logging.getLogger(__name__)

def parse_interop_server_arguments(argv):
    parser = argparse_flags.ArgumentParser()
    parser.add_argument(
        "--port", type=int, required=True, help="the port on which to serve"
    )
    parser.add_argument(
        "--use_tls",
        default=False,
        type=resources.parse_bool,
        help="require a secure connection",
    )
    parser.add_argument(
        "--use_alts",
        default=False,
        type=resources.parse_bool,
        help="require an ALTS connection",
    )
    return parser.parse_args(argv[1:])

def get_server_credentials(use_tls):
    if use_tls:
        private_key = resources.private_key()
        certificate_chain = resources.certificate_chain()
        return grpc.ssl_server_credentials(((private_key, certificate_chain),))
    else:
        return grpc.alts_server_credentials()

def serve(args):
    server = test_common.test_server()
    test_pb2_grpc.add_TestServiceServicer_to_server(
        service.TestService(), server
    )
    if args.use_tls or args.use_alts:
        credentials = get_server_credentials(args.use_tls)
        server.add_secure_port("[::]:{}".format(args.port), credentials)
    else:
        server.add_insecure_port("[::]:{}".format(args.port))

    server.start()
    _LOGGER.info("Server serving.")
    server.wait_for_termination()
    _LOGGER.info("Server stopped; exiting.")

if __name__ == "__main__":
    app.run(serve, flags_parser=parse_interop_server_arguments)
