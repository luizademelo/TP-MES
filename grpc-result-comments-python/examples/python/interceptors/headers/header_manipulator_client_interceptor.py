Here's the commented version of the code:

```c++
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Interceptor that adds headers to outgoing requests."""

import collections
import generic_client_interceptor
import grpc

# A named tuple class that extends grpc.ClientCallDetails, representing
# the details of a gRPC client call including method, timeout, metadata, and credentials
class _ClientCallDetails(
    collections.namedtuple(
        "_ClientCallDetails", ("method", "timeout", "metadata", "credentials")
    ),
    grpc.ClientCallDetails,
):
    pass

# Creates a gRPC interceptor that adds a specified header to outgoing requests
# Args:
#     header: The header key to add
#     value: The header value to add
# Returns:
#     A gRPC interceptor that will add the specified header to all outgoing requests
def header_adder_interceptor(header, value):
    # The actual interceptor function that will be called for each request
    def intercept_call(
        client_call_details,
        request_iterator,
        request_streaming,
        response_streaming,
    ):
        # Initialize metadata list
        metadata = []
        # If the original call has metadata, copy it
        if client_call_details.metadata is not None:
            metadata = list(client_call_details.metadata)
        # Add our new header to the metadata
        metadata.append(
            (
                header,
                value,
            )
        )
        # Create new call details with updated metadata
        client_call_details = _ClientCallDetails(
            client_call_details.method,
            client_call_details.timeout,
            metadata,
            client_call_details.credentials,
        )
        # Return the modified call details and request iterator
        # (None indicates we're not providing a custom continuation)
        return client_call_details, request_iterator, None

    # Create and return the actual interceptor using the generic interceptor factory
    return generic_client_interceptor.create(intercept_call)
```