Here's the commented version of the code:

```c++
# Copyright 2018 The gRPC Authors

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Reference implementation for status mapping in gRPC Python."""

import collections
import sys

from google.rpc import status_pb2  # Protocol buffers for rich error status
import grpc  # gRPC core library

from ._common import GRPC_DETAILS_METADATA_KEY  # Metadata key for status details
from ._common import code_to_grpc_status_code  # Converter between gRPC and status codes

# Custom status class that combines gRPC status with additional metadata
class _Status(
    collections.namedtuple("_Status", ("code", "details", "trailing_metadata")),
    grpc.Status,
):
    """Combines gRPC status information with trailing metadata.
    
    Inherits from both namedtuple (for immutable data storage) and grpc.Status.
    Contains:
        code: gRPC status code
        details: Human-readable status details
        trailing_metadata: Additional metadata sent with the status
    """
    pass

def from_call(call):
    """Returns a google.rpc.status.Status message corresponding to a given grpc.Call.

    This is an EXPERIMENTAL API.

    Args:
      call: A grpc.Call instance representing an RPC call.

    Returns:
      A google.rpc.status.Status message representing the status of the RPC,
      or None if no status metadata is present.

    Raises:
      ValueError: If the gRPC call's code or details are inconsistent with the
        status code and message inside of the google.rpc.status.Status.
    """
    # Return None if there's no trailing metadata
    if call.trailing_metadata() is None:
        return None
    
    # Search through metadata for the status details
    for key, value in call.trailing_metadata():
        if key == GRPC_DETAILS_METADATA_KEY:
            # Parse the status proto from the metadata value
            rich_status = status_pb2.Status.FromString(value)
            
            # Validate that the gRPC status code matches the proto status code
            if call.code().value[0] != rich_status.code:
                raise ValueError(
                    "Code in Status proto (%s) doesn't match status code (%s)"
                    % (code_to_grpc_status_code(rich_status.code), call.code())
                )
            
            # Validate that the gRPC details match the proto message
            if call.details() != rich_status.message:
                raise ValueError(
                    "Message in Status proto (%s) doesn't match status details"
                    " (%s)" % (rich_status.message, call.details())
                )
            
            return rich_status
    return None

def to_status(status):
    """Convert a google.rpc.status.Status message to grpc.Status.

    This is an EXPERIMENTAL API.

    Args:
      status: a google.rpc.status.Status message representing the non-OK status
        to terminate the RPC with and communicate it to the client.

    Returns:
      A grpc.Status instance containing:
        - The converted gRPC status code
        - The status message as details
        - The serialized status proto in trailing metadata
    """
    return _Status(
        code=code_to_grpc_status_code(status.code),  # Convert status code
        details=status.message,  # Use status message as details
        trailing_metadata=(
            (GRPC_DETAILS_METADATA_KEY, status.SerializeToString()),  # Include serialized proto
        ),
    )

# Public API exports
__all__ = [
    "from_call",  # Function to extract status from gRPC call
    "to_status",  # Function to convert status proto to gRPC status
]

# Conditionally import and expose async module for Python 3.6+
if sys.version_info[0] >= 3 and sys.version_info[1] >= 6:
    from . import _async as aio  # Asynchronous implementation

    __all__.append("aio")  # Add to public API
```