Here's the commented version of the code:

```c++
# Copyright 2016 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

# Import required modules
from concurrent import futures
import multiprocessing
import random
import threading
import time

try:
    # Import resource module if available (Unix-like systems)
    import resource
except ImportError:
    pass

import grpc

# Import protocol buffer definitions and generated gRPC classes
from src.proto.grpc.testing import benchmark_service_pb2_grpc
from src.proto.grpc.testing import control_pb2
from src.proto.grpc.testing import stats_pb2
from src.proto.grpc.testing import worker_service_pb2_grpc
from tests.qps import benchmark_client
from tests.qps import benchmark_server
from tests.qps import client_runner
from tests.qps import histogram
from tests.unit import resources
from tests.unit import test_common

class Snapshotter:
    """Utility class for tracking system resource usage and time metrics."""
    
    def __init__(self):
        # Initialize tracking variables
        self._start_time = 0.0  # Start time of measurement period
        self._end_time = 0.0    # End time of measurement period
        self._last_utime = 0.0  # Previous user CPU time
        self._utime = 0.0       # Current user CPU time
        self._last_stime = 0.0  # Previous system CPU time
        self._stime = 0.0      # Current system CPU time

    def get_time_elapsed(self):
        """Returns elapsed wall clock time between snapshots."""
        return self._end_time - self._start_time

    def get_utime(self):
        """Returns elapsed user CPU time between snapshots."""
        return self._utime - self._last_utime

    def get_stime(self):
        """Returns elapsed system CPU time between snapshots."""
        return self._stime - self._last_stime

    def snapshot(self):
        """Takes a snapshot of current resource usage and time."""
        self._end_time = time.time()
        usage = resource.getrusage(resource.RUSAGE_SELF)
        self._utime = usage.ru_utime  # Current user CPU time
        self._stime = usage.ru_stime  # Current system CPU time

    def reset(self):
        """Resets the snapshot to current values as new baseline."""
        self._start_time = self._end_time
        self._last_utime = self._utime
        self._last_stime = self._stime

    def stats(self):
        """Returns dictionary of collected statistics."""
        return {
            "time_elapsed": self.get_time_elapsed(),
            "time_user": self.get_utime(),
            "time_system": self.get_stime(),
        }

class WorkerServer(worker_service_pb2_grpc.WorkerServiceServicer):
    """Python Worker Server implementation for gRPC benchmarking."""

    def __init__(self, server_port=None):
        # Initialize worker server with optional port binding
        self._quit_event = threading.Event()  # Event for graceful shutdown
        self._server_port = server_port       # Optional port override
        self._snapshotter = Snapshotter()     # Resource usage tracker

    def RunServer(self, request_iterator, context):
        """Implements the RunServer RPC for benchmark server operations."""
        
        # Get initial configuration from first request
        config = next(request_iterator).setup
        
        # Create and start server based on configuration
        server, port = self._create_server(config)
        cores = multiprocessing.cpu_count()
        server.start()
        
        # Take initial snapshot and reset baseline
        self._snapshotter.snapshot()
        self._snapshotter.reset()
        
        # Return initial status
        yield self._get_server_status(port, cores)

        # Process subsequent requests (mark/reset commands)
        for request in request_iterator:
            self._snapshotter.snapshot()
            status = self._get_server_status(port, cores)
            if request.mark.reset:
                self._snapshotter.reset()
            yield status
        
        # Stop server when done
        server.stop(None)

    def _get_server_status(self, port, cores):
        """Creates a ServerStatus message with current stats."""
        stats = stats_pb2.ServerStats(**self._snapshotter.stats())
        return control_pb2.ServerStatus(stats=stats, port=port, cores=cores)

    def _create_server(self, config):
        """Creates a gRPC server based on configuration."""
        # Determine number of worker threads
        if config.async_server_threads == 0:
            server_threads = multiprocessing.cpu_count() * 5
        else:
            server_threads = config.async_server_threads
        
        # Create base server
        server = test_common.test_server(max_workers=server_threads)
        
        # Add appropriate service implementation based on server type
        if config.server_type == control_pb2.ASYNC_SERVER:
            servicer = benchmark_server.BenchmarkServer()
            benchmark_service_pb2_grpc.add_BenchmarkServiceServicer_to_server(
                servicer, server
            )
        elif config.server_type == control_pb2.ASYNC_GENERIC_SERVER:
            resp_size = config.payload_config.bytebuf_params.resp_size
            servicer = benchmark_server.GenericBenchmarkServer(resp_size)
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
            raise Exception(
                "Unsupported server type {}".format(config.server_type)
            )

        # Determine port to use
        if self._server_port is not None and config.port == 0:
            server_port = self._server_port
        else:
            server_port = config.port

        # Configure security if specified
        if config.HasField("security_params"):
            server_creds = grpc.ssl_server_credentials(
                ((resources.private_key(), resources.certificate_chain()),)
            )
            port = server.add_secure_port(
                "[::]:{}".format(server_port), server_creds
            )
        else:
            port = server.add_insecure_port("[::]:{}".format(server_port))

        return (server, port)

    def RunClient(self, request_iterator, context):
        """Implements the RunClient RPC for benchmark client operations."""
        
        # Get initial configuration from first request
        config = next(request_iterator).setup
        
        # Initialize client runners and statistics tracking
        client_runners = []
        qps_data = histogram.Histogram(
            config.histogram_params.resolution,
            config.histogram_params.max_possible,
        )
        
        # Take initial snapshot and reset baseline
        self._snapshotter.snapshot()
        self._snapshotter.reset()

        # Create and start client runners for each channel
        for i in range(config.client_channels):
            server = config.server_targets[i % len(config.server_targets)]
            runner = self._create_client_runner(server, config, qps_data)
            client_runners.append(runner)
            runner.start()

        # Return initial status
        self._snapshotter.snapshot()
        yield self._get_client_status(qps_data)

        # Process subsequent requests (mark/reset commands)
        for request in request_iterator:
            self._snapshotter.snapshot()
            status = self._get_client_status(qps_data)
            if request.mark.reset:
                qps_data.reset()
                self._snapshotter.reset()
            yield status

        # Stop all client runners when done
        for runner in client_runners:
            runner.stop()

    def _get_client_status(self, qps_data):
        """Creates a ClientStatus message with current stats."""
        latencies = qps_data.get_data()
        stats = stats_pb2.ClientStats(
            latencies=latencies, **self._snapshotter.stats()
        )
        return control_pb2.ClientStatus(stats=stats)

    def _create_client_runner(self, server, config, qps_data):
        """Creates an appropriate client runner based on configuration."""
        no_ping_pong = False
        
        # Create appropriate client based on type and RPC method
        if config.client_type == control_pb2.SYNC_CLIENT:
            if config.rpc_type == control_pb2.UNARY:
                client = benchmark_client.UnarySyncBenchmarkClient(
                    server, config, qps_data
                )
            elif config.rpc_type == control_pb2.STREAMING:
                client = benchmark_client.StreamingSyncBenchmarkClient(
                    server, config, qps_data
                )
            elif config.rpc_type == control_pb2.STREAMING_FROM_SERVER:
                no_ping_pong = True
                client = benchmark_client.ServerStreamingSyncBenchmarkClient(
                    server, config, qps_data
                )
        elif config.client_type == control_pb2.ASYNC_CLIENT:
            if config.rpc_type == control_pb2.UNARY:
                client = benchmark_client.UnaryAsyncBenchmarkClient(
                    server, config, qps_data
                )
            else:
                raise Exception("Async streaming client not supported")
        else:
            raise Exception(
                "Unsupported client type {}".format(config.client_type)
            )

        # Create appropriate runner based on load type
        load_factor = float(config.client_channels)
        if config.load_params.WhichOneof("load") == "closed_loop":
            runner = client_runner.ClosedLoopClientRunner(
                client, config.outstanding_rpcs_per_channel, no_ping_pong
            )
        else:
            alpha = config.load_params.poisson.offered_load / load_factor

            def poisson():
                """Generator for Poisson process intervals."""
                while True:
                    yield random.expovariate(alpha)

            runner = client_runner.OpenLoopClientRunner(client, poisson())

        return runner

    def CoreCount(self, request, context):
        """Returns the number of CPU cores available."""
        return control_pb2.CoreResponse(cores=multiprocessing.cpu_count())

    def QuitWorker(self, request, context):
        """Signals the worker to shut down."""
        self._quit_event.set()
        return control_pb2.Void()

    def wait_for_quit(self):
        """Blocks until quit signal is received."""
        self._quit_event.wait()
```