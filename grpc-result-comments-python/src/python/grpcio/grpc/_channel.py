Here's the commented version of the code:

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

"""Invocation-side implementation of gRPC Python."""

import copy
import functools
import logging
import os
import sys
import threading
import time
import types
from typing import (
    Any,
    Callable,
    Dict,
    Iterator,
    List,
    Optional,
    Sequence,
    Set,
    Tuple,
    Union,
)

import grpc
from grpc import _common
from grpc import _compression
from grpc import _grpcio_metadata
from grpc import _observability
from grpc._cython import cygrpc
from grpc._typing import ChannelArgumentType
from grpc._typing import DeserializingFunction
from grpc._typing import IntegratedCallFactory
from grpc._typing import MetadataType
from grpc._typing import NullaryCallbackType
from grpc._typing import ResponseType
from grpc._typing import SerializingFunction
from grpc._typing import UserTag
import grpc.experimental

# Logger for this module
_LOGGER = logging.getLogger(__name__)

# User agent string for gRPC Python
_USER_AGENT = "grpc-python/{}".format(_grpcio_metadata.__version__)

# Empty flags constant
_EMPTY_FLAGS = 0

# Flag for single-threaded unary stream mode
_DEFAULT_SINGLE_THREADED_UNARY_STREAM = (
    os.getenv("GRPC_SINGLE_THREADED_UNARY_STREAM") is not None
)

# Operation types for different RPC patterns
_UNARY_UNARY_INITIAL_DUE = (
    cygrpc.OperationType.send_initial_metadata,
    cygrpc.OperationType.send_message,
    cygrpc.OperationType.send_close_from_client,
    cygrpc.OperationType.receive_initial_metadata,
    cygrpc.OperationType.receive_message,
    cygrpc.OperationType.receive_status_on_client,
)
_UNARY_STREAM_INITIAL_DUE = (
    cygrpc.OperationType.send_initial_metadata,
    cygrpc.OperationType.send_message,
    cygrpc.OperationType.send_close_from_client,
    cygrpc.OperationType.receive_initial_metadata,
    cygrpc.OperationType.receive_status_on_client,
)
_STREAM_UNARY_INITIAL_DUE = (
    cygrpc.OperationType.send_initial_metadata,
    cygrpc.OperationType.receive_initial_metadata,
    cygrpc.OperationType.receive_message,
    cygrpc.OperationType.receive_status_on_client,
)
_STREAM_STREAM_INITIAL_DUE = (
    cygrpc.OperationType.send_initial_metadata,
    cygrpc.OperationType.receive_initial_metadata,
    cygrpc.OperationType.receive_status_on_client,
)

# Error message for channel subscription callback errors
_CHANNEL_SUBSCRIPTION_CALLBACK_ERROR_LOG_MESSAGE = (
    "Exception calling channel subscription callback!"
)

# Format strings for RPC status representations
_OK_RENDEZVOUS_REPR_FORMAT = (
    '<{} of RPC that terminated with:\n\tstatus = {}\n\tdetails = "{}"\n>'
)

_NON_OK_RENDEZVOUS_REPR_FORMAT = (
    "<{} of RPC that terminated with:\n"
    "\tstatus = {}\n"
    '\tdetails = "{}"\n'
    '\tdebug_error_string = "{}"\n'
    ">"
)

def _deadline(timeout: Optional[float]) -> Optional[float]:
    """Converts a timeout to an absolute deadline timestamp."""
    return None if timeout is None else time.time() + timeout

def _unknown_code_details(
    unknown_cygrpc_code: Optional[grpc.StatusCode], details: Optional[str]
) -> str:
    """Creates a details string for an unknown status code."""
    return 'Server sent unknown code {} and details "{}"'.format(
        unknown_cygrpc_code, details
    )

