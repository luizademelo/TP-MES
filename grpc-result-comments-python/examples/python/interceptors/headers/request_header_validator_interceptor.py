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
"""Interceptor that ensures a specific header is present."""

import grpc

def _unary_unary_rpc_terminator(code, details):
    """Creates a gRPC method handler that aborts RPCs with given status code and details.
    
    Args:
        code: gRPC status code to abort with
        details: Error message/details to include in the abort
        
    Returns:
        A gRPC unary-unary method handler that always aborts requests
    """
    def terminate(ignored_request, context):
        """Termination handler that aborts the RPC immediately."""
        context.abort(code, details)

    return grpc.unary_unary_rpc_method_handler(terminate)

class RequestHeaderValidatorInterceptor(grpc.ServerInterceptor):
    """gRPC interceptor that validates the presence of a specific header-value pair.
    
    If the required header is not present, the RPC is aborted with the configured
    error code and message.
    """
    
    def __init__(self, header, value, code, details):
        """Initialize the interceptor with validation requirements.
        
        Args:
            header: Header name to validate
            value: Expected header value
            code: gRPC status code to return if validation fails
            details: Error message to return if validation fails
        """
        self._header = header
        self._value = value
        self._terminator = _unary_unary_rpc_terminator(code, details)

    def intercept_service(self, continuation, handler_call_details):
        """Intercepts incoming RPCs to validate the required header.
        
        Args:
            continuation: Function to continue processing if validation passes
            handler_call_details: gRPC call details including metadata
            
        Returns:
            Either continues the RPC chain or terminates with error
        """
        if (
            self._header,
            self._value,
        ) in handler_call_details.invocation_metadata:
            # Header validation passed - continue processing
            return continuation(handler_call_details)
        else:
            # Header validation failed - abort the RPC
            return self._terminator
```