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

"""Translates gRPC's client-side API into gRPC's client-side Beta API."""

import grpc
from grpc import _common
from grpc.beta import _metadata
from grpc.beta import interfaces
from grpc.framework.common import cardinality
from grpc.framework.foundation import future
from grpc.framework.interfaces.face import face

# Mapping of gRPC status codes to abortion kinds and error classes
_STATUS_CODE_TO_ABORTION_KIND_AND_ABORTION_ERROR_CLASS = {
    grpc.StatusCode.CANCELLED: (
        face.Abortion.Kind.CANCELLED,
        face.CancellationError,
    ),
    grpc.StatusCode.UNKNOWN: (
        face.Abortion.Kind.REMOTE_FAILURE,
        face.RemoteError,
    ),
    grpc.StatusCode.DEADLINE_EXCEEDED: (
        face.Abortion.Kind.EXPIRED,
        face.ExpirationError,
    ),
    grpc.StatusCode.UNIMPLEMENTED: (
        face.Abortion.Kind.LOCAL_FAILURE,
        face.LocalError,
    ),
}

def _effective_metadata(metadata, metadata_transformer):
    """Returns the effective metadata after applying the transformer.
    
    Args:
        metadata: Original metadata to be transformed
        metadata_transformer: Function to transform the metadata
    
    Returns:
        Transformed metadata if transformer exists, otherwise original metadata
    """
    non_none_metadata = () if metadata is None else metadata
    if metadata_transformer is None:
        return non_none_metadata
    else:
        return metadata_transformer(non_none_metadata)

def _credentials(grpc_call_options):
    """Extracts credentials from call options if they exist."""
    return None if grpc_call_options is None else grpc_call_options.credentials

def _abortion(rpc_error_call):
    """Creates an Abortion object from an RPC error call.
    
    Args:
        rpc_error_call: The failed RPC call
        
    Returns:
        face.Abortion object containing error details
    """
    code = rpc_error_call.code()
    pair = _STATUS_CODE_TO_ABORTION_KIND_AND_ABORTION_ERROR_CLASS.get(code)
    error_kind = face.Abortion.Kind.LOCAL_FAILURE if pair is None else pair[0]
    return face.Abortion(
        error_kind,
        rpc_error_call.initial_metadata(),
        rpc_error_call.trailing_metadata(),
        code,
        rpc_error_call.details(),
    )

def _abortion_error(rpc_error_call):
    """Creates an appropriate exception from an RPC error call.
    
    Args:
        rpc_error_call: The failed RPC call
        
    Returns:
        Exception instance corresponding to the error type
    """
    code = rpc_error_call.code()
    pair = _STATUS_CODE_TO_ABORTION_KIND_AND_ABORTION_ERROR_CLASS.get(code)
    exception_class = face.AbortionError if pair is None else pair[1]
    return exception_class(
        rpc_error_call.initial_metadata(),
        rpc_error_call.trailing_metadata(),
        code,
        rpc_error_call.details(),
    )

class _InvocationProtocolContext(interfaces.GRPCInvocationContext):
    """Protocol context for gRPC invocations."""
    def disable_next_request_compression(self):
        """Placeholder for disabling request compression."""
        pass

