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
"""The Python AsyncIO Benchmark Clients."""

import abc
import asyncio
import logging
import random
import time

import grpc
from grpc.experimental import aio

from src.proto.grpc.testing import benchmark_service_pb2_grpc
from src.proto.grpc.testing import control_pb2
from src.proto.grpc.testing import messages_pb2
from tests.qps import histogram
from tests.unit import resources

class GenericStub(object):
    """Generic gRPC stub that provides unary, server streaming, and bidirectional streaming methods."""
    def __init__(self, channel: aio.Channel):
        # Initialize unary RPC method
        self.UnaryCall = channel.unary_unary(
            "/grpc.testing.BenchmarkService/UnaryCall"
        )
        # Initialize server streaming RPC method
        self.StreamingFromServer = channel.unary_stream(
            "/grpc.testing.BenchmarkService/StreamingFromServer"
        )
        # Initialize bidirectional streaming RPC method
        self.StreamingCall = channel.stream_stream(
            "/grpc.testing.BenchmarkService/StreamingCall"
        )

class BenchmarkClient(abc.ABC):
    """Abstract base class for benchmark clients that provides common functionality."""
    
    def __init__(
        self,
        address: str,
        config: control_pb2.ClientConfig,
        hist: histogram.Histogram,
    ):
        # Create a unique channel option for identification
        unique_option = (("iv", random.random()),)

        # Process channel arguments from config
        channel_args = tuple(
            (arg.name, arg.str_value)
            if arg.HasField("str_value")
            else (arg.name, int(arg.int_value))
            for arg in config.channel_args
        )

        # Configure secure channel if security parameters are provided
        if config.HasField("security_params"):
            channel_credentials = grpc.ssl_channel_credentials(
                resources.test_root_certificates(),
            )
            server_host_override_option = (
                (
                    "grpc.ssl_target_name_override",
                    config.security_params.server_host_override,
                ),
            )
            self._channel = aio.secure_channel(
                address,
                channel_credentials,
                unique_option + channel_args + server_host_override_option,
            )
        else:
            # Otherwise create insecure channel
            self._channel = aio.insecure_channel(
                address, options=unique_option + channel_args
            )

        # Configure payload and request based on config
        if config.payload_config.WhichOneof("payload") == "simple_params":
            self._generic = False
            self._stub = benchmark_service_pb2_grpc.BenchmarkServiceStub(
                self._channel
            )
            # Create simple request with specified payload size
            payload = messages_pb2.Payload(
                body=b"\0" * config.payload_config.simple_params.req_size
            )
            self._request = messages_pb2.SimpleRequest(
                payload=payload,
                response_size=config.payload_config.simple_params.resp_size,
            )
        else:
            # Use generic stub for byte buffer payloads
            self._generic = True
            self._stub = GenericStub(self._channel)
            self._request = (
                b"\0" * config.payload_config.bytebuf_params.req_size
            )

        self._hist = hist  # Histogram for recording query times
        self._response_callbacks = []
        self._concurrency = config.outstanding_rpcs_per_channel  # Number of concurrent RPCs

    async def run(self) -> None:
        """Wait for channel to be ready before starting benchmark."""
        await self._channel.channel_ready()

    async def stop(self) -> None:
        """Close the channel when stopping benchmark."""
        await self._channel.close()

    def _record_query_time(self, query_time: float) -> None:
        """Record query time in nanoseconds to histogram."""
        self._hist.add(query_time * 1e9)

class UnaryAsyncBenchmarkClient(BenchmarkClient):
    """Benchmark client for unary RPC calls."""
    
    def __init__(
        self,
        address: str,
        config: control_pb2.ClientConfig,
        hist: histogram.Histogram,
    ):
        super().__init__(address, config, hist)
        self._running = None  # Flag to control benchmark execution
        self._stopped = asyncio.Event()  # Event to signal when stopped

    async def _send_request(self):
        """Send a single unary request and record its duration."""
        start_time = time.monotonic()
        await self._stub.UnaryCall(self._request)
        self._record_query_time(time.monotonic() - start_time)

    async def _send_indefinitely(self) -> None:
        """Continuously send requests while benchmark is running."""
        while self._running:
            await self._send_request()

    async def run(self) -> None:
        """Start benchmark with specified concurrency."""
        await super().run()
        self._running = True
        # Create multiple concurrent request senders
        senders = (self._send_indefinitely() for _ in range(self._concurrency))
        await asyncio.gather(*senders)
        self._stopped.set()

    async def stop(self) -> None:
        """Stop benchmark and wait for completion."""
        self._running = False
        await self._stopped.wait()
        await super().stop()

class StreamingAsyncBenchmarkClient(BenchmarkClient):
    """Benchmark client for bidirectional streaming RPC calls."""
    
    def __init__(
        self,
        address: str,
        config: control_pb2.ClientConfig,
        hist: histogram.Histogram,
    ):
        super().__init__(address, config, hist)
        self._running = None  # Flag to control benchmark execution
        self._stopped = asyncio.Event()  # Event to signal when stopped

    async def _one_streaming_call(self):
        """Handle a single bidirectional streaming call."""
        call = self._stub.StreamingCall()
        while self._running:
            start_time = time.time()
            await call.write(self._request)
            await call.read()
            self._record_query_time(time.time() - start_time)
        await call.done_writing()

    async def run(self):
        """Start benchmark with specified concurrency."""
        await super().run()
        self._running = True
        # Create multiple concurrent streaming calls
        senders = (self._one_streaming_call() for _ in range(self._concurrency))
        await asyncio.gather(*senders)
        self._stopped.set()

    async def stop(self):
        """Stop benchmark and wait for completion."""
        self._running = False
        await self._stopped.wait()
        await super().stop()

class ServerStreamingAsyncBenchmarkClient(BenchmarkClient):
    """Benchmark client for server streaming RPC calls."""
    
    def __init__(
        self,
        address: str,
        config: control_pb2.ClientConfig,
        hist: histogram.Histogram,
    ):
        super().__init__(address, config, hist)
        self._running = None  # Flag to control benchmark execution
        self._stopped = asyncio.Event()  # Event to signal when stopped

    async def _one_server_streaming_call(self):
        """Handle a single server streaming call."""
        call = self._stub.StreamingFromServer(self._request)
        while self._running:
            start_time = time.time()
            await call.read()
            self._record_query_time(time.time() - start_time)

    async def run(self):
        """Start benchmark with specified concurrency."""
        await super().run()
        self._running = True
        # Create multiple concurrent server streaming calls
        senders = (
            self._one_server_streaming_call() for _ in range(self._concurrency)
        )
        await asyncio.gather(*senders)
        self._stopped.set()

    async def stop(self):
        """Stop benchmark and wait for completion."""
        self._running = False
        await self._stopped.wait()
        await super().stop()
```