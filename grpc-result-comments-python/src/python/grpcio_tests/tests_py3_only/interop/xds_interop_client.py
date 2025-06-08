Here's the commented version of the code:

```python
# Copyright 2020 The gRPC authors.
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

# Import necessary modules
import argparse
import collections
import concurrent.futures
import datetime
import logging
import signal
import threading
import time
from typing import (
    DefaultDict,
    Dict,
    FrozenSet,
    Iterable,
    List,
    Mapping,
    Sequence,
    Set,
    Tuple,
)

import grpc
from grpc import _typing as grpc_typing
import grpc_admin
from grpc_channelz.v1 import channelz
from grpc_csm_observability import CsmOpenTelemetryPlugin
from opentelemetry.exporter.prometheus import PrometheusMetricReader
from opentelemetry.sdk.metrics import MeterProvider
from prometheus_client import start_http_server

# Import protocol buffer definitions
from src.proto.grpc.testing import empty_pb2
from src.proto.grpc.testing import messages_pb2
from src.proto.grpc.testing import test_pb2
from src.proto.grpc.testing import test_pb2_grpc
from src.python.grpcio_tests.tests.fork import native_debug

# Install failure signal handler for debugging
native_debug.install_failure_signal_handler()

# Set up logging configuration
logger = logging.getLogger()
console_handler = logging.StreamHandler()
formatter = logging.Formatter(fmt="%(asctime)s: %(levelname)-8s %(message)s")
console_handler.setFormatter(formatter)
logger.addHandler(console_handler)

# Define supported RPC methods
_SUPPORTED_METHODS = (
    "UnaryCall",
    "EmptyCall",
)

# Mapping between method name formats
_METHOD_CAMEL_TO_CAPS_SNAKE = {
    "UnaryCall": "UNARY_CALL",
    "EmptyCall": "EMPTY_CALL",
}

# Mapping between method string names and enum values
_METHOD_STR_TO_ENUM = {
    "UnaryCall": messages_pb2.ClientConfigureRequest.UNARY_CALL,
    "EmptyCall": messages_pb2.ClientConfigureRequest.EMPTY_CALL,
}

# Reverse mapping from enum values to string names
_METHOD_ENUM_TO_STR = {v: k for k, v in _METHOD_STR_TO_ENUM.items()}

# Default Prometheus port for metrics
_PROMETHEUS_PORT = 9464

# Type alias for per-method metadata
PerMethodMetadataType = Mapping[str, Sequence[Tuple[str, str]]]

# Type alias for gRPC call that also behaves like a Future
class FutureFromCallType(grpc.Call, grpc.Future):
    pass

# Timeout for configuration changes
_CONFIG_CHANGE_TIMEOUT = datetime.timedelta(milliseconds=500)

class _StatsWatcher:
    """Tracks statistics for a range of RPCs."""
    
    def __init__(self, start: int, end: int, metadata_keys: Iterable[str]):
        """
        Initialize a stats watcher for RPCs in the range [start, end).
        
        Args:
            start: First RPC ID to watch
            end: First RPC ID to NOT watch (exclusive upper bound)
            metadata_keys: Metadata keys to collect for watched RPCs
        """
        self._start = start
        self._end = end
        self._rpcs_needed = end - start  # Number of RPCs we expect to see
        self._rpcs_by_peer = collections.defaultdict(int)  # RPC counts by peer
        self._rpcs_by_method = collections.defaultdict(
            lambda: collections.defaultdict(int)
        )  # Nested dict: method -> peer -> count
        self._condition = threading.Condition()  # For thread synchronization
        self._no_remote_peer = 0  # Count of RPCs with no peer info
        self._metadata_keys = frozenset(
            self._sanitize_metadata_key(key) for key in metadata_keys
        )  # Normalized metadata keys to collect
        self._include_all_metadata = "*" in self._metadata_keys  # Flag to collect all metadata
        self._metadata_by_peer = collections.defaultdict(
            messages_pb2.LoadBalancerStatsResponse.MetadataByPeer
        )  # Collected metadata by peer

    @classmethod
    def _sanitize_metadata_key(cls, metadata_key: str) -> str:
        """Normalize metadata key by stripping whitespace and converting to lowercase."""
        return metadata_key.strip().lower()

    def _add_metadata(
        self,
        rpc_metadata: messages_pb2.LoadBalancerStatsResponse.RpcMetadata,
        metadata_to_add: grpc_typing.MetadataType,
        metadata_type: messages_pb2.LoadBalancerStatsResponse.MetadataType,
    ) -> None:
        """
        Add relevant metadata to the RPC metadata collection.
        
        Args:
            rpc_metadata: Proto message to store collected metadata
            metadata_to_add: Metadata to potentially add
            metadata_type: Type of metadata (initial or trailing)
        """
        for key, value in metadata_to_add:
            if (
                self._include_all_metadata
                or self._sanitize_metadata_key(key) in self._metadata_keys
            ):
                rpc_metadata.metadata.append(
                    messages_pb2.LoadBalancerStatsResponse.MetadataEntry(
                        key=key, value=value, type=metadata_type
                    )
                )

    def on_rpc_complete(
        self,
        request_id: int,
        peer: str,
        method: str,
        *,
        initial_metadata: grpc_typing.MetadataType,
        trailing_metadata: grpc_typing.MetadataType,
    ) -> None:
        """Records statistics for a single RPC."""
        if self._start <= request_id < self._end:
            with self._condition:
                if not peer:
                    self._no_remote_peer += 1
                else:
                    # Update counts for this peer and method
                    self._rpcs_by_peer[peer] += 1
                    self._rpcs_by_method[method][peer] += 1
                    
                    # Collect metadata if requested
                    if self._metadata_keys:
                        rpc_metadata = (
                            messages_pb2.LoadBalancerStatsResponse.RpcMetadata()
                        )
                        self._add_metadata(
                            rpc_metadata,
                            initial_metadata,
                            messages_pb2.LoadBalancerStatsResponse.MetadataType.INITIAL,
                        )
                        self._add_metadata(
                            rpc_metadata,
                            trailing_metadata,
                            messages_pb2.LoadBalancerStatsResponse.MetadataType.TRAILING,
                        )
                        self._metadata_by_peer[peer].rpc_metadata.append(
                            rpc_metadata
                        )
                self._rpcs_needed -= 1
                self._condition.notify()  # Wake up waiting threads

    def await_rpc_stats_response(
        self, timeout_sec: int
    ) -> messages_pb2.LoadBalancerStatsResponse:
        """
        Blocks until a full response has been collected or timeout occurs.
        
        Returns:
            LoadBalancerStatsResponse containing collected statistics
        """
        with self._condition:
            # Wait until all expected RPCs complete or timeout
            self._condition.wait_for(
                lambda: not self._rpcs_needed, timeout=float(timeout_sec)
            
            # Build response message
            response = messages_pb2.LoadBalancerStatsResponse()
            for peer, count in self._rpcs_by_peer.items():
                response.rpcs_by_peer[peer] = count
            for method, count_by_peer in self._rpcs_by_method.items():
                for peer, count in count_by_peer.items():
                    response.rpcs_by_method[method].rpcs_by_peer[peer] = count
            for peer, metadata_by_peer in self._metadata_by_peer.items():
                response.metadatas_by_peer[peer].CopyFrom(metadata_by_peer)
            response.num_failures = self._no_remote_peer + self._rpcs_needed
        return response

# Global state variables
_global_lock = threading.Lock()  # Protects access to global state
_stop_event = threading.Event()  # Event to signal shutdown
_global_rpc_id: int = 0  # Counter for RPC IDs
_watchers: Set[_StatsWatcher] = set()  # Active stats watchers
_global_server = None  # gRPC server instance

# Global RPC statistics
_global_rpcs_started: Mapping[str, int] = collections.defaultdict(int)
_global_rpcs_succeeded: Mapping[str, int] = collections.defaultdict(int)
_global_rpcs_failed: Mapping[str, int] = collections.defaultdict(int)

# RPC status code counts by method
_global_rpc_statuses: Mapping[str, Mapping[int, int]] = collections.defaultdict(
    lambda: collections.defaultdict(int)
)

def _handle_sigint(sig, frame) -> None:
    """Signal handler for graceful shutdown on SIGINT."""
    logger.warning("Received SIGINT")
    _stop_event.set()
    _global_server.stop(None)

class _LoadBalancerStatsServicer(
    test_pb2_grpc.LoadBalancerStatsServiceServicer
):
    """gRPC servicer for load balancer statistics."""
    
    def __init__(self):
        super(_LoadBalancerStatsServicer).__init__()

    def GetClientStats(
        self,
        request: messages_pb2.LoadBalancerStatsRequest,
        context: grpc.ServicerContext,
    ) -> messages_pb2.LoadBalancerStatsResponse:
        """Handles request for load balancer statistics."""
        logger.info("Received stats request.")
        start = None
        end = None
        watcher = None
        with _global_lock:
            # Set up watcher for the requested RPC range
            start = _global_rpc_id + 1
            end = start + request.num_rpcs
            watcher = _StatsWatcher(start, end, request.metadata_keys)
            _watchers.add(watcher)
        
        # Wait for stats to be collected
        response = watcher.await_rpc_stats_response(request.timeout_sec)
        
        with _global_lock:
            _watchers.remove(watcher)
        logger.info("Returning stats response: %s", response)
        return response

    def GetClientAccumulatedStats(
        self,
        request: messages_pb2.LoadBalancerAccumulatedStatsRequest,
        context: grpc.ServicerContext,
    ) -> messages_pb2.LoadBalancerAccumulatedStatsResponse:
        """Handles request for cumulative statistics."""
        logger.info("Received cumulative stats request.")
        response = messages_pb2.LoadBalancerAccumulatedStatsResponse()
        with _global_lock:
            # Populate response with accumulated stats
            for method in _SUPPORTED_METHODS:
                caps_method = _METHOD_CAMEL_TO_CAPS_SNAKE[method]
                response.num_rpcs_started_by_method[
                    caps_method
                ] = _global_rpcs_started[method]
                response.num_rpcs_succeeded_by_method[
                    caps_method
                ] = _global_rpcs_succeeded[method]
                response.num_rpcs_failed_by_method[
                    caps_method
                ] = _global_rpcs_failed[method]
                response.stats_per_method[
                    caps_method
                ].rpcs_started = _global_rpcs_started[method]
                for code, count in _global_rpc_statuses[method].items():
                    response.stats_per_method[caps_method].result[code] = count
        logger.info("Returning cumulative stats response.")
        return response

def _start_rpc(
    method: str,
    metadata: Sequence[Tuple[str, str]],
    request_id: int,
    stub: test_pb2_grpc.TestServiceStub,
    timeout: float,
    futures: Mapping[int, Tuple[FutureFromCallType, str]],
    request_payload_size: int,
    response_payload_size: int,
) -> None:
    """Initiates an RPC call."""
    logger.debug(f"Sending {method} request to backend: {request_id}")
    if method == "UnaryCall":
        # Prepare request for UnaryCall
        request = messages_pb2.SimpleRequest(
            response_type=messages_pb2.COMPRESSABLE,
            response_size=response_payload_size,
            payload=messages_pb2.Payload(body=b"0" * request_payload_size),
        )
        future = stub.UnaryCall.future(
            request, metadata=metadata, timeout=timeout
        )
    elif method == "EmptyCall":
        # Validate payload sizes for EmptyCall
        if request_payload_size > 0:
            logger.error(
                f"request_payload_size should not be set for EMPTY_CALL"
            )
        if response_payload_size > 0:
            logger.error(
                f"response_payload_size should not be set for EMPTY_CALL"
            )
        future = stub.EmptyCall.future(
            empty_pb2.Empty(), metadata=metadata, timeout=timeout
        )
    else:
        raise ValueError(f"Unrecognized method '{method}'.")
    futures[request_id] = (future, method)

def _on_rpc_done(
    rpc_id: int, future: FutureFromCallType, method: str, print_response: bool
) -> None:
    """Callback for completed RPCs."""
    exception = future.exception()
    hostname = ""
    with _global_lock:
        # Record status code
        _global_rpc_statuses[method][future.code().value[0]] += 1
    
    if exception is not None:
        # Handle failed RPC
        with _global_lock:
            _global_rpcs_failed[method] += 1
        if exception.code() == grpc.StatusCode.DEADLINE_EXCEEDED:
            logger.error(f"RPC {rpc_id} timed out")
        else:
            logger.error(exception)
    else:
        # Handle successful RPC
        response = future.result()
        hostname = None
        # Extract hostname from metadata or response
        for metadatum in future.initial_metadata():
            if metadatum[0] == "hostname":
                hostname = metadatum[1]
                break
        else:
            hostname = response.hostname
        
        # Update success/failure counts
        if future.code() == grpc.StatusCode.OK:
            with _global_lock:
                _global_rpcs_succeeded[method] += 1
        else:
            with _global_lock:
                _global_rpcs_failed[method] += 1
        
        # Log response if requested
        if print_response:
            if future.code() == grpc.StatusCode.OK:
                logger.debug("Successful response.")
            else:
                logger.debug(f"RPC failed: {rpc_id}")
    
    # Notify all watchers about completed RPC
    with _global_lock:
        for watcher in _watchers:
            watcher.on_rpc_complete(
                rpc_id,
                hostname,
                method,
                initial_metadata=future.initial_metadata(),
                trailing_metadata=future.trailing_metadata(),
            )

def _remove_completed_rpcs(
    rpc_futures: Mapping[int, FutureFromCallType], print_response: bool
) -> None:
    """Cleans up completed RPCs from the futures dictionary."""
    logger.debug("Removing completed RPCs")
    done = []
    # Find all completed futures
    for future_id, (future, method) in rpc_futures.items():
        if future.done():
            _on_rpc_done(future_id, future, method, args.print_response)
            done.append(future_id)
    # Remove completed futures
    for rpc_id in done:
        del rpc_futures[rpc_id]

def _cancel_all_rpcs(futures: Mapping[int, Tuple[grpc.Future, str]]) -> None:
    """Cancels all outstanding RPCs."""
    logger.info("Cancelling all remaining RPCs")
    for future, _ in futures.values():
        future.cancel()

class _ChannelConfiguration:
    """Configuration for a single client channel.

    Instances of this class are meant to be dealt with as PODs. That is,
    data member should be accessed directly. This class is not thread-safe.
    When accessing any of its members, the lock member should be held.
    """

    def __init__(
        self,
        method: str,
        metadata: Sequence[Tuple[str, str]],
        qps: int,
        server: str,
        rpc_timeout_sec: int,
        print_response: bool,
        secure_mode: bool,
        request_payload_size: int,
        response_payload_size: int,
    ):
        """Initialize channel configuration."""
        self.condition = threading.Condition()  # For thread synchronization

        # Configuration parameters
        self.method = method
        self.metadata = metadata
        self.qps = qps
        self.server = server
        self.rpc_timeout_sec = rpc_timeout_sec
        self.print_response = print_response
        self.secure_mode = secure_mode
        self.response_payload_size = response_payload_size
        self.request_payload_size = request_payload_size

def _run_single_channel(config: _ChannelConfiguration) -> None:
    """Runs RPCs on a single channel according to the configuration."""
    global _global_rpc_id
    with config.condition:
        server = config.server
    
    # Create channel based on security mode
    channel = None
    if config.secure_mode:
        fallback_creds = grpc.experimental.insecure_channel_credentials()
        channel_creds = grpc.xds_channel_credentials(fallback_creds)
        channel = grpc.secure_channel(server, channel_creds)
    else:
        channel = grpc.insecure_channel(server)
    
    with channel:
        stub = test_pb2_grpc.Test