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

import collections
import logging
import threading
from typing import Callable, Optional, Type

import grpc
from grpc import _common
from grpc._cython import cygrpc
from grpc._typing import MetadataType

# Logger instance for this module
_LOGGER = logging.getLogger(__name__)

# Class representing authentication metadata context
# Inherits from both namedtuple and grpc.AuthMetadataContext
# Contains service URL and method name information
class _AuthMetadataContext(
    collections.namedtuple(
        "AuthMetadataContext",
        (
            "service_url",
            "method_name",
        ),
    ),
    grpc.AuthMetadataContext,
):
    pass

# Class to maintain state for callback operations
# Includes thread safety mechanisms and tracks callback status
class _CallbackState(object):
    def __init__(self):
        self.lock = threading.Lock()  # Thread lock for synchronization
        self.called = False          # Flag indicating if callback was invoked
        self.exception = None        # Stores any exception that occurred

# Class implementing AuthMetadataPluginCallback interface
# Handles the callback mechanism for auth metadata plugins
class _AuthMetadataPluginCallback(grpc.AuthMetadataPluginCallback):
    _state: _CallbackState
    _callback: Callable

    def __init__(self, state: _CallbackState, callback: Callable):
        self._state = state
        self._callback = callback

    # Invoked when auth metadata plugin completes
    def __call__(
        self, metadata: MetadataType, error: Optional[Type[BaseException]]
    ):
        with self._state.lock:
            if self._state.exception is None:
                if self._state.called:
                    raise RuntimeError(
                        "AuthMetadataPluginCallback invoked more than once!"
                    )
                else:
                    self._state.called = True
            else:
                raise RuntimeError(
                    'AuthMetadataPluginCallback raised exception "{}"!'.format(
                        self._state.exception
                    )
                )
        # Handle successful and error cases
        if error is None:
            self._callback(metadata, cygrpc.StatusCode.ok, None)
        else:
            self._callback(
                None, cygrpc.StatusCode.internal, _common.encode(str(error))
            )

# Wrapper class for auth metadata plugins
# Handles context preservation and plugin invocation
class _Plugin(object):
    _metadata_plugin: grpc.AuthMetadataPlugin

    def __init__(self, metadata_plugin: grpc.AuthMetadataPlugin):
        self._metadata_plugin = metadata_plugin
        self._stored_ctx = None  # For storing context if available

        # Attempt to preserve context if contextvars is available
        try:
            import contextvars
            self._stored_ctx = contextvars.copy_context()
        except ImportError:
            pass

    # Main plugin invocation method
    def __call__(self, service_url: str, method_name: str, callback: Callable):
        # Create auth context with decoded service URL and method name
        context = _AuthMetadataContext(
            _common.decode(service_url), _common.decode(method_name)
        )
        callback_state = _CallbackState()
        try:
            # Invoke the metadata plugin with context and callback
            self._metadata_plugin(
                context, _AuthMetadataPluginCallback(callback_state, callback)
            )
        except Exception as exception:
            # Log and handle exceptions from the plugin
            _LOGGER.exception(
                'AuthMetadataPluginCallback "%s" raised exception!',
                self._metadata_plugin,
            )
            with callback_state.lock:
                callback_state.exception = exception
                if callback_state.called:
                    return
            callback(
                None, cygrpc.StatusCode.internal, _common.encode(str(exception))
            )

# Creates call credentials from a metadata plugin
def metadata_plugin_call_credentials(
    metadata_plugin: grpc.AuthMetadataPlugin, name: Optional[str]
) -> grpc.CallCredentials:
    # Determine effective name for the credentials
    if name is None:
        try:
            effective_name = metadata_plugin.__name__
        except AttributeError:
            effective_name = metadata_plugin.__class__.__name__
    else:
        effective_name = name
    
    # Create and return call credentials using the plugin wrapper
    return grpc.CallCredentials(
        cygrpc.MetadataPluginCallCredentials(
            _Plugin(metadata_plugin), _common.encode(effective_name)
        )
    )
```