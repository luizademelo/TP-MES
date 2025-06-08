I'll provide a commented version of this code, explaining the key components and functionality. The comments will be added as docstrings and inline comments where appropriate.

```python
# Copyright 2016 gRPC authors.
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

"""Service-side implementation of gRPC Python."""

from __future__ import annotations

import abc
import collections
from concurrent import futures
import contextvars
import enum
import logging
import threading
import time
import traceback
from typing import (
    Any,
    Callable,
    Dict,
    Iterable,
    Iterator,
    List,
    Mapping,
    Optional,
    Sequence,
    Set,
    Tuple,
    Union,
)

import grpc
from grpc import _common
from grpc import _compression
from grpc import _interceptor
from grpc import _observability
from grpc._cython import cygrpc
from grpc._typing import ArityAgnosticMethodHandler
from grpc._typing import ChannelArgumentType
from grpc._typing import DeserializingFunction
from grpc._typing import MetadataType
from grpc._typing import NullaryCallbackType
from grpc._typing import ResponseType
from grpc._typing import SerializingFunction
from grpc._typing import ServerCallbackTag
from grpc._typing import ServerTagCallbackType

# Logger for server-side operations
_LOGGER = logging.getLogger(__name__)

# Constants for server operation tags
_SHUTDOWN_TAG = "shutdown"
_REQUEST_CALL_TAG = "request_call"

# Constants for RPC operation tokens
_RECEIVE_CLOSE_ON_SERVER_TOKEN = "receive_close_on_server"
_SEND_INITIAL_METADATA_TOKEN = "send_initial_metadata"
_RECEIVE_MESSAGE_TOKEN = "receive_message"
_SEND_MESSAGE_TOKEN = "send_message"
_SEND_INITIAL_METADATA_AND_SEND_MESSAGE_TOKEN = (
    "send_initial_metadata * send_message"
)
_SEND_STATUS_FROM_SERVER_TOKEN = "send_status_from_server"
_SEND_INITIAL_METADATA_AND_SEND_STATUS_FROM_SERVER_TOKEN = (
    "send_initial_metadata * send_status_from_server"
)

# Constants for RPC state
_OPEN = "open"
_CLOSED = "closed"
_CANCELLED = "cancelled"

_EMPTY_FLAGS = 0  # Default flags value for operations

# Server configuration constants
_DEALLOCATED_SERVER_CHECK_PERIOD_S = 1.0  # How often to check for server deallocation
_INF_TIMEOUT = 1e9  # Infinite timeout value

def _serialized_request(request_event: cygrpc.BaseEvent) -> bytes:
    """Extracts the serialized request message from a gRPC event."""
    return request_event.batch_operations[0].message()

def _application_code(code: grpc.StatusCode) -> cygrpc.StatusCode:
    """Converts a gRPC status code to a cygrpc status code."""
    cygrpc_code = _common.STATUS_CODE_TO_CYGRPC_STATUS_CODE.get(code)
    return cygrpc.StatusCode.unknown if cygrpc_code is None else cygrpc_code

def _completion_code(state: _RPCState) -> cygrpc.StatusCode:
    """Determines the completion status code for an RPC."""
    if state.code is None:
        return cygrpc.StatusCode.ok
    else:
        return _application_code(state.code)

def _abortion_code(
    state: _RPCState, code: cygrpc.StatusCode
) -> cygrpc.StatusCode:
    """Determines the abortion status code for an RPC."""
    if state.code is None:
        return code
    else:
        return _application_code(state.code)

def _details(state: _RPCState) -> bytes:
    """Gets the details message for an RPC, defaulting to empty bytes."""
    return b"" if state.details is None else state.details

class _HandlerCallDetails(
    collections.namedtuple(
        "_HandlerCallDetails",
        (
            "method",
            "invocation_metadata",
        ),
    ),
    grpc.HandlerCallDetails,
):
    """Container for handler call details including method name and metadata."""
    pass

class _Method(abc.ABC):
    """Abstract base class representing a gRPC method."""
    @abc.abstractmethod
    def name(self) -> Optional[str]:
        """Returns the method name if registered, None otherwise."""
        raise NotImplementedError()

    @abc.abstractmethod
    def handler(
        self, handler_call_details: _HandlerCallDetails
    ) -> Optional[grpc.RpcMethodHandler]:
        """Returns the method handler for the given call details."""
        raise NotImplementedError()

class _RegisteredMethod(_Method):
    """Represents a registered gRPC method with a known handler."""
    def __init__(
        self,
        name: str,
        registered_handler: Optional[grpc.RpcMethodHandler],
    ):
        self._name = name
        self._registered_handler = registered_handler

    def name(self) -> Optional[str]:
        return self._name

    def handler(
        self, handler_call_details: _HandlerCallDetails
    ) -> Optional[grpc.RpcMethodHandler]:
        return self._registered_handler

class _GenericMethod(_Method):
    """Represents a generic method that uses generic handlers."""
    def __init__(
        self,
        generic_handlers: List[grpc.GenericRpcHandler],
    ):
        self._generic_handlers = generic_handlers

    def name(self) -> Optional[str]:
        return None

    def handler(
        self, handler_call_details: _HandlerCallDetails
    ) -> Optional[grpc.RpcMethodHandler]:
        """Finds the appropriate handler by querying all generic handlers."""
        for generic_handler in self._generic_handlers:
            method_handler = generic_handler.service(handler_call_details)
            if method_handler is not None:
                return method_handler
        return None

class _RPCState(object):
    """Maintains the state of an RPC throughout its lifecycle."""
    context: contextvars.Context
    condition: threading.Condition
    due = Set[str]
    request: Any
    client: str
    initial_metadata_allowed: bool
    compression_algorithm: Optional[grpc.Compression]
    disable_next_compression: bool
    trailing_metadata: Optional[MetadataType]
    code: Optional[grpc.StatusCode]
    details: Optional[bytes]
    statused: bool
    rpc_errors: List[Exception]
    callbacks: Optional[List[NullaryCallbackType]]
    aborted: bool

    def __init__(self):
        """Initializes a new RPC state with default values."""
        self.context = contextvars.Context()
        self.condition = threading.Condition()
        self.due = set()
        self.request = None
        self.client = _OPEN
        self.initial_metadata_allowed = True
        self.compression_algorithm = None
        self.disable_next_compression = False
        self.trailing_metadata = None
        self.code = None
        self.details = None
        self.statused = False
        self.rpc_errors = []
        self.callbacks = []
        self.aborted = False

def _raise_rpc_error(state: _RPCState) -> None:
    """Raises an RPC error and records it in the RPC state."""
    rpc_error = grpc.RpcError()
    state.rpc_errors.append(rpc_error)
    raise rpc_error

def _possibly_finish_call(
    state: _RPCState, token: str
) -> ServerTagCallbackType:
    """Checks if the RPC can be finished after completing an operation."""
    state.due.remove(token)
    if not _is_rpc_state_active(state) and not state.due:
        callbacks = state.callbacks
        state.callbacks = None
        return state, callbacks
    else:
        return None, ()

def _send_status_from_server(state: _RPCState, token: str) -> ServerCallbackTag:
    """Creates a callback for sending status from server to client."""
    def send_status_from_server(unused_send_status_from_server_event):
        with state.condition:
            return _possibly_finish_call(state, token)

    return send_status_from_server

def _get_initial_metadata(
    state: _RPCState, metadata: Optional[MetadataType]
) -> Optional[MetadataType]:
    """Gets initial metadata with compression metadata if configured."""
    with state.condition:
        if state.compression_algorithm:
            compression_metadata = (
                _compression.compression_algorithm_to_metadata(
                    state.compression_algorithm
                ),
            )
            if metadata is None:
                return compression_metadata
            else:
                return compression_metadata + tuple(metadata)
        else:
            return metadata

def _get_initial_metadata_operation(
    state: _RPCState, metadata: Optional[MetadataType]
) -> cygrpc.Operation:
    """Creates an operation for sending initial metadata."""
    operation = cygrpc.SendInitialMetadataOperation(
        _get_initial_metadata(state, metadata), _EMPTY_FLAGS
    )
    return operation

def _abort(
    state: _RPCState, call: cygrpc.Call, code: cygrpc.StatusCode, details: bytes
) -> None:
    """Aborts an RPC with the given status code and details."""
    if state.client is not _CANCELLED:
        effective_code = _abortion_code(state, code)
        effective_details = details if state.details is None else state.details
        if state.initial_metadata_allowed:
            operations = (
                _get_initial_metadata_operation(state, None),
                cygrpc.SendStatusFromServerOperation(
                    state.trailing_metadata,
                    effective_code,
                    effective_details,
                    _EMPTY_FLAGS,
                ),
            )
            token = _SEND_INITIAL_METADATA_AND_SEND_STATUS_FROM_SERVER_TOKEN
        else:
            operations = (
                cygrpc.SendStatusFromServerOperation(
                    state.trailing_metadata,
                    effective_code,
                    effective_details,
                    _EMPTY_FLAGS,
                ),
            )
            token = _SEND_STATUS_FROM_SERVER_TOKEN
        call.start_server_batch(
            operations, _send_status_from_server(state, token)
        )
        state.statused = True
        state.due.add(token)

def _receive_close_on_server(state: _RPCState) -> ServerCallbackTag:
    """Creates a callback for receiving close notification from client."""
    def receive_close_on_server(receive_close_on_server_event):
        with state.condition:
            if receive_close_on_server_event.batch_operations[0].cancelled():
                state.client = _CANCELLED
            elif state.client is _OPEN:
                state.client = _CLOSED
            state.condition.notify_all()
            return _possibly_finish_call(state, _RECEIVE_CLOSE_ON_SERVER_TOKEN)

    return receive_close_on_server

def _receive_message(
    state: _RPCState,
    call: cygrpc.Call,
    request_deserializer: Optional[DeserializingFunction],
) -> ServerCallbackTag:
    """Creates a callback for receiving a message from the client."""
    def receive_message(receive_message_event):
        serialized_request = _serialized_request(receive_message_event)
        if serialized_request is None:
            with state.condition:
                if state.client is _OPEN:
                    state.client = _CLOSED
                state.condition.notify_all()
                return _possibly_finish_call(state, _RECEIVE_MESSAGE_TOKEN)
        else:
            request = _common.deserialize(
                serialized_request, request_deserializer
            )
            with state.condition:
                if request is None:
                    _abort(
                        state,
                        call,
                        cygrpc.StatusCode.internal,
                        b"Exception deserializing request!",
                    )
                else:
                    state.request = request
                state.condition.notify_all()
                return _possibly_finish_call(state, _RECEIVE_MESSAGE_TOKEN)

    return receive_message

def _send_initial_metadata(state: _RPCState) -> ServerCallbackTag:
    """Creates a callback for sending initial metadata to client."""
    def send_initial_metadata(unused_send_initial_metadata_event):
        with state.condition:
            return _possibly_finish_call(state, _SEND_INITIAL_METADATA_TOKEN)

    return send_initial_metadata

def _send_message(state: _RPCState, token: str) -> ServerCallbackTag:
    """Creates a callback for sending a message to the client."""
    def send_message(unused_send_message_event):
        with state.condition:
            state.condition.notify_all()
            return _possibly_finish_call(state, token)

    return send_message

class _Context(grpc.ServicerContext):
    """Implements the ServicerContext interface for handling RPCs."""
    _rpc_event: cygrpc.BaseEvent
    _state: _RPCState
    request_deserializer: Optional[DeserializingFunction]

    def __init__(
        self,
        rpc_event: cygrpc.BaseEvent,
        state: _RPCState,
        request_deserializer: Optional[DeserializingFunction],
    ):
        self._rpc_event = rpc_event
        self._state = state
        self._request_deserializer = request_deserializer

    def is_active(self) -> bool:
        """Returns True if the RPC is active, False otherwise."""
        with self._state.condition:
            return _is_rpc_state_active(self._state)

    def time_remaining(self) -> float:
        """Returns the remaining time before the RPC deadline."""
        return max(self._rpc_event.call_details.deadline - time.time(), 0)

    def cancel(self) -> None:
        """Cancels the RPC."""
        self._rpc_event.call.cancel()

    def add_callback(self, callback: NullaryCallbackType) -> bool:
        """Adds a callback to be invoked when the RPC completes."""
        with self._state.condition:
            if self._state.callbacks is None:
                return False
            else:
                self._state.callbacks.append(callback)
                return True

    def disable_next_message_compression(self) -> None:
        """Disables compression for the next message."""
        with self._state.condition:
            self._state.disable_next_compression = True

    def invocation_metadata(self) -> Optional[MetadataType]:
        """Returns the invocation metadata for the RPC."""
        return self._rpc_event.invocation_metadata

    def peer(self) -> str:
        """Returns the peer address for the RPC."""
        return _common.decode(self._rpc_event.call.peer())

    def peer_identities(self) -> Optional[Sequence[bytes]]:
        """Returns the peer identities for the RPC."""
        return cygrpc.peer_identities(self._rpc_event.call)

    def peer_identity_key(self) -> Optional[str]:
        """Returns the peer identity key for the RPC."""
        id_key = cygrpc.peer_identity_key(self._rpc_event.call)
        return id_key if id_key is None else _common.decode(id_key)

    def auth_context(self) -> Mapping[str, Sequence[bytes]]:
        """Returns the authentication context for the RPC."""
        auth_context = cygrpc.auth_context(self._rpc_event.call)
        auth_context_dict = {} if auth_context is None else auth_context
        return {
            _common.decode(key): value
            for key, value in auth_context_dict.items()
        }

    def set_compression(self, compression: grpc.Compression) -> None:
        """Sets the compression algorithm for the RPC."""
        with self._state.condition:
            self._state.compression_algorithm = compression

    def send_initial_metadata(self, initial_metadata: MetadataType) -> None:
        """Sends initial metadata to the client."""
        with self._state.condition:
            if self._state.client is _CANCELLED:
                _raise_rpc_error(self._state)
            else:
                if self._state.initial_metadata_allowed:
                    operation = _get_initial_metadata_operation(
                        self._state, initial_metadata
                    )
                    self._rpc_event.call.start_server_batch(
                        (operation,), _send_initial_metadata(self._state)
                    )
                    self._state.initial_metadata_allowed = False
                    self._state.due.add(_SEND_INITIAL_METADATA_TOKEN)
                else:
                    raise ValueError("Initial metadata no longer allowed!")

    def set_trailing_metadata(self, trailing_metadata: MetadataType) -> None:
        """Sets trailing metadata for the RPC."""
        with self._state.condition:
            self._state.trailing_metadata = trailing_metadata

    def trailing_metadata(self) -> Optional[MetadataType]:
        """Returns the trailing metadata for the RPC."""
        return self._state.trailing_metadata

    def abort(self, code: grpc.StatusCode, details: str) -> None:
        """Aborts the RPC with the given status code and details."""
        if code == grpc.StatusCode.OK:
            _LOGGER.error(
                "abort() called with StatusCode.OK; returning UNKNOWN"
            )
            code = grpc.StatusCode.UNKNOWN
            details = ""
        with self._state.condition:
            self._state.code = code
            self._state.details = _common.encode(details)
            self._state.aborted = True
            raise Exception()

    def abort_with_status(self, status: grpc.Status) -> None:
        """Aborts the RPC with the given status object."""
        self._state.trailing_metadata = status.trailing_metadata
        self.abort(status.code, status.details)

    def set_code(self, code: grpc.StatusCode) -> None:
        """Sets the status code for the RPC."""
        with self._state.condition:
            self