class _Rendezvous(future.Future, face.Call):
    """Combines Future and Call interfaces for gRPC operations."""
    
    def __init__(self, response_future, response_iterator, call):
        """Initializes with future, iterator and call objects."""
        self._future = response_future
        self._iterator = response_iterator
        self._call = call

    def cancel(self):
        """Cancels the RPC call."""
        return self._call.cancel()

    def cancelled(self):
        """Returns True if the call was cancelled."""
        return self._future.cancelled()

    def running(self):
        """Returns True if the call is still running."""
        return self._future.running()

    def done(self):
        """Returns True if the call is completed."""
        return self._future.done()

    def result(self, timeout=None):
        """Gets the result of the call with optional timeout.
        
        Raises:
            Appropriate exception if call failed or timed out
        """
        try:
            return self._future.result(timeout=timeout)
        except grpc.RpcError as rpc_error_call:
            raise _abortion_error(rpc_error_call)
        except grpc.FutureTimeoutError:
            raise future.TimeoutError()
        except grpc.FutureCancelledError:
            raise future.CancelledError()

    def exception(self, timeout=None):
        """Gets the exception from a failed call with optional timeout."""
        try:
            rpc_error_call = self._future.exception(timeout=timeout)
            if rpc_error_call is None:
                return None
            else:
                return _abortion_error(rpc_error_call)
        except grpc.FutureTimeoutError:
            raise future.TimeoutError()
        except grpc.FutureCancelledError:
            raise future.CancelledError()

    def traceback(self, timeout=None):
        """Gets the traceback from a failed call with optional timeout."""
        try:
            return self._future.traceback(timeout=timeout)
        except grpc.FutureTimeoutError:
            raise future.TimeoutError()
        except grpc.FutureCancelledError:
            raise future.CancelledError()

    def add_done_callback(self, fn):
        """Adds a callback to be executed when the call completes."""
        self._future.add_done_callback(lambda ignored_callback: fn(self))

    def __iter__(self):
        """Returns self as an iterator."""
        return self

    def _next(self):
        """Gets the next item from the iterator."""
        try:
            return next(self._iterator)
        except grpc.RpcError as rpc_error_call:
            raise _abortion_error(rpc_error_call)

    def __next__(self):
        """Python 3 iterator protocol."""
        return self._next()

    def next(self):
        """Python 2 iterator protocol."""
        return self._next()

    def is_active(self):
        """Returns True if the call is active."""
        return self._call.is_active()

    def time_remaining(self):
        """Returns remaining time for the call."""
        return self._call.time_remaining()

    def add_abortion_callback(self, abortion_callback):
        """Adds callback to be executed if call is aborted."""
        def done_callback():
            if self.code() is not grpc.StatusCode.OK:
                abortion_callback(_abortion(self._call))

        registered = self._call.add_callback(done_callback)
        return None if registered else done_callback()

    def protocol_context(self):
        """Returns the protocol context for this call."""
        return _InvocationProtocolContext()

    def initial_metadata(self):
        """Returns the initial metadata."""
        return _metadata.beta(self._call.initial_metadata())

    def terminal_metadata(self):
        """Returns the terminal metadata."""
        return _metadata.beta(self._call.terminal_metadata())

    def code(self):
        """Returns the status code."""
        return self._call.code()

    def details(self):
        """Returns the status details."""
        return self._call.details()

# Following are the implementation functions for different call types:

def _blocking_unary_unary(
    channel,
    group,
    method,
    timeout,
    with_call,
    protocol_options,
    metadata,
    metadata_transformer,
    request,
    request_serializer,
    response_deserializer,
):
    """Blocking unary-unary RPC call."""
    try:
        multi_callable = channel.unary_unary(
            _common.fully_qualified_method(group, method),
            request_serializer=request_serializer,
            response_deserializer=response_deserializer,
        )
        effective_metadata = _effective_metadata(metadata, metadata_transformer)
        if with_call:
            response, call = multi_callable.with_call(
                request,
                timeout=timeout,
                metadata=_metadata.unbeta(effective_metadata),
                credentials=_credentials(protocol_options),
            )
            return response, _Rendezvous(None, None, call)
        else:
            return multi_callable(
                request,
                timeout=timeout,
                metadata=_metadata.unbeta(effective_metadata),
                credentials=_credentials(protocol_options),
            )
    except grpc.RpcError as rpc_error_call:
        raise _abortion_error(rpc_error_call)

