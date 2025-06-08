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
"""Reference implementation for reflection in gRPC Python."""

import sys

import grpc
from grpc_reflection.v1alpha import reflection_pb2 as _reflection_pb2
from grpc_reflection.v1alpha import reflection_pb2_grpc as _reflection_pb2_grpc
from grpc_reflection.v1alpha._base import BaseReflectionServicer

# Full service name for the ServerReflection service from the protobuf descriptor
SERVICE_NAME = _reflection_pb2.DESCRIPTOR.services_by_name[
    "ServerReflection"
].full_name

class ReflectionServicer(BaseReflectionServicer):
    """Servicer handling RPCs for service statuses."""

    def ServerReflectionInfo(self, request_iterator, context):
        """
        Handles ServerReflection RPC requests.
        
        Args:
            request_iterator: Iterator of incoming ServerReflectionRequest objects
            context: RPC context
            
        Yields:
            ServerReflectionResponse objects corresponding to each request
        """
        for request in request_iterator:
            # Handle different types of reflection requests
            if request.HasField("file_by_filename"):
                # Return file descriptor for requested filename
                yield self._file_by_filename(request, request.file_by_filename)
            elif request.HasField("file_containing_symbol"):
                # Return file descriptor containing requested symbol
                yield self._file_containing_symbol(
                    request, request.file_containing_symbol
                )
            elif request.HasField("file_containing_extension"):
                # Return file descriptor containing requested extension
                yield self._file_containing_extension(
                    request,
                    request.file_containing_extension.containing_type,
                    request.file_containing_extension.extension_number,
                )
            elif request.HasField("all_extension_numbers_of_type"):
                # Return all extension numbers for requested type
                yield self._all_extension_numbers_of_type(
                    request, request.all_extension_numbers_of_type
                )
            elif request.HasField("list_services"):
                # Return list of all services
                yield self._list_services(request)
            else:
                # Invalid request - return error response
                yield _reflection_pb2.ServerReflectionResponse(
                    error_response=_reflection_pb2.ErrorResponse(
                        error_code=grpc.StatusCode.INVALID_ARGUMENT.value[0],
                        error_message=grpc.StatusCode.INVALID_ARGUMENT.value[
                            1
                        ].encode(),
                    ),
                    original_request=request,
                )

# Documentation string for enable_server_reflection function
_enable_server_reflection_doc = """Enables server reflection on a server.

Args:
    service_names: Iterable of fully-qualified service names available.
    server: grpc.Server to which reflection service will be added.
    pool: DescriptorPool object to use (descriptor_pool.Default() if None).
"""

# Python version check for async support (Python 3.6+)
if sys.version_info[0] >= 3 and sys.version_info[1] >= 6:
    # Import async components if available
    from grpc.experimental import aio as grpc_aio
    from . import _async as aio

    def enable_server_reflection(service_names, server, pool=None):
        """
        Adds reflection service to either synchronous or asynchronous server.
        
        Args:
            service_names: Iterable of service names to reflect
            server: grpc.Server or grpc.aio.Server instance
            pool: Optional descriptor pool
        """
        if isinstance(server, grpc_aio.Server):
            # Add async reflection servicer to async server
            _reflection_pb2_grpc.add_ServerReflectionServicer_to_server(
                aio.ReflectionServicer(service_names, pool=pool), server
            )
        else:
            # Add sync reflection servicer to sync server
            _reflection_pb2_grpc.add_ServerReflectionServicer_to_server(
                ReflectionServicer(service_names, pool=pool), server
            )

    enable_server_reflection.__doc__ = _enable_server_reflection_doc

    # Public API exports for Python 3.6+
    __all__ = [
        "SERVICE_NAME",
        "ReflectionServicer",
        "enable_server_reflection",
        "aio",  # Async module
    ]
else:
    # Synchronous-only implementation for Python versions < 3.6
    def enable_server_reflection(service_names, server, pool=None):
        """
        Adds reflection service to synchronous server.
        
        Args:
            service_names: Iterable of service names to reflect
            server: grpc.Server instance
            pool: Optional descriptor pool
        """
        _reflection_pb2_grpc.add_ServerReflectionServicer_to_server(
            ReflectionServicer(service_names, pool=pool), server
        )

    enable_server_reflection.__doc__ = _enable_server_reflection_doc

    # Public API exports for Python versions < 3.6
    __all__ = [
        "SERVICE_NAME",
        "ReflectionServicer",
        "enable_server_reflection",
    ]
```