class _RPCState(object):
    """Tracks the state of an RPC operation.

    Attributes:
        condition: Threading condition for synchronization
        due: Set of pending operation types
        initial_metadata: Initial metadata from server
        response: Deserialized response message
        trailing_metadata: Trailing metadata from server
        code: gRPC status code
        details: Status details
        debug_error_string: Debug error string
        cancelled: Whether RPC was cancelled
        callbacks: List of callbacks to invoke
        fork_epoch: Fork epoch for thread safety
        rpc_start_time: Timestamp when RPC started
        rpc_end_time: Timestamp when RPC ended
        method: RPC method name
        target: RPC target
    """
    condition: threading.Condition
    due: Set[cygrpc.OperationType]
    initial_metadata: Optional[MetadataType]
    response: Any
    trailing_metadata: Optional[MetadataType]
    code: Optional[grpc.StatusCode]
    details: Optional[str]
    debug_error_string: Optional[str]
    cancelled: bool
    callbacks: List[NullaryCallbackType]
    fork_epoch: Optional[int]
    rpc_start_time: Optional[float]
    rpc_end_time: Optional[float]
    method: Optional[str]
    target: Optional[str]

    def __init__(
        self,
        due: Sequence[cygrpc.OperationType],
        initial_metadata: Optional[MetadataType],
        trailing_metadata: Optional[MetadataType],
        code: Optional[grpc.StatusCode],
        details: Optional[str],
    ):
        """Initializes RPC state."""
        self.condition = threading.Condition()
        self.due = set(due)
        self.initial_metadata = initial_metadata
        self.response = None
        self.trailing_metadata = trailing_metadata
        self.code = code
        self.details = details
        self.debug_error_string = None
        self.rpc_start_time = None
        self.rpc_end_time = None
        self.method = None
        self.target = None
        self.cancelled = False
        self.callbacks = []
        self.fork_epoch = cygrpc.get_fork_epoch()

    def reset_postfork_child(self):
        """Resets state after a fork in the child process."""
        self.condition = threading.Condition()

def _abort(state: _RPCState, code: grpc.StatusCode, details: str) -> None:
    """Aborts an RPC with the given status code and details."""
    if state.code is None:
        state.code = code
        state.details = details
        if state.initial_metadata is None:
            state.initial_metadata = ()
        state.trailing_metadata = ()

def _handle_event(
    event: cygrpc.BaseEvent,
    state: _RPCState,
    response_deserializer: Optional[DeserializingFunction],
) -> List[NullaryCallbackType]:
    """Processes a gRPC event and updates RPC state.
    
    Args:
        event: The gRPC event to process
        state: The RPC state to update
        response_deserializer: Function to deserialize response messages
        
    Returns:
        List of callbacks to invoke
    """
    callbacks = []
    for batch_operation in event.batch_operations:
        operation_type = batch_operation.type()
        state.due.remove(operation_type)
        if operation_type == cygrpc.OperationType.receive_initial_metadata:
            state.initial_metadata = batch_operation.initial_metadata()
        elif operation_type == cygrpc.OperationType.receive_message:
            serialized_response = batch_operation.message()
            if serialized_response is not None:
                response = _common.deserialize(
                    serialized_response, response_deserializer
                )
                if response is None:
                    details = "Exception deserializing response!"
                    _abort(state, grpc.StatusCode.INTERNAL, details)
                else:
                    state.response = response
        elif operation_type == cygrpc.OperationType.receive_status_on_client:
            state.trailing_metadata = batch_operation.trailing_metadata()
            if state.code is None:
                code = _common.CYGRPC_STATUS_CODE_TO_STATUS_CODE.get(
                    batch_operation.code()
                )
                if code is None:
                    state.code = grpc.StatusCode.UNKNOWN
                    state.details = _unknown_code_details(
                        code, batch_operation.details()
                    )
                else:
                    state.code = code
                    state.details = batch_operation.details()
                    state.debug_error_string = batch_operation.error_string()
            state.rpc_end_time = time.perf_counter()
            _observability.maybe_record_rpc_latency(state)
            callbacks.extend(state.callbacks)
            state.callbacks = None
    return callbacks