def _future_unary_unary(
    channel,
    group,
    method,
    timeout,
    protocol_options,
    metadata,
    metadata_transformer,
    request,
    request_serializer,
    response_deserializer,
):
    """Future-based unary-unary RPC call."""
    multi_callable = channel.unary_unary(
        _common.fully_qualified_method(group, method),
        request_serializer=request_serializer,
        response_deserializer=response_deserializer,
    )
    effective_metadata = _effective_metadata(metadata, metadata_transformer)
    response_future = multi_callable.future(
        request,
        timeout=timeout,
        metadata=_metadata.unbeta(effective_metadata),
        credentials=_credentials(protocol_options),
    )
    return _Rendezvous(response_future, None, response_future)

def _unary_stream(
    channel,
    group,
    method,
    timeout,
    protocol_options,
    metadata,
    metadata_transformer,
    request,
    request_serializer,
    response_deserializer,
):
    """Unary-stream RPC call."""
    multi_callable = channel.unary_stream(
        _common.fully_qualified_method(group, method),
        request_serializer=request_serializer,
        response_deserializer=response_deserializer,
    )
    effective_metadata = _effective_metadata(metadata, metadata_transformer)
    response_iterator = multi_callable(
        request,
        timeout=timeout,
        metadata=_metadata.unbeta(effective_metadata),
        credentials=_credentials(protocol_options),
    )
    return _Rendezvous(None, response_iterator, response_iterator)

def _blocking_stream_unary(
    channel,
    group,
    method,
    timeout,
    with_call,
    protocol_options,
    metadata,
    metadata_transformer,
    request_iterator,
    request_serializer,
    response_deserializer,
):
    """Blocking stream-unary RPC call."""
    try:
        multi_callable = channel.stream_unary(
            _common.fully_qualified_method(group, method),
            request_serializer=request_serializer,
            response_deserializer=response_deserializer,
        )
        effective_metadata = _effective_metadata(metadata, metadata_transformer)
        if with_call:
            response, call = multi_callable.with_call(
                request_iterator,
                timeout=timeout,
                metadata=_metadata.unbeta(effective_metadata),
                credentials=_credentials(protocol_options),
            )
            return response, _Rendezvous(None, None, call)
        else:
            return multi_callable(
                request_iterator,
                timeout=timeout,
                metadata=_metadata.unbeta(effective_metadata),
                credentials=_credentials(protocol_options),
            )
    except grpc.RpcError as rpc_error_call:
        raise _abortion_error(rpc_error_call)

def _future_stream_unary(
    channel,
    group,
    method,
    timeout,
    protocol_options,
    metadata,
    metadata_transformer,
    request_iterator,
    request_serializer,
    response_deserializer,
):
    """Future-based stream-unary RPC call."""
    multi_callable = channel.stream_unary(
        _common.fully_qualified_method(group, method),
        request_serializer=request_serializer,
        response_deserializer=response_deserializer,
    )
    effective_metadata = _effective_metadata(metadata, metadata_transformer)
    response_future = multi_callable.future(
        request_iterator,
        timeout=timeout,
        metadata=_metadata.unbeta(effective_metadata),
        credentials=_credentials(protocol_options),
    )
    return _Rendezvous(response_future, None, response_future)

def _stream_stream(
    channel,
    group,
    method,
    timeout,
    protocol_options,
    metadata,
    metadata_transformer,
    request_iterator,
    request_serializer,
    response_deserializer,
):
    """Stream-stream RPC call."""
    multi_callable = channel.stream_stream(
        _common.fully_qualified_method(group, method),
        request_serializer=request_serializer,
        response_deserializer=response_deserializer,
    )
    effective_metadata = _effective_metadata(metadata, metadata_transformer)
    response_iterator = multi_callable(
        request_iterator,
        timeout=timeout,
        metadata=_metadata.unbeta(effective_metadata),
        credentials=_credentials(protocol_options),
    )
    return _Rendezvous(None, response_iterator, response_iterator)

# MultiCallable implementations for different call patterns:

