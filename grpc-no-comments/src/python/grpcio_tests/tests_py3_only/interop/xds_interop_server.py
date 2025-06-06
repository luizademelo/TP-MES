# Copyright 2021 The gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import collections
from concurrent import futures
import logging
import signal
import socket
import sys
import threading
import time
from typing import DefaultDict, Dict, List, Mapping, Sequence, Set, Tuple

import grpc
from grpc_channelz.v1 import channelz
from grpc_channelz.v1 import channelz_pb2
from grpc_csm_observability import CsmOpenTelemetryPlugin
from grpc_health.v1 import health as grpc_health
from grpc_health.v1 import health_pb2
from grpc_health.v1 import health_pb2_grpc
from grpc_reflection.v1alpha import reflection
from opentelemetry.exporter.prometheus import PrometheusMetricReader
from opentelemetry.sdk.metrics import MeterProvider
from prometheus_client import start_http_server

from src.proto.grpc.testing import empty_pb2
from src.proto.grpc.testing import messages_pb2
from src.proto.grpc.testing import test_pb2
from src.proto.grpc.testing import test_pb2_grpc
from src.python.grpcio_tests.tests.fork import native_debug

native_debug.install_failure_signal_handler()

# NOTE: This interop server is not fully compatible with all xDS interop tests.

_LISTEN_HOST = "0.0.0.0"
_PROMETHEUS_PORT = 9464

_THREAD_POOL_SIZE = 256

logger = logging.getLogger()
console_handler = logging.StreamHandler()
formatter = logging.Formatter(fmt="%(asctime)s: %(levelname)-8s %(message)s")
console_handler.setFormatter(formatter)
logger.addHandler(console_handler)

class TestService(test_pb2_grpc.TestServiceServicer):
    def __init__(self, server_id, hostname):
        self._server_id = server_id
        self._hostname = hostname

    def EmptyCall(
        self, _: empty_pb2.Empty, context: grpc.ServicerContext
    ) -> empty_pb2.Empty:
        context.send_initial_metadata((("hostname", self._hostname),))
        return empty_pb2.Empty()

    def UnaryCall(
        self, request: messages_pb2.SimpleRequest, context: grpc.ServicerContext
    ) -> messages_pb2.SimpleResponse:
        context.send_initial_metadata((("hostname", self._hostname),))
        if request.response_size > 0:
            response = messages_pb2.SimpleResponse(
                payload=messages_pb2.Payload(body=b"0" * request.response_size)
            )
        else:
            response = messages_pb2.SimpleResponse()
        response.server_id = self._server_id
        response.hostname = self._hostname
        return response

def _configure_maintenance_server(
    server: grpc.Server, maintenance_port: int
) -> None:
    channelz.add_channelz_servicer(server)
    listen_address = f"{_LISTEN_HOST}:{maintenance_port}"
    server.add_insecure_port(listen_address)
    health_servicer = grpc_health.HealthServicer(
        experimental_non_blocking=True,
        experimental_thread_pool=futures.ThreadPoolExecutor(
            max_workers=_THREAD_POOL_SIZE
        ),
    )

    health_pb2_grpc.add_HealthServicer_to_server(health_servicer, server)
    SERVICE_NAMES = (
        test_pb2.DESCRIPTOR.services_by_name["TestService"].full_name,
        health_pb2.DESCRIPTOR.services_by_name["Health"].full_name,
        channelz_pb2.DESCRIPTOR.services_by_name["Channelz"].full_name,
        reflection.SERVICE_NAME,
    )
    for service in SERVICE_NAMES:
        health_servicer.set(service, health_pb2.HealthCheckResponse.SERVING)
    reflection.enable_server_reflection(SERVICE_NAMES, server)

