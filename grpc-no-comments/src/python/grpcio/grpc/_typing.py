# Copyright 2022 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.
"""Common types for gRPC Sync API"""

from typing import (
    TYPE_CHECKING,
    Any,
    Callable,
    Iterable,
    Iterator,
    Optional,
    Sequence,
    Tuple,
    TypeVar,
    Union,
)

from grpc._cython import cygrpc

if TYPE_CHECKING:
    from grpc import ServicerContext
    from grpc._server import _RPCState

RequestType = TypeVar("RequestType")
ResponseType = TypeVar("ResponseType")
SerializingFunction = Callable[[Any], bytes]
DeserializingFunction = Callable[[bytes], Any]
MetadataType = Sequence[Tuple[str, Union[str, bytes]]]
ChannelArgumentType = Tuple[str, Any]
DoneCallbackType = Callable[[Any], None]
NullaryCallbackType = Callable[[], None]
RequestIterableType = Iterable[Any]
ResponseIterableType = Iterable[Any]
UserTag = Callable[[cygrpc.BaseEvent], bool]
IntegratedCallFactory = Callable[
    [
        int,
        bytes,
        None,
        Optional[float],
        Optional[MetadataType],
        Optional[cygrpc.CallCredentials],
        Sequence[Sequence[cygrpc.Operation]],
        UserTag,
        Any,
    ],
    cygrpc.IntegratedCall,
]
ServerTagCallbackType = Tuple[
    Optional["_RPCState"], Sequence[NullaryCallbackType]
]
ServerCallbackTag = Callable[[cygrpc.BaseEvent], ServerTagCallbackType]
ArityAgnosticMethodHandler = Union[
    Callable[
        [RequestType, "ServicerContext", Callable[[ResponseType], None]],
        ResponseType,
    ],
    Callable[
        [RequestType, "ServicerContext", Callable[[ResponseType], None]],
        Iterator[ResponseType],
    ],
    Callable[
        [
            Iterator[RequestType],
            "ServicerContext",
            Callable[[ResponseType], None],
        ],
        ResponseType,
    ],
    Callable[
        [
            Iterator[RequestType],
            "ServicerContext",
            Callable[[ResponseType], None],
        ],
        Iterator[ResponseType],
    ],
    Callable[[RequestType, "ServicerContext"], ResponseType],
    Callable[[RequestType, "ServicerContext"], Iterator[ResponseType]],
    Callable[[Iterator[RequestType], "ServicerContext"], ResponseType],
    Callable[
        [Iterator[RequestType], "ServicerContext"], Iterator[ResponseType]
    ],
]