class _UnaryUnaryMultiCallable(face.UnaryUnaryMultiCallable):
    """Implements unary-unary call pattern."""
    
    def __init__(
        self,
        channel,
        group,
        method,
        metadata_transformer,
        request_serializer,
        response_deserializer,
    ):
        self._channel = channel
        self._group = group
        self._method = method
        self._metadata_transformer = metadata_transformer
        self._request_serializer = request_serializer
        self._response_deserializer = response_deserializer

    def __call__(
        self,
        request,
        timeout,
        metadata=None,
        with_call=False,
        protocol_options=None,
    ):
        return _blocking_unary_unary(
            self._channel,
            self._group,
            self._method,
            timeout,
            with_call,
            protocol_options,
            metadata,
            self._metadata_transformer,
            request,
            self._request_serializer,
            self._response_deserializer,
        )

    def future(self, request, timeout, metadata=None, protocol_options=None):
        return _future_unary_unary(
            self._channel,
            self._group,
            self._method,
            timeout,
            protocol_options,
            metadata,
            self._metadata_transformer,
            request,
            self._request_serializer,
            self._response_deserializer,
        )

    def event(
        self,
        request,
        receiver,
        abortion_callback,
        timeout,
        metadata=None,
        protocol_options=None,
    ):
        raise NotImplementedError()

class _UnaryStreamMultiCallable(face.UnaryStreamMultiCallable):
    """Implements unary-stream call pattern."""
    
    def __init__(
        self,
        channel,
        group,
        method,
        metadata_transformer,
        request_serializer,
        response_deserializer,
    ):
        self._channel = channel
        self._group = group
        self._method = method
        self._metadata_transformer = metadata_transformer
        self._request_serializer = request_serializer
        self._response_deserializer = response_deserializer

    def __call__(self, request, timeout, metadata=None, protocol_options=None):
        return _unary_stream(
            self._channel,
            self._group,
            self._method,
            timeout,
            protocol_options,
            metadata,
            self._metadata_transformer,
            request,
            self._request_serializer,
            self._response_deserializer,
        )

    def event(
        self,
        request,
        receiver,
        abortion_callback,
        timeout,
        metadata=None,
        protocol_options=None,
    ):
        raise NotImplementedError()

class _StreamUnaryMultiCallable(face.StreamUnaryMultiCallable):
    """Implements stream-unary call pattern."""
    
    def __init__(
        self,
        channel,
        group,
        method,
        metadata_transformer,
        request_serializer,
        response_deserializer,
    ):
        self._channel = channel
        self._group = group
        self._method = method
        self._metadata_transformer = metadata_transformer
        self._request_serializer = request_serializer
        self._response_deserializer = response_deserializer

    def __call__(
        self,
        request_iterator,
        timeout,
        metadata=None,
        with_call=False,
        protocol_options=None,
    ):
        return _blocking_stream_unary(
            self._channel,
            self._group,
            self._method,
            timeout,
            with_call,
            protocol_options,
            metadata,
            self._metadata_transformer,
            request_iterator,
            self._request_serializer,
            self._response_deserializer,
        )

    def future(
        self, request_iterator, timeout, metadata=None, protocol_options=None
    ):
        return _future_stream_unary(
            self._channel,
            self._group,
            self._method,
            timeout,
            protocol_options,
            metadata,
            self._metadata_transformer,
            request_iterator,
            self._request_serializer,
            self._response_deserializer,
        )

    def event(
        self,
        receiver,
        abortion_callback,
        timeout,
        metadata=None,
        protocol_options=None,
    ):
        raise NotImplementedError()

class _StreamStreamMultiCallable(face.StreamStreamMultiCallable):
    """Implements stream-stream call pattern."""
    
    def __init__(
        self,
        channel,
        group,
        method,
        metadata_transformer,
        request_serializer,
        response_deserializer,
    ):
        self._channel = channel
        self._group = group
        self._method = method
        self._metadata_transformer = metadata_transformer
        self._request_serializer = request_serializer
        self._response_deserializer = response_deserializer

    def __call__(
        self, request_iterator, timeout, metadata=None, protocol_options=None
    ):
        return _stream_stream