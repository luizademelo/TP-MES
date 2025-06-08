Here's the commented version of the code:

```c++
# Copyright 2015 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Reference implementation for health checking in gRPC Python."""

# Import required modules
import collections  # For deque data structure
import sys          # For version checking
import threading    # For thread synchronization

import grpc  # gRPC core module
from grpc_health.v1 import health_pb2 as _health_pb2  # Health check protobuf messages
from grpc_health.v1 import health_pb2_grpc as _health_pb2_grpc  # Health check gRPC services

# Conditional import for async support in Python 3.6+
if sys.version_info[0] >= 3 and sys.version_info[1] >= 6:
    from . import _async as aio

# Constant for the full service name of the health check service
SERVICE_NAME = _health_pb2.DESCRIPTOR.services_by_name["Health"].full_name

# Constant representing the overall health check (empty string service name)
OVERALL_HEALTH = ""

class _Watcher:
    """Helper class for watching health status changes in a blocking manner."""
    
    def __init__(self):
        """Initialize the watcher with condition variable, response queue, and open state."""
        self._condition = threading.Condition()  # Thread synchronization primitive
        self._responses = collections.deque()    # Queue for storing responses
        self._open = True                        # Flag indicating if watcher is active

    def __iter__(self):
        """Make the watcher iterable."""
        return self

    def _next(self):
        """Internal method to get the next response in a thread-safe manner."""
        with self._condition:
            # Wait while there are no responses and watcher is still open
            while not self._responses and self._open:
                self._condition.wait()
            # Return response if available, otherwise stop iteration
            if self._responses:
                return self._responses.popleft()
            else:
                raise StopIteration()

    def next(self):
        """Python 2 compatible iterator method."""
        return self._next()

    def __next__(self):
        """Python 3 compatible iterator method."""
        return self._next()

    def add(self, response):
        """Add a new response to the watcher queue and notify waiting threads."""
        with self._condition:
            self._responses.append(response)
            self._condition.notify()

    def close(self):
        """Close the watcher and notify any waiting threads."""
        with self._condition:
            self._open = False
            self._condition.notify()

def _watcher_to_send_response_callback_adapter(watcher):
    """Adapter function to convert a watcher to a send_response callback.
    
    Args:
        watcher: The _Watcher instance to adapt
        
    Returns:
        A callback function that either adds responses to the watcher or closes it
    """
    def send_response_callback(response):
        if response is None:
            watcher.close()
        else:
            watcher.add(response)

    return send_response_callback

class HealthServicer(_health_pb2_grpc.HealthServicer):
    """Servicer handling RPCs for service statuses."""

    def __init__(
        self, experimental_non_blocking=True, experimental_thread_pool=None
    ):
        """Initialize the health servicer with thread synchronization and state tracking.
        
        Args:
            experimental_non_blocking: Flag for experimental non-blocking behavior
            experimental_thread_pool: Optional thread pool for experimental features
        """
        self._lock = threading.RLock()  # Reentrant lock for thread safety
        # Default server status with overall health set to SERVING
        self._server_status = {"": _health_pb2.HealthCheckResponse.SERVING}
        # Dictionary to track callbacks for each service being watched
        self._send_response_callbacks = {}
        # Set experimental flags on the Watch method
        self.Watch.__func__.experimental_non_blocking = (
            experimental_non_blocking
        )
        self.Watch.__func__.experimental_thread_pool = experimental_thread_pool
        self._gracefully_shutting_down = False  # Flag for shutdown state

    def _on_close_callback(self, send_response_callback, service):
        """Create a callback to clean up when a watch is closed.
        
        Args:
            send_response_callback: The callback to remove
            service: The service being watched
            
        Returns:
            A callback function that removes the specified callback
        """
        def callback():
            with self._lock:
                self._send_response_callbacks[service].remove(
                    send_response_callback
                )
            send_response_callback(None)

        return callback

    def Check(self, request, context):
        """Handle Check RPC - returns current health status of requested service.
        
        Args:
            request: The health check request containing service name
            context: gRPC context
            
        Returns:
            HealthCheckResponse with current status or NOT_FOUND error
        """
        with self._lock:
            status = self._server_status.get(request.service)
            if status is None:
                context.set_code(grpc.StatusCode.NOT_FOUND)
                return _health_pb2.HealthCheckResponse()
            else:
                return _health_pb2.HealthCheckResponse(status=status)

    def Watch(self, request, context, send_response_callback=None):
        """Handle Watch RPC - streams health status changes for requested service.
        
        Args:
            request: The health watch request containing service name
            context: gRPC context
            send_response_callback: Optional callback for async responses
            
        Returns:
            A blocking watcher if no callback was provided, None otherwise
        """
        blocking_watcher = None
        # Create a blocking watcher if no callback was provided
        if send_response_callback is None:
            blocking_watcher = _Watcher()
            send_response_callback = _watcher_to_send_response_callback_adapter(
                blocking_watcher
            )
        
        service = request.service
        with self._lock:
            # Get current status or default to SERVICE_UNKNOWN
            status = self._server_status.get(service)
            if status is None:
                status = _health_pb2.HealthCheckResponse.SERVICE_UNKNOWN
            
            # Send initial status
            send_response_callback(
                _health_pb2.HealthCheckResponse(status=status)
            
            # Register callback for future updates
            if service not in self._send_response_callbacks:
                self._send_response_callbacks[service] = set()
            self._send_response_callbacks[service].add(send_response_callback)
            
            # Add cleanup callback for when the watch ends
            context.add_callback(
                self._on_close_callback(send_response_callback, service)
            )
        
        return blocking_watcher

    def set(self, service, status):
        """Sets the status of a service.
        
        Args:
          service: string, the name of the service.
          status: HealthCheckResponse.status enum value indicating the status of
            the service
        """
        with self._lock:
            if self._gracefully_shutting_down:
                return
            else:
                # Update status and notify all watchers
                self._server_status[service] = status
                if service in self._send_response_callbacks:
                    for send_response_callback in self._send_response_callbacks[
                        service
                    ]:
                        send_response_callback(
                            _health_pb2.HealthCheckResponse(status=status)
                        )

    def enter_graceful_shutdown(self):
        """Permanently sets the status of all services to NOT_SERVING.
        
        This should be invoked when the server is entering a graceful shutdown
        period. After this method is invoked, future attempts to set the status
        of a service will be ignored.
        
        This is an EXPERIMENTAL API.
        """
        with self._lock:
            if self._gracefully_shutting_down:
                return
            else:
                # Set all services to NOT_SERVING and prevent further changes
                for service in self._server_status:
                    self.set(
                        service, _health_pb2.HealthCheckResponse.NOT_SERVING
                    )
                self._gracefully_shutting_down = True
```