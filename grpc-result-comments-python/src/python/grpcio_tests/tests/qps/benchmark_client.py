Here's the commented version of the code:

```python
# Copyright 2016 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""Defines test client behaviors (UNARY/STREAMING) (SYNC/ASYNC)."""

import abc
from concurrent import futures
import queue
import threading
import time

import grpc

from src.proto.grpc.testing import benchmark_service_pb2_grpc
from src.proto.grpc.testing import messages_pb2
from tests.unit import resources
from tests.unit import test_common

# Default timeout set to 24 hours (in seconds)
_TIMEOUT = 60 * 60 * 24

class GenericStub(object):
    """Generic gRPC stub that provides unary and streaming RPC methods."""
    
    def __init__(self, channel):
        """Initialize the stub with channel methods.
        
        Args:
            channel: gRPC channel to create stubs for
        """
        # Unary RPC method
        self.UnaryCall = channel.unary_unary(
            "/grpc.testing.BenchmarkService/UnaryCall",
            _registered_method=True,
        )
        # Server streaming RPC method
        self.StreamingFromServer = channel.unary_stream(
            "/grpc.testing.BenchmarkService/StreamingFromServer",
            _registered_method=True,
        )
        # Bidirectional streaming RPC method
        self.StreamingCall = channel.stream_stream(
            "/grpc.testing.BenchmarkService/StreamingCall",
            _registered_method=True,
        )

class BenchmarkClient:
    """Base class for benchmark clients that provides common functionality.
    
    This abstract class defines the interface for benchmark clients and implements
    common initialization and response handling logic.
    """
    __metaclass__ = abc.ABCMeta

    def __init__(self, server, config, hist):
        """Initialize the benchmark client.
        
        Args:
            server: Server address to connect to
            config: Configuration for the benchmark
            hist: Histogram to record latency measurements
        """
        # Create secure or insecure channel based on config
        if config.HasField("security_params"):
            creds = grpc.ssl_channel_credentials(
                resources.test_root_certificates()
            )
            channel = test_common.test_secure_channel(
                server, creds, config.security_params.server_host_override
            )
        else:
            channel = grpc.insecure_channel(server)

        # Wait for channel to be ready
        grpc.channel_ready_future(channel).result()

        # Configure request payload based on config
        if config.payload_config.WhichOneof("payload") == "simple_params":
            self._generic = False
            self._stub = benchmark_service_pb2_grpc.BenchmarkServiceStub(
                channel
            )
            # Create simple request with specified size
            payload = messages_pb2.Payload(
                body=bytes(b"\0" * config.payload_config.simple_params.req_size)
            )
            self._request = messages_pb2.SimpleRequest(
                payload=payload,
                response_size=config.payload_config.simple_params.resp_size,
            )
        else:
            self._generic = True
            self._stub = GenericStub(channel)
            # Create byte buffer request with specified size
            self._request = bytes(
                b"\0" * config.payload_config.bytebuf_params.req_size
            )

        self._hist = hist  # Histogram for recording latencies
        self._response_callbacks = []  # List of response callbacks

    def add_response_callback(self, callback):
        """Add a callback to be invoked when a response is received.
        
        Args:
            callback: Function to be called as callback(client, query_time)
        """
        self._response_callbacks.append(callback)

    @abc.abstractmethod
    def send_request(self):
        """Abstract method for sending requests (non-blocking)."""
        raise NotImplementedError()

    def start(self):
        """Optional method to start the client (default does nothing)."""
        pass

    def stop(self):
        """Optional method to stop the client (default does nothing)."""
        pass

    def _handle_response(self, client, query_time):
        """Handle response by recording latency and invoking callbacks.
        
        Args:
            client: The client instance
            query_time: Time taken for the request-response cycle (in seconds)
        """
        # Record latency in nanoseconds
        self._hist.add(query_time * 1e9)
        # Invoke all registered callbacks
        for callback in self._response_callbacks:
            callback(client, query_time)

class UnarySyncBenchmarkClient(BenchmarkClient):
    """Synchronous unary RPC benchmark client."""
    
    def __init__(self, server, config, hist):
        """Initialize synchronous unary client with thread pool."""
        super(UnarySyncBenchmarkClient, self).__init__(server, config, hist)
        # Create thread pool for concurrent RPCs
        self._pool = futures.ThreadPoolExecutor(
            max_workers=config.outstanding_rpcs_per_channel
        )

    def send_request(self):
        """Submit a new request to the thread pool."""
        self._pool.submit(self._dispatch_request)

    def stop(self):
        """Shutdown the thread pool and clean up."""
        self._pool.shutdown(wait=True)
        self._stub = None

    def _dispatch_request(self):
        """Execute a single unary RPC and record timing."""
        start_time = time.time()
        self._stub.UnaryCall(self._request, _TIMEOUT)
        end_time = time.time()
        self._handle_response(self, end_time - start_time)

class UnaryAsyncBenchmarkClient(BenchmarkClient):
    """Asynchronous unary RPC benchmark client."""
    
    def send_request(self):
        """Send an async unary RPC and register callback."""
        start_time = time.time()
        # Start async RPC
        response_future = self._stub.UnaryCall.future(self._request, _TIMEOUT)
        # Register callback for when response is received
        response_future.add_done_callback(
            lambda resp: self._response_received(start_time, resp)
        )

    def _response_received(self, start_time, resp):
        """Callback for completed async RPC that records timing."""
        resp.result()  # Get result (may raise exception)
        end_time = time.time()
        self._handle_response(self, end_time - start_time)

    def stop(self):
        """Clean up the client."""
        self._stub = None

class _SyncStream(object):
    """Helper class for managing synchronous streaming RPCs."""
    
    def __init__(self, stub, generic, request, handle_response):
        """Initialize streaming RPC helper.
        
        Args:
            stub: gRPC stub
            generic: Whether to use generic stub
            request: Request template
            handle_response: Callback for handling responses
        """
        self._stub = stub
        self._generic = generic
        self._request = request
        self._handle_response = handle_response
        self._is_streaming = False  # Streaming state flag
        self._request_queue = queue.Queue()  # Queue for outgoing requests
        self._send_time_queue = queue.Queue()  # Queue for tracking send times

    def send_request(self):
        """Enqueue a new request to be sent."""
        self._send_time_queue.put(time.time())
        self._request_queue.put(self._request)

    def start(self):
        """Start the streaming RPC and response processing."""
        self._is_streaming = True
        # Start bidirectional streaming RPC
        response_stream = self._stub.StreamingCall(
            self._request_generator(), _TIMEOUT
        )
        # Process responses as they arrive
        for _ in response_stream:
            self._handle_response(
                self, time.time() - self._send_time_queue.get_nowait()
            )

    def stop(self):
        """Stop the streaming RPC."""
        self._is_streaming = False

    def _request_generator(self):
        """Generator that yields requests from the queue."""
        while self._is_streaming:
            try:
                # Get next request from queue with timeout
                request = self._request_queue.get(block=True, timeout=1.0)
                yield request
            except queue.Empty:
                pass

class StreamingSyncBenchmarkClient(BenchmarkClient):
    """Synchronous streaming RPC benchmark client."""
    
    def __init__(self, server, config, hist):
        """Initialize with multiple streaming channels."""
        super(StreamingSyncBenchmarkClient, self).__init__(server, config, hist)
        # Create thread pool for concurrent streams
        self._pool = futures.ThreadPoolExecutor(
            max_workers=config.outstanding_rpcs_per_channel
        )
        # Create multiple streams for load balancing
        self._streams = [
            _SyncStream(
                self._stub, self._generic, self._request, self._handle_response
            )
            for _ in range(config.outstanding_rpcs_per_channel)
        ]
        self._curr_stream = 0  # Round-robin stream selector

    def send_request(self):
        """Send request via round-robin to available streams."""
        self._streams[self._curr_stream].send_request()
        self._curr_stream = (self._curr_stream + 1) % len(self._streams)

    def start(self):
        """Start all streaming RPCs."""
        for stream in self._streams:
            self._pool.submit(stream.start)

    def stop(self):
        """Stop all streams and clean up."""
        for stream in self._streams:
            stream.stop()
        self._pool.shutdown(wait=True)
        self._stub = None

class ServerStreamingSyncBenchmarkClient(BenchmarkClient):
    """Synchronous server streaming RPC benchmark client."""
    
    def __init__(self, server, config, hist):
        """Initialize server streaming client."""
        super(ServerStreamingSyncBenchmarkClient, self).__init__(
            server, config, hist
        )
        # Configure thread pool based on RPC count
        if config.outstanding_rpcs_per_channel == 1:
            self._pool = None  # No pool needed for single RPC
        else:
            self._pool = futures.ThreadPoolExecutor(
                max_workers=config.outstanding_rpcs_per_channel
            )
        self._rpcs = []  # Active RPC list
        self._sender = None  # Thread for single RPC case

    def send_request(self):
        """Start a new server streaming RPC."""
        if self._pool is None:
            # Single RPC case - use dedicated thread
            self._sender = threading.Thread(
                target=self._one_stream_streaming_rpc, daemon=True
            )
            self._sender.start()
        else:
            # Multiple RPC case - use thread pool
            self._pool.submit(self._one_stream_streaming_rpc)

    def _one_stream_streaming_rpc(self):
        """Execute a single server streaming RPC and process responses."""
        response_stream = self._stub.StreamingFromServer(
            self._request, _TIMEOUT
        )
        self._rpcs.append(response_stream)
        start_time = time.time()
        # Process each response as it arrives
        for _ in response_stream:
            self._handle_response(self, time.time() - start_time)
            start_time = time.time()

    def stop(self):
        """Cancel all RPCs and clean up."""
        for call in self._rpcs:
            call.cancel()
        if self._sender is not None:
            self._sender.join()
        if self._pool is not None:
            self._pool.shutdown(wait=False)
        self._stub = None
```