def _configure_test_server(
    server: grpc.Server, port: int, secure_mode: bool, server_id: str
) -> None:
    test_pb2_grpc.add_TestServiceServicer_to_server(
        TestService(server_id, socket.gethostname()), server
    )
    listen_address = f"{_LISTEN_HOST}:{port}"
    if not secure_mode:
        server.add_insecure_port(listen_address)
    else:
        logger.info("Running with xDS Server credentials")
        server_fallback_creds = grpc.insecure_server_credentials()
        server_creds = grpc.xds_server_credentials(server_fallback_creds)
        server.add_secure_port(listen_address, server_creds)

def _run(
    port: int,
    maintenance_port: int,
    secure_mode: bool,
    server_id: str,
    enable_csm_observability: bool,
) -> None:
    csm_plugin = None
    if enable_csm_observability:
        csm_plugin = _prepare_csm_observability_plugin()
        csm_plugin.register_global()
    if port == maintenance_port:
        server = grpc.server(
            futures.ThreadPoolExecutor(max_workers=_THREAD_POOL_SIZE)
        )
        _configure_test_server(server, port, secure_mode, server_id)
        _configure_maintenance_server(server, maintenance_port)
        server.start()
        logger.info("Test server listening on port %d", port)
        logger.info("Maintenance server listening on port %d", maintenance_port)
        server.wait_for_termination()
    else:
        maintenance_server = grpc.server(
            futures.ThreadPoolExecutor(max_workers=_THREAD_POOL_SIZE)
        )
        _configure_maintenance_server(maintenance_server, maintenance_port)
        maintenance_server.start()
        logger.info("Maintenance server listening on port %d", maintenance_port)
        test_server = grpc.server(
            futures.ThreadPoolExecutor(max_workers=_THREAD_POOL_SIZE),
            xds=secure_mode,
        )
        _configure_test_server(test_server, port, secure_mode, server_id)
        test_server.start()
        logger.info("Test server listening on port %d", port)
        test_server.wait_for_termination()
        maintenance_server.wait_for_termination()
    if csm_plugin:
        csm_plugin.deregister_global()

def bool_arg(arg: str) -> bool:
    if arg.lower() in ("true", "yes", "y"):
        return True
    elif arg.lower() in ("false", "no", "n"):
        return False
    else:
        raise argparse.ArgumentTypeError(f"Could not parse '{arg}' as a bool.")

def _prepare_csm_observability_plugin() -> CsmOpenTelemetryPlugin:

    start_http_server(port=_PROMETHEUS_PORT, addr="0.0.0.0")
    reader = PrometheusMetricReader()
    meter_provider = MeterProvider(metric_readers=[reader])
    csm_plugin = CsmOpenTelemetryPlugin(
        meter_provider=meter_provider,
    )
    return csm_plugin

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Run Python xDS interop server."
    )
    parser.add_argument(
        "--port", type=int, default=8080, help="Port for test server."
    )
    parser.add_argument(
        "--maintenance_port",
        type=int,
        default=8080,
        help="Port for servers besides test server.",
    )
    parser.add_argument(
        "--secure_mode",
        type=bool_arg,
        default="False",
        help="If specified, uses xDS to retrieve server credentials.",
    )
    parser.add_argument(
        "--server_id",
        type=str,
        default="python_server",
        help="The server ID to return in responses..",
    )
    parser.add_argument(
        "--verbose",
        help="verbose log output",
        default=False,
        action="store_true",
    )
    parser.add_argument(
        "--enable_csm_observability",
        help="Whether to enable CSM Observability",
        default="False",
        type=bool_arg,
    )
    args = parser.parse_args()
    if args.verbose:
        logger.setLevel(logging.DEBUG)
    else:
        logger.setLevel(logging.INFO)
    if args.secure_mode and args.port == args.maintenance_port:
        raise ValueError(
            "--port and --maintenance_port must not be the same when"
            " --secure_mode is set."
        )
    _run(
        args.port,
        args.maintenance_port,
        args.secure_mode,
        args.server_id,
        args.enable_csm_observability,
    )
