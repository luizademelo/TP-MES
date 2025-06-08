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
"""Reference implementation for health checking in gRPC Python."""

import asyncio
import collections
from typing import MutableMapping

import grpc
from grpc_health.v1 import health_pb2 as _health_pb2
from grpc_health.v1 import health_pb2_grpc as _health_pb2_grpc

class HealthServicer(_health_pb2_grpc.HealthServicer):
    """An AsyncIO implementation of health checking servicer."""

    # Dictionary mapping service names to their current health status
    _server_status: MutableMapping[
        str, "_health_pb2.HealthCheckResponse.ServingStatus"
    ]
    
    # Dictionary mapping service names to asyncio conditions for watch operations
    _server_watchers: MutableMapping[str, asyncio.Condition]
    
    # Flag indicating if the server is in graceful shutdown mode
    _gracefully_shutting_down: bool

    def __init__(self) -> None:
        """Initialize the health servicer with default status for empty service."""
        # Initialize with empty service name marked as SERVING
        self._server_status = {"": _health_pb2.HealthCheckResponse.SERVING}
        # Create defaultdict for conditions to synchronize watchers
        self._server_watchers = collections.defaultdict(asyncio.Condition)
        # Initialize graceful shutdown flag as False
        self._gracefully_shutting_down = False

    async def Check(
        self, request: _health_pb2.HealthCheckRequest, context
    ) -> None:
        """Implements the Check RPC method for immediate health status checking.
        
        Args:
            request: HealthCheckRequest containing service name to check
            context: gRPC context object
            
        Returns:
            HealthCheckResponse with current status of the service
            
        Raises:
            grpc.RpcError: If service is not found (NOT_FOUND status)
        """
        # Get current status for requested service
        status = self._server_status.get(request.service)

        if status is None:
            # Service not found - abort with NOT_FOUND status
            await context.abort(grpc.StatusCode.NOT_FOUND)
        else:
            # Return current status of the service
            return _health_pb2.HealthCheckResponse(status=status)

    async def Watch(
        self, request: _health_pb2.HealthCheckRequest, context
    ) -> None:
        """Implements the Watch RPC method for streaming health status updates.
        
        Args:
            request: HealthCheckRequest containing service name to watch
            context: gRPC context object
            
        Note:
            This method streams status updates whenever the service status changes.
            It continues until the connection is closed or the service is removed.
        """
        # Get or create condition variable for this service's watchers
        condition = self._server_watchers[request.service]
        last_status = None
        try:
            async with condition:
                while True:
                    # Get current status (default to SERVICE_UNKNOWN if not found)
                    status = self._server_status.get(
                        request.service,
                        _health_pb2.HealthCheckResponse.SERVICE_UNKNOWN,
                    )

                    # Only send update if status has changed
                    if status != last_status:
                        await context.write(
                            _health_pb2.HealthCheckResponse(status=status)
                        )
                    last_status = status

                    # Wait for status change notification
                    await condition.wait()
        finally:
            # Clean up watchers when connection ends
            if request.service in self._server_watchers:
                del self._server_watchers[request.service]

    async def _set(
        self,
        service: str,
        status: _health_pb2.HealthCheckResponse.ServingStatus,
    ) -> None:
        """Internal method to set service status and notify watchers.
        
        Args:
            service: Name of the service to update
            status: New health status for the service
        """
        if service in self._server_watchers:
            # If there are watchers, acquire lock and notify them
            condition = self._server_watchers.get(service)
            async with condition:
                self._server_status[service] = status
                condition.notify_all()
        else:
            # No watchers - just update status
            self._server_status[service] = status

    async def set(
        self,
        service: str,
        status: _health_pb2.HealthCheckResponse.ServingStatus,
    ) -> None:
        """Sets the status of a service.
        
        Args:
            service: string, the name of the service.
            status: HealthCheckResponse.status enum value indicating the status of
                the service
                
        Note:
            Does nothing if server is in graceful shutdown mode.
        """
        if self._gracefully_shutting_down:
            return
        else:
            await self._set(service, status)

    async def enter_graceful_shutdown(self) -> None:
        """Permanently sets the status of all services to NOT_SERVING.
        
        This should be invoked when the server is entering a graceful shutdown
        period. After this method is invoked, future attempts to set the status
        of a service will be ignored.
        """
        if self._gracefully_shutting_down:
            return
        else:
            self._gracefully_shutting_down = True
            # Update all services to NOT_SERVING status
            for service in self._server_status:
                await self._set(
                    service, _health_pb2.HealthCheckResponse.NOT_SERVING
                )
```