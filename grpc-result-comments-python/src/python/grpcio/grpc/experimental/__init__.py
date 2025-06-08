Here's the commented version of the code:

```c++
# Copyright 2018 gRPC authors.
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
"""gRPC's experimental APIs.

These APIs are subject to be removed during any minor version release.
"""

# Standard library imports
import copy
import functools
import sys
import warnings

# gRPC imports
import grpc
from grpc._cython import cygrpc as _cygrpc

# Set to track which experimental APIs have been used to avoid duplicate warnings
_EXPERIMENTAL_APIS_USED = set()

class ChannelOptions(object):
    """Indicates a channel option unique to gRPC Python.

    This enumeration is part of an EXPERIMENTAL API.

    Attributes:
      SingleThreadedUnaryStream: Perform unary-stream RPCs on a single thread.
          This is useful for testing or special cases where single-threaded
          execution is desired.
    """

    SingleThreadedUnaryStream = "SingleThreadedUnaryStream"

class UsageError(Exception):
    """Raised by the gRPC library to indicate usage not allowed by the API.

    This exception is thrown when the API is used in a way that violates
    its intended usage patterns.
    """

# Pre-created insecure channel credentials for performance optimization
_insecure_channel_credentials = grpc.ChannelCredentials(
    _cygrpc.channel_credentials_insecure()
)

def insecure_channel_credentials():
    """Creates a ChannelCredentials for use with an insecure channel.

    THIS IS AN EXPERIMENTAL API.
    Note: Insecure credentials should only be used for testing or in secure
    environments as they provide no transport security.
    """
    return _insecure_channel_credentials

class ExperimentalApiWarning(Warning):
    """A warning that an API is experimental.

    This warning is emitted when experimental APIs are used to alert developers
    that the API may change or be removed in future releases.
    """

def _warn_experimental(api_name, stack_offset):
    """Internal function to warn about experimental API usage.

    Args:
        api_name: Name of the experimental API being used.
        stack_offset: How many stack frames to skip when reporting the warning.
    """
    if api_name not in _EXPERIMENTAL_APIS_USED:
        _EXPERIMENTAL_APIS_USED.add(api_name)
        msg = (
            "'{}' is an experimental API. It is subject to change or ".format(
                api_name
            )
            + "removal between minor releases. Proceed with caution."
        )
        warnings.warn(msg, ExperimentalApiWarning, stacklevel=2 + stack_offset)

def experimental_api(f):
    """Decorator to mark functions as experimental APIs.

    When decorated functions are called, they will emit a warning about
    their experimental status.

    Args:
        f: The function to be decorated.

    Returns:
        A wrapped function that emits warnings when called.
    """
    @functools.wraps(f)
    def _wrapper(*args, **kwargs):
        _warn_experimental(f.__name__, 1)
        return f(*args, **kwargs)

    return _wrapper

def wrap_server_method_handler(wrapper, handler):
    """Wraps the server method handler function.

    The server implementation requires all server handlers being wrapped as
    RpcMethodHandler objects. This helper function ease the pain of writing
    server handler wrappers.

    Args:
        wrapper: A wrapper function that takes in a method handler behavior
          (the actual function) and returns a wrapped function.
        handler: A RpcMethodHandler object to be wrapped.

    Returns:
        A newly created RpcMethodHandler with all appropriate methods wrapped.
    """
    if not handler:
        return None

    # Handle all four combinations of streaming/non-streaming requests/responses
    if not handler.request_streaming:
        if not handler.response_streaming:
            # Unary request, unary response
            return handler._replace(unary_unary=wrapper(handler.unary_unary))
        else:
            # Unary request, streaming response
            return handler._replace(unary_stream=wrapper(handler.unary_stream))
    else:
        if not handler.response_streaming:
            # Streaming request, unary response
            return handler._replace(stream_unary=wrapper(handler.stream_unary))
        else:
            # Streaming request, streaming response
            return handler._replace(
                stream_stream=wrapper(handler.stream_stream)
            )

# Define public API exports
__all__ = (
    "ChannelOptions",
    "ExperimentalApiWarning",
    "UsageError",
    "insecure_channel_credentials",
    "wrap_server_method_handler",
)

# Python 3.6+ specific imports
if sys.version_info > (3, 6):
    from grpc._simple_stubs import stream_stream
    from grpc._simple_stubs import stream_unary
    from grpc._simple_stubs import unary_stream
    from grpc._simple_stubs import unary_unary

    # Add Python 3.6+ specific exports to __all__
    __all__ = __all__ + (unary_unary, unary_stream, stream_unary, stream_stream)
```