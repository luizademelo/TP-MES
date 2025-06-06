# Copyright 2019 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

cdef enum AioChannelStatus:
    AIO_CHANNEL_STATUS_UNKNOWN
    AIO_CHANNEL_STATUS_READY
    AIO_CHANNEL_STATUS_CLOSING
    AIO_CHANNEL_STATUS_DESTROYED

cdef class AioChannel:
    cdef:
        grpc_channel * channel
        object loop
        bytes _target
        AioChannelStatus _status
        bint _is_secure