def _event_handler(
    state: _RPCState, response_deserializer: Optional[DeserializingFunction]
) -> UserTag:
    """Creates an event handler function for gRPC operations.
    
    Args:
        state: RPC state to update
        response_deserializer: Function to deserialize responses
        
    Returns:
        A function that handles gRPC events
    """
    def handle_event(event):
        with state.condition:
            callbacks = _handle_event(event, state, response_deserializer)
            state.condition.notify_all()
            done = not state.due
        for callback in callbacks:
            try:
                callback()
            except Exception as e:
                logging.error(
                    "Exception in callback %s: %s", repr(callback.func), repr(e)
        return done and state.fork_epoch >= cygrpc.get_fork_epoch()

    return handle_event

def _consume_request_iterator(
    request_iterator: Iterator,
    state: _RPCState,
    call: Union[cygrpc.IntegratedCall, cygrpc.SegregatedCall],
    request_serializer: SerializingFunction,
    event_handler: Optional[UserTag],
) -> None:
    """Consumes requests from an iterator and sends them to the server.
    
    Args:
        request_iterator: Iterator yielding request messages
        state: RPC state
        call: gRPC call object
        request_serializer: Function to serialize requests
        event_handler: Event handler for call operations
    """
    def consume_request_iterator():
        while True:
            return_from_user_request_generator_invoked = False
            try:
                cygrpc.enter_user_request_generator()
                request = next(request_iterator)
            except StopIteration:
                break
            except Exception:
                cygrpc.return_from_user_request_generator()
                return_from_user_request_generator_invoked = True
                code = grpc.StatusCode.UNKNOWN
                details = "Exception iterating requests!"
                _LOGGER.exception(details)
                call.cancel(
                    _common.STATUS_CODE_TO_CYGRPC_STATUS_CODE[code], details
                )
                _abort(state, code, details)
                return
            finally:
                if not return_from_user_request_generator_invoked:
                    cygrpc.return_from_user_request_generator()
            serialized_request = _common.serialize(request, request_serializer)
            with state.condition:
                if state.code is None and not state.cancelled:
                    if serialized_request is None:
                        code = grpc.StatusCode.INTERNAL
                        details = "Exception serializing request!"
                        call.cancel(
                            _common.STATUS_CODE_TO_CYGRPC_STATUS_CODE[code],
                            details,
                        )
                        _abort(state, code, details)
                        return
                    else:
                        state.due.add(cygrpc.OperationType.send_message)
                        operations = (
                            cygrpc.SendMessageOperation(
                                serialized_request, _EMPTY_FLAGS
                            ),
                        )
                        operating = call.operate(operations, event_handler)
                        if not operating:
                            state.due.remove(cygrpc.OperationType.send_message)
                            return

                        def _done():
                            return (
                                state.code is not None
                                or cygrpc.OperationType.send_message
                                not in state.due
                            )

                        _common.wait(
                            state.condition.wait,
                            _done,
                            spin_cb=functools.partial(
                                cygrpc.block_if_fork_in_progress, state
                            ),
                        )
                        if state.code is not None:
                            return
                else:
                    return
        with state.condition:
            if state.code is None:
                state.due.add(cygrpc.OperationType.send_close_from_client)
                operations = (
                    cygrpc.SendCloseFromClientOperation(_EMPTY_FLAGS),
                )
                operating = call.operate(operations, event_handler)
                if not operating:
                    state.due.remove(
                        cygrpc.OperationType.send_close_from_client
                    )

    consumption_thread = cygrpc.ForkManagedThread(
        target=consume_request_iterator
    )
    consumption_thread.setDaemon(True)
    consumption_thread.start()

def _rpc_state_string(class_name: str, rpc_state: _RPCState) -> str:
    """Creates a string representation of RPC state.
    
    Args:
        class_name: Name of the RPC class
        rpc_state: State of the RPC
        
    Returns:
        String representation of the RPC state
    """
    with rpc_state.condition:
        if rpc_state.code is None:
            return "<{} object>".format(class_name)
        elif rpc_state.code is grpc.StatusCode.OK:
            return _OK_RENDEZVOUS_REPR_FORMAT.format(
                class_name, rpc_state.code, rpc_state.details
            )
        else:
            return _NON_OK_RENDEZVOUS_REPR_FORMAT.format(
                class_name,
                rpc_state.code,
                rpc_state.details,
                rpc_state.debug_error_string,
            )

class _InactiveRpcError(grpc.RpcError, grpc.Call, grpc.Future):
    """An RPC error not tied to an active RPC operation.
    
    Attributes:
        _state: The RPC state containing error information
    """
    _state: _RPCState

    def __init__(self, state: _RPCState):
        """Initializes with a copy of the RPC state."""
        with state.condition:
            self._state = _RPCState(
                (),
                copy.deepcopy(state.initial_metadata),
                copy.deepcopy(state.trailing_metadata),
                state.code,
                copy.deepcopy(state.details),
            )
            self._state.response = copy.copy(state.response)
            self._state.debug_error_string = copy.copy(state.debug_error_string)

    # Implementation of grpc.Call interface methods
    def initial_metadata(self) -> Optional[MetadataType]:
        return self._state.initial_metadata

    def trailing_metadata(self) -> Optional[MetadataType]:
        return self._state.trailing_metadata

    def code(self) -> Optional[grpc.StatusCode]:
        return self._state.code

    def details(self) -> Optional[str]:
        return _common.decode(self._state.details)

    def debug_error_string(self) -> Optional[str]:
        return _common.decode(self._state.debug_error_string)

    def _repr(self) -> str:
        return _rpc_state_string(self.__class__.__name__, self._state)

    def __repr__(self) -> str:
        return self._repr()

    def __str__(self) -> str:
        return self._repr()

    # Implementation of grpc.Future interface methods
    def cancel(self) -> bool:
        return False

    def cancelled(self) -> bool:
        return False

    def running(self) -> bool:
        return False

    def done(self) -> bool:
        return True

    def result(self, timeout: Optional[float] = None) -> Any:
        raise self

    def exception(self, timeout: Optional[float] = None) -> Optional[Exception]:
        return self

    def traceback(self, timeout: Optional[float] = None) -> Optional[types.TracebackType]:
        try:
            raise self
        except grpc.RpcError:
            return sys.exc_info()[2]

    def add_done_callback(self, fn: Callable[[grpc.Future], None]) -> None:
        fn(self)

class _Rendezvous(grpc.RpcError, grpc.RpcContext):
    """Base class for RPC iterators.
    
    Attributes:
        _state: The RPC state
        _call: The gRPC call object
        _response_deserializer: Function to deserialize responses
        _deadline: Deadline for the RPC
    """
    _state: _RPCState
    _call: Union[cygrpc.SegregatedCall, cygrpc.IntegratedCall]
    _response_deserializer: Optional[DeserializingFunction]
    _deadline: Optional[float]

    def __init__(
        self,
        state: _RPCState,
        call: Union[cygrpc.SegregatedCall, cygrpc.IntegratedCall],
        response_deserializer: Optional[DeserializingFunction],
        deadline: Optional[float],
    ):
        super(_Rendezvous, self).__init__()
        self._state = state
        self._call = call
        self._response_deserializer = response_deserializer
        self._deadline = deadline

    # Implementation of grpc.RpcContext interface
    def is_active(self) -> bool:
        with self._state.condition:
            return self._state.code is None

    def time_remaining(self) -> Optional[float]:
        with self._state.condition:
            if self._deadline is None:
                return None
            else:
                return max(self._deadline - time.time(), 0)

    def cancel(self) -> bool:
        with self._state.condition:
            if self._state.code is None:
                code = grpc.StatusCode.CANCELLED