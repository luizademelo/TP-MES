Here's the commented version of the code:

```c++
# Copyright 2020 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""The AsyncIO version of the reflection servicer."""

from typing import AsyncIterable

import grpc
from grpc_reflection.v1alpha import reflection_pb2 as _reflection_pb2
from grpc_reflection.v1alpha._base import BaseReflectionServicer

class ReflectionServicer(BaseReflectionServicer):
    """Servicer handling RPCs for service statuses.
    
    This class provides server reflection functionality for gRPC services using AsyncIO.
    It implements the ServerReflection RPC method which allows clients to discover
    information about services available on the server.
    """

    async def ServerReflectionInfo(
        self,
        request_iterator: AsyncIterable[
            _reflection_pb2.ServerReflectionRequest
        ],
        unused_context,
    ) -> AsyncIterable[_reflection_pb2.ServerReflectionResponse]:
        """Handle ServerReflection RPC requests.
        
        Args:
            request_iterator: Async iterator of ServerReflectionRequest messages
            unused_context: gRPC context (unused in this implementation)
            
        Returns:
            Async iterator of ServerReflectionResponse messages
            
        This method processes different types of reflection requests:
        - File by filename
        - File containing a symbol
        - File containing an extension
        - All extension numbers of a type
        - List of services
        For invalid requests, returns an error response.
        """
        async for request in request_iterator:
            # Handle request for file by filename
            if request.HasField("file_by_filename"):
                yield self._file_by_filename(request, request.file_by_filename)
            # Handle request for file containing a specific symbol
            elif request.HasField("file_containing_symbol"):
                yield self._file_containing_symbol(
                    request, request.file_containing_symbol
                )
            # Handle request for file containing a specific extension
            elif request.HasField("file_containing_extension"):
                yield self._file_containing_extension(
                    request,
                    request.file_containing_extension.containing_type,
                    request.file_containing_extension.extension_number,
                )
            # Handle request for all extension numbers of a type
            elif request.HasField("all_extension_numbers_of_type"):
                yield self._all_extension_numbers_of_type(
                    request, request.all_extension_numbers_of_type
                )
            # Handle request to list all services
            elif request.HasField("list_services"):
                yield self._list_services(request)
            # Handle invalid/unknown request types
            else:
                yield _reflection_pb2.ServerReflectionResponse(
                    error_response=_reflection_pb2.ErrorResponse(
                        error_code=grpc.StatusCode.INVALID_ARGUMENT.value[0],
                        error_message=grpc.StatusCode.INVALID_ARGUMENT.value[
                            1
                        ].encode(),
                    ),
                    original_request=request,
                )

__all__ = [
    "ReflectionServicer",  # List of public interface elements exposed by this module
]
```

Key improvements made:
1. Added detailed class docstring explaining the purpose of the ReflectionServicer
2. Added comprehensive method docstring for ServerReflectionInfo explaining:
   - Parameters
   - Return value
   - Overall functionality
   - Types of requests handled
3. Added inline comments for each request type handler
4. Added comment explaining the purpose of __all__
5. Maintained all existing functionality while making it more understandable

The comments now provide clear guidance for future developers about:
- What this code does
- How it processes different request types
- Where to look for implementation details of specific handlers
- What to expect when invalid requests are received