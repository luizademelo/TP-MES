Here's the commented version of the code:

```c++
# Copyright 2020 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

import asyncio
import collections
import logging
import multiprocessing
import os
import sys
import time
from typing import Tuple

import grpc
from grpc.experimental import aio

from src.proto.grpc.testing import benchmark_service_pb2_grpc
from src.proto.grpc.testing import control_pb2
from src.proto.grpc.testing import stats_pb2
from src.proto.grpc.testing import worker_service_pb2_grpc
from tests.qps import histogram
from tests.unit import resources
from tests.unit.framework.common import get_socket
from tests_aio.benchmark import benchmark_client
from tests_aio.benchmark import benchmark_servicer

# Number of CPU cores available on the system
_NUM_CORES = multiprocessing.cpu_count()

# Path to the worker entry script
_WORKER_ENTRY_FILE = os.path.join(
    os.path.split(os.path.abspath(__file__))[0], "worker.py"
)

# Logger instance for this module
_LOGGER = logging.getLogger(__name__)

class _SubWorker(
    collections.namedtuple("_SubWorker", ["process", "port", "channel", "stub"])
):
    """A data class that holds information about a child qps worker.
    Attributes:
        process: The subprocess running the worker
        port: The port number the worker is using
        channel: gRPC channel to communicate with the worker
        stub: gRPC stub for the worker service
    """

    def _repr(self):
        """Internal representation helper method."""
        return f"<_SubWorker pid={self.process.pid} port={self.port}>"

    def __repr__(self):
        """Official string representation."""
        return self._repr()

    def __str__(self):
        """Informal string representation."""
        return self._repr()

def _get_server_status(
    start_time: float, end_time: float, port: int
) -> control_pb2.ServerStatus:
    """Creates ServerStatus proto message with performance statistics.
    
    Args:
        start_time: Timestamp when measurement started
        end_time: Timestamp when measurement ended
        port: Port number the server is running on
        
    Returns:
        control_pb2.ServerStatus: Proto message containing server stats
    """
    end_time = time.monotonic()
    elapsed_time = end_time - start_time

    stats = stats_pb2.ServerStats(
        time_elapsed=elapsed_time,
        time_user=elapsed_time,
        time_system=elapsed_time,
    )
    return control_pb2.ServerStatus(stats=stats, port=port, cores=_NUM_CORES)

def _create_server(config: control_pb2.ServerConfig) -> Tuple[aio.Server, int]:
    """Creates and configures a gRPC server based on the provided configuration.
    
    Args:
        config: Server configuration parameters
        
    Returns:
        Tuple containing:
            - The configured server instance
            - Port number the server is bound to
            
    Raises:
        NotImplementedError: If unsupported server type is specified
    """
    # Process channel arguments from config
    channel_args = tuple(
        (arg.name, arg.str_value)
        if arg.HasField("str_value")
        else (arg.name, int(arg.int_value))
        for arg in config.channel_args
    )

    # Create server with channel arguments
    server = aio.server(options=channel_args + (("grpc.so_reuseport", 1),))
    
    # Configure server based on type
    if config.server_type == control_pb2.ASYNC_SERVER:
        # Standard benchmark service implementation
        servicer = benchmark_servicer.BenchmarkServicer()
        benchmark_service_pb2_grpc.add_BenchmarkServiceServicer_to_server(
            servicer, server
        )
    elif config.server_type == control_pb2.ASYNC_GENERIC_SERVER:
        # Generic benchmark service implementation
        resp_size = config.payload_config.bytebuf_params.resp_size
        servicer = benchmark_servicer.GenericBenchmarkServicer(resp_size)
        method_implementations = {
            "StreamingCall": grpc.stream_stream_rpc_method_handler(
                servicer.StreamingCall
            ),
            "UnaryCall": grpc.unary_unary_rpc_method_handler(
                servicer.UnaryCall
            ),
        }
        handler = grpc.method_handlers_generic_handler(
            "grpc.testing.BenchmarkService", method_implementations
        )
        server.add_generic_rpc_handlers((handler,))
    else:
        raise NotImplementedError(
            "Unsupported server type {}".format(config.server_type)
        )

    # Configure server security
    if config.HasField("security_params"):
        server_creds = grpc.ssl_server_credentials(
            ((resources.private_key(), resources.certificate_chain()),)
        port = server.add_secure_port(
            "[::]:{}".format(config.port), server_creds
        )
    else:
        port = server.add_insecure_port("[::]:{}".format(config.port))

    return server, port

def _get_client_status(
    start_time: float, end_time: float, qps_data: histogram.Histogram
) -> control_pb2.ClientStatus:
    """Creates ClientStatus proto message with performance statistics.
    
    Args:
        start_time: Timestamp when measurement started
        end_time: Timestamp when measurement ended
        qps_data: Histogram containing latency measurements
        
    Returns:
        control_pb2.ClientStatus: Proto message containing client stats
    """
    latencies = qps_data.get_data()
    end_time = time.monotonic()
    elapsed_time = end_time - start_time

    stats = stats_pb2.ClientStats(
        latencies=latencies,
        time_elapsed=elapsed_time,
        time_user=elapsed_time,
        time_system=elapsed_time,
    )
    return control_pb2.ClientStatus(stats=stats)

def _create_client(
    server: str, config: control_pb2.ClientConfig, qps_data: histogram.Histogram
) -> benchmark_client.BenchmarkClient:
    """Creates and configures a benchmark client based on the provided configuration.
    
    Args:
        server: Target server address
        config: Client configuration parameters
        qps_data: Histogram for storing latency measurements
        
    Returns:
        Configured benchmark client instance
        
    Raises:
        NotImplementedError: If unsupported client type or load parameter is specified
    """
    if config.load_params.WhichOneof("load") != "closed_loop":
        raise NotImplementedError(
            f"Unsupported load parameter {config.load_params}"
        )

    if config.client_type == control_pb2.ASYNC_CLIENT:
        # Select appropriate client type based on RPC type
        if config.rpc_type == control_pb2.UNARY:
            client_type = benchmark_client.UnaryAsyncBenchmarkClient
        elif config.rpc_type == control_pb2.STREAMING:
            client_type = benchmark_client.StreamingAsyncBenchmarkClient
        elif config.rpc_type == control_pb2.STREAMING_FROM_SERVER:
            client_type = benchmark_client.ServerStreamingAsyncBenchmarkClient
        else:
            raise NotImplementedError(
                f"Unsupported rpc_type [{config.rpc_type}]"
            )
    else:
        raise NotImplementedError(
            f"Unsupported client type {config.client_type}"
        )

    return client_type(server, config, qps_data)

def _pick_an_unused_port() -> int:
    """Finds and returns an unused TCP port.
    
    Returns:
        int: Available port number
    """
    _, port, sock = get_socket()
    sock.close()
    return port

async def _create_sub_worker() -> _SubWorker:
    """Creates a child qps worker as a subprocess.
    
    Returns:
        _SubWorker: Instance containing subprocess information
    """
    port = _pick_an_unused_port()

    _LOGGER.info("Creating sub worker at port [%d]...", port)
    # Launch worker subprocess
    process = await asyncio.create_subprocess_exec(
        sys.executable, _WORKER_ENTRY_FILE, "--driver_port", str(port)
    _LOGGER.info(
        "Created sub worker process for port [%d] at pid [%d]",
        port,
        process.pid,
    )
    # Create channel to communicate with worker
    channel = aio.insecure_channel(f"localhost:{port}")
    _LOGGER.info("Waiting for sub worker at port [%d]", port)
    await channel.channel_ready()
    stub = worker_service_pb2_grpc.WorkerServiceStub(channel)
    return _SubWorker(
        process=process,
        port=port,
        channel=channel,
        stub=stub,
    )

class WorkerServicer(worker_service_pb2_grpc.WorkerServiceServicer):
    """Implementation of the gRPC Worker Service.
    
    Handles server and client benchmark requests and manages worker processes.
    """

    def __init__(self):
        """Initializes the worker servicer with event loop and quit event."""
        self._loop = asyncio.get_event_loop()
        self._quit_event = asyncio.Event()

    async def _run_single_server(self, config, request_iterator, context):
        """Runs a single benchmark server instance.
        
        Args:
            config: Server configuration
            request_iterator: Stream of control messages
            context: RPC context
        """
        server, port = _create_server(config)
        await server.start()
        _LOGGER.info("Server started at port [%d]", port)

        start_time = time.monotonic()
        await context.write(_get_server_status(start_time, start_time, port))

        # Process control messages and update status
        async for request in request_iterator:
            end_time = time.monotonic()
            status = _get_server_status(start_time, end_time, port)
            if request.mark.reset:
                start_time = end_time
            await context.write(status)
        await server.stop(None)

    async def RunServer(self, request_iterator, context):
        """Implements the RunServer RPC method.
        
        Handles both single-process and multi-process server scenarios.
        """
        config_request = await context.read()
        config = config_request.setup
        _LOGGER.info("Received ServerConfig: %s", config)

        # Adjust number of server processes if needed
        if config.server_processes <= 0:
            _LOGGER.info("Using server_processes == [%d]", _NUM_CORES)
            config.server_processes = _NUM_CORES

        if config.port == 0:
            config.port = _pick_an_unused_port()
        _LOGGER.info("Port picked [%d]", config.port)

        if config.server_processes == 1:
            # Single process mode
            await self._run_single_server(config, request_iterator, context)
        else:
            # Multi-process mode - create sub-workers
            sub_workers = await asyncio.gather(
                *[_create_sub_worker() for _ in range(config.server_processes)]
            )

            # Set up RPC calls to each sub-worker
            calls = [worker.stub.RunServer() for worker in sub_workers]

            # Update config for sub-workers
            config_request.setup.server_processes = 1

            # Initialize all sub-workers
            for call in calls:
                await call.write(config_request)
                await call.read()

            # Send initial status
            start_time = time.monotonic()
            await context.write(
                _get_server_status(
                    start_time,
                    start_time,
                    config.port,
                )
            )

            _LOGGER.info("Servers are ready to serve.")

            # Process benchmark control messages
            async for request in request_iterator:
                end_time = time.monotonic()

                # Forward request to all sub-workers
                for call in calls:
                    await call.write(request)
                    await call.read()

                # Aggregate and send status
                status = _get_server_status(
                    start_time,
                    end_time,
                    config.port,
                )
                if request.mark.reset:
                    start_time = end_time
                await context.write(status)

            # Clean up sub-workers
            for call in calls:
                await call.done_writing()

            for worker in sub_workers:
                await worker.stub.QuitWorker(control_pb2.Void())
                await worker.channel.close()
                _LOGGER.info("Waiting for [%s] to quit...", worker)
                await worker.process.wait()

    async def _run_single_client(self, config, request_iterator, context):
        """Runs a single benchmark client instance.
        
        Args:
            config: Client configuration
            request_iterator: Stream of control messages
            context: RPC context
        """
        running_tasks = []
        qps_data = histogram.Histogram(
            config.histogram_params.resolution,
            config.histogram_params.max_possible,
        )
        start_time = time.monotonic()

        # Create client channels and start benchmark tasks
        for i in range(config.client_channels):
            server = config.server_targets[i % len(config.server_targets)]
            client = _create_client(server, config, qps_data)
            _LOGGER.info("Client created against server [%s]", server)
            running_tasks.append(self._loop.create_task(client.run()))

        # Send initial status
        end_time = time.monotonic()
        await context.write(_get_client_status(start_time, end_time, qps_data))

        # Process control messages and update status
        async for request in request_iterator:
            end_time = time.monotonic()
            status = _get_client_status(start_time, end_time, qps_data)
            if request.mark.reset:
                qps_data.reset()
                start_time = time.monotonic()
            await context.write(status)

        # Clean up running tasks
        for task in running_tasks:
            task.cancel()

    async def RunClient(self, request_iterator, context):
        """Implements the RunClient RPC method.
        
        Handles both single-process and multi-process client scenarios.
        """
        config_request = await context.read()
        config = config_request.setup
        _LOGGER.info("Received ClientConfig: %s", config)

        # Adjust number of client processes if needed
        if config.client_processes <= 0:
            _LOGGER.info(
                "client_processes can't be [%d]", config.client_processes
            )
            _LOGGER.info("Using client_processes == [%d]", _NUM_CORES)
            config.client_processes = _NUM_CORES

        if config.client_processes == 1:
            # Single process mode
            await self._run_single_client(config, request_iterator, context)
        else:
            # Multi-process mode - create sub-workers
            sub_workers = await asyncio.gather(
                *[_create_sub_worker() for _ in range(config.client_processes)]
            )

            # Set up RPC calls to each sub-worker
            calls = [worker.stub.RunClient() for worker in sub_workers]

            # Update config for sub-workers
            config_request.setup.client_processes = 1

            # Initialize all sub-workers
            for call in calls:
                await call.write(config_request)
                await call.read()

            # Prepare combined histogram for results
            start_time = time.monotonic()
            result = histogram.Histogram(
                config.histogram_params.resolution,
                config.histogram_params.max_possible,
            )
            end_time = time.monotonic()
            await context.write(
                _get_client_status(start_time, end_time, result)
            )

            # Process benchmark control messages
            async for request in request_iterator:
                end_time = time.monotonic()

                # Collect results from all sub-workers
                for call in calls:
                    _LOGGER.debug("Fetching status...")
                    await call.write(request)
                    sub_status = await call.read()
                    result.merge(sub_status.stats.latencies)
                    _LOGGER.debug(
                        "Update from sub worker count=[%d]",
                        sub_status.stats.latencies.count,
                    )

                # Send aggregated status
                status = _get_client_status(start_time, end_time, result)
                if request.mark.reset:
                    result.reset()
                    start_time = time.monotonic()
                _LOGGER.debug(
                    "Reporting count=[%d]", status.stats.latencies.count
                )
                await context.write(status)

            # Clean up sub-workers
            for call in calls:
                await call.done_writing()

            for worker in sub_workers:
                await worker.stub.QuitWorker(control_pb2.Void())
                await worker.channel.close()
                _LOGGER.info("Waiting for sub worker [%s] to quit...", worker)
                await worker.process.wait()
                _LOGGER.info("Sub worker [%s] quit", worker)

    @staticmethod
    async def CoreCount(unused_request, unused_context):
        """Returns the number of CPU cores available."""
        return control_pb2.CoreResponse(cores=_NUM_CORES)

    async def QuitWorker(self, unused_request, unused_context):
        """Handles quit command to shutdown the worker."""
        _LOGGER.info("QuitWorker command received.")
        self._quit_event.set()
        return control_pb2.Void()

    async def wait_for_quit(self):
        """Waits for quit command to be received."""
        await self._quit_event.wait()
```